// cliente.c
#include "cliente.h"
#include <stdlib.h>
#include <string.h>

Cliente* criar_cliente(int codCliente, const char* nome) {
    Cliente* novo_cliente = (Cliente*)malloc(sizeof(Cliente));
    novo_cliente->codCliente = codCliente;
    strncpy(novo_cliente->nome, nome, 100);
    return novo_cliente;
}