#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace pge {

struct Color {
    uint8_t r{0}, g{0}, b{0}, a{255};

    constexpr Color() = default;
    constexpr Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_ = 255)
        : r(r_), g(g_), b(b_), a(a_) {}

    constexpr bool operator==(const Color& o) const {
        return r == o.r && g == o.g && b == o.b && a == o.a;
    }
    constexpr bool operator!=(const Color& o) const { return !(*this == o); }
};

inline constexpr Color BLACK   {0, 0, 0};
inline constexpr Color WHITE   {255, 255, 255};
inline constexpr Color YELLOW  {255, 255, 0};
inline constexpr Color RED     {255, 0, 0};
inline constexpr Color GREEN   {0, 255, 0};
inline constexpr Color BLUE    {0, 0, 255};
inline constexpr Color CYAN    {0, 255, 255};
inline constexpr Color MAGENTA {255, 0, 255};
inline constexpr Color GREY    {192, 192, 192};
inline constexpr Color DARK_GREY {128, 128, 128};
inline constexpr Color BLANK   {0, 0, 0, 0};

struct vi2d {
    int x{0}, y{0};

    constexpr vi2d() = default;
    constexpr vi2d(int x_, int y_) : x(x_), y(y_) {}

    constexpr vi2d operator+(const vi2d& o) const { return {x + o.x, y + o.y}; }
    constexpr vi2d operator-(const vi2d& o) const { return {x - o.x, y - o.y}; }
    constexpr vi2d operator*(const vi2d& o) const { return {x * o.x, y * o.y}; }
    constexpr vi2d operator*(int s) const { return {x * s, y * s}; }

    constexpr bool operator==(const vi2d& o) const { return x == o.x && y == o.y; }
    constexpr bool operator!=(const vi2d& o) const { return !(*this == o); }
};

enum class Key {
    NONE = 0,
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
    UP, DOWN, LEFT, RIGHT,
    SPACE, ENTER, ESCAPE, TAB, BACK, INS, DEL, HOME, END,
    PGUP, PGDN, SHIFT, CTRL
};

struct KeyState {
    bool bPressed{false};
    bool bHeld{false};
    bool bReleased{false};
};

class Sprite {
public:
    Sprite() = default;
    explicit Sprite(const std::string& path);

    Color GetPixel(int x, int y) const;
    int width()  const { return w; }
    int height() const { return h; }

private:
    int w{0}, h{0};
    std::vector<Color> pixels;
};

class PixelGameEngine {
public:
    PixelGameEngine();
    virtual ~PixelGameEngine();

    PixelGameEngine(const PixelGameEngine&) = delete;
    PixelGameEngine& operator=(const PixelGameEngine&) = delete;

    bool Construct(int w, int h, int pixelW, int pixelH, bool fullscreen = false);
    void Start();

    int ScreenWidth()  const { return screenW; }
    int ScreenHeight() const { return screenH; }

    void Clear(Color c);
    void Draw(const vi2d& pos, Color c);
    void Draw(int x, int y, Color c);
    void DrawString(const vi2d& pos, const std::string& text, Color c, int scale = 1);

    KeyState GetKey(Key k) const;

    std::string sAppName{"Untitled"};

protected:
    virtual bool OnUserCreate() = 0;
    virtual bool OnUserUpdate(float fElapsedTime) = 0;

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
    int screenW{0}, screenH{0};
};

}  // namespace pge
