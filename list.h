

/*
 * list.h - definitions and declarations of the integer listt
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

	
 




/* lst_iitem - each element of the list points to the next element */
typedef struct lst_iitem {
   int pid;
   int r_time;
   int total_time;
   int num_iteracao;
   time_t starttime;
   time_t endtime;
   struct lst_iitem *next;
} lst_iitem_t;

/* list_t */
typedef struct {
   lst_iitem_t * first;
} list_t;

/// ******************* PID TERMINAL ********************************

/* lst_pid- each element of the list points to the next element */
typedef struct lst_pid {
   int pid;
   struct lst_pid *next;
} lst_pid;

/* list_t */
typedef struct {
   lst_pid *first;
}list_pid;



/* lst_new - allocates memory for list_t and initializes it */
list_t* lst_new();

/* lst_destroy - free memory of list_t and all its items */
void lst_destroy(list_t *);

/* insert_new_process - insert a new item with process id and its start time in list 'list' */
void insert_new_process(list_t *list, int pid, time_t starttime);

/* update_teminated_process - updates endtime of element with pid 'pid' */
void update_terminated_process(list_t *list, int pid, time_t endtime);

/* lst_print - print the content of list 'list' to standard output */
void lst_print(list_t *list, int pid);


///************************** PID TERMINAL FUNCAO **********************************************

/* lst_new_pid allocates memory for list_t and initializes it */
list_pid* lst_new_pid();

/* lst_destroy_pid free memory of list_t and all its items */
void lst_pid_destroy(list_pid *);

/* insert_new_process_pid- insert a new item with process id and its start time in list 'list' */
void insert_new_pid(list_pid *list, char *pidc);
/* lst_print_pid - print the content of list 'list' to standard output */
void terminal_kill(list_pid *list);


#endif 