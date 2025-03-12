#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED

#include <iostream>

using namespace std;

/**
 * @brief A classe ListaEncadeada é uma implementação genérica de uma lista encadeada, capaz de armazenar elementos de qualquer tipo.
 * Esta classe fornece métodos para adicionar, remover e imprimir elementos da lista, além de acessar o primeiro e o último elemento.
 * 
 * @tparam T Tipo dos elementos armazenados na lista.
 */
template <typename T>

class ListaEncadeada {
private:
    /**
     * @brief Ponteiro para o primeiro nó da lista.
     */
    T* primeiro;

    /**
     * @brief Ponteiro para o último nó da lista.
     */
    T* ultimo;

    /**
     * @brief Armazena o tamanho atual da lista.
     */
    int tamanho;

public:
    /**
     * @brief Construtor padrão da lista encadeada. Inicializa a lista com primeiro e último ponteiro nulos.
     */
    ListaEncadeada() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {}

    /**
     * @brief Obtém o primeiro nó da lista.
     * 
     * @return O ponteiro para o primeiro nó.
     */
    T* getInicio() const {
        return primeiro;
    }

    /**
     * @brief Adiciona um novo nó ao final da lista.
     * 
     * @param novoNo Ponteiro para o nó a ser adicionado.
     */
    void adicionar(T* novoNo) {
        if (primeiro == nullptr) {
            primeiro = novoNo;
            ultimo = novoNo;
        } else {
            ultimo->setProximo(novoNo);
            ultimo = novoNo;
        }
        tamanho++;
    }

    /**
     * @brief Imprime todos os elementos da lista.
     * 
     * @note A impressão é feita chamando o operador `<<` do tipo `T` para cada elemento da lista.
     */
    void imprimir() const {
        T* atual = primeiro;
        while (atual != nullptr) {
            cout << *atual << endl;
            atual = atual->getProximo();
        }
    }

    /**
     * @brief Remove um nó específico da lista.
     * 
     * @param noParaRemover Ponteiro para o nó a ser removido.
     * @note Se o nó não for encontrado ou a lista estiver vazia, a operação não será realizada.
     */
    void remover(T* noParaRemover) {
        if(!primeiro || !noParaRemover) {
            return;
        }
        if(primeiro == noParaRemover) {
            primeiro = primeiro->getProximo();
            if (!primeiro) {
                ultimo = nullptr;
            }
            tamanho--;
            delete noParaRemover;
            return;
        }

        T* atual = primeiro;
        while(atual->getProximo() && atual->getProximo() != noParaRemover) {
            atual = atual->getProximo();
        }

        if(atual->getProximo() == noParaRemover) {
            atual->setProximo(noParaRemover->getProximo());

            if (noParaRemover == ultimo) {
                ultimo = atual;
            }
            tamanho--;
            delete noParaRemover;
        }
    }

    /**
     * @brief Retorna o tamanho atual da lista (número de elementos armazenados).
     * 
     * @return O número de elementos na lista.
     */
    int get_tamanho() {
        return tamanho;
    }

    /**
     * @brief Destruidor da lista encadeada. Libera toda a memória alocada para os nós da lista.
     */
    ~ListaEncadeada() {
        T* atual = primeiro;
        while (atual != nullptr) {
            T* proximo = atual->getProximo();
            delete atual;
            atual = proximo;
        }
    }
};

#endif // LISTAENCADEADA_H_INCLUDED
