cmake_minimum_required(VERSION 3.10)

project(SocketExample)

set(CMAKE_CXX_STANDARD 11)
# set(CURL_LIBRARY "D:\\Code\\Socket\\Test-socket\\vcpkg\\packages\\curl_x64-windows\\lib")
# set(CURL_INCLUDE_DIR "D:\\Code\\Socket\\Test-socket\\vcpkg\\packages\\curl_x64-windows\\include")
# set(JSONCPP_LIBRARY "D:\\Code\\Socket\\Test-socket\\vcpkg\\packages\\jsoncpp_x64-windows\\lib")
# set(JSONCPP_INCLUDE_DIR "D:\\Code\\Socket\\Test-socket\\vcpkg\\packages\\jsoncpp_x64-windows\\include")
# set(JSONCPP_DIR "D:\\Code\\Socket\\Test-socket\\vcpkg\\packages\\jsoncpp_x64-windows\\share\\jsoncpp")

# Add the server executable
add_executable(server server.cpp)

# Add the client executable
add_executable(client client.cpp)

# Link Winsock library on Windows
if (WIN32)
    target_link_libraries(server ws2_32)
    target_link_libraries(client ws2_32)
endif()

# Find and link libcurl
# find_package(CURL REQUIRED)
# target_link_libraries(server CURL::libcurl)
# target_link_libraries(client CURL::libcurl)

# Set jsoncpp_DIR to the directory containing jsoncppConfig.cmake
# set(jsoncpp_DIR "D:\\Code\\Socket\\Test-socket\\vcpkg\\packages\\jsoncpp_x64-windows\\share\\jsoncpp")

# Find and link jsoncpp
# find_package(jsoncpp 1.9.6 CONFIG REQUIRED)
# target_include_directories(server PRIVATE ${JSONCPP_INCLUDE_DIR})
# target_include_directories(client PRIVATE ${JSONCPP_INCLUDE_DIR})
target_link_libraries(server)
target_link_libraries(client)