<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">GLESC Game Engine</h3>

  <p align="center">
    A c++ game engine using OpenGL and SDL2 based on ECS architecture.
    <br />
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template"><strong>Read the documentation »</strong></a>
    <br />
    <br />
    <a href="https://github.com/othneildrew/Best-README-Template">View Demo</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    ·
    <a href="https://github.com/othneildrew/Best-README-Template/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>


<!-- ABOUT THE PROJECT -->

## About The Project

[![Product Name Screen Shot]([GLESC-logo])](https://github.com/valydumitru01/GLESC)

<p>GLESC is a game engine implemented in C++ using OpenGL and SDL2. It is a final degree project for the Bachelor's 
Degree in Computer Engineering at the University of Oviedo. It's development lasted 1 year and a half of 
full-time work of a single person - <a href="#MyPortfolio">me</a>. <br>
The engine allows 3D rendering, shaders, physics, collisions, inputs and audio while also taking advantage of
ECS architecture (good cacheing).</p>

The project was developed with some principles in mind:

* **Modularity or Separation of Concerns (SoC)**: The engine is divided into modules, each one with a specific purpose.
  This allows for easy maintenance and scalability.
* **Performance**: The engine is designed to be as fast as possible. It uses ECS architecture, which is cache-friendly.
* **DRY**: The engine is designed to be as pretty DRY, but sometimes there is code repetition and it is not as DRY as it
  should be. This is because of the lack of time and experience of the developer. And sometimes for readability reasons.
* **KISS**: The engine is designed to be as simple as possible. This does not mean it is simple. It means that it is not
  more complex than it needs to be. Unfortunately, by definition, a game engine is a complex piece of software.
* **SOLID**: The engine is designed to be as SOLID as possible. This means that the code is easy to maintain and extend.
It takes advantage of c++'s OOP and polymorphism to improve SOLID principles.
* **Documentation**: The engine is well documented, as it is a requirement for the assignment of the degree project.

> **Note**: It's important to take into consideration the huge constraints of the project:
> * The lack of experience of the developer
> * The lack of time and the time restrictions
> * The lack of resources (hardware and software)
> * The lack of knowledge of the developer (therefore a lot of time was spent learning). 
> 
> This project is not perfect and has some ugly workarounds, some poor design decisions, some bugs, and some performance
> issues. But it has also some great design decisions, some great code, and some great performance that took a lot of time
> and effort to achieve.

### Built With

This section should list any major frameworks/libraries used to bootstrap your project. Leave any add-ons/plugins for the acknowledgements section. Here are a few examples.

* [![Next][Next.js]][Next-url]
* [![React][React.js]][React-url]
* [![Vue][Vue.js]][Vue-url]
* [![Angular][Angular.io]][Angular-url]
* [![Svelte][Svelte.dev]][Svelte-url]
* [![Laravel][Laravel.com]][Laravel-url]
* [![Bootstrap][Bootstrap.com]][Bootstrap-url]
* [![JQuery][JQuery.com]][JQuery-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>




# Code restrictions

Version of c++:

# Application Dependencies <a name="dependencies"></a>

**Important:** The only dependency you need to actually install is Mingw32 64 bits, the rest are static (portable).
Which means they are inside the repository (`lib` folder)

## 1. MinGW/GNU Compiler Collection (GCC) <a name="gcc"></a>

In order to execute our code, we will require GNU utilities. This contains numerous compilers for various languages (
e.g. Fortran, C++ etc.) classified as the **GNU Compiler Collection (GCC)**, and their respective debuggers.

**MinGW ("Minimalist GNU for Windows")** is a free and open source software development environment to create Microsoft
Windows applications.

MinGW includes a port of the **GNU Compiler Collection (GCC)**, GNU Binutils for Windows (assembler, linker, archive
manager), a set of freely distributable Windows specific header files and static import libraries which enable the use
of the Windows API, a Windows native build of the GNU Project's GNU Debugger, and miscellaneous utilities.

[Download here (Installer)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)

> _**IMPORTANT:** MUST SELECT x86_64 (which is 64 bits) **NOT** i686 (which is 32 bits)_

In case the installer doesn't work (which is likely):

[Download here (folder with 64 bits version)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z/download)

> _**HOW TO INSTALL:**_
>
> - Unzip the folder, copy it somewhere logical (for example `C:/MinGW` or `C:/Program Files/MinGW`).
> - Add to the path of the Environment Variables the bin folder.

* [MinGW wiki](http://mingw.org/)

---

## 2. SDL <a name ="sdl"></a>

**Simple DirectMedia Layer (SDL)** is a cross-platform software development library designed to provide a hardware
abstraction layer for computer multimedia hardware components.
SDL manages video, audio, input devices, CD-ROM, threads, shared object loading, networking and timers.

* [Download here](http://libsdl.org/download-2.0.php)

* [SDL2 wiki](http://wiki.libsdl.org/FrontPage)

### 2.1 SDL_ttf

* [Download here](https://www.libsdl.org/projects/SDL_ttf/release/)

### 2.2 SDL_image

* [Download here](https://www.libsdl.org/projects/SDL_image/)

### 2.3 SDL_mixer

* [Download here](https://www.libsdl.org/projects/SDL_mixer/)

### 2.4 SDL_net

* [Download here](https://www.libsdl.org/projects/SDL_net/)

> _**IMPORTANT:** MUST SELECT x86_64 (which is 64 bits) **NOT** i686 (which is 32 bits)_

* [Wiki of SDL_net, SDL_mixer, SDL_ttf and SDL_image](https://wiki.libsdl.org/Libraries)

---

## 3. OpenGL <a name ="opengl"></a>

The **Open Graphics Library (OpenGL)** is a specification of various operations (functions) that facilite the rendering
and manipulation of images, and other graphical niceties on our displays. The functions and the specification as a whole
is maintained by the Khronos Group; a body of various industry experts, GPU manufactors, and related companies that
collaborate to continually improve upon the capabilities of OpenGL -and the core requirements that supporting hardware
should implement. The key word there is 'should'.

As OpenGL is **NOT** actually a set of classes/libraries or Application Programming Interfaces (APIs), it falls upon the
Graphics Card Manufactors to implement the defined requirements i.e. they create the libraries, and classes that help
you to run your favorite games via software called drivers. Installing these drivers will allow you to access core
OpenGL functuality, and any further extensions to the specification which were supported by your Graphics card at the
time of release.

* [OpenGL Wiki](https://www.opengl.org/)

---

## 4. GLEW <a name ="glm"></a>

The OpenGL Extension Wrangler Library.
GLEW provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target
platform.
It allows us to check at runtime which extensions are present and which functions may be used. Basically allows you to
use OpenGL under the same interface no matter the SO you're in, simplifying it's interface.

* [Download](http://glew.sourceforge.net/install.html)

* [Video explaining how it works and how to install](https://www.youtube.com/watch?v=rQvWQDq3rLc)

* [GLEW wiki](https://en.wikipedia.org/wiki/OpenGL#Extension_loading_libraries)

[![License][license-shield]][license-url]
[![Issues][issues-shield]][issues-url]
[![Forks][forks-shield]][forks-url]
[![Stars][stars-shield]][stars-url]
[![Pull Requests][pull-requests-shield]][pull-requests-url]
[![C++][cpp-shield]][cpp-url]
[![Game Engine][game-engine-shield]][game-engine-url]
[![Version][version-shield]][version-url]
[![Platform][platform-shield]][platform-url]
[![Code Style][code-style-shield]][code-style-url]
[![Documentation][documentation-shield]][documentation-url]
[![Build With][build-with-shield]][build-with-url]

<!-- Build with shields -->
[![C++][cpp-shield]][cpp-url]
[![CMake][CMake-shield]][CMake-url]
[![OpenGL][OpenGL-shield]][OpenGL-url]
[![SDL2][SDL2-shield]][SDL2-url]
[![GLEW][GLEW-shield]][GLEW-url]
[![ImGui][ImGui-shield]][ImGui-url]

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[license-shield]: https://img.shields.io/badge/license-MIT-blue?style=for-the-badge
[issues-shield]: https://img.shields.io/github/issues/valydumitru01/GLESC?style=for-the-badge
[forks-shield]: https://img.shields.io/github/forks/valydumitru01/GLESC?style=for-the-badge
[stars-shield]: https://img.shields.io/github/stars/valydumitru01/GLESC?style=for-the-badge
[pull-requests-shield]: https://img.shields.io/github/issues-pr/valydumitru01/GLESC?style=for-the-badge
[game-engine-shield]: 
https://img.shields.io/badge/game_engine-C%2B%2B-00599C?style=for-the-badge&logo=game-engine&logoColor=white
[version-shield]: https://img.shields.io/badge/version-1.0.0-blue?style=for-the-badge
[platform-shield]: 
https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20MacOS-informational?style=for-the-badge
[code-style-shield]: https://img.shields.io/badge/code_style-LLVM-AB47BC?style=for-the-badge
[documentation-shield]: https://img.shields.io/badge/documentation-available-brightgreen?style=for-the-badge
[build-with-shield]: https://img.shields.io/badge/build_with-CMake-064F8C?style=for-the-badge&logo=cmake

<!-- Build with shields -->
[cpp-shield]: https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white
[CMake-shield]: https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white
[OpenGL-shield]: https://img.shields.io/badge/OpenGL-5586A4?style=for-the-badge&logo=opengl&logoColor=white
[SDL2-shield]: https://img.shields.io/badge/SDL2-FFCC00?style=for-the-badge&logo=sdl&logoColor=white
[GLEW-shield]: https://img.shields.io/badge/GLEW-FFCC00?style=for-the-badge&logo=glew&logoColor=white
[ImGui-shield]: https://img.shields.io/badge/ImGui-FF6F61?style=for-the-badge&logo=imgui&logoColor=white

<!-- Build with urls -->
[cpp-url]: https://cplusplus.com/
[CMake-url]: https://cmake.org/
[OpenGL-url]: https://www.opengl.org/
[SDL2-url]: https://www.libsdl.org/
[GLEW-url]: http://glew.sourceforge.net/
[ImGui-url]: https

[issues-url]: https://github.com/valydumitru01/GLESC/issues
[forks-url]: https://github.com/valydumitru01/GLESC/network/members
[stars-url]: https://github.com/valydumitru01/GLESC/stargazers
[pull-requests-url]: https://github.com/valydumitru01/GLESC/pulls
[project-url]: https://github.com/valydumitru01/GLESC
[cpp-url]: https://cplusplus.com/

[license-url]: LICENSE.txt
[project-version]: 0.0.1
[code-style-file-url]: doc/CODE_STYLE.md
[documentation-url]: doc/TFG_GLESC_Documentation.pdf
[GLESC_logo]: doc/images/GLESC_logo.png
[executable-download-url]:  