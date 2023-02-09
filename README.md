# What is this?
To be honest, I don't know. I want it to be alive, and breathe, and have almost unlimited replayability. But still be cool. I don't care about graphics though.

I suppose I could make it similar to No Man's Sky idea, but 2D.

Or a high-fantasy dragon-slayer game.

Or a flesh pit national park roguelike?

Or a terraforming game!

Or a cave ecosystem simulator.

Or all of them.

It could even be minecraft in the future.

https://youtu.be/yTB8qDbfhBg. 
could be what minecraft failed to be

# Engine
Place the engine source code (regardless of platform) inside `src/engine`.

https://github.com/MumflrFumperdink/olcPGEMac

# Design Pattern highly inspired in:
https://github.com/munificent/hauberk

# Broad inspiration
- https://github.com/CleverRaven/Cataclysm-DDA
- https://codereview.stackexchange.com/questions/254731/dwarf-fortress-clone-c
- https://github.com/th3v0ice/Dwarf_Fortress_Clone
- https://github.com/h4ctar/yadf
- https://github.com/Trevoke/dwarlixir
- https://docs.unity3d.com/Packages/com.unity.entities@0.51/manual/index.html
- https://www.youtube.com/watch?v=JKFC-TIGCO4&ab_channel=C0

# Dwarf fortress inspiration
- https://dwarffortresswiki.org/index.php/DF2014:Raw_file
- https://dwarffortresswiki.org/index.php/DF2014:Modding
- https://dwarffortresswiki.org/index.php/DF2014:Token
- https://dwarffortresswiki.org/index.php/DF2014:Tile
- https://dwarffortresswiki.org/index.php/DF2014:Inorganic_material_definition_token#SOIL

# Scientific data
- https://www.mars.asu.edu/data/
- http://www.mars.asu.edu/data/mola_color/
- https://en.wikipedia.org/wiki/Martian_soil
- https://en.wikipedia.org/wiki/Space_suit#Requirements

# Tilesets
https://vurmux.itch.io/urizen-onebit-tilesets  
https://v3x3d.itch.io/bountiful-bits  
https://lightcone-games.itch.io/the-1-bit-space-pack  

# Progress
- [X] Tile system
- [X] ASCII Sprite Tile Representations with colors
- [X] Tile Color variance for same context
- [X] Tile Sprite variance for same context
- [X] Third dimension
- [X] Rethink the current framework into separate systems
- [X] Tile primary & secondary color
- [X] Entities
  - [X] Organic and inorganic tiles
  - [X] Trees
  - [X] Creatures
  - [X] Small plants
- [X] Multilevel view
- [X] Code refactor
- [X] Change tileset to something prettier
- [X] Create grass
- [X] Real-time updates (with TPS)
- [ ] **Maintain goal of creating a **realistic** biome, then re-structure system from there.
  - Inheritance-based approach isn't that bad for now. Leave ECS for later.
- [ ] Introduce my own data structures for Vectors and Colors
- [ ] Add new sprites (e.g. surfaces and leaves from bountiful)
- [ ] Add automatic analog color variation
- [ ] Consider removing manual background color, that will save A LOT of space.
- [ ] Refactor leftover pointers into references
- [ ] Review Tile system
  - [ ] Remove "sand" named variables lol
  - [ ] Natural tyle. The hell is that?
  - [ ] Everything else
- [ ] Add sprite rotation system
- [ ] Investigate if there's any way to refactor the relation between World and Organism
- [ ] Approach for different biomes
- [ ] Create a better tile/organism system
  - [ ] Organize metadata system, it is COMPLETELY fucked up. Gladly not used, *yet*.
  - [ ] Track organisms outside of the grid
  - [ ] Tiles can have two things: What's its surface, and whats on top of it. Like DF.
- [ ] Introduce data oriented system. I'm tired of recompiling and calling builders inside headers.
- [ ] Refine the compilation system for faster building
- [ ] Player (Astronaut)
    - [ ] View mode (K)
- [ ] Create grass!
- [ ] Occlusion
- [ ] Separate OLC pixel game engine classes from mine (vi2d and Pixel)
- [ ] Color schemes (DF)
- [ ] Tile sprite & color variance by context
  - [ ] Slopes
  - [ ] Multi-level view
- [ ] Procedurally generate materials and creatures
- [ ] Procedurally generate planets and its geology
- [ ] Environment dynamics (weather, etc)
- [ ] Space travel & spaceship
- [ ] Octotrees

# Idea Dump
### Tile Size: two meters long, two meters wide, and three meters high
