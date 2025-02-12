#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED

#include <iostream>

using namespace std;

/**
 * @class ListaEncadeada
 * @brief Implementação genérica de uma lista encadeada.
 * 
 * Esta classe gerencia uma lista encadeada de elementos do tipo `T`.
 * Suporta operações básicas como adição, remoção e impressão dos elementos.
 * 
 * @tparam T Tipo dos elementos armazenados na lista.
 */
template <typename T>
class ListaEncadeada {
private:
    T* primeiro; ///< Ponteiro para o primeiro nó da lista.
    T* ultimo; ///< Ponteiro para o último nó da lista.
    int tamanho; ///< Número de elementos armazenados na lista.

public:
    /**
     * @brief Construtor da lista encadeada.
     * 
     * Inicializa a lista como vazia, com `primeiro` e `ultimo` apontando para nullptr.
     */
    ListaEncadeada() : primeiro(nullptr), ultimo(nullptr), tamanho(0) {}

    /**
     * @brief Obtém o primeiro nó da lista.
     * @return Ponteiro para o primeiro nó da lista.
     */
    T* getInicio() const {
        return primeiro;
    }

    /**
     * @brief Define um novo primeiro nó na lista.
     * @param novoInicio Ponteiro para o novo primeiro nó.
     */
    void setInicio(T* novoInicio) {
        primeiro = novoInicio;
        if (novoInicio == nullptr) {
            ultimo = nullptr;
        }
    }

    /**
     * @brief Adiciona um novo nó ao final da lista.
     * @param novoNo Ponteiro para o novo nó a ser adicionado.
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
     * @brief Imprime todos os elementos da lista encadeada.
     */
    void imprimir() const {
        T* atual = primeiro;
        while (atual != nullptr) {
            cout << *atual << endl;
            atual = atual->getProximo();
        }
    }

    /**
     * @brief Remove um nó específico da lista encadeada.
     * @param noParaRemover Ponteiro para o nó que será removido.
     */
    void remover(T* noParaRemover) {
        if (!primeiro || !noParaRemover) {
            return;
        }
        if (primeiro == noParaRemover) {
            primeiro = primeiro->getProximo();
            if (!primeiro) {
                ultimo = nullptr;
            }
            tamanho--;
            delete noParaRemover;
            return;
        }

        T* atual = primeiro;
        while (atual->getProximo() && atual->getProximo() != noParaRemover) {
            atual = atual->getProximo();
        }

        if (atual->getProximo() == noParaRemover) {
            atual->setProximo(noParaRemover->getProximo());

            if (noParaRemover == ultimo) {
                ultimo = atual;
            }
            tamanho--;
            delete noParaRemover;
        }
    }

    /**
     * @brief Obtém o tamanho atual da lista encadeada.
     * @return Número de elementos na lista.
     */
    int get_tamanho() {
        return tamanho;
    }

    /**
     * @brief Destrutor da lista encadeada.
     * 
     * Libera a memória de todos os nós armazenados na lista.
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
