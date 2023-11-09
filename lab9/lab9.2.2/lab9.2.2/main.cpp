#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <Windows.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];

void addEdge(int from, int to) {
	graph[from][to] = 1;
	graph[to][from] = 1; // ����� ��������� ��� ������������������ �����
}

void initializeGraph(int vertices) {
	for (int i = 0; i < vertices; ++i) {
		for (int j = 0; j < vertices; ++j) {
			graph[i][j] = 0;
		}
	}
}

void printAdjacencyList(int vertices) {
	printf("������ ���������:\n");
	for (int i = 0; i < vertices; ++i) {
		printf("%d: ", i);
		for (int j = 0; j < vertices; ++j) {
			if (graph[i][j] == 1) {
				printf("%d ", j);
			}
		}
		printf("\n");
	}
}

void dfs(int currentVertex, int vertices, bool visited[], int distances[]) {
	visited[currentVertex] = true;

	for (int i = 0; i < vertices; ++i) {
		if (graph[currentVertex][i] == 1 && !visited[i]) {
			distances[i] = distances[currentVertex] + 1;
			dfs(i, vertices, visited, distances);
		}
	}
}

void findDistancesDFS(int startVertex, int vertices, int distances[]) {
	bool visited[MAX_VERTICES] = { false };
	distances[startVertex] = 0;

	dfs(startVertex, vertices, visited, distances);
}

int main() {
	int vertices, edges;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// ������� ���������� ������ � ����
	printf("������� ���������� ������ � ���� �����: ");
	scanf("%d %d", &vertices, &edges);

	initializeGraph(vertices);

	// ���������� ������ ������ �������������
	for (int i = 0; i < edges; ++i) {
		int from = rand() % vertices;
		int to;
		do {
			to = rand() % vertices;
		} while (from == to);

		addEdge(from, to);
	}

	printAdjacencyList(vertices);

	int startVertex;
	// ������� ��������� �������
	printf("������� ��������� �������: ");
	scanf("%d", &startVertex);

	int distances[MAX_VERTICES];
	for (int i = 0; i < vertices; ++i) {
		distances[i] = INT_MAX;
	}

	findDistancesDFS(startVertex, vertices, distances);

	// �������� ���������� �� ��������� ������� �� ���� ���������
	printf("���������� �� ������� %d �� ���� ��������� (�� ������ � �������):\n", startVertex);
	for (int i = 0; i < vertices; ++i) {
		if (distances[i] == INT_MAX) {
			printf("�� ������� %d: �����������\n", i);
		}
		else {
			printf("�� ������� %d: %d\n", i, distances[i]);
		}
	}

	return 0;
}