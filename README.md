glfw_test
============

A small engine implementation. Started as a basic test of OpenGL + GLFW but evolved into a small game 
engine. Mostly in C++, with some code (File IO) done in C for fast its fast IO.

### Features

Simple engine implementation. It includes a 
- asynchronous assets loader
- half-done .obj mesh loader (it loads the geometry but not the material properties)
- shader loading from files 
- small wrappers for opengl primitives (shader, program, etc.)
- a vs/fs shader pipeline with uv texturing and basic blinn-phong ambient/specular/diffuse lightning
- basic fps camera primitive 

### Requires

- libSOIL
- GLFW3
- glm (lineal algebra)
- OpenGL 3.3+

### TODO

- Implement material loading 
