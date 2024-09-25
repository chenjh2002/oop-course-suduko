# oop-course-suduko

SuDuLo cpp version.

## How to build the project

in MacOS, for specific compiler & linker:
```cmake
${CMAKE} -DCMAKE_BUILD_TYPE=Debug \ 
-DCMAKE_C_COMPILER=${YOUR C COMPILER} \
-DCMAKE_CXX_COMPILER=${YOUR CPP COMPILER} \
-G "Unix Makefiles" \
-D CMAKE_OSX_SYSROOT= \
-D CMAKE_EXE_LINKER_FLAGS=-fuse-ld=lld \
-S ${FILER FOLDER}/suduko 
-B ${FILER FOLDER}/suduko/build
```

the expected output is:
```c
-- Found Python3: /usr/local/Frameworks/Python.framework/Versions/3.12/bin/python3.12 (found version "3.12.3") found components: Interpreter 
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE  
-- Version: 10.1.2
-- Build type: Debug
-- Performing Test HAS_NULLPTR_WARNING
-- Performing Test HAS_NULLPTR_WARNING - Success
-- Configuring done (8.4s)
-- Generating done (0.3s)
-- Build files have been written to: ${FILE FOLDER}/suduko/build
```

## Test result

in our test, we had tested the inference function of the suduko, the expected result is followed:
```C
====================Result====================
4 7 9 1 3 6 5 8 2 
6 5 1 9 8 2 4 3 7 
8 2 3 5 7 4 9 1 6 
7 9 6 2 1 3 8 4 5 
1 3 8 7 4 5 2 6 9 
2 4 5 6 9 8 1 7 3 
5 1 2 8 6 7 3 9 4 
3 8 7 4 2 9 6 5 1 
9 6 4 3 5 1 7 2 8 
==============================================
====================Result====================
8 6 5 7 3 4 2 9 1 
7 2 3 9 1 5 8 4 6 
4 1 9 8 2 6 7 5 3 
2 7 6 4 5 3 1 8 9 
5 9 4 1 6 8 3 7 2 
3 8 1 2 7 9 5 6 4 
9 3 8 5 4 1 6 2 7 
1 4 2 6 8 7 9 3 5 
6 5 7 3 9 2 4 1 8 
==============================================
====================Result====================
2 5 4 7 6 8 3 1 9 
3 8 9 4 5 1 7 2 6 
7 1 6 9 3 2 4 8 5 
8 2 3 5 4 6 1 9 7 
4 6 7 1 8 9 2 5 3 
1 9 5 2 7 3 8 6 4 
5 3 8 6 2 4 9 7 1 
6 4 1 8 9 7 5 3 2 
9 7 2 3 1 5 6 4 8 
==============================================
====================Result====================
5 2 1 6 8 4 3 7 9 
9 4 3 1 7 5 6 8 2 
8 7 6 9 3 2 5 1 4 
4 6 8 2 9 7 1 5 3 
2 1 9 3 5 8 4 6 7 
7 3 5 4 6 1 9 2 8 
1 8 7 5 4 3 2 9 6 
6 5 4 7 2 9 8 3 1 
3 9 2 8 1 6 7 4 5 
==============================================
```