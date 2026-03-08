#ifndef TIME_H
#define TIME_H

#include "Jogador.h"
#include <random>
#include <string>
#include <vector>

class Time {
private:
  std::string nome;
  std::string estadio;
  std::vector<Jogador> elenco;

public:
  Time(std::string n, std::string est);

  std::string getNome() const { return nome; }
  std::string getEstadio() const { return estadio; }
  std::vector<Jogador> &getElenco() { return elenco; }
  const std::vector<Jogador> &getElenco() const { return elenco; }

  void adicionarJogador(Jogador j);
  int calcularForcaGeral() const;
  Jogador *sortearJogadorAtivo(std::mt19937 &gerador);
};

#endif // TIME_H