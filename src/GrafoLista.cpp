#include <iostream>
#include <fstream>
#include "../include/GrafoLista.h"
#include "../include/Cluster.h"
#include "../include/ListaEncadeada.h"

using namespace std;

GrafoLista::GrafoLista()
{
    vertices = new ListaEncadeada<VerticeEncadeado>();
    arestas = new ListaEncadeada<ArestaEncadeada>();

    cout << "🔍 [DEBUG GRAFO_LISTA] Antes da inicialização, clusters = " << clusters << endl;

    // Verifica se clusters está corrompido antes de usá-lo
    if (!clusters || reinterpret_cast<uintptr_t>(clusters) < 0x1000) {
        cout << "🚨 [DEBUG] clusters estava inválido! Inicializando corretamente...\n";
        clusters = new ListaEncadeada<Cluster>();

        if (!clusters) {
            cerr << "❌ [ERRO FATAL] Falha ao alocar clusters!" << endl;
            exit(EXIT_FAILURE);
        }
        cout << "✅ [DEBUG] clusters inicializado com sucesso! Endereço: " << clusters << endl;
    }
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

int GrafoLista::get_vizinhos(int id)
{
    VerticeEncadeado *vertice = get_vertice_encadeado(id);

    if (vertice == nullptr)
        return 0;

    return vertice->getGrau();
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

    verticeOrigem->setConexao(verticeDestino, peso); // Comentei o direcionado, pq tu ja pega ele lá na função usando eh_direcionado()
    
    // Se não for direcionado, adiciona também no destino
    if (!eh_direcionado()) {
        verticeDestino->setConexao(verticeOrigem, peso); // idem
    }
}

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

    // Remove da lista de conexões do vértice de origem
    verticeOrigem->removeConexao(verticeDestino);

    // Se não for direcionado, remove do destino também
    if (!eh_direcionado()) {
        verticeDestino->removeConexao(verticeOrigem);
    }
}

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


void GrafoLista::novo_no(int peso) {
    // Aumenta a ordem do grafo
    aumenta_ordem();

    // Cria um novo vértice com o id correspondente
    set_vertice(get_ordem(), peso); // O peso pode ser inicializado com 0 ou outro valor, dependendo da necessidade
}
void GrafoLista::imprimirClusters() {
    Cluster* atual = clusters->getInicio();
    while (atual != nullptr) {
        atual->imprimirCluster();
        atual = atual->getProximo();
    }
}




GrafoLista::~GrafoLista()
{
    if (vertices) {
        delete vertices;
        vertices = nullptr;
    }

    if (arestas) {
        delete arestas;
        arestas = nullptr;
    }

    if (clusters) {
        Cluster* atual = clusters->getInicio();
        while (atual != nullptr) {
            Cluster* proximo = atual->getProximo();
            delete atual;
            atual = proximo;
        }
        delete clusters;
        clusters = nullptr; // 🔥 Evita ponteiro inválido
    }
}

