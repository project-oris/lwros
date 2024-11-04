
# modified zenoh-pico for light weighting

#set (lib_target_name lwzenohpico)

#add_library(${lib_target_name} "")

file (GLOB_RECURSE srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

target_sources(${lib_target_name} 
    PRIVATE
        ${srcs}        
)

target_include_directories(${lib_target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)