#include "query.h"
#include "users.h"
#include "datastruc.h"


void iQuery3 (DATA d, int n, char *output){
    USERS t;
    GList *list = getOrdUsers(d);
    char *nome, *username, strB[BUFSIZ];
    output[0]='\0';

    while (list != NULL && n > 0) {
        t = (USERS)list->data;

        if(getStatusContaU(t) != 'i'){
            nome = getNomeU(t);
            username = getUsernameU(t);
            sprintf(strB, "%s;%s;%d\n", username, nome, getDistTotalU(t));
            strcat(output, strB);
            free(nome);
            free(username);
            n--;
        }
        list = g_list_next(list);
    }
}

void bQuery3 (DATA d, int n, char path[]) {

    FILE *result = fopen(path, "w");

    USERS t;
    GList *list = getOrdUsers(d);
    char *nome, *username;

    while (list != NULL && n > 0) {
        t = (USERS)list->data;

        if(getStatusContaU(t) != 'i'){
            nome = getNomeU(t);
            username = getUsernameU(t);
            fprintf(result,"%s;%s;%d\n", username, nome, getDistTotalU(t));
            free(nome);
            free(username);
            n--;
        }
        
        list = g_list_next(list);
        
    } 

    fclose(result);
    
}