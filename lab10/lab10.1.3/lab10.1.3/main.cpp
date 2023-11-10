#define _CRT_SECURE_NO_WARNINGS
#include <clocale>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// ������� ��� ������ ������������ ����������
int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// ������� ��� ������ ������� ���������
void printMatrix(int** graph, int V) {
    printf("������� ���������:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

// ������� ��� ������ ����������� ������ ����������
void printSolution(int dist[], int V) {
    printf("������� \t ���������� �� ��������� �������\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// ������� ��� ���������� ������ ���������� � �����
void dijkstra(int** graph, int src, int V, int* dist) {
    int* sptSet = (int*)malloc(V * sizeof(int)); // ������ ��� ������������ ���������� ������

    // ������������� ������� ���������� � ������� ���������� ������
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // ���������� �� ��������� ������� �� �� ����� ����� 0
    dist[src] = 0;

    // ����� ����������� ���� ��� ���� ������
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);

        // �������� ��������� ������� ��� ����������
        sptSet[u] = 1;

        // ��������� �������� ���������� ��� ������� ��������� �������
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    free(sptSet);
}

// ������� ��� ����������� ������� �����
int findRadius(int** graph, int V) {
    int minEccentricity = INT_MAX;

    for (int i = 0; i < V; i++) {
        int* dist = (int*)malloc(V * sizeof(int));
        dijkstra(graph, i, V, dist);

        int maxDistance = 0;

        for (int j = 0; j < V; j++) {
            if (dist[j] != INT_MAX && dist[j] > maxDistance) {
                maxDistance = dist[j];
            }
        }

        if (maxDistance < minEccentricity) {
            minEccentricity = maxDistance;
        }

        free(dist);
    }

    return minEccentricity;
}

// ������� ��� ����������� �������� �����
int findDiameter(int** graph, int V) {
    int maxEccentricity = 0;

    for (int i = 0; i < V; i++) {
        int* dist = (int*)malloc(V * sizeof(int));
        dijkstra(graph, i, V, dist);

        int maxDistance = 0;

        for (int j = 0; j < V; j++) {
            if (dist[j] != INT_MAX && dist[j] > maxDistance) {
                maxDistance = dist[j];
            }
        }

        if (maxDistance > maxEccentricity) {
            maxEccentricity = maxDistance;
        }

        free(dist);
    }

    return maxEccentricity;
}

// ������� ��� ����������� ����������� ������
void findCentralVertices(int** graph, int V, int radius) {
    printf("����������� ������� (�������������� ����� ������� �����):\n");
    for (int i = 0; i < V; i++) {
        int* dist = (int*)malloc(V * sizeof(int));
        dijkstra(graph, i, V, dist);
        int maxDistance = 0;

        for (int j = 0; j < V; j++) {
            if (dist[j] != INT_MAX && dist[j] > maxDistance) {
                maxDistance = dist[j];
            }
        }

        if (maxDistance == radius) {
            printf("%d\n", i);
        }

        free(dist);
    }
}

// ������� ��� ����������� ������������ ������
void findPeripheralVertices(int** graph, int V, int diameter) {
    printf("������������ ������� (�������������� ����� �������� �����):\n");
    for (int i = 0; i < V; i++) {
        int* dist = (int*)malloc(V * sizeof(int));
        dijkstra(graph, i, V, dist);
        int maxDistance = 0;

        for (int j = 0; j < V; j++) {
            if (dist[j] != INT_MAX && dist[j] > maxDistance) {
                maxDistance = dist[j];
            }
        }

        if (maxDistance == diameter) {
            printf("%d\n", i);
        }

        free(dist);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int V; // ���������� ������
    printf("������� ���������� ������ � �����: ");
    scanf("%d", &V);

    // �������� ����� � �������������� ���������� ������� ���������
    int** graph = (int**)malloc(V * sizeof(int*));

    // ������������� ���������� ��������� �����
    srand(time(NULL));

    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0; // ���������� �� ������� �� ����� ����
            }
            else {
                // ��������� ���������� ������ �� 1 �� 10
                graph[i][j] = rand() % 10 + 1;
            }
        }
    }

    printMatrix(graph, V);

    // �������� ������� ��� �������� ����������
    int* dist = (int*)malloc(V * sizeof(int));

    // ����� ��������� ������� ��� ������ ����������
    int source;
    printf("������� ��������� ������� ��� ������ ����������: ");
    scanf("%d", &source);

    // ���������� ������ ���������� ��� ����� �� ������ (����� ������� �����)
    dijkstra(graph, source, V, dist);

    // ����� �����������
    printSolution(dist, V);

    // ����������� ������� � ��������
    int radius = findRadius(graph, V);
    int diameter = findDiameter(graph, V);

    printf("������ �����: %d\n", radius);
    printf("������� �����: %d\n", diameter);

    // ����������� ����������� � ������������ ������
    findCentralVertices(graph, V, radius);
    findPeripheralVertices(graph, V, diameter);

    // ������������ ���������� ������
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
    free(dist);

    return 0;
}