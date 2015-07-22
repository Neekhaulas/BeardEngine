cmake_minimum_required(VERSION 2.6)
project(BeardEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BeardEngine_SOURCE_DIR}/cmake")
set(BIN_DIR ${BeardEngine_SOURCE_DIR}/bin)

file(
  GLOB_RECURSE
  source_files
  src/*
)

add_executable(
  BeardEngine
  ${source_files}
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIRS})
set(LIBRARIES ${SDL2_LIBRARY} )

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

install(TARGETS BeardEngine RUNTIME DESTINATION ${BIN_DIR})
