#include <iostream>
#include <string>
#include "Interface.hpp"
#include "Personagem.hpp"
// gerei com IA uma pequena interface, ao inves de fazer um campo de batalha

static std::string repetir(char c, int n) {
    return std::string(n, c);
}

static std::string centralizar(const std::string& texto, int largura) {
    int espacos = (largura - (int)texto.size()) / 2;
    if (espacos < 0) espacos = 0;
    int espacoDir = largura - (int)texto.size() - espacos;
    if (espacoDir < 0) espacoDir = 0;
    return repetir(' ', espacos) + texto + repetir(' ', espacoDir);
}

// Funcoes da interface
void exibirCabecalho() {
    std::cout << "\n";
    std::cout << "  +" << repetir('=', LARGURA_CAIXA) << "+\n";
    std::cout << "  |" << centralizar("SIMULADOR DE BATALHA RPG", LARGURA_CAIXA) << "|\n";
    std::cout << "  |" << centralizar(" A Horda dos Goblins ", LARGURA_CAIXA)  << "|\n";
    std::cout << "  +" << repetir('=', LARGURA_CAIXA) << "+\n\n";
}

void exibirCaixaTitulo(const std::string& titulo) {
    std::cout << "\n  +" << repetir('-', LARGURA_CAIXA) << "+\n";
    std::cout << "  |" << centralizar(titulo, LARGURA_CAIXA) << "|\n";
    std::cout << "  +" << repetir('-', LARGURA_CAIXA) << "+\n";
}

void exibirSeparador() {
    std::cout << "  " << repetir('-', LARGURA_CAIXA + 2) << "\n";
}

// Exibe barra de vida no formato

void exibirBarraDeVida(const std::string& nome, int vida, int vidaMaxima) {
    int preenchido = (vida * TAMANHO_BARRA) / vidaMaxima;
    if (preenchido < 0) preenchido = 0;
    if (preenchido > TAMANHO_BARRA) preenchido = TAMANHO_BARRA;
    int vazio = TAMANHO_BARRA - preenchido;

    std::cout << "  [ " << nome << " ]\n";
    std::cout << "  Vida: [";
    for (int i = 0; i < preenchido; i++) std::cout << "#";
    for (int i = 0; i < vazio;      i++) std::cout << ".";
    std::cout << "] " << vida << "/" << vidaMaxima << "\n";
}

void exibirMenuAcao(int pocoes) {
    std::cout << "\n  +" << repetir('-', LARGURA_CAIXA) << "+\n";
    std::cout << "  |" << centralizar("--- SEU TURNO ---", LARGURA_CAIXA) << "|\n";
    std::cout << "  +" << repetir('-', LARGURA_CAIXA) << "+\n";
    std::cout << "  | 1. Atacar com a Espada" << repetir(' ', 19) << "|\n";
    std::cout << "  | 2. Defender (reduz dano pela metade)" << repetir(' ', 4)  << "|\n";
    std::cout << "  | 3. Usar Pocao de Cura (30 HP) [";

    // Mostra os icones de poção disponíveis
    for (int i = 0; i < pocoes;       i++) std::cout << "*";
    for (int i = pocoes; i < MAX_POCOES; i++) std::cout << ".";
    std::cout << "]   |\n";

    std::cout << "  +" << repetir('-', LARGURA_CAIXA) << "+\n";
    std::cout << "  Escolha: ";
}

void exibirAtaque(const std::string& atacante, const std::string& defensor,
                  int dano, bool critico, bool defendendo) {
    if (critico)   std::cout << "  *** GOLPE CRITICO! ***\n";
    if (defendendo) std::cout << "  >> Escudo levantado! Dano reduzido!\n";

    if (dano > 0) {
        std::cout << "  >> " << atacante << " ataca " << defensor
                  << " causando " << dano << " de dano!\n";
    } else {
        std::cout << "  >> Ataque de " << atacante
                  << " foi completamente bloqueado por " << defensor << "!\n";
    }
}

void exibirMensagem(const std::string& texto, TipoMensagem tipo) {
    std::string prefixo;
    switch (tipo) {
        case TipoMensagem::DANO:    prefixo = "  [DANO]   "; break;
        case TipoMensagem::CRITICO: prefixo = "  [CRIT]   "; break;
        case TipoMensagem::DEFESA:  prefixo = "  [DEF]    "; break;
        case TipoMensagem::CURA:    prefixo = "  [CURA]   "; break;
        case TipoMensagem::AVISO:   prefixo = "  [AVISO]  "; break;
        case TipoMensagem::INFO:    prefixo = "  [INFO]   "; break;
    }
    std::cout << prefixo << texto << "\n";
}

void exibirResumo(const std::string& nome, int vida, int vidaMaxima,
                  int pocoes, int batalha, int total) {
    std::cout << "\n  +" << repetir('=', LARGURA_CAIXA) << "+\n";
    std::cout << "  |" << centralizar("RESULTADO DA BATALHA " +
                   std::to_string(batalha) + "/" +
                   std::to_string(total), LARGURA_CAIXA) << "|\n";
    std::cout << "  +" << repetir('-', LARGURA_CAIXA) << "+\n";
    exibirBarraDeVida(nome, vida, vidaMaxima);
    std::cout << "  Pocoes restantes: ";
    for (int i = 0; i < pocoes;       i++) std::cout << "[*]";
    for (int i = pocoes; i < MAX_POCOES; i++) std::cout << "[.]";
    std::cout << "\n";
    std::cout << "  +" << repetir('=', LARGURA_CAIXA) << "+\n";
}

void exibirVitoria(const std::string& nomeHeroi) {
    std::cout << "\n  +" << repetir('=', LARGURA_CAIXA) << "+\n";
    std::cout << "  |" << centralizar("*** VITORIA! ***", LARGURA_CAIXA)          << "|\n";
    std::cout << "  |" << centralizar(nomeHeroi + " sobreviveu a horda!", LARGURA_CAIXA) << "|\n";
    std::cout << "  +" << repetir('=', LARGURA_CAIXA) << "+\n\n";
}

void exibirDerrota() {
    std::cout << "\n  +" << repetir('=', LARGURA_CAIXA) << "+\n";
    std::cout << "  |" << centralizar("*** DERROTA ***", LARGURA_CAIXA)           << "|\n";
    std::cout << "  |" << centralizar("O Heroi caiu em batalha...", LARGURA_CAIXA) << "|\n";
    std::cout << "  +" << repetir('=', LARGURA_CAIXA) << "+\n\n";
}