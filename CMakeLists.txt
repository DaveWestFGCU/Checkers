cmake_minimum_required(VERSION 3.25)
project(Checkers)

set(CMAKE_CXX_STANDARD 23)

add_executable(Checkers main.cpp Piece.h GameBoard.h GameTile.h Man.h Location.h King.h Checkers.cpp Checkers.h Location.cpp GameBoard.cpp GameTile.cpp Man.cpp King.cpp Piece.cpp)
