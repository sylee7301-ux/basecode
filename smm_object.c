#include <string.h>
#include "smm_common.h"
#include "smm_object.h"

#define MAX_NODETYPE    7
#define MAX_GRADE       9

#define MAX_NODE        50


#define SMMNODE_TYPE_LECTURE       0
#define SMMNODE_TYPE_RESTAURANT    1
#define SMMNODE_TYPE_LABORATORY    2
#define SMMNODE_TYPE_HOME          3
#define SMMNODE_TYPE_GOTOLAB       4
#define SMMNODE_TYPE_FOODCHANCE    5
#define SMMNODE_TYPE_FESTIVAL      6

static char smmNodeName[MAX_NODETYPE][MAX_CHARNAME] = {
    "lecture";
    "restaurant";
    "laboratory";
    "home";
    "gotolab";
    "foodChance";
    "festival";
}

static char board_name[MAX_NODE][MAX_CHARNAME];
static int board_type[MAX_NODE];
static int board_credit[MAX_NODE];
static int board_energy[MAX_NODE];
static int board_nr=0;

//object generation
void smmObj_genNode(char* name, int type, int credit, int energy){
    strcpy{&board_name[board_nr][0], name};
    board_type[board_nr]= type;
    board_credit[board_nr]= credit;
    board_energy[board_nr]= energy;

    board_nr++;
}


//member retrieving
char* smmObj_getBoardName(int idx) {
    return board_name[idx][0];
}

char* smmObj_getBoardType(int idx) {
    return board_type[idx];
}

char* smmObj_getBoardCredit(int idx) {
    return board_credit[idx];
}

char* smmObj_getBoardEnergy(int idx) {
    return board_energy[idx];
}

//element to string
char* smmObj_getNodeName(smmNode_e type) {
    return getNodename[type];
}

char* smmObj_getGradeName(smmGrade_e grade) {
    return smmGradename[grade];
}