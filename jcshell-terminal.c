#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <locale.h>
#include "Ficheiro.h"



int main(int argc, char **argv){


	char buffer[80];
    int filed;
    
    filed = open(argv[1], O_WRONLY);

    sprintf(buffer,"%d",getpid());
    strcat(buffer," pid");
    write(filed,buffer,80);

	
	
		while(1){
            printf("\n Insert commands$ >:");
            fflush(stdin);

            fgets(buffer,80,stdin);
            fflush(stdin);

            if(strcmp(buffer,"exit\n") == 0){
                close(filed);
                exit(EXIT_SUCCESS);

            }else if(strcmp(buffer,"stats\n") == 0){
                ler_dados();
                
                printf("\nNum_Pross_exec: %d\n",num_pross_exce);
                printf("Total_time_Process: %d\n",t_total);

                continue;

            }else{

            
             if(write(filed,buffer,80) == -1){
                        printf(" erro na ecrita\n");

             }
            }

        }
       
return 0;
}