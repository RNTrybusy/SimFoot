#ifndef GESTORDADOS_H
#define GESTORDADOS_H

#include "Time.h"
#include <string>

class GestorDados {
public:
  // Métodos estáticos para não precisarmos de instanciar o gestor sempre que o
  // usarmos
  static void guardarTime(const Time &equipa,
                          const std::string &caminhoFicheiro);
  static Time carregarTime(const std::string &caminhoFicheiro);
};

#endif // GESTORDADOS_H