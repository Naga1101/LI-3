#ifndef DRIVERS_H
#define DRIVERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glib.h"


#define STR_SIZE 50
#define DATA_REFERENCIA 738312        // 09/10/2022 em dias

typedef struct drivers *DRIVERS;

typedef struct driverC *DriverPC;

DRIVERS newDriver();

DriverPC newDPC(DRIVERS da);

int depenDrivers(gconstpointer at, gconstpointer t);

int depenCity(gconstpointer a, gconstpointer b);



char *getNomeD(DRIVERS d);

int getIdD(DRIVERS d);

char getGeneroD(DRIVERS d);

int getIdadeD(DRIVERS d);

int getDataCriaContaD(DRIVERS d);

char getStatusContaD(DRIVERS d);

char getTipoCarroD(DRIVERS d);

double getAvalTotalD(DRIVERS d);

int getNumViagensD(DRIVERS d);

double getTotalGanhoD(DRIVERS d);

double getTipsRecebidasD(DRIVERS d);

int getUltimaViagemD(DRIVERS d);

int getIdadePerfilD(DRIVERS d);

double getTotalScoreDPC(DriverPC d);

int getNumRidesDPC(DriverPC d);

DRIVERS getDriver(DriverPC d);



void setIdD (DRIVERS d, char str[]);

void setNomeD (DRIVERS d, char str[]);

void setIdadeD (DRIVERS d, char str[]);

void setGeneroD (DRIVERS d, char str[]);

void setTipoCarroD (DRIVERS d, char str[]);

void setDataCriaContaD (DRIVERS d, char str[]);

void setStatusContaD (DRIVERS d, char str[]);



void incNumViagensD (DRIVERS d);

void atualizaUltViagemD (DRIVERS d, int lastR);

void incTotalGanhoD (DRIVERS d, double auxP);

void atualizaScoreD(DRIVERS d, int auxS);

void incTipsRecebidasD (DRIVERS d, double auxS);

void updateDPC (DriverPC d, double score);

#endif