
float mediamv(int *vetor, int index);

int compare(char str1[], char str2[]);

float variacao(float * mediaMovel, int index, int prazo);

void imprimeResultados(int * vetor, char * opcao, int linhas, char datas[][6]);

void forRecursivo(int index, int max, int * vetor, char datas[][6]);

int countLines(char * filename);

void populaVetores(int * casos, int * obitos, char datas[][6], char * filename);

void imprimeDiaEspecifico(int * casos, int * obitos, char datas[][6], char dia[], int linhas);
