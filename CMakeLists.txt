cmake_minimum_required(VERSION 3.25)
project(Checkers)

set(CMAKE_CXX_STANDARD 23)

add_executable(Checkers main.cpp Piece.h GameBoard.h GameTile.h Man.h Location.h)
