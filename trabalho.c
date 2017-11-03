#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"

int main (){

    lista *logs = inicializa();

    char ip[20], usuario[20],data[255],metodo[255],caminho[255],http[255],agente[255],teste[255];
    char nomedoarquivo[255];
    int status,opcao,resp;
    long bytes;

    FILE *arq = fopen("testelogs.txt","r");

    do{
    printf("\n===================Menu====================\n1-Carregar logs\n2-Quantidade de Logs\n3-Buscar\n4-Excluir\n5-Quantidade de IPs Repetidos\n6-Periodo de maior utilizacao da rede\n7-Exibe\n8-SAIR\n===========================================\n");
    scanf("%d", &resp);
    system("cls");
         switch(resp){
                case 1:
                     //printf("Digite nome do arquivo (Ex: aqr.txt)\n: ");
                    //scanf("%s",&nomedoarquivo);
                    if(arq==NULL){
                        printf("Nao foi possivel abrir arquivo");
                    }else{

                            printf("Arquivo carregado!\n");
                        while(!feof(arq)){  // "!feof" enquanto nao chegar no fim do arquivo

                            fscanf(arq, "%s %*s %s [%s %*d] \"%s %s %[^\"]\" %d %ld  %*s \"%[^\"]\"" ,ip,usuario,data,metodo,caminho,http,&status,&bytes,agente);

                           // printf("\nIP: %s \nUSUARIO: %s\nDAta: %s\nMetodo: %s\nCaminho: %s\nhttp: %s\nStatus: %d\nBytes: %ld\nAgente: %s\n",ip,usuario,data,metodo,caminho,http,status,bytes,agente);
                            logs = insere(logs, criano(ip,usuario,data,metodo,caminho,http,status,bytes,agente));
                            fgets(teste,255,arq);

                        }

                    }

                break;

                case 2:
                     mostrarqntdelogs(logs);
                     printf("\n");
                break;

                case 3:
                    funcaobusca(logs);
                break;

                case 4:
                     logs= remover(logs);
                break;

                case 5:
                     quantIpsRepeditos(logs);
                     printf("\n");
                     break;
                break;
                case 6:
                    horariodefluxo(logs);
                    printf("\n");
                break;
                case 7:
                    exibelista(logs);
                    printf("\n");
                break;
                default:
                break;
        }
    }while(resp!=8);
	return 0;
}
