#ifndef GOBLIN_HPP
#define GOBLIN_HPP

#include "Personagem.hpp"  //herança da classe base
#include <string>
// substitui pelo enum simples
enum class TipoGoblin {             // enum para os tipos de goblin disponíveis
    GUERREIRO,  // alto dano, alta defesa
    ARQUEIRO,   // alto critico, baixa defesa
    XAMA        // se cura, stats medios
};
//goblin herda de personagem
class Goblin : public Personagem {
private:
    TipoGoblin tipo;  //comportamento e stats
    int nivel;
    // retorna o nome do tipo como string
    std::string nomeTipo() const;

public:
    Goblin();
    Goblin(int indice, int nivelBatalha);

    TipoGoblin getTipo() const;    // const, apenas leitura
    int getNivel() const;

    void executarTurno(Personagem& heroi); // para decidir a acao do turno

    void exibirApresentacao() const;      // exibe o tipo do goblin 

};
// sorteia um tipo de goblin aleatorio
TipoGoblin sortearTipo();

#endif