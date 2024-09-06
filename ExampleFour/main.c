#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_TAG_SIZE 100

typedef struct {
    char tags[MAX_STACK_SIZE][MAX_TAG_SIZE];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

void push(Stack *stack, char *tag) {
    if (stack->top < MAX_STACK_SIZE - 1) {
        strcpy(stack->tags[++stack->top], tag);
    }
}

char *pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->tags[stack->top--];
    }
    return NULL;
}

void check_html(char *html_code) {
    Stack stack;
    initStack(&stack);
    int i = 0;
    int contains_html = 0;
    while (html_code[i] != '\0') {
        if (html_code[i] == '<') {
            int j = i + 1;
            while (html_code[j] != '>' && html_code[j] != '\0') {
                j++;
            }
            if (html_code[j] == '\0') {
                printf("error: missing '>'\n");
                return;
            }
            char tag[MAX_TAG_SIZE];
            strncpy(tag, html_code + i + 1, j - i - 1);
            tag[j - i - 1] = '\0';
            if (tag[0] == '/') {
                if (stack.top < 0) {
                    printf("error <%s>\n", tag);
                    return;
                }
                char *top_tag = pop(&stack);
                if (strcmp(top_tag, tag + 1) != 0) {
                    printf("error <%s>\n", top_tag);
                    return;
                }
            } else {
                push(&stack, tag);
            }
            i = j + 1;
            contains_html = 1;
        } else {
            i++;
        }
    }
    if (!contains_html) {
        printf("error: no HTML tags found\n");
        return;
    }

    if (stack.top >= 0) {
        printf("error <%s>\n", stack.tags[stack.top]);
    } else {
        printf("correct\n");
    }
}

int main() {
    char html_code[1000];
    fgets(html_code, sizeof(html_code), stdin);
    html_code[strcspn(html_code, "\n")] = 0;
    check_html(html_code);
    return 0;
}

