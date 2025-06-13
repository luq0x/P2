#include "tokens.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * @brief Avança a posição no buffer de conteúdo, ignorando espaços e tabulações.
 * * @param content O buffer de bytes que contém o código-fonte.
 * @param current_pos Um ponteiro para a posição atual no buffer. A função
 * modifica o valor apontado para a posição do primeiro caractere que não
 * seja um espaço (' ') ou uma tabulação ('\t').
 */
void skip_whitespace(uint8_t *content, int *current_pos) {
    while (content[*current_pos] == ' ' || content[*current_pos] == '\t') {
        (*current_pos)++;
    }
}

/**
 * @brief Lê uma sequência de dígitos (um número inteiro) a partir da posição atual.
 * * @param content O buffer de bytes que contém o código-fonte.
 * @param current_pos Um ponteiro para a posição atual, que deve apontar para o
 * início de um número (um dígito ou um sinal de '-' seguido de um dígito). 
 * A função avança a posição para o final do número lido.
 * @return Devolve um Token do tipo TK_NUMBER. O campo `lexeme` do token conterá
 * a string de caracteres que representa o número.
 */
Token read_number(uint8_t *content, int *current_pos) {
    Token token;
    int start = *current_pos;

    if (content[*current_pos] == '-') {
        (*current_pos)++;
    }

    while (isdigit(content[*current_pos])) {
        (*current_pos)++;
    }

    int len = *current_pos - start;
    strncpy(token.lexeme, (char*)(content + start), len);
    token.lexeme[len] = '\0';
    token.type = TK_NUMBER;

    return token;
}

/**
 * @brief Lê uma sequência de letras e a classifica como palavra-chave ou identificador.
 * * @param content O buffer de bytes que contém o código-fonte.
 * @param current_pos Um ponteiro para a posição atual, que deve apontar para
 * o início de uma sequência de letras. A função avança a posição para o final 
 * da sequência lida.
 * @return Devolve um Token com o tipo da palavra-chave correspondente 
 * (ex: TK_IF, TK_WHILE) ou TK_IDENTIFIER se a sequência não for uma
 * palavra-chave reservada. O campo `lexeme` conterá a sequência lida.
 */
Token get_identifier_or_keyword(uint8_t *content, int *current_pos) {
    Token token;
    int start = *current_pos;

    while (isalpha(content[*current_pos])) {
        (*current_pos)++;
    }

    int len = *current_pos - start;
    strncpy(token.lexeme, (char*)(content + start), len);
    token.lexeme[len] = '\0';

    if (strcmp(token.lexeme, "PROGRAM") == 0) token.type = TK_PROGRAM;
    else if (strcmp(token.lexeme, "BEGIN") == 0) token.type = TK_BEGIN;
    else if (strcmp(token.lexeme, "END") == 0) token.type = TK_END;
    else if (strcmp(token.lexeme, "if") == 0) token.type = TK_IF;
    else if (strcmp(token.lexeme, "else") == 0) token.type = TK_ELSE;
    else if (strcmp(token.lexeme, "while") == 0) token.type = TK_WHILE;
    else if (strcmp(token.lexeme, "do") == 0) token.type = TK_DO;
    else if (strcmp(token.lexeme, "for") == 0) token.type = TK_FOR;
    else if (strcmp(token.lexeme, "function") == 0) token.type = TK_FUNCTION;
    else if (strcmp(token.lexeme, "int") == 0) token.type = TK_INT;
    else if (strcmp(token.lexeme, "float") == 0) token.type = TK_FLOAT;
    else if (strcmp(token.lexeme, "char") == 0) token.type = TK_CHAR;
    else if (strcmp(token.lexeme, "void") == 0) token.type = TK_VOID;
    else token.type = TK_IDENTIFIER; 

    return token;
}

/**
 * @brief Analisa o buffer e devolve o próximo token léxico.
 * * @param content O buffer de bytes que contém o código-fonte.
 * @param current_pos Um ponteiro para a posição atual no buffer. A função avança
 * esta posição para o final do token que foi lido.
 * @return Devolve o próximo Token encontrado na entrada. Se o fim do buffer
 * for alcançado (caractere '\0'), devolve um token do tipo TK_EOF.
 */
Token get_next_token(uint8_t *content, int *current_pos) {
    skip_whitespace(content, current_pos);
    
    char current_char = content[*current_pos];
    Token next_token;

    if (current_char == '\0') {
        next_token.type = TK_EOF;
        strcpy(next_token.lexeme, "EOF");
        return next_token;
    }

    if (isalpha(current_char)) {
        return get_identifier_or_keyword(content, current_pos);
    }

    if (isdigit(current_char) || (current_char == '-' && isdigit(content[*current_pos + 1]))) {
        return read_number(content, current_pos);
    }

    char next_char = content[*current_pos + 1];
    if (current_char == '&' && next_char == '&') {
        next_token.type = TK_AND;
        snprintf(next_token.lexeme, 3, "&&");
        *current_pos += 2;
        return next_token;
    } else if (current_char == '|' && next_char == '|') {
        next_token.type = TK_OR;
        snprintf(next_token.lexeme, 3, "||");
        *current_pos += 2;
        return next_token;
    } else if (current_char == '=' && next_char == '=') {
        next_token.type = TK_EQUAL;
        snprintf(next_token.lexeme, 3, "==");
        *current_pos += 2;
        return next_token;
    } else if (current_char == '!' && next_char == '=') {
        next_token.type = TK_NOT_EQUAL;
        snprintf(next_token.lexeme, 3, "!=");
        *current_pos += 2;
        return next_token;
    } else if (current_char == '>' && next_char == '=') {
        next_token.type = TK_GREATER_EQUAL;
        snprintf(next_token.lexeme, 3, ">=");
        *current_pos += 2;
        return next_token;
    } else if (current_char == '<' && next_char == '=') {
        next_token.type = TK_LESS_EQUAL;
        snprintf(next_token.lexeme, 3, "<=");
        *current_pos += 2;
        return next_token;
    }

    switch (current_char) {
        case '=': next_token.type = TK_ASSIGN;      snprintf(next_token.lexeme, 2, "="); break;
        case '+': next_token.type = TK_PLUS;        snprintf(next_token.lexeme, 2, "+"); break;
        case '-': next_token.type = TK_MINUS;       snprintf(next_token.lexeme, 2, "-"); break;
        case '*': next_token.type = TK_MULTIPLY;    snprintf(next_token.lexeme, 2, "*"); break;
        case '/': next_token.type = TK_DIVIDE;      snprintf(next_token.lexeme, 2, "/"); break;
        case '(': next_token.type = TK_LEFT_PAREN;  snprintf(next_token.lexeme, 2, "("); break;
        case ')': next_token.type = TK_RIGHT_PAREN; snprintf(next_token.lexeme, 2, ")"); break;
        case '{': next_token.type = TK_LEFT_BRACE;  snprintf(next_token.lexeme, 2, "{"); break;
        case '}': next_token.type = TK_RIGHT_BRACE; snprintf(next_token.lexeme, 2, "}"); break;
        case ';': next_token.type = TK_SEMICOLON;   snprintf(next_token.lexeme, 2, ";"); break;
        case ',': next_token.type = TK_COMMA;       snprintf(next_token.lexeme, 2, ","); break;
        case ':': next_token.type = TK_COLON;       snprintf(next_token.lexeme, 2, ":"); break;
        case '"': next_token.type = TK_QUOTE;       snprintf(next_token.lexeme, 2, "\""); break;
        case '\n':next_token.type = TK_NEWLINE;     snprintf(next_token.lexeme, 2, "\n"); break;
        default:
            next_token.type = TK_UNKNOWN;
            snprintf(next_token.lexeme, 2, "%c", current_char);
            break;
    }

    (*current_pos)++;
    return next_token;
}

/**
 * @brief Verifica se o token atual é do tipo esperado e avança para o próximo.
 * * @param expected_type O tipo de token esperado (`TokenType`) na posição atual da análise.
 * @param current_token Um ponteiro para o token atual. Se o tipo for o esperado,
 * a função atualizará o valor apontado para o próximo token da entrada.
 * @param content O buffer de bytes, necessário para obter o próximo token.
 * @param current_pos A posição no buffer, necessária para obter o próximo token.
 * * Efeito: Se `current_token->type` for igual a `expected_type`, o token é
 * "consumido" e `*current_token` é atualizado com o resultado da chamada a 
 * `get_next_token`. Caso contrário, a função imprime uma mensagem de erro
 * de sintaxe no `stderr` e encerra a execução do programa.
 */
void consume_token(TokenType expected_type, Token *current_token, uint8_t *content, int *current_pos) {
    if (expected_type == current_token->type) {
        *current_token = get_next_token(content, current_pos);
    } else {
        fprintf(stderr, "Error: Esperado um token %d, mas foi encontrado o token %d ('%s')\n",
                expected_type, current_token->type, current_token->lexeme);
        exit(EXIT_FAILURE);
    }
}