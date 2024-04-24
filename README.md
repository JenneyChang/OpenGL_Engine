# OpenGL_Engine
## Description
A game engine prototype using custom set of static libraries, a conversion tool, and OpenGL. 
## Demos
The engine has 3 predefined demos. The demos can be activated by setting the #define value to true in the Game.cpp file. 
```cpp
#define DEMO1 1
#define DEMO2 0
#define DEMO3 0
```
1. Demo 1: 2D Sprite and Font system
2. Demo 2: 3D System
3. Demo 3: Skinned Animations

## Instructions
1. Download converted data from google drive: https://drive.google.com/drive/folders/1OyBEGHnjmBhas2M6Qef55FK0_YezYSsy?usp=sharing
2. Place converted data into OpenGL\Data folder.
3. Open project solution, set desired demo to true, and Run.

## Documentation
### Table of Contents
* [Engine Loop](#engine-loop)
* [Camera](#camera)
* [Shader Objects](#shader-objects)
* [Game Objects](#game-objects)
* [Graphics Objects](#graphics-objects)
* [Models](#models)
* [Animation](#animation)

#### Engine Loop
Upon startup, a Game Manager singleton creates an instance of the Game. The Game class in turn instantiates the Engine singleton class. The Game instance loads all relevant content through various singleton Managers (textures, game objects, animation, etc). The Engine class loops to update and draw all game events. Once the user exits, the content is cleanly unloaded by their respective singleton Managers.
```cpp

```
### Camera
Engine allows for the use of multiple cameras; all cameras are created and managed through managers.
1. Orthogrpahic (Camera 2D)<br>
>```cpp
>
>```
2. Perspective (Camera 3D)<br>

### Shader Objects
### Game Objects
### Graphics Objects
### Models
### Animation
