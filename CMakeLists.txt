cmake_minimum_required(VERSION 3.10)
project(przetwarzanie_)

add_executable(${PROJECT_NAME} main.c modul.c)
target_link_libraries(${PROJECT_NAME} m)
