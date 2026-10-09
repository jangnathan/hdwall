cmake_minimum_required(VERSION 3.15)

project(hdwallet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

add_executable(hdwallet
src/helper/base58.cpp
src/helper/hex.cpp

src/main.cpp
src/cli/cli.cpp
src/wallet/wallet.cpp)

target_include_directories(hdwallet PRIVATE
src/
deps/phc-winner-argon2/include/
)

target_compile_definitions(hdwallet PRIVATE
CLI_APP
$<$<CONFIG:Debug>:DEBUG_MODE>
)

# argon
add_library(argon2 STATIC IMPORTED)
set_target_properties(argon2 PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/deps/phc-winner-argon2/libargon2.a
)

target_link_libraries(hdwallet PRIVATE OpenSSL::SSL OpenSSL::Crypto argon2)

option(TESTING "build testing" OFF)
if (TESTING)
add_executable(test
src/helper/hex.cpp
	test/main.cpp)
endif()
