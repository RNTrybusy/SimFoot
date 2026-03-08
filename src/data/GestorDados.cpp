#include "../../include/GestorDados.h"
#include <fstream>
#include <iostream>

using namespace std;

// Funções auxiliares privadas para lidar com strings em modo binário
void escreverString(ofstream &out, const string &str) {
  size_t tamanho = str.size();
  out.write((char *)&tamanho, sizeof(size_t)); // Guarda o tamanho da palavra
  out.write(str.c_str(), tamanho);             // Guarda a palavra em si
}

string lerString(ifstream &in) {
  size_t tamanho;
  in.read((char *)&tamanho, sizeof(size_t));
  string str(tamanho, '\0');
  in.read(&str[0], tamanho);
  return str;
}

void GestorDados::guardarTime(const Time &equipa,
                              const string &caminhoFicheiro) {
  // Abre o ficheiro em modo binário (ios::binary)
  ofstream out(caminhoFicheiro, ios::binary);
  if (!out) {
    cerr << "Erro ao criar o ficheiro: " << caminhoFicheiro << endl;
    return;
  }

  // 1. Guarda dados da Equipa
  escreverString(out, equipa.getNome());
  escreverString(out, equipa.getEstadio());

  // 2. Guarda o número de jogadores no vetor
  size_t numJogadores = equipa.getElenco().size();
  out.write((char *)&numJogadores, sizeof(size_t));

  // 3. Guarda jogador a jogador
  for (const auto &j : equipa.getElenco()) {
    escreverString(out, j.getNome());

    int idade = j.getIdade();
    int forca = j.getForca();
    int hab = j.getHabilidade();
    int stam = j.getStamina();
    int agr = j.getAgressividade();

    // Variáveis do tipo int (4 bytes) podem ser gravadas diretamente
    out.write((char *)&idade, sizeof(int));
    out.write((char *)&forca, sizeof(int));
    out.write((char *)&hab, sizeof(int));
    out.write((char *)&stam, sizeof(int));
    out.write((char *)&agr, sizeof(int));
  }

  out.close();
  cout << "Equipa '" << equipa.getNome()
       << "' guardada com sucesso em: " << caminhoFicheiro << endl;
}

Time GestorDados::carregarTime(const string &caminhoFicheiro) {
  ifstream in(caminhoFicheiro, ios::binary);
  if (!in) {
    cerr << "Erro ao abrir o ficheiro: " << caminhoFicheiro << endl;
    // Retorna uma equipa vazia em caso de erro
    return Time("ERRO", "ERRO");
  }

  // 1. Lê os dados da Equipa
  string nomeTime = lerString(in);
  string estadio = lerString(in);
  Time equipa(nomeTime, estadio);

  // 2. Lê a quantidade de jogadores
  size_t numJogadores;
  in.read((char *)&numJogadores, sizeof(size_t));

  // 3. Reconstrói os jogadores e insere-os na equipa
  for (size_t i = 0; i < numJogadores; ++i) {
    string nome = lerString(in);
    int idade, forca, hab, stam, agr;

    in.read((char *)&idade, sizeof(int));
    in.read((char *)&forca, sizeof(int));
    in.read((char *)&hab, sizeof(int));
    in.read((char *)&stam, sizeof(int));
    in.read((char *)&agr, sizeof(int));

    equipa.adicionarJogador(Jogador(nome, idade, forca, hab, stam, agr));
  }

  in.close();
  return equipa;
}