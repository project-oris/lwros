
# pan (all) network framework

#set (lib_target_name lwcomm)

#add_library(${lib_target_name} "")

file (GLOB_RECURSE comm_srcs ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp ${CMAKE_CURRENT_LIST_DIR}/src/*.c)

target_sources(${lib_target_name} 
    PRIVATE 
        ${comm_srcs}
)

target_include_directories(${lib_target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}/3rd_party/zenoh-pico/include
)