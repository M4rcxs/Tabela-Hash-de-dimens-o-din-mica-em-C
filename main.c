// main.c
#include "cliente.h"
#include "tabela_hash.h"
#include <stdio.h>
#include <stdlib.h>

#define FATOR_CARGA 75
#define TAMANHO_INICIAL 16

int main() {
    TabelaHash *tabela = criar_tabela(TAMANHO_INICIAL);

    //Adicionar clientes para teste
    Cliente *cliente1 = criar_cliente(1, "Cliente 1");
    inserir_cliente(tabela, cliente1);

    Cliente *cliente2 = criar_cliente(2, "Cliente 2");
    inserir_cliente(tabela, cliente2);

    Cliente *cliente3 = criar_cliente(3, "Cliente 3");
    inserir_cliente(tabela, cliente3);

    Cliente *cliente4 = criar_cliente(4, "Cliente 4");
    inserir_cliente(tabela, cliente4);

    //Buscar cliente
    // Cliente *encontrado = buscar_cliente(tabela, 4);
    // if (encontrado) {
    //     printf("Cliente encontrado: %s\n", encontrado->nome);
    // } else {
    //     printf("Cliente não encontrado\n");
    // }

    // Deletar cliente
    remover_cliente(tabela, 4);
    Cliente *encontrado = buscar_cliente(tabela, 4);
    if (encontrado) {
        printf("Cliente encontrado: %s\n", encontrado->nome);
    } else {
        printf("Cliente não encontrado\n");
    }

    // Limpeza e desalocação de memória
    free(cliente1);
    free(cliente2);
    free(tabela->buckets);
    free(tabela);

    return 0;
}