#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <string>  
#define LARGURA_CAIXA  42     // dimensões da interface - largura interna das caixas 
#define TAMANHO_BARRA  20   // quantidade de caracteres na barra de vida

// enum para categorizar mensagens de combate
enum class TipoMensagem {
    DANO,
    CRITICO,
    DEFESA,
    CURA,
    AVISO,
    INFO
};
// prototipos das funçoes de interface Lembrete: implementei em Interface.cpp
void exibirCabecalho();
void exibirCaixaTitulo(const std::string& titulo);
void exibirSeparador();
void exibirBarraDeVida(const std::string& nome, int vida, int vidaMaxima);
void exibirMenuAcao(int pocoes);
void exibirAtaque(const std::string& atacante, const std::string& defensor,
                  int dano, bool critico, bool defendendo);
void exibirMensagem(const std::string& texto, TipoMensagem tipo);
void exibirResumo(const std::string& nome, int vida, int vidaMaxima,
                  int pocoes, int batalha, int total);
void exibirVitoria(const std::string& nomeHeroi);
void exibirDerrota();
    // const, apenas para exibir
#endif