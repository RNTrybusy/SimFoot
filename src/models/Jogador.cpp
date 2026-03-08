#include "../../include/Jogador.h"

Jogador::Jogador(std::string n, int id, int f, int h, int stam, int agr) {
  nome = n;
  idade = id;
  forca = f;
  habilidade = h;
  stamina = stam;
  agressividade = agr;
  emCampo = true;
  cartoesAmarelos = 0;
}

void Jogador::cansar(int desgaste) {
  stamina -= desgaste;
  if (stamina < 0)
    stamina = 0;
}

void Jogador::receberAmarelo() { cartoesAmarelos++; }

void Jogador::expulsar() { emCampo = false; }

void Jogador::lesionar() { emCampo = false; }