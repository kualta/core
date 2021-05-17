## Contributing
- **[Wiki](https://github.com/lectroMathew/Core/wiki)** is open for anyone to contribute to. You're welcome to add new pages to it, but please be responsible.
- _Don't_ use emoji in PRs, commits, or code comments.  


## C++ Naming Convention 

It's mostly Google's convention, with several changes.

### Naming 
| Entity Kind | Naming Convention |
| :--- | --- |
| Macro | SCREAMING_SNAKE_CASE |
| Namespace | snake_case |
| Global Function | PascalCase |
| Memeber Function | PascalCase |
| Struct name | PascalCase |
| Class name | PascalCase |
| Enumerator | camelCase |
| Struct Member Field | camelCase |
| Parameter | camelCase |
| Local Variable | camelCase |
| Global Variable | don't | 

Header Guard Style: CORE_FILENAME_H


### Tabs and Indents
Follow existing code style  
God bless tab character. __Use spaces__  
| Indent Kind | Value | 
| :--- | --- |
| Regular | 4 | 
| Continuation  | 4 |
| Label | 0 | 
| Member of class | 4 |
| Member of namespcae | 0 |
| Visibility keywords | 0 |


## Files & Structure 

- C++ source files go to `src/` folder and use `.cpp` extention
- C++ header files go to `include/core/` folder and use `.h` extention
- C++ template implementations go to same folder as `.h` file they belong to and use `.tpp` extention
- Headers and source files use `PascalCase` for names, with one exception: `core.h` and `core.cpp`
- Every source file __must__ have corresponding header file. 
- Header file might be stand-alone. In this case this has to be specified in comment before header guard.


## Code Example 
```cpp
// file: core/EngineLoop.h
#ifndef CORE_ENGINELOOP_H
#define CORE_ENGINELOOP_H

#include "Essential.h"
#include "Logger.h"

#include "Modules/InputModule.h"
#include <forward_list>

namespace core {

class EngineLoop {
public:
    explicit EngineLoop(InputModule* inputModule);

    /**
     * Function which contains main engine loop.
     */
    int32_t Enter();

    /**
     * Stops main engine loop after current frame.
     */
    void Stop();

    /**
     * Ticks every module in tickedModules list
     */
    void UpdateModules();

protected:

    bool                        isRunning { true };
    InputModule*                Input;

};

}

#endif //CORE_ENGINELOOP_H

```
