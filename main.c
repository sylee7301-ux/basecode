#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smm_common.h"
#include "smm_object.h"
#include "smm_database.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTIVALFILEPATH "marbleFestivalConfig.txt"

//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;

//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
void generatePlayers(int n, int initEnergy); //generate a new player
void printGrades(int player); //print grade history of the player
void goForward(int player, int step); //make player go "step" steps on the board
void printPlayerStatus(void); //print all player status at the beginning of turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture
void* findGrade(int player, char *lectureName); //find the grade from the player
void printGrades(int player); //print all the grade history of the player
#endif

int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);

#if 0
    if (c == 'g')
        printGrades(player);
#endif

    return (rand() % 6 + 1);
}

//action code when a player stays at a node
void actionNode(int player)
{
    // switch(type)
    // {
    //     //case lecture:
    //     default:
    //         break;
    // }
}

int main(int argc, const char * argv[]) {
    FILE* fp;
    char name[MAX_CHARNAME];
    int type, credit, energy;
    int pos = 0;
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;

    srand((unsigned int)time(NULL));

    // 1. import parameters
    // 1-1. boardConfig
    if ((fp = fopen(BOARDFILEPATH, "r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }

    printf("Reading board component......\n");
    while (fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4) //read a node parameter
    {
        // store the parameter set
        smmObj_genNode(name, type, credit, energy);
        smmdb_addNode(obj_id);
        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes: %i\n", board_nr);

    //2. food card config
    if ((fp = fopen(FoodFILEPATH, "r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }

    printf("\n\nReading food card component......\n");
    while (2 == fscanf(fp, "%s %i", name, &energy)) //read a food parameter set
    {
        //store the parameter set
        food_nr++;
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);

    //festival card config
    if ((fp = fopen(FESTFILEPATH, "r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        getchar();
        return -1;
    }

    printf("\n\nReading festival card component......\n");
    while (1 == fscanf(fp, "%s", name)) //read a festival card string
    {
        //store the parameter set
        festival_nr++;
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);

    //2. Player configuration -----------------------------------------
    /*
    do
    {
        //input player number to player_nr
    }
    while ();
    generatePlayers();
    */

    //3. SM Marbld game starts
    while () //is anybody graduated?
    {
        int die_result;

        //4-1. initial printing
        //printPlayerStatus();

        //4-2. die rolling (if not in experiment)
        die_result = rolldie()
        pos+=die_result;

        printf("node %i : %s, %i, %i, %i\n",
            smmObj_getBordName(pos),
            smmObj_getBordType(pos),
            smmObj_getBordCredit(pos),
            smmObj_getBordEnergy(pos),
        
        //4-3. go forward
        //goForward();

        //4-4. take action at the destination node of the board
        //actionNode();

        //4-5. next turn
        
    }

    // 4. 보드 설정에 대한 검증 출력
    for (int i = 0; i < board_nr; i++) {
        int node_idx = smmdb_getNode(i);
        int node_type = smmObj_getType(node_idx);

        printf("node %d : %s, %s, %i, %i\n",
               i,
               smmObj_getBoardName(i),
               smmNodeName[smmObj_getBoardType(i)],
               smmObj_getBoardCredit(i),
               smmObj_getBoardEnergy(i));
    }

    return 0;
}