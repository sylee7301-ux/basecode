#ifndef smm_object_h
#define smm_object_h

/* node type :
    lecture,
    restaurant,
    laboratory,
    home,
    experiment,
    foodChance,
    festival
*/


/* grade :
    A+,
    A0,
    A-,
    B+,
    B0,
    B-,
    C+,
    C0,
    C-
*/s

#include "smm_common.h"

//object generation
void smmObj_genNode(char* name, int type, int credit, int energy);

//member retrieving
char* smmObj_getBoardName(int idx);
int* smmObj_getBoardType(int idx);
int* smmObj_getBoardCredit(int idx);
int* smmObj_getBoardEnergy(int idx);

//element to string
char* smmObj_getNodeName(int type);
char* smmObj_getGradeName(int grade);

// 캡슐화 데이터 get 함수들
char* smmObj_getBoardName(int idx);
int smmObj_getBoardType(int idx);
int smmObj_getBoardCredit(int idx);
int smmObj_getBoardEnergy(int idx);

char* smmObj_getNodeTypeName(int type);

#endif