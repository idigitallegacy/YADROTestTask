cmake_minimum_required(VERSION 3.0)
project(TestTask)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        TestTask main.cpp

        cfg.h

        Datatype/TableHeader/Header.cpp
        Datatype/TableHeader/ColumnHeader.cpp
        Datatype/TableHeader/RowHeader.cpp

        Datatype/Abstract/Optional.h Datatype/Abstract/Optional.cpp

        Service/IOReader/File/FileReader.cpp
        Service/IOReader/StringArray/StringArrayReader.cpp
        Service/Table/Table.cpp
        Service/Table/TableExecutor.cpp

        Exception/FileNotPermittedException.h
        Exception/EmptyDataException.h
        Exception/InvalidDataPatternException.h
        Exception/UnknownException.h
        Exception/InvalidCellTreeException.h
        Exception/ZeroDivisionException.h
        Exception/InvalidOperatorException.h
        Exception/SelfReferenceException.h
        Exception/InvalidCellAddressException.h)
