cmake_minimum_required(VERSION 3.17)
project(TestSFML)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5.1 REQUIRED graphics window system)

set(SOURCE
        Sources/Main.cpp
        Sources/Application.cpp
        Sources/Application.hpp
        Sources/Keyboard.cpp
        Sources/Keyboard.hpp
        Sources/Apps/GenericApp.cpp
        Sources/Apps/GenericApp.hpp
        Sources/Apps/TestApp.cpp
        Sources/Apps/TestApp.hpp
        Sources/Apps/LifeGame.cpp
        Sources/Apps/LifeGame.hpp
        Sources/Apps/AStar/AStar.cpp
        Sources/Apps/AStar/AStar.hpp Sources/Apps/AStar/AStarCell.cpp Sources/Apps/AStar/AStarCell.hpp)

add_executable(TestSFML ${SOURCE})

target_link_libraries(TestSFML ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})