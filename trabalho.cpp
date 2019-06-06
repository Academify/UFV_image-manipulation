#include <iostream>
#include <fstream>
#include <cstring>

const int MAXALTURA  = 500;							//tamanho maximo aceito (pode ser alterado)
const int MAXLARGURA = 500;

using namespace std;

int main() {
	unsigned char imagem[MAXALTURA][MAXLARGURA];	//a imagem propriamente dita
	int largura, altura;							//dimensoes da imagem
	char tipo[4];									//tipo da imagem
	ifstream arqentrada;							//arquivo que contem a imagem original
	ofstream arqsaida;								//arquivo que contera a imagem gerada
	char comentario[200], c;						//auxiliares
	int i, j, valor;								//auxiliares

//*** LEITURA DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte

	//*** Abertura do arquivo ***//
	arqentrada.open("arquivo.pnm",ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo.pnm\n";
		return 0;
	}
	//***************************//

	
	//*** Leitura do cabecalho ***//
	arqentrada >> tipo;	//Le o tipo de arquivo
	arqentrada.get();	//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n"; // Redirecionar para o menu de preto e branco;
	}
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida\n";// Redirecionar para o menu de colorida
		cout << "Desculpe, mas ainda nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, mas nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	//Enquanto for comentario
		arqentrada.getline(comentario,200);	//Le e descarta a linha "inteira"

	arqentrada.putback(c);	//Devolve o caractere lido para a entrada, pois como
							//nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	//Le o numero de pixels da horizontal e vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura>MAXLARGURA) {
		cout << "Desculpe, mas ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (largura>MAXALTURA) {
		cout << "Desculpe, mas ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}
	
	arqentrada >> valor;	//Valor maximo do pixel (temos que ler, mas nao sera usado)
	//****************************//

	//*** Leitura dos pixels da imagem ***//
	for(i=0;i<altura;i++){
		for(j=0;j<largura;j++) {
			arqentrada >> valor;
			imagem[i][j] = (unsigned char)valor;
			//cout<<valor<<" ";
		}
		cout<<endl;
	}
	//************************************//

	arqentrada.close();

//*** FIM DA LEITURA DA IMAGEM ***//




//*** TRATAMENTO DA IMAGEM ***//
//inicialmente e' nesta parte do codigo que voce vai trabalhar

	//int fator;
	//cout << "Qual o fator de escurecimento (1-100) ? ";
	//cin >> fator;

	//*** Escurece a imagem ***//
	//for(i=0;i<altura;i++)
	//	for(j=0;j<largura;j++) {
	//		valor = (int)imagem[i][j];				//pega o valor do pixel
	//		valor -= fator;							//escurece o pixel
	//		if (valor<0)							//se der negativo
	//			valor = 0;							//  deixa preto
	//		imagem[i][j] = (unsigned char)valor;	//modifica o pixel
	//	}
    //*************************// 
	
	//*** Gera o negativo da imagem ***//
	//for(i=0;i<altura;i++) {
	//	for(j=0;j<largura;j++) {
	//		valor = (int)imagem[i][j];			
	//		valor = 255 - valor;
	//		imagem[i][j] = (unsigned char)valor;
	//	}
	//}
    //*************************//
	
	//*** Gera o espelho da imagem ***//
	//for(i=0;i<altura;i++) {
	//	for(j=0;j<largura/2;j++) {
	//		valor = (int)imagem[i][j];			
	//		int aux = (int) imagem[i][largura-1-j];
	//		imagem[i][largura-1-j]=(unsigned char)valor;
	//		imagem[i][j] = (unsigned char) aux;
	//	}
	//}
    //*************************//
	
	//*** Gera o filtro de sobel ***//
	int matriz[3][3] = {1,2,1,0,0,0,-1,-2,-1};
	int soma = 0;
	unsigned char novaImagem[MAXALTURA][MAXLARGURA];
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < largura; j++){
			if (i!=0){ //não está na primeira linha
				soma+= ((int) imagem[i-1][j])*matriz[0][1];
				if(j!=0)  //não está na primeira coluna 
					soma+= ((int) imagem[i-1][j-1])*matriz[0][0];					
				if(j!=largura-1)  //não está na última coluna
					soma+= ((int) imagem[i-1][j+1])*matriz[0][2];
			}
			if(i!=altura-1){ //não está na última linha
				soma+= ((int) imagem[i+1][j])*matriz[2][1];
				if(j!=0)  //não está na primeira coluna 
					soma+= ((int) imagem[i+1][j-1])*matriz[2][0];					
				if(j!=largura-1)  //não está na última coluna
					soma+= ((int) imagem[i+1][j+1])*matriz[2][2];
			}
			soma+= ((int) imagem[i][j])*matriz[1][1];
			if(j!=0)  //não está na primeira coluna 
				soma+= ((int) imagem[i][j-1])*matriz[1][0];					
			if(j!=largura-1)  //não está na última coluna
				soma+= ((int) imagem[i][j+1])*matriz[1][2];
				
			if (soma>255) soma = 255;
			if (soma < 0) soma = 0;
			novaImagem[i][j] = (unsigned char) soma;
			soma = 0;
		}
	}
	int matriz2[3][3] = {1,0,-1,2,0,-2,1,0,-1};
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < largura; j++){
			if (i!=0){ //não está na primeira linha
				soma+= ((int) imagem[i-1][j])*matriz2[0][1];
				if(j!=0)  //não está na primeira coluna 
					soma+= ((int) imagem[i-1][j-1])*matriz2[0][0];					
				if(j!=largura-1)  //não está na última coluna
					soma+= ((int) imagem[i-1][j+1])*matriz2[0][2];
			}
			if(i!=altura-1){ //não está na última linha
				soma+= ((int) imagem[i+1][j])*matriz2[2][1];
				if(j!=0)  //não está na primeira coluna 
					soma+= ((int) imagem[i+1][j-1])*matriz2[2][0];					
				if(j!=largura-1)  //não está na última coluna
					soma+= ((int) imagem[i+1][j+1])*matriz2[2][2];
			}
			soma+= ((int) imagem[i][j])*matriz2[1][1];
			if(j!=0)  //não está na primeira coluna 
				soma+= ((int) imagem[i][j-1])*matriz2[1][0];					
			if(j!=largura-1)  //não está na última coluna
				soma+= ((int) imagem[i][j+1])*matriz2[1][2];
				
			if (soma>255) soma = 255;
			if (soma < 0) soma = 0;
			int media = ((int)novaImagem[i][j]+soma)/2;
			if (media>255) media = 255;
			if (media< 0) media = 0;
			novaImagem[i][j] = (unsigned char) media;
			soma = 0;
		}
	}
	//*************************//
	
//*** FIM DO TRATAMENTO DA IMAGEM ***//

//*** GRAVACAO DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte

	//*** Grava a nova imagem ***//
	arqsaida.open("novaimagem.pnm",ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar novaimagem.pnm\n";
		return 0;
	}

	arqsaida << tipo << endl;						//tipo
	arqsaida << "# INF110\n";						//comentario
	arqsaida << largura << " " << altura << endl;	//dimensoes
	arqsaida << 255 << endl;						//maior valor
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++)
			arqsaida << (int)novaImagem[i][j] << endl;	//pixels

	arqsaida.close();		//fecha o arquivo
	//***************************//

//*** FIM DA GRAVACAO DA IMAGEM ***//

	return 0;
}