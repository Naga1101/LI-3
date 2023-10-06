#include "batche.h"
#include "func.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "query.h"

double timer(long inicio, long fim){

        long tempo_tick;
        double tempo_seg;

            tempo_tick = fim - inicio;

            tempo_seg = ((double) tempo_tick ) / CLOCKS_PER_SEC     ;

    return tempo_seg;

}

int comparaResultados(char *pathRes, char *pathCorr){
    FILE *correções;
    FILE *resultados;
    resultados = fopen (pathRes,"r");
    correções = fopen (pathCorr,"r");

    int resultado = 2;
    int teste = EOF;
    int comp = EOF;

    if(!resultados)  perror("\nO ficheiro dos resultados não existe");

    if(!correções)  perror("\nO ficheiro das soluções não existe\n");

    // printf("\nentrei aqui\n");

    teste = fgetc(resultados);
    comp = fgetc(correções);

    /*
    printf("\n%d solução",comp);
   
    printf("\n%d resultado\n",teste);
    */

    if (teste == EOF){

        // printf("\nentrei na cena dos resultados igual a null");
        
        if(comp == EOF) {
            printf("\n| O output não existe");
            resultado = 0;  //// resultado igual a 0 acontece quando o resultado e a solução são NULL
            return resultado;
        }

        else {
            printf("\n| O resultado deu null e devia devolver um output");
            resultado = -1; //// resultado igual a -1 acontece quando o resultado da query é NULL mas devia dar uma resposta diferente
            return resultado;
        }

    }

    if (comp == EOF){
         printf("\n| O resultado devia dar null e devolveu um output");
         resultado = -2;  //// resultado igual a -2 acontece quando a query têm um resultado mas devia dar NULL
         return resultado;
    }

     while ((teste = fgetc(correções)) != EOF && (comp = fgetc(resultados)) != EOF) {
                           // printf("\nentrei na cena do while\n");
                            if (teste != comp) {
                            printf("\n| O output está errado");
                            resultado = -1; //// resultado igual a -1 acontece quando o resultado da query é diferente à solução
                            return resultado;                                  
                        }   
     }

    printf("\n| O output está correto");

        resultado = 1; //// resultado igual a 1 acontece quando o resultado da query está correto

    fclose(resultados);
    fclose(correções);

    return resultado;

}

void batche(DATA d, char *pathI, char *pathP) {
    FILE *inputFile;
    inputFile = fopen (pathI,"r");

    int i = 0, t;
    long inicio, fim;
    double tempo_Exec;

    int resultado;

    char str[200], param1[20], param2[20], param3[20], path[50], pathC[50];
    
    while (fgets(str, 200, inputFile)) {
        t = strlen(str)-1;
        if(str[t] == '\n') str[t] = '\0';
        i++;
        sprintf(path,"./Resultados/command%d_output.txt", i);
        sprintf(pathC,"%s/command%d_output.txt",pathP, i);
        switch (str[0]) {
            case '1':

                        printf("\n\t      -- 1 --");

                    inicio = clock();
                        bQuery1 (d, &str[2], path);
                    fim = clock();
                    tempo_Exec = timer(inicio, fim);
                    printf("\n| Query 1 demorou %lf segundos", tempo_Exec);

                    /// printf("\n%s\n",path);

                    resultado = comparaResultados(path, pathC);

                    /// printf("\n%s\n", pathC);

                break;
            case '2':

                        printf("\n\t      -- 2 --");

                    inicio = clock();
                        bQuery2 (d, atoi(&str[2]), path);
                    fim = clock();
                    tempo_Exec = timer(inicio, fim);
                    printf("\n| Query 2 demorou %lf segundos", tempo_Exec);

                    resultado = comparaResultados(path, pathC);

                break;
            case '3':

                        printf("\n\t      -- 3 --");
                
                    inicio = clock();
                        bQuery3 (d, atoi(&str[2]), path);
                    fim = clock();
                    tempo_Exec = timer(inicio, fim);
                    printf("\n| Query 3 demorou %lf segundos", tempo_Exec);

                    resultado = comparaResultados(path, pathC);

                break; 
            case '4':

                        printf("\n\t      -- 4 --");
                    
                    inicio = clock();
                        bQuery4(d, &str[2], path);
                    fim = clock();
                    tempo_Exec = timer(inicio, fim);
                    printf("\n| Query 4 demorou %lf segundos", tempo_Exec);

                    resultado = comparaResultados(path, pathC);

                break; 
            case '5':
            
                        printf("\n\t      -- 5 --");
                    
                        sscanf(&str[2], "%s %s", param1, param2);
                    inicio = clock();
                        bQuery5(d, convDataToDias(param1), convDataToDias(param2), path);
                    fim = clock();
                    tempo_Exec = timer(inicio, fim);
                    printf("\n| Query 5 demorou %lf segundos", tempo_Exec);

                    resultado = comparaResultados(path, pathC);

                break; 
            case '6':

                        printf("\n\t      -- 6 --");

                        sscanf(&str[2], "%s %s %s", param1, param2, param3);
                    inicio = clock();
                        bQuery6(d, param1, convDataToDias(param2), convDataToDias(param3), path);
                    fim = clock();
                    tempo_Exec = timer(inicio, fim);
                    printf("\n| Query 6 demorou %lf segundos", tempo_Exec);

                    resultado = comparaResultados(path, pathC);

                break; 
            case '7':

                        printf("\n\t      -- 7 --");
                    
                        sscanf(&str[2], "%s %s", param1, param2);
                    inicio = clock();
                        bQuery7(d, atoi(param1) , param2, path);
                    fim = clock();
                    tempo_Exec = timer(inicio, fim);
                    printf("\n| Query 7 demorou %lf segundos", tempo_Exec);

                    resultado = comparaResultados(path, pathC);

                break; 
            case '8':

                        printf("\n\t      -- 8 --");
                
                        sscanf(&str[2], "%s %s", param1, param2);
                    inicio = clock();
                        bQuery8(d, param1[0], atoi(param2), path);
                    fim = clock();
                    tempo_Exec = timer(inicio, fim);
                    printf("\n| Query 8 demorou %lf segundos", tempo_Exec);

                    resultado = comparaResultados(path, pathC);

                break; 
            case '9':

                        printf("\n\t      -- 9 --");
                
                        sscanf(&str[2], "%s %s", param1, param2);
                    inicio = clock();
                        bQuery9(d, convDataToDias(param1), convDataToDias(param2), path);
                    fim = clock();
                    tempo_Exec = timer(inicio, fim);
                    printf("\n| Query 9 demorou %lf segundos", tempo_Exec);

                    resultado = comparaResultados(path, pathC);

                break; 
        }
    }

    fclose(inputFile);
}

