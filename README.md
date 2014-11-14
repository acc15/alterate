
![alterate](https://raw.githubusercontent.com/acc15/alterate/master/images/logo.png)

### Install instructions

#### Ubuntu

##### Required libraries
1. sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev



Pure C++ OpenGL game engine

### What to use
#### Silence unused variable/parameter warning:

Just wrap unused parameter in comment. Example: 
```cpp
void foo(int bar, int /*unused*/) {}
```

#### For platform-dependent parts:
```cpp
#include <boost/predef.h>
```
http://www.boost.org/doc/libs/release/libs/predef/doc/html/predef/reference/boost_os_operating_system_macros.html

Macro `BOOST_OS_{XXX}`

#### For compiler-dependent parts:
```cpp
#include <boost/predef.h>
```
http://www.boost.org/doc/libs/release/libs/predef/doc/html/predef/reference/boost_comp_compiler_macros.html

Macro `BOOST_COMP_{XXX}`

#### For assertions:
```cpp
#include <boost/assert.hpp> 
```
http://www.boost.org/doc/libs/release/libs/assert/assert.html

Macro `BOOST_ASSERT` or `BOOST_ASSERT_MSG`

#### For logging:
Boost Log [http://www.boost.org/doc/libs/master/libs/log/doc/html/index.html]
