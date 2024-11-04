
set (exe_target_pub rclapi_pubhello)
set (exe_target_sub rclapi_subhello)

#file (GLOB SRCS src/*.cpp src/*.c)

add_executable(${exe_target_pub} src/lwpub.c)
add_executable(${exe_target_sub} src/lwsub.c)

#target_sources(${exe_target_name} 
#    PRIVATE 
#        ${SRCS}
#)

target_include_directories(${exe_target_pub}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(${exe_target_pub} lwros pthread)

target_include_directories(${exe_target_sub}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(${exe_target_sub} lwros pthread)