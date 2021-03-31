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
	struct node* temp = lista;
	int quantum = 10,tiempo;
	struct task* elemTemp;
	// Voltear la lista
	while(temp != NULL) {
		delete(&lista,temp->task);
		insert(&lista,temp->task);
		temp = temp->next;
	}
	temp = lista;
	while(temp != NULL) {
		tiempo = temp->task->burst < quantum ? temp->task->burst : quantum;
		run(temp->task,tiempo);
		temp->task->burst -= tiempo; 
		if(temp->task->burst <= 0) {
			elemTemp = temp->task;
			delete(&lista,temp->task);
			free(elemTemp);
		}
		if(temp->next == NULL && lista != NULL) {
			temp = lista;
		}
		else {
			temp = temp->next;
		}
	}
}
