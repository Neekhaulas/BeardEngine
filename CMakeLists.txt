cmake_minimum_required(VERSION 2.6)
project(BearEngine)

file(
  GLOB_RECURSE
  source_files
  src/*
)

add_executable(
  BeardEngine
  ${source_files}
)
