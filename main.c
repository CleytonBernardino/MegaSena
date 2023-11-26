#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --------------------- CONFIGURAÇÕES ---------------------

// Quantidade de sorteio a serem realizados 
#define NUMLIMIT 5000

// Define a quantidade de digitos por jogo
#define NUMPORJOGO 6

// Número maximo a ser gerado
#define MAXNUM 60

// Define a quantidade de usuarios a serem cadastrado
#define NUMDEJOGADOR 1

/* Para aumentar a quantidade de chars para o nome, deve-se ir no coletarUsuarios,
e alterar o valor do scanf para o novo valor de char, e alterar o valor do usuarios nome também. */

// --------------- FIM DAS CONFIGURAÇÕES ---------------------

// Adiciona mais um ao número maximo para ignora o 0
#define NUMMAX (MAXNUM + 1)

// Declara a lista de jogos
int jogos[NUMLIMIT][NUMPORJOGO + 1] = {};

// Define a lista de usuarios
int usuarios[NUMDEJOGADOR][NUMPORJOGO + 1] = {};
char usuarioNome[NUMDEJOGADOR][30];

// Gera um número aleatorio
int geraNumero() {
    return (rand() % MAXNUM) + 1;
}

// Remove números repetidos
void removerRepetidos(int indice) {
    int lin = NUMPORJOGO - 1; // Tamanho maximo de números em uma lista

    for (int linha = 0; linha < NUMPORJOGO; linha++){ // Intera sobre a linha
        for (int plinha = lin; plinha != 0; plinha--) { // Intera sobre a prox linha
            if (plinha == linha) {
                continue;
            }

            if (jogos[indice][linha] == jogos[indice][plinha]){ // Verifica se a números repetidos
                jogos[indice][plinha] = geraNumero(); // remove números repetidos
            }
        }
    }
}

// Organiza os jogos em ordem crescente
void organizarJogo(int indice) {
    int linha, l, menor;
    for (linha = 0; linha < NUMPORJOGO; linha++) {
        menor  = jogos[indice][linha];
        for (l = linha + 1; l < NUMPORJOGO ; l++) {
            if (menor > jogos[indice][l]) {
                menor = jogos[indice][l];
                jogos[indice][l] = jogos[indice][linha];
                jogos[indice][linha] = menor;
            }
        }
    }
}

// Exibe a sequencia de números até o limite definido
void exibirSequencia() {
    printf("\nSequencia de números até: %d\n", NUMLIMIT);
    int indice, linha;
    for (indice=0; indice < NUMLIMIT; indice++) {
        printf("Sequencia %d: ", indice + 1);
        for (linha=0; linha < NUMPORJOGO; linha++) {
            printf("%d ", jogos[indice][linha]);
        }
        printf("\n");
    }
}

// Exibe a quantidade de vezes que um número aparece
void qtdNumSequencia() {
    printf("\nQuantidade de vezes que um número aparece\n");
    int numeros[NUMMAX][1] = {};

    for (int indice = 0; indice < NUMLIMIT; indice++){
        for (int linha = 0; linha < NUMPORJOGO; linha++) {
           numeros[jogos[indice][linha]][0]++;
        }
    }

    for (int indice = 1; indice <= NUMMAX; indice++){
        printf("Número %d = %d vezes.\n", indice, numeros[indice][0]);
    }
}


// Exibe as 15 duplas que mais sairam
void listarQuinzeDuplas() {
    printf("\nAs 15 duplas que mais sairam\n");
    int indice, linha, aux;
    int duplas[NUMMAX][NUMMAX] = {};
    int quinzeDuplas[15][3] = {};

    for (indice = 1; indice < NUMLIMIT; indice++) {
        for (linha = 0; linha < (NUMPORJOGO - 1); linha++) {
            duplas[jogos[indice][linha]][jogos[indice][linha + 1]]++;
        }
    }

    for (aux = 0; aux < 15; aux++) {
        for (indice = 1; indice < NUMMAX; indice++) {
            for (linha = 0; linha < NUMMAX; linha++) {
                if (duplas[indice][linha] > quinzeDuplas[aux][0]) {
                    quinzeDuplas[aux][0] = duplas[indice][linha];
                    quinzeDuplas[aux][1] = indice;
                    quinzeDuplas[aux][2] = linha;
                }    
            }
        }
        duplas[quinzeDuplas[aux][1]][quinzeDuplas[aux][2]] = 0;
    }

    for (indice = 1; indice < 15; indice++) {
        printf("Números %d e %d = %d vezes.\n", quinzeDuplas[indice][1], quinzeDuplas[indice][2], quinzeDuplas[indice][0]);
    }
}


// Exibe os 15 números que mais sairam
void listaOsQuinzeMais() {
    printf("\nO Quinze que mais sairam\n");
    int numeros[NUMMAX][1] = {};
    int maisAparece[15][4] = {};
    int indice, linha, aux;

    for (indice = 0; indice < NUMLIMIT; indice++){
        for (linha = 0; linha < NUMPORJOGO; linha++) {
           numeros[jogos[indice][linha]][0]++;
        }
    }

    for (indice = 1; indice < NUMMAX; indice++){
        aux = 0;
        for (int i = 0; i < 15; i++) {
            if (aux || numeros[indice][0] > maisAparece[i][1]){
                if (aux) {
                    maisAparece[i][3] = maisAparece[i][1];
                    maisAparece[i][2] = maisAparece[i][0];
                    maisAparece[i][1] = maisAparece[i - 1][3];
                    maisAparece[i][0] = maisAparece[i - 1][2];
                    continue;
                }
                maisAparece[i][3] = maisAparece[i][1];
                maisAparece[i][2] = maisAparece[i][0];
                maisAparece[i][1] = numeros[indice][0];
                maisAparece[i][0] = indice;
                aux = 1;
            }
        }
    }


    for (indice = 0; indice < 15; indice++) {
        printf("Número %d = %d vezes.\n", maisAparece[indice][0], maisAparece[indice][1]);
    }

}


// Exibe a quantidade de sorteios que um número não aparece
void listarSorteios() {
    printf("\nUtima vez que o número saiu\n");
    int utimaVez[NUMMAX][1] = {};

    for (int indice=0; indice < NUMLIMIT; indice++) {
        for (int i = 1; i < NUMMAX; i++) {
            utimaVez[i][0]++;
        }
        for (int linha=0; linha < NUMPORJOGO; linha++) {
            utimaVez[jogos[indice][linha]][0] = 0;
        }
    }

    for (int sorteio=1; sorteio < NUMMAX; sorteio++) {
        if (utimaVez[sorteio][0] == 0) {
            printf("No %d = saiu no último sorteio.\n", sorteio);
            continue;
        }
        printf("No %d = não sai a %d sorteios seguidos.\n", sorteio, utimaVez[sorteio][0]);
    }
}


// Coleta os usuarios e seus jogos
void coletarUsuarios() {
    int numUser;
    int aux = 0;
    for (numUser=0; numUser < NUMDEJOGADOR; numUser++) {
        printf("Digite o nome do usuario %dª usuario: ", (numUser + 1));
        scanf("%30[^\n]", usuarioNome[numUser]); // Lê o nome do usuario até o enter ser pressionado ou atigir o limite de char

        printf("\nDigite o CPF do usuario %dª usuario: ", (numUser + 1));
        scanf("%d", &usuarios[numUser][0]);

        printf("\nAgora escolha 6 números de 1 a 60, Aperte enter a cada número digitado.");
        for (int num=1; num <= NUMPORJOGO; num++) {
            printf("\nDigite o %dª número: ", num);
            scanf("%d", &aux);
            if (aux > 60 || aux <= 0) {
                printf("\nNúmero invalido, digite novamente: ");
                num--;
                continue;
            }
            for (int repetido = 1; repetido < (NUMPORJOGO + 1); repetido++) {
                if (usuarios[numUser][repetido] == aux) {
                    printf("\nEsté número já foi utilizado neste sorteio escolha outro: ");
                    num--;
                    continue;
                }
            }
            usuarios[numUser][num] = aux;
        }
        printf("\n");
        scanf("%*c"); // Impede que o enter seja lido como um char
    }
}


// Classifica os ganhadores
void classificarGanhadores() {
    printf("\nQuantidade de pontos por usuario.");
    int sorteios[NUMDEJOGADOR][2] = {};
    int indice, linha, jogo, acertos;
    int i, j, maior, aux;
    for (indice=0; indice < NUMLIMIT; indice++) {
        for (i=0; i < NUMDEJOGADOR; i++) {
            acertos = 0;
            for (linha=0; linha < NUMPORJOGO; linha++) {
                jogo = jogos[indice][linha];
                for (j=1; j <= NUMPORJOGO; j++) {
                    if (jogo == usuarios[i][j]) {
                        acertos++;
                    }
                }
            }
            if (acertos > sorteios[i][0]) {
                    sorteios[i][0] = acertos;
                    sorteios[i][1] = indice;
            }
        }
        
    }

    maior = sorteios[0][0];
    for (indice=0; indice < NUMDEJOGADOR; indice++) {
        for (i=0; i < NUMDEJOGADOR; i++) {
            if (maior < sorteios[indice][0]) {
                maior = sorteios[indice][0];
            }
        }
        printf("\nParabéns, %s você acertou %d números! No sorteio %d.\n", usuarioNome[indice], sorteios[indice][0], (sorteios[indice][1] + 1));
        printf("Sorteio nº %d: ", sorteios[indice][1] + 1);
        for (linha=0; linha < NUMPORJOGO; linha++) {
            printf("%d ", jogos[sorteios[indice][1]][linha]);
        }
        printf("\n");
    }
}

int main(void) {
    srand(time(NULL)); // Define a semente para gerar números aleatorios

    coletarUsuarios();
    for (int indice=0; indice < NUMLIMIT; indice++) {
        for (int linha=0; linha < NUMPORJOGO; linha++) {
            jogos[indice][linha] = geraNumero();
        }
        removerRepetidos(indice);
        organizarJogo(indice);
    }

    exibirSequencia();
    qtdNumSequencia();
    listaOsQuinzeMais();
    listarSorteios();
    listarQuinzeDuplas();
    classificarGanhadores();

    return 0;
} 
