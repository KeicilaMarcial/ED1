#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"

int main (){

    lista *logs = inicializa();

    char ip[15], usuario[20],data[255],metodo[255],caminho[255],http[255],agente[255],teste[255];
    char nomedoarquivo[20];
    int status,opcao,resp;
    long bytes;

    FILE *arq ;// = fopen(nomedoarquivo,"r");

    do{
    printf("\n===================Menu====================\n");
    printf("(1)-Carregar logs\n");
    printf("(2)-Quantidade de Logs\n");
    printf("(3)-Buscar\n");
    printf("4-Excluir\n");
    printf("(5)-Quantidade de IPs Repetidos\n");
    printf("(6)-Periodo de maior utilizacao da rede\n");
    printf("(7)-Exibe\n");
    printf("(8)-SAIR\n");
    printf("===========================================\n");
    printf(": ");
    scanf("%d", &resp);
    system("cls");
         switch(resp){
                case 1:
                    printf("Digite nome do arquivo (Ex: aqr.txt)\n: ");
                    fflush(stdin);
                    gets(nomedoarquivo);

                    if( (arq = fopen(nomedoarquivo,"r")) == NULL){
                        printf("Nao foi possivel abrir o arquivo %s.",nomedoarquivo);
                    }else{

                            printf("%s CARREGADO!\n",nomedoarquivo);
                            while(!feof(arq)){  // "!feof" enquanto nao chegar no fim do arquivo

                            fscanf(arq, "%s %*s %s [%s %*d] \"%s %s %[^\"]\" %d %ld  %*s \"%[^\"]\"" ,ip,usuario,data,metodo,caminho,http,&status,&bytes,agente);

                           // printf("\nIP: %s \nUSUARIO: %s\nDAta: %s\nMetodo: %s\nCaminho: %s\nhttp: %s\nStatus: %d\nBytes: %ld\nAgente: %s\n",ip,usuario,data,metodo,caminho,http,status,bytes,agente);
                            logs = insere(logs, criano(ip,usuario,data,metodo,caminho,http,status,bytes,agente));
                            fgets(teste,255,arq);

                        }

                    }
                    logs = tamanhoLDE(logs,nomedoarquivo);

                break;

                case 2:
                    if(verificalistavazia(logs)==1)    mostrarqntdelogs(logs);
                    else           printf("Lista vazia");
                break;

                case 3:
                     if(verificalistavazia(logs)==1)    funcaobusca(logs);
                     else           printf("Lista vazia");
                break;

                case 4:
                    if(verificalistavazia(logs)==1){
                        printf("Inserir IP: ");
                        scanf("%s",&ip);
                        logs= removerchar(logs,ip);
                    }else printf("Lista vazia");
                break;

                case 5:
                     quantIpsRepeditos(logs);
                     printf("\n");
                     break;
                break;
                case 6:
                    if(verificalistavazia(logs)==1)     horariodefluxo(logs);
                    else           printf("Lista vazia");
                break;
                case 7:
                    if(verificalistavazia(logs)==1)     exibelista(logs);
                    else           printf("Lista vazia");
                break;
                default:
                break;
        }
    }while(resp!=8);
    free(logs);
	return 0;
}
