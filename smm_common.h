#ifndef smm_common_h
#define smm_common_h

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARNAME                200

#define GRADUATE_CREDIT             30
#define MAX_DIE                     6
#define MAX_PLAYER                  10

#define MAX_NODETYPE                7
#define MAX_GRADE                   9
#define MAX_NODE                    50

#define SMMNODE_TYPE_LECTURE        0
#define SMMNODE_TYPE_RESTAURANT     1
#define SMMNODE_TYPE_LABORATORY     2
#define SMMNODE_TYPE_HOME           3
#define SMMNODE_TYPE_GOTOLAB        4
#define SMMNODE_TYPE_FOODCHANCE     5
#define SMMNODE_TYPE_FESTIVAL       6

#define SMMNODE_GRADE_APLUS         0
#define SMMNODE_GRADE_AZERO         1
#define SMMNODE_GRADE_AMINUS        2
#define SMMNODE_GRADE_BPLUS         3
#define SMMNODE_GRADE_BZERO         4
#define SMMNODE_GRADE_BMINUS        5
#define SMMNODE_GRADE_CPLUS         6
#define SMMNODE_GRADE_CZERO         7
#define SMMNODE_GRADE_CMINUS        8

#define BOARDFILEPATH               "marbleBoardConfig.txt"
#define FOODFILEPATH                "marbleFoodConfig.txt"
#define FESTIVALFILEPATH            "marbleFestivalConfig.txt"

#endif /* smm_common_h */