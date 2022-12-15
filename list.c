/*
 * list.c - implementation of the integer list functions 
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "list.h"


list_pid* lst_new_pid(){
   list_pid *list;
   list = (list_pid*) malloc(sizeof(list_pid));
   list->first = NULL;
   return list;
}

void lst_pid_destroy(list_pid *list){

	struct lst_pid *item, *nextitem;

	item = list->first;
	while (item != NULL){
		nextitem = item->next;
		free(item);
		item = nextitem;
	}
	free(list);
}

void insert_new_pid(list_pid *list, char *pidc){
	lst_pid *item;
	int pid = atoi(pidc);

	item = (lst_pid*) malloc (sizeof(lst_pid));
	item->pid = pid;
	item->next = list->first;
	list->first = item;
}



/// ******************** PROCESSOS  FUNCOES **************


list_t* lst_new()
{
   list_t *list;
   list = (list_t*) malloc(sizeof(list_t));
   list->first = NULL;
   return list;
}


void lst_destroy(list_t *list)
{
	struct lst_iitem *item, *nextitem;

	item = list->first;
	while (item != NULL){
		nextitem = item->next;
		free(item);
		item = nextitem;
	}
	free(list);
}


void insert_new_process(list_t *list, int pid, time_t starttime)
{
	lst_iitem_t *item;

	item = (lst_iitem_t *) malloc (sizeof(lst_iitem_t));
	item->pid = pid;
	item->starttime = starttime;
	item->endtime = 0;
	item->r_time = 0;
	item->total_time = 0;
	item->next = list->first;
	list->first = item;
}


void update_terminated_process(list_t *list, int pid, time_t endtime)
{
	if(list->first == NULL) return;
	lst_iitem_t *aux1,*aux = list->first;
	aux1 = aux;
	while(aux != NULL){
		if(pid == aux->pid){
			aux->endtime = endtime;
			aux->r_time = aux->endtime - aux->starttime;

			while(aux1 != NULL){
				aux->total_time += aux1->r_time;
				aux1 = aux1->next;
			}

			return;	
		}
		
		aux = aux->next;
	}
	

   //printf("teminated process with pid: %d\n", pid);
}


void lst_print(list_t *list, int pid)
{
	lst_iitem_t *item;

	//printf("Process list with start and end time:\n");
	item = list->first;

	while (item != NULL){
		if(item->pid == pid){
			printf("Iteracao: %d\n", item->num_iteracao);	
			printf("Process : %d\t Run Time: %d seg\n", item->pid, item->r_time);	
			printf("Tempo total de exec: %d s\n\n",item->total_time);
		}
		item = item->next;
	}
	//printf("-- end of list.\n");
}





