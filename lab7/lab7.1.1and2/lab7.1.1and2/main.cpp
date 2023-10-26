#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <clocale> 


#define MAX_VERTICES 100

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

// ����� � �������
void depthFirstSearch(int matrix[MAX_VERTICES][MAX_VERTICES], bool visited[MAX_VERTICES], int currentVertex, int numVertices) {
    printf("������� �������: %d\n", currentVertex);
    visited[currentVertex] = true;

    for (int i = 0; i < numVertices; i++) {
        if (matrix[currentVertex][i] == 1 && !visited[i]) {
            depthFirstSearch(matrix, visited, i, numVertices);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
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

    bool visited[MAX_VERTICES];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    int startVertex;
    printf("������� ��������� ������� (�� 0 �� %d): ", numVertices - 1);
    scanf("%d", &startVertex);

    if (startVertex >= 0 && startVertex < numVertices) {
        printf("��������� ������ � �������, ������� � ������� %d:\n", startVertex);
        depthFirstSearch(adjacencyMatrix, visited, startVertex, numVertices);
    }
    else {
        printf("������������ ���� ��������� �������.\n");
    }

    return 0;
}