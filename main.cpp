// #include <iostream>
// #include <fstream>
// #include <string>
// #include <cstdlib>
// #include <ctime>

// #include "include/Grafo.h"
// #include "include/GrafoMatriz.h"
// #include "include/GrafoLista.h"

// void imprimirDescricaoGrafo(Grafo *graph)
// {
//     std::cout << "Grau: " << graph->get_grau() << std::endl;
//     std::cout << "Ordem: " << graph->get_ordem() << std::endl;
//     std::cout << "Direcionado: " << (graph->eh_direcionado() ? "Sim" : "Nao") << std::endl;
//     std::cout << "Componentes conexas: " << graph->n_conexo() << std::endl;
//     std::cout << "Completo: " << graph->eh_completo() << std::endl;
//     std::cout << "Vertices ponderados: " << (graph->vertice_ponderado() ? "Sim" : "Nao") << std::endl;
//     std::cout << "Arestas ponderadas: " << (graph->aresta_ponderada() ? "Sim" : "Nao") << std::endl;
//     graph->maior_menor_distancia();
//     std::cout << "----------------------------------------" << std::endl;
// }

// int main(int argc, char *argv[])
// {
//     Grafo *graph;
//     if (argc < 4)
//     {
//         std::cerr << "Uso incorreto. Veja as opções abaixo:\n";
//         std::cerr << "Caso 1: ./main.out -d -m grafo.txt\n";
//         std::cerr << "Caso 2: ./main.out -d -l grafo.txt\n";
//         return 1;
//     }

//     std::string opcao = argv[1];
//     std::string estrutura = argv[2];

//     if (opcao == "-d")
//     {
//         if (argc != 4)
//         {
//             std::cerr << "Uso incorreto para o modo de descricao." << std::endl;
//             return 1;
//         }
//         std::string caminhoArquivo = argv[3];

       

//         if (estrutura == "-m")
//         {
//             graph = new GrafoMatriz();
//             graph->carrega_grafo();
//             graph->carrega_clusters();
//         }
//         else
//         {
//             graph = new GrafoLista();
//             graph->carrega_grafo();
//             graph->carrega_clusters();
//             graph->imprimirClusters();
//         }
//     }

//         std::cout << "\nEstado inicial do grafo:\n";
//         imprimirDescricaoGrafo(graph);

//     delete graph;
//     return 0;
// }

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
        std::cerr << "Caso 3: ./main.out -p -m grafo.txt\n";
        std::cerr << "Caso 4: ./main.out -p -l grafo.txt\n";
        return 1;
    }

    std::string opcao = argv[1];
    std::string estrutura = argv[2];

    if (opcao == "-d" || opcao == "-p") // Agora aceita -p também
    {
        if (argc != 4)
        {
            std::cerr << "Uso incorreto para o modo selecionado." << std::endl;
            return 1;
        }
        std::string caminhoArquivo = argv[3];
        std::cout << "🔍 [DEBUG MAIN] Antes da criação do grafo: clusters = " << graph << std::endl;

        if (estrutura == "-m")
        {
            graph = new GrafoMatriz();
            graph->carrega_grafo();
        }
        else
        {
            graph = new GrafoLista();
            graph->carrega_grafo();
            std::cout << "🔍 [DEBUG MAIN] Depois da criação do grafo: clusters = " << graph << std::endl;

        }
    }
    else
    {
        std::cerr << "Opcao desconhecida: " << opcao << std::endl;
        return 1;
    }

    if (opcao == "-d")
    {
        std::cout << "\nEstado inicial do grafo:\n";
        imprimirDescricaoGrafo(graph);
    }
    else if (opcao == "-p")
    {
        std::cout << "Processando grafo...\n";
        imprimirDescricaoGrafo(graph);
    }

    std::cout << "🔍 [DEBUG MAIN] Antes de `carrega_clusters()`: clusters = " << graph << std::endl;

    graph->carrega_clusters();
    
    std::cout << "🔍 [DEBUG MAIN] Depois de `carrega_clusters()`: clusters = " << graph << std::endl;

    float pesoTotal = graph->encontrarAGMG();  
    if (pesoTotal >= 0) {
        graph->imprimirAGMG(pesoTotal);
    } else {
        cout << "❌ A AGMG falhou ao ser construída." << endl;
    }
    return 0;
}