#ifndef smm_object_h
#define smm_object_h

#include "smm_common.h"

#define SMMObj_TYPE_BOARD           0
#define SMMObj_TYPE_GRADE           1
#define SMMObj_TYPE_FOOD            2
#define SMMObj_TYPE_FESTIVAL        3

// object generation
void* smmObj_genObject(char* name, int objType, int type, int credit, int energy, int grade);

// member retrieving
char* smmObj_getName(void* obj);
int smmObj_getNdType(void* obj);
int smmObj_getCredit(void* obj);
int smmObj_getEnergy(void* obj);
int smmObj_getGrade(void* obj);

// element to string
char* smmObj_getNodeName(int type);
char* smmObj_getGradeName(int grade);
float smmObj_getGradeScore(int grade);

#endif /* smm_object_h */