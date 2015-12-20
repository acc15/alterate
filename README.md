![alterate](https://raw.githubusercontent.com/acc15/alterate/master/images/logo.png)

![build](https://travis-ci.org/acc15/alterate.svg?branch=master)

### Prerequisites
#### Windows
##### Supported compilers
MSVC 2013

#### Ubuntu
##### Required libraries
1. sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxi-dev libglew-dev
1. sudo apt-get install libxinerama-dev libxcursor-dev

##### Supported compilers
GNU C++ or clang with C++11 support

### Dependencies
#### CMake
http://www.cmake.org/

#### Boost
http://www.boost.org/

Compile with:
    ./bootstrap
	./b2

#### GLFW
http://www.glfw.org/

#### GLEW
http://glew.sourceforge.net/
### Windows install
Copy headers to "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include\gl"
Copy libs to "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib"
### Ubuntu
sudo apt-get install libglew-dev


#### Google Test
https://code.google.com/p/googletest/

### Building
In top-level project directory type:

    mkdir build
    cd build

	cmake "../sources" \
		"-DCMAKE_BUILD_TYPE=Debug" \
		"-DBOOST_ROOT=</path/to/boost>" \
		"-DGLFW_ROOT=</path/to/glfw>" \
		"-DGTEST_ROOT=</path/to/gtest>"

Additionally you may need to specify path to GLEW (if cmake can't find it):
		
		"-DCMAKE_INCLUDE_PATH=$CMAKE_INCLUDE_PATH;</path/to/glew/include>" \
		"-DCMAKE_LIBRARY_PATH=$CMAKE_LIBRARY_PATH;</path/to/glew/lib/folder/with/glew32s>" 

### Programming tips
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

#### TODO

1. Matrix
1. Vertex Buffer and Vertex Buffer Object
1. Texture loading & binding

1. Frame Buffer and Frame Buffer Object