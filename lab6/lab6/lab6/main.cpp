#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Структура данных для хранения ребра Graph
struct Edge {
    int src, dest;
};

// Класс для представления graphического объекта
class Graph
{
public:

    // вектор векторов для представления списка смежности
    vector<vector<int>> adjList;

    // vector для хранения степени вхождения каждой вершины в Graph
    vector<int> in;

    // Конструктор Graphа
    Graph(int n, vector<Edge> const& edges = {})
    {
        // изменить размер обоих векторов, чтобы каждый из них содержал `n` элементов
        adjList.resize(n);
        in.resize(n);

        // добавить ребра в ориентированный graph и обновить степень вхождения для каждого ребра
        for (auto& edge : edges) {
            addEdge(edge.src, edge.dest);
        }
    }

    // Вспомогательная функция для добавления ребра (u, v) к graphу
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        in[v]++;
    }
};

// Вспомогательная функция для обхода DFS на Graphе
void DFS(Graph const& graph, int u, vector<bool>& visited)
{
    // отметить текущий узел как посещенный
    visited[u] = true;

    // делаем для каждого ребра (u, v)
    for (int v : graph.adjList[u])
    {
        // повторяется, если `v` не посещается
        if (!visited[v]) {
            DFS(graph, v, visited);
        }
    }
}

// Функция для создания транспонированного Graphа, т.е. одного и того же Graphа
// с обратным направлением каждого ребра
Graph buildTranspose(Graph const& graph, int n)
{
    Graph g(n);

    for (int u = 0; u < n; u++)
    {
        // для каждого ребра (u, v) создаем обратное ребро (v, u)
        // в Graph транспонирования
        for (int v : graph.adjList[u]) {
            g.addEdge(v, u);
        }
    }
    return g;
}

// Функция проверки посещаемости всех вершин Graph с ненулевой степенью
bool isVisited(Graph const& graph, const vector<bool>& visited)
{
    for (int i = 0; i < visited.size(); i++)
    {
        if (graph.adjList[i].size() && !visited[i]) {
            return false;
        }
    }
    return true;
}

// Функция для проверки, принадлежат ли все вершины с ненулевой степенью в Graph
// один компонент сильной связности с использованием алгоритма Косараджу
bool isSC(Graph const& graph, int n)
{
    // отслеживаем все ранее посещенные вершины
    vector<bool> visited(n);

    // находим первую вершину `i` с ненулевой степенью и запускаем из нее DFS
    int i;
    for (i = 0; i < n; i++)
    {
        if (graph.adjList[i].size())
        {
            DFS(graph, i, visited);
            break;
        }
    }

    // вернуть false, если DFS не смог посетить все вершины с ненулевой степенью
    if (!isVisited(graph, visited)) {
        return false;
    }

    // сбросить посещенный массив
    fill(visited.begin(), visited.end(), false);

    // создаем транспонирование Graphа
    Graph g = buildTranspose(graph, n);

    // выполнить поиск в глубину на транспонированном Graph, используя ту же начальную вершину, что и
    // использовано в предыдущем вызове DFS
    DFS(g, i, visited);

    // вернуть true, если второй поиск в глубину также исследовал все вершины с ненулевой степенью;
    // false иначе
    return isVisited(g, visited);
}

// Функция для проверки наличия в ориентированном Graph эйлерова цикла
bool hasEulerianCycle(Graph const& graph, int n)
{
    // проверяем, имеют ли все вершины одинаковую степень входа и выхода
    for (int i = 0; i < n; i++)
    {
        if (graph.adjList[i].size() != graph.in[i]) {
            return false;
        }
    }

    // проверяем, принадлежат ли все вершины с ненулевой степенью одному
    // компонент сильной связности
    return isSC(graph, n);
}

int main()
{
    // vector ребер Graph согласно схеме выше
    vector<Edge> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 1}, {1, 4}, {4, 3}, {3, 0}
    };

    // общее количество узлов в Graph (от 0 до 4)
    int n = 5;

    // строим ориентированный graph из указанных выше ребер
    Graph graph(n, edges);

    if (hasEulerianCycle(graph, n)) {
        cout << "The graph has an Eulerian cycle" << endl;
    }
    else {
        cout << "The Graph does not contain Eulerian cycle" << endl;
    }

    return 0;
}