#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED

#include <iostream>

using namespace std;

template <typename T>

class ListaEncadeada {
private:
    T* primeiro;
    T* ultimo;
    int tamanho;


public:
    ListaEncadeada() : primeiro(nullptr), ultimo(nullptr) {}

    T* getInicio() const {
        return primeiro;
    }

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

    void imprimir() const {
        T* atual = primeiro;
        while (atual != nullptr) {
            cout << *atual << endl;
            atual = atual->getProximo();
        }
    }

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

    int get_tamanho() {
        return tamanho;
    }


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
