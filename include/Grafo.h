#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @brief Classe base para a representação de um grafo.
 * 
 * Essa classe define as operações gerais que podem ser realizadas em grafos,
 * como manipulação de arestas, vértices, grau, e conexões. As subclasses precisam
 * implementar a inicialização do grafo e operações de manipulação específicas.
 */
class Grafo
{
private:
    bool direcionado; /**< Flag que indica se o grafo é direcionado */
    bool vtp;         /**< Flag que indica se os vértices são ponderados */
    bool atp;         /**< Flag que indica se as arestas são ponderadas */
    int ordem;        /**< Número de vértices do grafo */
    int origem;       /**< Vértice de origem para operações com arestas */
    int destino;      /**< Vértice de destino para operações com arestas */
    int peso;         /**< Peso das arestas ou vértices (quando ponderados) */

public:
    /**
     * @brief Construtor padrão.
     */
    Grafo() = default;

    /**
     * @brief Destruidor virtual.
     */
    virtual ~Grafo() = default;

    /**
     * @brief Método abstrato para obter o peso de uma aresta entre dois vértices.
     * 
     * @param origem Vértice de origem da aresta.
     * @param destino Vértice de destino da aresta.
     * @return O peso da aresta.
     */
    virtual int get_aresta(int origem, int destino) = 0;

    /**
     * @brief Método abstrato para obter o peso de um vértice.
     * 
     * @param vertice O identificador do vértice.
     * @return O peso do vértice.
     */
    virtual int get_vertice(int vertice) = 0;

    /**
     * @brief Método abstrato para obter o número de vizinhos de um vértice.
     * 
     * @param vertice O identificador do vértice.
     * @return O número de vizinhos.
     */
    virtual int get_vizinhos(int vertice) = 0;

    /**
     * @brief Método abstrato para adicionar uma nova aresta entre dois vértices.
     * 
     * @param origem Vértice de origem da aresta.
     * @param destino Vértice de destino da aresta.
     * @param peso Peso da aresta.
     */
    virtual void nova_aresta(int origem, int destino, int peso) = 0;

    /**
     * @brief Método abstrato para definir o peso de uma aresta.
     * 
     * @param origem Vértice de origem da aresta.
     * @param destino Vértice de destino da aresta.
     * @param peso Peso da aresta.
     */
    virtual void set_aresta(int origem, int destino, float peso) = 0;

    /**
     * @brief Método abstrato para definir o peso de um vértice.
     * 
     * @param id Identificador do vértice.
     * @param peso Peso do vértice.
     */
    virtual void set_vertice(int id, float peso) = 0;

    /**
     * @brief Obtém o número de vértices no grafo (ordem do grafo).
     * 
     * @return O número de vértices do grafo.
     */
    int get_ordem()
    {
        return ordem;
    };

    /**
     * @brief Define o número de vértices do grafo.
     * 
     * @param ordem O número de vértices a ser definido.
     */
    void set_ordem(int ordem)
    {
        this->ordem = ordem;
    };

    /**
     * @brief Aumenta a ordem do grafo em 1.
     */
    void aumenta_ordem()
    {
        this->ordem++;
    };

    /**
     * @brief Verifica se o grafo é direcionado.
     * 
     * @return Verdadeiro se o grafo for direcionado, falso caso contrário.
     */
    bool eh_direcionado()
    {
        return direcionado;
    }

    /**
     * @brief Define se o grafo é direcionado.
     * 
     * @param direcionado Valor que define se o grafo será direcionado.
     */
    void set_eh_direcionado(bool direcionado)
    {
        this->direcionado = direcionado;
    };

    /**
     * @brief Verifica se os vértices do grafo são ponderados.
     * 
     * @return Verdadeiro se os vértices forem ponderados, falso caso contrário.
     */
    bool vertice_ponderado()
    {
        return vtp;
    }

    /**
     * @brief Define se os vértices do grafo são ponderados.
     * 
     * @param verticePonderado Valor que define se os vértices serão ponderados.
     */
    void set_vertice_ponderado(bool verticePonderado)
    {
        this->vtp = verticePonderado;
    };

    /**
     * @brief Verifica se as arestas do grafo são ponderadas.
     * 
     * @return Verdadeiro se as arestas forem ponderadas, falso caso contrário.
     */
    bool aresta_ponderada()
    {
        return atp;
    }

    /**
     * @brief Define se as arestas do grafo são ponderadas.
     * 
     * @param arestaPonderada Valor que define se as arestas serão ponderadas.
     */
    void set_aresta_ponderada(bool arestaPonderada)
    {
        this->atp = arestaPonderada;
    };

    /**
     * @brief Carrega o grafo a partir de um arquivo.
     */
    void carrega_grafo()
    {
        ifstream arquivo("./entradas/Grafo.txt");
        if (!arquivo.is_open())
        {
            cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
            return;
        }

        arquivo >> ordem >> direcionado >> vtp >> atp;
        set_ordem(ordem);
        set_eh_direcionado(direcionado);
        set_vertice_ponderado(vtp);
        set_aresta_ponderada(atp);

        inicializa_grafo();
    }

    /**
     * @brief Carrega o grafo a partir de um arquivo com outro formato.
     */
    void carrega_grafo2()
    {
        ifstream arquivo("./entradas/Grafo.txt");
        if (!arquivo.is_open())
        {
            cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
            return;
        }

        arquivo >> ordem >> direcionado >> vtp >> atp;
        set_ordem(ordem);
        set_eh_direcionado(direcionado);
        set_vertice_ponderado(vtp);
        set_aresta_ponderada(atp);

        for (int i = 1; i <= ordem; i++)
        {
            int peso_vertice;
            arquivo >> peso_vertice;

            if (vertice_ponderado())
                set_vertice(i, peso_vertice);
            else
                set_vertice(i, 1);
        }

        int origem, destino = 1;
        float peso = 0;

        while (arquivo >> origem >> destino >> peso)
        {
            if(!aresta_ponderada())
                peso = 0;
            set_aresta(origem, destino, peso);
        }
    }

    /**
     * @brief Obtém o grau (número de vizinhos) do vértice com maior grau.
     * 
     * @return O grau máximo.
     */
    int get_grau()
    {
        if (!eh_direcionado())
        {
            int grauMaximo = 0;
            for (int i = 1; i <= ordem; i++)
            {
                int numVizinhos = get_vizinhos(i);

                if (numVizinhos > grauMaximo)
                {
                    grauMaximo = numVizinhos;
                }
            }
            return grauMaximo;
        }
        else
        {
            int maxGrauSaida = 0;

            for (int i = 1; i <= ordem; i++)
            {
                int grauSaida = 0;

                // Calcula grau de saída
                int numVizinhos = get_vizinhos(i);
                grauSaida = numVizinhos;

                if (grauSaida > maxGrauSaida)
                {
                    maxGrauSaida = grauSaida;
                }
            }
            return maxGrauSaida;
        }
    }

    /**
     * @brief Verifica se o grafo é completo.
     * 
     * @return Verdadeiro se o grafo for completo (todos os vértices estão conectados entre si), falso caso contrário.
     */
    bool eh_completo()
    {
        for (int i = 1; i <= get_ordem(); i++)
        {
            if (get_vizinhos(i) < get_ordem() - 1)
                return false;
        }
        return true;
    }

    /**
     * @brief Realiza uma busca em profundidade (DFS) para explorar todos os vértices conectados a partir de um vértice inicial.
     * 
     * @param vertice Vértice de origem para a busca.
     * @param visitado Array de visitados para marcar os vértices já visitados.
     */
    void dfs(int vertice, bool visitado[]) {
        visitado[vertice] = true;
        for (int i = 1; i <= ordem; i++) {
            if (get_aresta(vertice, i) && !visitado[i]) {
                dfs(i, visitado);
            }
        }
    }

    /**
     * @brief Calcula o número de componentes conexas do grafo.
     * 
     * @return O número de componentes conexas no grafo.
     */
    int n_conexo() {
        bool* visitado = new bool[ordem + 1]; // Usa alocação dinâmica para evitar problemas de tamanho
        for (int i = 1; i <= ordem; i++) { // Se os vértices começam em 1
            visitado[i] = false; // Inicializa corretamente
        }

        int componentes = 0;
        
        for (int i = 1; i <= ordem; i++) { // Se os vértices começam em 1
            if (!visitado[i]) { // Usa índice corretamente
                dfs(i, visitado); // Chama a DFS
                componentes++;
            }
        }

        delete[] visitado; // Libera memória alocada dinamicamente
        return componentes;
    }

    /**
     * @brief Método abstrato para inicializar o grafo, implementado pelas classes derivadas.
     */
    virtual void inicializa_grafo() = 0;

    /**
     * @brief Encontra a maior menor distância entre os vértices utilizando o algoritmo de Floyd-Warshall.
     * 
     * O algoritmo calcula todas as menores distâncias entre pares de vértices e depois encontra a maior distância
     * entre qualquer par de vértices. Caso não haja caminho entre os vértices, o algoritmo considerará um valor
     * de infinito para aquelas distâncias.
     */
    void maior_menor_distancia() {
        int n = get_ordem();

        if (n == 0) {
            cout << "O grafo está vazio." << endl;
            return;
        }

        // Matriz de distâncias
        int dist[n + 1][n + 1];

        // Inicializa a matriz de distâncias
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) {
                    dist[i][j] = 0; // Distância de um nó para ele mesmo
                } else {
                    int peso = get_aresta(i, j);
                    dist[i][j] = (peso > 0) ? peso : 999999; // Se não há aresta, assume um valor alto (infinito)
                }
            }
        }

        // Algoritmo de Floyd-Warshall
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dist[i][k] != 999999 && dist[k][j] != 999999) {
                        if (dist[i][j] > dist[i][k] + dist[k][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }

        // Encontrar os nós mais distantes
        int maxDist = -1;
        int no1 = -1, no2 = -1;

        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (dist[i][j] != 999999 && dist[i][j] > maxDist) {
                    maxDist = dist[i][j];
                    no1 = i;
                    no2 = j;
                }
            }
        }

        // Exibir resultado
        if (no1 != -1 && no2 != -1) {
            cout << "Maior menor distância: (" << no1 << "-" << no2 << ") " << maxDist << endl;
        } else {
            cout << "Não há caminho entre os nós." << endl;
        }
    }
};

#endif // GRAFO_H_INCLUDED
