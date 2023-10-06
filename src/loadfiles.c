#include "loadfiles.h"
#include "func.h"
#include <stdlib.h>
#include <stdio.h>

#include "drivers.h"
#include "users.h"
#include "rides.h"

void loadTableU(DATA d, char *pathUsers) {
    FILE *lUsers;
    lUsers = fopen (pathUsers, "r");
    fseek(lUsers, 75, SEEK_SET);

    USERS newU = newUser();

    char *line = (char*) malloc(BUFSIZ), *token, *username;
    size_t len = 0;
    int flag, stop;

    while (fgets(line, BUFSIZ, lUsers) != NULL) {
        len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        if (checkBlank(line)) continue;
        token = strtok(line, ";");
        flag = 1;
        stop = 1;
        while (token != NULL) {
            switch (flag) {
                case 1:
                    //username
                    setUsernameU(newU, token);
                    break;
                case 2:
                    //name
                    setNomeU(newU, token);
                    break;
                case 3:
                    //gender
                    setGeneroU(newU, token);
                    break;
                case 4:
                    //birth_date
                    if (checkDate(token)) setIdadeU(newU, token);
                    else stop = -1;
                    break;
                case 5:
                    //account_creation
                    if (checkDate(token)) setDataCriaContaU(newU, token);
                    else stop = -1;
                    break;
                case 6:
                    //pay_method
                    break;
                case 7:
                    //account_status
                    strcpy(token, setLowercase(token));
                    if (checkAccountStatus(token)) setStatusContaU(newU, token);
                    else stop = -1;
                    break;           
            }
            flag++;

            if (stop == -1) break;
            if (flag > 7) {
                username = getUsernameU(newU);
                insertUser(username, newU, d);
                newU = newUser();
                break;
            }

            token = strtok(NULL, ";");
        }
    }
    fclose(lUsers);
    free(line);
}

void loadTableD(DATA d, char *pathDrivers) {
    FILE *lDrivers;
    lDrivers = fopen (pathDrivers, "r");
    fseek(lDrivers, 88, SEEK_SET);

    DRIVERS newD = newDriver();

    char *line = (char*) malloc(BUFSIZ), *token;
    size_t len = 0;
    int flag, stop;

    while (fgets(line, BUFSIZ, lDrivers) != NULL) {
        len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        if (checkBlank(line)) continue;
        token = strtok(line, ";");
        flag = 1;
        stop = 0;

        while (token != NULL) {            
            switch (flag) {
                case 1:
                    //id
                    setIdD(newD, token);
                    break;
                case 2:
                    //name
                    setNomeD(newD, token);
                    break;
                case 3:
                    //birth_date
                    if (checkDate(token)) setIdadeD(newD, token);
                    else stop = -1;
                    break;
                case 4:
                    //gender
                    setGeneroD (newD, token);
                    break;
                case 5:
                    //car_class
                    strcpy(token, setLowercase(token));
                    if (checkCarClassD(token)) setTipoCarroD(newD, token);
                    else stop = -1;
                    break;
                case 6:
                    //license_plate
                    break;
                case 7:
                    //city
                    break;
                case 8:
                    //account_creation
                    if (checkDate(token)) setDataCriaContaD(newD, token);
                    else stop = -1;
                    break;
                case 9:
                    //account_status
                    strcpy(token, setLowercase(token));
                    if (checkAccountStatus(token)) setStatusContaD(newD, token);
                    else stop = -1;
                    break;           
            }
            flag++;

            if (stop == -1) break;
            if (flag > 9) {
                insertDriver(getIdD(newD), newD, d);
                newD = newDriver();
                break;
            }
            token = strtok(NULL, ";");
        }
    }
    fclose(lDrivers);
    free(line);
}

void loadTableR(DATA d, char *pathRides) {
    FILE *lRides;

    lRides = fopen (pathRides, "r");

    DRIVERS newD;
    USERS newU;
    RIDES newR = newRide();

    fseek(lRides, 72, SEEK_SET);

    char *line = (char*) malloc(BUFSIZ), *token;
    size_t len = 0;
    int flag, stop, lastR;
    double auxP = 0, auxD = 0, auxSU = 0, auxSD = 0, auxT = 0;
  
    while (fgets(line, BUFSIZ, lRides) != NULL) {
        len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        if (checkBlankR(line)) continue;
        token = strtok(line, ";");
        flag = 1;
        stop = 0;

        while (token != NULL) {
            switch (flag) {
                case 1:
                    //id
                    setIdR(newR, atoi(token));
                    break;
                case 2:
                    //date
                    if (checkDate(token)){
                        lastR = convDataToDias(token);
                        setDateR(newR, lastR);
                    }
                    else stop = -1;    
                    break;
                case 3:
                    //id driver
                    newD = lookUpDriver(atoi(token), d);
                    setDriverR(newR, newD);
                    break;
                case 4:
                    //username
                    newU = lookUpUser(token, d);
                    setUserR(newR, newU);
                    break;
                case 5:
                    //city
                    setCityR(newR, token);
                    break;
                case 6:
                    //distance
                    if (checkDistance(token)) {
                        auxD = atof(token);
                        auxP = precoPorViagem(getTipoCarroD(newD), auxD);
                        addCostR(newR, auxP);
                        setDistanceR(newR, auxD);
                    }
                    else stop = -1;
                    break;
                case 7:
                    //score_user
                    if (checkScore(token)){
                        auxSU = atof(token);
                        setScoreUserR(newR, auxSU);
                    }
                    else stop = -1;
                    break;
                case 8:
                    //score_driver
                    if (checkScore(token)){
                        auxSD = atof(token);
                        setScoreDriverR(newR, auxSD);
                    }
                    else stop = -1;
                    break;
                case 9:
                    //tip
                    if (checkTips(token)){
                        auxT = (double)atof(token);
                        setTipR(newR, auxT);
                    }
                    else stop = -1;
                    break; 
                case 10:
                    //comment
                    break; 
            }
            flag++;

            if (stop == -1) break;
            if (flag > 9) {
                insertRide(newR, d);
                newR = newRide();

                incNumViagensD(newD);
                incNumViagensU(newU);
                if(getStatusContaD(newD) == 'a' && getStatusContaU(newU) == 'a') { 
                    atualizaUltViagemD(newD, lastR);
                    atualizaUltViagemU(newU, lastR);
                }
                incTotalGanhoD (newD, auxP);
                incTotalGastoU (newU, auxP);
                incDistTotalU (newU, auxD);
                atualizaScoreU(newU, auxSU);
                atualizaScoreD(newD, auxSD);
                incTipsRecebidasD (newD, auxT);
                incTipsRecebidasU (newU, auxT);
                break;
            }

            token = strtok(NULL, ";");
        }
    }
    fclose(lRides);
    free(line);
}


DATA load(char path[]) {
    DATA d = init();

    char pathUsers[200], pathDrivers[200], pathRides[200];

    if (path[strlen(path)-1] != '/') {
        sprintf(pathUsers, "%s/users.csv", path);
        sprintf(pathDrivers, "%s/drivers.csv", path);
        sprintf(pathRides, "%s/rides.csv", path);
    } else {
        sprintf(pathUsers, "%susers.csv", path);
        sprintf(pathDrivers, "%sdrivers.csv", path);
        sprintf(pathRides, "%srides.csv", path);
    }

    loadTableD(d, pathDrivers);
    //printf("\t----- drivers -----\n");

    loadTableU(d, pathUsers);
    //printf("\t  ---- users ----\n");

    loadTableR(d, pathRides);
    //printf("\t   --- rides ---\n");
    
    createLists(d);
    //printf("\t    -- lists --\n");
    
    return d;
}