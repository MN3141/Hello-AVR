set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.13)
project(memories)

include(cmake/AvrToolChain.cmake)

file(GLOB SOURCES "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
)
target_include_directories(${PROJECT_NAME} PRIVATE inc/)
target_include_directories(${PROJECT_NAME} PRIVATE /usr/lib/avr/include/) # or the path to your library

function(GEN_HEX_FILE)
  add_custom_target(hex_target ALL DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
  add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_NAME}
    COMMAND ${AVROBJ} ${AVROBJ_FLAGS} ${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}.elf ${PROJECT_BINARY_DIR}/bin/${PROJECT_NAME}.hex
  )
endfunction()


function(GET_PREPROCESSED_FILES)
  foreach(SOURCE ${SOURCES})
    file(RELATIVE_PATH RELATIVE_SOURCE ${CMAKE_SOURCE_DIR}/src ${SOURCE})
    file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/src)
    add_custom_target(
      ${RELATIVE_SOURCE}.i ALL
      DEPENDS ${SOURCE}
      COMMAND ${CMAKE_C_COMPILER} -o ${PROJECT_BINARY_DIR}/src/${RELATIVE_SOURCE}.i -E ${SOURCE}
    )
  endforeach()
endfunction()

function(GET_DISASSEMBLED_FILES)
  foreach(SOURCE ${SOURCES})
    file(RELATIVE_PATH RELATIVE_SOURCE ${CMAKE_SOURCE_DIR}/src ${SOURCE})
    file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/src)
    add_custom_target(
      ${RELATIVE_SOURCE}.s ALL
      DEPENDS ${SOURCE}
      COMMAND ${CMAKE_C_COMPILER} -o ${PROJECT_BINARY_DIR}/src/${RELATIVE_SOURCE}.s -S ${SOURCE}
    )
  endforeach()
endfunction()

add_custom_target(
  flash
  DEPENDS hex_target
  COMMAND ${AVR_DUDE} ${AVR_DUDE_FLAGS} flash:w:${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex:i
)
################################### MAIN ##########################################

GEN_HEX_FILE()
GET_DISASSEMBLED_FILES()
GET_PREPROCESSED_FILES()
