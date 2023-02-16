aux_source_directory(. DIR_SRCS)
aux_source_directory(./handlers DIRSRCS_HANDLERS)
aux_source_directory(./http DIRSRCS_HTTP)
aux_source_directory(./config DIRSRCS_CONFIG)
aux_source_directory(./common DIRSRCS_COMMON)
aux_source_directory(./model DIRSRCS_MODEL)
aux_source_directory(./manager DIRSRCS_MANAGER)
aux_source_directory(./module DIRSRCS_MODULE)
aux_source_directory(./component DIRSRCS_COMPONENT)
aux_source_directory(./utils DIRSRCS_UTILS)
aux_source_directory(./ipc DIRSRCS_IPC)


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(monitor-server ${DIR_SRCS} ${DIRSRCS_HANDLERS} ${DIRSRCS_HTTP} 
               ${DIRSRCS_CONFIG} ${DIRSRCS_COMMON} ${DIRSRCS_MODEL} 
               ${DIRSRCS_MANAGER} ${DIRSRCS_MODULE} 
    ${DIRSRCS_COMPONENT}  ${DIRSRCS_UTILS} ${DIRSRCS_IPC})
target_link_libraries(monitor-server ${LIBRARY_OUTPUT_PATH}/libjsoncpp.so 
                                ${LIBRARY_OUTPUT_PATH}/libmongoose.so)