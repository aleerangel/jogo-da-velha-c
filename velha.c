#include <stdio.h> 
#include <stdlib.h>
#include "velha.h"

#define LINHAS 3
#define COLUNAS 3

//cria a matriz do tabuleiro como variavel global
int tabuleiro[3][3];

int main() {
    int continuar=1;
    //loop para funcao de jogar novamente
    while(continuar==1) {
        int acabou=0;
        //preenche as posicoes da matriz
        iniciaTabuleiro();
        //armazena a quantidade de jogadas
        int jogadas=0;
        //enquanto nao acabou, acontece uma rodada
        while(acabou==0) {
            jogada(&jogadas);
            verificaAcabou(&acabou, jogadas);
        }
        //menu para jogar novamente ou sair
        menu(&continuar);
    }
    return 0;
}

//preenche a matriz inicial de 1 a 9
void iniciaTabuleiro() {
    int posicao=1;
    for(int i=0; i<LINHAS; i++ ) {
        for(int j=0; j<COLUNAS; j++) {
            tabuleiro[i][j]=posicao;
            posicao++;
        }
    }
    imprime();
}

//imprime o tabuleiro
void imprime() {
    //limpa o terminal antes de exibir o tabuleiro
    system("cls");
    for(int i=0; i<LINHAS; i++) {
        for(int j=0; j<COLUNAS; j++) {
            //se a posicao for preenchida por 1 a 9, imprime a posicao
            if(tabuleiro[i][j]<10) {
                printf("%d ", tabuleiro[i][j]);
            } 
            //se a posicao for preenchida por 11, imprime X
            else if(tabuleiro[i][j]==11) {
                printf("X ");
            }
            //se a posicao for preenchida por 12, imprime 0
            else if(tabuleiro[i][j]==12) {
                printf("O ");
            } 
            
        }
        printf("\n");
    }
}

void jogada(int* jogadas) {
    //se o numero da jogada for 0 ou par, a vez e do jogador 1 
    int vezJogador;
    if((*jogadas)%2==0) {
        vezJogador=1;
    } else {
        //se nao, e vez do jogador 3
        vezJogador=2;
    }
    //faz a jogada com base na vez do jogador
    joga(&vezJogador);
    //acrescenta 1 ao numero de jogadas
    (*jogadas)++;
}

void joga(int* vezJogador) {
    int pos;
    printf("Proxima jogada!\n");
    //do while para verificacao de entrada
    int valida=0;
    do{
        //imprime o jogador da vez com base na funcao anterior
    if((*vezJogador)==1) {
        printf("Jogador 1 - X\n");
    } else {
        printf("Jogador 2 - O\n");
    }
    //escaneia a posicao da jogada
    printf("Digite a posicao (1-9)\n");
    scanf("%d", &pos);
    //verifica se a posicao digitada e valida
    valida=verificaEntrada(pos);
    //repete enquanto a entrada for invalida
    } while(!valida);
    //adiciona X como 11 ou O como 12 no tabuleiro
    if(pos>=1 && pos<=3) {
        if((*vezJogador)==1) {
            tabuleiro[0][pos-1]= 11;
        } else{
            tabuleiro[0][pos-1]= 12;
        }
    } else if(pos>=4 && pos<=6) {
        if((*vezJogador)==1) {
            tabuleiro[1][pos-4]= 11;
        } else{
            tabuleiro[1][pos-4]= 12;
        }
    } else if(pos>=7 && pos<=9) {
        if((*vezJogador)==1) {
            tabuleiro[2][pos-7]= 11;
        } else{
            tabuleiro[2][pos-7]= 12;
        }
    }
    //imprime o tabuleiro
    imprime();
}

int verificaEntrada(int pos) {
    int valido=1;
    //verifica se a entrada esta entre 1 e 9
    //verifica se a posicoa esta ocupada
    if(pos>=1 && pos<=3) {
        if(tabuleiro[0][pos-1]==11||tabuleiro[0][pos-1]==12) {
            valido=0;
        } 
    } else if(pos>=4 && pos<=6) {
        if(tabuleiro[1][pos-4==11]||tabuleiro[1][pos-4==12]) {
            valido=0;
        }
    } else if(pos>=7 && pos<=9) {
        if(tabuleiro[2][pos-7]==11||tabuleiro[2][pos-7]==12) {
            valido=0;
        }
    } else {
        valido=0;
    }
    if(valido==1) {
        //se for tudo valido, retorna 1
        return 1;
    } else {
        //se nao for valido, mantem como 0
        printf("Entrada invalida!\n");
    }
}

void verificaAcabou(int* acabou, int jogadas) {
    int ganhador=0;
    // Verifica linhas
    for (int i = 0; i < LINHAS; i++) {
        //se as 3 posicoes forem iguais, retorna 11 ou 12 para o ganhador
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) {
            ganhador=tabuleiro[i][0];
        }
    }
    // Verifica colunas
    for (int i = 0; i < COLUNAS; i++) {
        //se as 3 posicoes forem iguais, retorna 11 ou 12 para o ganhador
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i]) {
            ganhador=tabuleiro[0][i];
        }
    }
    // Verifica diagonal principal (\)
    //se as 3 posicoes forem iguais, retorna 11 ou 12 para o ganhador
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
        ganhador=tabuleiro[0][0];
    }
    // Verifica diagonal secundária (/)
    //se as 3 posicoes forem iguais, retorna 11 ou 12 para o ganhador
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) {
        ganhador=tabuleiro[0][2];
    }
    //imprime o vencedor, caso tenha
    if(ganhador==11) {
        printf("Jogador 1 ganhou!\n");
        (*acabou)=1;
        return;
    } else if(ganhador==12) {
        printf("Jogador 2 ganhou!\n");
        (*acabou)=1;
        return;
    }
    //se der empate (9 jogadas sem vencedor)
    if(jogadas==9) {
        (*acabou)=1;
        printf("Empate!\n");
    }
}

void menu(int* continuar) {
    int resposta;
    printf("O jogo acabou!\n");
    printf("Jogar novamente: 1\n");
    printf("Sair: 2\n");
    //verifica se a entrada e valida
    do{
        scanf("%d", &resposta);
        if(resposta==1) {
        //retorna 1 em caso de jogo novo
            (*continuar)=1;
            break;
        } else if(resposta==2) {
        //retorna 0 para sair
            (*continuar)=0;
            break;
        }
    } while(resposta!=0 && resposta!=1);
}