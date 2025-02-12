#include <iostream>
#include <fstream>
#include "../include/GrafoLista.h"

using namespace std;

/**
 * @brief Construtor da classe GrafoLista.
 * 
 * Inicializa as listas encadeadas de vértices e arestas.
 */
GrafoLista::GrafoLista()
{
    vertices = new ListaEncadeada<VerticeEncadeado>();
    arestas = new ListaEncadeada<ArestaEncadeada>();
}

/**
 * @brief Obtém um vértice encadeado pelo seu identificador.
 * @param id Identificador do vértice.
 * @return Ponteiro para o vértice encontrado ou nullptr se não existir.
 */
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

/**
 * @brief Obtém o peso de um vértice pelo seu identificador.
 * @param id Identificador do vértice.
 * @return Peso do vértice ou -1 se não existir.
 */
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
/**
 * @brief Adiciona um novo vértice ao grafo.
 * @param peso Peso do novo vértice.
 */
void GrafoLista::novo_no(int peso) {
    // Aumenta a ordem do grafo
    aumenta_ordem();

    // Cria um novo vértice com o id correspondente
    set_vertice(get_ordem(), peso); // O peso pode ser inicializado com 0 ou outro valor, dependendo da necessidade
}

/**
 * @brief Obtém o peso de uma aresta entre dois vértices.
 * @param idOrigem Identificador do vértice de origem.
 * @param idDestino Identificador do vértice de destino.
 * @return Peso da aresta ou -1 se não existir.
 */
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

/**
 * @brief Adiciona um novo vértice ao grafo.
 * @param id Identificador do vértice.
 * @param peso Peso do vértice.
 */
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

/**
 * @brief Adiciona uma nova aresta ao grafo.
 * @param origem Identificador do vértice de origem.
 * @param destino Identificador do vértice de destino.
 * @param peso Peso da aresta.
 */
void GrafoLista::set_aresta(int origem, int destino, float peso)
{
    ArestaEncadeada *atual = arestas->getInicio();
    while (atual != nullptr)
    {
        if ((atual->getOrigem()->getId() == origem &&
            atual->getDestino()->getId() == destino) || (!eh_direcionado() && atual->getOrigem()->getId() == destino &&
            atual->getDestino()->getId() == origem))
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
    verticeOrigem->setConexao(verticeDestino, peso);

    if (!eh_direcionado()) {
        verticeDestino->setConexao(verticeOrigem, peso);
    }
    arestas->adicionar(novaAresta);
}

/**
 * @brief Obtém o número de vizinhos de um vértice.
 * @param id Identificador do vértice.
 * @return Número de vizinhos do vértice.
 */
int GrafoLista::get_vizinhos(int id)
{
    VerticeEncadeado *vertice = get_vertice_encadeado(id);

    if (vertice == nullptr)
        return 0;

    return vertice->getGrau();
}

/**
 * @brief Realiza uma busca em profundidade (DFS) no grafo.
 * @param vertice Ponteiro para o vértice inicial da busca.
 * @param visitados Vetor de vértices visitados.
 */
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

/**
 * @brief Imprime os vértices e as arestas do grafo.
 */
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

/**
 * @brief Remove uma aresta do grafo.
 * @param origem Identificador do vértice de origem.
 * @param destino Identificador do vértice de destino.
 */
void GrafoLista::deleta_aresta(int origem, int destino) {
    if (get_aresta(origem, destino) == -1) {
        cout << "Aresta entre " << origem << " e " << destino << " não existe!" << endl;
        return;
    }

    VerticeEncadeado* verticeOrigem = get_vertice_encadeado(origem);
    VerticeEncadeado* verticeDestino = get_vertice_encadeado(destino);

    if (!verticeOrigem || !verticeDestino) {
        return;
    }

    verticeOrigem->removeConexao(verticeDestino);

    if (!eh_direcionado()) {
        verticeDestino->removeConexao(verticeOrigem);
    }
}

/**
 * @brief Remove um vértice e todas as suas conexões do grafo.
 * @param id Identificador do vértice a ser removido.
 */
void GrafoLista::deleta_no(int id) {
    VerticeEncadeado* verticeAnterior = nullptr;
    VerticeEncadeado* verticeAtual = vertices->getInicio();

    while (verticeAtual != nullptr) {
        ArestaEncadeada* conexao = verticeAtual->getConexoes()->getInicio();
        ArestaEncadeada* proximaConexao;

        while (conexao != nullptr) {
            proximaConexao = conexao->getProximo();
            deleta_aresta(verticeAtual->getId(), conexao->getDestino()->getId());
            conexao = proximaConexao;
        }

        if (verticeAtual->getId() == id) {
            if (verticeAnterior == nullptr) {
                vertices->setInicio(verticeAtual->getProximo());
            } else {
                verticeAnterior->setProximo(verticeAtual->getProximo());
            }
            delete verticeAtual;
            set_ordem(get_ordem() - 1);
        }
        verticeAnterior = verticeAtual;
        verticeAtual = verticeAtual->getProximo();
    }
}
/**
 * @brief Adiciona uma nova aresta ao grafo.
 * @param origem Identificador do vértice de origem.
 * @param destino Identificador do vértice de destino.
 * @param peso Peso da aresta.
 */
void GrafoLista::nova_aresta(int origem, int destino, int peso) {
    // Verifica se a aresta já existe
    if (get_aresta(origem, destino) != -1) {
        cout << "Aresta entre " << origem << " e " << destino << " já existe!" << endl;
        return;
    }

    // Obtém os vértices de origem e destino
    VerticeEncadeado *verticeOrigem = get_vertice_encadeado(origem);
    VerticeEncadeado *verticeDestino = get_vertice_encadeado(destino);

    if (!verticeOrigem || !verticeDestino) {
        cout << "Erro: Um ou ambos os vértices não existem!" << endl;
        return;
    }

    // Cria e adiciona a nova aresta
    ArestaEncadeada *novaAresta = new ArestaEncadeada(verticeOrigem, verticeDestino, peso);
    arestas->adicionar(novaAresta);

    verticeOrigem->setConexao(verticeDestino, peso);
    
    // Se não for direcionado, adiciona também no destino
    if (!eh_direcionado()) {
        verticeDestino->setConexao(verticeOrigem, peso);
    }
}

/**
 * @brief Destrutor da classe GrafoLista.
 */
GrafoLista::~GrafoLista()
{
    delete vertices;
    delete arestas;
}
