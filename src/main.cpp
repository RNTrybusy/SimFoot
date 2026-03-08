#include "../include/Partida.h"
#include "../include/Time.h"
#include <iostream>
#include <string>


using namespace std;

// Função auxiliar para pausar a tela antes de limpar
void pausarTela() {
  cout << "\nPressione ENTER para continuar...";
  cin.ignore();
  cin.get();
}

// Limpa a tela de forma multiplataforma (Windows/Linux)
void limparTela() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// O nosso antigo main() virou uma função específica de Jogo Rápido
void iniciarJogoRapido() {
  limparTela();
  cout << "========================================" << endl;
  cout << "          MODO: JOGO RAPIDO             " << endl;
  cout << "========================================\n" << endl;

  Time saoPaulo("Sao Paulo", "Morumbi");
  saoPaulo.adicionarJogador(Jogador("Calleri", 29, 85, 80, 100, 70));
  saoPaulo.adicionarJogador(Jogador("Nestor", 22, 75, 78, 90, 40));
  saoPaulo.adicionarJogador(Jogador("Arboleda", 31, 82, 70, 85, 85));
  saoPaulo.adicionarJogador(Jogador("Jandrei", 29, 72, 65, 100, 20));

  Time palmeiras("Palmeiras", "Allianz Parque");
  palmeiras.adicionarJogador(Jogador("Dudu", 31, 86, 84, 85, 50));
  palmeiras.adicionarJogador(Jogador("Veiga", 28, 84, 82, 95, 40));
  palmeiras.adicionarJogador(Jogador("Gomez", 30, 85, 75, 90, 88));
  palmeiras.adicionarJogador(Jogador("Weverton", 35, 82, 70, 100, 10));

  simularPartida(saoPaulo, palmeiras);
  pausarTela();
}

void menuNovoJogo() {
  int opcao;
  do {
    limparTela();
    cout << "========================================" << endl;
    cout << "              NOVO JOGO                 " << endl;
    cout << "========================================" << endl;
    cout << " [1] Campanha (Em breve)" << endl;
    cout << " [2] Amistoso (Em breve)" << endl;
    cout << " [3] Jogo Rapido (Simular Partida)" << endl;
    cout << " [0] Voltar" << endl;
    cout << "========================================" << endl;
    cout << "> Escolha uma opcao: ";
    cin >> opcao;

    switch (opcao) {
    case 1:
      cout << "Modo Campanha ainda nao implementado!" << endl;
      pausarTela();
      break;
    case 2:
      cout << "Modo Amistoso ainda nao implementado!" << endl;
      pausarTela();
      break;
    case 3:
      iniciarJogoRapido();
      break;
    case 0:
      break;
    default:
      cout << "Opcao Invalida!" << endl;
      pausarTela();
      break;
    }
  } while (opcao != 0);
}

int main() {
  int opcao;
  bool rodando = true;

  while (rodando) {
    limparTela();
    cout << "========================================" << endl;
    cout << "       R-FOOT MANAGER (Basic Edition)   " << endl;
    cout << "========================================" << endl;
    cout << " [1] Novo Jogo" << endl;
    cout << " [2] Carregar Jogo" << endl;
    cout << " [3] Configuracoes" << endl;
    cout << " [4] Editar Banco de Dados" << endl;
    cout << " [0] Sair" << endl;
    cout << "========================================" << endl;
    cout << "> Escolha uma opcao: ";

    cin >> opcao;

    // Limpa o buffer de entrada para evitar bugs se o usuário digitar letras
    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
      opcao = -1;
    }

    switch (opcao) {
    case 1:
      menuNovoJogo();
      break;
    case 2:
      cout << "\n[Sistema de Load sera implementado em breve!]\n";
      pausarTela();
      break;
    case 3:
      cout << "\n[Configuracoes serao implementadas em breve!]\n";
      pausarTela();
      break;
    case 4:
      cout << "\n[Editor de Times .team sera implementado em breve!]\n";
      pausarTela();
      break;
    case 0:
      cout << "\nSaindo do R-Foot Manager. Ate a proxima, chefe!\n";
      rodando = false;
      break;
    default:
      cout << "\nOpcao invalida, sô! Tenta de novo.\n";
      pausarTela();
      break;
    }
  }

  return 0;
}