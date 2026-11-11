#ifndef SMM_OBJECT_H
#define SMM_OBJECT_H

#include "smm_common.h"

// 객체 생성
void smmObj_genNode(char* name, int type, int credit, int energy);

// 캡슐화 데이터 get 함수들
char* smmObj_getBoardName(int idx);
int smmObj_getBoardType(int idx);
int smmObj_getBoardCredit(int idx);
int smmObj_getBoardEnergy(int idx);

char* smmObj_getNodeTypeName(int type);

#endif