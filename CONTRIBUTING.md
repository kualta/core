## Contributing
- __Don't__ use emoji in PRs, commits, or code comments.  


## C++ Naming Convention 

It's mostly Google's convention, with several changes.

### Naming 
| Entity Kind | Naming Convention |
| :--- | --- |
| Macro | SCREAMING_SNAKE_CASE |
| Enumerator | SCREAMING_SNAKE_CASE |
| Namespace | snake_case |
| Struct Member Field | camelCase |
| Global Function | PascalCase |
| Memeber Function | PascalCase |
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
- C++ header files go to `include/` folder and use `.h` extention
- Headers and source files use `PascalCase` for names, with one exception: `core.h` and `core.cpp`
- Every source file __must__ have corresponding header file. 
- Header file might go alone, without source file. In this case this has to be specified at the beginning of the file.


## Code Example 
```c++
// file: include/MyClass.h
#ifndef CORE_MYCLASS_H
#define CORE_MYCLASS_H

#include "core.h"
#include "Singleton.h"

#include <string>


namespace core {

/// Use triple slash for documentation comment
class MyClass {

public:
    MyClass();
    ~Myclass();

    virtual Foo *getSelf() { return Foo::getSelf(); }

private:
    void innerFunc();
    std::string var;
    int anotherVarExample;
};


}


#endif //CORE_MYCLASS_H
```