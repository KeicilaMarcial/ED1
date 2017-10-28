#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"

int main (){
lista *logs = inicializa();
int opcao,a,b,c;
char ip[15],data[255],mes[255], ano[255], hora[255], min[255] ,seg[255],usuario[255], metodo [255], caminho[255], http[255], status[255], status2[255], agente[255], teste[255];
long bytes;
FILE *arq = fopen("testelogs.txt","r");
int resp=0;
while(resp!=7){
 printf("1-Caregar logs\n2-Quantidade de Logs\n3-Buscar\n4-Excluir\n5-Quantidade de IPs Repetidos\n6-Periodo de maior utilizacaoo da rede\n7-SAIR\n");
 scanf("%d", &resp);

     switch(resp){
            case 1:
                if(arq==NULL){
                    printf("Nao foi possivel abrir arquivo");
                }else{
                        printf("Arquivo carregado!\n");
                    while(!feof(arq)){  // "!feof" enquanto nao chegar no fim do arquivo

                         fscanf(arq, "%s %s %s %s %s",ip,usuario,metodo,data,caminho);

                        printf("\nIP: %s \nUSUARIO: %s\nMETODO: %s \nDAta: %s\nCAMINHO: %s\n",ip,usuario,metodo,data,caminho);
                        logs = insere(logs, criano(ip,usuario,metodo,data,caminho));
                        fgets(teste,255,arq);

                    }
                }
            break;
            case 2:
                 mostrarqntdelogs(logs);
                 printf("\n");
            break;
            case 3:
                 printf("Buscar");
            break;
            case 4:
                 printf("Exluir");
            break;
            case 5:
                printf("quantidade");
            break;
             case 6:
                printf("pico");
                break;
            default:
                break;
            }
    }
	//exibe(logs);
	//mostrarqntdelogs(logs);

	return 0;
}
