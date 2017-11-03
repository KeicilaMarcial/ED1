#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no{
	char ip[40];
	char usuario[255];
	char data[255];
	int hora;
	int dia;
	char mes[5];
	int ano;
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

typedef struct r{
    char ip;
    int qnt;
    struct r *prox;
}r;


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
    return u+d;
}

int milagre2(char *data){
    int u,d;
    u = (data[0]-48) * 10;
    d = (data[1]-48);
    return u+d;
}

int milagre3(char *data){
    int um,c,u,d;
    um =(data[7]-48) * 1000;
    c = (data[8]-48) * 100;
    u = (data[9]-48) * 10;
    d = (data[10]-48);
    return um+c+u+d;
}

char *milagre4(char *data){
    char *mes;
    mes = (char*)malloc(3*sizeof(char));
    mes[0] = data[3];
    mes[1] = data[4];
    mes[2]= data[5];
   // mes[3] = '\n';
    return mes;
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
		novo->status = status;
		novo->bytes = bytes;
		novo->hora = milagre(data);
		novo->dia = milagre2(data);
		novo->ano = milagre3(data);
		strcpy(novo->mes,milagre4(data));
		novo->ant = NULL;
		novo->prox = NULL;
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

int verificalistavazia(lista *l){
    if(l->qnt!=0)        return 1; // se ==1 lista esta vazia
    else return 0; // se ==0 lista NAO esta vazia
}

lista *desaloca(lista *l){
    no* aux=l->inicio;
    while(aux!=NULL){
        l=aux->prox;
        free(aux);
        aux=l;
    }
    return NULL;
}

void mostrarqntdelogs(lista *l){
	if(l==NULL) printf("\n Lista vazia!\n");
	else{
		printf("\nPossuui %d logs.\n",l->qnt);
	}
}

void printarNo(no *aux){
    printf("\nIP: %s    USUARIO: %s   Dia: %d  Mes: %s  Ano: %d    Hora:%d     Metodo: %s   Caminho: %s   http: %s\nStatus: %d   Bytes: %ld    Agente: %s\n",
                       aux->ip,aux->usuario,aux->dia,aux->mes,aux->ano,aux->hora,aux->metodo,aux->caminho,aux->http,aux->status,aux->bytes,aux->agente);
}

void exibelista(lista *l){
    int i;
	no *aux;
	if(l->qnt==0) printf("\n Lista vazia!\n");
	else{
		printf("------------------------------------Lista-----------------------------------");
		for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                    printarNo(aux);
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

r *inicializar(){
	r *nova = (r*)malloc(sizeof(r));
	nova = NULL;
	return nova;
}

r *inserer(r* l, char *ip){
    r *novo = (r*)malloc(sizeof(r));
    novo->qnt=0;
    strcmp(novo->ip,ip);

    novo->prox =l;
    return novo;
}

void exiber(r *l){
    r *aux;
    while(aux!=NULL){
        printf("\nIP: %s         Repetições: %d",aux->ip,aux->qnt);
        aux=aux->prox;
    }
}

lista *removerepetido(lista*l,no*r){
    if(r->prox!=NULL){
        r->ant->prox=r->prox;
        r->prox->ant= r->ant;
    }else{
        l->fim = r->ant;
        l->fim->prox=NULL;
    }
    return l;
}

void quantIpsRepeditos(lista *l){
    if(l->inicio==NULL) printf("Lista vazia");
    else{
        int cont;
        lista *aux;
        aux = l;
        no*aux1, *aux2, *aux3=l->fim;
        for(aux1=aux->inicio;aux1!=NULL;aux1=aux1->prox){
            cont =1;
            for(aux2=aux->fim;aux2!=aux1;aux2=aux3){
                aux3=aux2->ant;
                if (strcmp(aux1->ip,aux2->ip)==0){
                    aux= removerepetido(aux,aux2);
                    cont ++;
                }
            }
            printf("\nIP: %s Repeticaos %d",aux1->ip,cont);
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

void buscaTipoChar(lista *l, int opcao, char busca[255]){
        no *aux;
        int cont=0;
        switch(opcao){
        case 1:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                 if(strcmp (aux->ip,busca)==0){
                        cont ++;
                        printarNo(aux);
                 }
            }

        break;
        case 2:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                 if(strcmp (aux->usuario,busca)==0){
                        printarNo(aux);
                        cont ++;
                 }
            }
        break;
        case 3:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                 if(strcmp (aux->metodo,busca)==0){
                        printarNo(aux);
                        cont++;
                 }
            }
        break;
        case 4:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                 if(strcmp (aux->caminho,busca)==0){
                        printarNo(aux);
                        cont++;
                 }
            }
        break;
        case 5:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                 if(strcmp (aux->http,busca)==0){
                        printarNo(aux);
                        cont++;
                 }
            }
        break;
        case 6:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                 if(strcmp (aux->agente,busca)==0){
                        printarNo(aux);
                        cont ++;
                 }
            }
        break;
        case 8:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                 if(strcmp(aux->mes,busca)==0){
                        printarNo(aux);
                        cont ++;
                 }
            }
        break;
        }
    if(cont==0) printf("\nNada foi encontrado\n");

}

 void buscaTipoInt(lista *l,int opcao2,int busca){
        no *aux;
        int cont=0;
        switch(opcao2){
        case 1:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                 if(aux->status,busca){
                        cont ++;
                        printarNo(aux);
                 }
            }
        break;
        case 2:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                 if(aux->hora==busca){
                        printarNo(aux);
                        cont ++;
                 }
            }
        break;
        case 3:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                if(aux->dia == busca){
                    printarNo(aux);
                    cont++;
                }
            }
        break;
        case 5:
            for(aux=l->inicio; aux->prox!=NULL; aux=aux->prox){
                if(aux->ano == busca){
                    printarNo(aux);
                    cont++;
                }
            }
        break;
        }
        if(cont==0) printf("\nNada foi encontrado\n");
}


void funcaobusca(lista *l){
    int opcao2;
    char busca[255];

    if(verificalistavazia(l)==1){
                        printf ("\n----------------Buscar---------------- \n");
                        printf ("\n1 - IP \n");
                        printf ("2 - Usuario \n");
                        printf ("3 - Metodo \n");
                        printf ("4 - Caminho(PATH) \n");
                        printf ("5 - HTTP \n");
                        printf ("6 - Agente \n");
                        printf ("7 - Outros \n");
                        printf ("\n-------------------------------------- \n");


                        scanf("%d",&opcao2);
                        switch(opcao2){
                        case 1:
                                system("cls");
                                printf("Inserir IP: ");
                                scanf("%s",&busca);
                                buscaTipoChar(l,opcao2,busca);
                        break;
                        case 2:
                                system("cls");
                                printf("Inserir Usuario: ");
                                fflush(stdin);
                                gets(busca);
                                buscaTipoChar(l,opcao2,busca);
                        break;
                        case 3:
                                system("cls");
                                printf("Inserir Metodo: ");
                                fflush(stdin);
                                gets(busca);
                                buscaTipoChar(l,opcao2,busca);
                        break;
                        case 4:
                                system("cls");
                                printf("Inserir Caminho(Path): ");
                                fflush(stdin);
                                gets(busca);
                                buscaTipoChar(l,opcao2,busca);
                        break;
                        case 5:
                                system("cls");
                                printf("Inserir http: ");
                                fflush(stdin);
                                gets(busca);
                                buscaTipoChar(l,opcao2,busca);
                        break;
                        case 6:
                                system("cls");
                                printf("Inserir Agente: ");
                                fflush(stdin);
                                gets(busca);
                                buscaTipoChar(l,opcao2,busca);
                        break;
                        case 7:
                                system("cls");
                                contopcao0(l);
                        break;

                        }
    }else printf("Lista vazia");
}

 void contopcao0(lista *l){
        no *aux;
        int opcao,busca;
        char busca1[5];
        printf ("\n----------------Buscar---------------- \n");
        printf ("\n1 - Status  \n2 - Hora \n3 - Dia \n4 - Mes \n5 - Ano \n");
        scanf("%d",&opcao);
        switch(opcao){
        case 1:
            printf("Digite Status: ");
            scanf("%d",&busca);
            buscaTipoInt(l,opcao,busca);
        break;
        case 2:
            printf("Digite Hora: ");
            scanf("%d",&busca);
            buscaTipoInt(l,opcao,busca);
        break;
        case 3:
            printf("Digite Dia: ");
            scanf("%d",&busca);
            buscaTipoInt(l,opcao,busca);
        break;
        case 4:
            printf("Digite Mes: ");
            scanf("%s",busca1);
            opcao =8;
            buscaTipoChar(l,opcao,busca1);
        break;
        case 5:
            printf("Digite ano: ");
            scanf("%d",&busca);
            buscaTipoInt(l,opcao,busca);
        break;
        }
 }
