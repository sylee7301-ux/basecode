#ifndef SMM_DATABASE_H
#define SMM_DATABASE_H

#include "smm_common.h"

// 보드 및 카드 데이터 추가/조회
void smmdb_addNode(int node_idx);
int smmdb_getNode(int index);
int smmdb_getNodeCount(void);

#endif