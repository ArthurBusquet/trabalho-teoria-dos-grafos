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
        // Carregar o grafo a partir do arquivo
        
        //graph->nova_aresta(3, 1, 10);

        std::cout << "\nEstado inicial do grafo:\n";
        imprimirDescricaoGrafo(graph);

        // // TESTANDO nova_aresta
        // std::cout << "\n--- Testando nova_aresta ---\n";

        // // Adicionando nova aresta com vértices diferentes para não duplicar aresta entre 1 e 3
        // std::cout << "Adicionando aresta (2 -> 4) com peso 10..." << std::endl;
        // graph->nova_aresta(2, 4, 10);

        // // Verificando se a aresta foi realmente adicionada
        // int peso24 = graph->get_aresta(2, 4);
        // std::cout << "Verificando aresta (2 -> 4): " << peso24 << std::endl;

        // std::cout << endl << "Estado do grafo após adicionar a aresta (2 -> 4):\n";
        // imprimirDescricaoGrafo(graph);

        // std::cout << "Adicionando aresta (4 -> 1) com peso 5..." << std::endl;
        // graph->nova_aresta(4, 1, 5);

        // // Verificando se a aresta foi realmente adicionada
        // int peso41 = graph->get_aresta(4, 1);
        // std::cout << "Verificando aresta (4 -> 1): " << peso41 << std::endl;

        // std::cout << "Estado do grafo após adicionar a aresta (4 -> 1):\n";
        // imprimirDescricaoGrafo(graph);

        // // Garantindo que os valores armazenados são os esperados
        // if (peso24 != 10)
        // {
        //     std::cerr << "Erro: Aresta (2 -> 4) deveria ter peso 10, mas tem " << peso24 << std::endl;
        // }

        // if (peso41 != 5)
        // {
        //     std::cerr << "Erro: Aresta (4 -> 1) deveria ter peso 5, mas tem " << peso41 << std::endl;
        // }
        // else {
        //     std::cerr << "Opção inválida." << std::endl;
        //     return 1;
        // }
        delete graph;
    return 0;
}
