#ifndef SMM_OBJECT_H
#define SMM_OBJECT_H

#include "smm_common.h"

// 객체 생성 및 속성 정의
void smmObj_genNode(char* name, int type, int credit, int energy);

// 캡슐화 데이터 get 함수들
char* smmObj_getBordName(int idx);
char* smmObj_getBoardType(int idx);
char* smmObj_getBoardCredit(int idx);
char* smmObj_getBoardEnergy(int idx);

#endif