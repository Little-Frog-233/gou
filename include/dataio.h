#ifndef _DATAIO_H_
#define _DATAIO_H_

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

extern struct TP_data 
{
    double coor[3];
    // tw means time and water
    double * tw;
    // below are the pointer to the phrase position
    double M2;
    double S2;
    double K1;
    double O1;

    // below are the pointer to the f and u
    double * M2_f;
    double * M2_u;
    double * K1_f;
    double * K1_u;
    double * O1_f;
    double * O1_u;

    double S2_f;
    double S2_u;

    double * founier;
}TP;

typedef struct _TPNode
{
    struct TP_data data;
    struct _TPNode * next;
}TPNode;

void dataRead();
TPNode * createListFromFile(string );
void find_lessthannum(TPNode * );
void destroyListTP(TPNode * );
int lenListTP(TPNode * );
void traverseTPList(TPNode *, int );
void saveListTP2File(TPNode *, string );
void parameterCal(TPNode *);
void dataTrans(TPNode * head);

#endif
