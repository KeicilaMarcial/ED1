#include <stdio.h>
#include <stdlib.h>

int main(){
    char ip[20], usuario[20],dia[3], mes[5],ano[5],metodo[255],path[255],http[255],status[255],agente[255];
    int hora,min,seg;
    long bytes;
    FILE *arq = fopen("testelogs.txt","r");
    if(arq==NULL)             printf("Nao foi possivel abrir arquivo");
    else{
        printf("Arquivo carregado!\n");
            while(!feof(arq)){  // "!feof" enquanto nao chegar no fim do arquivo




            fscanf(arq,"%s %s %[-^]*s %[^\n]s %[^:]s %*d %*d %*d %*s %*s %*s %*d %ld %[^\n]s",ip,usuario,dia,mes,ano,hora,min,seg,metodo,path,http,status,
                                                                   bytes, agente);


             printf(" %s\n %s\n %s\n %s\n %s\n %d\n %d\n %d\n %s\n %s\n %s\n %d\n %ld\n %s\n",ip,usuario,dia,mes,ano,hora,min,seg,metodo,path,http,status,
                                                                   bytes, agente);

            //fgets(teste,255,arq);
            }
    }
    return 0;
}
