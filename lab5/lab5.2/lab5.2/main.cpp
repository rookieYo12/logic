#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale> 


#define MAX_VERTICES 10  // ������������ ���������� ������ � �����
#define MAX_EDGES 20     // ������������ ���������� ���� � �����

int main() {
    setlocale(LC_ALL, "Russian");
    int n;  // ���������� ������
    int m;  // ���������� ����
    int i, j, k;
    int incidenceMatrix[MAX_VERTICES][MAX_EDGES];

    // ������������� ���������� ��������� �����
    srand(time(NULL));

    // ������� ���������� ������ � ���� �����
    printf("������� ���������� ������ � ����� (�� ����� %d): ", MAX_VERTICES);
    scanf("%d", &n);
    printf("������� ���������� ���� � ����� (�� ����� %d): ", MAX_EDGES);
    scanf("%d", &m);

    // ��������� ������� �������������
    printf("������� ������������� �����:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            incidenceMatrix[i][j] = 0;  // �������������� ��� �������� �����
        }
    }
    for (k = 0; k < m; k++) {
        printf("������� ������ ������, ����������� ����� %d (0-%d): ", k, n - 1);
        int vertex1, vertex2;
        scanf("%d %d", &vertex1, &vertex2);
        incidenceMatrix[vertex1][k] = 1;
        incidenceMatrix[vertex2][k] = 1;
    }

    // ����� ������� �������������
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", incidenceMatrix[i][j]);
        }
        printf("\n");
    }

    // ����������� ������� �����
    printf("������ �����: %d ������, %d ����\n", n, m);

    // ����� �������������, �������� � ������������ ������
    int isolatedVertices = 0;
    int leafVertices = 0;
    int dominatingVertices = 0;

    for (i = 0; i < n; i++) {
        int degree = 0;
        for (j = 0; j < m; j++) {
            if (incidenceMatrix[i][j] == 1) {
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