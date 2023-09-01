cmake_minimum_required(VERSION 3.22)

project(ScreenSaver)

# Encontrar SDL2
find_package(SDL2 REQUIRED)

# Encontrar OpenMP
find_package(OpenMP REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

# Agregar todos tus archivos fuente aquí
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  OpenMP::OpenMP_CXX
  GL
)
