set(BINARY ${CMAKE_PROJECT_NAME})

# get all .cpp .hpp and .h files
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.h *.cpp)

# otherwise we can specify just what we need ex:
# set(SOURCES
#     main.cpp
# )

add_executable(${BINARY} ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})
