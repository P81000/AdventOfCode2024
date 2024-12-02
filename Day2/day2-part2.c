#include <stdlib.h>
#include <stdio.h>

int isSafe(int *row, int colCount) {
    for (int i = 1; i < colCount; i++) {
        int diff = abs(row[i] - row[i - 1]);
        if ((diff > 3 || diff == 0) || (i > 1 && ((row[i - 2] < row[i - 1] && row[i - 1] > row[i]) || (row[i - 2] > row[i - 1] && row[i - 1] < row[i])))) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int *row = NULL;
    int num, colCount;
    int safeReports = 0;

    while (1) {
        colCount = 0;
        row = NULL;

        while (scanf("%d", &num) == 1) {
            row = realloc(row, (colCount + 1) * sizeof(int));
            if (row == NULL) {
                printf("Mem alloc failed\n");
                return 1;
            }

            row[colCount] = num;
            colCount++;

            char c = getchar();
            if (c == '\n' || c == EOF) {
                ungetc(c, stdin);
                break;
            }
        }

        if (colCount == 0)
            break;

        if (isSafe(row, colCount)) {
            safeReports++;
        } else {
            int isSafeAfterRemoval = 0;
            for (int i = 0; i < colCount; i++) {
                int *auxRow = malloc((colCount - 1) * sizeof(int));
                if (auxRow == NULL) {
                    printf("Mem alloc failed\n");
                    free(row);
                    return 1;
                }

                for (int j = 0, k = 0; j < colCount; j++) {
                    if (j != i) {
                        auxRow[k++] = row[j];
                    }
                }

                if (isSafe(auxRow, colCount - 1)) {
                    isSafeAfterRemoval = 1;
                    free(auxRow);
                    break;
                }
                free(auxRow);
            }

            if (isSafeAfterRemoval) {
                safeReports++;
            }
        }

        free(row);
        row = NULL;
    }

    printf("%d\n", safeReports);

    return 0;
}
