#include <iostream>
#include <fstream>
#include "GrafoLista.h"

using namespace std;

GrafoLista::GrafoLista()
{
    vertices = new ListaEncadeada<VerticeEncadeado>();
    arestas = new ListaEncadeada<ArestaEncadeada>();
}

// void GrafoLista::carrega_grafo_lista()
// {
//     std::ifstream arquivo("Grafo.txt");

//     if (!arquivo.is_open())
//     {
//         cerr << "Erro ao abrir o arquivo: Grafo.txt" << endl;
//         std::exit(EXIT_FAILURE);
//     }

//     std::string linha;

//     if (std::getline(arquivo, linha))
//     {
//         int direcionado;
//         int ordem;
//         int atp;
//         int vtp;
//         if (std::sscanf(linha.c_str(), "%d %d %d %d", &ordem, &direcionado, &vtp, &atp) != 4)
//         {
//             cerr << "Formato inválido na primeira linha." << endl;
//             std::exit(EXIT_FAILURE);
//         }

//         set_ordem(ordem);
//         set_eh_direcionado(direcionado);
//         set_vertice_ponderado(vtp);
//         set_aresta_ponderada(atp);
//     }
//     else
//     {
//         cerr << "Arquivo vazio ou formato inválido na primeira linha." << endl;
//         std::exit(EXIT_FAILURE);
//     }

//     if (vertice_ponderado())
//     {
//         if (std::getline(arquivo, linha))
//         {
//             size_t pos = 0;
//             for (int i = 1; i <= get_ordem(); i++)
//             {
//                 size_t nextPos;
//                 try
//                 {
//                     float pesoVertice = std::stof(linha.substr(pos), &nextPos);
//                     pos += nextPos;
//                     set_vertice(i, pesoVertice);
//                 }
//                 catch (...)
//                 {
//                     cerr << "Erro ao converter peso dos vértices." << endl;
//                     std::exit(EXIT_FAILURE);
//                 }
//             }
//         }
//         else
//         {
//             cerr << "Pesos dos vértices não encontrados em arquivo ponderado." << endl;
//             std::exit(EXIT_FAILURE);
//         }
//     }
//     else
//     {
//         for (int i = 1; i <= get_ordem(); i++)
//         {
//             set_vertice(i, 0);
//         }
//     }

//     while (std::getline(arquivo, linha))
//     {
//         int origem, destino, peso = 0;
//         if (aresta_ponderada())
//         {
//             if (std::sscanf(linha.c_str(), "%d %d %d", &origem, &destino, &peso) < 3)
//             {
//                 cerr << "Erro ao ler peso da aresta em grafo ponderado." << endl;
//                 std::exit(EXIT_FAILURE);
//             }
//         }
//         else
//         {
//             if (std::sscanf(linha.c_str(), "%d %d", &origem, &destino) < 2)
//             {
//                 cerr << "Erro ao ler aresta (origem e destino)." << endl;
//                 std::exit(EXIT_FAILURE);
//             }
//         }
//         set_aresta(origem, destino, peso);
//     }

//     arquivo.close();
// }

void GrafoLista::inicializa_grafo()
{
    ifstream arquivo("Grafo.txt");
    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
        return;
    }
    // arquivo >>  >> direcionado >> vtp >> atp;

    std::string linha;

    if (vertice_ponderado())
    {
        if (std::getline(arquivo, linha))
        {
            size_t pos = 0;
            for (int i = 1; i <= get_ordem(); i++)
            {
                size_t nextPos;
                try
                {
                    float pesoVertice = std::stof(linha.substr(pos), &nextPos);
                    pos += nextPos;
                    set_vertice(i, pesoVertice);
                }
                catch (...)
                {
                    cerr << "Erro ao converter peso dos vértices." << endl;
                    std::exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            cerr << "Pesos dos vértices não encontrados em arquivo ponderado." << endl;
            std::exit(EXIT_FAILURE);
        }
    }
    else
    {
        for (int i = 1; i <= get_ordem(); i++)
        {
            set_vertice(i, 0);
        }
    }

    while (std::getline(arquivo, linha))
    {
        int origem, destino, peso = 0;
        if (aresta_ponderada())
        {
            if (std::sscanf(linha.c_str(), "%d %d %d", &origem, &destino, &peso) < 3)
            {
                cerr << "Erro ao ler peso da aresta em grafo ponderado." << endl;
                std::exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (std::sscanf(linha.c_str(), "%d %d", &origem, &destino) < 2)
            {
                cerr << "Erro ao ler aresta (origem e destino)." << endl;
                std::exit(EXIT_FAILURE);
            }
        }
        set_aresta(origem, destino, peso);
    }

    arquivo.close();
}

VerticeEncadeado *GrafoLista::get_vertice_encadeado(int id)
{
    VerticeEncadeado *vertice = vertices->getInicio();

    while (vertice != nullptr)
    {
        if (vertice->getId() == id)
        {
            return vertice;
        }
        vertice = vertice->getProximo();
    }
    return nullptr;
}

int GrafoLista::get_vertice(int id)
{
    VerticeEncadeado *vertice = vertices->getInicio();

    while (vertice != nullptr)
    {
        if (vertice->getId() == id)
        {
            return vertice->getPeso();
        }
        vertice = vertice->getProximo();
    }
    return -1;
}

int GrafoLista::get_aresta(int idOrigem, int idDestino)
{
    ArestaEncadeada *aresta = arestas->getInicio();

    while (aresta != nullptr)
    {
        if (aresta->getOrigem()->getId() == idOrigem && aresta->getDestino()->getId() == idDestino)
        {
            return aresta->getPeso();
        }
        aresta = aresta->getProximo();
    }
    return -1;
}

void GrafoLista::set_vertice(int id, float peso)
{
    if (get_vertice_encadeado(id) != nullptr)
    {
        cout << "VerticeEncadeado com ID " << id << " já existe!" << endl;
        return;
    }
    VerticeEncadeado *novoVertice = new VerticeEncadeado(id, peso);
    vertices->adicionar(novoVertice);
}

void GrafoLista::set_aresta(int origem, int destino, int peso)
{
    ArestaEncadeada *atual = arestas->getInicio();
    while (atual != nullptr)
    {
        if (atual->getOrigem()->getId() == origem &&
            atual->getDestino()->getId() == destino)
        {
            cout << "Aresta entre " << origem << " e " << destino << " já existe!" << endl;
            return;
        }
        atual = atual->getProximo();
    }

    VerticeEncadeado *verticeOrigem = get_vertice_encadeado(origem);
    VerticeEncadeado *verticeDestino = get_vertice_encadeado(destino);
    if (verticeOrigem == nullptr || verticeDestino == nullptr)
    {
        cout << "Erro: Um ou ambos os vértices não existem!" << endl;
        return;
    }

    ArestaEncadeada *novaAresta = new ArestaEncadeada(verticeOrigem, verticeDestino, peso);

    verticeOrigem->setConexao(verticeDestino, peso, false);

    if (!eh_direcionado())
        verticeDestino->setConexao(verticeOrigem, peso, true);
    arestas->adicionar(novaAresta);
}

int GrafoLista::get_vizinhos(int id)
{
    VerticeEncadeado *vertice = get_vertice_encadeado(id);
    int vizinhos[get_ordem() - 1];


    if (vertice == nullptr)
        return 0;

    return vertice->getConexoes()->get_tamanho();
}

void GrafoLista::buscaEmProfundidade(VerticeEncadeado *vertice, bool *visitados)
{
    visitados[vertice->getId()] = true;

    ArestaEncadeada *aresta = vertice->getPrimeiraConexao();
    while (aresta != nullptr)
    {
        VerticeEncadeado *vizinho = aresta->getDestino();
        if (!visitados[vizinho->getId()])
        {
            buscaEmProfundidade(vizinho, visitados);
        }
        aresta = aresta->getProximo();
    }
}

void GrafoLista::imprimir()
{
    cout << "Vertices:\n";
    vertices->imprimir();
    cout << "Arestas:\n";
    arestas->imprimir();
    cout << "\n";
    cout << "grau do grafo: " << get_grau() << "\n";
    cout << "Quantidade de componente conexas: " << n_conexo();
}

GrafoLista::~GrafoLista()
{
    delete vertices;
    delete arestas;
}
