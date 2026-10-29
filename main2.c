#define _CRT_SECURE_NO_WARNINGS
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
    for (int j = 0; j < n; j++) printf("%8s", names[j]);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%6s", names[i]);
        for (int j = 0; j < n; j++) printf("%8d", mat[i][j]);
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
            if ((double)rand() / RAND_MAX < p)
                mat[i][j] = mat[j][i] = 1;
}

void identify_vertices(int n, int mat[MAXV][MAXV], char names[MAXV][MAXNAME],
    int u, int v, int* nn, int res[MAXV][MAXV], char res_names[MAXV][MAXNAME]) {
    if (u == v) { printf("Вершины должны быть различны!\n"); *nn = -1; return; }

    int map[MAXV];
    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (i == u || i == v) map[i] = -1;
        else map[i] = idx++;
    }
    int z = idx;
    int total = idx + 1;

    for (int i = 0; i < total; i++)
        for (int j = 0; j < total; j++) res[i][j] = 0;

    for (int i = 0; i < n; i++) {
        if (map[i] != -1) strcpy(res_names[map[i]], names[i]);
    }
    snprintf(res_names[z], MAXNAME, "%s%s", names[u], names[v]);

    for (int i = 0; i < n; i++) {
        if (map[i] == -1) continue;
        for (int j = 0; j < n; j++) {
            if (map[j] == -1) continue;
            if (mat[i][j]) res[map[i]][map[j]] = 1;
        }
    }

    for (int w = 0; w < n; w++) {
        if (map[w] == -1) continue;
        if (mat[w][u] || mat[w][v]) {
            res[map[w]][z] = 1;
            res[z][map[w]] = 1;
        }
    }

    if (mat[u][v] || mat[u][u] || mat[v][v])
        res[z][z] = 1;

    *nn = total;
}

void contract_edge(int n, int mat[MAXV][MAXV], char names[MAXV][MAXNAME],
    int u, int v, int* nn, int res[MAXV][MAXV], char res_names[MAXV][MAXNAME]) {
    if (u == v) { printf("Вершины должны быть различны!\n"); *nn = -1; return; }
    if (mat[u][v] == 0) { printf("Ребра между вершинами нет!\n"); *nn = -1; return; }

    int tmp[MAXV][MAXV];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) tmp[i][j] = mat[i][j];
    tmp[u][v] = 0;
    tmp[v][u] = 0;

    identify_vertices(n, tmp, names, u, v, nn, res, res_names);

    if (*nn > 0) {
        int z = *nn - 1;
        snprintf(res_names[z], MAXNAME, "(%s %s)", names[u], names[v]);
    }
}

void split_vertex(int n, int mat[MAXV][MAXV], char names[MAXV][MAXNAME],
    int v, int* nn, int res[MAXV][MAXV], char res_names[MAXV][MAXNAME]) {
    int total = n + 1, w = n;

    for (int i = 0; i < total; i++)
        for (int j = 0; j < total; j++) res[i][j] = 0;

    for (int i = 0; i < n; i++) {
        strcpy(res_names[i], names[i]);
        for (int j = 0; j < n; j++)
            res[i][j] = mat[i][j];
    }

    snprintf(res_names[w], MAXNAME, "%s*", names[v]);

    for (int i = 0; i < n; i++) {
        if (mat[v][i]) {
            res[w][i] = 1;
            res[i][w] = 1;
        }
    }

    res[v][w] = 1;
    res[w][v] = 1;

    *nn = total;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(NULL));

    int n;
    printf("Введите число вершин для G1 и G2: ");
    scanf_s("%d", &n);
    if (n <= 0 || n > MAXV) { printf("Неверное число!\n"); return 1; }

    int G1[MAXV][MAXV], G2[MAXV][MAXV];
    char names1[MAXV][MAXNAME], names2[MAXV][MAXNAME];

    for (int i = 0; i < n; i++) {
        snprintf(names1[i], MAXNAME, "v%d", i + 1);
        snprintf(names2[i], MAXNAME, "v%d", i + 1);
    }

    generate_graph(n, G1, 0.5);
    generate_graph(n, G2, 0.5);

    printf("\n Исходный граф G1 \n");
    print_matrix(n, G1, names1);
    print_adj_list(n, G1, names1);

    printf("\n Исходный граф G2 \n");
    print_matrix(n, G2, names2);
    print_adj_list(n, G2, names2);

    int op, g, u, v, nn;
    int res[MAXV][MAXV];
    char res_names[MAXV][MAXNAME];

    while (1) {
        printf("\n МЕНЮ \n");
        printf(" 1 - отождествление вершин\n");
        printf(" 2 - стягивание ребра\n");
        printf(" 3 - расщепление вершины\n");
        printf(" 4 - показать исходные G1 и G2\n");
        printf(" 0 - выход\n");
        printf("Выбор операции: ");
        scanf_s("%d", &op);
        if (op == 0) break;

        if (op == 4) {
            printf("\n G1 \n");
            print_matrix(n, G1, names1);
            print_adj_list(n, G1, names1);
            printf("\n G2 \n");
            print_matrix(n, G2, names2);
            print_adj_list(n, G2, names2);
            continue;
        }

        printf("К какому графу применить? (1-G1, 2-G2): ");
        scanf_s("%d", &g);
        if (g != 1 && g != 2) { printf("Неверно!\n"); continue; }

        int (*G)[MAXV] = (g == 1) ? G1 : G2;
        char (*nm)[MAXNAME] = (g == 1) ? names1 : names2;

        if (op == 1) {
            printf("Введите номера вершин u v для отождествления (1..%d): ", n);
            scanf_s("%d %d", &u, &v);
            if (u < 1 || u > n || v < 1 || v > n) { printf("Ошибка!\n"); continue; }
            identify_vertices(n, G, nm, u - 1, v - 1, &nn, res, res_names);
        }
        else if (op == 2) {
            printf("Введите вершины u v для стягивания ребра (1..%d): ", n);
            scanf_s("%d %d", &u, &v);
            if (u < 1 || u > n || v < 1 || v > n) { printf("Ошибка!\n"); continue; }
            contract_edge(n, G, nm, u - 1, v - 1, &nn, res, res_names);
        }
        else if (op == 3) {
            printf("Введите номер вершины для расщепления (1..%d): ", n);
            scanf_s("%d", &v);
            if (v < 1 || v > n) { printf("Ошибка!\n"); continue; }
            split_vertex(n, G, nm, v - 1, &nn, res, res_names);
        }
        else {
            printf("Неверная операция!\n");
            continue;
        }

        if (nn > 0) {
            printf("\nРезультат:\n");
            print_matrix(nn, res, res_names);
            print_adj_list(nn, res, res_names);
        }
    }
    return 0;
}