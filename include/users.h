#ifndef USERS_H
#define USERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glib.h"


#define STR_SIZE 50
#define DATA_REFERENCIA 738312        // 09/10/2022 em dias

typedef struct users *USERS;


USERS newUser();

int depenUsers(gconstpointer a, gconstpointer b);


char *getNomeU(USERS u);

char *getUsernameU(USERS u);

char getGeneroU(USERS u);

int getIdadeU(USERS u);

int getDataCriaContaU(USERS u);

char getStatusContaU(USERS u);

double getAvalTotalU(USERS u);

int getNumViagensU(USERS u) ;

int getDistTotalU(USERS u);

double getTotalGastoU(USERS u);

double getTipsDadasU(USERS u);

int getUltimaViagemU(USERS u);

int getIdadePerfilU(USERS u);


void setUsernameU(USERS u, char str[]);

void setNomeU(USERS u, char str[]);

void setGeneroU(USERS u, char str[]);

void setIdadeU(USERS u, char str[]);

void setDataCriaContaU(USERS u, char str[]);

void setStatusContaU(USERS u, char str[]);



void atualizaUltViagemU (USERS u, int lastR);

void incNumViagensU (USERS u);

void incTotalGastoU (USERS u, double auxP);

void incDistTotalU (USERS u, int auxD);

void atualizaScoreU(USERS u, int auxS);

void incTipsRecebidasU (USERS u, double auxS);

#endif