#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no{
	char ip[40];
	char usuario[255];
	char data[255];
	int hora;
	char metodo [255];
	char caminho[255];
	char http[255];
	int status;
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
//MILAGREEEEE
int milagre(char *data){
    int u,d,hora;
    u = (data[12]-48) * 10;
    d = (data[13]-48);
    hora= u+d;
    return hora;
}

// cria um no qe recebe como parametro as informacoes e retorna o no
no *criano(char ip[20], char usuario[20], char data[255], char metodo[255], char caminho[255], char http[255], int status, long bytes, char agente[255]){

	no *novo = (no*)malloc(sizeof(no));
	if(novo!=NULL){
		strcpy(novo-> ip,ip);
		strcpy(novo-> usuario,usuario);
		strcpy(novo-> data,data);
		strcpy(novo-> metodo,metodo);
		strcpy(novo-> caminho,caminho);
		strcpy(novo-> http,http);
		strcpy(novo-> agente,agente);
		novo->status =status;
		novo->bytes = bytes;
		novo->ant=NULL;
		novo->prox=NULL;
		//add a hora
		novo->hora=milagre(data);
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
    int i;
	no *aux;
	if(l->qnt==0) printf("\n Lista vazia!\n");
	else{
		printf("------------------------------------Lista-----------------------------------");
		for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                printf("\nIP: %s    USUARIO: %s   Data: %s    Hora:%d     Metodo: %s   Caminho: %s   http: %s\nStatus: %d   Bytes: %ld    Agente: %s\n",
                       aux->ip,aux->usuario,aux->data,aux->hora,aux->metodo,aux->caminho,aux->http,aux->status,aux->bytes,aux->agente);
		}

	}
}
//---------------------------------------------------buscar-----------------------------------------------------------------------------
//buusca por ip
void buscaIP(lista *l,char ip[15]){//200.135.37.72
    if(l->inicio== NULL) printf("Lista vazia!");
    else{
        no *aux;
        for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                if(strcmp (aux->ip,ip)==0){
                    printf("\nIP: %s    USUARIO: %s   Data: %s    Hora:%d     Metodo: %s   Caminho: %s   http: %s\nStatus: %d   Bytes: %ld    Agente: %s\n",
                       aux->ip,aux->usuario,aux->data,aux->hora,aux->metodo,aux->caminho,aux->http,aux->status,aux->bytes,aux->agente);
                }

        }
    }
}
//Busca Usuario
void buscaUsuario(lista *l,char usuario[15]){//200.135.37.72
    if(l->inicio== NULL) printf("Lista vazia!");
    else{
        no *aux;
        for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                if(strcmp (aux->usuario,usuario)==0){
                    printf("\nIP: %s    USUARIO: %s   Data: %s    Hora:%d     Metodo: %s   Caminho: %s   http: %s\nStatus: %d   Bytes: %ld    Agente: %s\n",
                       aux->ip,aux->usuario,aux->data,aux->hora,aux->metodo,aux->caminho,aux->http,aux->status,aux->bytes,aux->agente);
                }

        }
    }
}

void buscaCaminho(lista *l,char caminho[255]){//200.135.37.72
    if(l->inicio== NULL) printf("Lista vazia!");
    else{
        no *aux;
        for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                if(strcmp (aux->caminho,caminho)==0){
                    printf("\nIP: %s    USUARIO: %s   Data: %s    Hora:%d     Metodo: %s   Caminho: %s   http: %s\nStatus: %d   Bytes: %ld    Agente: %s\n",
                       aux->ip,aux->usuario,aux->data,aux->hora,aux->metodo,aux->caminho,aux->http,aux->status,aux->bytes,aux->agente);
                }

        }
    }
}
//remover um(uns) no(s) da lista por meio do ip
lista* remover(lista *l){
    if(l->inicio==NULL)        return NULL;
    else{
        char id[15];
        printf("Inserir IP: ");
        scanf("%s",&id);
        no *aux = l->inicio;
        do{
            if(strcmp (aux->ip,id)==0){
                if(aux->ant==NULL){
                    l->inicio=aux;
                    l->inicio->ant=NULL;
                }else{
                    aux->ant->prox=aux->prox; //ver para onde ->fim esta apontando
                }
            l->qnt--;
            }
        aux=aux->prox;
        }while(aux!=NULL);
        return l;
    }
}

lista *removerepetido(lista*l,no*r){
    if(r->prox!=NULL){
        r->ant->prox=r->prox;
    }else{
        l->fim = r->ant;
        l->fim->prox=NULL;
    }
    return l;
}
//quuase pronta
void quantIpsRepeditos(lista *l){
    if(l->inicio==NULL) printf("Lista vazia");
    else{
        int cont=2, *vet;
        lista *aux;
        aux = l;
        no*aux1, *aux2;
//fazer uma estrutura para guardar
        for(aux1=aux->inicio;aux1!=NULL;aux1=aux1->prox){
           for(aux2=aux->fim;aux2!=NULL;aux2=aux2->prox){
                if (strcmp(aux1->ip,aux2->ip)==0){
                    aux= removerepetido(aux,aux2);
                    cont++;
                }
            }
        }
    }
}

//funçao que é usada na  fncao fluxodehoario onde percorre o vetor e ver qal o maior elemento
void maiorqntvetor(int*vet){
    int i,maior,posicao,soma;
    float media;
    maior= vet[0];
    posicao=0 ;
    soma=0;

    for(i=1; i<24; i++){
        if(maior< vet[i]){
            maior= vet[i];
            posicao = i;
            soma=soma+vet[i];
        }
    }
    printf("\nO horario de maior fluxo e as %d com %d com total de acesso nesse horario",posicao+1,maior);

}

void horariodefluxo(lista *l){
    int *vet,i;  //vetor de 24 posições pois são 24h
    vet = (int*)calloc(24,sizeof(int));
    no* aux;
    for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
        i= aux->hora;
        vet[i-1]= (vet[i-1])+1;
    }
    for(i=0;i<24;i++){
        printf("%d = %d\n",i+1,vet[i]);
    }
    maiorqntvetor(vet);
}
