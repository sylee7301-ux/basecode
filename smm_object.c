#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smm_common.h"
#include "smm_object.h"

static char smmNodeName[MAX_NODETYPE][MAX_CHARNAME] = {
    "lecture",
    "restaurant",
    "laboratory",
    "home",
    "gotoLab",
    "foodChance",
    "festival"
};

static char smmGradeName[MAX_GRADE][MAX_CHARNAME] = {
    "A+",
    "A0",
    "A-",
    "B+",
    "B0",
    "B-",
    "C+",
    "C0",
    "C-"
};

static float smmGradeScore[MAX_GRADE] = {
    4.3f,
    4.0f,
    3.7f,
    3.3f,
    3.0f,
    2.7f,
    2.3f,
    2.0f,
    1.7f
};

typedef struct {
    char name[MAX_CHARNAME];
    int objType;
    int type;
    int credit;
    int energy;
    int grade;
} smmObject_t;

// object generation
void* smmObj_genObject(char* name, int objType, int type, int credit, int energy, int grade)
{
    smmObject_t* ptr = (smmObject_t*)malloc(sizeof(smmObject_t));
    if (ptr == NULL)
    {
        printf("[ERROR] failed to create an object!\n");
        return NULL;
    }

    strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;

    return (void*)ptr;
}

// member retrieving
char* smmObj_getName(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;
    return ptr->name;
}

int smmObj_getNdType(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;
    return ptr->type;
}

int smmObj_getCredit(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;
    return ptr->credit;
}

int smmObj_getEnergy(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;
    return ptr->energy;
}

int smmObj_getGrade(void* obj)
{
    smmObject_t* ptr = (smmObject_t*)obj;
    return ptr->grade;
}

// element to string
char* smmObj_getNodeName(int type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(int grade)
{
    return smmGradeName[grade];
}

float smmObj_getGradeScore(int grade)
{
    return smmGradeScore[grade];
}