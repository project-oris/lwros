
# pan (all) network framework

#set (lib_target_name lwrosapi)

#add_library(${lib_target_name} "")


file (GLOB_RECURSE rosapi_srcs ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp ${CMAKE_CURRENT_LIST_DIR}/src/*.c)

target_sources(${lib_target_name} 
    PRIVATE 
        ${rosapi_srcs}
)

target_include_directories(${lib_target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_SOURCE_DIR}

)