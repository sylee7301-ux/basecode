#include <stdio.h>
#include "smm_common.h"
#include "smm_database.h"

#define MAX_BOARD_NODES 50

static int boardNodes[MAX_BOARD_NODES];
static int total_board_nodes = 0;

void smmdb_addNode(int node_idx) {
    if (total_board_nodes < MAX_BOARD_NODES) {
        boardNodes[total_board_nodes] = node_idx;
        total_board_nodes++;
    }
}

int smmdb_getNode(int index) {
    if (index >= 0 && index < total_board_nodes) {
        return boardNodes[index];
    }
    return -1;
}

int smmdb_getNodeCount(void) {
    return total_board_nodes;
}