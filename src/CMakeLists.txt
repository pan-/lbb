# Build steps
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_library(${LIB_NAME}.static STATIC ${SOURCES})
add_library(${LIB_NAME} SHARED ${SOURCES})
include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

# Installation steps
install(TARGETS ${LIB_NAME}.static ${LIB_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  COMPONENT libraries
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/lbb
  DESTINATION include
  COMPONENT headers
)
