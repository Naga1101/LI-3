#include "batch.h"
#include "func.h"
#include <stdlib.h>
#include <stdio.h>
#include "query.h"


void batch(DATA d, char *pathI) {
    FILE *inputFile;
    inputFile = fopen (pathI,"r");
    int i = 0, t;

    char str[200], param1[20], param2[20], param3[20], path[50];
    
    while (fgets(str, 200, inputFile)) {
        t = strlen(str)-1;
        if(str[t] == '\n') str[t] = '\0';
        i++;
        sprintf(path,"./Resultados/command%d_output.txt", i);
        switch (str[0]) {
            case '1':
                //printf("\t      -- 1 --\n");
                
                bQuery1 (d, &str[2], path);
                break;
            case '2':
                //printf("\t      -- 2 --\n");

                bQuery2 (d, atoi(&str[2]), path);
                break;
            case '3':
                //printf("\t      -- 3 --\n");

                bQuery3 (d, atoi(&str[2]), path);

                break; 
            case '4':
                //printf("\t      -- 4 --\n");
                    
                bQuery4(d, &str[2], path);
                break; 
            case '5':
                //printf("\t      -- 5 --\n");
                              
                sscanf(&str[2], "%s %s", param1, param2);
                bQuery5(d, convDataToDias(param1), convDataToDias(param2), path);
                break; 
            case '6':
                //printf("\t      -- 6 --\n");

                sscanf(&str[2], "%s %s %s", param1, param2, param3);
                bQuery6(d, param1, convDataToDias(param2), convDataToDias(param3), path);                   
                break; 
            case '7':
                //printf("\t      -- 7 --\n");
                    
                sscanf(&str[2], "%s %s", param1, param2);
                bQuery7(d, atoi(param1) , param2, path);
                break; 
            case '8':
                //printf("\t      -- 8 --\n");
                
                sscanf(&str[2], "%s %s", param1, param2);
                bQuery8(d, param1[0], atoi(param2), path);
                break; 
            case '9':
                //printf("\t      -- 9 --\n");
                
                sscanf(&str[2], "%s %s", param1, param2);
                bQuery9(d, convDataToDias(param1), convDataToDias(param2), path);
                break; 
        }
    }

    fclose(inputFile);
}