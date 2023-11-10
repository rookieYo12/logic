#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <clocale>

#define MAX_VERTICES 6 // Максимальное количество вершин
#define MAX_QUEUE_SIZE 100


// Генерация случайной матрицы смежности
void generateRandomAdjacencyMatrix(int matrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int numEdges) {
    int i, j;
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            matrix[i][j] = 0;
        }
    }

    int edgeCount = 0;
    while (edgeCount < numEdges) {
        int vertex1 = rand() % numVertices;
        int vertex2 = rand() % numVertices;

        if (vertex1 != vertex2 && matrix[vertex1][vertex2] == 0) {
            matrix[vertex1][vertex2] = 1;
            matrix[vertex2][vertex1] = 1;
            edgeCount++;
        }
    }
}

// Функция для обхода в ширину
void breadthFirstSearch(int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES], int startVertex, int numVertices) {
    bool visited[MAX_VERTICES] = { 0 };
    int queue[MAX_QUEUE_SIZE];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    printf("Посещенная вершина: %d\n", startVertex);
    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        for (int neighbor = 0; neighbor < numVertices; neighbor++) {
            if (adjacencyMatrix[currentVertex][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = true;
                printf("Посещенная вершина: %d\n", neighbor);
                queue[rear++] = neighbor;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int numVertices = 6; // Задайте желаемое количество вершин
    int numEdges = 8;    // Задайте желаемое количество ребер
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    generateRandomAdjacencyMatrix(adjacencyMatrix, numVertices, numEdges);


    printf("Матрица смежности:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    int startVertex;
    printf("Введите начальную вершину для обхода в ширину (от 0 до %d): ", numVertices - 1);
    scanf("%d", &startVertex);

    if (startVertex < 0 || startVertex >= numVertices) {
        printf("Недопустимая начальная вершина.\n Пожалуйста, введите вершину между 0 и %d.\n", numVertices - 1);
        return 1;//выход с ошибкой
    }

    printf("Обход в ширину, начиная с вершины %d:\n", startVertex);
    breadthFirstSearch(adjacencyMatrix, startVertex, numVertices);

    return 0;
}
//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <clocale>
//
//#define MAX_VERTICES 6
//
//// Функция для добавления ребра между вершинами u и v
//void addEdge(int adjacencyList[MAX_VERTICES][MAX_VERTICES], int u, int v) {
//    adjacencyList[u][v] = 1;
//    adjacencyList[v][u] = 1; // Для ненаправленного графа
//}
//
//// Процедура для вывода списка смежности графа
//void printAdjacencyList(int adjacencyList[MAX_VERTICES][MAX_VERTICES], int numVertices) {
//    printf("Список смежности графа:\n");
//    for (int i = 0; i < numVertices; i++) {
//        printf("Вершина %d: ", i);
//        for (int j = 0; j < numVertices; j++) {
//            if (adjacencyList[i][j] == 1) {
//                printf("%d ", j);
//            }
//        }
//        printf("\n");
//    }
//}
//
//// Процедура обхода в ширину
//void breadthFirstSearch(int adjacencyList[MAX_VERTICES][MAX_VERTICES], int startVertex, int numVertices) {
//    bool visited[MAX_VERTICES] = { false };
//    int queue[MAX_VERTICES];
//    int front = 0, rear = 0;
//
//    visited[startVertex] = true;
//    printf("Посещенная вершина: %d\n", startVertex);
//    queue[rear++] = startVertex;
//
//    while (front < rear) {
//        int currentVertex = queue[front++];
//        for (int neighbor = 0; neighbor < numVertices; neighbor++) {
//            if (adjacencyList[currentVertex][neighbor] == 1 && !visited[neighbor]) {
//                visited[neighbor] = true;
//                printf("Посещенная вершина: %d\n", neighbor);
//                queue[rear++] = neighbor;
//            }
//        }
//    }
//}
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//    int numVertices = 6;
//    int adjacencyList[MAX_VERTICES][MAX_VERTICES] = { 0 };
//
//    // Добавление ребер между вершинами (пример)
//    addEdge(adjacencyList, 0, 1);
//    addEdge(adjacencyList, 0, 2);
//    addEdge(adjacencyList, 1, 3);
//    addEdge(adjacencyList, 2, 3);
//    addEdge(adjacencyList, 3, 4);
//    addEdge(adjacencyList, 4, 5);
//
//    printAdjacencyList(adjacencyList, numVertices);
//
//    int startVertex;
//    printf("Введите начальную вершину для обхода в ширину (от 0 до %d): ", numVertices - 1);
//    scanf("%d", &startVertex);
//
//    if (startVertex < 0 || startVertex >= numVertices) {
//        printf("Недопустимая начальная вершина. Пожалуйста, введите вершину между 0 и %d.\n", numVertices - 1);
//        return 1; // Выход с кодом ошибки
//    }
//
//    printf("Обход в ширину, начиная с вершины %d:\n", startVertex);
//    breadthFirstSearch(adjacencyList, startVertex, numVertices);
//
//    return 0;
//}