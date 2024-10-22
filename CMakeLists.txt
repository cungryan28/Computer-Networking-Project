cmake_minimum_required(VERSION 3.10)

project(SocketExample)

set(CMAKE_CXX_STANDARD 11)

# Add the server executable
add_executable(server server.cpp ServerSocket.hpp ServerSocket.cpp)

# Add the client executable
add_executable(client client.cpp ClientSocket.hpp ClientSocket.cpp)

target_link_libraries(server ws2_32)
target_link_libraries(client ws2_32)