#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

int main(void) {
    char *input = NULL;
    size_t size = 0;
    int totalMul = 0;

    while (getline(&input, &size, stdin) != -1) {

        const char *pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";
        regex_t regex;
        regmatch_t matches[3];

        if (regcomp(&regex, pattern, REG_EXTENDED)) {
            printf("Error compiling regex\n");
            free(input);
            return 1;
        }

        const char *curr = input;
        while (regexec(&regex, curr, 3, matches, 0) == 0) {
            char x_str[matches[1].rm_eo - matches[1].rm_so + 1];
            char y_str[matches[2].rm_eo - matches[2].rm_so + 1];

            strncpy(x_str, curr + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
            int x = atoi(x_str);

            strncpy(y_str, curr + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
            int y = atoi(y_str);

            totalMul += x * y;

            curr += matches[0].rm_eo;
        }

        regfree(&regex);
    }

    printf("%d\n", totalMul);

    free(input);
    return 0;
}
