#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no{
	char ip[40];
	char usuario[255];
	char data[255];
	char metodo [255];
	char caminho[255];
	char http[255];
	char status[255];
	long bytes;
	char agente[255];
	struct no *prox;
	struct no *ant;
}no;

typedef struct lista{
	struct no *inicio;
	struct no *fim;
	int qnt;
}lista;

//inicializa uma lista vazia e retorna a lista vazia
lista *inicializa(){
	lista *nova = (lista*)malloc(sizeof(lista));
	nova->inicio = NULL;
	nova->fim = NULL;
	nova->qnt = 0;
	return nova;
}

// cria um no qe recebe como parametro as informacoes e retorna o no
no *criano(char ip[255], char usuario[255], char metodo[255],char data[255], char caminho[255]){

	no *novo = (no*)malloc(sizeof(no));
	if(novo!=NULL){
		strcpy(novo-> ip,ip);
		strcpy(novo-> usuario,usuario);
		strcpy(novo-> data,data);
		strcpy(novo-> metodo,metodo);
		strcpy(novo-> caminho,caminho);
		novo->ant=NULL;
		novo->prox=NULL;
	}
	return novo;
}

// add(no fim) o no criado na lista e retorna a lista atualizada
lista *insere(lista *l, no *novo){  //recebe como parametro a lista e no já alocado
	if(l->fim==NULL){  //sabemos que a lista esta vazia se nao possuir nenhum elemento
		l->inicio = novo;
		l->fim = novo;
	}else{  //se a lista nao estiver vazia vamos add no final, como temos referencia para o fim..
		l->fim->prox = novo;
		novo->ant=l->fim;
		l->fim = novo;
	}
	l->qnt++; //como de qualquer jeito vai add coloquei para somar fora das condições
	return l;
}

void mostrarqntdelogs(lista *l){
	if(l==NULL) printf("\n Lista vazia!\n");
	else{
		printf("\nPossuui %d logs.\n",l->qnt);
	}
}

void exibe(lista *l){
    int i=0;
	no *aux=l->fim;
	if(aux==NULL) printf("\n Lista vazia!\n");

	else{
		printf("------------------------------------Lista-----------------------------------");
		while(i<(l->qnt)){
			printf("\nIP: %s \nUSUARIO: %s\nMETODO: %s \nDAta: %s\nCAMINHO: %s\n",aux->ip,aux->usuario,aux->metodo,
			aux->data,aux->caminho);
			aux = aux->ant;
            i++;
		}

	}
}







