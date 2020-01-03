cmake_minimum_required(VERSION 3.15)
project(full_theater_backend)

set(CMAKE_CXX_STANDARD 14)

add_executable(full_theater_backend main.cpp auditorium.cpp auditorium.h baseNode.cpp baseNode.h orderData.cpp orderData.h programData.cpp programData.h theaterSeat.cpp theaterSeat.h userData.cpp userData.h)