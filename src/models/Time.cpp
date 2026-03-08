#include "../../include/Time.h"

Time::Time(std::string n, std::string est) {
  nome = n;
  estadio = est;
}

void Time::adicionarJogador(Jogador j) { elenco.push_back(j); }

int Time::calcularForcaGeral() const {
  if (elenco.empty())
    return 0;
  int soma = 0;
  int jogadoresAtivos = 0;

  for (const auto &j : elenco) {
    if (j.isEmCampo()) {
      int pesoStamina = (j.getStamina() > 30) ? 0 : -5;
      soma += j.getForca() + j.getHabilidade() + pesoStamina;
      jogadoresAtivos++;
    }
  }
  if (jogadoresAtivos == 0)
    return 0;
  return soma / (jogadoresAtivos * 2);
}

Jogador *Time::sortearJogadorAtivo(std::mt19937 &gerador) {
  std::vector<Jogador *> ativos;
  for (auto &j : elenco) {
    if (j.isEmCampo())
      ativos.push_back(&j);
  }
  if (ativos.empty())
    return nullptr;

  std::uniform_int_distribution<int> dist(0, ativos.size() - 1);
  return ativos[dist(gerador)];
}