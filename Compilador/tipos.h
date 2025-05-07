#ifndef TIPOS_H
#define TIPOS_H

// Definição dos tipos de dados suportados
#define TIPO_INT        1
#define TIPO_FLOAT      2
#define TIPO_STRING     3
#define TIPO_NAO_DEFINIDO  4  // Para variáveis ainda não resolvidas

// Definição das categorias de nós na AST
#define CONSTANTE      10
#define VARIAVEL       11
#define OPERACAO       12
#define FUNCAO         13

// Definindo os tipos de escopo
#define ESCOPOL_GLOBAL  1
#define ESCOPOL_LOCAL   2

// Outras constantes
#define TIPO_VOID      0   // Tipo de retorno de funções que não retornam valor (ex: void em C)

#endif // TIPOS_H
