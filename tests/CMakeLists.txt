# Make sure it finds the headers
#include_directories (../include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include ${GNULIBS_INCLUDE_DIR})
LINK_LIBRARIES(${PROJECT_NAME}  ${REQUIRED_LIBRARIES} )

ADD_EXECUTABLE(testcollection testcollection.cpp)
INSTALL(TARGETS testcollection RUNTIME DESTINATION bin)

ADD_EXECUTABLE(traincollection traincollection.cpp)
INSTALL(TARGETS traincollection RUNTIME DESTINATION bin)



