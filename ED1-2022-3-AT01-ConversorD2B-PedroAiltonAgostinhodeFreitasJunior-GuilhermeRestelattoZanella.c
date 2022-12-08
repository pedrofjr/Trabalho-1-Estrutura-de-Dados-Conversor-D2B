//Diretiva de inclusão das bibliotecas necessárias para o programa
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Definição da constante simbólica "TAMANHO" que retorna o valor utilizado
//como tamanho máximo da pilha
#define TAMANHO 8

//Definição da estrutura da pilha
typedef struct{
	//Declaração do vetor para armazenar elementos da pilha
	char vetor[TAMANHO+1];
	//Declaração de chave de identificação dos elementos da pilha
	int key;
} pilhaEst;

//Operação de início da pilha
void iniciar(pilhaEst *p){
	p->key=0;
}

//Operação de checagem se a pilha está vazia
bool vazia(pilhaEst *p){
	return(p->key==0);
}

//Operação de checagem se a pilha está cheia
bool cheia(pilhaEst *p){
	return(p->key==TAMANHO);
}

//Operação que retorna a quantidade de elementos da pilha
int tamanhoPilha(pilhaEst *p){
	return(p->key);
}

//Operação que insere elementos na pilha
void empilhar(pilhaEst *p, char n){
	if(!cheia(p)){
		p->vetor[p->key]=n;
		p->vetor[p->key+1]=0;
		p->key++;
	}
	else{
		printf("Aviso: pilha cheia.");
	}
}

//Operação que remove elementos da pilha
void desempilhar(pilhaEst *p){
	if(!vazia(p)){
		p->vetor[p->key]=0;
		p->key--;
	}
	else{
		printf("Aviso: pilha vazia.");
	}
}

//Operação que retorna elemento do topo da pilha
char topo(pilhaEst *p){
	return(p->vetor[p->key-1]);
}

//Função de conversão de números decimais em binário
int binario(int n){
	//Declarar pilha 1 e 2
	pilhaEst pilhaBin1, pilhaBin2;
	//Iniciar pilha 1 e 2
	iniciar(&pilhaBin1);
	iniciar(&pilhaBin2);
    //Se o número for igual a 1 ou 0, guardar o próprio valor na string de armazenamento
    if(n==1 || n==0){
    	//Converter inteiro para char e empilhar na pilha 1
        empilhar(&pilhaBin1, n+'0');
    }
    else{
    	//Laço de repetição para realizar operação de conversão
    	do{
    		//Armazenar na pilha o resto da divisão por 2 e converter para char
    	    empilhar(&pilhaBin1, n%2+'0');
    	    //Dividir n para próxima execução do laço
    	    n=n/2;
    	    //Se o resultado da divisão for igual a 1, empilhar na pilha 1,
    	    //pois é a última execução
    	    if(n==1){
    	        empilhar(&pilhaBin1, n+'0');
    	    }
    	//Condição do laço, pois o último valor do cálculo de um binário é 1
    	} while(n!=1); 
    }
    //Declarar ponteiro para puxar valores da pilha como string
	pilhaEst *pbin2=&pilhaBin2;
	//Declarar variável para armazenar valor da pilha 1 antes de desempilhar no laço
	int tamanho=tamanhoPilha(&pilhaBin1);
	//Laço para inverter os valores do binário, empilhando os caracteres
	//da pilha 1 na pilha 2
	for(int i=0; i<tamanho; i++){
		empilhar(&pilhaBin2, topo(&pilhaBin1));
	    desempilhar(&pilhaBin1);
	}
	//Retornar resultado da função atoi(que converte string em inteiro) na string da pilha 2
	return atoi(pbin2->vetor);
}

//Função main do programa
int main(int argc, const char *argv[]){
	//Verificação do argc
	if(argc!=3){
		printf("Quantidade de parametros invalidos: %d", argc);
		return 1;
	}
	//Declaração de ponteiros do tipo FILE
	FILE *arq1, *arq2;
	//Abrir arquivo 1 de leitura
	arq1=fopen(argv[1], "r");
	//Abrir arquivo 2 de gravação
	arq2=fopen(argv[2], "w");
	//Checagem se os arquivos puderam ser abertos com sucesso
	if(arq1 == NULL || arq2 == NULL){
		printf("Deu B.O nos arquivos!!!\n");
		return 0;
	}
	//Declarar string para armazenar números na leitura do arquivo
	char texto[TAMANHO+1], simbolo;
	//Declarar i para contar quantidade de caracteres válidos
	int i=0;
	//Declarar variável para armazenar valor booleano, dos testes de caracter
	bool continuar=true;
	//Laço de repetição para verificar se os caracteres são válidos
	while(!feof(arq1)){
		//Variável para armazenar caracter retornado da função fgetc
		simbolo=fgetc(arq1);
		//Verifica se o caracter é inválido, ou seja, não é um número ou o final do arquivo
		if((simbolo<48 || simbolo>57) && simbolo!='\n' && simbolo!=EOF){
			//Definir valor "false" para terminar execução do programa sem iniciar as pilhas
			continuar=false;
			break;
		}
		//Verifica o contador, para o caso de arquivos vazios, ou que apresentam somente quebra de linhas
		else if(i==0 && simbolo==EOF){
			continuar=false;
			break;
		}
		//Adicionar 1 ao contador se o caracter for válido
		else if(simbolo>=48 && simbolo<=57){
			i++;
		}
	}
	//Declarar vetor para armazenar os números extraídos e convertidos em binário do arquivo,
	//e o contador usado para delimitar onde os números serão invertidos
	int bin[20], contador=0;
	if(continuar==true){
		//Abrir arquivo de leitura novamente para extrair strings
		arq1=fopen(argv[1], "r");
		//Checagem se o arquivo de leitura pôde ser aberto com sucesso
		if(arq1 == NULL){
			printf("Deu B.O no arquivo de leitura!!!\n");
			return 0;
		}
		//Laço para a leitura da linha e armazenar na string "texto"
		for(i=0; fgets(texto, 10, arq1)!=NULL; i++){
			//Usar a função atoi para converter string em inteiro, para verificar seu valor
			bin[i]=atoi(texto);
			//Caso o número ultrapasse o valor de 8 bits, alterar valor de "continuar" para "false"
			if(bin[i]>255){
				continuar=false;
				break;
			}
			//Usar a função binario para converter retorno da função atoi em inteiro
			bin[i]=binario(atoi(texto));
			contador++;
		}
	}
	//Caso os valores do arquivo de entrada sejam válidos, continuar execução
	if(continuar==true){
		//Imprimir binário em ordem invertida no arquivo de saída
		for(i=contador-1; i>=0; i--){
			fprintf(arq2, "%d\n", bin[i]);
		}
	}
	//Caso os valores sejam inválidos, retornar "Arquivo inválido!" no arquivo de saída
	else{
		fclose(arq2);
		arq2=fopen(argv[2], "w");
		fprintf(arq2,"Arquivo invalido!\n");
	}
	//Fechar arquivos 1 e 2
	fclose(arq1);
	fclose(arq2);
	return 0;
}