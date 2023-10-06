#include "users.h"
#include "func.h"
#include "glib.h"
#include <stdlib.h>

struct users {
    char nome[STR_SIZE];
    char username[STR_SIZE];
    char genero;
    int idade;
    int dataCriaConta;
    char statusConta;
    int avalTotal;
    int numViagens;
    int distTotal;
    double totalGasto;
    double tipsDadas;
    int ultimaViagem;    
};


USERS newUser() {
    USERS u = malloc(sizeof (struct users));

    u->avalTotal = 0;
    u->numViagens = 0;
    u->totalGasto = 0;
    u->tipsDadas = 0;
    u->distTotal = 0;
    u->ultimaViagem = 0;  
    
    return u;
}

int depenUsers(gconstpointer a, gconstpointer b) {
    const USERS at = (USERS)a;
    const USERS t = (USERS)b;

    if (at->distTotal > t->distTotal) return -1;

    else if (at->distTotal == t->distTotal && (at->ultimaViagem) > (t->ultimaViagem)) return -1;

    else if (at->distTotal == t->distTotal && (at->ultimaViagem) == (t->ultimaViagem) && strcmp(at->username, t->username) < 0) return -1;
    
    else return 1;
}

char *getNomeU(USERS u) {
    char *nr = malloc(sizeof(char)*STR_SIZE+2);
    strcpy(nr, u->nome);

    return nr;
}

char *getUsernameU(USERS u) {
    char *ur = malloc(sizeof(char)*STR_SIZE+2);
    strcpy(ur, u->username);

    return ur;
}

char getGeneroU(USERS u) {
    return u->genero;
}

int getIdadeU(USERS u) {
    return u->idade/365;
}

int getDataCriaContaU(USERS u) {
    return u->dataCriaConta;
}

char getStatusContaU(USERS u) {
    return u->statusConta;
}

double getAvalTotalU(USERS u) {
    return u->avalTotal;
}

int getNumViagensU(USERS u) {
    return u->numViagens;
}

int getDistTotalU(USERS u) {
    return u->distTotal;
}

double getTotalGastoU(USERS u) {
    return u->totalGasto;
}

double getTipsDadasU(USERS u) {
    return u->tipsDadas;
}

int getUltimaViagemU(USERS u) {
    return u->ultimaViagem;
}

int getIdadePerfilU(USERS u) {
    return (DATA_REFERENCIA - u->dataCriaConta)/365;
}



void setUsernameU(USERS u, char str[]) {
    strcpy(u->username, str);
}

void setNomeU(USERS u, char str[]) {
    strcpy(u->nome, str);
}

void setGeneroU(USERS u, char str[]) {
    u->genero = str[0];
}

void setIdadeU(USERS u, char str[]) {
    u->idade = DATA_REFERENCIA - convDataToDias(str);
}

void setDataCriaContaU(USERS u, char str[]) {
    u->dataCriaConta = convDataToDias(str);
}

void setStatusContaU(USERS u, char str[]) {
    u->statusConta = str[0];
} 



void atualizaUltViagemU (USERS u, int lastR){
    u->ultimaViagem = lastR;
}

void incNumViagensU (USERS u){
    u->numViagens++;
}

void incTotalGastoU (USERS u, double auxP){
    u->totalGasto += auxP;
}

void incDistTotalU (USERS u, int auxD){
    u->distTotal += auxD;
}

void atualizaScoreU(USERS u, int auxS){
    u->avalTotal += auxS;
}

void incTipsRecebidasU (USERS u, double auxS){
    u->tipsDadas += auxS;
}