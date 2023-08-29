cmake_minimum_required(VERSION 3.22)

project(ScreenSaver)

include_directories(src)


target_link_libraries(${PROJECT_NAME}
  SDL2main
  SDL2
  GL
)