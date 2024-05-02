cmake_minimum_required(VERSION 3.27)
project(livros C)

set(CMAKE_C_STANDARD 11)

add_executable(livros cli.c gestao_emprestimos.c gestao_livros.c)

