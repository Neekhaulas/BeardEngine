cmake_minimum_required(VERSION 2.6)
project(client)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BeardEngine_SOURCE_DIR}/cmake")
set(BIN_DIR ${BeardEngine_SOURCE_DIR}/bin)

set(FILES
    ../src/client.cpp
    ../src/command.cpp
    ../src/entity.cpp
    ../src/file.cpp
    ../src/input.cpp
    ../src/keys.cpp
    ../src/server.cpp
    ../src/collision.cpp
    ../src/common.cpp
    ../src/cvar.cpp
    ../src/event.cpp
    ../src/game.cpp
    ../src/key_event.cpp
    ../src/main.cpp
    ../src/render.cpp
    ../src/texture.cpp
)

add_executable(
  client
  ${FILES}
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ENet REQUIRED)
find_package(PhysFS REQUIRED)
find_package(GLEW)
include_directories(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${ENet_INCLUDE_DIRS} ${PHYSFS_INCLUDE_DIR})
set(LIBRARIES ${SDL2_LIBRARY} ${SDL2IMAGE_LIBRARY} ${OPENGL_LIBRARY} ${ENet_LIBRARY} ${PHYSFS_LIBRARY} ${GLEW_LIBRARY})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

install(TARGETS client RUNTIME DESTINATION ${BIN_DIR})
