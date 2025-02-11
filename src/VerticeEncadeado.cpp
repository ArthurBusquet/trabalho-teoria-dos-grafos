#include "../include/VerticeEncadeado.h"

// Construtor de um vértice encadeado
VerticeEncadeado::VerticeEncadeado(int id, int peso)
    : id(id), peso(peso), grau(0), proximo(nullptr), conexoes(new ListaEncadeada<ArestaEncadeada>()) {}

// Getter para o id do vértice
int VerticeEncadeado::getId() const
{
    return id;
}

// Getter para o peso do vértice
int VerticeEncadeado::getPeso() const
{
    return peso;
}

// Getter para o grau do vértice (número de conexões)
int VerticeEncadeado::getGrau() const
{
    return grau;
}

// Getter para o próximo vértice encadeado na lista
VerticeEncadeado* VerticeEncadeado::getProximo() const
{
    return proximo;
}

// Estabelece uma conexão entre o vértice atual e outro vértice com um peso de aresta
void VerticeEncadeado::setConexao(VerticeEncadeado* verticeDestino, int pesoAresta)
{
    // Cria uma nova aresta entre o vértice atual e o destino
    ArestaEncadeada* novaAresta = new ArestaEncadeada(this, verticeDestino, pesoAresta);
    conexoes->adicionar(novaAresta);  // Adiciona a aresta à lista de conexões
    grau++;  // Incrementa o grau do vértice
}

// Retorna a primeira conexão (aresta) do vértice
ArestaEncadeada* VerticeEncadeado::getPrimeiraConexao()
{
    return conexoes->getInicio();  // Retorna a primeira aresta da lista de conexões
}

// Getter para as conexões (arestas) do vértice
ListaEncadeada<ArestaEncadeada>* VerticeEncadeado::getConexoes()
{
    return conexoes;  // Retorna a lista de conexões (arestas)
}

// Estabelece o próximo vértice encadeado na lista
void VerticeEncadeado::setProximo(VerticeEncadeado* novoProximo)
{
    proximo = novoProximo;  // Define o próximo vértice encadeado
}

// Atualiza as conexões do vértice com uma nova lista de conexões
void VerticeEncadeado::setConexoes(ListaEncadeada<ArestaEncadeada>* novasConexoes)
{
    conexoes = novasConexoes;  // Atualiza as conexões do vértice com a nova lista
}

// Retorna uma conexão (aresta) específica entre dois vértices
ArestaEncadeada* VerticeEncadeado::getConexao(int origem, int destino)
{
    ArestaEncadeada* arestaAtual = conexoes->getInicio();  // Começa pela primeira aresta

    while (arestaAtual != nullptr)
    {
        // Se encontrar a aresta correspondente, retorna ela
        if (arestaAtual->getOrigem()->getId() == origem && arestaAtual->getDestino()->getId() == destino)
            break;

        arestaAtual = arestaAtual->getProximo();  // Avança para a próxima aresta
    }
    return arestaAtual;  // Retorna a aresta encontrada ou nullptr se não encontrada
}

// Remove uma conexão (aresta) para o destino especificado
int VerticeEncadeado::removeConexao(VerticeEncadeado* destino)
{
    // Obtém a aresta para o destino
    ArestaEncadeada* aresta = getConexao(id, destino->getId());

    if (aresta == nullptr)  // Se a aresta não for encontrada
        return 0;  // Retorna 0 indicando que a aresta não existe

    int pesoAresta = aresta->getPeso();  // Obtém o peso da aresta
    conexoes->remover(aresta);  // Remove a aresta da lista de conexões
    return pesoAresta;  // Retorna o peso da aresta removida
}

// Sobrecarga do operador de inserção para imprimir o vértice e suas conexões
std::ostream& operator<<(std::ostream& os, const VerticeEncadeado& vertice)
{
    os << "VerticeEncadeado " << vertice.id
       << " (Peso: " << vertice.peso << ", Grau: " << vertice.grau << ")\n";  // Imprime id, peso e grau do vértice
    os << "Conexoes: ";  // Imprime as conexões
    vertice.conexoes->imprimir();  // Imprime a lista de conexões do vértice
    return os;  // Retorna o fluxo de saída
}
