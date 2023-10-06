#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

#include "datastruc.h"
#include "loadfiles.h"
#include "query.h"
#include "batch.h"

#include "func.h"

int main(int argc, char *argv[]) {  //// argv[3] --> resultados para comparar

    DATA d = load(argv[1]);


    batche(d, argv[2], argv[3]); // enviar os testes

    struct rusage memoria;
    getrusage(RUSAGE_SELF, &memoria);
                           
    printf("\n\t      -------");
      
    printf("\n| A memória total utilizada é de %ld bytes", memoria.ru_maxrss);

    /// printf("\n\t       -End-  \n");

    cleanStruct(d);
    return 0; 
    
}
