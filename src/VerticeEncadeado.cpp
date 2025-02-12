#include "../include/VerticeEncadeado.h"

/**
 * @brief Construtor da classe VerticeEncadeado.
 * 
 * Inicializa um vértice com um identificador e peso fornecidos. O grau é inicialmente 0,
 * e a lista de conexões é alocada dinamicamente.
 * 
 * @param id Identificador único do vértice.
 * @param peso Peso do vértice.
 */
VerticeEncadeado::VerticeEncadeado(int id, int peso)
    : id(id), peso(peso), grau(0), proximo(nullptr), conexoes(new ListaEncadeada<ArestaEncadeada>()) {}

/**
 * @brief Obtém o identificador do vértice.
 * @return O identificador do vértice.
 */
int VerticeEncadeado::getId() const {
    return id;
}

/**
 * @brief Obtém o peso do vértice.
 * @return O peso do vértice.
 */
int VerticeEncadeado::getPeso() const {
    return peso;
}

/**
 * @brief Obtém o grau do vértice (número de conexões).
 * @return Grau do vértice.
 */
int VerticeEncadeado::getGrau() const {
    return grau;
}

/**
 * @brief Obtém o próximo vértice encadeado.
 * @return Ponteiro para o próximo vértice na lista encadeada.
 */
VerticeEncadeado* VerticeEncadeado::getProximo() const {
    return proximo;
}

/**
 * @brief Adiciona uma conexão entre este vértice e outro vértice.
 * 
 * Cria uma nova aresta conectando este vértice ao vértice de destino e a adiciona à lista de conexões.
 * 
 * @param verticeDestino Ponteiro para o vértice de destino.
 * @param pesoAresta Peso da aresta que conecta os dois vértices.
 */
void VerticeEncadeado::setConexao(VerticeEncadeado* verticeDestino, int pesoAresta) {
    ArestaEncadeada* novaAresta = new ArestaEncadeada(this, verticeDestino, pesoAresta);
    conexoes->adicionar(novaAresta);
    grau++; 
}

/**
 * @brief Obtém a primeira conexão (aresta) do vértice.
 * @return Ponteiro para a primeira aresta conectada ao vértice.
 */
ArestaEncadeada* VerticeEncadeado::getPrimeiraConexao() {
    return conexoes->getInicio();
}

/**
 * @brief Obtém a lista de conexões (arestas) do vértice.
 * @return Ponteiro para a lista encadeada de arestas.
 */
ListaEncadeada<ArestaEncadeada>* VerticeEncadeado::getConexoes() {
    return conexoes;
}

/**
 * @brief Define o próximo vértice na lista encadeada.
 * @param novoProximo Ponteiro para o novo próximo vértice.
 */
void VerticeEncadeado::setProximo(VerticeEncadeado* novoProximo) {
    proximo = novoProximo;
}

/**
 * @brief Define a lista de conexões do vértice.
 * @param novasConexoes Ponteiro para a nova lista de conexões.
 */
void VerticeEncadeado::setConexoes(ListaEncadeada<ArestaEncadeada>* novasConexoes) {
    conexoes = novasConexoes;
}

/**
 * @brief Obtém uma conexão específica entre dois vértices.
 * 
 * Percorre a lista de conexões para encontrar uma aresta que conecte o vértice de origem ao de destino.
 * 
 * @param origem Identificador do vértice de origem.
 * @param destino Identificador do vértice de destino.
 * @return Ponteiro para a aresta correspondente ou nullptr se não existir.
 */
ArestaEncadeada* VerticeEncadeado::getConexao(int origem, int destino) {
    ArestaEncadeada* arestaAtual = conexoes->getInicio();

    while (arestaAtual != nullptr) {
        if (arestaAtual->getOrigem()->getId() == origem && arestaAtual->getDestino()->getId() == destino)
            break;

        arestaAtual = arestaAtual->getProximo();
    }
    return arestaAtual;
}

/**
 * @brief Remove uma conexão específica deste vértice para outro vértice.
 * 
 * Encontra a aresta que conecta este vértice ao vértice de destino e a remove da lista de conexões.
 * Reduz o grau do vértice após a remoção.
 * 
 * @param destino Ponteiro para o vértice de destino da conexão a ser removida.
 * @return Peso da aresta removida ou 0 se a conexão não existir.
 */
int VerticeEncadeado::removeConexao(VerticeEncadeado* destino) {
    ArestaEncadeada* aresta = getConexao(id, destino->getId());
    if (aresta == nullptr)
        return 0;

    int pesoAresta = aresta->getPeso();
    conexoes->remover(aresta);
    grau--;
    return pesoAresta;
}

/**
 * @brief Sobrecarga do operador de saída para exibir informações do vértice.
 * 
 * Exibe o identificador, peso e grau do vértice, bem como suas conexões.
 * 
 * @param os Fluxo de saída.
 * @param vertice Vértice a ser exibido.
 * @return Fluxo de saída atualizado.
 */
std::ostream& operator<<(std::ostream& os, const VerticeEncadeado& vertice) {
    os << "VerticeEncadeado " << vertice.id
       << " (Peso: " << vertice.peso << ", Grau: " << vertice.grau << ")\n";
    os << "Conexoes: ";
    vertice.conexoes->imprimir();
    return os;
}
