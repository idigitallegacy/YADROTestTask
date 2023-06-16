//
// Created by elfxe on 08.06.2023.
//

#ifndef TESTTASK_CFG_H
#define TESTTASK_CFG_H

#ifndef INDEX_T
#define INDEX_T long long
#endif

#ifndef TABLE_MAX_ELEMENTS
#define TABLE_MAX_ELEMENTS 1000 // used to build a hashtable with minimum of intersections
#endif

#ifndef MAX_RECURSION_DEPTH
#define MAX_RECURSION_DEPTH 100 // used to detect self-references (I've got an idea, how to detect it better, but don't know how to elaborate it)
#endif

#ifndef UNDEFINED_CELL_INDEX
#define UNDEFINED_CELL_INDEX -1 // used to throw exceptions, while the cell index id undefined yet.
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
