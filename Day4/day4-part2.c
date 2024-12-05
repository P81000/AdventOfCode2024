#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matLimits(int x, int y, int lines, int cols) {
    return x >= 0 && x < lines && y >= 0 && y < cols;
}

int checkMAS(char **mat, int x, int y, int lines, int cols) {
    if (mat[x][y] != 'A') return 0;

    int dx[] = {-1, -1, 1, 1};
    int dy[] = {-1,  1, 1, -1};

    for (int i = 0; i < 2; i++) {
        int mx = x + dx[i];
        int my = y + dy[i];
        int sx = x + dx[i + 2];
        int sy = y + dy[i + 2];

        // Verifica se ambos os cantos estão nos limites
        if (!matLimits(mx, my, lines, cols) || !matLimits(sx, sy, lines, cols)) {
            return 0;
        }

        char corner1 = mat[mx][my];
        char corner2 = mat[sx][sy];
        if (!((corner1 == 'M' && corner2 == 'S') || (corner1 == 'S' && corner2 == 'M'))) {
            return 0;
        }
    }

    return 1;
}

void markMAS(char **mat, char **marked, int x, int y, int lines, int cols) {
    marked[x][y] = 'A';

    int dx[] = {-1, -1, 1, 1};
    int dy[] = {-1,  1, 1, -1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (matLimits(nx, ny, lines, cols)) {
            marked[nx][ny] = mat[nx][ny];
        }
    }
}

int main() {
    char **mat = NULL;
    char buffer[1024];
    int lines = 0, cols = 0;

    while (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) break;

        mat = realloc(mat, sizeof(char *) * (lines + 1));
        mat[lines] = strdup(buffer);

        if (lines == 0) cols = strlen(buffer);

        lines++;
    }

    char **marked = malloc(lines * sizeof(char *));
    for (int i = 0; i < lines; i++) {
        marked[i] = malloc((cols + 1) * sizeof(char));
        memset(marked[i], '.', cols);
        marked[i][cols] = '\0';
    }

    int count = 0;

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < cols; j++) {
            if (checkMAS(mat, i, j, lines, cols)) {
                markMAS(mat, marked, i, j, lines, cols);
                count++;
            }
        }
    }

    printf("%d\n", count);

    for (int i = 0; i < lines; i++) {
        free(mat[i]);
        free(marked[i]);
    }
    free(mat);
    free(marked);

    return 0;
}

