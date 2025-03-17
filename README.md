# trabalho-teoria-dos-grafos-
Novo repositorio para o trabalho de teoria dos grafos

Para compilar use: g++ -o main.out main.cpp src/*.cpp -I./include -g -Wall -Werror

Para executar com lista use: time ./main.out -p -l grafo.txt

Para executar com a matriz use: time ./main.out -p -m grafo.txt

p = {1,2,3,4,5,6,7,8,9,10} para escolher a instância.

Para rodar o comando com Valgrind:
    Primeiro execute o comando: alias valgrind-simple='valgrind --leak-check=full'

    Agora é só executar usando: 
        valgrind ./main.out -p -m grafo.txt
        valgrind ./main.out -p -l grafo.txt