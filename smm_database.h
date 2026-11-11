#ifndef SMM_DATABASE_H
#define SMM_DATABASE_H

#include "smm_common.h"

void smmdb_addNode(int node_idx);
int smmdb_getNode(int index);
int smmdb_getNodeCount(void);

#endif