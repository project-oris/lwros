
# modified zenoh-pico for light weighting

#set (lib_target_name lwzenohpico)

#add_library(${lib_target_name} "")

if (OS_LINUX)
add_definition(ZENOH_LINUX)
file (GLOB_RECURSE system_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/system/unix/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/system/unix/*.c)
list (APPEND system_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/system/platform_common.c)
endif()

# System definition
if(CMAKE_SYSTEM_NAME MATCHES "Linux")  
  target_compile_definitions(${lib_target_name} PRIVATE ZENOH_LINUX)  
elseif(POSIX_COMPATIBLE)
  target_compile_definitions(${lib_target_name} PRIVATE ZENOH_LINUX)  
  set(CHECK_THREADS "OFF")
elseif(CMAKE_SYSTEM_NAME MATCHES "BSD")  
  target_compile_definitions(${lib_target_name} PRIVATE ZENOH_BSD)  
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")  
  target_compile_definitions(${lib_target_name} PRIVATE ZENOH_MACOS)  
  set(MACOSX_RPATH "ON")
elseif(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
  target_compile_definitions(${lib_target_name} PRIVATE ZENOH_EMSCRIPTEN)    
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
  target_compile_definitions(${lib_target_name} PRIVATE ZENOH_WINDOWS)  
  target_compile_definitions(${lib_target_name} PRIVATE _CRT_SECURE_NO_WARNINGS)    
elseif(CMAKE_SYSTEM_NAME MATCHES "Generic")
  if(WITH_ZEPHYR)
    target_compile_definitions(${lib_target_name} PRIVATE ZENOH_ZEPHYR)          
  elseif(WITH_FREERTOS_PLUS_TCP)
    target_compile_definitions(${lib_target_name} PRIVATE ZENOH_FREERTOS_PLUS_TCP)
  endif()
else()
  message(FATAL_ERROR "zenoh-pico is not yet available on ${CMAKE_SYSTEM_NAME} platform")
  return()
endif()


# Compiler definition
message("Compilers in use: ${CMAKE_C_COMPILER_ID}, ${CMAKE_CXX_COMPILER_ID}")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_definitions(${lib_target_name} PRIVATE ZENOH_COMPILER_CLANG)    
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_definitions(${lib_target_name} PRIVATE ZENOH_COMPILER_GCC)  
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel" OR CMAKE_C_COMPILER_ID STREQUAL "Intel")
    target_compile_definitions(${lib_target_name} PRIVATE ZENOH_COMPILER_INTEL)    
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" OR CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(${lib_target_name} PRIVATE ZENOH_COMPILER_MSVC)    
else()
    target_compile_definitions(${lib_target_name} PRIVATE ZENOH_COMPILER_OTHER)    
endif()

file (GLOB_RECURSE collections_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/collections/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/collections/*.c)
file (GLOB_RECURSE utils_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.c)
file (GLOB_RECURSE link_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/link/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/link/*.c)
#file (GLOB_RECURSE transport_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/transport/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/transport/*.c)
file (GLOB_RECURSE protocol_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/protocol/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/protocol/*.c)
file (GLOB_RECURSE net_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/net/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/net/*.c)

target_sources(${lib_target_name} 
    PRIVATE
        ${system_srcs}
        ${collections_srcs}
        ${protocol_srcs}
        ${utils_srcs}
        ${link_srcs}
        ${net_srcs}
)

target_include_directories(${lib_target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)