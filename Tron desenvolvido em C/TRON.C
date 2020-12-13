#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <time.h>


/*
	//Tabela de valores importantes//
	Setas:
	75	37	esquerda
	80	38	direita
	72	39	cima
	77	40	baixo
	
	Constante das setas	(-32)

*/

//Define o tamanho e posicao do tabuleiro
#define TW 60
#define TH 20
#define TX 10
#define TY 5
bool Tabuleiro[TW][TH];


//Constantes para reconhecimento das teclas

/*const int Setas = -32;
const int ESQUERDA = 75;
const int DIREITA = 77;
const int CIMA = 72;
const int BAIXO = 80;
const int ESC = 27;
const int ENTER = 13;
*/

#define Setas -32
#define ESQUERDA 75
#define DIREITA 77
#define CIMA 72
#define BAIXO 80
#define ESC 27
#define ENTER 13



//Variaveis globais para reconhcer quando alguma tecla foi pressionada
bool pressESQ = false;
bool pressDIR = false;
bool pressCIM = false;
bool pressBAI = false;

bool pressW = false;
bool pressA = false;
bool pressS = false;
bool pressD = false;

bool pressESC = false;
bool pressENTER = false;



//Marca na coordenada do tabuleiro
void marcaTabuleiro(int x, int y){
	Tabuleiro[x][y] = false;
}

//Função para inicializar o tabuleiro
void zeraTabuleiro(){
	int i; 
	int j;
	for(i = 0;i<TW;i++){		
		for(j = 0;j<TH;j++){
			Tabuleiro[i][j] = true;
			if (i == 0)
				Tabuleiro[i][j] = false;
			if (i == TW-1)
				Tabuleiro[i][j] = false;
			if (j == 0)
				Tabuleiro[i][j] = false;
			if (j == TH-1)
				Tabuleiro[i][j] = false;
		}
	}
}


//Função para imprimir o tablueiro apenas para debuggar e saber se está sendo marcado nas posições corretas
void imprimeTabuleiro(){
	system("cls");
	int i;
	int j;
	for(j=0;j<TH;j++){
		for(i=0;i<TW;i++){
			printf("%d",Tabuleiro[i][j]); 
		}
		printf("\n");
	}
}



void imprimeMenu(){
	printf("\t\t\tJogador contra Jogador");
	Sleep(50);
	printf("\n");
	Sleep(50);
	printf("\t\t\tJogador contra Computador");
	Sleep(50);
	printf("\n");
	Sleep(50);
	printf("\t\t\tComputador contra Computador");
	Sleep(50);
	printf("\n\n\n");
	Sleep(50);
	printf("\t\tPressione as Setas ou WASD e Enter para Selecionar");
	Sleep(50);
	printf("\n\n\n\n\tControles:");
	Sleep(50);
	printf("\t\t[[Jogador 1: WASD]]\t\t[[Jogador 2: Setas]]");
	Sleep(50);
	printf("\n\nObjetivo: Sobreviva o máximo de tempo sem bater em paredes ou rastros dos jogadores.");
	Sleep(50);
	printf("\n\n\t\tPressione Esc a qualquer momento para fechar o jogo");
}

void imprimeIntroducao(){
	printf("\n\t/////////////////\t\tTRON\t\t//////////////////");
	printf("\n\t/////////////////\tJogo por Thomaz Diniz\t//////////////////");
	printf("\n\n");
	Sleep(100);
}

//Função de fazer checagem nos botões que estão sendo teclados cada vez chamada reinicia todas as teclas e logo em seguida faz os testes necessários
bool atualizaBotoes(){	
	pressESQ = false;
	pressDIR = false;
	pressCIM = false;
	pressBAI = false;
	
	pressW = false;
	pressA = false;
	pressS = false;
	pressD = false;
	
	pressESC = false;
	pressENTER = false;
	
	int botao = 0;
	if (kbhit() != 0){
		botao = getch();
		switch(botao){
			case Setas:
				
				botao = getch();
				case ESQUERDA:
					pressESQ = true;
				break;
					
				case DIREITA:
					pressDIR = true;
				break;
				
				case CIMA:
					pressCIM = true;
				break;
				
				case BAIXO:
					pressBAI = true;
				break;
			break;
				
			case ESC:
				pressESC = true;
			break;				
			
			case ENTER:
				pressENTER = true;
			break;	
			
			case 'a':case 'A':
				pressA = true;
			break;
			
			case 'w': case 'W':
				pressW = true;
			break;
			
			case 's': case 'S':
				pressS = true;
			break;
			
			case 'd':case 'D':
				pressD = true;
			break;
				
			default:
				return false;
			break;
		}
		return true;
	}	

}

//Manda o teclado para a coordenada desejada
void consoleVaiPara(int x, int y){
	COORD p = {x,y}; //Estrutura de coordenadas?
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);//muda a coordenada do cursor para a coordenada p
}

//Tipo jogador que possui posição e velocidade
typedef struct{
	int x;
	int y;
	int vx;
	int vy;
} Jogador;

//Função para zerar o jogador
void zeraJogador(Jogador* jogador){
	jogador->x = 0;
	jogador->y = 0;
	jogador->vx = 0;
	jogador->vy = 0;
}

//Atualiza o jogador. Função para ser chamada cada vez que o jogo precisar atualizar
void jogadorAtualiza(Jogador* jogador){
	jogador->x += jogador->vx;
	jogador->y += jogador->vy;
	if (jogador->x < 0){jogador->x = 0;}
	if (jogador->y < 0){jogador->y = 0;}
	if (jogador->x > TW-1){jogador->x = TW-1;}
	if (jogador->y > TH-1){jogador->y = TH-1;}
}

//Modifica a velocidade do jogador
void jogadorSetVel(Jogador* jogador,int vx, int vy){
	jogador->vx = vx;
	jogador->vy = vy;
}

//modifica a posição diretamente do jogadador
void jogadorSetPosicao(Jogador* jogador, int x, int y){
	jogador->x = x;
	jogador->y = y;
}

//Desenha o jogador na posição
void jogadorDesenha(Jogador jogador){
	consoleVaiPara(TX+jogador.x,TY+jogador.y);//Desenha
	printf("%c", 'O');//Desenha
}

//Desenha indicador de morte
void jogadorDesenhaMorte(Jogador jogador){
	consoleVaiPara(TX+jogador.x,TY+jogador.y);//Desenha
	printf("%c", 'X');//Desenha
	Sleep(500);
	
	//Explosão para dar efeito
	int i, j, k, m;
	char c = '#';
	for(k = 0; k < 6; k++){
		for(m = 0; m < 2; m++){	
			for(i = -k*2; i<k*2; i++){
				for(j = -k; j < k; j++){
					consoleVaiPara(TX+jogador.x+i,TY+jogador.y+j);//Desenha
					printf("%c", c);//Desenha
				}
			}
			Sleep(100);
			if (c == '#'){c = 'X';} else if (c == 'X') {c = '%';}else {c='#';}
		}
	
	}
	
	
}

//Checa se a posição que o jogador se encontra está livre. Para testar a condição de derrota
bool posJogadorLivre(Jogador jogador){
	int x = jogador.x;
	int y = jogador.y;
	
	if (jogador.vx == 0 && jogador.vy == 0)
		return true;
	
	return Tabuleiro[x][y];
}

//Função para retornar o sinal de um numero
int sinal(int n){
	if (n > 0){return 1;}
	if (n < 0){return -1;}
	if (n == 0){return 0;}
}

//Funções necessárias para a IA

//Retorna um número aleatorio de 0 a i-1
int aleatorio(int i){return rand() % i;}

//Retorna um booleano para se a chance acontecer. Quanto maior o número, menor a chance. Imagine como um dado de n lados sendo lançado e você tem a chance de uma das faces cair a que você quer
bool chance(int i){return aleatorio(i) == i-1;}

//Escolhe um dos valores aleatoriamente
int escolhe(int a, int b){
	if (chance(2)){
		return a;
	} else{
		return b;
	}
}


//Retorna se o jogador está colidindo com uma parede a frente dele
bool ColideAFrente(Jogador jogador){
	int x = jogador.x + jogador.vx;
	int y = jogador.y + jogador.vy;
	
	return !Tabuleiro[x][y];
}

//Codigo de controle por meio de um burro artificial do jogo.
//Pode imaginar no Jogador como uma marionete que aceita tanto inputs automaticos como inputs do controle.
void iaControlaJogador(Jogador* jogador){	
	
	if (ColideAFrente(*jogador)){//Se colide a frente vira
		if (jogador->vx!=0){
			jogador->vx = 0;
			jogador->vy = escolhe(-1,1);
		} else {
			jogador->vy = 0;
			jogador->vx = escolhe(-1,1);
		}
		if(ColideAFrente(*jogador)){
			jogador->vx *= -1;
			jogador->vy *= -1;
		}
	}else{
		if (chance(12)){//muda Direcao da marionete aleatoriamente
				int vx = jogador->vx;
				int vy = jogador->vy;
				
				if (jogador->vx != 0){
					jogador->vx = 0;
					jogador->vy = escolhe(-1,1);
				} else {
					jogador->vy = 0;
					jogador->vx = escolhe(-1,1);	
				}
				
				if(ColideAFrente(*jogador)){
						jogador->vx = vx;
						jogador->vy = vy;
				}
		}
	}
}


void desenhaSala(){//Desenha o tabuleiro do jogo
	
	int x = TX;
	int y = TY;
	
	for(x = TX; x < (TX+TW); x++){
		Sleep(2);
		consoleVaiPara(x,y);
		printf("%c", 35); 
	}x--;
	for(y = TY; y < (TY+TH); y++){
		Sleep(2);
		consoleVaiPara(x,y);
		printf("%c", 35); 
	}y--;
	for(x = (TX+TW-1); x > (TX); x--){
		Sleep(2);
		consoleVaiPara(x,y);
		printf("%c", 35); 
	}
	for(y = (TY+TH-1); y > (TY); y--){
		Sleep(2);
		consoleVaiPara(x,y);
		printf("%c", 35); 
		
	}
}

//Script para mudar o valor d euma variável qualquer
void setVar(int *a, int valor){
	*a = valor;
}

//Script para adicionar o valor do vetor x,y pelo vetor vx,vy
void addPos(int *x, int *y, int vx, int vy){
	*x+=vx;
	*y+=vy;
}


//Que o jogo comece
int main(){
	
	//Muda o jogo para porugues
	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));
	
	//Declara os possíveis jogadores do jogo;
	Jogador jogador;
	Jogador jogador2;
	
	//Booleanos que indicam quais jogadores estão sendo controlados pelo computador
	bool computador1 = false;
	bool computador2 = false;
	
	int Estado = 0;//menu feito por meio de máquina de estados finitos
	int botaoMenu = 0;//inteiro que representa qual botão do menu principal está sendo selecionado
	int vencedor = 0;//Inteiro que me diz quem é o vencedor
	int empate = 0;//inteiro que indica se o joo empatou
				
	//Laço de repetição que vai rodar o jogo
	while(1){//Laço do jogo rodando
		
		atualizaBotoes();
		
		//Caso pressione esc, o laço quebra e o jogo finaliza
		if (pressESC){break;}
			
		switch(Estado){//Máquina de estados finitos para a lógica do jogo
			case 0://Desenha Introducao e Menu
				system("cls");
				imprimeIntroducao();
				imprimeMenu();
				Estado++;
				consoleVaiPara(23,4+botaoMenu);	printf(">");consoleVaiPara(23,4);//Desenha a setinha no menu
				
			break;
			
			case 1://Menu
				
				if (pressCIM || pressBAI || pressW || pressS){//Se pressionar o botão, muda a variavel botaomenu e muda a posicao da seta
					consoleVaiPara(23,4+botaoMenu);	
					printf(" ");
					if ((pressCIM) || (pressW))
						botaoMenu--;
					if ((pressBAI) || (pressS))
						botaoMenu++;
					if (botaoMenu > 2)
						botaoMenu = 0;
					if (botaoMenu < 0)
						botaoMenu = 2;
					consoleVaiPara(23,4+botaoMenu);
					printf(">");
				}
				
				//Se clicar enter muda o estado
				if (pressENTER){Estado++;	system("cls");}
			break;
			
			case 2://Carrega Sala
				system("cls");
				
				//Inicializa tudo que é necessário inicializar
				zeraJogador(&jogador);
					jogadorSetPosicao(&jogador,-5+TW/4,TH/2);
					jogadorSetVel(&jogador, 1,0);
				zeraJogador(&jogador2);
					jogadorSetPosicao(&jogador2,6+3*TW/4,TH/2);
					jogadorSetVel(&jogador2, -1,0);
				
				if (botaoMenu == 0){
					computador1 = false;
					computador2 = false;
				} else if (botaoMenu == 1){
					computador1 = false;
					computador2 = true;
				} else {
					computador1 = true;
					computador2 = true;
				}
				
				
				imprimeIntroducao();
				desenhaSala();
				zeraTabuleiro();
				Sleep(1000);
				Estado++;
			break;
			
			case 3://Jogo
			
					if (computador2){//computador controla
							iaControlaJogador(&jogador2);	
					} else {//jogador controla
						if (pressESQ){	if (jogador2.vx != 1 ){jogadorSetVel(&jogador2, -1,0);}}
						if (pressDIR){	if (jogador2.vx != -1){jogadorSetVel(&jogador2, 1,0); }}
						if (pressCIM){	if (jogador2.vy != 1 ){jogadorSetVel(&jogador2, 0,-1);}}
						if (pressBAI){	if (jogador2.vy != -1){jogadorSetVel(&jogador2, 0,1); }}
					}
				
				
					if (computador1){//computador controla
							iaControlaJogador(&jogador);	
					} else {//jogador controla
						if (pressA){	if (jogador.vx != 1 ){jogadorSetVel(&jogador, -1,0);}}
						if (pressD){	if (jogador.vx != -1){jogadorSetVel(&jogador, 1,0); }}
						if (pressW){	if (jogador.vy != 1 ){jogadorSetVel(&jogador, 0,-1);}}
						if (pressS){	if (jogador.vy != -1){jogadorSetVel(&jogador, 0,1); }}
					}
	
					//atualiza coordenadas
					jogadorAtualiza(&jogador);
					jogadorAtualiza(&jogador2);
					
					//desenha nas coordenadas
					jogadorDesenha(jogador);
					jogadorDesenha(jogador2);
					
					//Condição de derrota e empate
					empate = 0;
					if (!posJogadorLivre(jogador))	{Estado=4;	vencedor = 2;	empate++;	jogadorDesenhaMorte(jogador);	Sleep(100);}
					if (!posJogadorLivre(jogador2))	{Estado=4;	vencedor = 1;	empate++;	jogadorDesenhaMorte(jogador2);	Sleep(100);}
					
					//Marca no mapa de colisão
					marcaTabuleiro(jogador.x,jogador.y);
					marcaTabuleiro(jogador2.x,jogador2.y);
					
					//Checa se os dois morreram no mesmo frame
					if (empate == 2)
						vencedor = 3;					
					
					Sleep(100);	
			break;
			
			case 4://Tela de vencedor
				
				Sleep(500);
				system("cls");
				Sleep(50);
				consoleVaiPara(TX+TW/3,TY+TH/3);
				if (vencedor == 3){
					printf("O jogo empatou :(");
				} else {
					printf("Jogador %d Venceu! :D", vencedor);
				}
					
				getch();
				Estado = 0;
			break;
		}
	}
	return 0;
}
