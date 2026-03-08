#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>

class Jogador {
private:
  std::string nome;
  int idade;
  int forca;
  int habilidade;
  int stamina;
  int agressividade;
  bool emCampo;
  int cartoesAmarelos;

public:
  // Construtor
  Jogador(std::string n, int id, int f, int h, int stam, int agr);

  // Getters Simples (podem ficar inline dentro de .h para otimização)
  std::string getNome() const { return nome; }
  int getIdade() const { return idade; }
  int getForca() const { return forca; }
  int getHabilidade() const { return habilidade; }
  int getStamina() const { return stamina; }
  int getAgressividade() const { return agressividade; }
  bool isEmCampo() const { return emCampo; }
  int getCartoesAmarelos() const { return cartoesAmarelos; }

  // Métodos que alteram o estado do jogador
  void cansar(int desgaste);
  void receberAmarelo();
  void expulsar();
  void lesionar();
};

#endif // JOGADOR_H