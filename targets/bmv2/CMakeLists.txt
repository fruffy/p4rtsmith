if(ENABLE_TESTING)
  # Include the test subdirectory.
  message("-- Adding RTSmith v1model test suite.")
  include(test/P4Tests.cmake)
endif()

# Source files for the main P4RtSmith.
set(RTSMITH_SOURCES
    ${RTSMITH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/constants.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fuzzer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/program_info.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/target.cpp
    PARENT_SCOPE
)

set(RTSMITH_LIBS ${RTSMITH_LIBS} ${P4C_LIBRARIES} ${P4C_LIB_DEPS} ${CMAKE_THREAD_LIBS_INIT} PARENT_SCOPE)

