#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rafael.c"

// Pesquisa sobre os dados da COVID-19

// Uma pesquisa com intuito de obter dados
// de casos e mortes numa média móvel de
// 7 dias, todas as analises do COVID eram feitas testando variação de 14 dias p avaliar estabilidade.
// fonte: https://g1.globo.com/bemestar/coronavirus/noticia/2020/07/27/entenda-como-e-calculada-a-media-movel-e-a-variacao-dos-casos-e-mortes-por-covid-19.ghtml

// Os dados coletados foram referentes ao dia 01/02/2022 até 28/02/2022, época com os maiores de índices de casos de contaminação do vírus.
// fonte: https://covid.saude.gov.br/


int main() {

	char * filename = "dados.dat"; // Arquivo de dados
	int LINHAS = countLines(filename); // Conta quantas linhas tem no arquivo de dados
	char datas[LINHAS][6];
	int * casos = malloc(LINHAS*sizeof(int)); //Aloca memoria para casos
	int * obitos = malloc(LINHAS*sizeof(int)); //Aloca memoria para obitos

	populaVetores(casos, obitos, datas, filename);

	imprimeResultados(casos, "casos", LINHAS, datas);

	printf("\n\n\n\n\n\n");

	imprimeResultados(obitos, "obitos", LINHAS, datas);

	imprimeDiaEspecifico(casos, obitos, datas, "10/02", LINHAS); // Se mudar a string '05/02' para '20/02', ira imprimir os dados do dia 20/02

	free(casos);
	free(obitos);

	return 0;
}
