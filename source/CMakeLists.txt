cmake_minimum_required(VERSION 3.10)
project(tarea_1 VERSION 0.1.0)


set(src_include

)



set(src
    ${src_include}
)

add_executable(source ${src} src/source.c)
target_include_directories(source PRIVATE include)


