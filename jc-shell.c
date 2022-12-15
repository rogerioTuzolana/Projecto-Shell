#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "list.h"
#include "Ficheiro.h"
#include "commandlinereader.h"

#define MAXPAR 1

void *tarefa_monitora();
void imprimir_dados(list_t *list, int pid);
void ler_dados();
void ler_comado(char *buf);




int num_filho = 0,finalizar = 0;
pthread_t tid;
pthread_mutex_t mutex;
pthread_cond_t cond, cond_1;


//lista de dados
list_t *list;
list_pid *list_p;



int main(int argc, char **argv){

	

	char *args[7],buffer[100],fileps[50];
	int filed_p;
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_cond_init(&cond_1, NULL);

	/* initialize list */
  	list = lst_new();
	list_p = lst_new_pid();  

	  /* ler dados guardados */
		ler_dados();

	/* crear pipe */
	
	   mkfifo("jcshell-in",0777);
	  
	
	if(pthread_create(&tid,NULL,tarefa_monitora,NULL) != 0){
		printf("ERROR to CREATE PTHREAD");
		exit(EXIT_FAILURE);
	}else{
	
		while(1){
				
				filed_p= open("jcshell-in",O_RDONLY);
				read(filed_p,buffer,sizeof(buffer));

     			readLineArguments(args,7, buffer); 
				 printf(" \nROGERIO  %s \n\n ",args[0]);
				// sleep(200);
	                                                                                                                    
				close(filed_p);

				if(args[0] == NULL){
					printf(" \nComando invalido <Argumento NULL> \n\n ");

				}else if(strcmp(args[1],"pid") == 0){
					printf(" \nROGERIO PID: %s \n\n ",args[0]);

					insert_new_pid(list_p, args[0]);

					//continue;

				}else{
				
					if(strcmp(args[0],"exit-global") == 0 ){
						
						finalizar = 1;
						pthread_cond_signal(&cond_1);
						pthread_join(tid,NULL);

						fclose(arq1); // FECHAR FICHEIRO
						//close(filed_p);

						lst_destroy(list);
						lst_pid_destroy(list_p);
						pthread_mutex_destroy(&mutex);
						pthread_cond_destroy(&cond);
						pthread_cond_destroy(&cond_1);
						unlink("jcshell-in");

						exit(EXIT_SUCCESS);
					
		    		}else{
							//............................ ZONA CRITICA DO var de cond ESPERAR.............................................................
							pthread_mutex_lock(&mutex);	
							while(num_filho == MAXPAR) pthread_cond_wait(&cond, &mutex);
							pthread_mutex_unlock(&mutex);
							//............................ ........ZONA CRITICA .............................................................
							int pid, filed;
							pid = fork();
							
							if(pid == 0){
							
								sprintf(fileps,"jcshell-out-%d.txt",getpid());
								filed = open(fileps,O_CREAT | O_RDWR,S_IWUSR | S_IRUSR);
								dup2(filed,STDOUT_FILENO);

								if(execv(args[0], args) == -1){
									printf("Process pid <%d> Programa inexistente\n\n",getpid());
									close(filed);
								
									exit(EXIT_FAILURE);
								}

							}else if(pid == -1){

								printf(" erro no fork \n");
								exit(EXIT_FAILURE);
						
						 	 }else if(pid > 0){
							  
//............................ ZONA CRITICA DO PROCESSO PAI.............................................................
								pthread_mutex_lock(&mutex);	
								insert_new_process(list, pid , time(NULL)); 
								num_pross_exce = ++num_filho;
								pthread_cond_signal(&cond_1);
								pthread_mutex_unlock(&mutex);
									
//............................fim zona critica..........................................................................
		
								continue;
							}
						}
					}	
				}
			}
	return 0;
}



///......................... FUNCAO TAREFA MONITORA .....................................
void *tarefa_monitora(){
	int pid_filho, status;

 while(1){
//............................ ZONA CRITICA ESPERA ATIVA.............................................................

	pthread_mutex_lock(&mutex);
	 if(num_filho == 0){
		 if(finalizar == 1){
			pthread_mutex_unlock(&mutex);
			pthread_exit(NULL);
		}
	 			while(num_filho == 0 && finalizar == 0)pthread_cond_wait(&cond_1, &mutex);
				pthread_mutex_unlock(&mutex);
		
		continue;
	}else{		
	pthread_mutex_unlock(&mutex);
	//............................  .............................................................


				pid_filho = wait(&status); // ESPERA PS FILHO TERMINA

//............................ ZONA CRITICA DA TAREFA MONITORA.............................................................
			pthread_mutex_lock(&mutex);
				
				update_terminated_process(list, pid_filho, time(NULL));
				imprimir_dados(list, pid_filho);
				lst_print(list,pid_filho);
			
				num_pross_exce=--num_filho;
			pthread_cond_signal(&cond); // ASSINALAR PARA DEIXAR DE ESPERA
			pthread_mutex_unlock(&mutex);
			
			
			
			continue;
//............................fim zona critica..........................................................................
		}
		
	
		}
	}

void *tarefa_monitora2(){



while(1){




}






}
