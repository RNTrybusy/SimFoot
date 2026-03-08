# ⚽ R-Foot

**R-Foot** é um simulador de futebol em texto desenvolvido em C++ (padrão C++11), inspirado em clássicos como de futebol (Brasfoot, Elifoot). Esta é uma demo inicial focada nas mecânicas bases de simulação de partidas e gerenciamento e criação de times esportivos.

## 🌟 Funcionalidades da Demo

- **Simulação de Partidas (Jogo Rápido):** Coloque dois times frente a frente em uma simulação baseada em atributos dos jogadores, com cálculos de força, rng (aleatoriedade) e eventos de jogo (Gols, Cartões, Lesões, etc).
- **Editor de Base de Dados Integrado:** Criação de novos times e escalação de elencos através do terminal (informando nome, idade, força, habilidade, stamina e agressividade de cada jogador). Os times gerados são salvos na pasta `data_files/`.
- **Interface via Linha de Comando:** Operações simples e rápidas com menus diretos e limpos no terminal multiplataforma.

## 📂 Estrutura do Projeto

Abaixo um resumo da organização dos arquivos:

```text
SimFoot/
├── src/            (Código fonte principal, motor de partida e classes)
├── include/        (Arquivos de cabeçalho .h)
├── data_files/     (Local onde os arquivos binários .team dos times são criados e lidos)
└── compilado/      (Lista de tarefas, planejamento e anotações do projeto)
```

## 🚀 Como Compilar e Executar

**Pré-requisitos:**
- Um compilador C++ (como o `g++` via MinGW no Windows ou GCC no Linux).

**Passos para compilação:**
 Abra o terminal na raiz do projeto (pasta `SimFoot`) e rode o comando:
```bash
g++ src/main.cpp src/models/*.cpp src/core/*.cpp src/data/*.cpp -o rfoot_v0.0.1.exe -std=c++11
```
*(Nota: O comando de compilação pode variar conforme você move os arquivos do `src/` para pastas filhas, ajuste-o para incluir todos os `.cpp`)*

**Para iniciar o jogo:**
No Windows:
```cmd
.\rfoot_v0.0.1.exe
```
No Linux/Mac:
```bash
./rfoot_v0.0.1.exe
```

## 🎮 Primeiro Passos (Como jogar)

1. **Crie seus times:** No menu principal, vá na opção **[4] Editar Banco de Dados** e crie no mínimo duas equipes. Siga as instruções na tela para adicionar jogadores e o time será salvo automaticamente dentro de `data_files/`.
2. **Inicie um Jogo Rápido:** No menu principal, vá em **[1] Novo Jogo** e depois **[3] Jogo Rápido (Simular Partida)**. Digite os números (IDs) referentes às equipes desejadas para a partida, e o simulador fará o resto!

---
*Excelente experiência de criar um mini simulador e a ideia é usar como início para algo maior!* ⚽
