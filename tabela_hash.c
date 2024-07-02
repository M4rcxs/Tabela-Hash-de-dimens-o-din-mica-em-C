// tabela_hash.c
#include "tabela_hash.h"
#include <stdlib.h>
#include <stdio.h>

#define TAMANHO_INICIAL 16
#define FATOR_CARGA 75

static unsigned int calcular_hash(int codCliente, int tamanho, int nivel) {
    return codCliente % (tamanho * (1 << nivel));
}

TabelaHash* criar_tabela(int tamanho_inicial) {
    TabelaHash *tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabela->tamanho = tamanho_inicial;
    tabela->elementos = 0;
    tabela->fator_carga = (tamanho_inicial * FATOR_CARGA) / 100;
    tabela->nivel = 0;
    tabela->proximo = 0;
    tabela->buckets = (NoHash**)calloc(tamanho_inicial, sizeof(NoHash*));
    return tabela;
}

void inserir_cliente(TabelaHash *tabela, Cliente *cliente) {
    unsigned int indice = calcular_hash(cliente->codCliente, tabela->tamanho, tabela->nivel);
    NoHash *novo_no = (NoHash*)malloc(sizeof(NoHash));
    novo_no->cliente = cliente;
    novo_no->proximo = tabela->buckets[indice];
    tabela->buckets[indice] = novo_no;
    tabela->elementos++;

    if (tabela->elementos > tabela->fator_carga) {
        redimensionar_tabela(tabela);
    }
}

Cliente* buscar_cliente(TabelaHash *tabela, int codCliente) {
    unsigned int indice = calcular_hash(codCliente, tabela->tamanho, tabela->nivel);
    NoHash *atual = tabela->buckets[indice];
    while (atual) {
        if (atual->cliente->codCliente == codCliente) {
            return atual->cliente;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void remover_cliente(TabelaHash *tabela, int codCliente) {
    unsigned int indice = calcular_hash(codCliente, tabela->tamanho, tabela->nivel);
    NoHash *atual = tabela->buckets[indice];
    NoHash *anterior = NULL;
    while (atual) {
        if (atual->cliente->codCliente == codCliente) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                tabela->buckets[indice] = atual->proximo;
            }
            free(atual);
            tabela->elementos--;
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void redimensionar_tabela(TabelaHash *tabela) {
    int novo_tamanho = tabela->tamanho * 2;
    NoHash **novos_buckets = (NoHash**)calloc(novo_tamanho, sizeof(NoHash*));
    for (int i = 0; i < tabela->tamanho; i++) {
        NoHash *atual = tabela->buckets[i];
        while (atual) {
            unsigned int novo_indice = calcular_hash(atual->cliente->codCliente, novo_tamanho, tabela->nivel + 1);
            NoHash *proximo = atual->proximo;
            atual->proximo = novos_buckets[novo_indice];
            novos_buckets[novo_indice] = atual;
            atual = proximo;
        }
    }
    free(tabela->buckets);
    tabela->buckets = novos_buckets;
    tabela->tamanho = novo_tamanho;
    tabela->nivel++;
    tabela->fator_carga = (novo_tamanho * FATOR_CARGA) / 100;
}