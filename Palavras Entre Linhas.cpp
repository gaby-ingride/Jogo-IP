/* ==================== BIBLIOTECAS NECESSÁRIAS ==================== */
#include <stdio.h>       // Para funções de entrada/saída (printf, scanf, fgets)
#include <stdlib.h>      // Para alocação de memória, sistema, números aleatórios
#include <string.h>      // Para manipulação de strings (strcmp, strlen)
#include <time.h>        // Para medição e controle de tempo
#include <locale.h>      // Para configuração regional (caracteres especiais)
#include <windows.h>     // Para funções específicas do Windows (Sleep)
#include <ctype.h>       // Para verificação de tipos de caracteres
#include <stdbool.h>     // Para uso de valores booleanos (true/false)
#include <conio.h>       // Para leitura de teclado não-bloqueante

/* ==================== CONSTANTES GLOBAIS ==================== */
#define MAXIMO_NOME 50           // Tamanho máximo para nome do jogador
#define MAXIMO_RANKING 100       // Capacidade máxima do ranking

/* ==================== ESTRUTURAS DE DADOS ==================== */

// Estrutura principal do jogo
typedef struct {
    int pontuacao;               // Pontuação acumulada do jogador
    int tempo_limite;            // Duração do nível em segundos
} Jogo;

Jogo jogo;  // Instância global do jogo

/* ==================== CONFIGURAÇÕES DO JOGO ==================== */

// Sistema de pontuação
#define PONTUACAO_FACIL 50       // Pontos por palavra fácil acertada
#define PONTUACAO_MEDIO 100      // Pontos por palavra média acertada
#define PONTUACAO_DIFICIL 100    // Pontos por palavra difícil acertada
#define PONTUACAO_TRYHARD 150    // Pontos por tradução correta

// Duração dos níveis (em segundos)
const int TEMPO_FACIL = 60;      // Duração do nível fácil
const int TEMPO_MEDIO = 60;      // Duração do nível médio
const int TEMPO_DIFICIL = 60;    // Duração do nível difícil
const int TEMPO_TRYHARD = 60;    // Duração do modo tryhard

/* ==================== BANCO DE DADOS DE PALAVRAS ==================== */

// Conjunto de palavras fáceis (curtas)
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
const int total_palavras_faceis = 47;  // Quantidade de palavras fáceis

// Conjunto de palavras médias
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
const int total_palavras_medianas = 50; // Quantidade de palavras médias

// Conjunto de palavras difíceis (longas e complexas)
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
const int total_palavras_dificeis = 50; // Quantidade de palavras difíceis

// Estrutura para pares de tradução (inglês-português)
typedef struct {
    const char *ingles;         // Palavra em inglês
    const char *portugues;      // Tradução correta em português
} Vocabulario;

// Banco de dados de traduções para o modo tryhard
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
const int total_palavras_tryhard = 50; // Quantidade de pares de tradução

/* ==================== FUNÇÕES AUXILIARES ==================== */

/**
 * Função para leitura de entrada com tempo limitado
 * Parâmetros:
 *   - entrada: buffer para armazenar o texto digitado
 *   - tamanho: tamanho máximo do buffer
 *   - inicio: momento em que a contagem começou
 *   - limite_segundos: tempo máximo permitido
 * Retorno:
 *   - true se o usuário completou a entrada
 *   - false se o tempo esgotou
 */
bool leitura_nao_bloqueante(char *entrada, int tamanho, time_t inicio, int limite_segundos) {
    int indice = 0;
    char caractere;
    entrada[0] = '\0'; // Inicializa string vazia

    while (difftime(time(NULL), inicio) < limite_segundos) {
        if (_kbhit()) { // Verifica se há tecla pressionada
            caractere = _getch(); // Lê o caractere sem eco
            
            if (caractere == '\r') { // Enter pressionado
                entrada[indice] = '\0'; // Finaliza a string
                printf("\n");
                return true;
            } else if (caractere == '\b' && indice > 0) { // Backspace
                indice--;
                printf("\b \b"); // Apaga o caractere no console
            } else if (isprint(caractere) && indice < tamanho - 1) { // Caractere imprimível
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
 * Salva a pontuação do jogador no arquivo de ranking
 * Parâmetros:
 *   - arquivo: nome do arquivo de ranking
 *   - nome: nome do jogador
 *   - pontuacao: pontuação a ser salva
 */
void salvar_ranking(const char *arquivo, const char *nome, int pontuacao) {
    FILE *arquivo_ranking;
    arquivo_ranking = fopen(arquivo, "a"); // Abre para adição
    if (!arquivo_ranking) return;
    
    fprintf(arquivo_ranking, "%s;%d\n", nome, pontuacao);
    fclose(arquivo_ranking);
}

/**
 * Exibe o ranking de pontuações a partir de um arquivo
 * Parâmetros:
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

    // Lê todos os registros do arquivo
    while (fscanf(arquivo_ranking, "%[^;];%d\n", 
           lista_ranking[contador].nome, 
           &lista_ranking[contador].pontos) == 2 && 
           contador < MAXIMO_RANKING) {
        contador++;
    }
    fclose(arquivo_ranking);

    // Ordena os registros por pontuação (decrescente)
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
    printf("\n--- Resultado da Missão ---\n");
    if (pontos < 600) {
        printf("Você não conseguiu disseminar sua língua.\n");
        printf("Os alienígenas inimigos interferiram demais na comunicação,\n");
        printf("impedindo que sua mensagem fosse compreendida.\n");
        printf("Tente novamente para melhorar sua habilidade e vencer a interferência!\n");
    } else if (pontos < 1000) {
        printf("Você resistiu à interferência dos alienígenas.\n");
        printf("Sua língua começou a se espalhar, mas ainda há muitos desafios pela frente.\n");
        printf("Continue praticando para fortalecer sua comunicação!\n");
    } else {
        printf("Você foi bem sucedido em disseminar sua língua!\n");
        printf("A mensagem foi clara e compreendida pelos povos alienígenas.\n");
        printf("Parabéns, astronauta! Sua missão avançou com grande êxito.\n");
    }
    printf("---------------------------\n");
}

void mostrar_historia() {
    system("cls");
    printf("=== CARTA PARA O ASTRONAUTA ===\n\n");
    printf("Em um futuro não muito distante, a humanidade expandiu suas fronteiras\n");
    printf("para além do Sistema Solar, descobrindo planetas habitados por\n");
    printf("civilizações alienígenas fascinantes. No entanto, a falta de comunicação\n");
    printf("entre as espécies gera desconfiança e conflitos.\n\n");
    
    printf("É aí que entra você - um Astronauta Pró-Interconhecimento determinado\n");
    printf("a mudar esse cenário. Sua missão é pacífica: viajar de planeta em planeta\n");
    printf("ensinando os idiomas da Terra aos alienígenas, criando pontes culturais\n");
    printf("e fortalecendo a harmonia intergaláctica. Seu sonho é um universo onde\n");
    printf("todas as espécies possam se entender.\n\n");
    
    printf("Porém, nem todos apoiam sua iniciativa. A Polícia Intergaláctica, uma\n");
    printf("organização autoritária que controla o fluxo de informações entre os\n");
    printf("planetas, vê seu trabalho como uma ameaça à \"ordem cósmica\". Eles\n");
    printf("acreditam que o conhecimento linguístico pode dar poder demais às\n");
    printf("civilizações menos desenvolvidas e começam a caçá-lo.\n\n");
    
    printf("Agora, você precisa ensinar de forma rápida e secreta, visitando planetas\n");
    printf("sob o radar da polícia. Cada fase do jogo representa um novo mundo, onde\n");
    printf("você tem um tempo limitado para ensinar palavras e frases antes que os\n");
    printf("oficiais intergalácticos cheguem.\n\n");
    
    printf("Sua coragem pode mudar o destino da comunicação intergaláctica!\n\n");
    
    system("pause");
}

/* ==================== FUNÇÕES PRINCIPAIS DO JOGO ==================== */

/**
 * Controla a execução dos modos Normal (Fácil, Médio, Difícil)
 * Parâmetros:
 *   - dificuldade: nível selecionado (1-Fácil, 2-Médio, 3-Difícil)
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

    // Configurações específicas por dificuldade
    if (dificuldade == 1) { // Fácil
        banco_palavras = palavras_faceis;
        total_palavras = total_palavras_faceis;
        pontos_por_palavra = PONTUACAO_FACIL;
        jogo.tempo_limite = TEMPO_FACIL;
        nome_dificuldade = "FACIL";
        arquivo_ranking = "ranking_facil.txt";
    } else if (dificuldade == 2) { // Médio
        banco_palavras = palavras_medianas;
        total_palavras = total_palavras_medianas;
        pontos_por_palavra = PONTUACAO_MEDIO;
        jogo.tempo_limite = TEMPO_MEDIO;
        nome_dificuldade = "MEDIO";
        arquivo_ranking = "ranking_medio.txt";
    } else if (dificuldade == 3) { // Difícil
        banco_palavras = palavras_dificeis;
        total_palavras = total_palavras_dificeis;
        pontos_por_palavra = PONTUACAO_DIFICIL;
        jogo.tempo_limite = TEMPO_DIFICIL;
        nome_dificuldade = "DIFICIL";
        arquivo_ranking = "ranking_dificil.txt";
    } else {
        return; // Dificuldade inválida
    }

    // Inicialização do jogo
    jogo.pontuacao = 0;
    inicio_tempo = time(NULL);

    printf("\n=== Modo %s ===\n", nome_dificuldade);
    printf("Você tem %d segundos para digitar o máximo de palavras!\n", 
           jogo.tempo_limite);
    Sleep(2000); // Pausa para leitura

    // Loop principal do jogo
    while (difftime(time(NULL), inicio_tempo) < jogo.tempo_limite) {
        tempo_restante = jogo.tempo_limite - (int)difftime(time(NULL), inicio_tempo);
        printf("\nTempo restante: %02d segundos\n", tempo_restante);

        // Seleciona palavra aleatória
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
        if (_stricmp(entrada_jogador, palavra_atual) == 0) { // Comparação case-insensitive
            jogo.pontuacao += pontos_por_palavra;
            printf("[OK] Correto! +%d pontos (Total: %d)\n", 
                   pontos_por_palavra, jogo.pontuacao);
        } else {
            printf("[X] Incorreto! Você digitou: %s\n", entrada_jogador);
            printf("A palavra era: %s\n", palavra_atual);
        }
    }

    // Finalização
    printf("\nPontuação final no modo %s: %d pontos\n", 
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
 * Controla a execução do modo TryHard (tradução inglês-português)
 */
void jogar_modo_tryhard() {
    time_t inicio_tempo;
    int tempo_restante;
    char entrada_jogador[50];
    Vocabulario palavra_atual;
    const char *arquivo_ranking = "ranking_tryhard.txt";

    // Inicialização
    jogo.pontuacao = 0;
    inicio_tempo = time(NULL);

    printf("\n=== Modo TRYHARD ===\n");
    printf("Você tem %d segundos para traduzir o máximo de palavras!\n", 
           TEMPO_TRYHARD);
    Sleep(2000);

    // Loop principal do jogo
    while (difftime(time(NULL), inicio_tempo) < TEMPO_TRYHARD) {
        tempo_restante = TEMPO_TRYHARD - (int)difftime(time(NULL), inicio_tempo);
        printf("\nTempo restante: %02d segundos\n", tempo_restante);

        // Seleciona par de tradução aleatório
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
            printf("[X] Incorreto! Você digitou: %s\n", entrada_jogador);
            printf("Tradução correta: %s = %s\n", 
                   palavra_atual.ingles, palavra_atual.portugues);
        }
    }

    // Finalização
    printf("\nPontuação final no modo TRYHARD: %d pontos\n", jogo.pontuacao);
    
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
 * Exibe menu de visualização dos rankings por dificuldade
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
        printf("Escolha uma opção: ");

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
                printf("Opção inválida! Tente novamente.\n");
                Sleep(1000);
        }
    } while(true);
}

/* ==================== FUNÇÃO PRINCIPAL ==================== */

int main() {
    int opcao;
    char buffer[10];

    // Inicializações importantes
    srand((unsigned int)time(NULL)); // Semente para números aleatórios
    
    // Configurações de localidade e codificação
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
            jogar_modo_normal(1);  // Fácil
        } else if (opcao == 3) {
            jogar_modo_normal(2);  // Médio
        } else if (opcao == 4) {
            jogar_modo_normal(3);  // Difícil
        } else if (opcao == 5) {
            jogar_modo_tryhard();
        } else if (opcao == 6) {
            mostrar_menu_ranking();
        } else if (opcao == 7) {
            printf("Obrigado por jogar!\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
            Sleep(1000);
        }
        
	} while (opcao != 7);

    return 0;
}