cmake_minimum_required(VERSION 3.16)
project(test C)

set(CMAKE_C_STANDARD 99)
include_directories(/data/redis/redis-6.0.7/deps/hiredis)

link_directories(/usr/local/lib)

link_libraries(hiredis  pthread )

link_libraries(jemalloc)
#link_libraries(tcmalloc)
add_executable(test main.c socket_util.c socket_util.h redis_util.c redis_util.h mmalloc.c mmalloc.h jemalloc-tcmalloc-malloc.c jemalloc-tcmalloc-malloc.h thpool.c thpool.h)