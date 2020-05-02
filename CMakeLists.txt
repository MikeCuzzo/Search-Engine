cmake_minimum_required(VERSION 3.14)
project(CS2341-SearchEngine)
set (EXE_NAME SearchEngine)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "")
set (input02 "")
set (input03 "")
set (input04 "")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp AVLTree.h parser.h parser.cpp porter2_stemmer.cpp porter2_stemmer.h wordobject.h wordobject.cpp
        HashTable.h QueryEngine.cpp QueryEngine.h ui.cpp ui.h DataStructures.h)
