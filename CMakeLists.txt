CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

project(ral LANGUAGES CXX)

# please keep this layout for version setting, used by the automatic tagging script
set(PACKAGE_VERSION_MAJOR 0)
set(PACKAGE_VERSION_MINOR 0)
set(PACKAGE_VERSION_PATCH 1)

set(PACKAGE_VERSION "${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}.${PACKAGE_VERSION_PATCH}")

#--- enable unit testing capabilities -----------------------------------------
include(CTest)

#--- Set a better default for installation directory---------------------------
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/install" CACHE PATH "default install path" FORCE)
endif()

# Use GNU-style hierarchy for installing build products
include(GNUInstallDirs)

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")

# Set up C++ Standard
# ``-DCMAKE_CXX_STANDARD=<standard>`` when invoking CMake
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

if(NOT CMAKE_CXX_STANDARD MATCHES "14|17|20")
  message(FATAL_ERROR "Unsupported C++ standard: ${CMAKE_CXX_STANDARD}")
endif()

# dependencies are declared like this
find_package(ROOT COMPONENTS ROOTVecOps ROOTDataFrame REQUIRED)
find_package(EDM4HEP REQUIRED)
find_package(podio)


# Defining the target
file(GLOB sources src/*.cc)
file(GLOB headers RELATIVE ${CMAKE_CURRENT_LIST_DIR} "include/${PROJECT_NAME}/*.h")

add_library("${PROJECT_NAME}" SHARED  ${sources} ${headers} )
target_include_directories("${PROJECT_NAME}" PUBLIC
                           "${CMAKE_CURRENT_BINARY_DIR}"
                           "${CMAKE_CURRENT_SOURCE_DIR}/include"
                           )

target_link_libraries("${PROJECT_NAME}" PUBLIC
                      ROOT::Physics
                      ROOT::MathCore
                      ROOT::ROOTVecOps
                      ROOT::ROOTDataFrame
                      EDM4HEP::edm4hep
                      EDM4HEP::edm4hepDict
                      podio::podio
                      )

set_target_properties("${PROJECT_NAME}" PROPERTIES
  PUBLIC_HEADER "${headers}")

#Installation policies

ROOT_GENERATE_DICTIONARY("G__${PROJECT_NAME}"
                         ${headers}
                         MODULE "${PROJECT_NAME}"
                         LINKDEF "include/${PROJECT_NAME}/LinkDef.h"
                         )

install(TARGETS "${PROJECT_NAME}"
    EXPORT "${PROJECT_NAME}Targets"
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${PROJECT_NAME}" COMPONENT dev
    )

install(FILES "${PROJECT_BINARY_DIR}/lib${PROJECT_NAME}.rootmap"
    DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)

if (${ROOT_VERSION} GREATER 6)
    install(FILES "${PROJECT_BINARY_DIR}/lib${PROJECT_NAME}.pcm"
            DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)
    endif()

