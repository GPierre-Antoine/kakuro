project('kakuro')

add_custom_target(parser COMMAND make parser WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/parser)
add_custom_target(clean COMMAND make clean WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/parser)

