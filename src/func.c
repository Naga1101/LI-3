#include "func.h"
#include <stdio.h>
#include <ctype.h>

// preço por viagem
double precoPorViagem(char p, double d){
    double r = (double)0;
    if (p == 'b') r = 3.25 + 0.62*d;
    else if( p == 'g') r = 4.00 + 0.79*d;
    else if( p == 'p') r = 5.20 + 0.94*d;
    
    return r;
}

int convDataToDias(char *str) {
    if(str[0] < '0' || str[0] > '9') return 0;

    int r = 0, d, m, a;
    sscanf(str, "%d/%d/%d", &d, &m, &a);

    r = d + a*365;

    for (int i = 1; i < m; i++) 
        switch (i) {
            case 1:
                r = r + 31;
                break;
            case 2:
                r = r + 28;
                break;
            case 3:
                r = r + 31;
                break;
            case 4:
                r = r + 30;
                break;
            case 5:
                r = r + 31;
                break;
            case 6:
                r = r + 30;
                break;
            case 7:
                r = r + 31;
                break;
            case 8:
                r = r + 31;
                break;
            case 9:
                r = r + 30;
                break;
            case 10:
                r = r + 31;
                break;
            case 11:
                r = r + 30;
                break;
            case 12:
                r = r + 31;
                break;
            
        }
    
    return r;

}

char *convDiasToData(int nd) {
    int m = 1, a;
    
    a = nd/365;
    nd -= a*365;

    while (nd > 31) {
        switch (m) {
            case 1:
                nd -= 31;
                break;
            case 2:
                nd -= 28;
                break;
            case 3:
                nd -= 31;
                break;
            case 4:
                nd -= 30;
                break;
            case 5:
                nd -= 31;
                break;
            case 6:
                nd -= 30;
                break;
            case 7:
                nd -= 31;
                break;
            case 8:
                nd -= 31;
                break;
            case 9:
                nd -= 30;
                break;
            case 10:
                nd -= 31;
                break;
            case 11:
                nd -= 30;
                break;
            case 12:
                nd -= 31;
                break;
        }
        m++;
    }
    char *r = (char *)malloc(sizeof(char)*BUFSIZ);

    sprintf(r, "%02d/%02d/%d", nd, m, a);
    return r;
}

// verifica se a data está no formato correto
int checkDate (char *str){
    int i, d, m, a;
    int len = strlen(str);

    for (i=0; i < len; i++){ 
        if(!isdigit(str[i]) && str[i] != '/') return 0;
    }

    if (sscanf(str, "%d/%d/%d", &d, &m, &a)!=3) return 0;

    if (( d < 1 || d > 31) || ( m < 1 || m > 12) || ( a < 1000 || a > 9999)) return 0;

    return 1;
}

char *setLowercase (char str[]){
    int len = strlen(str);
    for(int i=0;i < len;i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

//verificar se o tipo de carro foi inserido corretamente
int checkCarClassD (char str[]){
    if ((strcmp(str, "basic") == 0) || (strcmp(str, "green") == 0) || (strcmp(str, "premium") == 0)) return 1;
    return 0;
}

// verificar se o estado da conta foi inserido corretamente
int checkAccountStatus (char str[]){
    if ((strcmp(str, "active") == 0) || (strcmp(str, "inactive") == 0)) return 1;
    return 0;

}


// verificar o formato de uma distância & score inseridos

int checkScore(char str[]){
    int i, len = strlen(str);
    for(i = 0; i < len; i++){
        if(!isdigit(str[i])) return 0;
    } 
    if (str[0] == '0') return 0;
    return 1;
}


int checkDistance(char str[]){
    int i, len = strlen(str);
    for(i = 0; i < len; i++){
        if(!isdigit(str[i])) return 0;
    }
    if (str[0] == '0') return 0;
    return 1;
}

// verifica formato de scores e Tips 
int checkTips(char str []){
    int i, len = strlen(str);
    for(i = 0; i < len; i++) {
        if(!isdigit(str[i]) && str[i] != '.') return 0;
    } 
    return 1;
}

//verifica se o espaço de informação foi deixado em branco
int checkBlank(char str[]) {
    int i;
    if (str[0] == ';') return 1;
    for(i = 0; str[i+1] != '\0'; i++) {
        if(str[i] == ';' && str[i+1] == ';') return 1;
    }
    if (str[i] == ';') return 1;
    return 0;
}

int checkBlankR(char str[]) {
    int i;
    if (str[0] == ';') return 1;
    for(i = 0; str[i+1] != '\0'; i++) {
        if(str[i] == ';' && str[i+1] == ';') return 1;
    }
    return 0;
}