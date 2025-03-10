#include "../include/GrafoMatriz.h"
#include "../include/Grafo.h"
#include "../include/Cluster.h"
#include "../include/ListaEncadeada.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Definindo o tamanho estático da matriz
const int TAMANHO_ESTATICO = 10000; // Defina o tamanho máximo da matriz aqui

GrafoMatriz::GrafoMatriz() {
    tamanhoAtual = TAMANHO_ESTATICO;
    size_t tamanhoAtualLinear = ((size_t)TAMANHO_ESTATICO * (TAMANHO_ESTATICO + 1)) / 2;

    // Aloca matriz 2D estaticamente
    Matriz = new int*[TAMANHO_ESTATICO];
    for (int i = 0; i < TAMANHO_ESTATICO; i++) {
        Matriz[i] = new int[TAMANHO_ESTATICO](); // Inicializa com zero
    }

    // Aloca matriz linear estaticamente
    MatrizLinear = new int[tamanhoAtualLinear](); // Inicializa com zero

    // Inicializa o vetor de pesos dos vértices com 0
    VetorPesosVertices = new int[TAMANHO_ESTATICO](); // Inicializa com zero

    clusters = new ListaEncadeada<Cluster>();
}

GrafoMatriz::~GrafoMatriz() {
    cout << "Destruindo GrafoMatriz..." << endl;

    // Libera a matriz bidimensional de forma segura
    if (Matriz != nullptr) {  // Verifica se o ponteiro da Matriz não é nulo
        for (int i = 0; i < TAMANHO_ESTATICO; i++) {
            if (Matriz[i] != nullptr) {  // Verifica se a linha não é nula antes de liberar
                delete[] Matriz[i]; // Libera apenas se o ponteiro for válido
            }
        }
        delete[] Matriz;  // Libera a matriz inteira
        Matriz = nullptr;  // Evita dangling pointers (ponteiro inválido)
    }

    // Libera a matriz linear de forma segura
    if (MatrizLinear != nullptr) {  // Verifica se o ponteiro não é nulo
        delete[] MatrizLinear;
        MatrizLinear = nullptr;  // Evita dangling pointer
    }

    // Libera o vetor de pesos
    if (VetorPesosVertices != nullptr) {  // Verifica se o vetor não é nulo
        delete[] VetorPesosVertices;
        VetorPesosVertices = nullptr;  // Evita dangling pointer
    }

    Cluster* atual = clusters->getInicio();
    while (atual != nullptr) {
        Cluster* proximo = atual->getProximo();
        delete atual;
        atual = proximo;
    }
    delete clusters;
}

// Método para redimensionar a matriz quadrada (COMENTADO, pois a matriz é estática)
/*
void GrafoMatriz::redimensionarMatriz() {
    int novoTamanho = tamanhoAtual * 2;
    cout << "Redimensionando matriz quadrada para " << novoTamanho << "..." << endl;
    cout << "Aqui" << endl << endl;
    
    int** novaMatriz = new int*[novoTamanho];
    cout << "Aqui" << endl << endl;
    for (int i = 0; i < novoTamanho; i++) {
        
        novaMatriz[i] = new int[novoTamanho];
        
        for (int j = 0; j < novoTamanho; j++) {
            novaMatriz[i][j] = (i < tamanhoAtual && j < tamanhoAtual) ? Matriz[i][j] : 0;
        }
    }

    // Libera matriz antiga
    for (int i = 0; i < tamanhoAtual; i++) {
        delete[] Matriz[i];
    }
    delete[] Matriz;

    // Atualiza ponteiro e tamanho
    Matriz = novaMatriz;
    tamanhoAtual = novoTamanho;
}
*/

// Método para redimensionar a matriz linear (COMENTADO, pois a matriz é estática)
/*
void GrafoMatriz::redimensionarMatrizLinear() {
    int novoTamanho = (tamanhoAtual * (tamanhoAtual + 1)) / 2;
    cout << "Redimensionando matriz linear para " << novoTamanho << "..." << endl;

    int* novaMatrizLinear = new int[novoTamanho];
    for (int i = 0; i < novoTamanho; i++) {
        novaMatrizLinear[i] = (i < tamanhoAtualLinear) ? MatrizLinear[i] : 0;
    }

    // Libera a matriz linear antiga
    delete[] MatrizLinear;

    // Atualiza ponteiro e tamanho
    MatrizLinear = novaMatrizLinear;
    tamanhoAtualLinear = novoTamanho;
}
*/

void GrafoMatriz::carrega_clusters() {
    ifstream arquivo("./entradas/Clusters.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo Clusters.txt" << endl;
        return;
    }

    int clusterId, vertice;
    while (arquivo >> clusterId >> vertice) {
        // Verifica se o cluster já existe na lista
        Cluster* clusterExistente = nullptr;
        Cluster* atual = clusters->getInicio();

        while (atual != nullptr) {
            if (atual->getId() == clusterId) {
                clusterExistente = atual;
                break;
            }
            atual = atual->getProximo();  // ✅ Agora usa `getProximo()`
        }

        // Se não existe, cria um novo cluster
        if (clusterExistente == nullptr) {
            clusterExistente = new Cluster(clusterId);
            clusters->adicionar(clusterExistente);
        }

        // Adiciona o vértice ao cluster correspondente
        clusterExistente->adicionarVertice(vertice);
    }

    arquivo.close();
}





int GrafoMatriz::calcularIndiceLinear(int origem, int destino) {
    if (origem <= destino) {
        return (destino * (destino - 1)) / 2 + origem;
    }
    return (origem * (origem - 1)) / 2 + destino;
}

int GrafoMatriz::get_aresta(int origem, int destino) {
    if (origem < 0 || destino < 0 || origem >= TAMANHO_ESTATICO || destino >= TAMANHO_ESTATICO) {
        //cerr << "Erro: Índices fora dos limites da matriz!" << endl;
        return -1; // Retorno de erro
    }

    if (eh_direcionado()) {
        return Matriz[origem][destino];
    } else {
        if (origem > destino) {
            std::swap(origem, destino);
        }
        int indice = calcularIndiceLinear(origem, destino);
        return MatrizLinear[indice];
    }
}

void GrafoMatriz::set_vertice(int id, float peso) {
    if(!vertice_ponderado())
        peso = 0;

    VetorPesosVertices[id - 1] = peso;
}

void GrafoMatriz::set_aresta(int origem, int destino, float peso) {
    if(!aresta_ponderada())
        peso = 0;
    
    if (eh_direcionado()) {
        Matriz[origem][destino] = peso;
    } else {
        // Certifique-se de que origem é sempre menor ou igual a destino
        if (origem > destino) {
            std::swap(origem, destino);
        }
        int indice = calcularIndiceLinear(origem, destino);
        MatrizLinear[indice] = peso;
    }
}

int GrafoMatriz::get_vertice(int origem) {
    if (vertice_ponderado()) {
        return VetorPesosVertices[origem - 1];
    }
    return 1;
}

int GrafoMatriz::get_vizinhos(int vertice) {
    if (vertice < 1 || vertice > get_ordem()) {
        cerr << "Vértice inválido!" << endl;
        return -1;
    }

    int vizinhos = 0;
    int v = vertice - 1; // Ajustando para índice 0

    if (eh_direcionado()) {
        // Contar arestas de saída (direcionadas)
        for (int i = 0; i < get_ordem(); i++) {
            if (Matriz[v][i] != 0) { // Verifica se existe aresta de v para i
                vizinhos++;
            }
        }
    } else {
        // Grafo não direcionado: verificar matriz comprimida sem contar duplicados
        for (int i = 0; i < get_ordem(); i++) {
            if (i == v) continue; // Evita contar o próprio vértice

            int indice = calcularIndiceLinear(std::min(i + 1, vertice), std::max(i + 1, vertice));
            if (MatrizLinear[indice] != 0) {
                vizinhos++;
            }
        }
    }

    return vizinhos;
}

void GrafoMatriz::nova_aresta(int origem, int destino, int peso) {
    std::cout << "Tentando adicionar aresta entre " << origem << " e " << destino << " com peso " << peso << std::endl;
    
    // Verificando se a aresta já existe
    if (get_aresta(origem, destino) != 0) {
        std::cout << "Aresta entre " << origem << " e " << destino << " já existe!" << std::endl;
        return;
    }

    // Verifica se os índices estão dentro do limite
    if (origem > TAMANHO_ESTATICO || destino > TAMANHO_ESTATICO) {
        std::cerr << "Erro: Índices de vértice estão fora dos limites da matriz!" << std::endl;
        return;
    }

    // Para grafos direcionados
    if (eh_direcionado()) {
        // Adicionando a aresta na posição correta para grafo direcionado
        Matriz[origem - 1][destino - 1] = peso;
        std::cout << "Aresta adicionada na matriz de adjacência!" << std::endl;
    } 
    // Para grafos não direcionados
    else {
        int indice = calcularIndiceLinear(origem, destino);
        MatrizLinear[indice] = peso;
    }
}

void GrafoMatriz::deleta_aresta(int vertice1, int vertice2) {
    if (eh_direcionado()) {
        // Remove a aresta na matriz de adjacência
        Matriz[vertice1 - 1][vertice2 - 1] = 0;
    } else {
        // Certifique-se de que origem é sempre menor ou igual a destino
        if (vertice1 > vertice2) {
            std::swap(vertice1, vertice2);
        }
        int indice = calcularIndiceLinear(vertice1, vertice2);
        MatrizLinear[indice] = 0;
    }
}

void GrafoMatriz::novo_no(int peso) {
    // Aumenta a ordem do grafo
    aumenta_ordem();
    
    // Verifica se é necessário redimensionar a matriz (COMENTADO, pois a matriz é estática)
    /*
    if (get_ordem() > tamanhoAtual) {
        if( eh_direcionado() ) {
            redimensionarMatriz();           // Redimensiona a matriz quadrada
        } else {
            redimensionarMatrizLinear();     // Redimensiona a matriz linear
        }
    }
    */
    
    // Inicializa o novo vértice na matriz (adiciona a linha e a coluna na matriz)
    for (int i = 0; i < get_ordem(); i++) {
        Matriz[i][get_ordem() - 1] = 0;  // Adiciona nova coluna
        Matriz[get_ordem() - 1][i] = 0;  // Adiciona nova linha
    }
    
    // Inicializa o vetor de pesos do novo vértice
    VetorPesosVertices[get_ordem() - 1] = peso; // Valor padrão para o peso do vértice
}

// Método para reorganizar a matriz (COMENTADO, pois a matriz é estática)
/*
void GrafoMatriz::reorganiza_matriz(int vertice) {
    int v = vertice - 1; // Ajustando para índice 0

    // Cria uma nova matriz com tamanho reduzido
    int novoTamanho = tamanhoAtual - 1;
    int** novaMatriz = new int*[novoTamanho];
    for (int i = 0, ni = 0; i < tamanhoAtual; i++) {
        if (i == v) continue; // Pula o vértice a ser deletado
        novaMatriz[ni] = new int[novoTamanho];
        for (int j = 0, nj = 0; j < tamanhoAtual; j++) {
            if (j == v) continue; // Pula o vértice a ser deletado
            novaMatriz[ni][nj] = Matriz[i][j];
            nj++;
        }
        ni++;
    }

    // Libera a matriz antiga
    for (int i = 0; i < tamanhoAtual; i++) {
        delete[] Matriz[i];
    }
    delete[] Matriz;

    // Atualiza ponteiro e tamanho
    Matriz = novaMatriz;
    tamanhoAtual = novoTamanho;
}
*/

// Método para reorganizar o vetor de pesos (COMENTADO, pois a matriz é estática)
/*
void GrafoMatriz::reorganiza_vetor_pesos(int vertice) {
    int v = vertice - 1; // Ajustando para índice 0

    // Cria um novo vetor de pesos com tamanho reduzido
    int* novoVetorPesos = new int[tamanhoAtual - 1];
    for (int i = 0, ni = 0; i < tamanhoAtual; i++) {
        if (i == v) continue; // Pula o vértice a ser deletado
        novoVetorPesos[ni] = VetorPesosVertices[i];
        ni++;
    }

    // Libera o vetor antigo
    delete[] VetorPesosVertices;

    // Atualiza ponteiro
    VetorPesosVertices = novoVetorPesos;
}
*/

void GrafoMatriz::deleta_no(int vertice) {
    if (vertice < 1 || vertice > TAMANHO_ESTATICO) {
        cerr << "Erro: Vértice inválido!" << endl;
        return;
    }

    // Remove todas as arestas associadas ao vértice
    if (eh_direcionado()) {
        deleta_arestas_direcionadas(vertice);
    } else {
        deleta_arestas_nao_direcionadas(vertice);
    }

    // Reorganiza a matriz de adjacência ou a matriz linear (COMENTADO, pois a matriz é estática)
    // reorganiza_matriz(vertice);

    // Atualiza o vetor de pesos dos vértices (COMENTADO, pois a matriz é estática)
    // reorganiza_vetor_pesos(vertice);

    // Decrementa a ordem do grafo
    set_ordem(get_ordem() - 1);

    cout << "Vértice " << vertice << " deletado com sucesso!" << endl;
}

void GrafoMatriz::deleta_arestas_direcionadas(int vertice) {
    int v = vertice - 1; // Ajustando para índice 0

    // Remove todas as arestas de saída do vértice
    for (int i = 0; i < TAMANHO_ESTATICO; i++) {
        Matriz[v][i] = 0;
    }

    // Remove todas as arestas de entrada para o vértice
    for (int i = 0; i < TAMANHO_ESTATICO; i++) {
        Matriz[i][v] = 0;
    }
}

void GrafoMatriz::deleta_arestas_nao_direcionadas(int vertice) {
    int v = vertice - 1; // Ajustando para índice 0

    // Remove todas as arestas associadas ao vértice na matriz linear
    for (int i = 0; i < TAMANHO_ESTATICO; i++) {
        if (i == v) continue; // Evita o próprio vértice

        int indice = calcularIndiceLinear(i + 1, vertice);
        MatrizLinear[indice] = 0;
    }
}