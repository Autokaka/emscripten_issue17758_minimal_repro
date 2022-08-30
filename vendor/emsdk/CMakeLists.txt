project(emsdk)

set(EMSDK_LINK_OPTIONS 
  -lembind
  -pthread 
  -sPROXY_TO_PTHREAD 
  -sALLOW_MEMORY_GROWTH=1 
  -sUSE_ZLIB=1 
  -sFULL_ES3 
  -sOFFSCREEN_FRAMEBUFFER 
  -sLLD_REPORT_UNDEFINED
  -sWASM_BIGINT
  -sENVIRONMENT=webview,web,worker
  -sMODULARIZE
  -sEXPORT_NAME=loadChronosModule
)

# Let emcc prebuild before generating cmake project.
execute_process(COMMAND emcc ${PROJECT_SOURCE_DIR}/emsdk.cc
  --no-entry
  -o ${PROJECT_BINARY_DIR}/emsdk.js 
  ${EMSDK_LINK_OPTIONS}
)

add_library(emsdk INTERFACE)

target_compile_options(emsdk INTERFACE -pthread)
target_link_options(emsdk INTERFACE ${EMSDK_LINK_OPTIONS})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(ENV{EMCC_DEBUG} 2)
  target_compile_options(emsdk INTERFACE -g -fdebug-compilation-dir='${CMAKE_SOURCE_DIR}')
  target_link_options(emsdk INTERFACE 
    -sSAFE_HEAP=1 
    -sSAFE_HEAP_LOG 
    -sDEMANGLE_SUPPORT=1
    -sASSERTIONS=2
    -sTRACE_WEBGL_CALLS
    -sGL_DEBUG
  )
endif()
