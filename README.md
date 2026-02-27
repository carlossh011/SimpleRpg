# Sobre O Trabalho
No trabalho anterior em grupo a gente tinha feito um RPG, então decidi manter o tema e aproveitar para explorar o uso de ponteiros, já que quando fui pesquisar sobre o assunto vi que eles são bastante usados no desenvolvimento de jogos para gerenciar objetos e memoria.
Dito isso, não sei se utilizei os ponteiros da maneira mais eficiente ou se os apliquei em situações onde eles eram realmente necessários, foi mais uma tentativa de entender como funcionam na pratica do que uma aplicação com um proposito muito bem definido.

## SimpleRpg
Jogo de batalha por turnos no terminal onde o jogador enfrenta uma horda de goblins. Cada goblin tem um tipo diferente com comportamentos e stats únicos, e o jogador deve gerenciar seus ataques, defesas e poções para sobreviver.

## Tipos de Goblin

- Guerreiro — alto dano e alta defesa, estilo tanque
- Arqueiro — alta chance de crítico, baixa defesa
- Xamã — stats medianos, pode se curar durante o combate

## Compilar
g++ *.cpp -o rpg
./rpg
