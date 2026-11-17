#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct
{
    int itens[MAX];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

void inicializarFila(FilaCircular *f)
{
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int estaCheia(FilaCircular *f)
{
    return f->quantidade == MAX;
}

int estaVazia(FilaCircular *f)
{
    return f->quantidade == 0;
}

void exibirEstado(FilaCircular *f)
{
    printf("[Estado -> inicio: %d | fim: %d | quantidade: %d/%d]\n",
           f->inicio, f->fim, f->quantidade, MAX);
}

void inserir(FilaCircular *f, int valor)
{
    if (estaCheia(f))
    {
        printf("\n[ERRO - OVERFLOW] A fila esta cheia! Nao e possivel inserir %d.\n", valor);
        exibirEstado(f);
        return;
    }

    f->itens[f->fim] = valor;
    printf("\nElemento %d inserido na posicao [%d] do array.\n", valor, f->fim);
    f->fim = (f->fim + 1) % MAX;
    f->quantidade++;
    exibirEstado(f);
}

void remover(FilaCircular *f)
{
    if (estaVazia(f))
    {
        printf("\n[ERRO - UNDERFLOW] A fila esta vazia! Nada para remover.\n");
        exibirEstado(f);
        return;
    }

    int removido = f->itens[f->inicio];
    printf("\nElemento %d removido da posicao [%d] do array.\n", removido, f->inicio);
    f->inicio = (f->inicio + 1) % MAX;
    f->quantidade--;
    exibirEstado(f);
}

void listar(FilaCircular *f)
{
    if (estaVazia(f))
    {
        printf("\nA fila esta vazia.\n");
        exibirEstado(f);
        return;
    }

    printf("\n--- Elementos na Fila (Ordem FIFO) ---\n");
    int idx = f->inicio;
    for (int i = 0; i < f->quantidade; i++)
    {
        printf("%d. Valor: %d (indice no array: [%d])\n", i + 1, f->itens[idx], idx);
        idx = (idx + 1) % MAX;
    }
    exibirEstado(f);
}

int main()
{
    FilaCircular fila;
    inicializarFila(&fila);

    int opcao, valor;

    do
    {
        printf("\n==============================\n");
        printf("    FILA CIRCULAR (INT)       \n");
        printf("==============================\n");
        printf("1. Inserir um elemento na fila\n");
        printf("2. Remover um elemento da fila\n");
        printf("3. Listar os elementos armazenados\n");
        printf("4. Sair do programa\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            while (getchar() != '\n')
                ; // Limpa buffer em caso de entrada invalida
            opcao = 0;
        }

        switch (opcao)
        {
        case 1:
            printf("Digite o valor inteiro a inserir: ");
            scanf("%d", &valor);
            inserir(&fila, valor);
            break;
        case 2:
            remover(&fila);
            break;
        case 3:
            listar(&fila);
            break;
        case 4:
            printf("\nEncerrando o programa...\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
