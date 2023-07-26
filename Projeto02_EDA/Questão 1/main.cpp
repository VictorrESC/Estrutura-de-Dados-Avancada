#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

// função que realiza busca em largura no grafo
bool verticeValido(const vector<list<char>>& grafo) {
    int n = grafo.size();
    vector<char> cores(n, ' '); // ' ' representa vértices não coloridos

    queue<int> q;
    q.push(0); // Começando pelo vértice 0
    cores[0] = 'R'; // Atribuir cor 'R' ao vértice 0

    while (!q.empty()) { // enquanto a fila não estiver vazia
        int u = q.front(); // u é o primeiro vértice da fila
        q.pop(); // remove u da fila

        for (int v : grafo[u]) { // para cada vértice v adjacente a u 
            if (cores[v] == ' ') { // ou seja, se v não foi colorido
                cores[v] = (cores[u] == 'R') ? 'B' : 'R'; // Atribuir uma cor diferente da de u
                q.push(v); // Adicionar v à fila
            } else if (cores[v] == cores[u]) { // Se v já foi colorido e tem a mesma cor de u
                return false; // Vértices adjacentes com a mesma cor, coloração inválida
            }
        }
    }

    return true; // coloração válida
}

void le_arquivo(string nome_arquivo) {
    ifstream arquivo(nome_arquivo);
    if(!arquivo) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        exit(1);
    }

    int n, m, s=1;
    while(arquivo >> n >> m) {
        vector<list<char>> grafo;
        grafo.resize(n);

        int count = m;
        while(count > 0) {
            int u, v;
            arquivo >> u >> v;
            grafo[u].push_back(v);
            grafo[v].push_back(u);
            count--;
        }

        cout << "Grafo " << s << endl;
        bool coloracaoValida = verticeValido(grafo);
        if(coloracaoValida) {
            cout << "SIM" << endl;
        } else {
            cout << "NAO" << endl;
        }
        cout << "-----------------------------------------" << endl;
        // reinicie o grafo para a próxima iteração
        grafo.clear();
        s++;
    }

    arquivo.close();
}


int main() {
    le_arquivo("cubic_bipartite_26_vertices_sim.txt");
}

/*
Análise de complexidade:
    - O algoritmo realiza uma busca em largura no grafo, portanto, a complexidade é O(V+E), onde V é o número de vértices e E o número de arestas.
    - O algoritmo utiliza uma fila para armazenar os vértices que serão visitados, portanto, a complexidade de espaço é O(V).
*/