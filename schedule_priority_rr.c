#include<stdio.h>
#include<stdlib.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
struct node* lista;

struct task* buscarMasPrioritario(struct node* lista);
void roundRobin(struct node** lista);
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
	// Voltear la lista
	while(temp != NULL) {
		delete(&lista,temp->task);
		insert(&lista,temp->task);
		temp = temp->next;
	}
	temp = lista;
	struct task* priori;
	int prioridadActual,pSig;
	struct node* listaPrioridad;
	while(lista != NULL) {
		priori = buscarMasPrioritario(lista);
		prioridadActual = priori->priority;
		if(listaPrioridad == NULL) {
			do {
				insert(&listaPrioridad,priori);
				delete(&lista,priori);
				if(lista == NULL) break;
				priori = buscarMasPrioritario(lista);
				pSig = priori->priority;
			}
			while(prioridadActual == pSig);
		}
		roundRobin(&listaPrioridad);
	}
}

void roundRobin(struct node** listap) {
	int quantum = 10,tiempo;
	struct node* temp = *listap;
	struct task* elemTemp;
	while(temp != NULL) {
		tiempo = temp->task->burst < quantum ? temp->task->burst : quantum;
		run(temp->task,tiempo);
		temp->task->burst -= tiempo;
		if(temp->task->burst <= 0) {
			elemTemp = temp->task;
			delete(listap,temp->task);
			free(elemTemp);
		}
		if(temp->next == NULL && listap != NULL) {
			 temp = *listap;
		}
		else {
			temp = temp->next;
		}
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
