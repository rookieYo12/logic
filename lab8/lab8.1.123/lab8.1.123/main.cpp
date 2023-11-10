#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <clocale>

#define MAX_VERTICES 6 // ������������ ���������� ������
#define MAX_QUEUE_SIZE 100


// ��������� ��������� ������� ���������
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

// ������� ��� ������ � ������
void breadthFirstSearch(int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES], int startVertex, int numVertices) {
    bool visited[MAX_VERTICES] = { 0 };
    int queue[MAX_QUEUE_SIZE];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    printf("���������� �������: %d\n", startVertex);
    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        for (int neighbor = 0; neighbor < numVertices; neighbor++) {
            if (adjacencyMatrix[currentVertex][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = true;
                printf("���������� �������: %d\n", neighbor);
                queue[rear++] = neighbor;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int numVertices = 6; // ������� �������� ���������� ������
    int numEdges = 8;    // ������� �������� ���������� �����
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    generateRandomAdjacencyMatrix(adjacencyMatrix, numVertices, numEdges);


    printf("������� ���������:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }

    int startVertex;
    printf("������� ��������� ������� ��� ������ � ������ (�� 0 �� %d): ", numVertices - 1);
    scanf("%d", &startVertex);

    if (startVertex < 0 || startVertex >= numVertices) {
        printf("������������ ��������� �������.\n ����������, ������� ������� ����� 0 � %d.\n", numVertices - 1);
        return 1;//����� � �������
    }

    printf("����� � ������, ������� � ������� %d:\n", startVertex);
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
//// ������� ��� ���������� ����� ����� ��������� u � v
//void addEdge(int adjacencyList[MAX_VERTICES][MAX_VERTICES], int u, int v) {
//    adjacencyList[u][v] = 1;
//    adjacencyList[v][u] = 1; // ��� ��������������� �����
//}
//
//// ��������� ��� ������ ������ ��������� �����
//void printAdjacencyList(int adjacencyList[MAX_VERTICES][MAX_VERTICES], int numVertices) {
//    printf("������ ��������� �����:\n");
//    for (int i = 0; i < numVertices; i++) {
//        printf("������� %d: ", i);
//        for (int j = 0; j < numVertices; j++) {
//            if (adjacencyList[i][j] == 1) {
//                printf("%d ", j);
//            }
//        }
//        printf("\n");
//    }
//}
//
//// ��������� ������ � ������
//void breadthFirstSearch(int adjacencyList[MAX_VERTICES][MAX_VERTICES], int startVertex, int numVertices) {
//    bool visited[MAX_VERTICES] = { false };
//    int queue[MAX_VERTICES];
//    int front = 0, rear = 0;
//
//    visited[startVertex] = true;
//    printf("���������� �������: %d\n", startVertex);
//    queue[rear++] = startVertex;
//
//    while (front < rear) {
//        int currentVertex = queue[front++];
//        for (int neighbor = 0; neighbor < numVertices; neighbor++) {
//            if (adjacencyList[currentVertex][neighbor] == 1 && !visited[neighbor]) {
//                visited[neighbor] = true;
//                printf("���������� �������: %d\n", neighbor);
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
//    // ���������� ����� ����� ��������� (������)
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
//    printf("������� ��������� ������� ��� ������ � ������ (�� 0 �� %d): ", numVertices - 1);
//    scanf("%d", &startVertex);
//
//    if (startVertex < 0 || startVertex >= numVertices) {
//        printf("������������ ��������� �������. ����������, ������� ������� ����� 0 � %d.\n", numVertices - 1);
//        return 1; // ����� � ����� ������
//    }
//
//    printf("����� � ������, ������� � ������� %d:\n", startVertex);
//    breadthFirstSearch(adjacencyList, startVertex, numVertices);
//
//    return 0;
//}