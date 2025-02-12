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
    graph->maior_menor_distancia();
    std::cout << "----------------------------------------" << std::endl;
}

int main(int argc, char *argv[])
{
    Grafo *graph;
    if (argc < 4)
    {
        std::cerr << "Uso incorreto. Veja as opções abaixo:\n";
        std::cerr << "Caso 1: ./main.out -d -m grafo.txt\n";
        std::cerr << "Caso 2: ./main.out -d -l grafo.txt\n";
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
    }

        std::cout << "\nEstado inicial do grafo:\n";
        imprimirDescricaoGrafo(graph);

    delete graph;
    return 0;
}
