#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct FilmeAtor {
    string ator1;
    string filme;
    string ator2;
};

// Função responsável por calcular o número de Bacon para cada ator
void calcularNumerosDeBacon(const vector<FilmeAtor>& filmesAtores) {
    map<string, int> numerosDeBacon;
    map<string, string> filmesBacon;
    map<string, set<string>> listaDeAdjacencia;

    // Construir o grafo a partir dos pares de atores em filmes
    for (const auto& filmeAtor : filmesAtores) {
        listaDeAdjacencia[filmeAtor.ator1].insert(filmeAtor.ator2);
        listaDeAdjacencia[filmeAtor.ator2].insert(filmeAtor.ator1);
    }

    queue<string> filaBFS;
    set<string> atoresVisitados;

    string kevinBacon = "Kevin Bacon";
    numerosDeBacon[kevinBacon] = 0;
    filaBFS.push(kevinBacon);

    while (!filaBFS.empty()) {
        string atorAtual = filaBFS.front();
        filaBFS.pop();

        atoresVisitados.insert(atorAtual);

        // Percorrer os vizinhos do ator atual no grafo
        for (const auto& vizinho : listaDeAdjacencia[atorAtual]) {
            // Verificar se o vizinho ainda não foi visitado
            if (atoresVisitados.count(vizinho) == 0) {
                numerosDeBacon[vizinho] = numerosDeBacon[atorAtual] + 1;
                filmesBacon[vizinho] = "";
                // Encontrar o filme em comum entre o atorAtual e o vizinho
                for (const auto& filmeAtor : filmesAtores) {
                    if ((filmeAtor.ator1 == atorAtual && filmeAtor.ator2 == vizinho) ||
                        (filmeAtor.ator1 == vizinho && filmeAtor.ator2 == atorAtual)) {
                        filmesBacon[vizinho] = filmeAtor.filme;
                        break;
                    }
                }
                filaBFS.push(vizinho);
            }
        }
    }

    // Imprimir os números de Bacon para cada ator
    for (const auto& par : numerosDeBacon) {
        string ator = par.first;
        int numeroDeBacon = par.second;
        string filme = filmesBacon[ator];
        cout << "O numero de Bacon de " << ator << " eh " << numeroDeBacon << " pelo filme " << filme << endl;
    }
}

// função que lê o arquivo de entrada e chama a função calcularNumerosDeBacon
void lerArquivo() {
    vector<FilmeAtor> filmesAtores;

    ifstream arquivoDeEntrada("input.txt");
    if (!arquivoDeEntrada) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        exit(1);
    }

    string linha;
    while (getline(arquivoDeEntrada, linha)) {
        istringstream iss(linha);
        string ator1, filme, ator2;
        if (getline(iss, ator1, ';') &&
            getline(iss, filme, ';') &&
            getline(iss, ator2)) {
            FilmeAtor filmeAtor;
            filmeAtor.ator1 = ator1;
            filmeAtor.filme = filme;
            filmeAtor.ator2 = ator2;
            filmesAtores.push_back(filmeAtor);
        }
    }

    arquivoDeEntrada.close();

    // Ordenar os filmes e atores em ordem alfabética pelo ator1
    sort(filmesAtores.begin(), filmesAtores.end(), [](const FilmeAtor& a, const FilmeAtor& b) {
        return a.ator1 < b.ator1;
    });

    calcularNumerosDeBacon(filmesAtores);
}

int main() {
    lerArquivo();
    return 0;
}

/*
Análise de complexidade:
    - O algoritmo de busca em largura (BFS) é utilizado para calcular o número de Bacon de cada ator.
    - O algoritmo de ordenação quicksort é utilizado para ordenar os filmes e atores em ordem alfabética pelo ator1.
    - A complexidade do algoritmo de busca em largura é O(V + E), onde V é o número de vértices e E é o número de arestas.
    - A complexidade do algoritmo de ordenação quicksort é O(n log n), onde n é o número de elementos a serem ordenados.
    - A complexidade total do algoritmo é O(V + E + n log n).

    - O número de vértices é igual ao número de atores, que é igual ao número de linhas do arquivo de entrada.
    - O número de arestas é igual ao número de pares de atores em filmes, que é igual ao número de linhas do arquivo de entrada.
    - O número de elementos a serem ordenados é igual ao número de pares de atores em filmes, que é igual ao número de linhas do arquivo de entrada.

*/