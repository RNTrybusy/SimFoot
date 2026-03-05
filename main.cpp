#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

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

    // Método para listar o plantel com jogadores
    void mostrarElenco() const {
        cout << "\n=======================================" << endl;
        cout << "TIME: " << nome << " | ESTADIO: " << estadio << endl;
        cout << "=======================================" << endl;
        
        if (elenco.empty()) {
            cout << "Nenhum jogador cadastrado neste time." << endl;
            return;
        }
        
        for (size_t i = 0; i < elenco.size(); i++) {
            cout << "[" << i + 1 << "] " 
                << left << setw(20) << elenco[i].getNome()
                << " | Idade: " << elenco[i].getIdade()
                << " | Forca: " << elenco[i].getForca()
                << " | Hab: " << elenco[i].getHabilidade()
                << endl;
        }
        
    }
};

// ==========================================
// O MOTOR DO JOGO (Função Principal)
// ==========================================
int main() {
    cout << "Iniciando o Simulador de Futebol C++..." << endl;

    // Criando o nosso time
    Time meuTime("Sao Paulo", "Morumbi");

    // Criando uns craques e colocando no time
    meuTime.adicionarJogador(jogador("Jonathan Calleri", 29, 85, 80));
    meuTime.adicionarJogador(jogador("Rodrigo Nestor", 22, 75, 78));
    meuTime.adicionarJogador(jogador("Arboleda", 31, 82, 70));
    meuTime.adicionarJogador(jogador("Jandrei", 29, 72, 65));

    // Exibindo o resultado na tela
    meuTime.mostrarElenco();

    return 0;
}
