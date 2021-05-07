# cmake_minimum_required(VERSION 3.0.0)
# project(smart-air-purifier VERSION 0.1.0)

# # include(CTest)
# # enable_testing()

# find_package(PkgConfig)
# pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

# add_executable(smart-air-purifier main.cpp)
# target_link_libraries(${PROJECT_NAME} PkgConfig::Pistache)


# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
cmake_minimum_required(VERSION 3.6)
project("smart-air-purifier")

set(PKG_CONFIG_EXECUTABLE "/usr/bin/pkg-config")
set(CMAKE_CXX_STANDARD 11)

#####################################
##      HEADERS SEARCH PATHS       ##
##################################### 
set(PROJECT_INCLUDE_DIR "src/include")
set(PISTACHE_INCLUDE_DIR "include")

set(HEADER_SEARCH_PATHS ${PROJECT_INCLUDE_DIR} ${PISTACHE_INCLUDE_DIR})

#####################################
##      LIBRARY SEARCH PATHS       ##
#####################################
set(PISTACHE_LIBRARY "${PROJECT_SOURCE_DIR}/libs/pistache/lib/libpistache.a")
set(EXTRA_LIBRARY "-pthread -lssl")



find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

include_directories(${HEADER_SEARCH_PATHS})
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PkgConfig::Pistache)