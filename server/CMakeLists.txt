cmake_minimum_required(VERSION 2.6)
project(server)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BeardEngine_SOURCE_DIR}/cmake")
set(BIN_DIR ${BeardEngine_SOURCE_DIR}/bin)

set(FILES
    ../src/common.cpp
    ../src/file.cpp
    ../src/server.cpp
    ../src/game.cpp
    ../src/collision.cpp
    ../src/cvar.cpp
    ../src/command.cpp
    ../src/entity.cpp
)

add_executable(
  server
  ${FILES}
)

add_definitions(-DSERVER)

find_package(ENet REQUIRED)
find_package(PhysFS REQUIRED)
include_directories(${ENet_INCLUDE_DIRS} ${PHYSFS_INCLUDE_DIR})
set(LIBRARIES ${ENet_LIBRARY} ${PHYSFS_LIBRARY})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})

install(TARGETS server RUNTIME DESTINATION ${BIN_DIR})
