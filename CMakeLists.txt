cmake_minimum_required(VERSION 3.10)

project(icp1_s17 LANGUAGES C)

add_subdirectory(01-fork)
add_subdirectory(02-exec)
add_subdirectory(03-forkplusexec)
add_subdirectory(04-threads)
add_subdirectory(05-pthreads)
add_subdirectory(06-pthreads-mutex)
add_subdirectory(07-pthreads-condvar)
add_subdirectory(08-semaphores)
add_subdirectory(09-barriers)