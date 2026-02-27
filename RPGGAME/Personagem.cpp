#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Personagem.hpp"
#include "Interface.hpp"
                                 //lembrete: a ordem deve ser a mesma do hpp
Personagem::Personagem()             // construtor
    : nome("Desconhecido"), vidaMaxima(50), vida(50),
      defendendo(false), pocoes(0) {
    stats.forca = 10;
    stats.defesa = 3;
    stats.chanceCritico = 0.10; 
}

Personagem::Personagem(std::string n, int v, int f, int d, double crit)
    : nome(n), vidaMaxima(v), vida(v),
      defendendo(false), pocoes(MAX_POCOES) {
    stats.forca = f;
    stats.defesa = d;
    stats.chanceCritico = crit;
}

// getters (const. para n modificar o objeto)
// const garante que o metodo não altera nenhum atributo de nenhum obj
std::string Personagem::getNome()     const { return nome; }
int         Personagem::getVida()     const { return vida; }
int         Personagem::getVidaMaxima() const { return vidaMaxima; }
int         Personagem::getPocoes()   const { return pocoes; }
Atributos   Personagem::getStats()    const { return stats; }
bool        Personagem::estaDefendendo() const { return defendendo; }

void Personagem::exibirStatus() const {     //const, exibir o status nao deve alterar o objeto
    exibirBarraDeVida(nome, vida, vidaMaxima);
}

// metodos que modificam 

void Personagem::receberDano(int dano) {
    vida -= dano;
    if (vida < 0) vida = 0;  // impede vida negativa 
}

void Personagem::curar(int quantidade) {
    if (pocoes <= 0) {
        exibirMensagem("Sem pocoes disponiveis!", TipoMensagem::AVISO);
        return;
    }
    pocoes--;  //consumir porçao
    vida += quantidade;
    if (vida > vidaMaxima) vida = vidaMaxima;
    exibirMensagem(nome + " usou uma pocao e recuperou " +
                   std::to_string(quantidade) + " de vida!", TipoMensagem::CURA);
}

void Personagem::defender() {    //defesa
    defendendo = true;
    exibirMensagem(nome + " assumiu postura de defesa!", TipoMensagem::DEFESA);
}

void Personagem::resetarDefesa() {       //reseta a defesa
    defendendo = false;
}

// funcoes livres

void realizarAtaque(const Personagem& atacante, Personagem& defensor) {
    int dano = atacante.stats.forca - defensor.stats.defesa;   //ataque

    double sorte = (double)rand() / RAND_MAX;  // double entre 0.0 e 1.0
    bool critico = (sorte < atacante.stats.chanceCritico);  // se o valor for menor que chancecritico o golpe e critico
    if (critico) dano *= 2;

    if (defensor.defendendo) dano = dano / 2;  //o dano e cortado pela metade

    if (dano < 0) dano = 0;

    exibirAtaque(atacante.nome, defensor.nome, dano, critico, defensor.defendendo);

    if (dano > 0) defensor.receberDano(dano);
}

int solicitarAcao(const Personagem& heroi) {    //menu de acoes
    int escolha = 0;
    exibirMenuAcao(heroi.getPocoes());    // passa a quantidade de pocoes para o menu
    std::cin >> escolha;
    return escolha;
}
                                  //apenas ler, nao modificar
void exibirResultadoBatalha(const Personagem& heroi, int batalha, int total) {
    exibirResumo(heroi.getNome(), heroi.getVida(), heroi.getVidaMaxima(),
                 heroi.getPocoes(), batalha, total);
}