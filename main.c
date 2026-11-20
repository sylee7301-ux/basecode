#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smm_common.h"
#include "smm_object.h"
#include "smm_database.h"

// board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;
static int player_nr;
static int lab_index;
static int homeCharge;

typedef struct {
    int credit;
    int energy;
    int position;
    char name[MAX_CHARNAME];
    int isGraduate;
    int inExperiment;
} smm_player_t;

static smm_player_t players[MAX_PLAYER];

// function prototypes
int isGraduated(void);
void generatePlayers(int n, int initEnergy);
void goForward(int player, int step);
void printPlayerStatus(void);
float calcTotalGrade(int player);
int takeLecture(int player, char *lectureName, int credit);
void* findGrade(int player, char *lectureName);
void printGrades(int player);
int rolldie(int player);
void actionNode(int player);

int isGraduated(void)
{
    int i;
    for (i = 0; i < player_nr; i++)
    {
        if (players[i].isGraduate == 1)
            return i;
    }
    return -1;
}

void generatePlayers(int n, int initEnergy)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("Input player %i name : ", i);
        scanf("%s", players[i].name);
        fflush(stdin);

        players[i].position = 0;
        players[i].credit = 0;
        players[i].energy = initEnergy;
        players[i].isGraduate = 0;
        players[i].inExperiment = 0;
    }
}

int rolldie(int player)
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);

    if (c == 'g')
        printGrades(player);

    return (rand() % MAX_DIE + 1);
}

void goForward(int player, int step)
{
    int i;
    void* ptr;

    for (i = 0; i < step; i++)
    {
        players[player].position = (players[player].position + 1) % board_nr;
        ptr = smmdb_getData(LISTNO_NODE, players[player].position);
        printf(" => Jump to %s\n", smmObj_getName(ptr));

        if (smmObj_getNdType(ptr) == SMMNODE_TYPE_HOME)
        {
            players[player].energy += homeCharge;
            printf("     -> returned to HOME! energy charged by %i (total : %i)\n",
                   homeCharge, players[player].energy);

            if (players[player].credit >= GRADUATE_CREDIT)
            {
                players[player].isGraduate = 1;
                break;
            }
        }
    }
}

void printPlayerStatus(void)
{
    int i;
    void* ptr;

    printf("\n\n========================== PLAYER STATUS ==========================\n");
    for (i = 0; i < player_nr; i++)
    {
        ptr = smmdb_getData(LISTNO_NODE, players[i].position);
        if (players[i].inExperiment == 1)
        {
            printf("%s at %i.%s(exp.), credit: %i, energy: %i\n",
                   players[i].name, players[i].position, smmObj_getName(ptr),
                   players[i].credit, players[i].energy);
        }
        else
        {
            printf("%s at %i.%s, credit: %i, energy: %i\n",
                   players[i].name, players[i].position, smmObj_getName(ptr),
                   players[i].credit, players[i].energy);
        }
    }
    printf("========================== PLAYER STATUS ==========================\n\n");
}

float calcTotalGrade(int player)
{
    int i;
    int len = smmdb_len(LISTNO_OFFSET_GRADE + player);
    int totalCredit = 0;
    float totalScore = 0.0f;

    if (len == 0)
        return 0.0f;

    for (i = 0; i < len; i++)
    {
        void* ptr = smmdb_getData(LISTNO_OFFSET_GRADE + player, i);
        int credit = smmObj_getCredit(ptr);
        int grade = smmObj_getGrade(ptr);
        totalScore += credit * smmObj_getGradeScore(grade);
        totalCredit += credit;
    }

    if (totalCredit == 0)
        return 0.0f;

    return totalScore / totalCredit;
}

void* findGrade(int player, char *lectureName)
{
    int i;
    int len = smmdb_len(LISTNO_OFFSET_GRADE + player);

    for (i = 0; i < len; i++)
    {
        void* ptr = smmdb_getData(LISTNO_OFFSET_GRADE + player, i);
        if (strcmp(smmObj_getName(ptr), lectureName) == 0)
        {
            return ptr;
        }
    }
    return NULL;
}

int takeLecture(int player, char *lectureName, int credit)
{
    int grade = rand() % MAX_GRADE;
    void* gradeObj = smmObj_genObject(lectureName, SMMObj_TYPE_GRADE, 0, credit, 0, grade);
    smmdb_addTail(LISTNO_OFFSET_GRADE + player, gradeObj);
    return grade;
}

void printGrades(int player)
{
    int i;
    int len = smmdb_len(LISTNO_OFFSET_GRADE + player);

    printf(" --> Printing player %s's grade (average %f) ::::\n",
           players[player].name, calcTotalGrade(player));

    for (i = 0; i < len; i++)
    {
        void* ptr = smmdb_getData(LISTNO_OFFSET_GRADE + player, i);
        printf(" => %s (credit:%i) : %s\n",
               smmObj_getName(ptr),
               smmObj_getCredit(ptr),
               smmObj_getGradeName(smmObj_getGrade(ptr)));
    }
}

void actionNode(int player)
{
    void* ptr = smmdb_getData(LISTNO_NODE, players[player].position);
    int type = smmObj_getNdType(ptr);
    int credit = smmObj_getCredit(ptr);
    int energy = smmObj_getEnergy(ptr);
    char choice[MAX_CHARNAME];

    switch (type)
    {
        case SMMNODE_TYPE_LECTURE:
            if (findGrade(player, smmObj_getName(ptr)) != NULL)
            {
                printf(" -> %s has already taken the lecture %s!!\n",
                       players[player].name, smmObj_getName(ptr));
                break;
            }
            if (players[player].energy < energy)
            {
                printf(" -> %s is too hungry to take the lecture %s (remained:%i, required:%i)\n",
                       players[player].name, smmObj_getName(ptr), players[player].energy, energy);
                break;
            }

            while (1)
            {
                printf(" -> Lecture %s (credit:%i, energy:%i) starts! are you going to join? or drop? : ",
                       smmObj_getName(ptr), credit, energy);
                scanf("%s", choice);
                fflush(stdin);

                if (strcmp(choice, "join") == 0)
                {
                    int grade = takeLecture(player, smmObj_getName(ptr), credit);
                    players[player].credit += credit;
                    players[player].energy -= energy;
                    printf(" -> %s successfully takes the lecture %s with grade %s (average : %f), remained energy : %i)\n",
                           players[player].name, smmObj_getName(ptr),
                           smmObj_getGradeName(grade), calcTotalGrade(player), players[player].energy);
                    break;
                }
                else if (strcmp(choice, "drop") == 0)
                {
                    printf(" -> Player %s drops the lecture %s!\n",
                           players[player].name, smmObj_getName(ptr));
                    break;
                }
                else
                {
                    printf(" -> invalid input! input \"drop\" or \"join\"!\n");
                }
            }
            break;

        case SMMNODE_TYPE_RESTAURANT:
            players[player].energy += energy;
            printf(" -> Let's eat in %s and charge %i energies (remained energy : %i)\n",
                   smmObj_getName(ptr), energy, players[player].energy);
            break;

        case SMMNODE_TYPE_LABORATORY:
            if (players[player].inExperiment == 1)
            {
                int exp_res = rand() % MAX_DIE + 1;
                printf(" -> Experiment time! Let's see if you can satisfy professor (threshold: %i)\n", energy);
                printf(" -> Experiment result : %i, ", exp_res);
                if (exp_res >= energy)
                {
                    players[player].inExperiment = 0;
                    printf("success! %s can exit this lab!\n", players[player].name);
                }
                else
                {
                    printf("fail T_T. %s needs more experiment......\n", players[player].name);
                }
            }
            else
            {
                printf(" -> This is not experiment time. You can go through this lab.\n");
            }
            break;

        case SMMNODE_TYPE_HOME:
            if (players[player].credit >= GRADUATE_CREDIT)
            {
                players[player].isGraduate = 1;
            }
            break;

        case SMMNODE_TYPE_GOTOLAB:
            printf(" -> OMG! This is experiment time!! Player %s goes to the lab.\n",
                   players[player].name);
            players[player].position = lab_index;
            players[player].inExperiment = 1;
            break;

        case SMMNODE_TYPE_FOODCHANCE:
        {
            char c;
            int randFood = rand() % food_nr;
            void* foodPtr = smmdb_getData(LISTNO_FOODCARD, randFood);
            int fEnergy = smmObj_getEnergy(foodPtr);

            printf(" -> %s gets a food chance! press any key to pick a food card: ", players[player].name);
            c = getchar();
            fflush(stdin);

            players[player].energy += fEnergy;
            printf(" -> %s picks %s and charges %i (remained energy : %i)\n",
                   players[player].name, smmObj_getName(foodPtr), fEnergy, players[player].energy);
            break;
        }

        case SMMNODE_TYPE_FESTIVAL:
        {
            char c;
            int randFest = rand() % festival_nr;
            void* festPtr = smmdb_getData(LISTNO_FESTCARD, randFest);

            printf(" -> %s participates to Snow Festival! press any key to pick a festival card: ", players[player].name);
            c = getchar();
            fflush(stdin);

            printf(" -> MISSION : %s !!\n", smmObj_getName(festPtr));
            printf("    (Press any key when mission is ended.) ");
            c = getchar();
            fflush(stdin);
            break;
        }

        default:
            break;
    }
}

int main(int argc, const char * argv[]) {
    FILE* fp;
    char name[MAX_CHARNAME];
    int type, credit, energy;
    int turn = 0;

    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    lab_index = 0;
    homeCharge = 0;

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
    while (fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4)
    {
        void* obj = smmObj_genObject(name, SMMObj_TYPE_BOARD, type, credit, energy, 0);
        smmdb_addTail(LISTNO_NODE, obj);
        printf(" => %i. %s (%s), credit:%i, energy:%i\n",
               board_nr, name, smmObj_getNodeName(type), credit, energy);

        if (type == SMMNODE_TYPE_HOME)
            homeCharge = energy;
        if (type == SMMNODE_TYPE_LABORATORY)
            lab_index = board_nr;

        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);

    // 1-2. food card config
    if ((fp = fopen(FOODFILEPATH, "r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        getchar();
        return -1;
    }

    printf("\n\nReading food card component......\n");
    while (fscanf(fp, "%s %i", name, &energy) == 2)
    {
        void* obj = smmObj_genObject(name, SMMObj_TYPE_FOOD, 0, 0, energy, 0);
        smmdb_addTail(LISTNO_FOODCARD, obj);
        printf(" => %i. %s, charge:%i\n", food_nr, name, energy);
        food_nr++;
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);

    // 1-3. festival card config
    if ((fp = fopen(FESTIVALFILEPATH, "r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTIVALFILEPATH);
        getchar();
        return -1;
    }

    printf("\n\nReading festival card component......\n");
    while (fscanf(fp, "%s", name) == 1)
    {
        void* obj = smmObj_genObject(name, SMMObj_TYPE_FESTIVAL, 0, 0, 0, 0);
        smmdb_addTail(LISTNO_FESTCARD, obj);
        printf(" => %i. %s\n", festival_nr, name);
        festival_nr++;
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);

    // 2. Player configuration
    printf("\n\n\n=======================================================================\n");
    printf("-----------------------------------------------------------------------\n");
    printf("                Sookmyung Marble !! Let's Graduate (total credit : %i)!!\n", GRADUATE_CREDIT);
    printf("-----------------------------------------------------------------------\n");
    printf("=======================================================================\n\n\n\n");

    do
    {
        printf("Input No. of players (1 ~ %i) : ", MAX_PLAYER);
        scanf("%i", &player_nr);
        fflush(stdin);
    }
    while (player_nr <= 0 || player_nr > MAX_PLAYER);

    generatePlayers(player_nr, homeCharge);

    // 3. SM Marble game starts
    while (isGraduated() == -1)
    {
        int die_result;

        // 4-1. initial printing
        printPlayerStatus();

        printf("This is %s's turn ::::", players[turn].name);

        // 4-2. die rolling (if not in experiment)
        if (players[turn].inExperiment == 0)
        {
            die_result = rolldie(turn);
            printf(" --> result : %i\n", die_result);

            // 4-3. go forward
            goForward(turn, die_result);
        }
        else
        {
            printf("\n");
        }

        // 4-4. take action at the destination node of the board
        actionNode(turn);

        // 4-5. next turn
        turn = (turn + 1) % player_nr;
    }

    int winner = isGraduated();
    printf("\n\n=======================================================================\n");
    printf("-----------------------------------------------------------------------\n");
    printf("Congraturation!!!! %s graduates with credits %i (grade:%f)!\n",
           players[winner].name, players[winner].credit, calcTotalGrade(winner));
    printf("=======================================================================\n");

    return 0;
}