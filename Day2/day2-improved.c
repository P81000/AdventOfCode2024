#include <stdlib.h>
#include <stdio.h>

int isSafe(int *row, int colCount) {
    int prev = -1, curr = -1, next = -1;

    for (int i = 0; i < colCount; i++) {
        prev = curr;
        curr = next;
        next = row[i];

        if (prev != -1 && curr != -1) {
            int diff = abs(next - curr);
            if ((diff > 3 || diff == 0) ||
                (prev < curr && curr > next) ||
                (prev > curr && curr < next))
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

        // Process line
        if (isSafe(row, colCount))
            safeReports++;

        free(row);
        row = NULL;
    }

    printf("%d\n", safeReports);

    return 0;
}
