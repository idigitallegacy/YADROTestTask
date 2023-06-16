cmake_minimum_required(VERSION 3.0)
project(TestTask)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        TestTask main.cpp

        cfg.h

        Datatype/TableHeader/Header.cpp
        Datatype/TableHeader/ColumnHeader.cpp
        Datatype/TableHeader/RowHeader.cpp

        Datatype/Abstract/Optional.cpp

        Service/IOReader/File/FileReader.cpp
        Service/IOReader/StringArray/StringArrayReader.cpp
        Service/Table/Table.cpp
        Service/Table/TableExecutor.cpp

        Exception/FileNotPermittedException.cpp
        Exception/EmptyDataException.cpp
        Exception/InvalidDataPatternException.cpp
        Exception/UnknownException.cpp
        Exception/InvalidCellTreeException.cpp
        Exception/ZeroDivisionException.cpp
        Exception/InvalidOperatorException.cpp
        Exception/SelfReferenceException.cpp
        Exception/InvalidCellAddressException.cpp)
