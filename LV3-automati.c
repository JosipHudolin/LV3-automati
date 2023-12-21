#include <stdio.h>
#include <string.h>
#include <ctype.h>

void analyzeLine(const char *line, int *identifiers, int *keywords, int *separators, int *operators, int *constants, int *comments) {
    printf("Line: %s\n", line);

    printf("Analysis:\n");

    int length = strlen(line);
    int i = 0;

    while (i < length) {
        if (isalpha(line[i])) { // Check for identifiers or keywords
            int start = i;
            int len = 0;
            char str[20] = {0};
            while (isalpha(line[i]) || isdigit(line[i]) || line[i] == '_') {
                str[len] = line[i];
                len++;
                i++;
            }
            str[len] = '\0';
            if (strcmp(str, "if") == 0 || strcmp(str, "else") == 0 || strcmp(str, "while") == 0 ||
                strcmp(str, "for") == 0 || strcmp(str, "function") == 0 || strcmp(str, "return") == 0) {
                (*keywords)++;
            } else {
                (*identifiers)++;
                printf("('%s', identificator)\n", str);
            }
        } else if (line[i] == ' ') { // Check for separators (space)
            printf("(' ', separator)\n");
            (*separators)++;
            i++;
        } else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/') { // Check for operators
            printf("('%c', operator)\n", line[i]);
            (*operators)++;
            i++;
        } else if (line[i] == '=' && line[i+1] == '=') {
            printf("('==', operator)\n");
            i = i + 2;
            (*operators)++;
        } else if (line[i] == '=') {
            printf("('=', operator)\n");
            i++;
            (*operators)++;
        } else {
            // Skip characters not processed in this basic example
            i++;
        }
    }

    printf("\n");
}

int main() {
    char line[100];
    int identifiers = 0;
    int keywords = 0;
    int separators = 0;
    int operators = 0;
    int constants = 0;
    int comments = 0;

    printf("Enter lines of code (type 'exit' to quit):\n");

    while (1) {
        printf("> ");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0; // Remove the newline character from input

        if (strcmp(line, "exit") == 0) {
            break;
        }

        analyzeLine(line, &identifiers, &keywords, &separators, &operators, &constants, &comments);
    }

    printf("Token Summary:\n");
    printf("- Identifiers: %d\n", identifiers);
    printf("- Keywords: %d\n", keywords);
    printf("- Separators: %d\n", separators);
    printf("- Operators: %d\n", operators);
    printf("- Constants: %d\n", constants);
    printf("- Comments: %d\n", comments);

    return 0;
}
