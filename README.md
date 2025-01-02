# sVector
sVector is a vector like container that stores its memory on the stack rather than the heap. Was primarily created to have an array that kept track of size.
## Install
### sVector Library
You can install just the library using:
```console
git clone https://github.com/garthable/sVector sVector
```
Once installed you can link it to your projects CMake file by adding:
```cmake
add_subdirectory(sVector)
target_link_libraries(<EXECUTABLE_TARGET> <PUBLIC/PRIVATE/INTERFACE> <OTHER_LIBRARIES> sVector)
```
I have not tested sVector with CMake's fetch so its unknown if that works.
### sVector Workspace
You can download the entire project using:
```console
git clone https://github.com/garthable/sVector
```
Inorder to compile the project use the following commands:
```console
mkdir build
cd build
cmake ..
make
```
This will produce an binary file name ```sVectorTests.exe``` or ```sVectorTests.out```. When run these binary files will run tests on the project.