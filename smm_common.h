#ifndef smm_common_h
#define smm_common_h

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARNAME 200

#define GRADUATE_CREDIT             30
#define MAX_DIE                     6
#define MAX_PLAYER                  10

#define MAX_NODETYPE 7
#define MAX_NODES 50

// 노드 유형 정의
#define SMMNODE_TYPE_LECTURE      0
#define SMMNODE_TYPE_RESTAURANT   1
#define SMMNODE_TYPE_LABORATORY   2
#define SMMNODE_TYPE_HOME         3
#define SMMNODE_TYPE_GOTOLAB      4
#define SMMNODE_TYPE_FOODCHANCE   5
#define SMMNODE_TYPE_FESTIVAL     6

// 노드 유형 문자열 배열
static char smmNodeName[MAX_NODETYPE][MAX_CHARNAME] = {
    "lecture",
    "restaurant",
    "laboratory",
    "home",
    "gotoLab",
    "foodChance",
    "festival"
};

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTIVALFILEPATH "marbleFestivalConfig.txt"

#endif