<p align="center">
    <img src="https://rlsl.dev/favicon.png" width="35%">
</p>
<p align="center">A custom shading language made to be used for different graphics APIs in the OpenGL 3.3 and DirectX 10 era</p>

[![Tests](https://github.com/01rasmus/rlsl/actions/workflows/tests.yml/badge.svg?branch=main)](https://github.com/01rasmus/rlsl/actions/workflows/tests.yml)
<a href="LICENSE">
    <img src="https://img.shields.io/badge/license-MIT-green" alt="License">
</a>
<a href="https://rlsl.dev">
    <img src="https://img.shields.io/badge/docs-rlsl.dev-blue" alt="Documentation">
</a>

## Motivation
For renderers or engines that use mutliple graphics APIs, different shaders might need to be compiled for their respective backend. This makes writing shaders tedious since is has to be written for every unique backend. This project tries to solve this problem by having one shader as a single source of truth that then gets transpiled into the right shader code that is compatible with a certain graphics API.

## Target Languages
- GLSL 330
- GLSL ES 3.00
- HSLS 4.0