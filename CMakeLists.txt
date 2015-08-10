CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(DynamicFusion)
SET(MY_DIR ${PROJECT_SOURCE_DIR})

####### guard against in-sourced builds #######
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	MESSAGE(FATAL_ERROR "In-source builds not allowed.")
ENDIF()

####### local cmake modules ######
SET(CMAKE_MODULE_PATH "${MY_DIR}/cmake_modules")

####### enable c++11 #######
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
IF(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSEIF(COMPILER_SUPPORTS_CXX0X)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ELSE()
		MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	ENDIF()

####### Dependencies #######
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(PCL 1.7 REQUIRED)
FIND_PACKAGE(freenect2 REQUIRED)
FIND_PACKAGE(RTABMap REQUIRED)

SET(INCLUDE_DIRS
	${OpenCV_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	${RTAB_Map_INCLUDE_DIRS}
	"${MY_DIR}/include"
)

SET(LIBRARIES
	${OpenCV_LIBRARIES}
	${PCL_LIBRARIES}
	${RTABMap_LIBRARIES}
)

SET(SOURCES
	include/dualquaternion/dual_quat_cu.hpp
	include/dualquaternion/mat3.hpp
	include/dualquaternion/point3.hpp
	include/dualquaternion/quat_cu.hpp
	include/dualquaternion/transfo.hpp
	include/dualquaternion/vec3.hpp
	src/*.cpp
)

LINK_DIRECTORIES(
	${PCL_LIBRARY_DIRS}
)

ADD_DEFINITIONS(
	${PCL_DEFINITIONS}
)

####### Make Settings #######
ADD_LIBRARY(dynamicfusion OBJECT ${SOURCES})
SET_TARGET_PROPERTIES(dynamicfusion PROPERTIES POSITION_INDEPENDENT_CODE 1)
ADD_LIBRARY(dynamicfusionshared SHARED $<TARGET_OBJECTS:dynamicfusion>)
ADD_LIBRARY(dynamicfusionstatic STATIC $<TARGET_OBJECTS:dynamicfusion>)
SET_TARGET_PROPERTIES(dynamicfusionshared PROPERTIES OUTPUT_NAME dynamicfusion)
SET_TARGET_PROPERTIES(dynamicfusionstatic PROPERTIES OUTPUT_NAME dynamicfusion)
MESSAGE("Linking with these libraries: ${LIBRARIES}")

INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(dynamicfusionshared ${LIBRARIES})
ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main dynamicfusionshared)
