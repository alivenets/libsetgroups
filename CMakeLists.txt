cmake_minimum_required(VERSION 3.10)

add_library(setgroups SHARED libsetgroups.c)

install(TARGETS setgroups DESTINATION lib)
