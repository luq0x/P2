# Analisador para Linguagem de Programação Fictícia

Este repositório acadêmico documenta a criação de um analisador léxico e a especificação gramatical para uma linguagem de programação customizada. O objetivo é construir as bases para um futuro compilador ou interpretador, focando nos estágios iniciais da análise de código-fonte.

---

## Sobre a Linguagem

A linguagem foi projetada para ser simples e intuitiva, com uma sintaxe fortemente inspirada no C para facilitar o aprendizado e a implementação. Ela suporta construções de programação essenciais, incluindo:

* **Tipos de dados primitivos:** `int`, `float`, `char`.
* **Declaração e atribuição** de variáveis.
* **Estruturas de controle:** condicionais (`if`, `else`) e laços de repetição (`while`, `for`).
* **Declaração e chamada** de funções.
* **Expressões aritméticas** com tratamento de precedência e parênteses.

#### Exemplo de Código

O trecho abaixo ilustra a sintaxe que a gramática e o lexer são capazes de processar:

```txt
PROGRAMA "exemplo":
INICIO
int x = 10
if (x > 5) {
float y = x * 2.5
}
FIM
```

---

## Componentes do Projeto

O projeto está organizado em componentes bem definidos, cada um com uma responsabilidade clara no processo de análise.

* **`gramatica_bnf.txt`**
    * Define a **estrutura formal** e as regras sintáticas da linguagem utilizando a notação BNF (*Backus-Naur Form*). Este arquivo é o "manual de regras" que dita o que é um programa válido.

* **`tokens.h`**
    * Arquivo de cabeçalho que define a **interface pública** do analisador léxico. Contém a `enum` `TokenType` com todos os tokens possíveis e os protótipos das funções do lexer.

* **`tokens.c`**
    * **Implementação do analisador léxico (lexer)**. É responsável por ler o código-fonte como uma string e convertê-lo em uma sequência de tokens (como `TK_IF`, `TK_IDENTIFIER`, `TK_NUMBER`, etc.), que servirão de entrada para a próxima fase de análise.

---

## Próximos Passos

O projeto está em desenvolvimento contínuo. O status atual e os planos futuros são:

* ✅ **Gramática BNF:** Definida e servindo como base para a análise.
* ✅ **Analisador Léxico (Lexer):** Implementado e funcional.
* ➡️ **Analisador Sintático (Parser):** Próxima etapa crucial, responsável por verificar se a sequência de tokens obedece às regras da gramática.
* 🔜 **Analisador Semântico:** Futura implementação para checar a lógica e o significado do código (ex: tipos compatíveis em uma operação).
* 🏁 **Interpretador/Compilador:** O objetivo final do projeto, que permitirá a execução do código escrito na nova linguagem.
