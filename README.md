# Slide Puzzle

Um jogo de **Slide Puzzle** desenvolvido em C utilizando a biblioteca [Raylib](https://www.raylib.com/).

Projeto desenvolvido como trabalho final da disciplina de **Algoritmos e Estruturas de Dados I**, do curso de **Bacharelado em Tecnologia da Informação (BTI) da UFERSA**.

## Sobre o projeto

O Slide Puzzle é um jogo de quebra-cabeça baseado na movimentação de peças numeradas através de um espaço vazio.

O objetivo do jogador é reorganizar as peças até alcançar a configuração correta do tabuleiro.

O projeto tem como objetivo aplicar, de forma prática, conceitos de programação em C, algoritmos e estruturas de dados estudados durante a disciplina.

A primeira versão do jogo será desenvolvida utilizando um tabuleiro **3×3**, com possibilidade de expansão para tabuleiros maiores durante o desenvolvimento.

## Funcionalidades

* [ ] Tabuleiro 3×3
* [ ] Movimentação das peças pelo teclado
* [ ] Movimentação das peças pelo mouse
* [ ] Verificação de movimentos válidos
* [ ] Embaralhamento do tabuleiro
* [ ] Verificação de vitória
* [ ] Contagem de movimentos
* [ ] Reinício da partida
* [ ] Seleção do tamanho do tabuleiro
* [ ] Suporte a tabuleiros maiores

> A lista de funcionalidades será atualizada conforme o desenvolvimento do projeto.

## Tecnologias

* **C**
* **Raylib**
* **Git**
* **GitHub**

## Estrutura do projeto

```text
slide-puzzle/
│
├── src/
│   ├── main.c
│   │
│   ├── board.c
│   ├── board.h
│   │
│   ├── game.c
│   ├── game.h
│   │
│   ├── input.c
│   ├── input.h
│   │
│   ├── draw.c
│   └── draw.h
│
├── assets/
│   └── fonts/
│
├── .gitignore
├── LICENSE
├── Makefile
└── README.md
```

### `src/`

Contém o código-fonte do jogo, dividido de acordo com suas responsabilidades.

* **`main.c`** — inicialização do programa e loop principal.
* **`board.c/h`** — representação e manipulação do tabuleiro.
* **`game.c/h`** — controle do estado e das regras da partida.
* **`input.c/h`** — tratamento das entradas do jogador.
* **`draw.c/h`** — renderização da interface utilizando Raylib.

### `assets/`

Contém recursos externos utilizados pelo jogo, como fontes e outros arquivos gráficos.

## Controles

Os controles serão definidos e documentados conforme o desenvolvimento do projeto.

Inicialmente, o jogo deverá oferecer suporte a:

* **Teclado**
* **Mouse**

## Conceitos abordados

O desenvolvimento do projeto busca aplicar conceitos estudados na disciplina de Algoritmos e Estruturas de Dados I, incluindo:

* Vetores e matrizes;
* Funções;
* Estruturas de controle;
* Modularização;
* Manipulação de dados;
* Algoritmos de movimentação;
* Geração de estados válidos do puzzle;
* Verificação de condições;
* Organização e abstração de código.

## Equipe

* **Pedro Phelippo Freitas Sarmento**
* **Maria Eduarda Soares de Sousa**
* **Erick Leonardus Bezerra Fernandes**

## Instituição

**Universidade Federal Rural do Semi-Árido (UFERSA)**
**Bacharelado em Tecnologia da Informação (BTI)**

Projeto desenvolvido para fins acadêmicos.
