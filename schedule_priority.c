
#include<stdio.h>
#include<stdlib.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
struct node* lista;

struct task* buscarMasPrioritario(struct node* lista);
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
	struct task* prioritario;
	while(temp != NULL) {
		prioritario = buscarMasPrioritario(temp);
		run(prioritario,prioritario->burst);
		delete(&temp,prioritario);
	}
}

struct task* buscarMasPrioritario(struct node* lista) {
	struct node *temp = lista;
	struct task *prioritario = temp->task;
	while(temp != NULL) {
		if(temp->task->priority < prioritario->priority) {
			prioritario = temp->task;
		}
		temp = temp->next;
	}
	return prioritario;
}
