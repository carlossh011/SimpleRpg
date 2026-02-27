#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>

#define MAX_POCOES 3  // numero maximo de pocoes que o heroi pode carregar

struct Atributos {   //agrupar os atributos
    int forca;
    int defesa;
    double chanceCritico;
};

class Personagem {
protected:               // protected acessivel pela propria classe e pela classe goblin
    std::string nome;
    int vidaMaxima;
    int vida;
    Atributos stats;
    bool defendendo;
    int pocoes;

public:
    Personagem();
    Personagem(std::string n, int v, int f, int d, double crit); // construtor com parametros

    std::string getNome() const;
    int getVida() const;
    int getVidaMaxima() const;
    int getPocoes() const;
    Atributos getStats() const;

    void exibirStatus() const;
    void receberDano(int dano);
    void curar(int quantidade);
    void defender();
    void resetarDefesa();
    bool estaDefendendo() const;
     // const , o atacante é lido mas nunca modificado durante o ataque
    
     friend void realizarAtaque(const Personagem& atacante, Personagem& defensor);

};   //friend para acessar atributos privados de personagem diretamente

// prototipagem das funcoess livres
void realizarAtaque(const Personagem& atacante, Personagem& defensor);
int  solicitarAcao(const Personagem& heroi);
void exibirResultadoBatalha(const Personagem& heroi, int batalha, int total);

#endif