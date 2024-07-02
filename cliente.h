// cliente.h
#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int codCliente;
    char nome[100];
} Cliente;

Cliente* criar_cliente(int codCliente, const char* nome);

#endif