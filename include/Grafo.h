#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @class Grafo
 * @brief Classe abstrata que representa um grafo.
 * 
 * Define operações fundamentais para manipulação de grafos, como adição e remoção de arestas e vértices.
 * Essa classe serve como base para diferentes representações de grafos.
 */
class Grafo
{
private:
    bool direcionado; ///< Indica se o grafo é direcionado.
    bool vtp; ///< Indica se os vértices são ponderados.
    bool atp; ///< Indica se as arestas são ponderadas.
    int ordem; ///< Número total de vértices no grafo.
    int origem, destino, peso; ///< Atributos auxiliares para operações no grafo.

public:
    Grafo() = default; ///< Construtor padrão.
    virtual ~Grafo() = default; ///< Destrutor virtual.

    /**
     * @brief Retorna o peso da aresta entre dois vértices.
     * @param origem Vértice de origem.
     * @param destino Vértice de destino.
     * @return Peso da aresta ou um valor indicando inexistência.
     */
    virtual int get_aresta(int origem, int destino) = 0;

    /**
     * @brief Obtém o peso de um vértice.
     * @param vertice Identificador do vértice.
     * @return Peso do vértice.
     */
    virtual int get_vertice(int vertice) = 0;

    /**
     * @brief Retorna o número de vizinhos de um vértice.
     * @param vertice Identificador do vértice.
     * @return Número de vizinhos do vértice.
     */
    virtual int get_vizinhos(int vertice) = 0;

    virtual void nova_aresta(int origem, int destino, int peso) = 0;
    virtual void deleta_aresta(int vertice1, int vertice2) = 0;

    virtual void set_aresta(int origem, int destino, float peso) = 0;
    virtual void set_vertice(int id, float peso) = 0;
    
    virtual void novo_no(int peso) = 0;
    virtual void deleta_no(int vertice) = 0;

    int get_ordem()
    {
        return ordem;
    };

    void set_ordem(int ordem)
    {
        this->ordem = ordem;
    };

    void aumenta_ordem()
    {
        this->ordem++;
    };

    bool eh_direcionado()
    {
        return direcionado;
    }

    void set_eh_direcionado(bool direcionado)
    {
        this->direcionado = direcionado;
    };

    bool vertice_ponderado()
    {
        return vtp;
    }

    void set_vertice_ponderado(bool verticePonderado)
    {
        this->vtp = verticePonderado;
    };

    bool aresta_ponderada()
    {
        return atp;
    }

    void set_aresta_ponderada(bool arestaPonderada)
    {
        this->atp = arestaPonderada;
    };

    /**
     * @brief Carrega o grafo a partir de um arquivo de entrada.
     * 
     * O formato do arquivo deve conter:
     * - Número de vértices, se é direcionado e se é ponderado.
     * - Lista de vértices e seus pesos (se for ponderado).
     * - Lista de arestas com origem, destino e peso (se for ponderado).
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
            if (!aresta_ponderada())
                peso = 0;
            set_aresta(origem, destino, peso);
        }
    }

    /**
     * @brief Calcula o grau máximo do grafo.
     * @return O maior grau encontrado entre os vértices.
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
                int grauSaida = get_vizinhos(i);
                if (grauSaida > maxGrauSaida)
                {
                    maxGrauSaida = grauSaida;
                }
            }
            return maxGrauSaida;
        }
    }

    bool eh_completo()
    {
        for (int i = 1; i <= get_ordem(); i++)
        {
            if (get_vizinhos(i) < get_ordem() - 1)
                return false;
        }
        return true;
    }

    void dfs(int vertice, bool visitado[]) {
        visitado[vertice] = true;
        for (int i = 1; i <= ordem; i++) {
            if (get_aresta(vertice, i) != -1 && !visitado[i]) {
                dfs(i, visitado);
            }
        }
    }

    /**
     * @brief Determina o número de componentes conexas do grafo.
     * @return Número de componentes conexas.
     */
    int n_conexo() {
        bool* visitado = new bool[ordem + 1];
        for (int i = 1; i <= ordem; i++) {
            visitado[i] = false;
        }

        int componentes = 0;
        for (int i = 1; i <= ordem; i++) {
            if (!visitado[i]) {
                dfs(i, visitado);
                componentes++;
            }
        }

        delete[] visitado;
        return componentes;
    }

    /**
     * @brief Calcula a maior menor distância entre dois vértices utilizando o algoritmo de Floyd-Warshall.
     */
    void maior_menor_distancia()
    {
        int n = get_ordem();
        if (n == 0)
        {
            cout << "O grafo está vazio." << endl;
            return;
        }

        int dist[n + 1][n + 1];

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                    dist[i][j] = 0;
                else
                {
                    int peso = get_aresta(i, j);
                    dist[i][j] = (peso > 0) ? peso : 999999;
                }
            }
        }

        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (dist[i][k] != 999999 && dist[k][j] != 999999)
                    {
                        if (dist[i][j] > dist[i][k] + dist[k][j])
                            dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
};

#endif // GRAFO_H_INCLUDED
