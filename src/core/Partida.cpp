#include "../../include/Partida.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void simularPartida(Time &casa, Time &fora) {
  cout << "\n==================================================" << endl;
  cout << "   " << casa.getNome() << " x " << fora.getNome() << endl;
  cout << "==================================================\n" << endl;

  int golsCasa = 0, golsFora = 0;
  unsigned semente = chrono::system_clock::now().time_since_epoch().count();
  mt19937 gerador(semente);
  uniform_int_distribution<int> chance(1, 100);

  for (int minuto = 1; minuto <= 90; minuto++) {
    this_thread::sleep_for(chrono::milliseconds(40));

    int forcaCasa = casa.calcularForcaGeral() + 5;
    int forcaFora = fora.calcularForcaGeral();

    for (auto &j : casa.getElenco())
      j.cansar(chance(gerador) > 50 ? 1 : 0);
    for (auto &j : fora.getElenco())
      j.cansar(chance(gerador) > 50 ? 1 : 0);

    int evento = chance(gerador);

    // --- TIME DA CASA ATACA ---
    if (evento <= 6) {
      Jogador *atacante = casa.sortearJogadorAtivo(gerador);
      Jogador *defensor = fora.sortearJogadorAtivo(gerador);
      if (!atacante || !defensor)
        continue;

      int finalizacao = chance(gerador) + forcaCasa;
      int defesa = chance(gerador) + forcaFora;

      if (atacante->getHabilidade() > defensor->getHabilidade() + 15 ||
          defensor->getStamina() < 40) {
        if (chance(gerador) < defensor->getAgressividade()) {
          cout << "[" << minuto << "'] Falta dura de " << defensor->getNome()
               << " parando o contra-ataque!" << endl;
          defensor->receberAmarelo();
          if (defensor->getCartoesAmarelos() == 2 || chance(gerador) > 85) {
            cout << "      -> VERMELHO DIRETO! " << defensor->getNome()
                 << " ta expulso!" << endl;
            defensor->expulsar();
          } else {
            cout << "      -> Juizao mostra o cartao amarelo." << endl;
          }
          continue;
        }
      }

      if (finalizacao > defesa + 15) {
        golsCasa++;
        cout << "[" << minuto << "'] GOOOOOOOOOOL DO " << casa.getNome() << "! "
             << atacante->getNome() << " manda pra rede!" << endl;
      } else if (finalizacao > defesa + 5) {
        cout << "[" << minuto << "'] Zaga corta mal! Escanteio pro "
             << casa.getNome() << "!" << endl;
        if (chance(gerador) + (forcaCasa / 2) > 60) {
          golsCasa++;
          cout << "      -> Na cobranca, a bola sobra limpa e e GOOOL!" << endl;
        }
      } else {
        cout << "[" << minuto << "'] " << atacante->getNome()
             << " chuta pra fora!" << endl;
      }
    }
    // --- EVENTO DE LESÃO ---
    else if (evento == 50) {
      Jogador *azarado = (chance(gerador) > 50)
                             ? casa.sortearJogadorAtivo(gerador)
                             : fora.sortearJogadorAtivo(gerador);
      if (azarado && azarado->getStamina() < 60 && chance(gerador) > 30) {
        cout << "[" << minuto << "'] Vixe! " << azarado->getNome()
             << " sentiu fisgada na coxa e cai no gramado. Substituicao "
                "obrigatoria!"
             << endl;
        azarado->lesionar();
      }
    }
    // --- TIME DE FORA ATACA ---
    else if (evento >= 95) {
      int finalizacao = chance(gerador) + forcaFora;
      int defesa = chance(gerador) + forcaCasa;
      if (finalizacao > defesa + 15) {
        golsFora++;
        cout << "[" << minuto << "'] GOOOOOOOOOOL DO " << fora.getNome()
             << "!!!" << endl;
      }
    }
  }

  cout << "\n==================================================" << endl;
  cout << "   FIM DE PAPO! PLACAR FINAL:" << endl;
  cout << "   " << casa.getNome() << " " << golsCasa << " x " << golsFora << " "
       << fora.getNome() << endl;
  cout << "==================================================\n" << endl;
}