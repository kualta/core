# <center> Core Engine </center>

Engine built on top of [SDL](https://github.com/libsdl-org/SDL) and [bgfx](https://github.com/bkaradzic/bgfx). An attempt to bring ease and flexibility to С++ game development.  
Inspired by MonoGame, raylib and OGRE.  
<br>
**Early stages of development**

## Usage
To init the engine create `core::CoreConfig` object and declare dependencies with `CoreConfig::Add()` 
and then call `CoreConfig::Build()` to build your `Core` object, like this:


```c++
CoreConfig cfg;
cfg.Add(NewModuleFactory<WindowModule>);

Core core = cfg.Build();
```
For more information, check engine wiki page 

## Contributing 
Check naming convensions and contributing guidelines [here](https://github.com/lectroMathew/Core/blob/master/CONTRIBUTING.md)

<br>
<br>
  
> not to be confused with [core game platform](https://en.wikipedia.org/wiki/Core_\(video_game_platform\))
