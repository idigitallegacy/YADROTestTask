//
// Created by elfxe on 08.06.2023.
//

#ifndef TESTTASK_CFG_H
#define TESTTASK_CFG_H

//    // *************************************** \\
//    || Change these constants if it's required ||
//    \\ *************************************** //

#ifndef INDEX_T
    #define INDEX_T long long
#endif

#ifndef TABLE_MAX_ELEMENTS
    #define TABLE_MAX_ELEMENTS 1000 // used to build a hashtable with minimum of intersections
#endif

#ifndef MAX_RECURSION_DEPTH
    // Set this constant to 0 to unlimit the recursion depth
    #define MAX_RECURSION_DEPTH 300 // used to detect self-references (if the default check didn't pass).
#endif

#ifndef TEST_DATA_PATH
    #ifdef __linux__
        #define TEST_DATA_PATH "./TestData/"
    #elif _WIN32
        // Github workflow path
        #define TEST_DATA_PATH "D:\\a\\YADROTestTask\\YADROTestTask\\TestData\\"
    #elif __APPLE__
        #define TEST_DATA_PATH "./TestData/"
    #endif
#endif





//    // *************************************** \\
//    ||              DO NOT CHANGE              ||
//    \\ *************************************** //

#ifndef PATH_SPLITTER
    #ifdef __linux__
        #define PATH_SPLITTER "/"
    #elif _WIN32
        #define PATH_SPLITTER "\\"
    #elif __APPLE__
        #define PATH_SPLITTER "/"
    #endif
#endif

#ifndef UNDEFINED_CELL_INDEX
    #define UNDEFINED_CELL_INDEX (-1) // used to throw exceptions, while the cell index id undefined yet.
#endif

#ifndef CELL_FORMULA_REGEX_MATCHER
    #define CELL_FORMULA_REGEX_MATCHER "^=[a-zA-Z]+[0-9]+([+-\\/*]{1}[a-zA-Z]+[0-9]+)*$" // used to check if the cell value is formula
#endif

#ifndef CELL_FORMULA_VALUE_REGEX_MATCHER
    #define CELL_FORMULA_VALUE_REGEX_MATCHER "^[a-zA-Z]+[0-9]+([+-\\/*]{1}[a-zA-Z]+[0-9]+)*$" // used to check if the cell formula is correct
#endif

#ifndef CELL_VALUE_REGEX_MATCHER
    #define CELL_VALUE_REGEX_MATCHER "^[0-9]+$" // used to check if the cell value is just a number
#endif

#ifndef COLUMN_NAME_REGEX_MATCHER
    #define COLUMN_NAME_REGEX_MATCHER "^[a-zA-Z]+$" // used to check if the column header name is correct
#endif

#ifndef ROW_NAME_REGEX_MATCHER
    #define ROW_NAME_REGEX_MATCHER "^[0-9]+$" // used to check if the row header name is correct
#endif

#endif //TESTTASK_CFG_H
