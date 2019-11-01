#include <iostream>
#include <vector>
#include <stdlib.h>

//#define TABULEIRO

/* Universidade Federal do Pampa - Campus Alegrete
Aluna: Isadora Garcia Ferrão
Disciplina: Inteligência Artificial*/

using namespace std;

int solucaoEncontrada = 0; // o algoritmo poderia contar a quantidade de soluções possíveis, mas vai ser usado para quando for igual a 1 parar a execução do algoritmo, já que o enunciado pedia uma saída padrão.

void mostrarTabuleiro(vector<vector<int> > & tabuleiro, int dimensao){
	for(int i = 0; i < dimensao; i++){
		for(int j = 0; j < dimensao; j++){
			if(tabuleiro[i][j] == 1)
				cout << "R\t";
			else
				cout << "-\t";
		}
		cout << "\n\n";
	}
	cout << "\n";
}

void mostrarSaida(vector<vector<int> > & tabuleiro, int dimensao){
	cout << "Saida: ";
	for(int i = 0; i < dimensao; i++){
		for(int j = 0; j < dimensao; j++){
			if(tabuleiro[j][i] == 1)
				cout << (j+1) << " ";
		}
	}
	cout << "\n\n";
}

void executar(vector<vector<int> > & tabuleiro, int dimensao, int coluna){
	#pragma loop(hint_parallel(8))  
	if(coluna == dimensao){
		#ifdef TABULEIRO
			mostrarTabuleiro(tabuleiro, dimensao); //Se Quiser mostrar o Tabuleiro Descomente o Define
		#endif
		mostrarSaida(tabuleiro, dimensao);
		solucaoEncontrada++;
		return;
	}

	for(int i = 0; i < dimensao; i++){ // verificação de coluna com chamada recursiva
		#pragma loop(hint_parallel(8))  
		if(seguro(tabuleiro, dimensao, i, coluna)){
			tabuleiro[i][coluna] = 1;
			executar(tabuleiro, dimensao, coluna + 1);
			if(solucaoEncontrada == 1){
				return;
			}
			tabuleiro[i][coluna] = 0;
		}
	}
}

bool seguro(vector<vector<int> > & tabuleiro, int dimensao, int linha, int coluna){
	int i, j;
	
	for(i = 0; i < dimensao; i++){
		if(tabuleiro[linha][i] == 1)
			return false;
	}

	for(i = 0; i < dimensao; i++){
		if(tabuleiro[i][coluna] == 1)
			return false;
	}

	for(i = linha, j = coluna; i >= 0 && j >= 0; i--, j--){
		if(tabuleiro[i][j] == 1)
			return false;
	}
	
	for(i = linha, j = coluna; i < dimensao && j < dimensao; i++, j++){
		if(tabuleiro[i][j] == 1)
			return false;
	}

	for(i = linha, j = coluna; i >= 0 && j < dimensao; i--, j++){
		if(tabuleiro[i][j] == 1)
			return false;
	}
	
	for(i = linha, j = coluna; i < dimensao && j >= 0; i++, j--){
		if(tabuleiro[i][j] == 1)
			return false;
	}

	return true;
}

int main(int argc, char *argv[]){
	int dimensao;
	if(argc!=2){
		cout << "Digite: " << argv[0] << " <NumerodeRainhas>\n\n";
		exit(0);
	}
	dimensao = atoi(argv[1]);
	if(dimensao <= 0 || dimensao < 4){
		cout << "Digite um valor positivo Maior ou Igual a 4\n\n";
		exit(0);
	}
    cout << "Entrada: " << dimensao << "\n";
	vector<vector<int> > tabuleiro;

	for(int i = 0; i < dimensao; i++){
		vector<int> linha(dimensao);
		tabuleiro.push_back(linha);
	}
	
	executar(tabuleiro, dimensao, 0);
	return 0;
}
