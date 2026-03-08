#include "../include/Partida.h"
#include "../include/Time.h"
#include <iostream>


using namespace std;

int main() {
  cout << "Iniciando R-Foot Manager..." << endl;

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

  return 0;
}