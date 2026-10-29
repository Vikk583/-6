#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(NULL));

    int n1, n2;
    int G1[50][50] = { 0 };
    int G2[50][50] = { 0 };
    int R[50][50] = { 0 };

    printf(" количество вершин графа G1 (от 1 до 50): ");
    scanf_s("%d", &n1);

    printf(" количество вершин графа G2 (от 1 до 50): ");
    scanf_s("%d", &n2);

    if (n1 < 1 || n1 > 50 || n2 < 1 || n2 > 50) {
        printf(" количество вершин должно быть от 1 до 50.\n");
        return 1;
    }

    for (int i = 0; i < n1; i++) {
        for (int j = i + 1; j < n1; j++) {
            if (rand() % 2)
                G1[i][j] = G1[j][i] = 1;
        }
    }

    for (int i = 0; i < n2; i++) {
        for (int j = i + 1; j < n2; j++) {
            if (rand() % 2)
                G2[i][j] = G2[j][i] = 1;
        }
    }

    printf("\n матрица смежности G1:\n");
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++)
            printf("%d ", G1[i][j]);
        printf("\n");
    }

    printf("\n матрица смежности G2:\n");
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n2; j++)
            printf("%d ", G2[i][j]);
        printf("\n");
    }

    int n;
    if (n1 > n2)
        n = n1;
    else
        n = n2;

    printf("\nОбъединение:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a = (i < n1 && j < n1) ? G1[i][j] : 0;
            int b = (i < n2 && j < n2) ? G2[i][j] : 0;

            R[i][j] = a | b;
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }

    printf("\nПересечение:\n");

    int minN;
    if (n1 < n2)
        minN = n1;
    else
        minN = n2;

    for (int i = 0; i < minN; i++) {
        for (int j = 0; j < minN; j++) {
            int a = G1[i][j];
            int b = G2[i][j];

            R[i][j] = a & b;
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }

    printf("\nКольцевая сумма:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a = (i < n1 && j < n1) ? G1[i][j] : 0;
            int b = (i < n2 && j < n2) ? G2[i][j] : 0;

            R[i][j] = a ^ b;
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }

    return 0;
}