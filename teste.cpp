#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// - Variáveis Globais --------------------------------------------------------------

	const int MAXALTURA  = 500;
	const int MAXLARGURA = 500;
	unsigned char novaImagem[MAXALTURA][MAXLARGURA];
	unsigned char imagemC[MAXALTURA][MAXLARGURA][3];
	unsigned char imagem[MAXALTURA][MAXLARGURA];	//a imagem propriamente dita
	char tipo[4];  									//tipo da imagem
	int largura, altura;							//dimensoes da imagem

// ----------------------------------------------------------------------------------

// - Declaração de funções ------------------------------------------------------

	void menu();
	int verificaResposta(int resp);
	int leituraImagem(string nome);
	void clarearPB();
	void clarearRGB();
	void escurecerPB();
	void escurecerRGB();
	void negativoPB();
	void espelhoPB();
	void sobelPB();
	int salvarPB();

// ------------------------------------------------------------------------------


int main(){

    int resp = 8;
    string nome;
    cout << "Informe o nome da imagem a ser lida: " << endl;
    cin >> nome;
	cout << endl;
    resp = leituraImagem(nome);
    while (resp!= 0){
        menu();
        cin >> resp;
        resp = verificaResposta(resp);
    }
    
    return 0;
}

void menu(){
    cout << "O que deseja fazer com a sua imagem?" << endl;
    cout << "1 - Clarear imagem" << endl;
    cout << "2 - Escurecer imagem" << endl;
    cout << "3 - Negativo da imagem" << endl;
    cout << "4 - Espelho da imagem" << endl;
    cout << "5 - Filtro de sobel" << endl;
    cout << "6 - Salvar imagem" << endl;
    cout << "0 - Sair"<< endl;
	cout << endl;
}

int verificaResposta(int resp){
    switch (resp){
    case 1:
		if (strcmp(tipo,"P2")==0){
			clarearPB();
		}else{
			//clarearRGB();
		}
		cout << "Efeito 1 aplicado!" << endl;
		cout << endl;
        break;
    case 2:
		if (strcmp(tipo,"P2")==0){
			escurecerPB();
		}else{
			//escurecerRGB();
		}
        cout << "Efeito 2 aplicado!" << endl;
		cout << endl;
        break;
    case 3:
		if (strcmp(tipo,"P2")==0){
			negativoPB();
		}else{
			//negativoRGB();
		}
        cout << "Efeito 3 aplicado!" << endl;
		cout << endl;
        break;
    case 4:
        if (strcmp(tipo,"P2")==0){
			espelhoPB();
		}else{
			//espelhoRGB();
		}
        cout << "Efeito 4 aplicado!" << endl;
		cout << endl;
        break;
    case 5:
        if (strcmp(tipo,"P2")==0){
			sobelPB();
		}else{
			//sobelRGB();
		}
        cout << "Efeito 5 aplicado!" << endl;
		cout << endl;
        break;
	case 6:
        if (strcmp(tipo,"P2")==0){
			salvarPB();
		}else{
			//salvarRGB();
		}
        cout << "Imagem salva!" << endl;
		cout << endl;
        break;	
    case 0:
		int resposta;
		cout << endl;
		cout << "Deseja realmente sair?"<< endl;
		cout << endl;
		cout << "1 - SIM "<< endl;
		cout << "2 - NAO"<< endl;
		cout << endl;	
		cin >> resposta;
		cout << endl;
		if (resposta == 1){
			return 0;
		}
        break;
    default:
		return 0;
        break;
    }
}

int leituraImagem(string nome){
    // -------------------------------------------------------------------------------------
    
	ifstream arqentrada;							//arquivo que contem a imagem original
	ofstream arqsaida;  							//arquivo que contera a imagem gerada
	char comentario[200], c;						//auxiliares
	int i, j, valor;
    string extensao = ".pnm";

    // -------------------------------------------------------------------------------------

    //*** LEITURA DA IMAGEM ***//
	//*** Abertura do arquivo ***//
	arqentrada.open(nome + extensao,ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir "+ nome + extensao +"\n";
		return 0;
	}
	//***************************//

	
	//*** Leitura do cabecalho ***//
	arqentrada >> tipo;	//Le o tipo de arquivo
	arqentrada.get();	//Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << endl;
		cout << "Imagem em tons de cinza\n"; // Redirecionar para o menu de preto e branco;
		cout << endl;
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
	cout << endl;
	cout << "Tamanho: " << largura << " x " << altura << endl;
	cout << endl;
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
		//cout<<endl;
	}
	//************************************//

	arqentrada.close();
    return 8;
    //*** FIM DA LEITURA DA IMAGEM ***//
}

void clarearPB(){
	int valor, fator;
	cout << endl;
	cout << "Informe o fator de clareamento da imagem: " << endl;
	cout << endl;
	cin >> fator;
	cout << endl;
	for(int i=0;i<altura;i++){
		for(int j=0;j<largura;j++) {
			valor = (int)imagem[i][j];				//pega o valor do pixel
			valor += fator;							//escurece o pixel
			if (valor<0){							//se der negativo
				valor = 0;							//  deixa preto
			}								
			imagem[i][j] = (unsigned char)valor;	//modifica o pixel
		}
	}	
}
void escurecerPB(){
	int valor, fator;
	cout << endl;
	cout << "Informe o fator de escurecimento da imagem: " << endl;
	cout << endl;
	cin >> fator;
	cout << endl;
	for(int i=0;i<altura;i++){
		for(int j=0;j<largura;j++) {
			valor = (int)imagem[i][j];				//pega o valor do pixel
			valor -= fator;							//escurece o pixel
			if (valor<0){							//se der negativo
				valor = 0;							//  deixa preto
			}								
			imagem[i][j] = (unsigned char)valor;	//modifica o pixel
		}
	}	
}
void negativoPB(){
	int valor;
	for(int i=0;i<altura;i++) {
		for(int j=0;j<largura;j++) {
			valor = (int)imagem[i][j];			
			valor = 255 - valor;
			imagem[i][j] = (unsigned char)valor;
		}
	}
}
void espelhoPB(){
	int valor;
	for(int i=0;i<altura;i++) {
		for(int j=0;j<largura/2;j++) {
			valor = (int)imagem[i][j];			
			int aux = (int) imagem[i][largura-1-j];
			imagem[i][largura-1-j]=(unsigned char)valor;
			imagem[i][j] = (unsigned char) aux;
		}
	}
}
void sobelPB(){
	int matriz[3][3] = {1,2,1,0,0,0,-1,-2,-1};
	int soma = 0;
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < largura; j++){
			soma+= ((int) imagem[i-1][j])*matriz[0][1];
			soma+= ((int) imagem[i-1][j-1])*matriz[0][0];					
			soma+= ((int) imagem[i-1][j+1])*matriz[0][2];
			soma+= ((int) imagem[i+1][j])*matriz[2][1];
			soma+= ((int) imagem[i+1][j-1])*matriz[2][0];					
			soma+= ((int) imagem[i+1][j+1])*matriz[2][2];
			soma+= ((int) imagem[i][j])*matriz[1][1]; 
			soma+= ((int) imagem[i][j-1])*matriz[1][0];					
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
			soma+= ((int) imagem[i-1][j])*matriz2[0][1]; 
			soma+= ((int) imagem[i-1][j-1])*matriz2[0][0];					
			soma+= ((int) imagem[i-1][j+1])*matriz2[0][2];
			soma+= ((int) imagem[i+1][j])*matriz2[2][1]; 
			soma+= ((int) imagem[i+1][j-1])*matriz2[2][0];					
			soma+= ((int) imagem[i+1][j+1])*matriz2[2][2];
			soma+= ((int) imagem[i][j])*matriz2[1][1];
			soma+= ((int) imagem[i][j-1])*matriz2[1][0];					
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
	for (int i = 0; i < altura; i++) 
		for (int j = 0; j < largura; j++)
			imagem[i][j] = novaImagem[i][j];
}
int salvarPB(){

	ofstream arqsaida;  							//arquivo que contera a imagem gerada
	char comentario[200], c;						//auxiliares
	int i, j, valor;
    string extensao = ".pnm";

	//*** GRAVACAO DA IMAGEM ***//
	//inicialmente nao sera necessario entender nem mudar nada nesta parte

	//*** Grava a nova imagem ***//
	string novoNome;
	cout << endl;
	cout << "Informe o nome da imagem a ser salva: " << endl;
	cout << endl;
	cin >> novoNome;
	arqsaida.open(novoNome + extensao, ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << endl;
		cout << "Nao consegui criar " + novoNome + extensao + "\n";
		return 0;
	}

	arqsaida << tipo << endl;						//tipo
	arqsaida << "# INF110\n";						//comentario
	arqsaida << largura << " " << altura << endl;	//dimensoes
	arqsaida << 255 << endl;						//maior valor
	for(int i=0;i<altura;i++)
		for(int j=0;j<largura;j++)
			arqsaida << (int)imagem[i][j] << endl;	//pixels

	arqsaida.close();		//fecha o arquivo
	//***************************//

	//*** FIM DA GRAVACAO DA IMAGEM ***//
}

void clarearRGB(){
	int valor, fator;
	cout << endl;
	cout << "Informe o fator de clareamento da imagem: " << endl;
	cout << endl;
	cin >> fator;
	cout << endl;
	for(int i=0;i<altura;i++){
		for(int j=0;j<largura;j++) {
			for(int k=0; k<3; k++){
				valor = (int)imagemC[i][j][k];				//pega o valor do pixel
				valor += fator;							//escurece o pixel
				if (valor<0){							//se der negativo
				valor = 0;							//  deixa preto
				}
				imagemC[i][j][k] = (unsigned char)valor;	//modifica o pixel
			}								
		}
	}	
}
void escurecerRGB(){
	int valor, fator;
	cout << endl;
	cout << "Informe o fator de escurecimento da imagem: " << endl;
	cout << endl;
	cin >> fator;
	cout << endl;
	for(int i=0;i<altura;i++){
		for(int j=0;j<largura;j++) {
			for(int k=0; k<3; k++){
				valor = (int)imagemC[i][j][k];				//pega o valor do pixel
				valor -= fator;							//escurece o pixel
				if (valor<0){							//se der negativo
					valor = 0;							//  deixa preto
				}
				imagemC[i][j][k] = (unsigned char)valor;	//modifica o pixel
			}								
		}
	}
}
void negativoRGB(){
	int valor;
	for(int i=0;i<altura;i++) {
		for(int j=0;j<largura;j++) {
			for(int k=0; k<3; k++){
				valor = (int)imagemC[i][j][k];			
				valor = 255 - valor;
				imagemC[i][j][k]= (unsigned char)valor;
			}
		}
	}
}
void espelhoRGB(){
	int valor;
	for(int i=0;i<altura;i++) {
		for(int j=0;j<largura/2;j++) {
			for(int k=0; k<3; k++){
				valor = (int)imagemC[i][j][k];			
				int aux = (int) imagemC[i][j][largura - 1 - k];
				imagemC[i][j][largura-1-k]=(unsigned char)valor;
				imagemC[i][j][k] = (unsigned char) aux;
			}
		}
	}
}
 /* void sobelRGB(){
	int matriz[3][3] = {1,2,1,0,0,0,-1,-2,-1};
	int soma = 0;
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < largura; j++){
			soma+= ((int) imagem[i-1][j])*matriz[0][1];
			soma+= ((int) imagem[i-1][j-1])*matriz[0][0];					
			soma+= ((int) imagem[i-1][j+1])*matriz[0][2];
			soma+= ((int) imagem[i+1][j])*matriz[2][1];
			soma+= ((int) imagem[i+1][j-1])*matriz[2][0];					
			soma+= ((int) imagem[i+1][j+1])*matriz[2][2];
			soma+= ((int) imagem[i][j])*matriz[1][1]; 
			soma+= ((int) imagem[i][j-1])*matriz[1][0];					
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
			soma+= ((int) imagem[i-1][j])*matriz2[0][1]; 
			soma+= ((int) imagem[i-1][j-1])*matriz2[0][0];					
			soma+= ((int) imagem[i-1][j+1])*matriz2[0][2];
			soma+= ((int) imagem[i+1][j])*matriz2[2][1]; 
			soma+= ((int) imagem[i+1][j-1])*matriz2[2][0];					
			soma+= ((int) imagem[i+1][j+1])*matriz2[2][2];
			soma+= ((int) imagem[i][j])*matriz2[1][1];
			soma+= ((int) imagem[i][j-1])*matriz2[1][0];					
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
	for (int i = 0; i < altura; i++) 
		for (int j = 0; j < largura; j++)
			imagem[i][j] = novaImagem[i][j];
}
int salvarRGB(){ */

} */