#ifndef FICHEIRO_H_INCLUDED
#define FICHEIRO_H_INCLUDED
#include "list.h"
#include <unistd.h>

FILE *arq1;
int iteracao = -1, t_total = 0, num_pross_exce ;



//............................ FUNCAO PARA IMPRIMIR DADOS .............................................................

void imprimir_dados(list_t *list, int pid){
     arq1 = fopen("log.txt", "ab");
    if(arq1 == NULL){
     printf("\nErro: Nao foi possivel abrir o arquivo para imprimir\n");
     return;
    }
        lst_iitem_t *aux = list->first;

        while(aux != NULL ){
            if(pid == aux->pid){
                aux->num_iteracao = ++iteracao;
                if(t_total > 0){
                    aux->total_time += t_total;
                }
                
                fprintf(arq1, "iteracao %d\n",aux->num_iteracao);
                fprintf(arq1, "pid: %d exec time: %d s \n",aux->pid,aux->r_time);
                fprintf(arq1, "total exec time: %d s\n",aux->total_time);
                fclose(arq1);
               
                return;
            }            
            aux = aux->next;

        }
        
        

}


//............................ FUNCAO PARA LER DADOS .............................................................

void ler_dados(){

    arq1 = fopen("log.txt", "rt");
    if(arq1 == NULL){
       fopen("log.txt", "ab");
        return;
    }
 char linha[100];
    char *result;
    int i, j;

       while(!feof(arq1)){

           for(i=0;i<3;i++){

               fgets(linha, 100, arq1);

                   if(i== 0){
                       
                       result = strtok(linha," ");
                       result = strtok(NULL," ");
                       if(result != NULL)
                            iteracao = atoi(result);
                   }else if(i==1){
                       continue;
                   }else{
                       result = strtok(linha," ");
                        for(j=0; j<3;j++)
                        result = strtok(NULL," ");
                        if(result != NULL)
                            t_total= atoi(result);

                   } 

           }       
       }
       
       fclose(arq1);
       
}






#endif // FICHEIRO_H_INCLUDED