# CMake file for P4RuntimeSmith.
project(rtsmith)

# Add cmake directory to our module path. Also add cmake directory from P4C
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


# Declare common P4RuntimeSmith variables.
set(RTSMITH_DIR ${P4C_BINARY_DIR}/rtsmith)
set(RTSMITH_DRIVER "${CMAKE_CURRENT_BINARY_DIR}/p4rtsmith")


# Source files for rtsmith.
set(RTSMITH_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/options.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rtsmith.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/program_info.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/core/target.cpp
)

# RTSmith libraries.
set(RTSMITH_LIBS p4tools-common)

file(GLOB rtsmith_targets RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/targets
     ${CMAKE_CURRENT_SOURCE_DIR}/targets/*
)
foreach(ext ${rtsmith_targets})
  set(rtsmith_targets_dir ${CMAKE_CURRENT_SOURCE_DIR}/targets/${ext}/)
  if(EXISTS ${rtsmith_targets_dir}/CMakeLists.txt AND IS_DIRECTORY ${rtsmith_targets_dir})
    # Generate an option that makes it possible to disable this extension.
    string(MAKE_C_IDENTIFIER ${ext} EXT_AS_IDENTIFIER)
    string(TOUPPER ${EXT_AS_IDENTIFIER} EXT_AS_OPTION_NAME)
    string(CONCAT ENABLE_EXT_OPTION "ENABLE_TOOLS_TARGET_" ${EXT_AS_OPTION_NAME})
    string(CONCAT EXT_HELP_TEXT "Build the " ${ext} " target")
    option(${ENABLE_EXT_OPTION} ${EXT_HELP_TEXT} ON)
    if(${ENABLE_EXT_OPTION})
      message("-- Enabling target ${ext}")
      add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/targets/${ext})
      set(include_statements_var
          "${include_statements_var}#include \"backends/p4tools/modules/p4rtsmith/targets/${ext}/register.h\"\n"
      )
      set(compiler_targets_var "${compiler_targets_var}    ${ext}_registerCompilerTarget();\n")
      set(rtsmith_targets_var "${rtsmith_targets_var}    ${ext}_registerRtSmithTarget();\n")
    endif()
  endif()
endforeach(ext)

# Convert the list of files into #includes
foreach(include_file ${include_files})

endforeach()

# Fill the template
configure_file(register.h.in register.h)

add_p4tools_library(librtsmith ${RTSMITH_SOURCES})
add_dependencies(librtsmith p4tools-common controlplane)
target_include_directories(librtsmith SYSTEM BEFORE PUBLIC ${Protobuf_INCLUDE_DIR})

add_p4tools_executable(p4rtsmith main.cpp)

target_link_libraries(p4rtsmith librtsmith ${RTSMITH_LIBS})

# Add some convenience links for invoking p4rtsmith.
add_custom_target(
  linkrtsmith
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_BINARY_DIR}/p4rtsmith
          ${P4C_BINARY_DIR}/p4rtsmith
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${P4C_BINARY_DIR}/p4include
          ${CMAKE_CURRENT_BINARY_DIR}/p4include
  DEPENDS update_includes
)

add_dependencies(p4rtsmith linkrtsmith)
