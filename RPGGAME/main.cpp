#include <iostream>   
#include <cstdlib>     // rand e srand numeros aleatorios
#include <ctime>     
#include "Personagem.hpp"  
#include "Goblin.hpp"     
#include "Interface.hpp"   

int main() {        // inicializa o gerador de numeros aleatorios com o tempo atual
    srand(static_cast<unsigned int>(time(0)));

    exibirCabecalho();

    // inicial
    std::string nomeHeroi;
    int qtdInimigos = 0;

    std::cout << "  Nome do seu Heroi: ";
    std::getline(std::cin, nomeHeroi);

    std::cout << "  Quantos Goblins deseja enfrentar? ";
    std::cin >> qtdInimigos;
                                // encerra o jogo se o jogador nao escolher nenhum inimigo
    if (qtdInimigos <= 0) {
        exibirMensagem("Covarde! O jogo foi encerrado.", TipoMensagem::AVISO);
        return 0;
    }

    // criaçao dos personaagens
    // ponteiro para vetor de Goblins alocado dinamicamente
    // o tamanho so e conhecido apos o usuario digitar a quantidade de inimigos(tempo de execuçao)
    Personagem heroi(nomeHeroi, 100, 15, 5, 0.25);
    Goblin* horda = new Goblin[qtdInimigos];

    // reiniciacada goblin com seu indice e nivel de batalha
    for (int i = 0; i < qtdInimigos; i++) {
        horda[i] = Goblin(i, i + 1); // nivel escala com a posição na horda
    }                                // goblins mais ao final sao mais fortes

    // loop principal das batalhas
    for (int i = 0; i < qtdInimigos; i++) {

        // acessando via aritmetica de ponteiro
        Goblin* goblinAtual = (horda + i);
        // (horda + i) avanca o ponteiro i posições apontando para o goblin da vez
        exibirCaixaTitulo("BATALHA " + std::to_string(i + 1) +
                          " DE "     + std::to_string(qtdInimigos));
        goblinAtual->exibirApresentacao();

        //  rodadas 
        for (int rodada = 1; rodada <= 3; rodada++) {
            if (heroi.getVida() <= 0 || goblinAtual->getVida() <= 0) break;

            exibirCaixaTitulo("RODADA " + std::to_string(rodada) + " DE 3");

            heroi.exibirStatus();
            goblinAtual->exibirStatus(); // acesso via ponteiro ->
            exibirSeparador();

            //  turno heroi
            heroi.resetarDefesa();
            int escolha = solicitarAcao(heroi);

            switch (escolha) {     //*goblinAtual desreferencia o ponteiro acessando o objeto Goblin diretamente
                case 1: realizarAtaque(heroi, *goblinAtual); break; // desreferencia *
                case 2: heroi.defender();                    break;
                case 3: heroi.curar(30);                     break;
                default:
                    exibirMensagem("Opcao invalida! Turno perdido.", TipoMensagem::AVISO);
                    break;
            }

            //turno do goblin
            if (goblinAtual->getVida() > 0) {
                exibirSeparador();
                std::cout << "  --- TURNO DO GOBLIN ---\n";
                goblinAtual->executarTurno(heroi); // goblin automatizado
            }
        }

        // resuktado da batalha 
        exibirResultadoBatalha(heroi, i + 1, qtdInimigos);

        if (heroi.getVida() <= 0) {
            exibirDerrota();
            break;
        } else if (goblinAtual->getVida() <= 0) {
            exibirMensagem("Goblin derrotado! Voce avanca. Marcha.", TipoMensagem::INFO);
        } else {
            exibirMensagem("3 rodadas encerradas! O Goblin pegou o Beco.", TipoMensagem::INFO);
        }
    }

    // resultado final
    if (heroi.getVida() > 0) {
        exibirVitoria(heroi.getNome());
    }
    
    // delete, libera o vetor de goblins alocado com new
    delete[] horda;

    return 0;
}