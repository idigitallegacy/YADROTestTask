cmake_minimum_required(VERSION 3.0)
project(TestTask)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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

enable_testing()

add_executable(
        TestTaskTest
        test.cc

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
        Exception/InvalidCellAddressException.cpp
)
target_link_libraries(
        TestTaskTest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(TestTaskTest)