#include <stdlib.h>
#include <stdio.h>

#define MAX 1000000

int main(void) {
    int *leftList = NULL;
    int *rigthList = NULL;
    int left, rigth;
    int count = 0;
    int auxArr[MAX + 1] = {0};

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

    for (int i = 0; i < count; i++) {
        auxArr[rigthList[i]]++;
    }

    int similarityScore = 0;

    for (int i = 0; i < count; i++) {
        int auxVar = leftList[i] * auxArr[leftList[i]];
        similarityScore += auxVar;
    }

    printf("%d\n", similarityScore);

    free(rigthList);
    free(leftList);

    return 0;
}
