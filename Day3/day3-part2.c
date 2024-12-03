#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

int main(void) {
    char *input = NULL;
    size_t size = 0;
    int totalMul = 0;
    int enableMul = 1;

    while (getline(&input, &size, stdin) != -1) {

        const char *mulPattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";
        regex_t regex;
        regmatch_t matches[3];

        const char *dontPattern = "don't\\(\\)";
        regex_t dontRegex;
        regmatch_t dontMatches[1];

        const char *doPattern = "do\\(\\)";
        regex_t doRegex;
        regmatch_t doMatches[1];

        if (regcomp(&regex, mulPattern, REG_EXTENDED)) {
            printf("Error compiling regex\n");
            regfree(&regex);
            regfree(&dontRegex);
            regfree(&doRegex);
            free(input);
            return 1;
        }

        if (regcomp(&dontRegex, dontPattern, REG_EXTENDED)) {
            printf("Error compiling regex\n");
            regfree(&regex);
            regfree(&dontRegex);
            regfree(&doRegex);
            free(input);
            return 1;
        }

        if (regcomp(&doRegex, doPattern, REG_EXTENDED)) {
            printf("Error compiling regex\n");
            regfree(&regex);
            regfree(&dontRegex);
            regfree(&doRegex);
            free(input);
            return 1;
        }

        const char *curr = input;
        while (regexec(&regex, curr, 3, matches, 0) == 0) {
            size_t searchLength = matches[0].rm_so;
            char searchArea[searchLength];
            strncpy(searchArea, curr, searchLength);

            if (regexec(&dontRegex, searchArea, 1, dontMatches, 0) == 0)
                enableMul = 0;

            if (regexec(&doRegex, searchArea, 1, doMatches, 0) == 0)
                enableMul = 1;

            if (enableMul) {
                char x_str[matches[1].rm_eo - matches[1].rm_so + 1];
                char y_str[matches[2].rm_eo - matches[2].rm_so + 1];

                strncpy(x_str, curr + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
                int x = atoi(x_str);

                strncpy(y_str, curr + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
                int y = atoi(y_str);

                totalMul += x * y;
            }

            curr += matches[0].rm_eo;
        }

        regfree(&regex);
        regfree(&dontRegex);
        regfree(&doRegex);
    }

    printf("%d\n", totalMul);

    free(input);
    return 0;
}
