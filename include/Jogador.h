#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>

class Jogador {
private:
  std::string nomeJogador;
  int idadeJogador;
  int forca;
  int habilidade;
  int stamina;
  int agressividade;
  bool emCampo;
  int cartoesAmarelos;

public:
  // Construtor com variáveis super claras
  Jogador(std::string nomeDoAtleta, int idadeDoAtleta, int forcaDoAtleta,
          int habDoAtleta, int stamDoAtleta, int agrDoAtleta);

  std::string getNome() const { return nomeJogador; }
  int getIdade() const { return idadeJogador; }
  int getForca() const { return forca; }
  int getHabilidade() const { return habilidade; }
  int getStamina() const { return stamina; }
  int getAgressividade() const { return agressividade; }
  bool isEmCampo() const { return emCampo; }
  int getAmarelos() const { return cartoesAmarelos; }

  void cansar(int desgaste);
  void receberAmarelo();
  void expulsar();
  void lesionar();
};

#endif // JOGADOR_H