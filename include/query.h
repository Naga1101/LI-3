#ifndef QUERY_H
#define QUERY_H

#include "datastruc.h"
#include <ncurses.h>

char *iQuery1 (DATA d, char id[]);

void bQuery1 (DATA d, char id[], char path[]);


void iQuery2 (DATA d, int n, char *output);

void bQuery2 (DATA d, int n, char path[]);


void iQuery3 (DATA d, int n, char *output);

void bQuery3 (DATA d, int n, char path[]);


char *iQuery4(DATA d, char city[]);

void bQuery4(DATA d, char city[], char path[]);


char *iQuery5(DATA d, char *incio, char *fim);

void bQuery5(DATA d, int i, int f, char path[]);


char *iQuery6(DATA d, char city[], char *inicio, char *fim);

void bQuery6(DATA d, char city[], int i, int f, char path[]);


void iQuery7(DATA d, int n, char city[], char *output);

void bQuery7(DATA d, int n , char city[], char path[]);


int iQuery8(DATA d, char g, int age, char *output);

void bQuery8(DATA d, char gender, int age, char path[]);


int iQuery9(DATA d, char *inicio, char *fim, char *output);

void bQuery9(DATA d, int i, int f, char path[]);

#endif