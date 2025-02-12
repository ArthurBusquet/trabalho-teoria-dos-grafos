#include "../include/GrafoMatriz.h"
#include "../include/Grafo.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * @brief Construtor da classe GrafoMatriz.
 * 
 * Inicializa a matriz de adjacência, a matriz linear e o vetor de pesos dos vértices.
 * O grafo começa com um tamanho inicial definido por `TAMANHO_INICIAL`.
 */
GrafoMatriz::GrafoMatriz() {
    tamanhoAtual = TAMANHO_INICIAL;
    tamanhoAtualLinear = (TAMANHO_INICIAL * (TAMANHO_INICIAL + 1)) / 2;

    // Aloca matriz 2D dinamicamente
    Matriz = new int*[tamanhoAtual];
    for (int i = 0; i < tamanhoAtual; i++) {
        Matriz[i] = new int[tamanhoAtual](); // Inicializa com zero
    }

    // Aloca matriz linear dinamicamente para grafos não direcionados
    MatrizLinear = new int[tamanhoAtualLinear](); // Inicializa com zero

    // Inicializa o vetor de pesos dos vértices com 0
    VetorPesosVertices = new int[tamanhoAtual](); // Inicializa com zero
}


/**
 * @brief Destrutor da classe GrafoMatriz.
 * 
 * Libera a memória alocada para a matriz de adjacência, a matriz linear e o vetor de pesos dos vértices.
 * Garante que todos os ponteiros sejam corretamente liberados e evita dangling pointers.
 */
GrafoMatriz::~GrafoMatriz() {
    cout << "Destruindo GrafoMatriz..." << endl;

    // Libera a matriz bidimensional de forma segura
    if (Matriz != nullptr) {  // Verifica se o ponteiro da Matriz não é nulo
        for (int i = 0; i < tamanhoAtual; i++) {
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
}


/**
 * @brief Redimensiona a matriz de adjacência para acomodar novos vértices.
 * 
 * A matriz é duplicada em tamanho para evitar realocações frequentes.
 * Os valores da matriz original são copiados para a nova matriz, e as novas posições
 * são inicializadas com zero. Após a cópia, a matriz original é desalocada.
 */
void GrafoMatriz::redimensionarMatriz() {
    int novoTamanho = tamanhoAtual * 2;
    cout << "Redimensionando matriz quadrada para " << novoTamanho << "..." << endl;
    cout << "Aqui" << endl << endl;
    
    // Aloca uma nova matriz com o dobro do tamanho
    int** novaMatriz = new int*[novoTamanho];
    cout << "Aqui" << endl << endl;
    for (int i = 0; i < novoTamanho; i++) {
        novaMatriz[i] = new int[novoTamanho];

        // Copia os valores da matriz original e inicializa novas posições com zero
        for (int j = 0; j < novoTamanho; j++) {
            novaMatriz[i][j] = (i < tamanhoAtual && j < tamanhoAtual) ? Matriz[i][j] : 0;
        }
    }

    // Libera a matriz original
    for (int i = 0; i < tamanhoAtual; i++) {
        delete[] Matriz[i];
    }
    delete[] Matriz;

    // Atualiza ponteiro e tamanho
    Matriz = novaMatriz;
    tamanhoAtual = novoTamanho;
}


/**
 * @brief Redimensiona a matriz linear de adjacência para acomodar novos vértices.
 * 
 * A matriz linear é usada para representar grafos não direcionados de forma eficiente.
 * Essa função realoca a matriz linear, copiando os valores existentes e inicializando
 * novas posições com zero. Após a cópia, a matriz original é desalocada.
 */
void GrafoMatriz::redimensionarMatrizLinear() {
    int novoTamanho = (tamanhoAtual * (tamanhoAtual + 1)) / 2;
    cout << "Redimensionando matriz linear para " << novoTamanho << "..." << endl;

    // Aloca uma nova matriz linear com o novo tamanho
    int* novaMatrizLinear = new int[novoTamanho];

    // Copia os valores da matriz original e inicializa novas posições com zero
    for (int i = 0; i < novoTamanho; i++) {
        novaMatrizLinear[i] = (i < tamanhoAtualLinear) ? MatrizLinear[i] : 0;
    }

    // Libera a matriz linear antiga
    delete[] MatrizLinear;

    // Atualiza ponteiro e tamanho
    MatrizLinear = novaMatrizLinear;
    tamanhoAtualLinear = novoTamanho;
}


/**
 * @brief Calcula o índice correspondente na matriz linear para uma aresta.
 * 
 * A matriz linear armazena apenas a metade da matriz de adjacência para economizar espaço.
 * Este método converte um par (origem, destino) em um índice dentro dessa matriz comprimida.
 * 
 * @param origem Vértice de origem da aresta.
 * @param destino Vértice de destino da aresta.
 * @return Índice correspondente na matriz linear.
 */
int GrafoMatriz::calcularIndiceLinear(int origem, int destino) {
    if (origem <= destino) {
        return (destino * (destino - 1)) / 2 + origem;
    }
    return (origem * (origem - 1)) / 2 + destino;
}

/**
 * @brief Obtém o peso da aresta entre dois vértices.
 * 
 * Retorna o valor armazenado na matriz de adjacência ou na matriz linear,
 * dependendo se o grafo é direcionado ou não.
 * 
 * @param origem Identificador do vértice de origem.
 * @param destino Identificador do vértice de destino.
 * @return Peso da aresta ou -1 se não existir.
 */
int GrafoMatriz::get_aresta(int origem, int destino) {
    if (origem < 0 || destino < 0 || origem >= tamanhoAtual || destino >= tamanhoAtual) {
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

/**
 * @brief Define o peso de um vértice.
 * 
 * Se o grafo não for ponderado nos vértices, o peso será forçado para 0.
 * 
 * @param id Identificador do vértice.
 * @param peso Novo peso do vértice.
 */
void GrafoMatriz::set_vertice(int id, float peso) {
    if (!vertice_ponderado()) {
        peso = 0;
    }

    VetorPesosVertices[id - 1] = peso;
}

/**
 * @brief Define o peso de uma aresta existente.
 * 
 * Se o grafo não for ponderado nas arestas, o peso será forçado para 0.
 * O método verifica se o grafo é direcionado e armazena o peso na estrutura correspondente.
 * 
 * @param origem Identificador do vértice de origem.
 * @param destino Identificador do vértice de destino.
 * @param peso Novo peso da aresta.
 */
void GrafoMatriz::set_aresta(int origem, int destino, float peso) {
    if (!aresta_ponderada()) {
        peso = 0;
    }

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

/**
 * @brief Obtém o peso de um vértice.
 * 
 * Se o grafo for ponderado nos vértices, retorna o peso armazenado.
 * Caso contrário, retorna 1 (peso padrão para vértices não ponderados).
 * 
 * @param origem Identificador do vértice.
 * @return Peso do vértice.
 */
int GrafoMatriz::get_vertice(int origem) {
    if (vertice_ponderado()) {
        return VetorPesosVertices[origem - 1];
    }
    return 1;
}


/**
 * @brief Obtém o número de vizinhos de um vértice.
 * 
 * Para grafos direcionados, conta o número de arestas de saída do vértice.
 * Para grafos não direcionados, verifica a matriz linear de adjacência, evitando contagens duplicadas.
 * 
 * @param vertice Identificador do vértice.
 * @return Número de vizinhos do vértice ou -1 se o vértice for inválido.
 */
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

/**
 * @brief Adiciona uma nova aresta ao grafo.
 * 
 * A função verifica se a aresta já existe antes de adicioná-la.
 * Para grafos direcionados, a aresta é armazenada na matriz de adjacência.
 * Para grafos não direcionados, a aresta é armazenada na matriz linear comprimida.
 * 
 * @param origem Identificador do vértice de origem.
 * @param destino Identificador do vértice de destino.
 * @param peso Peso da aresta.
 */
/**
 * @brief Adiciona uma nova aresta ao grafo.
 * 
 * A função verifica se a aresta já existe antes de adicioná-la.
 * Para grafos direcionados, a aresta é armazenada na matriz de adjacência.
 * Para grafos não direcionados, a aresta é armazenada na matriz linear comprimida.
 * 
 * @param origem Identificador do vértice de origem.
 * @param destino Identificador do vértice de destino.
 * @param peso Peso da aresta.
 */
void GrafoMatriz::nova_aresta(int origem, int destino, int peso) {
    std::cout << "Tentando adicionar aresta entre " << origem << " e " << destino << " com peso " << peso << std::endl;
    
    // Verificando se a aresta já existe
    if (get_aresta(origem, destino) != 0) {
        std::cout << "Aresta entre " << origem << " e " << destino << " já existe!" << std::endl;
        return;
    }

    // Verifica se os índices estão dentro do limite
    if (origem > tamanhoAtual || destino > tamanhoAtual) {
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

/**
 * @brief Remove uma aresta do grafo.
 * 
 * Para grafos direcionados, apenas a entrada correspondente na matriz de adjacência é apagada.
 * Para grafos não direcionados, a aresta é removida da matriz linear comprimida.
 * 
 * @param vertice1 Identificador do primeiro vértice.
 * @param vertice2 Identificador do segundo vértice.
 */
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


/**
 * @brief Adiciona um novo vértice ao grafo.
 * 
 * Aumenta a ordem do grafo e redimensiona a matriz de adjacência ou a matriz linear se necessário.
 * Inicializa a nova linha e a nova coluna da matriz com zeros.
 * 
 * @param peso Peso do novo vértice.
 */
void GrafoMatriz::novo_no(int peso) {
    // Aumenta a ordem do grafo
    aumenta_ordem();
    
    // Verifica se é necessário redimensionar a matriz
    if (get_ordem() > tamanhoAtual) {
        if (eh_direcionado()) {
            redimensionarMatriz();  // Redimensiona a matriz quadrada
        } else {
            redimensionarMatrizLinear();  // Redimensiona a matriz linear
        }
    }
    
    // Inicializa o novo vértice na matriz (adiciona a linha e a coluna na matriz)
    for (int i = 0; i < get_ordem(); i++) {
        Matriz[i][get_ordem() - 1] = 0;  // Adiciona nova coluna
        Matriz[get_ordem() - 1][i] = 0;  // Adiciona nova linha
    }
    
    // Inicializa o vetor de pesos do novo vértice
    VetorPesosVertices[get_ordem() - 1] = peso; // Valor padrão para o peso do vértice
}

/**
 * @brief Reorganiza a matriz de adjacência após a remoção de um vértice.
 * 
 * Cria uma nova matriz sem a linha e a coluna do vértice removido, copiando os dados restantes.
 * 
 * @param vertice Identificador do vértice removido.
 */
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

/**
 * @brief Reorganiza o vetor de pesos dos vértices após a remoção de um vértice.
 * 
 * Cria um novo vetor de pesos sem o valor correspondente ao vértice removido.
 * 
 * @param vertice Identificador do vértice removido.
 */
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

/**
 * @brief Remove um vértice do grafo e reorganiza suas estruturas.
 * 
 * Remove todas as arestas associadas ao vértice e reorganiza a matriz de adjacência
 * e o vetor de pesos. Reduz a ordem do grafo.
 * 
 * @param vertice Identificador do vértice a ser removido.
 */
void GrafoMatriz::deleta_no(int vertice) {
    if (vertice < 1 || vertice > tamanhoAtual) {
        cerr << "Erro: Vértice inválido!" << endl;
        return;
    }

    // Remove todas as arestas associadas ao vértice
    if (eh_direcionado()) {
        deleta_arestas_direcionadas(vertice);
    } else {
        deleta_arestas_nao_direcionadas(vertice);
    }

    // Reorganiza a matriz de adjacência ou a matriz linear
    reorganiza_matriz(vertice);

    // Atualiza o vetor de pesos dos vértices
    reorganiza_vetor_pesos(vertice);

    // Decrementa a ordem do grafo
    set_ordem(get_ordem() - 1);

    cout << "Vértice " << vertice << " deletado com sucesso!" << endl;
}

/**
 * @brief Remove todas as arestas direcionadas associadas a um vértice.
 * 
 * Remove todas as conexões de saída e entrada do vértice na matriz de adjacência.
 * 
 * @param vertice Identificador do vértice.
 */
void GrafoMatriz::deleta_arestas_direcionadas(int vertice) {
    int v = vertice - 1; // Ajustando para índice 0

    // Remove todas as arestas de saída do vértice
    for (int i = 0; i < tamanhoAtual; i++) {
        Matriz[v][i] = 0;
    }

    // Remove todas as arestas de entrada para o vértice
    for (int i = 0; i < tamanhoAtual; i++) {
        Matriz[i][v] = 0;
    }
}

/**
 * @brief Remove todas as arestas não direcionadas associadas a um vértice.
 * 
 * Remove as conexões do vértice na matriz linear de adjacência.
 * 
 * @param vertice Identificador do vértice.
 */
void GrafoMatriz::deleta_arestas_nao_direcionadas(int vertice) {
    int v = vertice - 1; // Ajustando para índice 0

    // Remove todas as arestas associadas ao vértice na matriz linear
    for (int i = 0; i < tamanhoAtual; i++) {
        if (i == v) continue; // Evita o próprio vértice

        int indice = calcularIndiceLinear(i + 1, vertice);
        MatrizLinear[indice] = 0;
    }
}
