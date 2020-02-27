cmake_minimum_required(VERSION 3.5)
project(electric_eye) # Project Name Here

find_package(wpilib REQUIRED)
add_executable(electric_eye Target.h Target.cpp CameraInfo.h GoalPipeline.h GoalPipeline.cpp main.cpp)  # exectuable name as first parameter
target_link_libraries(electric_eye cameraserver ntcore cscore wpiutil)
