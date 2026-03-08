#include "../../include/GestorDados.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

// Macro pra garantir compatibilidade entre Windows e Linux na hora de criar a
// pasta
#if defined(_WIN32)
#include <direct.h>
#define CRIAR_PASTA(caminho) _mkdir(caminho)
#else
#define CRIAR_PASTA(caminho) mkdir(caminho, 0777)
#endif

using namespace std;

// Funções auxiliares privadas
void escreverString(ofstream &out, const string &str) {
  size_t tamanho = str.size();
  out.write((char *)&tamanho, sizeof(size_t));
  out.write(str.c_str(), tamanho);
}

string lerString(ifstream &in) {
  size_t tamanho;
  in.read((char *)&tamanho, sizeof(size_t));
  string str(tamanho, '\0');
  in.read(&str[0], tamanho);
  return str;
}

void GestorDados::guardarTime(const Time &time, const string &caminhoArquivo) {
  // Tenta criar a pasta antes de qualquer coisa. Se já existir, ele só ignora.
  CRIAR_PASTA("data_files");

  ofstream out(caminhoArquivo, ios::binary);
  if (!out) {
    cerr << "Erro ao criar o arquivo: " << caminhoArquivo << endl;
    return;
  }

  escreverString(out, time.getNome());
  escreverString(out, time.getEstadio());

  size_t numJogadores = time.getElenco().size();
  out.write((char *)&numJogadores, sizeof(size_t));

  for (const auto &j : time.getElenco()) {
    escreverString(out, j.getNome());

    int idade = j.getIdade();
    int forca = j.getForca();
    int hab = j.getHabilidade();
    int stam = j.getStamina();
    int agr = j.getAgressividade();

    out.write((char *)&idade, sizeof(int));
    out.write((char *)&forca, sizeof(int));
    out.write((char *)&hab, sizeof(int));
    out.write((char *)&stam, sizeof(int));
    out.write((char *)&agr, sizeof(int));
  }

  out.close();
}

Time GestorDados::carregarTime(const string &caminhoArquivo) {
  ifstream in(caminhoArquivo, ios::binary);
  if (!in) {
    cerr << "Erro ao abrir o arquivo: " << caminhoArquivo << endl;
    return Time("ERRO", "ERRO");
  }

  string nomeTime = lerString(in);
  string estadio = lerString(in);
  Time time(nomeTime, estadio);

  size_t numJogadores;
  in.read((char *)&numJogadores, sizeof(size_t));

  for (size_t i = 0; i < numJogadores; ++i) {
    string nome = lerString(in);
    int idade, forca, hab, stam, agr;

    in.read((char *)&idade, sizeof(int));
    in.read((char *)&forca, sizeof(int));
    in.read((char *)&hab, sizeof(int));
    in.read((char *)&stam, sizeof(int));
    in.read((char *)&agr, sizeof(int));

    time.adicionarJogador(Jogador(nome, idade, forca, hab, stam, agr));
  }

  in.close();
  return time;
}