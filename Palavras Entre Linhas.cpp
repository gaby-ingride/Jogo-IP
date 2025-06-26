/* ==================== BIBLIOTECAS NECESS�RIAS ==================== */
#include <stdio.h>       // Para fun��es de entrada/sa�da (printf, scanf, fgets)
#include <stdlib.h>      // Para aloca��o de mem�ria, sistema, n�meros aleat�rios
#include <string.h>      // Para manipula��o de strings (strcmp, strlen)
#include <time.h>        // Para medi��o e controle de tempo
#include <locale.h>      // Para configura��o regional (caracteres especiais)
#include <windows.h>     // Para fun��es espec�ficas do Windows (Sleep)
#include <ctype.h>       // Para verifica��o de tipos de caracteres
#include <stdbool.h>     // Para uso de valores booleanos (true/false)
#include <conio.h>       // Para leitura de teclado n�o-bloqueante

/* ==================== CONSTANTES GLOBAIS ==================== */
#define MAXIMO_NOME 50           // Tamanho m�ximo para nome do jogador
#define MAXIMO_RANKING 100       // Capacidade m�xima do ranking

/* ==================== ESTRUTURAS DE DADOS ==================== */

// Estrutura principal do jogo
typedef struct {
    int pontuacao;               // Pontua��o acumulada do jogador
    int tempo_limite;            // Dura��o do n�vel em segundos
} Jogo;

Jogo jogo;  // Inst�ncia global do jogo

/* ==================== CONFIGURA��ES DO JOGO ==================== */

// Sistema de pontua��o
#define PONTUACAO_FACIL 50       // Pontos por palavra f�cil acertada
#define PONTUACAO_MEDIO 100      // Pontos por palavra m�dia acertada
#define PONTUACAO_DIFICIL 100    // Pontos por palavra dif�cil acertada
#define PONTUACAO_TRYHARD 150    // Pontos por tradu��o correta

// Dura��o dos n�veis (em segundos)
const int TEMPO_FACIL = 60;      // Dura��o do n�vel f�cil
const int TEMPO_MEDIO = 60;      // Dura��o do n�vel m�dio
const int TEMPO_DIFICIL = 60;    // Dura��o do n�vel dif�cil
const int TEMPO_TRYHARD = 60;    // Dura��o do modo tryhard

/* ==================== BANCO DE DADOS DE PALAVRAS ==================== */

// Conjunto de palavras f�ceis (curtas)
const char *palavras_faceis[] = {
    "agua", "avido", "ceu", "coracao", "facao",
    "firmeza", "gloria", "habito", "impeto", "joia",
    "lapis", "lagrima", "mare", "nausea", "orgao",
    "passaro", "pe", "radio", "saude", "torax",
    "umido", "volei", "xicara", "zambia", "ambar",
    "bencao", "ciume", "dolar", "exito", "folego",
    "guria", "hifen", "juri", "magoa", "nodoa",
    "publico", "quorum", "regua", "subito", "tenue",
    "utero", "venus", "bonus", "camera", "duvida",
    "femea", "genio", "hibrido"
};
const int total_palavras_faceis = 47;  // Quantidade de palavras f�ceis

// Conjunto de palavras m�dias
const char *palavras_medianas[] = {
    "acordao", "aerobico", "ambiguo", "amnesia", "antidoto",
    "apendice", "arduo", "autentico", "bacteriofago", "catastrofe",
    "comercio", "compondo", "cranio", "cronometro", "demonio",
    "desagravo", "efemero", "embriao", "estereo", "excentrico",
    "farmaceutico", "fenomeno", "filantropico", "fosforo", "glorioso",
    "harmonico", "heroico", "hidrometro", "historico", "identico",
    "imperio", "incendio", "individuo", "inocuo", "intrinseco",
    "jubileu", "latifundio", "magnetico", "metafora", "miopia",
    "neurotico", "obstaculo", "origem", "parametro", "patetico",
    "quilometro", "refrao", "reporter", "sincero", "textil"
};
const int total_palavras_medianas = 50; // Quantidade de palavras m�dias

// Conjunto de palavras dif�ceis (longas e complexas)
const char *palavras_dificeis[] = {
    "anticonstitucionalissimo", "circunspecto", "desproporcionalidade",
    "heterogeneidade", "inconstitucionalidade", "interdisciplinaridade",
    "otorrinolaringologista", "paralelepipedo", "prognosticabilidade",
    "quarentenario", "revolucionariamente", "transcendentalismo",
    "incompreensibilidade", "desenvolvimentista", "contemporaneidade",
    "desnecessariamente", "espontaneidade", "fisiopatologico",
    "gastroenterologia", "hipoteticamente", "idiossincrasia",
    "jurisprudencial", "laboratorialmente", "metalinguistico",
    "neocapitalismo", "objetivamente", "psicossomatico", "quintessencia",
    "reconhecidamente", "socioeconomico", "termoelectricidade",
    "ultraconservador", "veterinariamente", "xenotransplante",
    "zoologicamente", "antropomorfico", "biodiversidade",
    "cinematografico", "desumanizadamente", "eclesiasticamente",
    "fotossensibilidade", "geometricamente", "historiograficamente",
    "indiscriminadamente", "jurisdicionalmente", "lexicograficamente",
    "matematicamente", "neoliberalismo", "obstetricamente"
};
const int total_palavras_dificeis = 50; // Quantidade de palavras dif�ceis

// Estrutura para pares de tradu��o (ingl�s-portugu�s)
typedef struct {
    const char *ingles;         // Palavra em ingl�s
    const char *portugues;      // Tradu��o correta em portugu�s
} Vocabulario;

// Banco de dados de tradu��es para o modo tryhard
const Vocabulario palavras_tryhard[] = {
    {"apple", "maca"}, {"book", "livro"}, {"computer", "computador"},
    {"water", "agua"}, {"house", "casa"}, {"dog", "cachorro"},
    {"cat", "gato"}, {"sun", "sol"}, {"moon", "lua"}, {"tree", "arvore"},
    {"car", "carro"}, {"friend", "amigo"}, {"school", "escola"},
    {"time", "tempo"}, {"food", "comida"}, {"city", "cidade"},
    {"country", "pais"}, {"music", "musica"}, {"love", "amor"},
    {"world", "mundo"}, {"hello", "ola"}, {"goodbye", "adeus"},
    {"thank you", "obrigado"}, {"please", "por favor"}, {"sorry", "desculpa"},
    {"happy", "feliz"}, {"sad", "triste"}, {"big", "grande"}, {"small", "pequeno"},
    {"hot", "quente"}, {"cold", "frio"}, {"new", "novo"}, {"old", "velho"},
    {"good", "bom"}, {"bad", "ruim"}, {"beautiful", "bonito"}, {"ugly", "feio"},
    {"fast", "rapido"}, {"slow", "lento"}, {"strong", "forte"}, {"weak", "fraco"},
    {"man", "homem"}, {"woman", "mulher"}, {"child", "crianca"}, {"family", "familia"},
    {"work", "trabalho"}, {"home", "casa"}, {"money", "dinheiro"}, {"life", "vida"}
};
const int total_palavras_tryhard = 50; // Quantidade de pares de tradu��o

/* ==================== FUN��ES AUXILIARES ==================== */

/**
 * Fun��o para leitura de entrada com tempo limitado
 * Par�metros:
 *   - entrada: buffer para armazenar o texto digitado
 *   - tamanho: tamanho m�ximo do buffer
 *   - inicio: momento em que a contagem come�ou
 *   - limite_segundos: tempo m�ximo permitido
 * Retorno:
 *   - true se o usu�rio completou a entrada
 *   - false se o tempo esgotou
 */
bool leitura_nao_bloqueante(char *entrada, int tamanho, time_t inicio, int limite_segundos) {
    int indice = 0;
    char caractere;
    entrada[0] = '\0'; // Inicializa string vazia

    while (difftime(time(NULL), inicio) < limite_segundos) {
        if (_kbhit()) { // Verifica se h� tecla pressionada
            caractere = _getch(); // L� o caractere sem eco
            
            if (caractere == '\r') { // Enter pressionado
                entrada[indice] = '\0'; // Finaliza a string
                printf("\n");
                return true;
            } else if (caractere == '\b' && indice > 0) { // Backspace
                indice--;
                printf("\b \b"); // Apaga o caractere no console
            } else if (isprint(caractere) && indice < tamanho - 1) { // Caractere imprim�vel
                entrada[indice++] = caractere;
                printf("%c", caractere); // Exibe o caractere
            }
        }
        Sleep(10); // Pequena pausa para evitar uso excessivo da CPU
    }
    printf("\nTempo esgotado!\n");
    return false;
}

/**
 * Salva a pontua��o do jogador no arquivo de ranking
 * Par�metros:
 *   - arquivo: nome do arquivo de ranking
 *   - nome: nome do jogador
 *   - pontuacao: pontua��o a ser salva
 */
void salvar_ranking(const char *arquivo, const char *nome, int pontuacao) {
    FILE *arquivo_ranking;
    arquivo_ranking = fopen(arquivo, "a"); // Abre para adi��o
    if (!arquivo_ranking) return;
    
    fprintf(arquivo_ranking, "%s;%d\n", nome, pontuacao);
    fclose(arquivo_ranking);
}

/**
 * Exibe o ranking de pontua��es a partir de um arquivo
 * Par�metros:
 *   - arquivo: nome do arquivo de ranking a ser lido
 */
void mostrar_ranking(const char *arquivo) {
    FILE *arquivo_ranking;
    
    // Estrutura para armazenar registros do ranking
    typedef struct {
        char nome[MAXIMO_NOME];
        int pontos;
    } RegistroRanking;

    RegistroRanking lista_ranking[MAXIMO_RANKING];
    int contador = 0;

    arquivo_ranking = fopen(arquivo, "r");
    if (!arquivo_ranking) {
        printf("Nenhum recorde salvo ainda.\n");
        return;
    }

    // L� todos os registros do arquivo
    while (fscanf(arquivo_ranking, "%[^;];%d\n", 
           lista_ranking[contador].nome, 
           &lista_ranking[contador].pontos) == 2 && 
           contador < MAXIMO_RANKING) {
        contador++;
    }
    fclose(arquivo_ranking);

    // Ordena os registros por pontua��o (decrescente)
    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            if (lista_ranking[j].pontos > lista_ranking[i].pontos) {
                RegistroRanking temporario = lista_ranking[i];
                lista_ranking[i] = lista_ranking[j];
                lista_ranking[j] = temporario;
            }
        }
    }

    // Exibe o top 5
    printf("\n===== TOP 5 RECORDES =====\n");
    for (int i = 0; i < contador && i < 5; i++) {
        printf("%d. %s - %d pontos\n", i + 1, 
               lista_ranking[i].nome, 
               lista_ranking[i].pontos);
    }
    printf("==========================\n");
}

/* =================== MENSAGEM FINAL =================== */

void mostrar_mensagem_final(int pontos) {
    printf("\n--- Resultado da Miss�o ---\n");
    if (pontos < 600) {
        printf("Voc� n�o conseguiu disseminar sua l�ngua.\n");
        printf("Os alien�genas inimigos interferiram demais na comunica��o,\n");
        printf("impedindo que sua mensagem fosse compreendida.\n");
        printf("Tente novamente para melhorar sua habilidade e vencer a interfer�ncia!\n");
    } else if (pontos < 1000) {
        printf("Voc� resistiu � interfer�ncia dos alien�genas.\n");
        printf("Sua l�ngua come�ou a se espalhar, mas ainda h� muitos desafios pela frente.\n");
        printf("Continue praticando para fortalecer sua comunica��o!\n");
    } else {
        printf("Voc� foi bem sucedido em disseminar sua l�ngua!\n");
        printf("A mensagem foi clara e compreendida pelos povos alien�genas.\n");
        printf("Parab�ns, astronauta! Sua miss�o avan�ou com grande �xito.\n");
    }
    printf("---------------------------\n");
}

void mostrar_historia() {
    system("cls");
    printf("=== CARTA PARA O ASTRONAUTA ===\n\n");
    printf("Em um futuro n�o muito distante, a humanidade expandiu suas fronteiras\n");
    printf("para al�m do Sistema Solar, descobrindo planetas habitados por\n");
    printf("civiliza��es alien�genas fascinantes. No entanto, a falta de comunica��o\n");
    printf("entre as esp�cies gera desconfian�a e conflitos.\n\n");
    
    printf("� a� que entra voc� - um Astronauta Pr�-Interconhecimento determinado\n");
    printf("a mudar esse cen�rio. Sua miss�o � pac�fica: viajar de planeta em planeta\n");
    printf("ensinando os idiomas da Terra aos alien�genas, criando pontes culturais\n");
    printf("e fortalecendo a harmonia intergal�ctica. Seu sonho � um universo onde\n");
    printf("todas as esp�cies possam se entender.\n\n");
    
    printf("Por�m, nem todos apoiam sua iniciativa. A Pol�cia Intergal�ctica, uma\n");
    printf("organiza��o autorit�ria que controla o fluxo de informa��es entre os\n");
    printf("planetas, v� seu trabalho como uma amea�a � \"ordem c�smica\". Eles\n");
    printf("acreditam que o conhecimento lingu�stico pode dar poder demais �s\n");
    printf("civiliza��es menos desenvolvidas e come�am a ca��-lo.\n\n");
    
    printf("Agora, voc� precisa ensinar de forma r�pida e secreta, visitando planetas\n");
    printf("sob o radar da pol�cia. Cada fase do jogo representa um novo mundo, onde\n");
    printf("voc� tem um tempo limitado para ensinar palavras e frases antes que os\n");
    printf("oficiais intergal�cticos cheguem.\n\n");
    
    printf("Sua coragem pode mudar o destino da comunica��o intergal�ctica!\n\n");
    
    system("pause");
}

/* ==================== FUN��ES PRINCIPAIS DO JOGO ==================== */

/**
 * Controla a execu��o dos modos Normal (F�cil, M�dio, Dif�cil)
 * Par�metros:
 *   - dificuldade: n�vel selecionado (1-F�cil, 2-M�dio, 3-Dif�cil)
 */
void jogar_modo_normal(int dificuldade) {
    const char **banco_palavras;
    int total_palavras;
    int pontos_por_palavra;
    const char *nome_dificuldade;
    const char *arquivo_ranking;
    time_t inicio_tempo;
    int tempo_restante;
    char entrada_jogador[50];
    const char *palavra_atual;

    // Configura��es espec�ficas por dificuldade
    if (dificuldade == 1) { // F�cil
        banco_palavras = palavras_faceis;
        total_palavras = total_palavras_faceis;
        pontos_por_palavra = PONTUACAO_FACIL;
        jogo.tempo_limite = TEMPO_FACIL;
        nome_dificuldade = "FACIL";
        arquivo_ranking = "ranking_facil.txt";
    } else if (dificuldade == 2) { // M�dio
        banco_palavras = palavras_medianas;
        total_palavras = total_palavras_medianas;
        pontos_por_palavra = PONTUACAO_MEDIO;
        jogo.tempo_limite = TEMPO_MEDIO;
        nome_dificuldade = "MEDIO";
        arquivo_ranking = "ranking_medio.txt";
    } else if (dificuldade == 3) { // Dif�cil
        banco_palavras = palavras_dificeis;
        total_palavras = total_palavras_dificeis;
        pontos_por_palavra = PONTUACAO_DIFICIL;
        jogo.tempo_limite = TEMPO_DIFICIL;
        nome_dificuldade = "DIFICIL";
        arquivo_ranking = "ranking_dificil.txt";
    } else {
        return; // Dificuldade inv�lida
    }

    // Inicializa��o do jogo
    jogo.pontuacao = 0;
    inicio_tempo = time(NULL);

    printf("\n=== Modo %s ===\n", nome_dificuldade);
    printf("Voc� tem %d segundos para digitar o m�ximo de palavras!\n", 
           jogo.tempo_limite);
    Sleep(2000); // Pausa para leitura

    // Loop principal do jogo
    while (difftime(time(NULL), inicio_tempo) < jogo.tempo_limite) {
        tempo_restante = jogo.tempo_limite - (int)difftime(time(NULL), inicio_tempo);
        printf("\nTempo restante: %02d segundos\n", tempo_restante);

        // Seleciona palavra aleat�ria
        palavra_atual = banco_palavras[rand() % total_palavras];
        printf("Digite: %s\n> ", palavra_atual);
        fflush(stdout); // Garante que a mensagem seja exibida imediatamente

        // Captura entrada do jogador
        if (!leitura_nao_bloqueante(entrada_jogador, 
                                   sizeof(entrada_jogador), 
                                   inicio_tempo, 
                                   jogo.tempo_limite)) {
            break; // Tempo esgotado
        }

        // Verifica resposta
        if (_stricmp(entrada_jogador, palavra_atual) == 0) { // Compara��o case-insensitive
            jogo.pontuacao += pontos_por_palavra;
            printf("[OK] Correto! +%d pontos (Total: %d)\n", 
                   pontos_por_palavra, jogo.pontuacao);
        } else {
            printf("[X] Incorreto! Voc� digitou: %s\n", entrada_jogador);
            printf("A palavra era: %s\n", palavra_atual);
        }
    }

    // Finaliza��o
    printf("\nPontua��o final no modo %s: %d pontos\n", 
           nome_dificuldade, jogo.pontuacao);
           
	mostrar_mensagem_final(jogo.pontuacao);

    // Captura nome do jogador para o ranking
    printf("Digite seu nome para salvar o recorde: ");
    fgets(entrada_jogador, sizeof(entrada_jogador), stdin);
    entrada_jogador[strcspn(entrada_jogador, "\n")] = '\0'; // Remove quebra de linha

    salvar_ranking(arquivo_ranking, entrada_jogador, jogo.pontuacao);
    mostrar_ranking(arquivo_ranking);

    system("pause"); // Aguarda pressionamento de tecla
}

/**
 * Controla a execu��o do modo TryHard (tradu��o ingl�s-portugu�s)
 */
void jogar_modo_tryhard() {
    time_t inicio_tempo;
    int tempo_restante;
    char entrada_jogador[50];
    Vocabulario palavra_atual;
    const char *arquivo_ranking = "ranking_tryhard.txt";

    // Inicializa��o
    jogo.pontuacao = 0;
    inicio_tempo = time(NULL);

    printf("\n=== Modo TRYHARD ===\n");
    printf("Voc� tem %d segundos para traduzir o m�ximo de palavras!\n", 
           TEMPO_TRYHARD);
    Sleep(2000);

    // Loop principal do jogo
    while (difftime(time(NULL), inicio_tempo) < TEMPO_TRYHARD) {
        tempo_restante = TEMPO_TRYHARD - (int)difftime(time(NULL), inicio_tempo);
        printf("\nTempo restante: %02d segundos\n", tempo_restante);

        // Seleciona par de tradu��o aleat�rio
        palavra_atual = palavras_tryhard[rand() % total_palavras_tryhard];
        printf("Traduza: %s\n> ", palavra_atual.ingles);
        fflush(stdout);

        // Captura entrada do jogador
        if (!leitura_nao_bloqueante(entrada_jogador, 
                                   sizeof(entrada_jogador), 
                                   inicio_tempo, 
                                   TEMPO_TRYHARD)) {
            break; // Tempo esgotado
        }

        // Verifica resposta
        if (_stricmp(entrada_jogador, palavra_atual.portugues) == 0) {
            jogo.pontuacao += PONTUACAO_TRYHARD;
            printf("[OK] Correto! +%d pontos (Total: %d)\n", 
                   PONTUACAO_TRYHARD, jogo.pontuacao);
        } else {
            printf("[X] Incorreto! Voc� digitou: %s\n", entrada_jogador);
            printf("Tradu��o correta: %s = %s\n", 
                   palavra_atual.ingles, palavra_atual.portugues);
        }
    }

    // Finaliza��o
    printf("\nPontua��o final no modo TRYHARD: %d pontos\n", jogo.pontuacao);
    
    mostrar_mensagem_final(jogo.pontuacao);

    // Captura nome do jogador para o ranking
    printf("Digite seu nome para salvar o recorde: ");
    fgets(entrada_jogador, sizeof(entrada_jogador), stdin);
    entrada_jogador[strcspn(entrada_jogador, "\n")] = '\0';

    salvar_ranking(arquivo_ranking, entrada_jogador, jogo.pontuacao);
    mostrar_ranking(arquivo_ranking);

    system("pause");
}

/**
 * Exibe menu de visualiza��o dos rankings por dificuldade
 */
void mostrar_menu_ranking() {
    int opcao;
    char buffer[10];
    
    do {
        system("cls"); // Limpa a tela
        printf("===== MENU DE RANKINGS =====\n");
        printf("1. Ranking FACIL\n");
        printf("2. Ranking MEDIO\n");
        printf("3. Ranking DIFICIL\n");
        printf("4. Ranking TRYHARD\n");
        printf("5. Voltar\n");
        printf("Escolha uma op��o: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &opcao);

        switch(opcao) {
            case 1:
                mostrar_ranking("ranking_facil.txt");
                system("pause");
                break;
            case 2:
                mostrar_ranking("ranking_medio.txt");
                system("pause");
                break;
            case 3:
                mostrar_ranking("ranking_dificil.txt");
                system("pause");
                break;
            case 4:
                mostrar_ranking("ranking_tryhard.txt");
                system("pause");
                break;
            case 5:
                return; // Volta ao menu principal
            default:
                printf("Op��o inv�lida! Tente novamente.\n");
                Sleep(1000);
        }
    } while(true);
}

/* ==================== FUN��O PRINCIPAL ==================== */

int main() {
    int opcao;
    char buffer[10];

    // Inicializa��es importantes
    srand((unsigned int)time(NULL)); // Semente para n�meros aleat�rios
    
    // Configura��es de localidade e codifica��o
    setlocale(LC_ALL, "Portuguese");
    SetConsoleOutputCP(65001); // UTF-8
    SetConsoleCP(65001);

    // Loop do menu principal
    do {
        system("cls");
        printf("=== PALAVRAS ENTRE MUNDOS ===\n");
        printf("\nMenu Principal:\n");
        printf("1. Carta para o Astronauta\n");
        printf("2. Nivel Facil (%d pts)\n", PONTOS_FACIL);
        printf("3. Nivel Medio (%d pts)\n", PONTOS_MEDIO);
        printf("4. Nivel Dificil (%d pts)\n", PONTOS_DIFICIL);
        printf("5. Modo TryHard (Traducao - %d pts)\n", PONTOS_TRYHARD);
        printf("6. Visualizar Ranking\n");
        printf("7. Sair\n");
        printf("Escolha: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &opcao);

        if (opcao == 1) {
            mostrar_historia();
        } else if (opcao == 2) {
            jogar_modo_normal(1);  // F�cil
        } else if (opcao == 3) {
            jogar_modo_normal(2);  // M�dio
        } else if (opcao == 4) {
            jogar_modo_normal(3);  // Dif�cil
        } else if (opcao == 5) {
            jogar_modo_tryhard();
        } else if (opcao == 6) {
            mostrar_menu_ranking();
        } else if (opcao == 7) {
            printf("Obrigado por jogar!\n");
        } else {
            printf("Op��o inv�lida! Tente novamente.\n");
            Sleep(1000);
        }
        
	} while (opcao != 7);

    return 0;
}