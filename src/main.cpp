#include "../include/GestorDados.h"
#include "../include/Partida.h"
#include "../include/Time.h"
#include <dirent.h> // Biblioteca para ler as diretorias (pastas)
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Função auxiliar para pausar a tela antes de limpar
void pausarTela() {
  cout << "\nPressione ENTER para continuar...";
  cin.ignore();
  cin.get();
}

// Limpa a tela de forma multiplataforma (Windows/Linux)
void limparTela() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Função para procurar todos os arquivos .team na pasta
vector<string> obterArquivosEquipas() {
  vector<string> arquivos;
  DIR *dir;
  struct dirent *ent;

  // Tenta abrir a pasta data_files
  if ((dir = opendir("data_files")) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      string nomeArquivo = ent->d_name;
      // Se o ficheiro tiver ".team" no nome, adiciona à lista
      if (nomeArquivo.find(".team") != string::npos) {
        arquivos.push_back(nomeArquivo);
      }
    }
    closedir(dir);
  }
  return arquivos;
}

void iniciarJogoRapido() {
  limparTela();
  cout << "========================================" << endl;
  cout << "          MODO: JOGO RAPIDO             " << endl;
  cout << "========================================\n" << endl;

  vector<string> arquivos = obterArquivosEquipas();

  // Verifica se existem equipas suficientes para um jogo
  if (arquivos.size() < 2) {
    cout << "Erro: Precisas de pelo menos 2 equipas criadas!" << endl;
    cout << "Vai ao 'Editor de Base de Dados' e cria os teus planteis." << endl;
    pausarTela();
    return;
  }

  cout << "Equipas disponiveis no teu Banco de Dados:" << endl;
  for (size_t i = 0; i < arquivos.size(); i++) {
    // Remove a extensao .team para mostrar mais limpo no ecrã
    string nomeExibicao = arquivos[i];
    nomeExibicao.erase(nomeExibicao.find(".team"), 5);
    cout << " [" << i + 1 << "] " << nomeExibicao << endl;
  }

  int escolhaCasa = 0, escolhaFora = 0;
  cout << "\n> Escolhe o numero da equipa da CASA: ";
  cin >> escolhaCasa;
  cout << "> Escolhe o numero da equipa de FORA: ";
  cin >> escolhaFora;

  if (cin.fail()) {
    cin.clear();
    cin.ignore(10000, '\n');
    escolhaCasa = -1; // força invalidação abaixo
  }

  // Validação de segurança
  if (escolhaCasa < 1 || escolhaCasa > arquivos.size() || escolhaFora < 1 ||
      escolhaFora > arquivos.size()) {
    cout << "\nEscolha invalida! Regressando ao menu..." << endl;
    pausarTela();
    return;
  }

  // Prepara os caminhos dos arquivos escolhidos
  string caminhoCasa = "data_files/" + arquivos[escolhaCasa - 1];
  string caminhoFora = "data_files/" + arquivos[escolhaFora - 1];

  // O nosso Gestor de Dados faz a magia de carregar tudo para a memória
  Time equipaCasa = GestorDados::carregarTime(caminhoCasa);
  Time equipaFora = GestorDados::carregarTime(caminhoFora);

  if (equipaCasa.getNome() == "ERRO" || equipaFora.getNome() == "ERRO") {
    cout << "\nOcorreu um erro ao carregar o ficheiro binario da equipa!"
         << endl;
    pausarTela();
    return;
  }

  // O Juiz apita!
  simularPartida(equipaCasa, equipaFora);
  pausarTela();
}

void menuNovoJogo() {
  int opcao;
  do {
    limparTela();
    cout << "========================================" << endl;
    cout << "              NOVO JOGO                 " << endl;
    cout << "========================================" << endl;
    cout << " [1] Campanha (Em breve)" << endl;
    cout << " [2] Amistoso (Em breve)" << endl;
    cout << " [3] Jogo Rapido (Simular Partida)" << endl;
    cout << " [0] Voltar" << endl;
    cout << "========================================" << endl;
    cout << "> Escolha uma opcao: ";
    cin >> opcao;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
      opcao = -1;
    }

    switch (opcao) {
    case 1:
      cout << "Modo Campanha ainda nao implementado!" << endl;
      pausarTela();
      break;
    case 2:
      cout << "Modo Amistoso ainda nao implementado!" << endl;
      pausarTela();
      break;
    case 3:
      iniciarJogoRapido();
      break;
    case 0:
      break;
    default:
      cout << "Opcao Invalida!" << endl;
      pausarTela();
      break;
    }
  } while (opcao != 0);
}

void menuEditorBD() {
  limparTela();
  cout << "========================================" << endl;
  cout << "       CRIAR NOVO TIME NO BANCO         " << endl;
  cout << "========================================" << endl;

  string nomeTime, estadio;
  cout << "> Nome do Time: ";
  // O 'ws' limpa qualquer lixo ou pulo de linha que sobrou antes de ler
  getline(cin >> ws, nomeTime);
  cout << "> Nome do Estadio: ";
  getline(cin >> ws, estadio);

  Time novoTime(nomeTime, estadio);

  char continuar = 's';
  int contador = 1;

  cout << "\n--- ESCALANDO O ELENCO ---" << endl;
  while (tolower(continuar) == 's') {
    cout << "\n[ Jogador " << contador << " ]" << endl;
    string nomeJog;
    int id, forca, hab, stam, agr;

    cout << "  Nome: ";
    // Mesmo truque aqui pra não engolir a primeira letra do craque!
    getline(cin >> ws, nomeJog);
    cout << "  Idade: ";
    cin >> id;
    cout << "  Forca (1-100): ";
    cin >> forca;
    cout << "  Habilidade (1-100): ";
    cin >> hab;
    cout << "  Stamina (1-100): ";
    cin >> stam;
    cout << "  Agressividade (1-100): ";
    cin >> agr;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "\n[ERRO] Valores invalidos! Digite apenas numeros para idade e "
              "atributos.\n";
      cout << "Tente adicionar o Jogador " << contador << " novamente.\n";
      continue;
    }

    novoTime.adicionarJogador(Jogador(nomeJog, id, forca, hab, stam, agr));
    contador++;

    cout << "\n> Adicionar outro jogador? (s/n): ";
    cin >> continuar;

    if (cin.fail()) {
      cin.clear();
    }
    cin.ignore(10000, '\n');
  }

  // Formata o nome do arquivo (ex: "Sao Paulo" vira "sao_paulo")
  string nomeArquivo = nomeTime;
  for (char &c : nomeArquivo) {
    if (c == ' ')
      c = '_';
    c = tolower(c);
  }
  string caminho = "data_files/" + nomeArquivo + ".team";

  // Salva usando o nosso Gestor
  GestorDados::guardarTime(novoTime, caminho);

  cout << "\n========================================" << endl;
  cout << "  SUCESSO! Time guardado no cofre." << endl;
  cout << "  Arquivo gerado: " << caminho << endl;
  cout << "========================================" << endl;

  pausarTela();
}

int main() {
  int opcao;
  bool rodando = true;

  while (rodando) {
    limparTela();
    cout << "========================================" << endl;
    cout << "       R-FOOT MANAGER (Basic Edition)   " << endl;
    cout << "========================================" << endl;
    cout << " [1] Novo Jogo" << endl;
    cout << " [2] Carregar Jogo" << endl;
    cout << " [3] Configuracoes" << endl;
    cout << " [4] Editar Banco de Dados" << endl;
    cout << " [0] Sair" << endl;
    cout << "========================================" << endl;
    cout << "> Escolha uma opcao: ";

    cin >> opcao;

    // Limpa o buffer de entrada para evitar bugs se o usuário digitar letras
    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
      opcao = -1;
    }

    switch (opcao) {
    case 1:
      menuNovoJogo();
      break;
    case 2:
      cout << "\n[Sistema de Load sera implementado em breve!]\n";
      pausarTela();
      break;
    case 3:
      cout << "\n[Configuracoes serao implementadas em breve!]\n";
      pausarTela();
      break;
    case 4:
      menuEditorBD();
      break;
    case 0:
      cout << "\nSaindo do R-Foot Manager. Ate a proxima, chefe!\n";
      rodando = false;
      break;
    default:
      cout << "\nOpcao invalida, sô! Tenta de novo.\n";
      pausarTela();
      break;
    }
  }

  return 0;
}