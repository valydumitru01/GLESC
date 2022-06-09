
# Table of Contents
1. [Introduction](#introduction)
2. [Required Tools](#tools)
3. [Application Dependencies](#dependencies) <span style="color:cyan">_**(EVERYTING MUST BE 32 BITS)**_</span> 
    1. [MinGW/GCC](#gcc)
    2. [SDL2](#sdl)
    3. [OpenGL](#opengl)
    4. [GLEW](#glew)
    5. [GLM](#glm)
    6. [OpenAL](#openal)
    7. [Bullet](#bullet)
3. [Documentation](#documentation)
# Introduction <a name="introduction"></a>
![](/doc/images/Game_Prototype_1.png)
## What is this game about?
This game will be an isometric 2D turn based game with a lot of familiar/minion/companion functionalities. Such as being able to gather a team to fight on your side and owning pets. 

### Main character
The basic idea is that a main character goes around finding team members and convincing them to join him/her. The main character should be strong compared to the other team members, but not necessarily the strongest, that could change depending on the build you try. 

### Team members
The team members are monsters (or people) you find around the world. You have to gather them to make your team stronger, althogh you can only use a limited amount of them at once in a battle. 

### Pets
Pets are little friends (primarily monsters) you find around the world. These pets can be obtained fighting enemies, dropping them as if they were their "children". They can also be found around the world, like fairies or monkeys. They dont (usually) attack but only give buffs and bonuses to the character they follow. Each team member can have their own pet.
### Battle
Battles are turn based with tactical positioning. It includes mechanics such as AOE abilities, ground advantage, use of environment (push boulder) between others.  

![](/doc/images/Prototype_Battle_1.png)

## 32 Bits project
This game uses 32 bits, which means we can only use 4 GB of ram (even less due to some operating system space). This is not a big restriction for us hence the game will be simple and 2D. This will be a first touch with game development for most of the integrants of our team, and it should be ok. We must learn how to avoid memory leaks and to occupy too much memory. This will be a learning experience for all of us. 
## Relationship between SDL2 and OpenGL
Explanation why are SDL and OpenGL related, so we can understand better what we are doing.

[Why is SDL and OpenGL related?](https://stackoverflow.com/questions/5769031/why-are-sdl-and-opengl-related)

## Examples of other games on Github
[Games in Github](https://github.com/leereilly/gameshttps://github.com/leereilly/games)

## Original structure from where the project started (Github)
[Original Project](https://github.com/kbrawley95/VSCode-OpenGL-Game-Engine)


# Required Tools <a name="tools"></a>

1. [Git](https://git-scm.com/) / [Github](https://desktop.github.com/)
2.  (Optional) [Visual Studio Code](https://code.visualstudio.com/)
3. (Optional) [Vmware Player Virtual Machine](https://www.vmware.com/products/player/playerpro-evaluation.html) for testing your code on different operating systems.


# Application Dependencies <a name="dependencies"></a>

## 1. MinGW/GNU Compiler Collection (GCC) <a name="gcc"></a>

In order to execute our code, we will require GNU utilities. This contains numerous compilers for various languages (e.g. Fortran, C++ etc.) classified as the **GNU Compiler Collection (GCC)**, and their respective debuggers.

**MinGW ("Minimalist GNU for Windows")** is a free and open source software development environment to create Microsoft Windows applications.

MinGW includes a port of the **GNU Compiler Collection (GCC)**, GNU Binutils for Windows (assembler, linker, archive manager), a set of freely distributable Windows specific header files and static import libraries which enable the use of the Windows API, a Windows native build of the GNU Project's GNU Debugger, and miscellaneous utilities. 

[Download here (Installer)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)
>_**IMPORTANT:** MUST SELECT x86_64 (which is 64 bits) **NOT** i686 (which is 32 bits)_

In case the installer doesn't work (which is likely):

[Download here (folder with 32 bits version)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z/download) 
>_**HOW TO INSTALL:**_
>- Unzip the folder, copy it somewhere logical (for example C:/MinGW or C:/Program Files/MinGW).
>- Add to the path of the Environment Variables the bin folder.

___
## 2. SDL <a name ="sdl"></a>
**Simple DirectMedia Layer (SDL)** is a cross-platform software development library designed to provide a hardware abstraction layer for computer multimedia hardware components. 
SDL manages video, audio, input devices, CD-ROM, threads, shared object loading, networking and timers.[5] For 3D graphics

[Download here](http://libsdl.org/download-2.0.php)
>_**IMPORTANT:** MUST SELECT 32 Bits VERSION **NOT** 64 Bits_
___
## 3. OPENGL <a name ="opengl"></a>

The **Open Graphics Library (OpenGL)** is a specification of various operations (functions) that facilite the rendering and manipulation of images, and other graphical niceties on our displays. The functions and the specification as a whole is maintain by the Khronos Group; a body of various industry experts, GPU manufactors, and related companies that collaborate to continually improve upon the capabilties of OpenGL -and the core requirements that supporting hardware should implement. The key word there is 'should'. 

As OpenGL is **NOT** actually set of classes/libaries or **Application Programming Interface (API)**, it falls upon the Graphics Card Manufactors to implement the defined requirements i.e. they create the libraries, and classes that help you to run your favourite games via software called drivers. Installing these drivers will allow you to access core OpenGL functuality, and any further extensions to the specification which were supported by your Graphics card at the time of release. 

___
## 4. GLEW <a name ="glm"></a>

The OpenGL Extension Wrangler Library. 

[Download](http://glew.sourceforge.net/install.html)
___
## 5. GLM <a name ="glm"></a>

GLSL + Optional features = OpenGL Mathematics (GLM)
A C++ mathematics library for graphics programming. 

[Download](http://glm.g-truc.net/0.9.5/index.html)
___
## 6. OPENAL <a name ="openal"></a>

OpenAL is a cross-platform 3D audio API appropriate for use with gaming applications and many other types of audio applications.

The library models a collection of audio sources moving in a 3D space that are heard by a single listener somewhere in that space. The basic OpenAL objects are a Listener, a Source, and a Buffer. There can be a large number of Buffers, which contain audio data. Each buffer can be attached to one or more Sources, which represent points in 3D space which are emitting audio. There is always one Listener object (per audio context), which represents the position where the sources are heard -- rendering is done from the perspective of the Listener.

[Download](http://www.openal.org/)
___
## 7. BULLET <a name ="bullet"></a>

Bullet Physics SDK: real-time collision detection and multi-physics simulation for VR, games, visual effects, robotics, machine learning etc.

[Download](https://github.com/bulletphysics/bullet3/releases)


# Documentation <a name="documentation"></a>
For more information on the materials provided, refer to the sources below:

### Minimalist GNU for Windows
* [MinGW](http://mingw.org/)

### OpenGL & Related Libraries
* [Bullet Physics Documentation](https://github.com/bulletphysics/bullet3)
* [GLEW](https://github.com/nigels-com/glew#authors)
* [GLM](http://glm.g-truc.net/0.9.5/api/index.html)
* [OpenAL](http://www.openal.org/documentation/)
* [OpenGL](https://www.opengl.org/)
* [SDL2](http://wiki.libsdl.org/FrontPage)

### Visual Studio Code
* [VS Portable](http://gareth.flowers/vscode-portable/)
* [Debugging](http://code.visualstudio.com/docs/editor/debugging)
* [Integrated Terminal](https://code.visualstudio.com/docs/editor/integrated-terminal)
* [Tasks](http://code.visualstudio.com/docs/editor/tasks)
