#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int n, G1[50][50], G2[50][50], R[50][50];

    printf("Введите n: ");
    scanf_s("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            G1[i][j] = G2[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (rand() % 2) G1[i][j] = G1[j][i] = 1;
            if (rand() % 2) G2[i][j] = G2[j][i] = 1;
        }

    printf("\nG1:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", G1[i][j]);
        printf("\n");
    }
    printf("G2:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", G2[i][j]);
        printf("\n");
    }

    printf("\nОбъединение:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R[i][j] = G1[i][j] | G2[i][j];
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }

    printf("\nПересечение:\n");
    int minN = n - 1;
    for (int i = 0; i < minN; i++) {
        for (int j = 0; j < minN; j++) {
            R[i][j] = G1[i][j] & G2[i][j];
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }

    printf("\nКольцевая сумма:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R[i][j] = G1[i][j] ^ G2[i][j];
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }

    return 0;
}
