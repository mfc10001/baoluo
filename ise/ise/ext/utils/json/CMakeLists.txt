
aux_source_directory(. ise_utils_json_SRCS)
add_library(ise_utils_json ${ise_utils_json_SRCS})

install(TARGETS ise_utils_json DESTINATION lib)

file(GLOB ise_utils_json_HEADERS ${ISE_ROOT_PATH}/ise/ext/utils/json/*.h)
install(FILES ${ise_utils_json_HEADERS} DESTINATION include/ise/ext/utils/json)
