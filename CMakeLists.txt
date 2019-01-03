cmake_minimum_required(VERSION 3.12)
project(ServersProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(ServersProject main.cpp Server.h ClientHandler.h Solver.h CacheManager.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h FileCacheManager.cpp FileCacheManager.h)