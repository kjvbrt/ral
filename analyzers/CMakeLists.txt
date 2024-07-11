# workaround for ROOT not properly exporting the VDT includes
find_package(Vdt)

message(STATUS "includes-------------------------- dataframe edm4hep: ${EDM4HEP_INCLUDE_DIRS}")
message(STATUS "includes-------------------------- dataframe podio  : ${podio_INCLUDE_DIR}")
message(STATUS "includes-------------------------- dataframe delphes: ${DELPHES_INCLUDE_DIR}")
message(STATUS "includes-------------------------- dataframe delphes EXt TrkCov: ${DELPHES_EXTERNALS_TKCOV_INCLUDE_DIR}")
message(STATUS "includes-------------------------- dataframe delphes EXt: ${DELPHES_EXTERNALS_INCLUDE_DIR}")

include_directories(${DELPHES_INCLUDE_DIR}
                    ${DELPHES_EXTERNALS_INCLUDE_DIR}
                    ${DELPHES_EXTERNALS_TKCOV_INCLUDE_DIR}
                    )

file(GLOB sources src/*.cc)
file(GLOB headers RELATIVE ${CMAKE_CURRENT_LIST_DIR} RAL/*.h)

message(STATUS "includes headers ${headers}")
message(STATUS "includes sources ${sources}")

message(STATUS "CMAKE_CURRENT_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR  ${CMAKE_INSTALL_INCLUDEDIR}")

add_library(RAL SHARED  ${sources} ${headers} )
target_include_directories(RAL  PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:include>
                           ${VDT_INCLUDE_DIR}
                           ${DELPHES_INCLUDE_DIR}
                           ${DELPHES_EXTERNALS_INCLUDE_DIR}
                           ${DELPHES_EXTERNALS_TKCOV_INCLUDE_DIR}
                           )

message(STATUS " ====== DELPHES LIBRARY = " ${DELPHES_LIBRARY} )
message(STATUS " ====== DELPHES_EXTERNALS_TKCOV_INCLUDE_DIR = " ${DELPHES_EXTERNALS_TKCOV_INCLUDE_DIR} )


target_link_libraries(RAL PUBLIC
                      ROOT::Physics
                      ROOT::MathCore
                      ROOT::ROOTVecOps
                      ROOT::ROOTDataFrame
                      EDM4HEP::edm4hep
                      EDM4HEP::edm4hepDict
                      podio::podio
                      ${DELPHES_LIBRARY}
                      ${ADDONS_LIBRARIES}
                      )

if(WITH_DD4HEP)
  target_link_libraries(RAL PUBLIC DD4hep::DDCore)
endif()

if(WITH_ACTS)
  target_link_libraries(RAL PUBLIC ActsCore)
  target_compile_definitions(RAL PRIVATE "ACTS_VERSION_MAJOR=${Acts_VERSION_MAJOR}")
endif()

set_target_properties(RAL PROPERTIES
  PUBLIC_HEADER "${headers}")

install(TARGETS RAL
    EXPORT RALTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/RAL"
    COMPONENT dev
    )

install(FILES
  "${PROJECT_BINARY_DIR}/analyzers/libRAL.rootmap"
    DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)

if (${ROOT_VERSION} GREATER 6)
    install(FILES
          "${PROJECT_BINARY_DIR}/analyzers/libRAL.pcm"
                DESTINATION "${INSTALL_LIB_DIR}" COMPONENT dev)
    endif()
