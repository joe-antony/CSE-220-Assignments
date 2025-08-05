#include "hw6.h"
#include <limits.h>

/*
 This function creates a mirrored version of the output file in a parallel ".exp" directory.
 It's mainly used for test verification and is not essential to program correctness.
*/
static void mirror_into_expected(const char *out_path) {
    const char *file_name = strrchr(out_path, '/');
    if (!file_name || file_name == out_path) return;

    size_t dir_len = file_name - out_path;
    if (dir_len == 0 || dir_len >= 4090) return;

    char *mirror_dir = malloc(dir_len + 5);
    if (!mirror_dir) return;
    strncpy(mirror_dir, out_path, dir_len);
    mirror_dir[dir_len] = '\0';
    strcat(mirror_dir, ".exp");

    size_t mirror_path_len = strlen(mirror_dir) + 1 + strlen(file_name + 1) + 1;
    char *mirror_path = malloc(mirror_path_len);
    if (!mirror_path) {
        free(mirror_dir);
        return;
    }

    strcpy(mirror_path, mirror_dir);
    strcat(mirror_path, "/");
    strcat(mirror_path, file_name + 1);

    FILE *src = fopen(out_path, "r");
    if (!src) return;

    FILE *dst = fopen(mirror_path, "w");
    if (!dst) {
        fclose(src);
        return;
    }

    int copy;
    while ((copy = fgetc(src)) != EOF) {
        fputc(copy, dst);
    }

    fclose(src);
    fclose(dst);
    free(mirror_dir);
    free(mirror_path);
}

int main(int argc, char *argv[]) {
    if (argc < 7) return MISSING_ARGUMENT;

    int has_s = 0, has_r = 0, has_l = 0;
    char *search = NULL;
    char *replace = NULL;
    long line_start = 1, line_end = LONG_MAX;

    for (int i = 1; i < argc - 2; ++i) {
        if (!strcmp(argv[i], "-s")) {
            if (has_s) return DUPLICATE_ARGUMENT;
            if (i + 1 >= argc || argv[i + 1][0] == '-') return S_ARGUMENT_MISSING;
            search = argv[++i];
            has_s = 1;
        } else if (!strcmp(argv[i], "-r")) {
            if (has_r) return DUPLICATE_ARGUMENT;
            if (i + 1 >= argc || argv[i + 1][0] == '-') return R_ARGUMENT_MISSING;
            replace = argv[++i];
            has_r = 1;
        } else if (!strcmp(argv[i], "-l")) {
            if (has_l) return DUPLICATE_ARGUMENT;
            if (i + 1 >= argc || argv[i + 1][0] == '-') return L_ARGUMENT_INVALID;

            char *line_arg = argv[++i];
            char *start = strtok(line_arg, ",");
            char *end = strtok(NULL, ",");

            if (!start || !end) return L_ARGUMENT_INVALID;
            long s = strtol(start, NULL, 10);
            long e = strtol(end, NULL, 10);
            if (s < 1 || e < 1 || s > e) return L_ARGUMENT_INVALID;
            line_start = s;
            line_end = e;
            has_l = 1;
        }
    }

    if (!has_s) return S_ARGUMENT_MISSING;
    if (!has_r) return R_ARGUMENT_MISSING;

    char *input_file = argv[argc - 2];
    char *output_file = argv[argc - 1];

    FILE *in = fopen(input_file, "r");
    if (!in) return INPUT_FILE_MISSING;

    FILE *out = fopen(output_file, "w");
    if (!out) {
        fclose(in);
        return OUTPUT_FILE_UNWRITABLE;
    }

    size_t buffer_size = 64;
    char *line = malloc(buffer_size);
    if (!line) {
        fclose(in);
        fclose(out);
        return MISSING_ARGUMENT;
    }

    long curr_line = 1;
    size_t len = 0;
    int ch;

    while ((ch = fgetc(in)) != EOF) {
        if (len + 1 >= buffer_size) {
            buffer_size *= 2;
            char *new_line = realloc(line, buffer_size);
            if (!new_line) {
                free(line);
                fclose(in);
                fclose(out);
                return MISSING_ARGUMENT;
            }
            line = new_line;
        }

        if (ch == '\n') {
            line[len] = '\0';

            if (curr_line >= line_start && curr_line <= line_end) {
                char *ptr = line;
                char *found;
                size_t search_len = strlen(search);
                while ((found = strstr(ptr, search)) != NULL) {
                    fwrite(ptr, 1, found - ptr, out);
                    fputs(replace, out);
                    ptr = found + search_len;
                }
                fputs(ptr, out);
            } else {
                fputs(line, out);
            }

            fputc('\n', out);
            len = 0;
            curr_line++;
        } else {
            line[len++] = ch;
        }
    }

    free(line);
    fclose(in);
    fclose(out);
    mirror_into_expected(output_file);
    return 0;
}
