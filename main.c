//Aluno: Jackson Breno Gomes Ferreira - n�USP: 11917761
//Aluno: Vileno Cunha Cavalcante - n�USP: 12559249

#include<stdio.h>
#include<string.h>
#define LIMPATELA system("cls")

void espera()
{
    system("pause");
}

// definindo os tipos de estruturas para o jogo
// coordenadas do tabuleiro por linha e coluna
struct coordenada
{
    int linha;
    int coluna;
};

typedef struct coordenada Coordenada;

//tipo de estrutura direcionada as pecas do tabuleiro
struct peca{
    char nome[30];
    int codigo;
    int esta_no_tabuleiro;
    int posicao_atual;
};

typedef struct peca Peca;

// tipo de estrutura direcionada ao jogador e suas jogadas
struct jogador{
    struct peca pecas[3];
    int jogadas;
};

typedef struct jogador Jogador;

//tipo de estrutura direcionada ao tabuleiro do jogo
struct tabuleiro{
    int tabuleiro[3][3];
    int pecas_no_tabuleiro;
};

typedef struct tabuleiro Tabuleiro;

//tipo de estrutura direcionada as posicoes das pecas no tabuleiro do jogo
struct jogadas{
    int posicoes[4];
    int total;
};

typedef struct jogadas Jogadas;

//funcao que retorna as coordenadas do tabuleiro
// -1 eh o caso em que nao eh possivel obter tal coordenada
Coordenada obtem_coordenada(int posicao)
{
    int i, j;
    switch(posicao){
    	//Analiando todas as coordenadas do tabuleiro, comecando da coordenada (0,0) e indo ate a (2,2)
        case 1:
            i = j = 0;
            break;
        case 2:
            i = 0, j = 1;
            break;
        case 3:
            i = 0, j = 2;
            break;
        case 4:
            i = 1, j = 0;
            break;
        case 5:
            i = 1, j = 1;
            break;
        case 6:
            i = 1, j = 2;
            break;
        case 7:
            i = 2, j = 0;
            break;
        case 8:
            i = 2, j = 1;
            break;
        case 9:
            i = 2, j = 2;
            break;
        default:
            i = j = -1;
        }
    Coordenada c = {i, j};
    return c;
}

//Essa funcao verifica quais posicoes uma peca pode ser colocada.
//Funcao recebe o tabuleiro, verifica a configuracao atual do tabuleiro,
//recebe a peca, verifica o tipo da peca e analisa para quais lugares do tabuleiro ela pode ir
//quando eh -1, entao a peca nao pode ir para uma determinada regiao do tabuleiro
//e quando eh diferente de -1, entao as posicoes sao validas para colocar uma peca.
//eh declarado um vetor com quatro posicoes pois a depender da posicao do bispo no tabuleiro
//o mesmo pode ir a somente quatro posicoes possiveis
Jogadas jogadas_possiveis(Peca* peca, Tabuleiro* tabuleiro)
{
    Jogadas jogadas = {{-1, -1, -1, -1}, 0};
    Coordenada c;
    int i;
    //O if verifica as posicoes que uma determinada peca pode ir
    if(peca->codigo == 1 || peca->codigo == 4){
        //jogadas - cavalo (possiveis posicoes no tabuleiro para o qual a pessa pode ir)
        //preenchendo os vetores com as posicoes que uma determinada peca pode ir em cada caso 
        switch(peca->posicao_atual){
            case 1:
                jogadas.posicoes[0] = 8;
                jogadas.posicoes[1] = 6;
            break;
            case 2:
                jogadas.posicoes[0] = 7;
                jogadas.posicoes[1] = 9;
            break;
            case 3:
                jogadas.posicoes[0] = 8;
                jogadas.posicoes[1] = 4;
            break;
            case 4:
                jogadas.posicoes[0] = 9;
                jogadas.posicoes[1] = 3;
            break;
            case 6:
                jogadas.posicoes[0] = 7;
                jogadas.posicoes[1] = 1;
            break;
            case 7:
                jogadas.posicoes[0] = 6;
                jogadas.posicoes[1] = 2;
            break;
            case 8:
                jogadas.posicoes[0] = 1;
                jogadas.posicoes[1] = 3;
            break;
            case 9:
                jogadas.posicoes[0] = 2;
                jogadas.posicoes[1] = 4;
            break;
            default:
            break;
        }
    }else if(peca->codigo == 2 || peca->codigo == 5){
        //jogadas - bispo (possiveis posicoes no tabuleiro para o qual a peca pode ir)
        //preenchendo os vetores com as posicoes que uma determinada peca pode ir em cada caso
        switch(peca->posicao_atual){
            case 1:
                jogadas.posicoes[0] = 5;
                jogadas.posicoes[1] = 9;
            break;
            case 2:
                jogadas.posicoes[0] = 6;
                jogadas.posicoes[1] = 4;
            break;
            case 3:
                jogadas.posicoes[0] = 5;
                jogadas.posicoes[1] = 7;
            break;
            case 4:
                jogadas.posicoes[0] = 2;
                jogadas.posicoes[1] = 8;
            break;
            case 5:
                jogadas.posicoes[0] = 1;
                jogadas.posicoes[1] = 9;
                jogadas.posicoes[2] = 3;
                jogadas.posicoes[3] = 7;
            break;
            case 6:
                jogadas.posicoes[0] = 2;
                jogadas.posicoes[1] = 8;
            break;
            case 7:
                jogadas.posicoes[0] = 5;
                jogadas.posicoes[1] = 3;
            break;
            case 8:
                jogadas.posicoes[0] = 4;
                jogadas.posicoes[1] = 6;
            break;
            case 9:
                jogadas.posicoes[0] = 1;
                jogadas.posicoes[1] = 5;
            break;
        }
    }else if(peca->codigo == 3 || peca->codigo == 6){
        //jogadas - torre (possiveis posicoes no tabuleiro para o qual a peca pode ir)
        //preenchendo os vetores com as posicoes que a peca pode ir em cada caso
        //os if's verificam em quais posicoes uma determinada peca, em cada caso, pode ir
        switch(peca->posicao_atual){
            case 1:
                if(tabuleiro->tabuleiro[0][1] == 0){
                    jogadas.posicoes[0] = 2;
                    if(tabuleiro->tabuleiro[0][2] == 0)
                        jogadas.posicoes[1] = 3;
                }
                if(tabuleiro->tabuleiro[1][0] == 0){
                    jogadas.posicoes[2] = 4;
                        if(tabuleiro->tabuleiro[2][0] == 0){
                            jogadas.posicoes[3] = 7;
                        }
                }
            break;
            case 2:
                if(tabuleiro->tabuleiro[0][0] == 0){
                    jogadas.posicoes[0] = 1;
                }

                if(tabuleiro->tabuleiro[0][2] == 0){
                    jogadas.posicoes[1] = 3;
                }

                if(tabuleiro->tabuleiro[1][1] == 0){
                    jogadas.posicoes[2] = 5;
                    if(tabuleiro->tabuleiro[2][1] == 0){
                        jogadas.posicoes[3] = 8;
                    }
                }
            break;
            case 3:
                if(tabuleiro->tabuleiro[0][1] == 0){
                    jogadas.posicoes[0] = 2;
                    if(tabuleiro->tabuleiro[0][0] == 0){
                        jogadas.posicoes[1] = 1;
                    }
                }

                if(tabuleiro->tabuleiro[1][2] == 0){
                    jogadas.posicoes[2] = 6;
                    if(tabuleiro->tabuleiro[2][2] == 0){
                        jogadas.posicoes[3] = 9;
                    }
                }
            break;
            case 4:
                if(tabuleiro->tabuleiro[1][1] == 0){
                    jogadas.posicoes[0] = 5;
                    if(tabuleiro->tabuleiro[1][2] == 0){
                        jogadas.posicoes[1] = 6;
                    }
                }

                if(tabuleiro->tabuleiro[0][0] == 0){
                    jogadas.posicoes[2] = 1;
                }

                if(tabuleiro->tabuleiro[0][2] == 0){
                    jogadas.posicoes[3] = 7;
                }
            break;
            case 5:
                if(tabuleiro->tabuleiro[0][1] == 0){
                    jogadas.posicoes[0] = 2;
                }

                if(tabuleiro->tabuleiro[1][0] == 0){
                    jogadas.posicoes[1] = 4;
                }

                if(tabuleiro->tabuleiro[1][2] == 0){
                    jogadas.posicoes[2] = 6;
                }

                if(tabuleiro->tabuleiro[2][1] == 0){
                    jogadas.posicoes[3] = 8;
                }
            break;
            case 6:
                if(tabuleiro->tabuleiro[0][2] == 0){
                    jogadas.posicoes[0] = 3;
                }

                if(tabuleiro->tabuleiro[1][1] == 0){
                    jogadas.posicoes[1] = 5;
                    if(tabuleiro->tabuleiro[1][0] == 0){
                        jogadas.posicoes[2] = 4;
                    }
                }

                if(tabuleiro->tabuleiro[2][2] == 0){
                    jogadas.posicoes[3] = 9;
                }
            break;
            case 7:
                if(tabuleiro->tabuleiro[1][0] == 0){
                    jogadas.posicoes[0] = 4;
                    if(tabuleiro->tabuleiro[0][0] == 0){
                        jogadas.posicoes[1] = 1;
                    }
                }

                if(tabuleiro->tabuleiro[2][1] == 0){
                    jogadas.posicoes[2] = 8;
                    if(tabuleiro->tabuleiro[2][2] == 0){
                        jogadas.posicoes[3] = 9;
                    }
                }
            break;
            case 8:
                if(tabuleiro->tabuleiro[2][0] == 0){
                    jogadas.posicoes[0] = 7;
                }
                if(tabuleiro->tabuleiro[1][1] == 0){
                    jogadas.posicoes[1] = 5;
                    if(tabuleiro->tabuleiro[0][1] == 0){
                        jogadas.posicoes[2] = 2;
                    }
                }

                if(tabuleiro->tabuleiro[2][2] == 0){
                    jogadas.posicoes[3] = 9;
                }
            break;
            case 9:
                if(tabuleiro->tabuleiro[2][1] == 0){
                    jogadas.posicoes[0] = 8;
                    if(tabuleiro->tabuleiro[2][0] == 0){
                        jogadas.posicoes[1] = 7;
                    }
                }
                if(tabuleiro->tabuleiro[1][2] == 0){
                    jogadas.posicoes[2] = 6;
                    if(tabuleiro->tabuleiro[0][2] == 0){
                        jogadas.posicoes[3] = 3;
                    }
                }
            break;
        }
    }

    for(i = 0; i < 4; i++){
        if(jogadas.posicoes[i] != -1){
            c = obtem_coordenada(jogadas.posicoes[i]);
            if(tabuleiro->tabuleiro[c.linha][c.coluna] == 0){
                jogadas.total++;
            }
        }
    }

    return jogadas;
}

//funcao que faz inserir as 3 pecas de cada jogador no tabuleiro
//essa funcao tambem recebe o tabuleiro e analisa as configuracoes momentaneas 
//apos inserir alguma peca no jogo
int insere_peca(Peca* peca, Tabuleiro* tabuleiro, int posicao)
{
    Coordenada c = obtem_coordenada(posicao);
    if(tabuleiro->tabuleiro[c.linha][c.coluna] == 0){
        tabuleiro->tabuleiro[c.linha][c.coluna] = peca->codigo;
        peca->esta_no_tabuleiro = 1;
        tabuleiro->pecas_no_tabuleiro++;
        peca->posicao_atual = posicao;
        return 1;
    }else{
        return 0;
    }
}

//funcao que retorna as siglas dos nomes das pecas do jogo
//CB - Cavalo Branco
//BB - Bispo Branco
//TB - Torre Branca
//CP - Cavalo Preto
//BP - Bispo Preto
//TP - Torre Preta
char* peca(int codigo)
{
    switch(codigo){
    case 1:
        return "CB";
        break;
    case 2:
        return "BB";
        break;
    case 3:
        return "TB";
        break;
    case 4:
        return "CP";
        break;
    case 5:
        return "BP";
        break;
    case 6:
        return "TP";
        break;
    }
}

//funcao que exibe o tabuleiro na tela dos jogadores
//o simbolo "#" representa uma casa branca do tabuleiro
//como eh utilizado pecas de xadrez, para adaptar o tabuleiro, seria interessante fazer uma diferenca nas casas do tabuleiro
void exibe_tabuleiro(int tabuleiro[][3])
{
    int i, j;
    for(i = 0; i < 3; i++){
        printf("+---+---+---+\n|");
        for(j = 0; j < 3; j++){
            if(tabuleiro[i][j] != 0){
                printf("%s |", peca(tabuleiro[i][j]));
            }else{
                if((i*3 + j) % 2 == 0){
                    printf(" # |");
                }else{
                    printf("   |");
                }
            }
        }
        printf("\n");
    }
    printf("+---+---+---+\n");
    return;
}

int total_pecas(int tabuleiro[0][3])
{
    int i, j, total = 0;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(tabuleiro[i][j] != 0)
                total++;
        }
    }
    return total;
}

//funcao que exibe as pecas no tabuleiro da tela dos jogadores
void exibe_pecas(Peca pecas[3])
{
    int i;
    for(i = 0; i < 3; i++)
        if(!(pecas[i].esta_no_tabuleiro))
            printf("\n\t%s - %d", pecas[i].nome, pecas[i].codigo);
    return;
}

//funcao que exibe as pecas no tabuleiro da tela dos jogadores
void exibe_pecas_jogada(Peca pecas[3])
{
    int i;
    for(i = 0; i < 3; i++)
        printf("\n\t%s - %d", pecas[i].nome, pecas[i].codigo);
    return;
}

//funcao que realiza as jogadas das pecas no tabuleiro
//essa funcao tambem verifica se uma determinada regiao ja se encontra preenchida com outra peca
//Verifica tambem se o local para aonde deseja-se mover a peca eh invalido ou nao
int realiza_jogada(Peca *peca, int posicao_destino, Tabuleiro* tabuleiro, Jogador *jogador)
{
    //retorna 1 se jogada foi feita com sucesso
    //retorna 2 se na posicao destino já tem uma peça
    //retorna 3 se a posição destino é inválida

    Jogadas jogadas = jogadas_possiveis(peca, tabuleiro);

    int i, jogada_invalida = 1, posicao_ocupada = 1;

    for(i = 0; i < 4; i++)
        if(jogadas.posicoes[i] == posicao_destino)
            jogada_invalida = 0;

    if(jogada_invalida)
        return 3;
        
    //O jogador escolhe a peca que deseja mover e escolhe a regiao
	//para o qual aquela peca ira se posicionar. Nesse caso,
	//a peca sai da coordenada de origem e vai para uma outra
	//posicao, a qual eh referida como coordenada de destino    

    Coordenada destino = obtem_coordenada(posicao_destino);
    Coordenada origem = obtem_coordenada(peca->posicao_atual);
    if(tabuleiro->tabuleiro[destino.linha][destino.coluna] != 0)
        return 2;


    tabuleiro->tabuleiro[origem.linha][origem.coluna] = 0;
    tabuleiro->tabuleiro[destino.linha][destino.coluna] = peca->codigo;
    peca->posicao_atual = posicao_destino;
    jogador->jogadas++;
    return 1;
}

int total_jogadas_possiveis(Jogador jogador, Tabuleiro tab)
{
    Jogadas jogadas_cavalo = jogadas_possiveis(&(jogador.pecas[0]), &tab);
    Jogadas jogadas_bispo = jogadas_possiveis(&(jogador.pecas[1]), &tab);
    Jogadas jogadas_torre = jogadas_possiveis(&(jogador.pecas[2]), &tab);
    return jogadas_cavalo.total + jogadas_bispo.total + jogadas_torre.total;
}

int peca_mesmo_jogador(codigo1, codigo2)
{
    switch(codigo1){
        case 1:
            return codigo2 == 2 || codigo2 == 3;
        break;
        case 2:
            return codigo2 == 1 || codigo2 == 3;
        break;
        case 3:
            return codigo2 == 1 || codigo2 == 2;
        break;
        case 4:
            return codigo2 == 5 || codigo2 == 6;
        break;
        case 5:
            return codigo2 == 4|| codigo2 == 6;
        break;
        case 6:
            return codigo2 == 4 || codigo2 == 5;
        break;
        default:
            return 0;
    }
}

//As funcoes 8 funcoes a seguir representam o preenchimento das linhas, colunas e diagonais do tabuleiro do jogo

int linha1_preenchida(Tabuleiro tabuleiro)
{
    if(peca_mesmo_jogador(tabuleiro.tabuleiro[0][0], tabuleiro.tabuleiro[0][1]) && peca_mesmo_jogador(tabuleiro.tabuleiro[0][1], tabuleiro.tabuleiro[0][2]))
        return 1;
    return 0;
}

int linha2_preenchida(Tabuleiro tabuleiro)
{
    if(peca_mesmo_jogador(tabuleiro.tabuleiro[1][0], tabuleiro.tabuleiro[1][1]) && peca_mesmo_jogador(tabuleiro.tabuleiro[1][1], tabuleiro.tabuleiro[1][2]))
        return 1;
    return 0;
}

int linha3_preenchida(Tabuleiro tabuleiro)
{
    if(peca_mesmo_jogador(tabuleiro.tabuleiro[2][0], tabuleiro.tabuleiro[2][1]) && peca_mesmo_jogador(tabuleiro.tabuleiro[2][1], tabuleiro.tabuleiro[2][2]))
        return 1;
    return 0;
}

int coluna1_preenchida(Tabuleiro tabuleiro)
{
    if(peca_mesmo_jogador(tabuleiro.tabuleiro[0][0], tabuleiro.tabuleiro[1][0]) && peca_mesmo_jogador(tabuleiro.tabuleiro[1][0], tabuleiro.tabuleiro[2][0]))
        return 1;
    return 0;
}

int coluna2_preenchida(Tabuleiro tabuleiro)
{
    if(peca_mesmo_jogador(tabuleiro.tabuleiro[0][1], tabuleiro.tabuleiro[1][1]) && peca_mesmo_jogador(tabuleiro.tabuleiro[1][1], tabuleiro.tabuleiro[2][1]))
        return 1;
    return 0;
}

int coluna3_preenchida(Tabuleiro tabuleiro)
{
    if(peca_mesmo_jogador(tabuleiro.tabuleiro[0][2], tabuleiro.tabuleiro[1][2]) && peca_mesmo_jogador(tabuleiro.tabuleiro[1][2], tabuleiro.tabuleiro[2][2]))
        return 1;
    return 0;
}

int diagonal_principal_preenchida(Tabuleiro tabuleiro)
{
    if(peca_mesmo_jogador(tabuleiro.tabuleiro[0][0], tabuleiro.tabuleiro[1][1]) && peca_mesmo_jogador(tabuleiro.tabuleiro[1][1], tabuleiro.tabuleiro[2][2]))
        return 1;
    return 0;
}

int diagonal_secundaria_preenchida(Tabuleiro tabuleiro)
{
    if(peca_mesmo_jogador(tabuleiro.tabuleiro[0][2], tabuleiro.tabuleiro[1][1]) && peca_mesmo_jogador(tabuleiro.tabuleiro[1][1], tabuleiro.tabuleiro[2][0]))
        return 1;
    return 0;
}

//funcao principal
int main ()
{
    Tabuleiro tabuleiro = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0};
    Peca pecas_j1[3], pecas_j2[3];

    pecas_j1[0].codigo = 1;
    pecas_j1[0].esta_no_tabuleiro = 0;
    pecas_j1[0].posicao_atual =  -1;
    strcpy(pecas_j1[0].nome, "CAVALO BRANCO");

    pecas_j1[1].codigo = 2;
    pecas_j1[1].esta_no_tabuleiro = 0;
    strcpy(pecas_j1[1].nome, "BISPO BRANCO");
    pecas_j1[1].posicao_atual =  -1;

    pecas_j1[2].codigo = 3;
    pecas_j1[2].esta_no_tabuleiro = 0;
    strcpy(pecas_j1[2].nome, "TORRE BRANCA");
    pecas_j1[2].posicao_atual =  -1;

    pecas_j2[0].codigo = 4;
    pecas_j2[0].esta_no_tabuleiro = 0;
    strcpy(pecas_j2[0].nome, "CAVALO PRETO");
    pecas_j2[0].posicao_atual =  -1;


    pecas_j2[1].codigo = 5;
    pecas_j2[1].esta_no_tabuleiro = 0;
    strcpy(pecas_j2[1].nome, "BISPO PRETO");
    pecas_j2[1].posicao_atual =  -1;

    pecas_j2[2].codigo = 6;
    pecas_j2[2].esta_no_tabuleiro = 0;
    strcpy(pecas_j2[2].nome, "TORRE PRETA");
    pecas_j2[2].posicao_atual =  -1;


    Jogador j1 = {{pecas_j1[0], pecas_j1[1], pecas_j1[2]}, 0};
    Jogador j2 = {{pecas_j2[0], pecas_j2[1], pecas_j2[2]}, 0};


    int peca_escolhida, posicao, resultado_insercao, resultado_jogada;

    while(tabuleiro.pecas_no_tabuleiro < 6){
        //momentos de insercao das pecas do jogador 1 no tabuleiro
        //o jogador devera, nas tres primeiras jogadas, colocar todas
        //as suas pecas no tabuleiro
        LIMPATELA;
        exibe_tabuleiro(tabuleiro.tabuleiro);
        printf("\nJogador 1, qual peca gostaria de por no tabuleiro? ");
        exibe_pecas(j1.pecas);
        printf("\n>> ");
        scanf("%d", &peca_escolhida);
        fflush(stdin);
        if(peca_escolhida < 1 || peca_escolhida > 3){
            while(peca_escolhida < 1 || peca_escolhida > 3){
                printf("NUMERO INVALIDO!\nDigite outro: \n>> ");
                scanf("%d", &peca_escolhida);
                fflush(stdin);
            }
        }else if(j1.pecas[peca_escolhida - 1].esta_no_tabuleiro){
            while(j1.pecas[peca_escolhida - 1].esta_no_tabuleiro){
                printf("NUMERO INVALIDO!\nDigite outro: \n>> ");
                scanf("%d", &peca_escolhida);
                fflush(stdin);
            }
        }
        printf("Digite a posicao do tabuleiro na qual deseja inserir a peca %s?\n>> ", j1.pecas[peca_escolhida - 1].nome);
        scanf("%d", &posicao);
        fflush(stdin);
        if(posicao < 1 || posicao > 9){
        	//loop infinito, caso o jogador nao digitar os numeros que estao em alcance
            while(posicao < 1 || posicao > 9){
                printf("POSICAO INVALIDA! Digite uma posicao valida\n>> ");
                scanf("%d", &posicao);
            }
        }
        if((insere_peca(&(j1.pecas[peca_escolhida - 1]), &tabuleiro, posicao)) == 0){
            while((insere_peca(&(j1.pecas[peca_escolhida - 1]), &tabuleiro, posicao)) == 0){
                printf("POSICAO JA OCUPADA! Digite uma posicao vazia\n>> ");
                scanf("%d", &posicao);
                if(posicao < 1 || posicao > 9){
                    while(posicao < 1 || posicao > 9){
                        printf("POSICAO INVALIDA! Digite uma posicao valida\n>> ");
                        scanf("%d", &posicao);
                    }
                }
            }
        }
        //momento de insercao das pecas do jogador 2 no tabuleiro
        LIMPATELA;
        exibe_tabuleiro(tabuleiro.tabuleiro);
        printf("\nJogador 2, qual peca gostaria de por no tabuleiro? ");
        exibe_pecas(j2.pecas);
        printf("\n>> ");
        scanf("%d", &peca_escolhida);
        fflush(stdin);
        if(peca_escolhida < 4 || peca_escolhida > 6){
            while(peca_escolhida < 4 || peca_escolhida > 6){
                printf("NUMERO INVALIDO!\nDigite outro: \n>> ");
                scanf("%d", &peca_escolhida);
                fflush(stdin);
            }
        }else if(j2.pecas[peca_escolhida - 4].esta_no_tabuleiro){
            while(j2.pecas[peca_escolhida - 4].esta_no_tabuleiro){
                printf("NUMERO INVALIDO!\nDigite outro: \n>> ");
                scanf("%d", &peca_escolhida);
                fflush(stdin);
            }
        }
        printf("Digite a posicao do tabuleiro na qual deseja inserir a peca %s?\n>> ", j2.pecas[peca_escolhida - 4].nome);
        scanf("%d", &posicao);
        fflush(stdin);
        if(posicao < 1 || posicao > 9){
            while(posicao < 1 || posicao > 9){
                printf("POSICAO INVALIDA! Digite uma posicao valida\n>> ");
                scanf("%d", &posicao);
            }
        }
        if((insere_peca(&(j2.pecas[peca_escolhida - 4]), &tabuleiro, posicao)) == 0){
            while((insere_peca(&(j2.pecas[peca_escolhida - 4]), &tabuleiro, posicao)) == 0){
                printf("POSICAO JA OCUPADA! Digite uma posicao vazia\n>> ");
                scanf("%d", &posicao);
                if(posicao < 1 || posicao > 9){
                    while(posicao < 1 || posicao > 9){
                        printf("POSICAO INVALIDA! Digite uma posicao valida\n>> ");
                        scanf("%d", &posicao);
                    }
                }
            }
        }
    }

    LIMPATELA;
    printf("As pecas foram colocadas no tabuleiro.\nPressione qualquer tecla para continuar...\n\n");
    getchar();

    int empate = 0, vencedor = 0, vez = 1;

    //jogo iniciado
    while(1){
        if(total_jogadas_possiveis(j1, tabuleiro) == 0 || total_jogadas_possiveis(j2, tabuleiro) == 0){
            empate = 1;
            break;
        }

        if(vez == 1){
            LIMPATELA;
            exibe_tabuleiro(tabuleiro.tabuleiro);
            printf("\n\nJogador 1, qual peca deseja mover? ");
            exibe_pecas_jogada(j1.pecas);
            printf("\n\n");
            scanf("%d", &peca_escolhida);
            if(peca_escolhida >= 1 && peca_escolhida <=3){
                //se chegou nessa parte, o jogador 1 tem, pelo menos, uma peça com jogadas possíveis
                Jogadas jogadas = jogadas_possiveis(&(j1.pecas[peca_escolhida-1]), &tabuleiro);
                if(jogadas.total == 0){
                    printf("NAO HA JOGADAS DISPONIVEIS PARA A PECA ESCOLHIDA! ESCOLHA OUTRA!\n");
                    //espera
                    espera();
                    vez = 1;
                    continue;
                }

                printf("Digite a posicao para a qual deseja mover a peca %s\n>> ", j1.pecas[peca_escolhida-1].nome);
                scanf("%d", &posicao);
                if(posicao >= 1 && posicao <= 9){
                    resultado_jogada = realiza_jogada(&(j1.pecas[peca_escolhida-1]), posicao, &tabuleiro, &j1);
                    if(resultado_jogada != 1){
                        switch(resultado_jogada){
                            case 2:
                                printf("A POSICAO ESCOLHIDA JA TEM UMA PECA!\n");
                            break;
                            case 3:
                                printf("ESTA JOGADA EH INVALIDA PARA A PECA ESCOLHIDA!\n");
                            break;
                        }
                        espera();
                        vez = 1;
                        continue;
                    }else{
                        printf("JOGADA REALIZADA COM SUCESSO!\n");
                        espera();
                        vez = 2;
                        if(diagonal_principal_preenchida(tabuleiro) || diagonal_secundaria_preenchida(tabuleiro)){
                            vencedor = 1;
                            break;
                        }

                        if(linha1_preenchida(tabuleiro) || linha2_preenchida(tabuleiro)){
                            vencedor = 1;
                            break;
                        }

                        if(linha3_preenchida(tabuleiro) || coluna1_preenchida(tabuleiro)){
                            vencedor = 1;
                            break;
                        }

                        if(coluna2_preenchida(tabuleiro) || coluna3_preenchida(tabuleiro)){
                            vencedor = 1;
                            break;
                        }
                    }
                }else{
                    printf("ESTA POSICAO E INVALIDA!\n");
                    espera();
                    vez = 1;
                    continue;
                }
            }else{
                printf("PECA INVALIDA!\n");
                espera();
                vez = 1;
                continue;
            }
        }else if(vez == 2){
            LIMPATELA;
            exibe_tabuleiro(tabuleiro.tabuleiro);
            printf("\n\nJogador 2, qual peca deseja mover? ");
            exibe_pecas_jogada(j2.pecas);
            printf("\n\n");
            scanf("%d", &peca_escolhida);
            if(peca_escolhida >= 4 && peca_escolhida <=6){
                //se chegou nessa parte, o jogador 1 tem, pelo menos, uma peça com jogadas possíveis
                Jogadas jogadas = jogadas_possiveis(&(j2.pecas[peca_escolhida-4]), &tabuleiro);
                if(jogadas.total == 0){
                    printf("NAO HA JOGADAS DISPONIVEIS PARA A PECA ESCOLHIDA! ESCOLHA OUTRA!\n");
                    espera();
                    vez = 2;
                    continue;
                }

                printf("Digite a posicao para a qual deseja mover a peca %s\n>> ", j2.pecas[peca_escolhida-4].nome);
                scanf("%d", &posicao);
                if(posicao >= 1 && posicao <= 9){
                    resultado_jogada = realiza_jogada(&(j2.pecas[peca_escolhida-4]), posicao, &tabuleiro, &j2);
                    if(resultado_jogada != 1){
                        switch(resultado_jogada){
                            case 2:
                                printf("A POSICAO ESCOLHIDA JA TEM UMA PECA!\n");
                            break;
                            case 3:
                                printf("ESTA JOGADA EH INVALIDA PARA A PECA ESCOLHIDA!\n");
                            break;
                        }
                        espera();
                        vez = 2;
                        continue;
                    }else{
                        printf("JOGADA REALIZADA COM SUCESSO!\n");
                        espera();
                        vez = 1;

                        if(diagonal_principal_preenchida(tabuleiro) || diagonal_secundaria_preenchida(tabuleiro)){
                            vencedor = 1;
                            break;
                        }

                        if(linha1_preenchida(tabuleiro) || linha2_preenchida(tabuleiro)){
                            vencedor = 1;
                            break;
                        }

                        if(linha3_preenchida(tabuleiro) || coluna1_preenchida(tabuleiro)){
                            vencedor = 1;
                            break;
                        }

                        if(coluna2_preenchida(tabuleiro) || coluna3_preenchida(tabuleiro)){
                            vencedor = 1;
                            break;
                        }
                    }
                }else{
                    printf("ESTA POSICAO E INVALIDA!\n");
                    espera();
                    vez = 2;
                    continue;
                }
            }else{
                printf("PECA INVALIDA!\n");
                espera();
                vez = 2;
                continue;
            }
        }
    }

    printf("\nRESULTADO\n");
    if(empate == 1){
        printf("O JOGO TERMINOU EMPATADO!\n");
    }else{
        if(vencedor == 1){
            printf("O JOGADOR 1 FOI O VENCEDOR, COM %d JOGADAS.\n", j1.jogadas);
        }else{
            printf("O JOGADOR 2 FOI O VENCEDOR, COM %d JOGADAS.\n", j2.jogadas);
        }
    }

    return 0;
}


