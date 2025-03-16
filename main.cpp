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
    std::cout << "----------------------------------------" << std::endl;

    int *clusters = graph->get_clusters();
    for (int i = 1; i <= graph->get_ordem(); i++)
    {
        std::cout << "Vértice " << i << " está no cluster " << clusters[i] << std::endl;
    }
}

int main(int argc, char *argv[])
{
    Grafo *graph;

    if (argc < 3)
    {
        std::cerr << "Uso incorreto. Veja as opções abaixo:\n";
        std::cerr << "Caso 1: ./main.out -d -m grafo.txt\n";
        std::cerr << "Caso 2: ./main.out -d -l grafo.txt\n";
        std::cerr << "Caso 3: ./main.out -<numero> -m grafo.txt\n";
        std::cerr << "Caso 4: ./main.out -<numero> -l grafo.txt\n";
        return 1;
    }

    std::string opcao = argv[1];
    std::string estrutura;
    int parametro_p = -1; // Inicializa com um valor inválido

    if (opcao == "-d")
    {
        estrutura = argv[2]; // Define a estrutura para o modo -d
    }
    else
    {
        // Verifica se o argumento começa com um '-' e se o número é válido
        if (opcao[0] == '-' && opcao.length() > 1)
        {
            try
            {
                parametro_p = std::stoi(opcao.substr(1)); // Remove o '-' e converte o número
            }
            catch (const std::exception &e)
            {
                std::cerr << "Erro: O valor após o '-' deve ser um número válido entre 1 e 10.\n";
                return 1;
            }

            if (parametro_p < 1 || parametro_p > 10)
            {
                std::cerr << "Erro: O número deve estar entre 1 e 10.\n";
                return 1;
            }

            estrutura = argv[2]; // Define a estrutura (-m ou -l)
        }
        else
        {
            std::cerr << "Erro: O primeiro argumento deve ser -<numero> ou -d.\n";
            return 1;
        }
    }

    std::string caminhoArquivo = argv[argc - 1]; // O arquivo sempre será o último argumento

    if (estrutura == "-m")
    {
        graph = new GrafoMatriz();
    }
    else if (estrutura == "-l")
    {
        graph = new GrafoLista();
    }
    else
    {
        std::cerr << "Erro: Estrutura inválida. Use -m para matriz ou -l para lista.\n";
        return 1;
    }

    if (parametro_p != -1)
    {
        graph->carrega_grafo_novo(parametro_p);
        std::cout << "Processando grafo com p = " << parametro_p << "...\n";
    }
    else
    {
        std::cout << "\nEstado inicial do grafo:\n";
    }

    imprimirDescricaoGrafo(graph);

    delete graph;
    return 0;
}
