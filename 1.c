#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAXV 100
#define MAXNAME 32

void print_matrix(int n, int mat[MAXV][MAXV], char names[MAXV][MAXNAME]) {
    printf("Матрица смежности (%d вершин):\n", n);

    printf("%6s", "");
    for (int j = 0; j < n; j++) printf("%6s", names[j]);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%6s", names[i]);
        for (int j = 0; j < n; j++) printf("%6d", mat[i][j]);
        printf("\n");
    }
}

void print_adj_list(int n, int mat[MAXV][MAXV], char names[MAXV][MAXNAME]) {
    printf("Списки смежности:\n");
    for (int i = 0; i < n; i++) {
        printf("%s: ", names[i]);
        int first = 1;
        for (int j = 0; j < n; j++) {
            if (mat[i][j]) {
                if (!first) printf(", ");
                printf("%s", names[j]);
                first = 0;
            }
        }
        printf("\n");
    }
}

void generate_graph(int n, int mat[MAXV][MAXV], double p) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) mat[i][j] = 0;

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if ((double)rand() / RAND_MAX < p) {
                mat[i][j] = 1;
                mat[j][i] = 1;
            }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(NULL));

    int n;
    printf("Введите число вершин для G1 и G2: ");
    scanf_s("%d", &n);
    if (n <= 0 || n > MAXV) {
        printf("Недопустимое число вершин. Допустимо от 1 до %d.\n", MAXV);
        return 1;
    }

    int M1[MAXV][MAXV], M2[MAXV][MAXV];
    char names[MAXV][MAXNAME];

    for (int i = 0; i < n; i++)
        snprintf(names[i], MAXNAME, "v%d", i + 1);

    generate_graph(n, M1, 0.5);
    generate_graph(n, M2, 0.5);

    printf("\n Граф G1 \n");
    print_matrix(n, M1, names);
    printf("\n");
    print_adj_list(n, M1, names);

    printf("\n Граф G2 \n");
    print_matrix(n, M2, names);
    printf("\n");
    print_adj_list(n, M2, names);

    return 0;
}