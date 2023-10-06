#include "rides.h"
#include "users.h"
#include "drivers.h"
#include "func.h"


struct rides {
    int id;
    int date;
    DRIVERS driver;
    USERS user;
    char city[STR_SIZE];
    double distance;
    double scoreUser;
    double scoreDriver;
    double tip;
    double cost;
};

RIDES newRide() {
    return malloc(sizeof (struct rides));
}

int depenDateRides(gconstpointer a, gconstpointer b) {
    const RIDES at = (RIDES)a;
    const RIDES t = (RIDES)b;

    if (at->date < t->date) return -1;

    else return 1;
}

int depenIdRides(gconstpointer a, gconstpointer b) {
    const RIDES atr = (RIDES)a;
    const RIDES tr = (RIDES)b;
    
    DRIVERS atd = getDriverR(atr);
    DRIVERS td = getDriverR(tr);

    if (getIdD(atd) < getIdD(td)) return -1;

    else return 1;
}

int depenDistRides(gconstpointer a, gconstpointer b) {
    const RIDES at = (RIDES)a;
    const RIDES t = (RIDES)b;

    if (at->distance > t->distance) return -1;

    else if (at->distance == t->distance && at->date > t->date) return -1;

    else if (at->distance == t->distance && at->date == t->date && at->id > t->id) return -1;

    else return 1;
}

int depenGenderRides(gconstpointer a, gconstpointer b) {
    const RIDES atr = (RIDES)a;
    const RIDES tr = (RIDES)b;
    
    DRIVERS atd = getDriverR(atr);
    USERS atu = getUserR(atr);
    DRIVERS td = getDriverR(tr);
    USERS tu = getUserR(tr);

    if (getDataCriaContaD(atd) < getDataCriaContaD(td))  return -1;

    else if ((getDataCriaContaD(atd) == getDataCriaContaD(td)) && (getDataCriaContaU(atu) < getDataCriaContaU(tu))) return -1;

    else if ((getDataCriaContaD(atd) == getDataCriaContaD(td)) && (getDataCriaContaU(atu) == getDataCriaContaU(tu)) && (getIdR(atr) < getIdR (tr))) return -1;

    else return 1;
}



int getIdR(RIDES r) {
    return r->id;
}

int getDateR(RIDES r) {
    return r->date;
}

DRIVERS getDriverR(RIDES r) {
    return r->driver;
}

USERS getUserR(RIDES r) {
    return r->user;
}

char *getCityR(RIDES r) {
    char *cr = malloc(sizeof(char)*STR_SIZE+2);
    strcpy(cr, r->city);

    return cr;
}

double getDistanceR(RIDES r) {
    return r->distance;
}

double getScoreUserR(RIDES r) {
    return r->scoreUser;
}

double getScoreDriverR(RIDES r) {
    return r->scoreDriver;
}

double getTipR(RIDES r) {
    return r->tip;
}

double getCostR(RIDES r){
    return r->cost;
}




void setIdR (RIDES r, int aux){
    r->id = aux;
}

void setDateR (RIDES r, int aux){
    r->date = aux;
}

void setUserR (RIDES r, USERS u){
    r->user= u;
}

void setDriverR (RIDES r, DRIVERS d){
    r->driver= d;
}

void setCityR (RIDES r, char str[]){
    strcpy(r->city, str);
}

void setDistanceR (RIDES r, double aux){
    r->distance = aux;
}

void setScoreUserR (RIDES r, double aux){
    r->scoreUser = aux;
}

void setScoreDriverR (RIDES r, double aux){
    r->scoreDriver = aux;
}

void setTipR (RIDES r, double aux){
    r->tip = aux;
}

void addCostR (RIDES r, double aux){
    r->cost = aux;
}