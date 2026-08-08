#include "platform/pixel_engine.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <array>
#include <cstdio>
#include <cstring>

namespace pge {

// ---------- Sprite ----------

Sprite::Sprite(const std::string& path) {
    SDL_Surface* raw = IMG_Load(path.c_str());
    if (!raw) {
        std::fprintf(stderr, "[pge] Failed to load image '%s': %s\n",
                     path.c_str(), IMG_GetError());
        return;
    }
    SDL_Surface* conv = SDL_ConvertSurfaceFormat(raw, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(raw);
    if (!conv) {
        std::fprintf(stderr, "[pge] Failed to convert image '%s': %s\n",
                     path.c_str(), SDL_GetError());
        return;
    }
    w = conv->w;
    h = conv->h;
    pixels.resize(static_cast<size_t>(w) * h);

    SDL_LockSurface(conv);
    const uint8_t* src = static_cast<const uint8_t*>(conv->pixels);
    for (int y = 0; y < h; ++y) {
        std::memcpy(&pixels[static_cast<size_t>(y) * w],
                    src + y * conv->pitch,
                    static_cast<size_t>(w) * 4);
    }
    SDL_UnlockSurface(conv);
    SDL_FreeSurface(conv);
}

Color Sprite::GetPixel(int x, int y) const {
    if (x < 0 || y < 0 || x >= w || y >= h) return Color{};
    return pixels[static_cast<size_t>(y) * w + x];
}

// ---------- Engine impl ----------

namespace {

SDL_Scancode mapKey(Key k) {
    switch (k) {
        case Key::A: return SDL_SCANCODE_A;
        case Key::B: return SDL_SCANCODE_B;
        case Key::C: return SDL_SCANCODE_C;
        case Key::D: return SDL_SCANCODE_D;
        case Key::E: return SDL_SCANCODE_E;
        case Key::F: return SDL_SCANCODE_F;
        case Key::G: return SDL_SCANCODE_G;
        case Key::H: return SDL_SCANCODE_H;
        case Key::I: return SDL_SCANCODE_I;
        case Key::J: return SDL_SCANCODE_J;
        case Key::K: return SDL_SCANCODE_K;
        case Key::L: return SDL_SCANCODE_L;
        case Key::M: return SDL_SCANCODE_M;
        case Key::N: return SDL_SCANCODE_N;
        case Key::O: return SDL_SCANCODE_O;
        case Key::P: return SDL_SCANCODE_P;
        case Key::Q: return SDL_SCANCODE_Q;
        case Key::R: return SDL_SCANCODE_R;
        case Key::S: return SDL_SCANCODE_S;
        case Key::T: return SDL_SCANCODE_T;
        case Key::U: return SDL_SCANCODE_U;
        case Key::V: return SDL_SCANCODE_V;
        case Key::W: return SDL_SCANCODE_W;
        case Key::X: return SDL_SCANCODE_X;
        case Key::Y: return SDL_SCANCODE_Y;
        case Key::Z: return SDL_SCANCODE_Z;
        case Key::K0: return SDL_SCANCODE_0;
        case Key::K1: return SDL_SCANCODE_1;
        case Key::K2: return SDL_SCANCODE_2;
        case Key::K3: return SDL_SCANCODE_3;
        case Key::K4: return SDL_SCANCODE_4;
        case Key::K5: return SDL_SCANCODE_5;
        case Key::K6: return SDL_SCANCODE_6;
        case Key::K7: return SDL_SCANCODE_7;
        case Key::K8: return SDL_SCANCODE_8;
        case Key::K9: return SDL_SCANCODE_9;
        case Key::UP:     return SDL_SCANCODE_UP;
        case Key::DOWN:   return SDL_SCANCODE_DOWN;
        case Key::LEFT:   return SDL_SCANCODE_LEFT;
        case Key::RIGHT:  return SDL_SCANCODE_RIGHT;
        case Key::SPACE:  return SDL_SCANCODE_SPACE;
        case Key::ENTER:  return SDL_SCANCODE_RETURN;
        case Key::ESCAPE: return SDL_SCANCODE_ESCAPE;
        case Key::TAB:    return SDL_SCANCODE_TAB;
        case Key::BACK:   return SDL_SCANCODE_BACKSPACE;
        case Key::INS:    return SDL_SCANCODE_INSERT;
        case Key::DEL:    return SDL_SCANCODE_DELETE;
        case Key::HOME:   return SDL_SCANCODE_HOME;
        case Key::END:    return SDL_SCANCODE_END;
        case Key::PGUP:   return SDL_SCANCODE_PAGEUP;
        case Key::PGDN:   return SDL_SCANCODE_PAGEDOWN;
        case Key::SHIFT:  return SDL_SCANCODE_LSHIFT;
        case Key::CTRL:   return SDL_SCANCODE_LCTRL;
        case Key::NONE:   default: return SDL_SCANCODE_UNKNOWN;
    }
}

TTF_Font* tryOpenSystemFont(int ptSize) {
    const char* candidates[] = {
        "assets/fonts/font.ttf",
#ifdef __APPLE__
        "/System/Library/Fonts/Monaco.ttf",
        "/System/Library/Fonts/Menlo.ttc",
        "/System/Library/Fonts/Supplemental/Courier New.ttf",
        "/Library/Fonts/Courier New.ttf",
#elif defined(_WIN32)
        "C:/Windows/Fonts/consola.ttf",
        "C:/Windows/Fonts/cour.ttf",
        "C:/Windows/Fonts/arial.ttf",
#else
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/TTF/DejaVuSansMono.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf",
#endif
    };
    for (const char* p : candidates) {
        if (TTF_Font* f = TTF_OpenFont(p, ptSize)) return f;
    }
    return nullptr;
}

}  // namespace

struct PixelGameEngine::Impl {
    SDL_Window*   window   {nullptr};
    SDL_Renderer* renderer {nullptr};
    SDL_Texture*  fbTex    {nullptr};
    TTF_Font*     font     {nullptr};

    std::vector<Color> framebuffer;

    std::array<bool, SDL_NUM_SCANCODES> currKeys{};
    std::array<bool, SDL_NUM_SCANCODES> prevKeys{};

    bool running {false};
    bool sdlReady{false};
    bool imgReady{false};
    bool ttfReady{false};
};

PixelGameEngine::PixelGameEngine() : impl(std::make_unique<Impl>()) {}

PixelGameEngine::~PixelGameEngine() {
    if (!impl) return;
    if (impl->font)     TTF_CloseFont(impl->font);
    if (impl->fbTex)    SDL_DestroyTexture(impl->fbTex);
    if (impl->renderer) SDL_DestroyRenderer(impl->renderer);
    if (impl->window)   SDL_DestroyWindow(impl->window);
    if (impl->ttfReady) TTF_Quit();
    if (impl->imgReady) IMG_Quit();
    if (impl->sdlReady) SDL_Quit();
}

bool PixelGameEngine::Construct(int w, int h, int pixelW, int pixelH, bool fullscreen) {
    if (w <= 0 || h <= 0 || pixelW <= 0 || pixelH <= 0) return false;
    screenW = w;
    screenH = h;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::fprintf(stderr, "[pge] SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }
    impl->sdlReady = true;

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::fprintf(stderr, "[pge] IMG_Init failed: %s\n", IMG_GetError());
    } else {
        impl->imgReady = true;
    }

    if (TTF_Init() != 0) {
        std::fprintf(stderr, "[pge] TTF_Init failed: %s\n", TTF_GetError());
    } else {
        impl->ttfReady = true;
    }

    Uint32 winFlags = SDL_WINDOW_ALLOW_HIGHDPI;
    if (fullscreen) winFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

    int winW = w * pixelW;
    int winH = h * pixelH;

    impl->window = SDL_CreateWindow(sAppName.c_str(),
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    winW, winH, winFlags);
    if (!impl->window) {
        std::fprintf(stderr, "[pge] SDL_CreateWindow failed: %s\n", SDL_GetError());
        return false;
    }

    impl->renderer = SDL_CreateRenderer(impl->window, -1,
                                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!impl->renderer) {
        impl->renderer = SDL_CreateRenderer(impl->window, -1, 0);
    }
    if (!impl->renderer) {
        std::fprintf(stderr, "[pge] SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return false;
    }

    SDL_RenderSetLogicalSize(impl->renderer, w, h);
    SDL_SetRenderDrawBlendMode(impl->renderer, SDL_BLENDMODE_NONE);

    impl->fbTex = SDL_CreateTexture(impl->renderer,
                                    SDL_PIXELFORMAT_RGBA32,
                                    SDL_TEXTUREACCESS_STREAMING,
                                    w, h);
    if (!impl->fbTex) {
        std::fprintf(stderr, "[pge] SDL_CreateTexture failed: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetTextureBlendMode(impl->fbTex, SDL_BLENDMODE_NONE);

    impl->framebuffer.assign(static_cast<size_t>(w) * h, Color{0, 0, 0, 255});

    if (impl->ttfReady) {
        impl->font = tryOpenSystemFont(8);
        if (!impl->font) {
            std::fprintf(stderr,
                "[pge] No usable font found. DrawString will be a no-op. "
                "Drop a TTF at assets/fonts/font.ttf to enable debug text.\n");
        }
    }
    return true;
}

void PixelGameEngine::Clear(Color c) {
    if (!impl) return;
    for (auto& px : impl->framebuffer) px = c;
}

void PixelGameEngine::Draw(int x, int y, Color c) {
    if (x < 0 || y < 0 || x >= screenW || y >= screenH) return;
    impl->framebuffer[static_cast<size_t>(y) * screenW + x] = c;
}

void PixelGameEngine::Draw(const vi2d& pos, Color c) { Draw(pos.x, pos.y, c); }

void PixelGameEngine::DrawString(const vi2d& pos, const std::string& text, Color c, int scale) {
    if (!impl || !impl->font || text.empty()) return;
    SDL_Color sc { c.r, c.g, c.b, c.a };
    SDL_Surface* s = TTF_RenderUTF8_Solid(impl->font, text.c_str(), sc);
    if (!s) return;
    SDL_Surface* conv = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(s);
    if (!conv) return;

    SDL_LockSurface(conv);
    const uint8_t* src = static_cast<const uint8_t*>(conv->pixels);
    for (int yy = 0; yy < conv->h; ++yy) {
        for (int xx = 0; xx < conv->w; ++xx) {
            const uint8_t* p = src + yy * conv->pitch + xx * 4;
            if (p[3] == 0) continue;
            for (int dy = 0; dy < scale; ++dy)
                for (int dx = 0; dx < scale; ++dx)
                    Draw(pos.x + xx * scale + dx, pos.y + yy * scale + dy, c);
        }
    }
    SDL_UnlockSurface(conv);
    SDL_FreeSurface(conv);
}

KeyState PixelGameEngine::GetKey(Key k) const {
    KeyState s;
    SDL_Scancode sc = mapKey(k);
    if (sc == SDL_SCANCODE_UNKNOWN) return s;
    bool curr = impl->currKeys[sc];
    bool prev = impl->prevKeys[sc];
    s.bHeld     = curr;
    s.bPressed  = curr && !prev;
    s.bReleased = !curr && prev;
    return s;
}

void PixelGameEngine::Start() {
    if (!impl || !impl->renderer) return;

    if (!OnUserCreate()) return;

    impl->running = true;
    Uint64 prevCounter = SDL_GetPerformanceCounter();
    const double freq = static_cast<double>(SDL_GetPerformanceFrequency());

    while (impl->running) {
        impl->prevKeys = impl->currKeys;

        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) impl->running = false;
        }
        const Uint8* keyboard = SDL_GetKeyboardState(nullptr);
        for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
            impl->currKeys[i] = keyboard[i] != 0;
        }

        SDL_Keymod mods = SDL_GetModState();
        if (impl->currKeys[SDL_SCANCODE_Q] && (mods & (KMOD_GUI | KMOD_CTRL))) {
            impl->running = false;
        }

        Uint64 nowCounter = SDL_GetPerformanceCounter();
        float dt = static_cast<float>((nowCounter - prevCounter) / freq);
        prevCounter = nowCounter;
        if (dt > 0.25f) dt = 0.25f;

        if (!OnUserUpdate(dt)) impl->running = false;

        SDL_UpdateTexture(impl->fbTex, nullptr,
                          impl->framebuffer.data(),
                          screenW * static_cast<int>(sizeof(Color)));
        SDL_RenderClear(impl->renderer);
        SDL_RenderCopy(impl->renderer, impl->fbTex, nullptr, nullptr);
        SDL_RenderPresent(impl->renderer);
    }
}

}  // namespace pge
