//
// Created by elfxe on 08.06.2023.
//

#ifndef TESTTASK_CFG_H
#define TESTTASK_CFG_H

#ifndef INDEX_T
#define INDEX_T long long
#endif

#ifndef WIDTH_T
#define WIDTH_T unsigned short
#endif

#ifndef TABLE_MAX_ELEMENTS
#define TABLE_MAX_ELEMENTS 1000 // used to build a hashtable with minimum of intersections
#endif

#ifndef MAX_RECURSION_DEPTH
#define MAX_RECURSION_DEPTH 100 // used to detect self-references (I've got an idea, how to detect it better, but don't know how to elaborate it)
#endif

#endif //TESTTASK_CFG_H
