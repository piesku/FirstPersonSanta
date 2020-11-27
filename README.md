# FirstPerson

An FPS playground for creating game prototypes in C using ECS. The ECS architecture is based on [Goodluck](https://gdlck.com). Prior attempt: [breakoutc](https://github.com/stasm/breakoutc), [OpenGLESApp1](https://github.com/stasm/OpenGLESApp1).


## Building

_FirstPerson_ uses [vcpkg](https://github.com/microsoft/vcpkg) to manage dependencies. When you first clone it, you'll need to run the bootstrap script once. It's called `bootstrap-vcpkg.bat` on Windows and `bootstrap-vcpkg.sh` on macOS and Linux.

### Windows

1. (If you haven't already) Install `vcpkg` anywhere on your disk and `cd` into it.

    1. Run `.\vcpkg.exe integrate install` to inform Visual Studio of the location of `vcpkg`.

2. Install the dependencies:

        $ .\vcpkg.exe install glew:x64-windows sdl2:x64-windows sdl2-image:x64-windows

3. Open the repo in Visual Studio 2019 using the _Open a local folder_ option.
4. Build `FirstPerson.exe`.
5. Run `out\Windows\x64-Debug\FirstPerson.exe` or `out\Windows\x64-Release\FirstPerson.exe`.

### macOS & Linux

1. (If you haven't already) Install `vcpkg` in `/opt/vcpkg` and `cd` into it.

    1. If you choose a different location, pass `-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake` to the `cmake ..` command below.

2. Install the dependencies:

        $ ./vcpkg install sdl2 sdl2-image          # For macOS
        $ ./vcpkg install sdl2 sdl2-image glew     # For Linux

3. `cd` into the repo and run `cmake` as usual:

    $ mkdir build
    $ cd build
    $ cmake .. -DCMAKE_BUILD_TYPE=Debug            # Or: Release, MinSizeRel, RelWithDebInfo
    $ make

4. Run it!

    $ ./build/FirstPerson


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
