#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5
#define TAM_NOME 100

typedef struct
{
    int senha;
    char nome[TAM_NOME];
} Pessoa;

typedef struct
{
    Pessoa fila[MAX];
    int inicio;
    int fim;
    int quantidade;
} FilaAtendimento;

void inicializarFila(FilaAtendimento *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int estaCheia(FilaAtendimento *f)
{
    return f->quantidade == MAX;
}

int estaVazia(FilaAtendimento *f)
{
    return f->quantidade == 0;
}

void exibirStatusIndices(FilaAtendimento *f)
{
    printf("[Indices -> inicio: %d | fim: %d | quantidade: %d/%d]\n",
           f->inicio, f->fim, f->quantidade, MAX);
}

void inserirPessoa(FilaAtendimento *f, int senha, const char *nome)
{
    if (estaCheia(f))
    {
        printf("\n[AVISO - OVERFLOW] Fila de atendimento cheia! Nao foi possivel adicionar %s (Senha %d).\n", nome, senha);
        exibirStatusIndices(f);
        return;
    }

    f->fila[f->fim].senha = senha;
    strncpy(f->fila[f->fim].nome, nome, TAM_NOME - 1);
    f->fila[f->fim].nome[TAM_NOME - 1] = '\0';

    printf("\n[+] Senha %d (%s) entrou na fila na posicao [%d] do array.\n", senha, nome, f->fim);
    f->fim = (f->fim + 1) % MAX;
    f->quantidade++;
    exibirStatusIndices(f);
}

void chamarProxima(FilaAtendimento *f)
{
    if (estaVazia(f))
    {
        printf("\n[AVISO - UNDERFLOW] Nenhuma pessoa na fila para atender!\n");
        exibirStatusIndices(f);
        return;
    }

    Pessoa atendida = f->fila[f->inicio];
    printf("\n[->] Chamando proxima pessoa: Senha %d - %s (liberada posicao [%d] do array).\n",
           atendida.senha, atendida.nome, f->inicio);

    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;
    exibirStatusIndices(f);
}

void visualizarFila(FilaAtendimento *f)
{
    if (estaVazia(f))
    {
        printf("\nA fila de atendimento esta vazia no momento.\n");
        exibirStatusIndices(f);
        return;
    }

    printf("\n--- Fila de Espera Atual ---\n");
    int idx = f->inicio;
    for (int i = 0; i < f->quantidade; i++)
    {
        printf("%do da fila | Senha: %03d | Nome: %-20s | Posicao no array: [%d]\n",
               i + 1, f->fila[idx].senha, f->fila[idx].nome, idx);
        idx = (idx + 1) % MAX;
    }
    exibirStatusIndices(f);
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    FilaAtendimento fila;
    inicializarFila(&fila);

    int opcao;
    int geradorSenha = 1;
    char nome[TAM_NOME];

    do
    {
        printf("\n======================================\n");
        printf("   SISTEMA DE ATENDIMENTO (FIFO)      \n");
        printf("======================================\n");
        printf("1. Inserir pessoa na fila\n");
        printf("2. Chamar proxima pessoa\n");
        printf("3. Visualizar fila de espera\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            limparBuffer();
            opcao = 0;
        }
        else
        {
            limparBuffer();
        }

        switch (opcao)
        {
        case 1:
            printf("Digite o nome da pessoa: ");
            if (fgets(nome, TAM_NOME, stdin) != NULL)
            {
                nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n' final
                if (strlen(nome) == 0)
                {
                    strcpy(nome, "Cliente");
                }
                inserirPessoa(&fila, geradorSenha, nome);
                if (!estaCheia(&fila) || fila.quantidade == MAX)
                {
                    // Incrementa senha apenas se houve insercao bem-sucedida
                }
            }
            break;
        case 2:
            chamarProxima(&fila);
            break;
        case 3:
            visualizarFila(&fila);
            break;
        case 4:
            printf("\nEncerrando sistema de atendimento...\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }

        // Controla o incremento da senha apenas quando a insercao realmente ocorre
        if (opcao == 1 && fila.quantidade > 0)
        {
            int ultimoIdx = (fila.fim - 1 + MAX) % MAX;
            if (fila.fila[ultimoIdx].senha == geradorSenha)
            {
                geradorSenha++;
            }
        }

    } while (opcao != 4);

    return 0;
}