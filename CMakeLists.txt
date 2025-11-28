cmake_minimum_required(VERSION 3.16)
project(CppLearning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 各学習ステップのサブディレクトリを追加
add_subdirectory(00_setup)
add_subdirectory(01_basics)
add_subdirectory(02_oop)
add_subdirectory(03_memory)
add_subdirectory(04_templates)
add_subdirectory(05_stl)
# 06_app はまだ空なのでコメントアウトしておきます
# add_subdirectory(06_app)
