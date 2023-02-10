aux_source_directory(./json DIR_JSONCPP)
aux_source_directory(./lib DIR_JSONLIB)


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(jsoncpp SHARED  ${DIR_JSONCPP} ${DIR_JSONLIB})