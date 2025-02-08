#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "include/Grafo.h"
#include "include/GrafoMatriz.h"
#include "include/GrafoLista.h"

void imprimirDescricaoGrafo(Grafo *graph)
{
    std::cout << "Grau: " << graph->get_grau() << std::endl;
    std::cout << "Ordem: " << graph->get_ordem() << std::endl;
    std::cout << "Direcionado: " << (graph->eh_direcionado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Componentes conexas: " << graph->n_conexo() << std::endl;
    std::cout << "Completo: " << graph->eh_completo() << std::endl;
    std::cout << "Vertices ponderados: " << (graph->vertice_ponderado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Arestas ponderadas: " << (graph->aresta_ponderada() ? "Sim" : "Nao") << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Uso incorreto. Veja as op��es abaixo:\n";
        std::cerr << "Caso 1: ./main.out -d -m grafo.txt\n";
        std::cerr << "Caso 2: ./main.out -d -l grafo.txt\n";
        std::cerr << "Caso 3: ./main.out -c -m descricao.txt grafo.txt\n";
        std::cerr << "Caso 4: ./main.out -c -l descricao.txt grafo.txt\n";
        return 1;
    }

    std::string opcao = argv[1];
    std::string estrutura = argv[2];

    if (opcao == "-d")
    {
        if (argc != 4)
        {
            std::cerr << "Uso incorreto para o modo de descricao." << std::endl;
            return 1;
        }
        std::string caminhoArquivo = argv[3];

        Grafo *graph;

        if (estrutura == "-m")
        {

            graph = new GrafoMatriz();

            graph->carrega_grafo();
        }
        else
        {
            graph = new GrafoLista();
            graph->carrega_grafo();
        }
        imprimirDescricaoGrafo(graph);
        delete graph;
    }
    else if (opcao == "-c")
    {
        if (argc != 5)
        {
            std::cerr << "Uso incorreto para o modo de cria��o." << std::endl;
            return 1;
        }
        std::string caminhoDescricao = argv[3];
        std::string caminhoSaida = argv[4];
        bool usarMatriz = (estrutura == "-m");
    }
    else
    {
        std::cerr << "Op��o inv�lida." << std::endl;
        return 1;
    }

    return 0;
}
