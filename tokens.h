#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdint.h>

/**
 * @brief Define todos os tipos de tokens (unidades léxicas) que o analisador
 * léxico é capaz de reconhecer no código-fonte.
 */
typedef enum {
    // Palavras-chave da linguagem
    TK_PROGRAM, TK_BEGIN, TK_END,
    TK_IF, TK_ELSE, TK_ELSEIF,
    TK_WHILE, TK_DO, TK_FOR,
    TK_FUNCTION, TK_INT, TK_FLOAT, TK_CHAR, TK_VOID,

    // Identificadores e literais
    TK_IDENTIFIER, TK_NUMBER,

    // Operadores
    TK_ASSIGN,
    TK_PLUS, TK_MINUS, TK_MULTIPLY, TK_DIVIDE,
    TK_GREATER, TK_LESS, TK_GREATER_EQUAL, TK_LESS_EQUAL,
    TK_EQUAL, TK_NOT_EQUAL,
    TK_AND, TK_OR, TK_NOT,

    // Pontuação e delimitadores
    TK_LEFT_PAREN, TK_RIGHT_PAREN,
    TK_LEFT_BRACE, TK_RIGHT_BRACE,
    TK_SEMICOLON, TK_COMMA, TK_COLON,
    TK_QUOTE,
    
    // Caracteres especiais e controle
    TK_NEWLINE,
    TK_EOF,       // Fim de arquivo (End of File)
    TK_UNKNOWN,   // Token desconhecido
    TK_ERROR      // Token que representa um erro léxico
} TokenType;

/**
 * @brief Representa uma unidade léxica (token) individual.
 * É a estrutura de dados fundamental que o analisador léxico produz e que
 * o analisador sintático consome.
 */
typedef struct {
    TokenType type;      /**< O tipo do token, conforme definido em TokenType. */
    char lexeme[64]; /**< A string de caracteres (lexema) que compõe o token. */
} Token;

/**
 * @brief Avança a posição no buffer de conteúdo, ignorando espaços e tabulações.
 * * @param content O buffer de bytes que contém o código-fonte.
 * @param current_pos Um ponteiro para a posição atual no buffer. A função
 * modifica o valor apontado para a posição do primeiro caractere que não
 * seja um espaço (' ') ou uma tabulação ('\t').
 */
void skip_whitespace(uint8_t*, int*);

/**
 * @brief Lê uma sequência de dígitos (um número inteiro) a partir da posição atual.
 * * @param content O buffer de bytes que contém o código-fonte.
 * @param current_pos Um ponteiro para a posição atual, que deve apontar para o
 * início de um número. A função avança a posição para o final do número lido.
 * @return Devolve um Token do tipo TK_NUMBER.
 */
Token read_number(uint8_t*, int*);

/**
 * @brief Lê uma sequência de letras e a classifica como palavra-chave ou identificador.
 * * @param content O buffer de bytes que contém o código-fonte.
 * @param current_pos Um ponteiro para a posição atual, que deve apontar para
 * o início de uma sequência de letras. A função avança a posição para o final 
 * da sequência lida.
 * @return Devolve um Token com o tipo da palavra-chave correspondente ou TK_IDENTIFIER.
 */
Token get_identifier_or_keyword(uint8_t*, int*);

/**
 * @brief Analisa o buffer e devolve o próximo token léxico.
 * * @param content O buffer de bytes que contém o código-fonte.
 * @param current_pos Um ponteiro para a posição atual no buffer. A função avança
 * esta posição para o final do token que foi lido.
 * @return Devolve o próximo Token encontrado na entrada. Se o fim do buffer
 * for alcançado, devolve um token do tipo TK_EOF.
 */
Token get_next_token(uint8_t*, int*);

/**
 * @brief Verifica se o token atual é do tipo esperado e avança para o próximo.
 * * @param expected_type O tipo de token esperado (`TokenType`).
 * @param current_token Um ponteiro para o token atual. Se o tipo for o esperado,
 * a função atualizará o valor apontado para o próximo token da entrada.
 * @param content O buffer de bytes, necessário para obter o próximo token.
 * @param current_pos A posição no buffer, necessária para obter o próximo token.
 * * Efeito: Se o tipo do token atual não for o esperado, a função imprime um
 * erro e encerra a execução do programa.
 */
void consume_token(TokenType, Token*, uint8_t*, int*);

#endif // TOKENIZER_H