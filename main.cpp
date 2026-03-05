#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

// ==========================================
// CLASSE JOGADOR
// ==========================================
class jogador {
private: 
    string nome;
    int idade;
    int forca; // característica 1
    int habilidade; // característica 2

public:
    // Construtor pra criar o jogador
    jogador(string n, int id, int f, int h) {
        nome = n;
        idade = id;
        forca = f;
        habilidade = h;
    }

    // Métodos para pegar os dados (Getters)
    string getNome() const { return nome;}
    int getIdade() const { return idade;}
    int getForca() const { return forca;}
    int getHabilidade() const { return habilidade;}
};

// ==========================================
// CLASSE TIME
// ==========================================
class Time {
private:
    string nome;
    string estadio;
    vector<jogador> elenco; // Equivalente ao ArrayList de jogadores

public:
    Time(string n, string est) {
        nome = n;
        estadio = est;
    }    

    string getNome() const { return nome; }
    string getEstadio() const { return estadio; }

    // Método para contratar/adicionar jogador ao time
    void adicionarJogador(jogador j) {
        elenco.push_back(j);
    }

    // Calcular a força geral do time para usar na partida
    int calcularForcaGeral() const {
        if (elenco.empty()) return 0;
        int soma = 0;
        for (const auto& j : elenco) {
            soma += j.getForca() + j.getHabilidade();
        }   
        return soma / (elenco.size() * 2);
    }
};
// ==========================================
// MOTOR DE PARTIDA
// ==========================================
void simularPartida(Time& casa, Time& fora) {
    cout << "\n==================================================" << endl;
    cout << "   " << casa.getNome() << " x " << fora.getNome() << endl;
    cout << "   Estadio: " << casa.getEstadio() << endl;
    cout << "==================================================\n" << endl;

    int golsCasa = 0;
    int golsFora = 0;

    int forcaCasa = casa.calcularForcaGeral();
    int forcaFora = fora.calcularForcaGeral();

    // Preparar as ações de sorteio aleatório baseados no relógio do sistema (nunca se repete!)
    unsigned semente = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gerador(semente);
    uniform_int_distribution<int> chance(1, 100);

    // Bônus de jogar em casa (Apoio do torcedor)
    forcaCasa += 5;

    // Relógio de tempo de Jogo
    for (int minuto = 1; minuto <= 90; minuto++) {

        // Pausa de alguns milissegundos para cada evento ativado
        this_thread::sleep_for(chrono::milliseconds(50));

        int evento = chance(gerador);
        
        // Lógica de chances de gol
        if (evento <= 4) { // 4% de chance para lances perigosos time da casa
            int finalizacao = chance(gerador) + forcaCasa;
            int defesa = chance(gerador) + forcaFora;
            
            if (finalizacao > defesa + 15) {
                golsCasa++;
                cout << "[" << minuto << "'] GOOOOOOOOOOL DO " << casa.getNome() << "!!!" << endl;
            } else {
                cout << "[" << minuto << "'] Uuuuuh! O ataque do " << casa.getNome() << " quase marca!" << endl;
            }
        }
        else if (evento >= 97) { // 4% de chance para um lance do time visitante
            int finalizacao = chance(gerador) + forcaFora;
            int defesa = chance(gerador) + forcaCasa;

            if (finalizacao > defesa + 15) {
                golsFora++;
                cout << "[" << minuto << "'] GOOOOOOOOOOL DO " << fora.getNome() << "!!!" << endl;
            } else {
                cout << "[" << minuto << "'] Defesaca da zaga do " << casa.getNome() << ", salvando o time!" << endl;
            }
        }
    }

    cout << "\n==================================================" << endl;
    cout << "   FIM DE PAPO! PLACAR FINAL:" << endl;
    cout << "   " << casa.getNome() << " " << golsCasa << " x " << golsFora << " " << fora.getNome() << endl;
    cout << "==================================================\n" << endl;
}

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================
int main() {
    // 1. Montando o time da casa
    Time saoPaulo("Sao Paulo", "Morumbi");
    saoPaulo.adicionarJogador(jogador("Jonathan Calleri", 29, 85, 80));
    saoPaulo.adicionarJogador(jogador("Rodrigo Nestor", 22, 75, 78));
    saoPaulo.adicionarJogador(jogador("Arboleda", 31, 82, 70));
    saoPaulo.adicionarJogador(jogador("Jandrei", 29, 72, 65));

    // 2. Montando o time visitante
    Time palmeiras("Palmeiras", "Allianz Parque");
    palmeiras.adicionarJogador(jogador("Dudu", 31, 86, 84));
    palmeiras.adicionarJogador(jogador("Raphael Veiga", 28, 84, 82));
    palmeiras.adicionarJogador(jogador("Gustavo Gomez", 30, 85, 75));
    palmeiras.adicionarJogador(jogador("Weverton", 35, 82, 70));

    // 3. O Juiz apita!
    simularPartida(saoPaulo, palmeiras);

    return 0;
}
