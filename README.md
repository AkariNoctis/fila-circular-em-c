FILA CIRCULAR EM C

Autor: Cauã Correa do Nascimento
Disciplina: Estrutura de Dados

DESCRIÇÃO DOS EXERCÍCIOS

Este repositório contém a implementação prática do conceito de Fila Circular (FIFO — First In, First Out) em linguagem C, utilizando arrays estáticos, struct e aritmética modular (%) para o reaproveitamento de memória.

- exercicio_1.c: Implementa uma fila circular de números inteiros com menu interativo para inserção, remoção e listagem dos elementos, controlando condições de overflow e underflow.
- exercicio_2.c: Simula um sistema de fila de atendimento utilizando uma struct (Pessoa, contendo número da senha e nome). Exibe o estado dos ponteiros (inicio, fim e quantidade) e os índices reais do array após cada operação para demonstrar o comportamento circular.

INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO

Certifique-se de ter o compilador gcc instalado. No terminal, dentro da pasta do projeto, execute:

Exercício 1:
gcc exercicio_1.c -o exercicio_1
./exercicio_1

Exercício 2:
gcc exercicio_2.c -o exercicio_2
./exercicio_2

(No Windows, execute exercicio1.exe ou exercicio2.exe)

TESTES REALIZADOS

Os programas foram configurados com capacidade MAX = 5 e validados nos seguintes cenários obrigatórios:

1. Inserção até completar a fila: Inseridos 5 elementos sequencialmente (índices [0] a [4]). Ao final, inicio = 0, fim = 0 (após (4 + 1) % 5) e quantidade = 5.
2. Tentativa de inserção em fila cheia (Overflow): Ao tentar inserir um 6º elemento com quantidade == 5, o sistema bloqueia a operação e exibe alerta de fila cheia sem sobrescrever dados.
3. Remoção de elementos: Removidos os 2 primeiros elementos (posições [0] e [1]), atualizando inicio = 2, fim = 0 e quantidade = 3.
4. Nova inserção utilizando posições liberadas: Inserido um novo elemento, que ocupou exatamente a posição [0] anteriormente liberada, avançando fim para 1 e quantidade para 4 (comprovando o reaproveitamento circular).
5. Remoção total e tentativa em fila vazia (Underflow): Removidos todos os elementos restantes até quantidade = 0 (inicio == fim). Ao tentar remover novamente, o programa impede a operação e sinaliza fila vazia.
