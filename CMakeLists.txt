cmake_minimum_required(VERSION 3.23)
project(Advanced_databases)

set(CMAKE_CXX_STANDARD 14)

add_executable(Advanced_databases
        entities/storage.h entities/storage.cpp entities/datablock.h entities/datablock.cpp entities/BTree.cpp entities/database.h entities/database.cpp controllers/DatabaseManager.cpp test/testBlock.cpp test/testBPtree.cpp entities/BTree.h)
