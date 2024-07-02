#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include "cliente.h"

typedef struct NoHash {
    Cliente *cliente;
    struct NoHash *proximo;
} NoHash;

typedef struct {
    NoHash **buckets;
    int tamanho;
    int elementos;
    int fator_carga;
    int nivel;
    int proximo;
} TabelaHash;

TabelaHash* criar_tabela(int tamanho_inicial);
void inserir_cliente(TabelaHash *tabela, Cliente *cliente);
Cliente* buscar_cliente(TabelaHash *tabela, int codCliente);
void remover_cliente(TabelaHash *tabela, int codCliente);
void redimensionar_tabela(TabelaHash *tabela);

#endif