cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(AtelierProg)

add_executable(AtelierProg
               box.cpp box.h
               ball.cpp ball.h
               joint.cpp joint.h
               main.cpp
               tools.cpp tools.h
               vector.cpp vector.h
               vehicle.cpp vehicle.h
               liste_des_skins.cpp liste_des_skins.h
               skin.h skin.cpp
               weapon.cpp weapon.h
               structure.cpp structure.h
               level.cpp level.h)
ImagineUseModules(AtelierProg Images LinAlg)
