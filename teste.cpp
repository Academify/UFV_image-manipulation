#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAXALTURA  = 500;
const int MAXLARGURA = 500;
unsigned char imagem[MAXALTURA][MAXLARGURA];	//a imagem propriamente dita
char tipo[4];  									//tipo da imagem
int largura, altura;							//dimensoes da imagem


	// - Declaração de funções ------------------------------------------------------

	void menu();
	int verificaResposta(int resp);
	int leituraImagem(string nome);
	unsigned char clarearPB(unsigned char imagem);

	// ------------------------------------------------------------------------------

int main(){

    int resp = 8;
    string nome;
    cout << "Informe o nome da imagem a ser lida: " << endl;
    cin >> nome;
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
    cout << "0 - Sair"<< endl;
}

int verificaResposta(int resp){
    switch (resp){
    case 1:
		if (tipo == "P2"){
			//clarearPB(imagem, altura, largura);
		}else{
			//clarearRGB(imagem, altura, largura);
		}
		cout << "Efeito 1 aplicado!" << endl;
        break;
    case 2:
		if (tipo == "P2"){
			//escurecerPB(imagem, altura, largura);
		}else{
			//escurecerRGB(imagem, altura, largura);
		}
        cout << "Efeito 2 aplicado!" << endl;
        break;
    case 3:
		if (tipo == "P2"){
			//negativoPB(imagem, altura, largura);
		}else{
			//negativoRGB(imagem, altura, largura);
		}
        cout << "Efeito 3 aplicado!" << endl;
        break;
    case 4:
        if (tipo == "P2"){
			//espelhoPB(imagem, altura, largura);
		}else{
			//espelhoRGB(imagem, altura, largura);
		}
        cout << "Efeito 4 aplicado!" << endl;
        break;
    case 5:
        if (tipo == "P2"){
			//sobelPB(imagem, altura, largura);
		}else{
			//sobelRGB(imagem, altura, largura);
		}
        cout << "Efeito 5 aplicado!" << endl;
        break;
    case 0:
        return 0;
        break;
    default:
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
		//cout<<endl;
	}
	//************************************//

	arqentrada.close();
    return 8;
    //*** FIM DA LEITURA DA IMAGEM ***//
}