#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<double>> MP;

void leituraGrafo(MP &, int);
void escritaGrafo(MP &);

bool bfs(const MP&, int, int, vector<int>&);
double fordFulkerson(const MP&, int, int);

int main()
{
    int n, m;   // n = vertices ; m = arestas

    cin >> n >> m;

    MP Grafo;
    Grafo.assign(n, vector<double>(n, 0));

    leituraGrafo(Grafo, m);

    escritaGrafo(Grafo);

    int fonte, sumidouro;

    cout << "\nFonte: ";
    cin >> fonte;

    cout << "Sumidouro: ";
    cin >> sumidouro;

    double fluxoMaximo = fordFulkerson(Grafo, fonte, sumidouro);

    cout << "\nFluxo Maximo = " << fluxoMaximo << endl;

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

        for (int v = sumidouro;
             v != fonte;
             v = pai[v])
        {
            int u = pai[v];

            fluxoCaminho =
                min(fluxoCaminho,
                    residual[u][v]);
        }

        for (int v = sumidouro;
             v != fonte;
             v = pai[v])
        {
            int u = pai[v];

            residual[u][v] -= fluxoCaminho;

            residual[v][u] += fluxoCaminho;
        }

        fluxoMaximo += fluxoCaminho;
    }

    return fluxoMaximo;
}

void leituraGrafo(MP &G, int m)
{
    int a, b;
    double c;

    while (m--)
    {
        cin >> a >> b >> c;

        G[a][b] = c;

        // G[b][a] = c;
    }
}

void escritaGrafo(MP &G)
{
    int n = G.size();

    cout << "Matriz de Adjacencia:" << endl;
    cout << "   ";

    for (int u = 0; u < n; u++)
    {
        printf("%4d ", u);
    }

    cout << endl;

    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";

        for (int v = 0; v < n; v++)
        {
            printf("%0.2lf ", G[u][v]);
        }

        cout << endl;
    }
}