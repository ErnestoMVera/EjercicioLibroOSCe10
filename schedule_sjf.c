#include<stdio.h>
#include<stdlib.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
struct node* lista;

struct task* buscarMasCorto(struct node* lista);
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
	struct task* corto;
	while(temp != NULL) {
		corto = buscarMasCorto(temp);
		run(corto,corto->burst);
		delete(&temp,corto);
	}
}

struct task* buscarMasCorto(struct node* lista) {
	struct node *temp = lista;
	struct task *corto = temp->task;
	while(temp != NULL) {
		if(temp->task->burst < corto->burst) {
			corto = temp->task;
		}
		temp = temp->next;
	}
	return corto;
}
