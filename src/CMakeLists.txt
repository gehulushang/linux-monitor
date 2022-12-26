aux_source_directory(. DIR_SRCS)
aux_source_directory(./common DIRSRCS_COMMON)
aux_source_directory(./model DIRSRCS_MODEL)
aux_source_directory(./manager DIRSRCS_MANAGER)
aux_source_directory(./module DIRSRCS_MODULE)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_library(linux_monitor SHARED  ${DIR_SRCS} ${DIRSRCS_COMMON}
${DIRSRCS_MODEL} ${DIRSRCS_MANAGER} ${DIRSRCS_MODULE})
add_library(linux_monitor_static STATIC  ${DIR_SRCS} ${DIRSRCS_COMMON}
${DIRSRCS_MODEL} ${DIRSRCS_MANAGER} ${DIRSRCS_MODULE})

add_executable(linux-monitor ${DIR_SRCS} ${DIRSRCS_COMMON}
    ${DIRSRCS_MODEL} ${DIRSRCS_MANAGER} ${DIRSRCS_MODULE})
# target_link_libraries(monitor)
