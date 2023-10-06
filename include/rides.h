#ifndef RIDES_H
#define RIDES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "drivers.h"


typedef struct rides *RIDES;

int depenDateRides(gconstpointer a, gconstpointer b); //5 6

int depenDistRides(gconstpointer a, gconstpointer b); //9 

int depenGenderRides(gconstpointer a, gconstpointer b); //8

int depenIdRides(gconstpointer a, gconstpointer b); //7

RIDES newRide();



int getIdR(RIDES r);

int getDateR(RIDES r);

DRIVERS getDriverR(RIDES r);

USERS getUserR(RIDES r);

char *getCityR(RIDES r);

double getDistanceR(RIDES r);

double getScoreUserR(RIDES r);

double getScoreDriverR(RIDES r);

double getTipR(RIDES r) ;

double getCostR(RIDES r);



void setIdR (RIDES r, int aux);

void setDateR (RIDES r, int aux);

void setUserR (RIDES r, USERS u);

void setDriverR (RIDES r, DRIVERS d);

void setCityR (RIDES r, char str[]);

void setDistanceR (RIDES r, double aux);

void setScoreUserR (RIDES r, double aux);

void setScoreDriverR (RIDES r, double aux);

void setTipR (RIDES r, double aux);

void addCostR (RIDES r, double aux);

#endif