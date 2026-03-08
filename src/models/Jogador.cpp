#include "../../include/Jogador.h"

Jogador::Jogador(std::string nomeDoAtleta, int idadeDoAtleta, int forcaDoAtleta,
                 int habDoAtleta, int stamDoAtleta, int agrDoAtleta) {
  nomeJogador = nomeDoAtleta;
  idadeJogador = idadeDoAtleta;
  forca = forcaDoAtleta;
  habilidade = habDoAtleta;
  stamina = stamDoAtleta;
  agressividade = agrDoAtleta;
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