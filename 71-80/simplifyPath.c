//
// Created by zzt on 11/18/16.
//



#include <string.h>
#include <stdio.h>

typedef struct {
    const char *s;
    int len;
} string;

void check_dir(const char *path, string *stack, int new_slash, int *sp, int *old_slash);

static char simple_path[1024] = {0};


static
char *simplifyPath(char *path) {
    string stack[128];
    int sp = 0;

    int old_slash = 0;
    int i = 1; // skip first slash
    while (path[i] != '\0') {
        if (path[i] == '/') {
            check_dir(path, stack, i, &sp, &old_slash);
        }
        i++;
    }
    if (i != old_slash + 1) {
        check_dir(path, stack, i, &sp, &old_slash);
    }
    int len = 0;
    for (int j = 0; j < sp; ++j) {
        simple_path[len++] = '/';
        for (int l = 0; l < stack[j].len; ++l) {
            simple_path[len++] = stack[j].s[l];
        }
    }
    if (sp == 0) {
        simple_path[len++] = '/';
    }
    simple_path[len] = '\0';
    return simple_path;
}

void check_dir(const char *path, string *stack, int new_slash, int *sp, int *old_slash) {
    printf("%d %d %d\n", new_slash, *old_slash, *sp);
    const char *dir = path + *old_slash + 1;
    int dir_len = new_slash - *old_slash - 1;
    if (dir_len == 0) {
    } else if (dir_len == 1 && strncmp(".", dir, dir_len) == 0) {
        // just skip
    } else if (dir_len == 2 && strncmp("..", dir, dir_len) == 0) {
        if ((*sp) != 0) {
            (*sp)--;
        }
    } else {
        string s = {dir, dir_len};
        stack[(*sp)++] = s;

    }
    (*old_slash) = new_slash;
};
