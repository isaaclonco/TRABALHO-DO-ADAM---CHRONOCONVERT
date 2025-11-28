CronoMaker – Conversor e Cronômetro de Tempo em C

Projeto desenvolvido em linguagem C para a disciplina de *Lógica de Programação e Algoritmos – 2025* (UCB).

O CronoMaker permite conversões entre horas, minutos e segundos, além de registrar automaticamente 
cada operação num histórico consultável, pesquisável e que pode ser salvo/recuperado a partir de 
um arquivo de texto. Também inclui um cronômetro animado integrado ao registro.

---
Estrutura do Projeto

ProjetoCronoMaker/
│
├── src/            # Código-fonte (.c)
│   ├── main.c
│   ├── tarefas.c
│   ├── io.c
│   └── util.c
│
├── include/        # Cabeçalhos (.h)
│   ├── tarefas.h
│   ├── io.h
│   ├── util.h
│   └── platform.h
│
├── data/           # Dados salvos pelo sistema
│   └── historico.txt
│
├── docs/           # Documentação e relatórios
│   ├── README.md
│   └── Relatorio.pdf
│
└── compilado/      # Local para o executável
```
Funcionalidades

- Conversões de Tempo
- Converter **horas ↔ minutos**
- Converter **minutos ↔ segundos**
- Converter **segundos ↔ horas**
- Registro automático de cada conversão com data/hora

Gerenciamento de Histórico

- *Ver histórico completo* com todos os registros
- *Pesquisar* registros por tipo específico
- *Limpar* todo o histórico de uma vez
- *Salvar* e *carregar* histórico em arquivo `.txt`
- Listagem organizada com ID, tipo, valores e data/hora

Cronômetro

- Cronômetro animado com precisão de milissegundos
- Controle intuitivo (ENTER para iniciar/parar)
- Salvar medições direto no histórico

Persistência de Dados

- Carregamento automático do histórico ao iniciar
- Salvamento manual ou automático ao sair
- Formato de arquivo texto legível
- Gerenciamento dinâmico com alocação de memória

Interface

- Menu interativo em modo texto (CLI)
- Cores ANSI para melhor experiência visual
- Caixas centralizadas e bordas desenhadas
- Feedback visual em todas as operações
- Compatível com Windows 10+ e Linux

---

Tecnologias Utilizadas

- *Linguagem C** (C99)
- *Structs* (`typedef struct`)
- *Alocação dinâmica* (`malloc`, `realloc`, `free`)
- *Manipulação de arquivos* texto (`fopen`, `fprintf`, `fscanf`)
- *Modularização* com múltiplos arquivos `.c` e `.h`
- *Interface texto* (CLI) com ANSI colors
- *Gerenciamento de memória* dinâmica

---
Como Compilar e Executar

No *Windows* (MinGW):

No prompt/pasta do projeto (`ProjetoCronoMaker`):

gcc -Iinclude -o compilado/cronomaker.exe src/main.c src/tarefas.c src/util.c src/io.c

Depois, execute:

cd compilado

cronomaker.exe

No **Linux**:

Da pasta do projeto:

gcc -Iinclude -o compilado/cronomaker src/main.c src/tarefas.c src/util.c src/io.c

chmod +x compilado/cronomaker

./compilado/cronomaker

---
Exemplos de Uso

  Conversões:
- *Horas → Minutos*: Digite as horas e obtenha os minutos equivalentes
- *Minutos → Segundos*: Converta minutos para segundos
- *Segundos → Horas*: Transforme segundos em horas decimais
- Todas as conversões são registradas automaticamente no histórico

  Histórico:
- *Listar tudo*: Veja todas as conversões e medições realizadas
- *Pesquisar*: Filtre por tipo (ex: "Cronômetro", "Horas → Minutos")
- *Remover*: Delete registros específicos por ID
- *Limpar*: Apague todo o histórico de uma vez
- *Salvar/Recuperar*: Dados persistem entre execuções

Cronômetro:
- Pressione *ENTER* para iniciar a contagem
- Pressione *ENTER* novamente para parar
- Opção de salvar o tempo medido no histórico
- Animação visual durante a contagem

---

Estruturas de Dados

```c
typedef struct {
    int id;              // Identificador único do registro
    char tipo[30];       // Tipo de operação realizada
    double valorOriginal;    // Valor de entrada
    double valorConvertido;  // Valor de saída/resultado
    char data[20];       // Data e hora da operação
} Conversao;
```

Características do Sistema:

- O histórico é um *vetor dinâmico* que cresce com `realloc()` conforme necessário
- Capacidade inicial: 5 registros
- Expansão automática quando o limite é atingido
- Os dados são salvos/carregados de `data/historico.txt` para persistência
- Liberação de memória (`free()`) ao encerrar o programa

---

Observações

- O programa utiliza *ANSI Colors* em terminais compatíveis (Linux/Windows 10+)
- Interface totalmente em **modo texto CLI*
- Arquivo de histórico é salvo automaticamente (ou manualmente, se desejar!)
- Suporte a UTF-8 para caracteres especiais
- Código modular e bem documentado
- Tratamento de erros em entradas inválidas

---

Autores

*Isaac Alonço Itacarambi de Souza Silva*  
*Desmond Aboagye*  
*Gustavo Junio de Souza Pereira*  
*Hugo Oliveira da Silva*

*Curso:* Bacharelado em Ciências da Computação  
*Professor:* Adam Smith Gontijo Brito de Assis  
*Instituição:* Universidade Católica de Brasília (UCB) — Câmpus Taguatinga  
*Ano:* 2025

Integridade Acadêmica

Este projeto foi desenvolvido integralmente pela equipe acima, em ambiente acadêmico. 

*Ferramentas de apoio consultadas:*
- ChatGPT (OpenAI) — sugestões de modularização e boas práticas
- Claude AI (Anthropic) — revisão lógica e documentação
- Grok AI (xAI) — análise de ponteiros e gerenciamento de memória

*Materiais de referência:*
- Curso em Vídeo (Gustavo Guanabara)
- Programação Dinâmica
- Fessor Bruno
- Filipe Deschamps

Todo o código e suas soluções são *originais da equipe*.

*Desenvolvido com ❤️ em C* | *UCB 2025* | *CronoMaker v1.0*