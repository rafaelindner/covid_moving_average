#include <stdio.h>
#include <string.h>

#include "rafael.h"


float mediamv(int * vetor, int index){
	/* Funcao para calcular a media movel*/
    int soma=0;
    float media;
	int i;
    for(i=index; i<index+7; i++){
        soma = soma + vetor[i];
    }
    media = (float)soma/7;
    return media;
}

int compare(char str1[], char str2[]){
	/* Compara duas strings. Se ambas forem iguais, retorna 0. Se nao, retorna -1*/
    int i=0;
    while(str1[i] == str2[i]){
          if(str1[i]=='\0'){ return 0;}
          i=i+1;
    }
    return -1; 
}

float variacao(float * mediaMovel, int index, int prazo){
	/* Calcula a variacao dado um certo prazo. */
    return mediaMovel[index+prazo-1]/mediaMovel[index];
}

void forRecursivo(int index, int max, int * vetor, char datas[][6]){
	/* Isso eh um 'for loop' utilizando recursao. Ele imprime os dados de um vetor escolhido
	('casos' ou 'obitos') e as datas. */
    printf("%s\t\t\t%d\n", datas[index], vetor [index]);
    if (index<=max-1){
   forRecursivo(index+1, max, vetor, datas);
}
}

void imprimeResultados(int * vetor, char * opcao, int linhas, char datas[][6]){
	/* Essa eh a funcao que mostra os dados e calculos do programa.
	Ela mostra as datas e os valores para cada tipo de dado (casos ou obitos), utilizando a
	'forRecursivo'.
	Depois, calcula e imprime os valores de mediaMovel.
	Apos isso, calcula e imprime os valores de variacaoo entre as datas, utilizando um intervalo 
	padrao de 14 dias (ver referencias) */
	int i;
	float mediaMovel[linhas-6], variacaoVet[linhas-6-13];
	printf("#-------------------------------------------------------------------------------#\n");
	printf("|\tApresentando os resultados sobre os %s entre os dias %s e %s: |\n", opcao, datas[0], datas[linhas-1]);
	printf("#-------------------------------------------------------------------------------#\n\n");
	printf("Dia:\t\t\t%s:\n", opcao);
	forRecursivo(0, linhas-1, vetor, datas);
	printf("\n-------------------------------------------------------------------\n");
	printf("Intervalo:\t\tMedia movel:\n");
	for(i=0; i<linhas-6; i++){
		mediaMovel[i] = mediamv(vetor, i);
		printf("%s~%s\t\t%.2f\n", datas[i], datas[i+6], mediaMovel[i]);
	}
	printf("\n-------------------------------------------------------------------\n");
	printf("Intervalo:\t\tVariacao:\n");
	for(i=0; i<linhas-6-13; i++){
		variacaoVet[i] = variacao(mediaMovel, i, 14);
		printf("%s~%s \t\t%.2f%%\n", datas[i], datas[i+13], (variacaoVet[i]-1)*100);
	}
}


int countLines(char * filename){

	/* Conta quantas linhas o arquivo de dados tem (excluindo o cabecalho)
	para saber quanto alocar para os vetores */

	FILE* f = fopen(filename, "r");

	int counter=0;

	// Aloca 3 variaveis para poder jogar fora o cabecalho do arquivo.
	
	char * dump1 = (char *) malloc(50*sizeof(char));
	char * dump2 = (char *) malloc(50*sizeof(char));
	char * dump3 = (char *) malloc(50*sizeof(char));

	fscanf(f, "%s %s %s", dump1, dump2, dump3); // Coloca os valores lidos do cabecalho nas variaveis

	// Libera a memoria dessas variaveis
	free(dump1);
	free(dump2);
	free(dump3);

	// Alocamos memoria para variaveis 'temporarias'
	char * data = (char *) malloc(50*sizeof(char));
	int * caso = malloc(sizeof(int));
	int * obito = malloc(sizeof(int));

	while(fscanf(f, "%s%d%d", data, caso, obito)!=EOF){
		counter=counter+1;
	}

	// Liberamos a memoria de todas as variaveis temporarias
	free(data);
	free(caso);
	free(obito);

	return counter;
}

void populaVetores(int * casos, int * obitos, char datas[][6], char * filename){

	char dia[6]; // Variavel temporaria

	// Crio ponteiro pro arquivo, e abro ele para leitura
	FILE* file;
	file = fopen(filename, "r");
	if(file==NULL){
		printf("Esse arquivo não existe\n");
		exit(1);
	}

	// Crio as 3 variaveis 'dump' para o cabecalho, novamente.
	char *dump1 = (char*) malloc(50*sizeof(char)+1);
	char *dump2 = (char*) malloc(50*sizeof(char)+1);
	char *dump3 = (char*) malloc(50*sizeof(char)+1);

	fscanf(file, "%s %s %s", dump1, dump2, dump3);

	free(dump1);
	free(dump2);
	free(dump3);

	// Populo os vetores com datas, casos e obitos.
	int i=0;
	while( fscanf(file, "%s %d %d", dia, casos+i, obitos+i) != EOF ){
		strcpy(datas[i], dia); 
		i = i+1; 
	}
}

void imprimeDiaEspecifico(int * casos, int * obitos, char datas[][6], char dia[], int linhas){
	// Funcao que escolhe um dia especifico para declarar os dados
	int i=0;
	for(i=0; i<linhas; i++){
		if(compare(datas[i], dia)==0){
			printf("\nOs dados do dia %s sao:\n", dia);
			printf("Casos: %d\tObitos: %d\n", casos[i], obitos[i]);
		}
	}
}




