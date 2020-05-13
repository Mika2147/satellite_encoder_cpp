cmake_minimum_required(VERSION 3.16)
project(Satellite_Encoder_CPP)

set(CMAKE_CXX_STANDARD 17)

add_executable(Satellite_Encoder_CPP main.cpp SatelliteChipCodeGenerator.cpp SatelliteChipCodeGenerator.h Constants.h)