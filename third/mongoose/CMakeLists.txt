aux_source_directory(./mongoose DIR_MONGOOSE)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(mongoose SHARED  ${DIR_MONGOOSE})