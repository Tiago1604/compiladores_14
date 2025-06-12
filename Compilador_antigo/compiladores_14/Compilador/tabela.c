#include "tabela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int linha_atual; // Linha atual para mensagens de erro
Simbolo *tabela = NULL;  // Ponteiro para o início da tabela (implementada como lista encadeada)

// Função para converter string de tipo para enum TipoDado
TipoDado stringParaTipoDado(const char *tipo) {
    if (strcmp(tipo, "int") == 0) return TIPO_INT;
    if (strcmp(tipo, "float") == 0) return TIPO_FLOAT;
    if (strcmp(tipo, "str") == 0) return TIPO_STR;
    if (strcmp(tipo, "bool") == 0) return TIPO_BOOL;
    if (strcmp(tipo, "None") == 0) return TIPO_NONE;
    if (strcmp(tipo, "list") == 0) return TIPO_LIST;
    if (strcmp(tipo, "dict") == 0) return TIPO_DICT;
    if (strcmp(tipo, "function") == 0) return TIPO_FUNCTION;
    if (strcmp(tipo, "object") == 0) return TIPO_OBJECT;
    return TIPO_UNKNOWN;
}

// Função para converter enum TipoDado para string
const char *tipoDadoParaString(TipoDado tipo) {
    switch (tipo) {
        case TIPO_INT: return "int";
        case TIPO_FLOAT: return "float";
        case TIPO_STR: return "str";
        case TIPO_BOOL: return "bool";
        case TIPO_NONE: return "None";
        case TIPO_LIST: return "list";
        case TIPO_DICT: return "dict";
        case TIPO_FUNCTION: return "function";
        case TIPO_OBJECT: return "object";
        case TIPO_UNKNOWN: return "unknown";
        default: return "error";
    }
}

// Função para inserir um símbolo na tabela (mantida para compatibilidade)
void inserirSimbolo(const char *nome, const char *tipo) {
    // Delega para a função completa, considerando:
    // - Categoria padrão: variável
    // - Linha desconhecida (-1)
    inserirSimboloCompleto(nome, tipo, SIM_VARIAVEL, -1);
}

// Função para inserir um símbolo completo na tabela (sem escopo)
void inserirSimboloCompleto(const char *nome, const char *tipo, SimboloCategoria categoria, int linha) {
    Simbolo *s = tabela;
    
    // Verifica se o símbolo já existe na tabela
    while (s) {
        if (strcmp(s->nome, nome) == 0) {
            // O símbolo já existe
            if (strcmp(s->tipo, tipo) != 0) {
                fprintf(stderr, "[AVISO] Linha %d: Variável '%s' alterou tipo de '%s' para '%s'\n", 
                        linha_atual, nome, s->tipo, tipo);
                // Em Python, podemos mudar o tipo de uma variável, então atualizamos
                strncpy(s->tipo, tipo, 15);
                s->tipo[15] = '\0';
                s->tipo_dado = stringParaTipoDado(tipo);
            }
            return; // Não insere novamente
        }
        s = s->prox;
    }
    
    // Cria um novo símbolo
    Simbolo *novo = malloc(sizeof(Simbolo));
    if (novo == NULL) {
        fprintf(stderr, "[ERRO GRAVE] Linha %d: Falha na alocação de memória para a tabela de símbolos\n", linha_atual);
        exit(1);  // Erro crítico
    }

    strncpy(novo->nome, nome, 31);      // Copia o nome (limitado a 31 caracteres)
    novo->nome[31] = '\0';              // Garante terminação nula
    strncpy(novo->tipo, tipo, 15);      // Copia o tipo (limitado a 15 caracteres)
    novo->tipo[15] = '\0';              // Garante terminação nula
    
    // Inicializa os novos campos
    novo->tipo_dado = stringParaTipoDado(tipo);  // Converte string para enum
    novo->categoria = categoria;
    novo->linha = (linha >= 0) ? linha : linha_atual;  // Se linha não for fornecida, usa linha atual
    novo->inicializado = (categoria == SIM_CONSTANTE) ? 1 : 0;  // Constantes já estão inicializadas
    novo->utilizado = 0;  // Inicialmente não utilizado
    
    // Inicializa valores com zero/vazio
    novo->valor.valorInt = 0;
    novo->valor.valorFloat = 0.0f;
    novo->valor.valorChar = '\0';
    novo->valor.valorStr[0] = '\0';
    
    // Insere no início da lista
    novo->prox = tabela;
    tabela = novo;
}

// Função para buscar um símbolo pelo nome (simplificada, sem escopo)
Simbolo *buscarSimbolo(const char *nome) {
    for (Simbolo *s = tabela; s; s = s->prox) {
        if (strcmp(s->nome, nome) == 0) {
            return s;  // Retorna o símbolo se encontrado
        }
    }
    return NULL;  // Não encontrado
}

// Função para obter o tipo de dado de um símbolo
TipoDado obterTipoSimbolo(const char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        return s->tipo_dado;
    }
    
    fprintf(stderr, "[ERRO] Linha %d: Tentativa de obter tipo da variável '%s' que não existe\n",
            linha_atual, nome);
    return TIPO_UNKNOWN;
}

// Função para marcar uma variável como inicializada
void marcarInicializado(const char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        s->inicializado = 1;
    } else {
        fprintf(stderr, "[ERRO INTERNO] Linha %d: Tentativa de marcar como inicializada a variável '%s' que não existe na tabela de símbolos\n",
                linha_atual, nome);
    }
}

// Função para marcar uma variável como utilizada
void marcarUtilizado(const char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        s->utilizado = 1;
    } else {
        fprintf(stderr, "[ERRO INTERNO] Linha %d: Tentativa de marcar como utilizada a variável '%s' que não existe na tabela de símbolos\n",
                linha_atual, nome);
    }
}

// Função para atribuir valor inteiro a uma variável
void atribuirValorInt(const char *nome, int valor) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        // Em Python, variáveis podem mudar de tipo
        s->valor.valorInt = valor;
        s->tipo_dado = TIPO_INT;
        strncpy(s->tipo, "int", 15);
        marcarInicializado(nome);
    } else {
        fprintf(stderr, "[ERRO] Linha %d: Tentativa de atribuir valor à variável '%s' não declarada\n",
                linha_atual, nome);
    }
}

// Função para atribuir valor flutuante a uma variável
void atribuirValorFloat(const char *nome, float valor) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        // Em Python, variáveis podem mudar de tipo
        s->valor.valorFloat = valor;
        s->tipo_dado = TIPO_FLOAT;
        strncpy(s->tipo, "float", 15);
        marcarInicializado(nome);
    } else {
        fprintf(stderr, "[ERRO] Linha %d: Tentativa de atribuir valor à variável '%s' não declarada\n",
                linha_atual, nome);
    }
}

// Função para atribuir valor booleano a uma variável
void atribuirValorBool(const char *nome, int valor) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        // Em Python, variáveis podem mudar de tipo
        s->valor.valorBool = valor ? 1 : 0;
        s->tipo_dado = TIPO_BOOL;
        strncpy(s->tipo, "bool", 15);
        marcarInicializado(nome);
    } else {
        fprintf(stderr, "[ERRO] Linha %d: Tentativa de atribuir valor à variável '%s' não declarada\n",
                linha_atual, nome);
    }
}

// Função para atribuir valor string a uma variável
void atribuirValorStr(const char *nome, const char *valor) {
    Simbolo *s = buscarSimbolo(nome);
    if (s) {
        // Em Python, variáveis podem mudar de tipo
        strncpy(s->valor.valorStr, valor, 255);
        s->valor.valorStr[255] = '\0';  // Garante terminação nula
        s->tipo_dado = TIPO_STR;
        strncpy(s->tipo, "str", 15);
        marcarInicializado(nome);
    } else {
        fprintf(stderr, "[ERRO] Linha %d: Tentativa de atribuir valor à variável '%s' não declarada\n",
                linha_atual, nome);
    }
}

// Função para inferir tipo de uma expressão da AST
TipoDado inferirTipo(const NoAST *expr) {
    if (!expr) return TIPO_UNKNOWN;
    
    switch (expr->tipo) {
        case AST_NUM:
            return TIPO_INT;  // Números são int em nosso compilador simplificado
            
        case AST_ID: {
            // Busca o tipo da variável na tabela de símbolos
            Simbolo *s = buscarSimbolo(expr->nome);
            if (s) {
                return s->tipo_dado;
            } else {
                fprintf(stderr, "[ERRO] Linha %d: Variável '%s' usada mas não declarada\n",
                    linha_atual, expr->nome);
                return TIPO_UNKNOWN;
            }
        }
            
        case AST_OP: {
            // Operações básicas
            TipoDado tipo_esq = inferirTipo(expr->esquerda);
            TipoDado tipo_dir = inferirTipo(expr->direita);
            
            // Regras de conversão de tipo do Python simplificadas
            if (tipo_esq == TIPO_FLOAT || tipo_dir == TIPO_FLOAT) {
                return TIPO_FLOAT;  // float + qualquer coisa = float
            } else if (tipo_esq == TIPO_STR || tipo_dir == TIPO_STR) {
                if (expr->operador == '+') {
                    return TIPO_STR;  // str + str = str (concatenação)
                } else {
                    fprintf(stderr, "[ERRO] Linha %d: Operador '%c' não pode ser aplicado a strings\n",
                        linha_atual, expr->operador);
                    return TIPO_UNKNOWN;
                }
            }
            
            // Padrão: int
            return TIPO_INT;
        }
            
        case AST_COMP:
            // Comparações sempre retornam bool
            return TIPO_BOOL;
            
        case AST_ATRIB:
            // O tipo de uma atribuição é o tipo do lado direito
            return inferirTipo(expr->direita);
            
        default:
            return TIPO_UNKNOWN;
    }
}

// Função para verificar se dois tipos são compatíveis para uma operação
void verificarTiposCompativel(TipoDado tipo1, TipoDado tipo2, const char *operacao, int linha) {
    // Em Python, muitas operações são permitidas entre tipos diferentes
    // Aqui implementamos apenas verificações básicas
    
    if (tipo1 == TIPO_UNKNOWN || tipo2 == TIPO_UNKNOWN) {
        fprintf(stderr, "[AVISO] Linha %d: Operação '%s' com tipo desconhecido\n", linha, operacao);
        return;
    }
    
    // Verificações específicas
    if ((tipo1 == TIPO_STR && tipo2 != TIPO_STR) || 
        (tipo1 != TIPO_STR && tipo2 == TIPO_STR)) {
        // Operações entre strings e não-strings
        if (strcmp(operacao, "+") == 0) {
            fprintf(stderr, "[AVISO] Linha %d: Concatenando string com não-string\n", linha);
        } else {
            fprintf(stderr, "[ERRO] Linha %d: Operação '%s' não suportada entre string e não-string\n", 
                  linha, operacao);
        }
    }
    
    // Verificação para divisão por zero potencial
    if (strcmp(operacao, "/") == 0) {
        fprintf(stderr, "[AVISO] Linha %d: Divisão pode causar erro em tempo de execução se o divisor for zero\n", linha);
    }
}

// Função para analisar uma AST e construir/atualizar a tabela de símbolos
void analisarAST(const NoAST *raiz) {
    if (!raiz) return;
    
    switch (raiz->tipo) {
        case AST_PROGRAMA:
            // Programa contém uma lista de comandos
            analisarAST(raiz->esquerda);
            break;
            
        case AST_LISTA_CMD:
            // Lista de comandos - analisa o comando atual e depois os próximos
            analisarAST(raiz->esquerda);
            analisarAST(raiz->proximo);
            break;
            
        case AST_DECL:
            // Declaração de variável
            analisarDeclaracaoAST(raiz);
            break;
            
        case AST_ATRIB:
            // Atribuição de valor
            analisarAtribuicaoAST(raiz);
            break;
            
        case AST_IF:
        case AST_IF_ELSE:
            // Estruturas condicionais
            analisarAST(raiz->esquerda);  // Condição
            analisarAST(raiz->direita);   // Bloco(s)
            break;
            
        case AST_WHILE:
            // Laço while
            analisarAST(raiz->esquerda);  // Condição
            analisarAST(raiz->direita);   // Bloco
            break;
            
        case AST_FOR:
            // Laço for
            analisarAST(raiz->esquerda);  // Componentes do for
            analisarAST(raiz->direita);   // Bloco
            break;
            
        case AST_BLOCO:
            // Bloco de código
            analisarAST(raiz->esquerda);  // Lista de comandos
            break;
            
        case AST_PRINT:
            // Comando print
            analisarExpressaoAST(raiz->esquerda);  // Expressão a ser impressa
            break;
            
        case AST_COMP:
            // Comparação
            analisarExpressaoAST(raiz->esquerda);
            analisarExpressaoAST(raiz->direita);
            break;
            
        case AST_ID:
            // Uso de variável
            {
                Simbolo *s = buscarSimbolo(raiz->nome);
                if (!s) {
                    fprintf(stderr, "[ERRO] Linha %d: Variável '%s' usada mas não declarada\n",
                            linha_atual, raiz->nome);
                    // Para Python, podemos implicitamente declarar
                    inserirSimboloCompleto(raiz->nome, "unknown", SIM_VARIAVEL, linha_atual);
                } else {
                    marcarUtilizado(raiz->nome);
                    if (!s->inicializado) {
                        fprintf(stderr, "[AVISO] Linha %d: Variável '%s' usada antes de ser inicializada\n",
                                linha_atual, raiz->nome);
                    }
                }
            }
            break;
            
        default:
            // Para outros nós, apenas continue a análise recursiva
            if (raiz->esquerda) analisarAST(raiz->esquerda);
            if (raiz->direita) analisarAST(raiz->direita);
            if (raiz->proximo) analisarAST(raiz->proximo);
            break;
    }
}

// Função para analisar um nó de declaração
void analisarDeclaracaoAST(const NoAST *no_decl) {
    if (!no_decl || no_decl->tipo != AST_DECL) return;
    
    // Verifica se já existe uma variável com este nome
    Simbolo *s = buscarSimbolo(no_decl->nome);
    if (s) {
        fprintf(stderr, "[AVISO] Linha %d: Variável '%s' redeclarada (primeira declaração na linha %d)\n",
                linha_atual, no_decl->nome, s->linha);
        // Em Python, redeclaração é permitida
    } else {
        // Insere na tabela de símbolos
        inserirSimboloCompleto(no_decl->nome, no_decl->tipo_var, SIM_VARIAVEL, linha_atual);
    }
}

// Função para analisar um nó de atribuição
void analisarAtribuicaoAST(const NoAST *no_atrib) {
    if (!no_atrib || no_atrib->tipo != AST_ATRIB) return;
    
    // Analisa o lado direito (expressão)
    analisarExpressaoAST(no_atrib->direita);
    
    // Obtém o identificador do lado esquerdo
    if (no_atrib->esquerda && no_atrib->esquerda->tipo == AST_ID) {
        const char *nome = no_atrib->esquerda->nome;
        
        // Verifica se a variável existe
        Simbolo *s = buscarSimbolo(nome);
        if (!s) {
            fprintf(stderr, "[AVISO] Linha %d: Implicitamente declarando variável '%s'\n",
                    linha_atual, nome);
            // Em Python, podemos implicitamente declarar variáveis
            inserirSimboloCompleto(nome, "unknown", SIM_VARIAVEL, linha_atual);
            s = buscarSimbolo(nome);
        }
        
        // Infere o tipo da expressão
        TipoDado tipo_expr = inferirTipo(no_atrib->direita);
        
        // Atualiza o tipo se for diferente
        if (s->tipo_dado != tipo_expr && tipo_expr != TIPO_UNKNOWN) {
            fprintf(stderr, "[INFO] Linha %d: Variável '%s' mudou de tipo %s para %s\n",
                    linha_atual, nome, tipoDadoParaString(s->tipo_dado), tipoDadoParaString(tipo_expr));
            
            s->tipo_dado = tipo_expr;
            strncpy(s->tipo, tipoDadoParaString(tipo_expr), 15);
            s->tipo[15] = '\0';
        }
        
        // Marca como inicializada
        marcarInicializado(nome);
    }
}

// Função para analisar um nó de expressão
void analisarExpressaoAST(const NoAST *no_expr) {
    if (!no_expr) return;
    
    switch (no_expr->tipo) {
        case AST_ID:
            // Verifica se a variável existe e está inicializada
            {
                Simbolo *s = buscarSimbolo(no_expr->nome);
                if (!s) {
                    fprintf(stderr, "[ERRO] Linha %d: Variável '%s' usada mas não declarada\n",
                            linha_atual, no_expr->nome);
                    // Para Python, podemos implicitamente declarar
                    inserirSimboloCompleto(no_expr->nome, "unknown", SIM_VARIAVEL, linha_atual);
                } else {
                    marcarUtilizado(no_expr->nome);
                    if (!s->inicializado) {
                        fprintf(stderr, "[AVISO] Linha %d: Variável '%s' usada antes de ser inicializada\n",
                                linha_atual, no_expr->nome);
                    }
                }
            }
            break;
            
        case AST_OP:
            // Analisa os operandos
            analisarExpressaoAST(no_expr->esquerda);
            analisarExpressaoAST(no_expr->direita);
            
            // Verifica compatibilidade de tipos
            {
                TipoDado tipo_esq = inferirTipo(no_expr->esquerda);
                TipoDado tipo_dir = inferirTipo(no_expr->direita);
                
                // Cria uma string para o operador
                char op_str[2] = {no_expr->operador, '\0'};
                
                verificarTiposCompativel(tipo_esq, tipo_dir, op_str, linha_atual);
                
                // Verifica divisão por zero para constantes
                if (no_expr->operador == '/' && no_expr->direita->tipo == AST_NUM && 
                    no_expr->direita->valor == 0) {
                    fprintf(stderr, "[ERRO] Linha %d: Divisão por zero detectada\n", linha_atual);
                }
            }
            break;
            
        case AST_COMP:
            // Analisa os operandos da comparação
            analisarExpressaoAST(no_expr->esquerda);
            analisarExpressaoAST(no_expr->direita);
            break;
            
        default:
            // Para outros tipos de nós, continua a análise recursiva
            if (no_expr->esquerda) analisarExpressaoAST(no_expr->esquerda);
            if (no_expr->direita) analisarExpressaoAST(no_expr->direita);
            break;
    }
}

// Função para verificar todas referências a variáveis em uma AST
void verificarReferenciasAST(const NoAST *raiz) {
    // Primeiro faz uma análise para construir a tabela
    analisarAST(raiz);
    
    // Depois verifica variáveis não utilizadas
    verificarVariaveisNaoUtilizadas();
}

// Função para verificar variáveis não utilizadas
void verificarVariaveisNaoUtilizadas() {
    int count = 0;
    printf("\n[ANÁLISE] Variáveis declaradas mas não utilizadas:\n");
    
    for (Simbolo *s = tabela; s; s = s->prox) {
        if (s->categoria == SIM_VARIAVEL && !s->utilizado) {
            printf("- '%s' (linha %d)\n", s->nome, s->linha);
            count++;
        }
    }
    
    if (count == 0) {
        printf("[OK] Nenhuma variável não utilizada encontrada.\n");
    } else {
        printf("[AVISO] Total: %d variáveis declaradas mas nunca utilizadas.\n", count);
    }

    // Agora verifica variáveis utilizadas mas não inicializadas
    count = 0;
    printf("\n[ANÁLISE] Variáveis utilizadas sem inicialização prévia:\n");
    
    for (Simbolo *s = tabela; s; s = s->prox) {
        if (s->categoria == SIM_VARIAVEL && s->utilizado && !s->inicializado) {
            printf("- '%s' (linha %d)\n", s->nome, s->linha);
            count++;
        }
    }
    
    if (count == 0) {
        printf("[OK] Todas as variáveis utilizadas foram corretamente inicializadas.\n");
    } else {
        printf("[AVISO] Total: %d variáveis podem ter sido usadas sem inicialização.\n", count);
    }
}

// Função para imprimir toda a tabela de símbolos
void imprimirTabela() {
    printf("\n[TABELA DE SÍMBOLOS] Resumo da análise:\n");
    printf("------------------------------------------------------------------------\n");
    printf("| %-15s | %-10s | %-10s | %-6s | %-10s |\n", 
           "Nome", "Tipo", "Categoria", "Linha", "Status");
    printf("------------------------------------------------------------------------\n");
    
    for (Simbolo *s = tabela; s; s = s->prox) {
        char *categoria_str;
        switch (s->categoria) {
            case SIM_VARIAVEL: categoria_str = "Variável"; break;
            case SIM_CONSTANTE: categoria_str = "Constante"; break;
            case SIM_FUNCAO: categoria_str = "Função"; break;
            case SIM_PARAMETRO: categoria_str = "Parâmetro"; break;
            case SIM_CLASSE: categoria_str = "Classe"; break;
            default: categoria_str = "Desconhecido";
        }
        
        char status[20] = "";
        if (s->inicializado && s->utilizado) strcpy(status, "OK");
        else if (!s->inicializado && s->utilizado) strcpy(status, "Não inic.");
        else if (s->inicializado && !s->utilizado) strcpy(status, "Não usada");
        else strcpy(status, "Problema");
        
        printf("| %-15s | %-10s | %-10s | %-6d | %-10s |\n", 
               s->nome, s->tipo, categoria_str, s->linha, status);
    }
    printf("------------------------------------------------------------------------\n");
}

// Função para obter estatísticas da tabela
EstatisticasTabela obterEstatisticas() {
    EstatisticasTabela stats = {0};
    
    for (Simbolo *s = tabela; s; s = s->prox) {
        stats.total_simbolos++;
        
        switch (s->categoria) {
            case SIM_VARIAVEL: stats.variaveis++; break;
            case SIM_CONSTANTE: stats.constantes++; break;
            case SIM_FUNCAO: stats.funcoes++; break;
            default: break;
        }
        
        if (s->categoria == SIM_VARIAVEL) {
            if (!s->inicializado) stats.nao_inicializadas++;
            if (!s->utilizado) stats.nao_utilizadas++;
        }
    }
    
    return stats;
}

// Função para liberar a memória da tabela de símbolos
void liberarTabela() {
    Simbolo *s = tabela;
    while (s) {
        Simbolo *prox = s->prox;
        free(s);
        s = prox;
    }
    tabela = NULL;  // Reinicia a tabela
}

// Função para obter o valor inteiro de uma variável
int obterValorInt(const char *nome, int *valor) {
    Simbolo *s = buscarSimbolo(nome);
    if (s && s->tipo_dado == TIPO_INT && s->inicializado) {
        *valor = s->valor.valorInt;
        return 1;  // Sucesso
    }
    
    // Mensagem de erro específica dependendo da causa
    if (!s) {
        fprintf(stderr, "[ERRO] Linha %d: Tentativa de acessar variável '%s' não declarada\n",
                linha_atual, nome);
    } else if (s->tipo_dado != TIPO_INT) {
        fprintf(stderr, "[ERRO] Linha %d: Variável '%s' não é do tipo int (tipo atual: '%s')\n",
                linha_atual, nome, s->tipo);
    } else if (!s->inicializado) {
        fprintf(stderr, "[ERRO] Linha %d: Tentativa de acessar valor da variável '%s' antes de inicialização\n",
                linha_atual, nome);
    }
    
    return 0;  // Falha
}

// Função para obter o valor flutuante de uma variável
int obterValorFloat(const char *nome, float *valor) {
    Simbolo *s = buscarSimbolo(nome);
    if (s && s->tipo_dado == TIPO_FLOAT && s->inicializado) {
        *valor = s->valor.valorFloat;
        return 1;  // Sucesso
    }
    
    // Conversão automática de int para float (como em Python)
    if (s && s->tipo_dado == TIPO_INT && s->inicializado) {
        *valor = (float)s->valor.valorInt;
        return 1;  // Sucesso
    }
    
    return 0;  // Falha
}

// Função para obter o valor booleano de uma variável
int obterValorBool(const char *nome, int *valor) {
    Simbolo *s = buscarSimbolo(nome);
    if (s && s->tipo_dado == TIPO_BOOL && s->inicializado) {
        *valor = s->valor.valorBool;
        return 1;  // Sucesso
    }
    
    // Em Python, números podem ser convertidos para bool
    if (s && s->tipo_dado == TIPO_INT && s->inicializado) {
        *valor = (s->valor.valorInt != 0);
        return 1;  // Sucesso
    }
    
    return 0;  // Falha
}

// Função para obter o valor string de uma variável
int obterValorStr(const char *nome, char *valor, int max_len) {
    Simbolo *s = buscarSimbolo(nome);
    if (s && s->tipo_dado == TIPO_STR && s->inicializado) {
        strncpy(valor, s->valor.valorStr, max_len - 1);
        valor[max_len - 1] = '\0';
        return 1;  // Sucesso
    }
    
    return 0;  // Falha
}

// Função para verificar se uma variável está inicializada
int estaInicializada(const char *nome) {
    Simbolo *s = buscarSimbolo(nome);
    if (!s) {
        fprintf(stderr, "[ERRO] Linha %d: Verificação de inicialização da variável '%s' que não existe\n",
                linha_atual, nome);
        return 0;
    }
    return s->inicializado;
}