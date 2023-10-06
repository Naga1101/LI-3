#ifndef BASH_H
#define BASH_H

#include "datastruc.h"

void batche(DATA d, char *pathI, char *pathP);

double timer(long inicio, long fim);

int comparaResultados(char *pathRes, char *pathCorr);

#endif
