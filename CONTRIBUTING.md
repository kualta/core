## Contributing
- __Don't__ use emoji in PRs, commits, or code comments.  


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
```c++
// file: include/core/MyClass.h
#ifndef CORE_MYCLASS_H
#define CORE_MYCLASS_H

#include "Essential.h"
#include "Singleton.h"

#include <string>

namespace core {

/** 
 * My shiny class
 */
class MyClass {

public:
    MyClass();
    ~Myclass();

    MyClass* *Ptr() { return this; }

private:
    void InnerFunc();
    std::string var;
    int anotherVarExample;
};

} // namespace core


#endif //CORE_MYCLASS_H
```
