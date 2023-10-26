#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <clocale>

#define MAX_VERTICES 100

// ������� ��� ���������� ������� � ������ ���������
void addEdge(int* adjacencyLists[], int u, int v) {
	// �������� ������� v � ������ ��������� ������� u
	adjacencyLists[u][v] = 1;

	// ��� ������������������ �����
	adjacencyLists[v][u] = 1;
}

// ������� ��� ������ ������ ���������
void printAdjacencyList(int* adjacencyLists[], int numVertices) {
	for (int i = 0; i < numVertices; i++) {
		printf("������ ��������� ��� ������� %d: ", i);
		for (int j = 0; j < numVertices; j++) {
			if (adjacencyLists[i][j] == 1) {
				printf("%d -> ", j);
			}
		}
		printf("---- \n");
	}
}

// ������� ��� ������ � �������
void DFS(int* adjacencyLists[], int numVertices, int vertex, int visited[]) {
	visited[vertex] = 1;
	printf("���������� �������: %d\n", vertex);

	for (int i = 0; i < numVertices; i++) {
		if (adjacencyLists[vertex][i] == 1 && !visited[i]) {
			DFS(adjacencyLists, numVertices, i, visited);
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	int numVertices = 6;
	int* adjacencyLists[MAX_VERTICES];

	for (int i = 0; i < numVertices; i++) {
		adjacencyLists[i] = (int*)malloc(numVertices * sizeof(int));
		for (int j = 0; j < numVertices; j++) {
			adjacencyLists[i][j] = 0; // ������������� ������
		}
	}

	addEdge(adjacencyLists, 0, 1);
	addEdge(adjacencyLists, 0, 2);
	addEdge(adjacencyLists, 1, 3);
	addEdge(adjacencyLists, 2, 4);
	addEdge(adjacencyLists, 3, 5);

	int visited[MAX_VERTICES] = { 0 };

	printf("������ ���������:\n");
	printAdjacencyList(adjacencyLists, numVertices);

	int startVertex;
	printf("������� ��������� ������� (�� 0 �� %d): ", numVertices - 1);
	scanf("%d", &startVertex);

	if (startVertex >= 0 && startVertex < numVertices) {
		printf("��������� ������ � �������, ������� � ������� %d:\n", startVertex);
		DFS(adjacencyLists, numVertices, startVertex, visited);
	}
	else {
		printf("������������ ���� ��������� �������.\n");
	}

	// ������������ ������
	for (int i = 0; i < numVertices; i++) {
		free(adjacencyLists[i]);
	}

	return 0;
}