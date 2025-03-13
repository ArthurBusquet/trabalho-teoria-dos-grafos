#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <fstream>
#include "Cluster.h"
#include "ListaEncadeada.h"

using namespace std;


class Grafo
{
private:
    bool direcionado, vtp, atp;
    int ordem, origem, destino, peso;
 

protected:

    ListaEncadeada<Cluster>* clusters;
    ListaEncadeada<ArestaEncadeada>* resultado = new ListaEncadeada<ArestaEncadeada>();

public:
    Grafo() = default;
    virtual ~Grafo() = default;

    virtual int get_aresta(int origem, int destino) = 0;
    virtual int get_vertice(int vertice) = 0;
    virtual int get_vizinhos(int vertice) = 0;
    virtual void nova_aresta(int origem, int destino, int peso) = 0;
    virtual void deleta_aresta(int vertice1, int vertice2) = 0;
    virtual void imprimirClusters() = 0; // Torna obrigatório nas classes filhas
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
            if(!aresta_ponderada())
                peso = 0;
            set_aresta(origem, destino, peso);
        }
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
            if (get_aresta(vertice, i) != -1 && !visitado[i]) {
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
    struct NoInt {
        int valor;
        NoInt* proximo;
    
        NoInt(int v) : valor(v), proximo(nullptr) {}
    
        NoInt* getProximo() { return proximo; }
        void setProximo(NoInt* prox) { proximo = prox; }
    };
    
    struct VizinhosValidos {
        int id;
        int qtd;
        VizinhosValidos* proximo;
    
        VizinhosValidos(int id, int qtd) : id(id), qtd(qtd), proximo(nullptr) {}
    
        VizinhosValidos* getProximo() { return proximo; }
        void setProximo(VizinhosValidos* novoProximo) { proximo = novoProximo; }
    };
    
    
    float encontrarAGMG() {
        float pesoTotal = 0.0;
        ListaEncadeada<NoInt>* clustersCobertos = new ListaEncadeada<NoInt>();
        ListaEncadeada<NoInt>* nosNaArvore = new ListaEncadeada<NoInt>();
    
        cout << "🔍 Iniciando cálculo da AGMG..." << endl;
    
        if (!clusters) {
            cerr << "❌ ERRO FATAL: clusters está nullptr!" << endl;
            return -1;
        }
    
        // 🟢 Escolher nó inicial com mais vizinhos válidos
        int melhorNo = -1, maxVizinhos = -1;
        for (int i = 1; i <= get_ordem(); i++) {
            int vizinhos = 0;
            for (int j = 1; j <= get_ordem(); j++) {
                if (get_aresta(i, j) > 0 && encontrarCluster(i) != encontrarCluster(j)) {
                    vizinhos++;
                }
            }
            if (vizinhos > maxVizinhos) {
                melhorNo = i;
                maxVizinhos = vizinhos;
            }
        }
    
        if (melhorNo == -1) {
            cout << "❌ Erro: Nenhum nó válido encontrado!" << endl;
            return -1;
        }
    
        cout << "✔ Nó inicial: " << melhorNo << endl;
        nosNaArvore->adicionar(new NoInt(melhorNo));
        clustersCobertos->adicionar(new NoInt(encontrarCluster(melhorNo)));
    
        // 🟢 Expansão progressiva da árvore
        while (clustersCobertos->get_tamanho() < clusters->get_tamanho()) {
            int proximoNo = -1, menorPeso = INT_MAX;
            ArestaEncadeada* melhorAresta = nullptr;
    
            NoInt* noAtual = nosNaArvore->getInicio();
            while (noAtual != nullptr) {
                for (int j = 1; j <= get_ordem(); j++) {
                    int pesoAresta = get_aresta(noAtual->valor, j);
                    if (pesoAresta > 0) {
                        int clusterVizinho = encontrarCluster(j);
                        if (clustersCobertos->get_tamanho() >= clusters->get_tamanho()) break;
    
                        cout << "🔹 Tentando expandir com aresta " << noAtual->valor << " <-> " << j
                             << " (Peso: " << pesoAresta << ", Cluster vizinho: " << clusterVizinho << ")" << endl;
    
                        bool jaNaArvore = false;
                        NoInt* naArvore = nosNaArvore->getInicio();
                        while (naArvore != nullptr) {
                            if (naArvore->valor == j) {
                                jaNaArvore = true;
                                break;
                            }
                            naArvore = naArvore->getProximo();
                        }
    
                        bool clusterJaCoberto = false;
                        NoInt* coberto = clustersCobertos->getInicio();
                        while (coberto != nullptr) {
                            if (coberto->valor == clusterVizinho) {
                                clusterJaCoberto = true;
                                break;
                            }
                            coberto = coberto->getProximo();
                        }
    
                        if (!jaNaArvore && !clusterJaCoberto) {
                            if (pesoAresta < menorPeso) {
                                proximoNo = j;
                                menorPeso = pesoAresta;
                                melhorAresta = new ArestaEncadeada(
                                    new VerticeEncadeado(noAtual->valor, 1),
                                    new VerticeEncadeado(j, 1),
                                    pesoAresta
                                );
                            }
                        }
                    }
                }
                noAtual = noAtual->getProximo();
            }
    
            if (proximoNo == -1) {
                cout << "❌ Erro: Não foi possível conectar todos os clusters!" << endl;
                break;
            }
    
            nosNaArvore->adicionar(new NoInt(proximoNo));
            clustersCobertos->adicionar(new NoInt(encontrarCluster(proximoNo)));
    
            if (melhorAresta) {
                pesoTotal += melhorAresta->getPeso();
                resultado->adicionar(melhorAresta);
                cout << "✔ Adicionando aresta: " << melhorAresta->getOrigem()->getId()
                     << " -> " << melhorAresta->getDestino()->getId()
                     << " (Peso: " << melhorAresta->getPeso() << ")" << endl;
                cout << "⚡ Peso Total atualizado: " << pesoTotal << endl;
            }
        }
    
        cout << "✔ AGMG construída com sucesso!" << endl;
        cout << "🔸 Peso total da árvore geradora mínima: " << pesoTotal << endl;
    
        delete clustersCobertos;
        delete nosNaArvore;
    
        return pesoTotal;
    }
    
    
    
    
    void imprimirAGMG(float pesoTotalAGMG) {
        if (pesoTotalAGMG == 0.0) {
            cout << "A AGMG ainda não foi construída ou não possui arestas." << endl;
            return;
        }
    
        cout << "Peso total da Árvore Geradora Mínima dos Clusters: " << pesoTotalAGMG << endl;
    
        ArestaEncadeada* atual = resultado->getInicio();
        while (atual != nullptr) {
            cout << atual->getOrigem()->getId() << " -- "
                 << atual->getDestino()->getId()
                 << " (Peso: " << atual->getPeso() << ")" << endl;
            atual = atual->getProximo();
        }
    }
    
    
    int encontrarCluster(int id) {
        Cluster* atual = clusters->getInicio();
        while (atual != nullptr) {
            ListaEncadeada<VerticeEncadeado>* verticesCluster = atual->getVertices();
            VerticeEncadeado* v = verticesCluster->getInicio();
            while (v != nullptr) {
                if (v->getId() == id) return atual->getId();
                v = v->getProximo();
            }
            atual = atual->getProximo();
        }
        return -1; // Caso não encontrado
    }
    
    void carrega_clusters() { 
        cout << "🔍 [DEBUG CARREGA_CLUSTERS] Antes da inicialização, clusters = " << clusters << std::endl;
    
        if (!clusters || clusters == reinterpret_cast<ListaEncadeada<Cluster>*>(-1)) {
            cerr << "❌ ERRO FATAL: clusters está inválido ANTES da inicialização!" << endl;
            clusters = new ListaEncadeada<Cluster>();
            if (clusters) {
                cout << "✅ [DEBUG] clusters foi alocado dinamicamente!" << endl;
            } else {
                cerr << "❌ ERRO GRAVE: Falha ao alocar clusters!" << endl;
                return;
            }
        }
    
        ifstream arquivo("./entradas/Clusters.txt");
        if (!arquivo.is_open()) {
            cerr << "Erro ao abrir o arquivo Clusters.txt" << endl;
            return;
        }
    
        int clusterId, vertice;
        cout << "🔍 Carregando clusters...\n";
    
        while (arquivo >> clusterId >> vertice) {
            cout << "➡️ [DEBUG] Tentando adicionar vértice " << vertice << " ao cluster " << clusterId << endl;
    
            Cluster* clusterExistente = nullptr;
            for (Cluster* atual = clusters->getInicio(); atual != nullptr; atual = atual->getProximo()) {
                if (atual->getId() == clusterId) {
                    clusterExistente = atual;
                    break;
                }
            }
            
            if (!clusterExistente) {
                clusterExistente = new Cluster(clusterId);
                clusters->adicionar(clusterExistente);
                cout << "➕ [DEBUG] Criado novo Cluster " << clusterId << endl;
            }
    
            clusterExistente->adicionarVertice(vertice);
            cout << "✔ Cluster " << clusterId << " recebeu vértice " << vertice << endl;
        }
    
        arquivo.close();
        cout << "✔ Clusters carregados com sucesso! Tamanho final: " << clusters->get_tamanho() << endl;
    }
    
};




#endif // GRAFO_H_INCLUDED
