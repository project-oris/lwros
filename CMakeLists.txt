cmake_minimum_required(VERSION 3.2)

set(CMAKE_BUILD_TYPE Release)

project(lwros)

set (lib_target_name ${PROJECT_NAME})

add_library(${lib_target_name} "")

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

function(add_definition value)
  add_definitions(-D${value})
  # target_compile_definitions(${Libname} PUBLIC ${value})
endfunction()

#add_definitions (-Os)
#add_definitions (-Ofast)

# System definition
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  add_definition(OS_LINUX)  
  set(OS_LINUX true)
elseif(POSIX_COMPATIBLE)
  add_definition(OS_LINUX)
  set(OS_LINUX true)
  set(CHECK_THREADS "OFF")
elseif(CMAKE_SYSTEM_NAME MATCHES "BSD")
  add_definition(OS_BSD)
  set(OS_BSD true)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  add_definition(OS_MACOS)
  set(MACOSX_RPATH "ON")
  set(OS_MACOS true)
elseif(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
  add_definition(OS_EMSCRIPTEN)
  set(OS_EMSCRIPTEN true)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
  add_definition(OS_WINDOWS)
  add_definition(_CRT_SECURE_NO_WARNINGS)
  set(OS_WINDOWS true)
elseif(CMAKE_SYSTEM_NAME MATCHES "Generic")
  if(WITH_ZEPHYR)
    add_definition(OS_ZEPHYR)
    set(OS_ZEPHYR true)
  elseif(WITH_FREERTOS_PLUS_TCP)
    add_definition(OS_FREERTOS_PLUS_TCP)
    set(OS_FREERTOS_PLUS_TCP true)
  endif()
else()
  message(FATAL_ERROR "ORIS is not yet available on ${CMAKE_SYSTEM_NAME} platform")
  return()
endif()



add_subdirectory(3rd_party/zenoh-pico)
add_subdirectory(3rd_party/micro-cdr)
add_subdirectory(modules)
add_subdirectory(devtests)



#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMADN ${CMAKE_AR} cr $<TARGET_FILE:lwros> $<TARGET_FILE:lwcomm> $<TARGET_FILE:lwrosapi> $<TARGET_FILE:lwzenohpico>
#    COMMAND ${CMAKE_RANLIB} $<TARGET_FILE:lwros>
#)