cmake_minimum_required(VERSION 3.20)
project(re_file_server C)

set(CMAKE_C_STANDARD 11)

# set the include directory
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${LIBEVENT_INCLUDE_DIRS}
)

add_executable(re_file_server
        main.c
        src/constants.c
        src/http_server.c
        src/utils.c
)

# Link the library
target_link_libraries(re_file_server event)

