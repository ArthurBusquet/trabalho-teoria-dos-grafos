#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>

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
    int *clusters;    // Array para armazenar os clusters de cada vértice

    float modulo_subtracao(int a, int b)
    {
        if (a > b)
        {
            return a - b;
        }
        else if (a < b)
        {
            return b - a;
        }
        else
        {
            return 1;
        }
    }

    const int MAX_NODES = 50000;
    const int MAX_EDGES = 1000000;

    struct NodeMapping
    {
        int original;
        int mapped;
    };

    int mapeia_vertice(NodeMapping node_mapping[], int &node_count, int node, int &next_id)
    {
        for (int i = 0; i < node_count; i++)
        {
            if (node_mapping[i].original == node)
            {
                return node_mapping[i].mapped; // Retorna o ID já mapeado
            }
        }
        node_mapping[node_count].original = node;
        node_mapping[node_count].mapped = next_id;
        set_vertice(next_id, 1);
        node_count++;
        return next_id++; // Retorna o novo ID e incrementa o próximo ID
    }

public:
    /**
     * @brief Construtor padrão.
     */
    Grafo() = default;

    /**
     * @brief Carrega o grafo a partir de um arquivo que contem a instancia do grafo.
     *
     * @param d Parametro que seleciona o arquivo a ser lido
     */
    void carrega_grafo_novo(int d)
    {
        // int d = 1; // Aqui você pode mudar para testar diferentes arquivos
        std::string filename;

        if (d == 1)
        {
            filename = "./entradas/aa4.mtx";
        } else if (d == 2) {
            filename = "./entradas/bio-grid-fruitfly.mtx";
        } else if (d == 3) {
            filename = "./entradas/bio-grid-yeast.mtx";
        } else if (d == 4) {
            filename = "./entradas/ca-Erdos992.mtx";
        } else if (d == 5) {
            filename = "./entradas/airfoil1_dual.mtx";
        } else if (d == 6) {
            filename = "./entradas/EX5.mtx";
        } else if (d == 7) {
            filename = "./entradas/ukerbe1.mtx";
        } else if (d == 8) {
            filename = "./entradas/as-735.mtx";
        } else if (d == 9) {
            filename = "./entradas/p2p-Gnutella08.mtx";
        } else if (d == 10) {
            filename = "./entradas/bio-dmela.mtx";
        } else {
            std::cout << "Arquivo Inválido" << std::endl;
        }
        // Abre o arquivo para leitura
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
            return;
        }

        set_eh_direcionado(false);
        set_aresta_ponderada(true);
        set_vertice_ponderado(false);

        NodeMapping node_mapping[MAX_NODES];
        int node_count = 0; // Contador de nós mapeados
        int edge_count = 0; // Contador de arestas
        int next_id = 1;    // Próximo ID sequencial a ser atribuído

        int node1, node2;

        // Lê o arquivo linha por linha
        while (file >> node1 >> node2)
        {

            int mapped_node1 = mapeia_vertice(node_mapping, node_count, node1, next_id);
            int mapped_node2 = mapeia_vertice(node_mapping, node_count, node2, next_id);
            if (node1 != node2)
            {
                set_aresta(mapped_node1, mapped_node2, modulo_subtracao(mapped_node1, mapped_node2));
                edge_count++;
            }
        }

        file.close();

        set_ordem(node_count);

        // Cria clusters aleatórios após carregar o grafo
        criar_clusters_aleatorios(10); // Exemplo: 3 clusters
    };

    /**
     * @brief Destruidor virtual.
     */
    // virtual ~Grafo() = default;
    virtual ~Grafo()
    {
        if (clusters)
        {
            delete[] clusters; // Libera a memória alocada para os clusters
        }
    }

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
    * @brief Obtém os vértices vizinhos de um determinado vértice.
    *
    * @details Esta função retorna um array contendo os vértices vizinhos
    * do vértice especificado. A quantidade de vizinhos é armazenada na 
    * variável passada por referência.
    *
    * @param vertice O vértice cujo vizinhos serão buscados.
    * @param qtdvizinhos Referência para armazenar a quantidade total de vizinhos.
    * @return Ponteiro para um array contendo os vértices vizinhos.
    */
    virtual int *get_vizinhos_vertices(int vertice, int &qtdvizinhos) = 0;

    virtual int *get_vizinhos_array(int id, int &tamanho) = 0;

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
     * @brief Obtém o grau (número de vizinhos) do vértice com maior grau.
     *
     * @return O grau máximo.
     */
    int get_grau()
    {
        if (!eh_direcionado())
        {
            int grauMaximo = 0;
            for (int i = 1; i <= 100; i++)
            {
                // int quantidadeVizinhos = get_vizinhos(i);
                // int* vizinhos = get_vizinhos_vertices(i, quantidadeVizinhos);
                // if (vizinhos) {
                //     cout << "Vizinhos do vértice " << i << ": ";
                //     for (int i = 0; i < quantidadeVizinhos; i++) {
                //         cout << vizinhos[i] << " ";
                //     }
                //     cout << endl;

                //     // Libera a memória alocada para o array de vizinhos
                //     delete[] vizinhos;
                // } else {
                //     cout << "Vértice inválido ou sem vizinhos." << endl;
                // }
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
    void dfs(int vertice, bool visitado[])
    {
        visitado[vertice] = true;
        for (int i = 1; i <= ordem; i++)
        {
            if (get_aresta(vertice, i) && !visitado[i])
            {
                dfs(i, visitado);
            }
        }
    }

    /**
     * @brief Calcula o número de componentes conexas do grafo.
     *
     * @return O número de componentes conexas no grafo.
     */
    int n_conexo()
    {

        bool *visitado = new bool[ordem + 1]; // Usa alocação dinâmica para evitar problemas de tamanho
        for (int i = 1; i <= ordem; i++)
        {                        // Se os vértices começam em 1
            visitado[i] = false; // Inicializa corretamente
        }

        int componentes = 0;

        for (int i = 1; i <= ordem; i++)
        { // Se os vértices começam em 1
            if (!visitado[i])
            {                     // Usa índice corretamente
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
    void maior_menor_distancia()
    {
        int n = get_ordem();

        if (n == 0)
        {
            cout << "O grafo está vazio." << endl;
            return;
        }

        // Matriz de distâncias
        int dist[n + 1][n + 1];

        // Inicializa a matriz de distâncias
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                {
                    dist[i][j] = 0; // Distância de um nó para ele mesmo
                }
                else
                {
                    int peso = get_aresta(i, j);
                    dist[i][j] = (peso > 0) ? peso : 999999; // Se não há aresta, assume um valor alto (infinito)
                }
            }
        }

        // Algoritmo de Floyd-Warshall
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (dist[i][k] != 999999 && dist[k][j] != 999999)
                    {
                        if (dist[i][j] > dist[i][k] + dist[k][j])
                        {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }
        }

        // Encontrar os nós mais distantes
        int maxDist = -1;
        int no1 = -1, no2 = -1;

        for (int i = 1; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                if (dist[i][j] != 999999 && dist[i][j] > maxDist)
                {
                    maxDist = dist[i][j];
                    no1 = i;
                    no2 = j;
                }
            }
        }

        // Exibir resultado
        if (no1 != -1 && no2 != -1)
        {
            cout << "Maior menor distância: (" << no1 << "-" << no2 << ") " << maxDist << endl;
        }
        else
        {
            cout << "Não há caminho entre os nós." << endl;
        }
    }

    void criar_clusters_aleatorios(int num_clusters)
    {
        if (clusters)
        {
            delete[] clusters; // Libera a memória anterior, se houver
        }
        clusters = new int[ordem + 1]; // Aloca memória para os clusters

        for (int i = 1; i <= ordem; i++)
        {
            // Obtém o último dígito do número do vértice
            int ultimo_digito = i % 10;

            // Atribui o cluster com base no último dígito

            clusters[i] = i % 71 == 0 ? (ultimo_digito % num_clusters) + 1 : 0;
        }
    }

    int *get_clusters()
    {
        return clusters;
    }

    /**
     * @brief Encontra o  Árvore Geradora Mínima (AGM) do grafo, garantindo que contenha pelo menos um vértice de cada cluster.
     *
     * Esta função utiliza uma abordagem gulosa
     *
     * @return O somatorio dos pesos das arestas que compoe a arvore
     */
    float encontrar_agmg_guloso()
    {
        int num_clusters = 10;

        bool *vertices_visitados = new bool[ordem + 1]();        // Inicializa todos como false
        bool *cluster_conectados = new bool[num_clusters + 1](); // Inicializa todos como false
        float soma_pesos_agmg = 0;

        int vertice_atual = 1;                              // Começa no vértice 1
        vertices_visitados[vertice_atual] = true;           // Marca o vértice inicial como visitado
        cluster_conectados[clusters[vertice_atual]] = true; // Marca o cluster do vértice inicial como conectado

        while (true)
        {
            std::cout << "soma_pesos_agmg: " << soma_pesos_agmg << std::endl;

            int qtd_vizinhos;
            int *vizinhos = get_vizinhos_vertices(vertice_atual, qtd_vizinhos);

            if (qtd_vizinhos == 0)
            {
                delete[] vizinhos;
                std::cout << "Nao foi possivel encontrar uma arvore que ligue todos os clusters " << std::endl;
                break;
            }

            float menor_peso_local = 99999;
            int proximo_vertice = -1;

            for (int i = 0; i < qtd_vizinhos; i++)
            {
                int vizinho = vizinhos[i];
                float peso_aresta = get_aresta(vertice_atual, vizinho);

                if (!cluster_conectados[clusters[vizinho]])
                {
                    if (peso_aresta < menor_peso_local)
                    {
                        menor_peso_local = peso_aresta;
                        proximo_vertice = vizinho;
                    }

                    else if (peso_aresta == menor_peso_local)
                    {
                    }
                }
            }

            if (proximo_vertice == -1)
            {
                for (int i = 0; i < qtd_vizinhos; i++)
                {
                    int vizinho = vizinhos[i];
                    float peso_aresta = get_aresta(vertice_atual, vizinho);

                    if (!vertices_visitados[vizinho] && peso_aresta < menor_peso_local)
                    {
                        menor_peso_local = peso_aresta;
                        proximo_vertice = vizinho;
                    }
                }
            }

            if (proximo_vertice == -1)
            {
                delete[] vizinhos;
                std::cout << "Nao foi possivel encontrar uma arvore que ligue todos os clusters " << std::endl;
                break;
            }

            vertice_atual = proximo_vertice;
            vertices_visitados[vertice_atual] = true;
            cluster_conectados[clusters[vertice_atual]] = true;
            soma_pesos_agmg += menor_peso_local;

            bool todos_clusters_conectados = true;
            for (int i = 1; i <= num_clusters; i++)
            {
                if (!cluster_conectados[i])
                {

                    todos_clusters_conectados = false;
                    break;
                }
            }

            delete[] vizinhos;

            if (todos_clusters_conectados)
            {
                break;
            }
        }

        delete[] cluster_conectados;
        delete[] vertices_visitados;

        return soma_pesos_agmg;
    }

    /**
     * @brief Encontra o  Árvore Geradora Mínima (AGM) do grafo, garantindo que contenha pelo menos um vértice de cada cluster.
     *
     * Esta função utiliza uma abordagem gulosa randomizada
     *
     * @return O somatorio dos pesos das arestas que compoe a arvore
     */
    float encontrar_agmg_randomizado()
    {
        int num_clusters = 10;

        bool *vertices_visitados = new bool[ordem + 1]();
        bool *cluster_conectados = new bool[num_clusters + 1]();
        float soma_pesos_agmg = 0;

        std::srand(std::time(0));

        int vertice_atual = std::rand() % ordem + 1;
        vertices_visitados[vertice_atual] = true;
        cluster_conectados[clusters[vertice_atual]] = true;

        while (true)
        {
            std::cout << "vertice_atual: " << vertice_atual << std::endl;

            int qtd_vizinhos;
            int *vizinhos = get_vizinhos_vertices(vertice_atual, qtd_vizinhos);

            if (qtd_vizinhos == 0)
            {
                delete[] vizinhos;
                std::cout << "Nao foi possivel encontrar uma arvore que ligue todos os clusters " << std::endl;
                break;
            }

            float menor_peso_local = 99999;
            int candidatos[ordem];
            int num_candidatos = 0;

            for (int i = 0; i < qtd_vizinhos; i++)
            {
                int vizinho = vizinhos[i];
                float peso_aresta = get_aresta(vertice_atual, vizinho);

                if (!vertices_visitados[vizinho] && peso_aresta <= menor_peso_local)
                {
                    if (peso_aresta < menor_peso_local)
                    {
                        menor_peso_local = peso_aresta;
                        num_candidatos = 0;
                    }
                    candidatos[num_candidatos++] = vizinho;
                }

                if (!cluster_conectados[clusters[vizinho]])
                {
                    std::cout << "cluster do " << vizinho << " e " << clusters[vizinho] << std::endl;
                    num_candidatos = 0;
                    candidatos[num_candidatos++] = vizinho;
                    break;
                }
            }

            if (num_candidatos == 0)
            {
                delete[] vizinhos;
                std::cout << "Nao foi possivel encontrar uma arvore que ligue todos os clusters " << std::endl;
                break;
            }

            int proximo_vertice = candidatos[std::rand() % num_candidatos];

            vertice_atual = proximo_vertice;
            vertices_visitados[vertice_atual] = true;
            cluster_conectados[clusters[vertice_atual]] = true;
            soma_pesos_agmg += menor_peso_local;

            bool todos_clusters_conectados = true;
            for (int i = 1; i <= num_clusters; i++)
            {
                if (!cluster_conectados[i])
                {
                    todos_clusters_conectados = false;
                    break;
                }
            }

            delete[] vizinhos;

            if (todos_clusters_conectados)
            {
                break;
            }
        }

        delete[] cluster_conectados;
        delete[] vertices_visitados;

        return soma_pesos_agmg;
    }

    void testa_get_vizinhos(int id)
    {
        int *vizinhos = new int[ordem];
        int qtd_vizinhos;
        vizinhos = get_vizinhos_vertices(id, qtd_vizinhos);

        cout << "vizinhos do " << id << " ";
        for (int i = 0; i < qtd_vizinhos; i++)
        {
            cout << vizinhos[i] << " ";
        }
        cout << endl;
    }

    /**
    * @brief Encontra a Árvore Geradora Mínima (AGM) do grafo de forma reativa, garantindo que contenha pelo menos um vértice de cada cluster.
    *
    * Esta função utiliza uma abordagem gulosa semelhante ao algoritmo de Prim, mas com a adição de uma verificação para garantir que todos os clusters estejam representados na árvore.
    *
    * @return Um array de pares representando as arestas da AGM.
    */
    std::pair<int, int>* arvore_geradora_minima_reativa(int& tamanho_agm) {
        // Verifica se o grafo tem vértices
        if (ordem == 0) {
            std::cerr << "Erro: O grafo não tem vértices." << std::endl;
            tamanho_agm = 0;
            return nullptr;
        }

        // Estrutura para armazenar as arestas da AGM
        std::pair<int, int>* agm = new std::pair<int, int>[ordem]; // No máximo, a AGM terá (ordem - 1) arestas
        tamanho_agm = 0; // Inicializa o tamanho da AGM

        // Estrutura para verificar se um vértice já está na AGM
        bool* na_agm = new bool[ordem + 1];
        for (int i = 1; i <= ordem; i++) {
            na_agm[i] = false;
        }

        // Estrutura para verificar se um cluster já está representado na AGM
        bool* cluster_representado = new bool[clusters[ordem] + 1];
        for (int i = 1; i <= clusters[ordem]; i++) {
            cluster_representado[i] = false;
        }

        // Contador de clusters representados
        int clusters_representados = 0;

        // Função para verificar se todos os clusters estão representados
        auto todos_clusters_representados = [&]() {
            return clusters_representados == clusters[ordem];
        };

        // Função para adicionar um vértice à AGM e atualizar os clusters representados
        auto adicionar_vertice = [&](int vertice) {
            if (!na_agm[vertice]) {
                na_agm[vertice] = true;
                if (!cluster_representado[clusters[vertice]]) {
                    cluster_representado[clusters[vertice]] = true;
                    clusters_representados++;
                }
            }
        };

        // Estrutura para armazenar as arestas candidatas
        struct Aresta {
            int peso;
            int origem;
            int destino;
        };

        // Array para armazenar todas as arestas do grafo
        Aresta* arestas = new Aresta[ordem * ordem]; // Número máximo de arestas em um grafo completo
        int num_arestas = 0;

        // Coleta todas as arestas do grafo
        for (int i = 1; i <= ordem; i++) {
            int qtdVizinhos;
            int* vizinhos = get_vizinhos_vertices(i, qtdVizinhos);
            for (int j = 0; j < qtdVizinhos; j++) {
                int vizinho = vizinhos[j];
                int peso = get_aresta(i, vizinho);
                if (peso > 0) { // Ignora arestas com peso zero ou inválido
                    arestas[num_arestas].peso = peso;
                    arestas[num_arestas].origem = i;
                    arestas[num_arestas].destino = vizinho;
                    num_arestas++;
                }
            }
            delete[] vizinhos; // Libera a memória alocada para o array de vizinhos
        }

        // Ordena as arestas manualmente (usando Bubble Sort)
        for (int i = 0; i < num_arestas - 1; i++) {
            for (int j = 0; j < num_arestas - i - 1; j++) {
                if (arestas[j].peso > arestas[j + 1].peso) {
                    // Troca as arestas
                    Aresta temp = arestas[j];
                    arestas[j] = arestas[j + 1];
                    arestas[j + 1] = temp;
                }
            }
        }

        // Adiciona o primeiro vértice de cada cluster à AGM
        for (int i = 1; i <= ordem; i++) {
            if (!cluster_representado[clusters[i]]) {
                adicionar_vertice(i);
            }
        }

        // Enquanto nem todos os clusters estiverem representados, adiciona arestas
        for (int i = 0; i < num_arestas && !todos_clusters_representados(); i++) {
            int u = arestas[i].origem;
            int v = arestas[i].destino;

            // Se o vértice de destino ainda não está na AGM, adiciona a aresta
            if (!na_agm[v]) {
                agm[tamanho_agm] = {u, v};
                tamanho_agm++;
                adicionar_vertice(v);
            }
        }

        // Verifica se todos os clusters foram representados
        if (!todos_clusters_representados()) {
            std::cerr << "Aviso: Nem todos os clusters estão conectados no grafo." << std::endl;
        }

        // Libera a memória alocada
        delete[] na_agm;
        delete[] cluster_representado;
        delete[] arestas;

        return agm;
    }
};

#endif // GRAFO_H_INCLUDED
