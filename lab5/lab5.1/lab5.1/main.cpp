#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale> 

#define MAX_VERTICES 10  // ������������ ���������� ������ � �����

int main() {
    setlocale(LC_ALL, "Russian");

    int n;  // ���������� ������
    int i, j;
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];

    // ������������� ���������� ��������� �����
    srand(time(NULL));

    // ������� ���������� ������ �����
    printf("������� ���������� ������ � ����� (�� ����� %d): ", MAX_VERTICES);
    scanf("%d", &n);

    // ��������� ������� ���������
    printf("������� ��������� �����:\n");
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            if (i == j) {
                adjacencyMatrix[i][j] = 0;  // ��� ����� � �������
            }
            else {
                int random = rand() % 2;  // ��������� 0 ��� 1 ��� ����������� ������� �����
                adjacencyMatrix[i][j] = random;
                adjacencyMatrix[j][i] = random;  // ���� �����������������, ������� �����������
            }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
    // ����������� ������� �����
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (adjacencyMatrix[i][j] == 0)
                continue;
            else
                count++;
        }
    }
    printf("������ �����: %d \n", count);

    // ����� �������������, �������� � ������������ ������

    int isolatedVertices = 0;
    int leafVertices = 0;
    int dominatingVertices = 0;

    for (i = 0; i < n; i++) {
        int degree = 0;
        for (j = 0; j < n; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                degree++;
            }
        }
        if (degree == 0) {
            isolatedVertices++;
        }
        else if (degree == 1) {
            leafVertices++;
        }
        if (degree == n - 1) {
            dominatingVertices++;
        }
    }

    printf("������������� ������: %d\n", isolatedVertices);
    printf("�������� ������: %d\n", leafVertices);
    printf("������������ ������: %d\n", dominatingVertices);

    return 0;
}