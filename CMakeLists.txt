cmake_minimum_required(VERSION 3.12)
project(ServersProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ServersProject main.cpp Server.h ClientHandler.h Solver.h CacheManager.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h FileCacheManager.cpp FileCacheManager.h StringReverser.cpp StringReverser.h Searcher.h Searchable.h BestFirstSearch.cpp BestFirstSearch.h State.cpp State.h SolverSearcher.h Point.cpp Point.h MyClientHandler.cpp MyClientHandler.h Matrix.cpp Matrix.h BFS.cpp BFS.h DFS.cpp DFS.h)