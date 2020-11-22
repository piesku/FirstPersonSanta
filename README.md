# FirstPerson

An FPS playground for creating game prototypes in C using ECS. The ECS architecture is based on [Goodluck](https://gdlck.com). Prior attempt: [breakoutc](https://github.com/stasm/breakoutc), [OpenGLESApp1](https://github.com/stasm/OpenGLESApp1).


## Building

### Windows

Install SDL2 and GLEW using `vcpkg`. Open the repo in Visual Studio 2019 using the _Open a local folder_ option.

    $ .\vcpkg.exe install sdl2:x64-windows glew:x64-windows

### Linux (Ubuntu, Debian, WSL)

    $ sudo apt install libsdl2-dev libglew-dev
    $ mkdir out
    $ cd out
    $ cmake ..
    $ make
    $ ./breakoutc

### MacOS

[Download SDL2](https://www.libsdl.org/download-2.0.php) and copy it to `/Library/Frameworks`

    $ mkdir out
    $ cd out
    $ cmake ..
    $ make
    $ ./breakoutc


## Implementation Notes

### Entity indices start at 1
    
Entity 0 is a special "null" entity. When used as `Transform.parent`, it signifies that the transform doesn't have a parent.

### `children[MAX_CHILDREN]`

For simplicity, `Transform.children` is a static array and `MAX_CHILDREN` is 2. The value of the parent field and the values of the children array are entity indices rather than pointers to actual Transforms.

### Forward declarations and typedefs

Forward declarations are used for most structs when they're used as opaque pointers. This helps avoid creating extra dependencies between header files.  For the same reason, I avoided typedefs, except for: `entity`, `signature`, component data structs and math data types.

### Client and the world (on Android)

`struct world` stores the component data of the current scene. It persists until the app is killed. `struct client` is similar to the `Game` class from Goodluck in TypeScript, and it stores data and references related to the GL context, the viewport and the input. Importantly, client is destroyed every time the app is sent to backgournd, and recreated every time it resumes. All shaders and vertex buffers are recreated too.

### Math library

The math library is based on gl-matrix used in Goodluck. The vector and matrix data types are typedef'ed arrays. I might try structs at some point in the future. No effort to use SIMD has been made.

### Single-threaded

The code is currently written with a single thread of execution in mind.  Specifically, I used a few static variables in some systems to store data between frames. In the future, I'd like to consider introducing storage for system-wide data.

### Code style

I've used `clang-format` to help maintain the consistency in the code base. I've tried something new, too: there's no limit on line width. I'm starting to think that deciding where to put line breaks is an integral part of the process of writing code, and that it shouldn't be automated. It's a hypothesis which I'm currently testing, and I might change my opinion on it in the future.  
