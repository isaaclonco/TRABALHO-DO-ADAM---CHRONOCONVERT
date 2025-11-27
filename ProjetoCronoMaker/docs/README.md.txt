CRONOMAKER – Conversor de Tempo com Histórico

Projeto desenvolvido em Linguagem C para a disciplina de LÓGICA DE PROGRAMAÇÃO E ALGORITMOS – 2025.

O sistema realiza conversões de unidades de tempo (horas, minutos e segundos) e 
registra automaticamente cada conversão, permitindo consultar, pesquisar, editar 
e remover registros, além de salvar tudo em arquivo.

==================================================================================

ESTRUTURA DO PROJETO

ProjetoCronoMaker/
│
├── src/             → arquivos .c (código fonte)
│   ├── main.c
│   ├── tarefas.c
│   ├── io.c
│   ├── util.c
│
├── include/         → arquivos .h (cabeçalhos)
│   ├── tarefas.h
│   ├── io.h
│   ├── util.h
│
├── data/            → arquivos gerados (histórico.txt)
│   └── historico.txt
│
├── docs/            → relatório, README, apresentação
│   ├── README.md
│   └── Relatorio.pdf
│
└── compilado/       → opcional (onde fica o .exe)


==================================================================================

FUNCIONALIDADES IMPLEMENTADAS

* Converter horas, minutos e segundos
* Registrar conversão automaticamente com ID
* Listar histórico completo
* Pesquisar registros por ID ou tipo
* Editar registros
* Remover registros individualmente
* Limpar todo o histórico
* Salvar e carregar dados em arquivo .txt
* Uso de malloc e realloc para expansão dinâmica
* Modularização completa (.c e .h)

==================================================================================

TECNOLOGIAS UTILIZADAS

* Linguagem C
* Structs e Typedef
* Alocação dinâmica (malloc, realloc, free)
* Manipulação de arquivos com fopen, fprintf, fscanf
* Modularização com múltiplos arquivos .c e .h
* Interface em modo texto (CLI)

==================================================================================

COMO COMPILAR E EXECUTAR

para comopilar é necessario estar na pasta do projeto: cd/downloads cd/ProjetoCronoMaker;

No Windows (PowerShell ou MinGW):
gcc -Wall -std=c99 -Iinclude -o compilado/cronomaker.exe src/*.c

para executar:
cd compilado

logo apos:
cronomaker.exe


==================================================================================

AUTORES

Nome dos alunos : ISAAC ALONÇO ITACARAMBI DE SOUZA SILVA, DESMOND ABOAGYE, GUSTAVO JUNIO DE SOUZA PEREIRA & HUGO OLIVEIRA DA SILVA.
Curso: Bacharelado em Ciências da Computação.
Professor: ADAM SMITH GONTIJO BRITO DE ASSIS.
Instituição: (UCB )Universidade Católica de Brasília - Câmpus Taguatinga.