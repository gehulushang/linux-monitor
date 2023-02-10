aux_source_directory(. DIR_SRCS)
aux_source_directory(./handlers DIRSRCS_HANDLERS)
aux_source_directory(./http DIRSRCS_HTTP)
# aux_source_directory(./manager DIRSRCS_MANAGER)
# aux_source_directory(./module DIRSRCS_MODULE)
# aux_source_directory(./component DIRSRCS_COMPONENT)
# aux_source_directory(./utils DIRSRCS_UTILS)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(httpserver ${DIR_SRCS} ${DIRSRCS_HANDLERS} ${DIRSRCS_HTTP})
target_link_libraries(httpserver ${LIBRARY_OUTPUT_PATH}/libjsoncpp.so 
                                ${LIBRARY_OUTPUT_PATH}/libmongoose.so)