#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include "drivers.h"
#include "users.h"
#include "rides.h"

typedef struct data *DATA;

DATA init();

void cleanStruct(DATA d);


void insertDriver(int id, DRIVERS nd, DATA d);

void insertUser(char username[], USERS nu, DATA d);

void insertRide(RIDES nr, DATA d);

DRIVERS lookUpDriver(int id, DATA d);

USERS lookUpUser(char username[], DATA d);

GList *getOrdUsers(DATA d);

GList *getOrdDrivers(DATA d);

GList *lookUpCityRides(char city[], DATA d);

GList *lookUpTopDrivRides(char city[], DATA d);

GList *getRides(DATA d);

int getArraySize(DATA d);


void createLists(DATA d);

#endif