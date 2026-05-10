<h1 align="center">RLSL 🖼️</h1>
<p align="center">A custom shading language made to be used for different graphics APIs in the OpenGL 3.3 and DirectX 10 era</p>

## Motivation
For renderers or engines that use mutliple graphics APIs, different shaders might need to be compiled for their respective backend. This makes writing shaders tedious since is has to be written for every unique backend. This project tries to solve this problem by having one shader as a single source of truth that then gets transpiled into the right shader code that is compatible with a certain graphics API.

## Target Languages
- GLSL 330
- GLSL ES 3.00
- HSLS 4.0