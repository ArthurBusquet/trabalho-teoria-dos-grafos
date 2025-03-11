#include <iostream>
#include <fstream>
#include "../include/GrafoLista.h"

using namespace std;

// Construtor da classe GrafoLista
// Inicializa as listas encadeadas de vértices e arestas.
GrafoLista::GrafoLista()
{
    vertices = new ListaEncadeada<VerticeEncadeado>(); // Criação da lista de vértices
    arestas = new ListaEncadeada<ArestaEncadeada>();   // Criação da lista de arestas
}

// Função responsável por inicializar o grafo a partir de um arquivo
// Lê o arquivo, inicializa os vértices e arestas, e define o tipo de grafo (direcionado ou não) e ponderado.
void GrafoLista::inicializa_grafo()
{
    ifstream arquivo("./entradas/Grafo.txt");
    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
        return;
    }

    std::string linha;
    int numNos;
    bool direcionado, ponderadoVertices, ponderadoArestas;

    // Lê as propriedades do grafo (número de nós, direcionado, ponderado para vértices e arestas)
    arquivo >> numNos >> direcionado >> ponderadoVertices >> ponderadoArestas;

    // Criação dos vértices, com ou sem peso
    for (int i = 1; i <= numNos; i++)
    {
        int j;
        arquivo >> j;
        if (vertice_ponderado())
        {
            set_vertice(i, j);
        }
        else
        {
            set_vertice(i, 1); // Se não for ponderado, o peso será 1
        }
    }

    int origem, destino = 1;
    float peso = 0;
    while (arquivo >> origem >> destino >> peso)
    {
        set_aresta(origem, destino, peso);
    }

    arquivo.close();
}

// Método privado para buscar um vértice pela ID (usado para obter um vértice encadeado)
VerticeEncadeado *GrafoLista::get_vertice_encadeado(int id)
{
    VerticeEncadeado *vertice = vertices->getInicio();

    while (vertice != nullptr)
    {
        if (vertice->getId() == id)
        {
            return vertice; // Retorna o vértice encontrado
        }
        vertice = vertice->getProximo();
    }
    return nullptr;
}

// Função para retornar o peso de um vértice dado seu ID.
int GrafoLista::get_vertice(int id)
{
    VerticeEncadeado *vertice = vertices->getInicio();

    while (vertice != nullptr)
    {
        if (vertice->getId() == id)
        {
            return vertice->getPeso(); // Retorna o peso do vértice
        }
        vertice = vertice->getProximo();
    }
    return -1; // Retorna -1 caso o vértice não seja encontrado
}

// Função para retornar o peso da aresta entre dois vértices, dado seu ID
int GrafoLista::get_aresta(int idOrigem, int idDestino)
{
    ArestaEncadeada *aresta = arestas->getInicio();
    

    while (aresta != nullptr)
    {
        if (aresta->getOrigem()->getId() == idOrigem && aresta->getDestino()->getId() == idDestino)
        {
            return aresta->getPeso(); // Retorna o peso da aresta
        }
        aresta = aresta->getProximo();
    }
    return -1; // Retorna -1 caso a aresta não seja encontrada
}

// Função para adicionar um vértice ao grafo
// Verifica se o vértice já existe, e se não, cria e adiciona.
void GrafoLista::set_vertice(int id, float peso)
{
    if (get_vertice_encadeado(id) != nullptr)
    {
        cout << "VerticeEncadeado com ID " << id << " já existe!" << endl;
        return;
    }
    VerticeEncadeado *novoVertice = new VerticeEncadeado(id, peso);
    vertices->adicionar(novoVertice); // Adiciona o novo vértice à lista
}

// Função para adicionar uma aresta ao grafo
// Verifica se a aresta já existe, e se não, cria e adiciona.
void GrafoLista::set_aresta(int origem, int destino, float peso)
{
    // Se o grafo não for direcionado, sempre ordenamos os vértices
    if (!eh_direcionado() && origem > destino)
    {
        swap(origem, destino);
    }

    // Verifica se a aresta já existe
    ArestaEncadeada *atual = arestas->getInicio();
    while (atual != nullptr)
    {
        if (atual->getOrigem()->getId() == origem && atual->getDestino()->getId() == destino)
        {
            return; // Se a aresta já existe, não a adicionamos novamente
        }
        atual = atual->getProximo();
    }

    // Obtém os vértices de origem e destino
    VerticeEncadeado *verticeOrigem = get_vertice_encadeado(origem);
    VerticeEncadeado *verticeDestino = get_vertice_encadeado(destino);

    if (verticeOrigem == nullptr || verticeDestino == nullptr)
    {
        cout << "Erro: Um ou ambos os vértices não existem!" << endl;
        return;
    }

    // Cria e adiciona a nova aresta
    ArestaEncadeada *novaAresta = new ArestaEncadeada(verticeOrigem, verticeDestino, peso);
    arestas->adicionar(novaAresta);

    // Adiciona conexão ao vértice de origem (somente uma vez)
    verticeOrigem->setConexao(verticeDestino, peso);
}

// Função que retorna o grau de um vértice, ou seja, o número de conexões (arestas) que ele possui.
int GrafoLista::get_vizinhos(int id)
{
    VerticeEncadeado *vertice = get_vertice_encadeado(id);

    if (vertice == nullptr)
        return 0; // Se o vértice não existe, retorna 0

    return vertice->getGrau(); // Retorna o grau do vértice
}

// Função de busca em profundidade (DFS) que visita todos os vértices conectados a partir de um vértice específico.
void GrafoLista::buscaEmProfundidade(VerticeEncadeado *vertice, bool *visitados)
{
    visitados[vertice->getId()] = true; // Marca o vértice como visitado

    ArestaEncadeada *aresta = vertice->getPrimeiraConexao();
    while (aresta != nullptr)
    {
        VerticeEncadeado *vizinho = aresta->getDestino();
        if (!visitados[vizinho->getId()])
        {
            buscaEmProfundidade(vizinho, visitados); // Chama recursivamente para os vizinhos
        }
        aresta = aresta->getProximo(); // Move para a próxima aresta
    }
}

// Função que imprime os vértices, arestas e algumas propriedades do grafo.
void GrafoLista::imprimir()
{
    cout << "Vertices:\n";
    vertices->imprimir(); // Imprime todos os vértices
    cout << "Arestas:\n";
    arestas->imprimir(); // Imprime todas as arestas
    cout << "\n";
    cout << "grau do grafo: " << get_grau() << "\n";             // Imprime o grau do grafo
    cout << "Quantidade de componentes conexas: " << n_conexo(); // Imprime o número de componentes conexas
}

// Função para adicionar uma nova aresta ao grafo, verificando se ela já existe.
void GrafoLista::nova_aresta(int origem, int destino, int peso)
{
    // Verifica se a aresta já existe
    if (get_aresta(origem, destino) != -1)
    {
        return; // Se a aresta já existe, não a adiciona novamente
    }

    // Obtém os vértices de origem e destino
    VerticeEncadeado *verticeOrigem = get_vertice_encadeado(origem);
    VerticeEncadeado *verticeDestino = get_vertice_encadeado(destino);

    if (!verticeOrigem || !verticeDestino)
    {
        cout << "Erro: Um ou ambos os vértices não existem!" << endl;
        return;
    }

    // Cria e adiciona a nova aresta
    ArestaEncadeada *novaAresta = new ArestaEncadeada(verticeOrigem, verticeDestino, peso);
    arestas->adicionar(novaAresta);

    verticeOrigem->setConexao(verticeDestino, peso); // Cria a conexão no sentido origem -> destino

    // Se o grafo não for direcionado, adiciona também no sentido inverso
    if (!eh_direcionado())
    {
        verticeDestino->setConexao(verticeOrigem, peso); // Cria a conexão no sentido destino -> origem
    }
}

// Destruidor da classe GrafoLista
// Libera a memória utilizada pelas listas de vértices e arestas.
GrafoLista::~GrafoLista()
{
    delete vertices; // Libera a lista de vértices
    delete arestas;  // Libera a lista de arestas
}
