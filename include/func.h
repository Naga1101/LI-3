#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double precoPorViagem(char p, double d);

int convDataToDias(char *str);

char *convDiasToData(int nd);


int checkDate (char *str);

char *setLowercase (char str[]);

int checkCarClassD (char str[]);

int checkAccountStatus (char str[]);

int checkScore(char str[]);

int checkDistance(char str[]);

int checkTips(char str []);

int checkBlank(char str[]);

int checkBlankR(char str[]);

#endif