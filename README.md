# HelloVoxel
HelloVoxel is dead simple 3D endless runner game being developed in C++ and OpenGL as my C++/gamedev learning effort. It uses GLFW library to handle window/context creation and gathering input, GLAD extension loader for OpenGL and GLM for math. Currently it's in kind of pre-alpha stage, a lot of things are missing.

![Hello Voxel](hellovoxel.jpg?raw=true "Hello Voxel")

Gameplay is quite simple, your task as to go as far as you can avoiding collisions with obstacles (latter is optional at least until I implement collision detection ¯\\_(ツ)_/¯)

When finished it would be something like Voxel Rush mobile game by HyperBees.


TBD:

* bugfixes and refactoring;

* collisions: AABB collisions with collision direction checking at first, later switch to OBB;

* better entity design that allow for different behaviors or states and reactions to events (i. e. collisions);

* ok, better design for everything;

* powerups and game events like in original Voxel Rush game (powerups are this small red things and they have no effect for now due to absence of collision detection);

* better renderer capable of rendering to texture and instancing and not being that slow;

* postprocessing (motion blur, chromatic abberations, etc);

* particles;

* model loading if it makes sense for game where the only model is a cube and mostly single color textures;

* HUD and game menus;

* scoring;

* better player controls, gamepad support, mb make some use of keyboard;

* sound;
