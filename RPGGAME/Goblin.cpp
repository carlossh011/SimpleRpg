#include <iostream>
#include <cstdlib>
#include "Goblin.hpp"
#include "Interface.hpp"

// sorteia tipo de goblin aleatoriamente. Funacao liv
TipoGoblin sortearTipo() {
    int sorteio = rand() % 3;         //cada valor corresnponde a um tipo
    if (sorteio == 0) return TipoGoblin::GUERREIRO;
    if (sorteio == 1) return TipoGoblin::ARQUEIRO;
    return TipoGoblin::XAMA;
}

// construtores
Goblin::Goblin()
    : Personagem("Goblin", 30, 8, 2, 0.10),
      tipo(TipoGoblin::GUERREIRO), nivel(1) {
    nome = "Goblin Guerreiro";
}
// construtor princip: recebe o indice na horda e o nivel da batalha
// cada tipo tem stats diferentes que escalam com nivelBatalha
Goblin::Goblin(int indice, int nivelBatalha)
    : Personagem(), nivel(nivelBatalha) {

    tipo = sortearTipo();
        // escalonamento(escala)
    int escala = nivelBatalha - 1; // nivel 1 = sem bônus

    switch (tipo) {                             //lembret: to_string converte um numero para texto
        case TipoGoblin::GUERREIRO:
            nome       = "Goblin Guerreiro #" + std::to_string(indice + 1);
            vidaMaxima = 40 + (escala * 5);
            vida       = vidaMaxima;
            stats.forca        = 12 + (escala * 2);
            stats.defesa       = 5  + (escala * 1);
            stats.chanceCritico = 0.10;
            break;

        case TipoGoblin::ARQUEIRO:
            nome       = "Goblin Arqueiro #" + std::to_string(indice + 1);
            vidaMaxima = 25 + (escala * 3);
            vida       = vidaMaxima;
            stats.forca        = 10 + (escala * 3);
            stats.defesa       = 2;
            stats.chanceCritico = 0.30 + (escala * 0.05);
            break;

        case TipoGoblin::XAMA:
            nome       = "Goblin Xama #" + std::to_string(indice + 1);
            vidaMaxima = 35 + (escala * 4);
            vida       = vidaMaxima;
            stats.forca        = 9  + (escala * 2);
            stats.defesa       = 3  + (escala * 1);
            stats.chanceCritico = 0.15;
            break;
    }

    defendendo = false;   //comeca sem escudo
    pocoes     = 0;
}

// getters
TipoGoblin  Goblin::getTipo()  const { return tipo; }
int         Goblin::getNivel() const { return nivel; }

std::string Goblin::nomeTipo() const {
    switch (tipo) {
        case TipoGoblin::GUERREIRO: return "GUERREIRO";
        case TipoGoblin::ARQUEIRO:  return "ARQUEIRO";
        case TipoGoblin::XAMA:      return "XAMA";
        default:                    return "?!?!?!";
    }
}

// goblin "automatizado"
void Goblin::executarTurno(Personagem& heroi) {
    resetarDefesa();              // abaixa o escudo no inicio do turno
    int acao = rand() % 10;

    switch (tipo) {
        case TipoGoblin::GUERREIRO:
            // 70% ataca, 30% defende
            if (acao < 7) realizarAtaque(*this, heroi);
            else          defender();
            break;

        case TipoGoblin::ARQUEIRO:
            // 90% sempre ataca (arqueiro agressivo)
            if (acao < 9) realizarAtaque(*this, heroi);
            else          defender();
            break;

        case TipoGoblin::XAMA:
            // 60% ataca, 20% defende, 20% se cura (se estiver abaixo de 50% de vida)
            if (acao < 6) {           // this é um ponteiro para o proprio objeto goblin que esta executando o turno
                realizarAtaque(*this, heroi);  //desreferencia ele para passar o goblin como referencia para realizarataque
            } else if (acao < 8) {
                defender();
            } else {
                // xama se cura apenas se estiver com menos de metade da vida
                if (vida < vidaMaxima / 2) {
                    exibirMensagem(nome + " conjura uma magica de cura!", TipoMensagem::CURA);
                    vida += 10;
                    if (vida > vidaMaxima) vida = vidaMaxima;
                } else {
                    realizarAtaque(*this, heroi);
                }
            }
            break;
    }
}

void Goblin::exibirApresentacao() const {
    exibirCaixaTitulo("INIMIGo: " + nome + " [" + nomeTipo() + "]");
}