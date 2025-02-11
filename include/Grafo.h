#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

class Grafo
{
private:
    bool direcionado, vtp, atp;
    int ordem, origem, destino, peso;

public:
    Grafo() = default;
    virtual ~Grafo() = default;

    virtual int get_aresta(int origem, int destino) = 0;
    virtual int get_vertice(int vertice) = 0;
    virtual int get_vizinhos(int vertice) = 0;
    virtual void nova_aresta(int origem, int destino, int peso) = 0;
    virtual void deleta_aresta(int vertice1, int vertice2) = 0;

    virtual void set_aresta(int origem, int destino, float peso) = 0;
    virtual void set_vertice(int id, float peso) = 0;
    //virtual void deleta_aresta(int origem, int destino) = 0;

    virtual void novo_no() = 0;

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

        // inicializa_grafo();
    }

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
            if (get_aresta(vertice, i) && !visitado[i]) {
                dfs(i, visitado);
            }
        }
    }

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



    virtual void inicializa_grafo() = 0;

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
