cmake_minimum_required(VERSION 3.10)
project(tarea_1 VERSION 0.1.0)


set(src_include
    include/string_util.h
    include/informacion.h
    include/habitacion.h
    include/cliente.h
    include/contenedora.h
    include/utils.h
)



set(src
    ${src_include}
    src/string_util.c
    src/interfaz.c
    src/memoria.c
    src/hotel.c
    src/utils.c
)

add_executable(source ${src} src/source.c)
target_include_directories(source PRIVATE include)


