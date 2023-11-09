#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <queue>
#include <clocale>

#define MAX_NODES 400

// ������� ��� ��������� ��������� ������� ���������
void generateRandomGraph(int graph[MAX_NODES][MAX_NODES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                graph[i][j] = 0; // ��� ������
            }
            else {
                int random_value = rand() % 2; // ���������� 0 ��� 1
                graph[i][j] = random_value;
                graph[j][i] = random_value; // ���� �����������������
            }
        }
    }
}

// ������� ��� ������ ���������� � ����� � �������������� BFS
void bfs(int graph[MAX_NODES][MAX_NODES], int n, int startNode) {
    bool visited[MAX_NODES] = { false };
    int distances[MAX_NODES] = { 0 };
    std::queue<int> q;

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();

        for (int i = 0; i < n; i++) {
            if (graph[currentNode][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
                distances[i] = distances[currentNode] + 1;
            }
        }
    }

    // ������� ���������� �� startNode �� ���� ��������� �����
    for (int i = 0; i < n; i++) {
        printf("���������� �� ����� %d �� ����� %d: %d\n", startNode, i, distances[i]);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL)); // �������������� ��������� ��������� �����

    int n; // ���������� ����� � �����
    printf("������� ���������� ����� � �����: ");
    scanf("%d", &n);

    int graph[MAX_NODES][MAX_NODES] = { 0 };

    generateRandomGraph(graph, n);

    // ������� ������� ���������
    printf("������� ��������� �����:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    int startNode;
    printf("������� ��������� ���� ��� ������ ����������: ");
    scanf("%d", &startNode);

    clock_t start = clock();
    bfs(graph, n, startNode);
    clock_t end = clock();
    double time_spent5 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time adjmatrix v wiriny: %f s.\n", time_spent5);

    return 0;
}