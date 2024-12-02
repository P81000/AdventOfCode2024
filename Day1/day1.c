#include <stdlib.h>
#include <stdio.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(void) {
    int *leftList = NULL;
    int *rigthList = NULL;
    int left, rigth;
    int count = 0;

    while (scanf("%d %d", &left, &rigth) == 2) {
        leftList = realloc(leftList, (count + 1) * sizeof(int));
        rigthList = realloc(rigthList, (count + 1) * sizeof(int));

        if (leftList == NULL || rigthList == NULL) {
            printf("Allocation error\n");
            free(leftList);
            free(rigthList);
            return 1;
        }

        leftList[count] = left;
        rigthList[count] = rigth; 
        count++;
    }

    qsort(leftList, count, sizeof(int), compare);
    qsort(rigthList, count, sizeof(int), compare);

    int totalDist = 0;
    for (int i = 0; i < count; i++) {
        totalDist += abs(compare(&leftList[i], &rigthList[i]));
    }

    printf("%d\n", totalDist);

    free(rigthList);
    free(leftList);

    return 0;
}
