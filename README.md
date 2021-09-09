<img alt="Core Engine" height=120 align="right" valign="middle" src="CoreLogo.png">

## Game Engine focused on performance and flexibility

[![MIT License](https://img.shields.io/badge/license-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/358e19c958144c918940a8f1a1ad7f6f)](https://www.codacy.com/gh/lectroMathew/Core/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=lectroMathew/Core&amp;utm_campaign=Badge_Grade)

## Usage

### Building 
_For full guide, read **[Building](https://github.com/lectroMathew/Core/wiki/Building-Core-Engine)** the engine_
1. Clone the main repository:
```
git clone --recursive https://github.com/lectroMathew/Core.git
```
1.1 On **Unix*** systems, make sure you have **sdl2** library installed:
```
sudo pacman -S sdl2             # on ArchLinux
sudo apt install libsdl2-dev    # on Ubuntu / Debian
brew install sdl2               # on macOS (via Homebrew)
```
2. Add **Core Engine** to your `CMakeLists.txt` as subdirectory and link against `core` target:
```cmake
add_subdirectory(Core)
target_link_libraries(MyApplication PUBLIC core)
```
3. Build your application
```
cmake --build . --target MyApplication
```
> Note: on Unix* systems use **gcc** or **g++** to compile, on Windows **MinGW** is recommended, 
> **MSVC** compilation is somtimes possible, but not guaranteed


### Using the engine
_For full guide, read **[Quick Start](https://github.com/lectroMathew/Core/wiki/Quick-Start-guide)** guide for newcomers_
1. In your application, `#include` all module files you wish to use, together with `CoreConfig.h` header:
````c++
#include <core/Modules/ApplicationModule.h>
#include <core/Modules/EngineModule.h>
#include <core/Modules/SceneModule.h>
#include <core/CoreConfig.h>
````
2. Use `CoreConfig` to configure your `Core` and then build it:
```c++
using namespace core;
int main() {
    
CoreConfig config;

config
    .Add(NewModule<InputModule>)
    .Add(NewModule<EngineModule, InputModule>)
    .Add(NewModule<SceneModule>)
    .Add(NewModule<ApplicationModule>);
CoreContainer coreContainer = config.Build();
```
3. Create a window and enter the main engine loop like so:
```c++
                                                     // window title     x, y, w,    h
Core::GetModule<ApplicationModule>()->CreateApplication("Core Engine", { 0, 0, 1280, 720 });

Core::GetModule<EngineModule>()->Main(); // Enter engine main loop

return 0;
}
```
4. You're amazing!   

Congratulations, you've successfully built your `Core` and put it to work!   
Find out how to make more exciting stuff with **Core Engine** by reading architecture guides on our wiki:

### **[Engine Architecture](https://github.com/lectroMathew/Core/wiki/Architecture)** introduction

Check out **Core Engine [Wiki](https://github.com/lectroMathew/Core/wiki)** for more information and guides

## Contributing
Get involved into **Core Engine** development, read **[Contributing](https://github.com/lectroMathew/Core/wiki/Contributing)** guidelines

### License
**Core Engine** is destributed under **MIT License**, check [LICENSE](LICENSE) for details

<br>
<br>