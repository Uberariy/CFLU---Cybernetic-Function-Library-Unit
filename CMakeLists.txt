cmake_minimum_required(VERSION 3.16)
project(CFLU)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Function lib/Factory.hpp lib/Function.hpp lib/Function.cpp)
# set(Operations lib/Factory.hpp lib/Function.hpp lib/Function.cpp)

add_library(CFLU ${Function})# ${Operations})

add_executable(test lib/test/Function_test.cpp lib/test/Operations_test.cpp)
target_link_libraries(test CFLU)
target_link_libraries(test gtest_main)
add_test(NAME test COMMAND test)