#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>


using namespace std;

// ==========================================
// CLASSE JOGADOR (Turbinada)
// ==========================================
class Jogador {
private:
  string nome;
  int idade;
  int forca;
  int habilidade;
  int stamina;       // Começa em 100, vai caindo e gera lesões/faltas
  int agressividade; // 1 a 100: dita a chance de bater

  // Status na partida
  bool emCampo;
  int cartoesAmarelos;

public:
  Jogador(string n, int id, int f, int h, int stam, int agr) {
    nome = n;
    idade = id;
    forca = f;
    habilidade = h;
    stamina = stam;
    agressividade = agr;
    emCampo = true;
    cartoesAmarelos = 0;
  }

  string getNome() const { return nome; }
  int getForca() const { return forca; }
  int getHabilidade() const { return habilidade; }
  int getStamina() const { return stamina; }
  int getAgressividade() const { return agressividade; }
  bool isEmCampo() const { return emCampo; }

  void cansar(int desgaste) {
    stamina -= desgaste;
    if (stamina < 0)
      stamina = 0;
  }

  void receberAmarelo() { cartoesAmarelos++; }
  int getAmarelos() const { return cartoesAmarelos; }

  void expulsar() { emCampo = false; }
  void lesionar() { emCampo = false; }
};

// ==========================================
// CLASSE TIME
// ==========================================
class Time {
private:
  string nome;
  string estadio;
  vector<Jogador> elenco;

public:
  Time(string n, string est) {
    nome = n;
    estadio = est;
  }

  string getNome() const { return nome; }
  string getEstadio() const { return estadio; }
  vector<Jogador> &getElenco() { return elenco; }

  void adicionarJogador(Jogador j) { elenco.push_back(j); }

  // Só calcula a força de quem tá em pé no campo!
  int calcularForcaGeral() const {
    if (elenco.empty())
      return 0;
    int soma = 0;
    int jogadoresAtivos = 0;
    for (const auto &j : elenco) {
      if (j.isEmCampo()) {
        // Stamina baixa derruba o rendimento do time
        int pesoStamina = (j.getStamina() > 30) ? 0 : -5;
        soma += j.getForca() + j.getHabilidade() + pesoStamina;
        jogadoresAtivos++;
      }
    }
    if (jogadoresAtivos == 0)
      return 0;
    return soma / (jogadoresAtivos * 2);
  }

  // Pega um jogador aleatório que ainda tá em campo (pra faltas e gols)
  Jogador *sortearJogadorAtivo(mt19937 &gerador) {
    vector<Jogador *> ativos;
    for (auto &j : elenco) {
      if (j.isEmCampo())
        ativos.push_back(&j);
    }
    if (ativos.empty())
      return nullptr;
    uniform_int_distribution<int> dist(0, ativos.size() - 1);
    return ativos[dist(gerador)];
  }
};

// ==========================================
// MOTOR DE PARTIDA
// ==========================================
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

    // Força dinâmica (cai se tiver expulso ou cansado)
    int forcaCasa = casa.calcularForcaGeral() + 5; // +5 fator casa
    int forcaFora = fora.calcularForcaGeral();

    // 1. DRENO DE STAMINA (Cansaço)
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

      // Diferença técnica gigante gera falta brusca
      if (atacante->getHabilidade() > defensor->getHabilidade() + 15 ||
          defensor->getStamina() < 40) {
        if (chance(gerador) < defensor->getAgressividade()) {
          cout << "[" << minuto << "'] Falta dura de " << defensor->getNome()
               << " parando o contra-ataque!" << endl;
          defensor->receberAmarelo();
          if (defensor->getAmarelos() == 2 || chance(gerador) > 85) {
            cout << "      -> VERMELHO DIRETO! " << defensor->getNome()
                 << " ta expulso!" << endl;
            defensor->expulsar();
          } else {
            cout << "      -> Juizao mostra o cartao amarelo." << endl;
          }
          continue; // Parou a jogada
        }
      }

      if (finalizacao > defesa + 15) {
        golsCasa++;
        cout << "[" << minuto << "'] GOOOOOOOOOOL DO " << casa.getNome() << "! "
             << atacante->getNome() << " manda pra rede!" << endl;
      } else if (finalizacao > defesa + 5) {
        cout << "[" << minuto << "'] Zaga corta mal! Escanteio pro "
             << casa.getNome() << "!" << endl;
        // Escanteio: Nova chance com bônus
        if (chance(gerador) + (forcaCasa / 2) > 60) {
          golsCasa++;
          cout << "      -> Na cobranca, a bola sobra limpa e e GOOOL!" << endl;
        }
      } else {
        cout << "[" << minuto << "'] " << atacante->getNome()
             << " chuta pra fora!" << endl;
      }
    }
    // --- EVENTO DE LESÃO NEUTRA ---
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
    // --- TIME DE FORA ATACA (Simplificado pra focar na lógica) ---
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

// ==========================================
// A FUNÇÃO PRINCIPAL
// ==========================================
int main() {
  Time saoPaulo("Sao Paulo", "Morumbi");
  // (Nome, Idade, Força, Hab, Stamina, Agressividade)
  saoPaulo.adicionarJogador(Jogador("Calleri", 29, 85, 80, 100, 70));
  saoPaulo.adicionarJogador(Jogador("Nestor", 22, 75, 78, 90, 40));
  saoPaulo.adicionarJogador(
      Jogador("Arboleda", 31, 82, 70, 85, 85)); // Zagueiro bate mais
  saoPaulo.adicionarJogador(Jogador("Jandrei", 29, 72, 65, 100, 20));

  Time palmeiras("Palmeiras", "Allianz Parque");
  palmeiras.adicionarJogador(Jogador("Dudu", 31, 86, 84, 85, 50));
  palmeiras.adicionarJogador(Jogador("Veiga", 28, 84, 82, 95, 40));
  palmeiras.adicionarJogador(Jogador("Gomez", 30, 85, 75, 90, 88));
  palmeiras.adicionarJogador(Jogador("Weverton", 35, 82, 70, 100, 10));

  simularPartida(saoPaulo, palmeiras);

  return 0;
}