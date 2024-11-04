
set (exe_target_pub comm_pubhello)
set (exe_target_sub comm_subhello)

set (exe_target_zpub z_test_pub)
set (exe_target_zsub z_test_sub)

#file (GLOB SRCS src/*.cpp src/*.c)

add_executable(${exe_target_pub} src/comm_pubhello.c)
add_executable(${exe_target_sub} src/comm_subhello.c)
add_executable(${exe_target_zpub} src/z_test_pub.c)
add_executable(${exe_target_zsub} src/z_test_sub.c)

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

target_include_directories(${exe_target_zpub}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(${exe_target_zpub} lwros pthread)

target_include_directories(${exe_target_zsub}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(${exe_target_zsub} lwros pthread)