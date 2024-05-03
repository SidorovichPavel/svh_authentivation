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
        GIT_TAG "d4a2ddfc5df87883ee9dc6e72df6e13485e79836"
)
FetchContent_MakeAvailable(uopenapi)

find_package(jwt-cpp CONFIG REQUIRED)

CreateTrivialPart(
        name "src"
        path "/src"
        )

target_link_libraries(${src_module} PUBLIC openapi-extension-userver_library)

add_executable(service service/main.cpp)

target_link_libraries(service PUBLIC ${src_module})

target_link_libraries(service PUBLIC PRIVATE jwt-cpp::jwt-cpp)

SET(USERVER_PYTHON "python3")
userver_testsuite_add_simple()
