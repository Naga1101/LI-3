#include "drivers.h"
#include "func.h"
#include <stdio.h>
#include <string.h>
#include "glib.h"

struct drivers {
    char nome[STR_SIZE];
    int id;
    char genero;
    int idade; //em dias, para "imprimir /365"
    int dataCriaConta; // em dias, para "imprimir /365"
    char statusConta;
    char tipoCarro; // b - basic; g - green; p - premium;
    int avalTotal;
    int numViagens;
    double totalGanho;
    double tipsRecebidas;
    int ultimaViagem;
};

struct driverC {
    double totalScore;
    int numRides;
    DRIVERS driver;
};

DRIVERS newDriver() {
    DRIVERS d = malloc(sizeof (struct drivers));

    d->avalTotal = 0;
    d->numViagens = 0;
    d->totalGanho = 0;
    d->tipsRecebidas = 0;
    d->ultimaViagem = 0;

    return d;
}

DriverPC newDPC(DRIVERS da) {
    DriverPC d = malloc(sizeof(struct driverC));

    d->totalScore = 0;
    d->numRides = 0;
    d->driver = da;
    return d;
}

int depenDrivers(gconstpointer a, gconstpointer b) {
    const DRIVERS at = (DRIVERS)a;
    const DRIVERS t = (DRIVERS)b;

    if (((double) at->avalTotal)/((double) at->numViagens) > ((double) t->avalTotal)/((double) t->numViagens)) return -1;

    else if (((double) at->avalTotal)/((double) at->numViagens) == ((double) t->avalTotal)/((double) t->numViagens) && (at->ultimaViagem) > (t->ultimaViagem)) return -1;

    else if (((double) at->avalTotal)/((double) at->numViagens) == ((double) t->avalTotal)/((double) t->numViagens) && (at->ultimaViagem) == (t->ultimaViagem) && (at->id) < (t->id)) return -1;
    
    else return 1;
}

int depenCity(gconstpointer a, gconstpointer b) {
    const DriverPC at = (DriverPC)a;
    const DriverPC t = (DriverPC)b;

    if (at->totalScore/at->numRides > t->totalScore/t->numRides) return -1;

    else if (at->totalScore/at->numRides == t->totalScore/t->numRides && at->driver->id > t->driver->id) return -1;
    
    else return 1;
}


char *getNomeD(DRIVERS d) {
    char *nr = malloc(sizeof(char)*STR_SIZE+2);
    strcpy(nr, d->nome);

    return nr;
}

int getIdD(DRIVERS d) {
    return d->id;
}

char getGeneroD(DRIVERS d) {
    return d->genero;
}

int getIdadeD(DRIVERS d) {
    return d->idade/365;
}

int getDataCriaContaD(DRIVERS d) {
    return d->dataCriaConta;
}

char getStatusContaD(DRIVERS d) {
    return d->statusConta;
}

char getTipoCarroD(DRIVERS d) {
    return d->tipoCarro;
}

double getAvalTotalD(DRIVERS d) {
    return d->avalTotal;
}

int getNumViagensD(DRIVERS d) {
    return d->numViagens;
}

double getTotalGanhoD(DRIVERS d) {
    return d->totalGanho;
}

double getTipsRecebidasD(DRIVERS d) {
    return d->tipsRecebidas;
}

int getUltimaViagemD(DRIVERS d) {
    return d->ultimaViagem;
}


void setIdD (DRIVERS d, char str[]){
    d->id = atoi(str);
}

void setNomeD (DRIVERS d, char str[]){
    strcpy (d->nome, str);
}

void setIdadeD (DRIVERS d, char str[]){
    d->idade = DATA_REFERENCIA - convDataToDias(str);
}

void setGeneroD (DRIVERS d, char str[]){
    d->genero = str[0];
}

void setTipoCarroD (DRIVERS d, char str[]){
    d->tipoCarro = str[0];
}

void setDataCriaContaD (DRIVERS d, char str[]){
    d->dataCriaConta = convDataToDias(str);
}

void setStatusContaD (DRIVERS d, char str[]){
    d->statusConta = str[0];
}

int getIdadePerfilD(DRIVERS d) {
    return (DATA_REFERENCIA - d->dataCriaConta)/365;
}

double getTotalScoreDPC(DriverPC d) {
    return d->totalScore;
}

int getNumRidesDPC(DriverPC d) {
    return d->numRides;
}

DRIVERS getDriver(DriverPC d) {
    return d->driver;
}


void incNumViagensD (DRIVERS d){
    d->numViagens++;
}

void atualizaUltViagemD (DRIVERS d, int lastR){
    d->ultimaViagem = lastR;
}

void incTotalGanhoD (DRIVERS d, double auxP){
    d->totalGanho += auxP;
}

void atualizaScoreD(DRIVERS d, int auxS){
    d->avalTotal += auxS;
}

void incTipsRecebidasD (DRIVERS d, double auxS){
    d->tipsRecebidas += auxS;
}

void updateDPC (DriverPC d, double score) {
    d->totalScore += score;
    d->numRides++;
}