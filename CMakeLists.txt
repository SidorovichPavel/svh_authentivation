cmake_minimum_required(VERSION 3.20)
project(service)
set(CMAKE_CXX_STANDARD 20)

set(openapi-extension-userver_BUILD_UNIT_TESTS false)
set(openapi-extension-userver_BUILD_TEST_SERVICES false)
set(USERVER_FEATURE_POSTGRESQL ON)

enable_testing()
include(FetchContent)
FetchContent_Declare(
        uopenapi
        GIT_REPOSITORY https://github.com/sabudilovskiy/userver-openapi-extension
        GIT_TAG "9e517b8f14b8ffd056eef82344b37729f29d0f49"
)
FetchContent_MakeAvailable(uopenapi)

CreateTrivialPart(
        name "src"
        path "/src"
)

target_link_libraries(${src_module} PUBLIC openapi-extension-userver_library)

add_executable(service service/main.cpp)

target_link_libraries(service PUBLIC ${src_module})

SET(USERVER_PYTHON "python3")
userver_testsuite_add_simple()
