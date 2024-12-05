#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

int matLimits(int x, int y, int lines, int cols) {
    return x >= 0 && x < lines && y >= 0 && y < cols;
}

int searchWord(char **mat, int lines, int cols, int x, int y, int dir_x, int dir_y) {
    char word[] = "XMAS";
    for (int i = 0; i < 4; i++) {
        int nx = x + i * dir_x;
        int ny = y + i * dir_y;
        if (!matLimits(nx, ny, lines, cols) || mat[nx][ny] != word[i]) {
            return 0;
        }
    }
    return 1;
}

void markWord(char **mat, int x, int y, int dir_x, int dir_y, char **marked) {
    for (int i = 0; i < 4; i++) {
        int nx = x + i * dir_x;
        int ny = y + i * dir_y;
        marked[nx][ny] = mat[nx][ny];
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
            for (int d = 0; d < 8; d++) {
                if (searchWord(mat, lines, cols, i, j, dx[d], dy[d])) {
                    markWord(mat, i, j, dx[d], dy[d], marked);
                    count++;
                }
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
