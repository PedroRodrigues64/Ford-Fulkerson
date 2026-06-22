#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

typedef vector<vector<double>> MP;

void leituraGrafo(MP &, int, ifstream &);
void escritaGrafo(MP &, ofstream &);

bool bfs(const MP&, int, int, vector<int>&);
double fordFulkerson(const MP&, int, int);

int main()
{
    ifstream arqIn("entrada.txt");
    ofstream arqOut("saida.txt");

    if (!arqIn)
    {
        cerr << "Erro ao abrir entrada.txt\n";
        return 1;
    }

    int n, m;

    arqIn >> n >> m;

    MP Grafo(n, vector<double>(n, 0));

    leituraGrafo(Grafo, m, arqIn);

    escritaGrafo(Grafo, arqOut);

    int fonte, sumidouro;

    arqIn >> fonte >> sumidouro;

    double fluxoMaximo = fordFulkerson(Grafo, fonte, sumidouro);

    arqOut << "\nFluxo Maximo = " << fluxoMaximo << endl;

    arqIn.close();
    arqOut.close();

    return 0;
}

bool bfs(const MP& residual,
         int fonte,
         int sumidouro,
         vector<int>& pai)
{
    int n = residual.size();

    vector<bool> visitado(n, false);
    queue<int> fila;

    fila.push(fonte);
    visitado[fonte] = true;
    pai[fonte] = -1;

    while (!fila.empty())
    {
        int u = fila.front();
        fila.pop();

        for (int v = 0; v < n; v++)
        {
            if (!visitado[v] && residual[u][v] > 0)
            {
                fila.push(v);
                pai[v] = u;
                visitado[v] = true;
            }
        }
    }

    return visitado[sumidouro];
}

double fordFulkerson(const MP& grafo,
                     int fonte,
                     int sumidouro)
{
    int n = grafo.size();

    MP residual = grafo;
    vector<int> pai(n);

    double fluxoMaximo = 0;

    while (bfs(residual, fonte, sumidouro, pai))
    {
        double fluxoCaminho = numeric_limits<double>::max();

        for (int v = sumidouro; v != fonte; v = pai[v])
        {
            int u = pai[v];
            fluxoCaminho = min(fluxoCaminho, residual[u][v]);
        }

        for (int v = sumidouro; v != fonte; v = pai[v])
        {
            int u = pai[v];

            residual[u][v] -= fluxoCaminho;
            residual[v][u] += fluxoCaminho;
        }

        fluxoMaximo += fluxoCaminho;
    }

    return fluxoMaximo;
}

void leituraGrafo(MP &G, int m, ifstream &arqIn)
{
    int a, b;
    double c;

    while (m--)
    {
        arqIn >> a >> b >> c;
        G[a][b] = c;
    }
}

void escritaGrafo(MP &G, ofstream &arqOut)
{
    int n = G.size();

    arqOut << "Matriz de Adjacencia:\n";
    arqOut << "   ";

    for (int u = 0; u < n; u++)
        arqOut << setw(6) << u;

    arqOut << '\n';

    for (int u = 0; u < n; u++)
    {
        arqOut << u << ": ";

        for (int v = 0; v < n; v++)
            arqOut << fixed << setprecision(2)
                   << setw(6) << G[u][v];

        arqOut << '\n';
    }
}