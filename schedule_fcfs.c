#include<stdio.h>
#include<stdlib.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
struct node* lista;

void add(char* name, int priority, int burst) {
	struct task* proceso;
	proceso = (struct task*) malloc(sizeof(struct task));
	proceso->name = name;
	proceso->priority = priority;
	proceso->burst = burst;
	insert(&lista,proceso);	
}

void schedule() {
	struct node* temp;
	struct task* proceso;
	temp = lista;
	// Voltear lista.
	while(temp != NULL) {
		proceso = temp->task;
		delete(&lista,temp->task);
		insert(&lista,proceso);
		temp = temp->next;
	}
	temp = lista;
	while(temp != NULL) {
		run(temp->task,temp->task->burst);
		free(temp->task);	
		temp = temp->next;
	}
}
