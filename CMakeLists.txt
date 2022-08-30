cmake_minimum_required(VERSION 3.8.0)
project(wasm-playground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/emsdk)

file(GLOB_RECURSE SOURCE "src/*")

add_executable(wasm-playground ${SOURCE})

target_link_libraries(wasm-playground PRIVATE emsdk)

file(GLOB EXAMPLE_RESOURCES "wasm/*")
foreach(RESOURCE ${EXAMPLE_RESOURCES})
  configure_file(${RESOURCE} ${PROJECT_BINARY_DIR} COPYONLY)
endforeach()
