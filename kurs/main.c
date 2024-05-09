#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "videos.h"

/*
Гига Максим = 6; theme = (6-1)/3 = 5/3 = 1; action = (6-1)%3 = 5%3 = 2
1. Табличка роликов на YouTube, поля:
Название, канал, дата (сделайте структуру с полями день, месяц год), количество
просмотров, число 8 байт
2. Выгружает все ролики имеющие количество просмотров больше либо равное чем
указанное
*/

int main(int argc, char **argw) {
    bool header = true;
    bool out_header = true;
    char sep = 0;
    char out_sep = 0;
    char *input_file = NULL;
    char *output_file = NULL;
    size_t views = 0;

    // skip first argument as it's program name
    for (int i = 1; i < argc; i++) {
        if (strcmp("--no_header", argw[i]) == 0) {
            header = false;
            continue;
        }
        if (strcmp("--out_no_header", argw[i]) == 0) {
            out_header = false;
            continue;
        }
        if (strcmp("-o", argw[i]) == 0 || strcmp("--out", argw[i]) == 0) {
            if (i + 1 == argc) {
                fprintf(stderr, "ERROR: output file must be specified\n");
                return 1;
            }
            output_file = argw[++i];
            continue;
        }
        if (strcmp("--csv", argw[i]) == 0) {
            if (i + 1 == argc) {
                fprintf(stderr, "ERROR: separator must be specified\n");
                return 1;
            }
            sep = argw[++i][0];
            if (argw[i][1]) {
                fprintf(stderr, "ERROR: separator must be a single char\n");
                return 1;
            }
            continue;
        }
        if (strcmp("--out_csv", argw[i]) == 0) {
            if (i + 1 == argc) {
                fprintf(stderr, "ERROR: separator must be specified\n");
                return 1;
            }
            out_sep = argw[++i][0];
            if (argw[i][1]) {
                fprintf(stderr, "ERROR: separator must be a single char\n");
                return 1;
            }
            continue;
        }
        if (strcmp("-v", argw[i]) == 0 || strcmp("--views", argw[i]) == 0) {
            if (i + 1 == argc) {
                fprintf(stderr, "ERROR: views value must be specified\n");
                return 1;
            }
            char *end;
            long long v = strtoll(argw[++i], &end, 10);
            if (*end) {
                fprintf(stderr, "ERROR: invalid number: %s\n", argw[i]);
                return 1;
            }
            if (v < 0) {
                fprintf(stderr, "ERROR: views value must not be negative\n");
                return 1;
            }
            views = v;
            continue;
        }
        if (strcmp("--help", argw[i]) == 0) {
            printf("Usage: %s [OPTIONS] input_file\n", argw[0]);
            printf("Options:\n");
            printf("\t--csv <sep>\tSpecify that the input file is csv "
                   "table with <sep>. If this argument is not specified, "
                   "separator will be assumed based on file extension\n");
            printf("\t--no_header\tSpecify that the input csv file has no "
                   "header\n'");
            printf("\t-o, --out\tSpecify output file. Otherwise data will be "
                   "outputed in stdout\n");
            printf("\t--out_csv <sep>\tSpecify that the output file "
                   "should be csv table with <sep>. If this argument is "
                   "not specified, separator will be assumed based on file "
                   "extension\n");
            printf("\t--out_no_header\tSpecify that the output csv file should "
                   "have no header\n'");
            printf("\t-v, --views <N>\tspecify bottom value for filtering "
                   "videos\n");
            printf("\t--help\tprint this message\n");
            return 0;
        }
        if (argw[i][0] == '-') {
            fprintf(stderr, "ERROR: unknown flag: \"%s\"\n", argw[i]);
            return 1;
        }
        if (input_file) {
            fprintf(stderr, "ERROR: input file already specified\n");
            return 1;
        }
        input_file = argw[i];
    }

    if (!input_file) {
        fprintf(stderr, "ERROR: input file must be specified\n");
        return 1;
    }

    if (!sep) {
        char *ext = strrchr(input_file, '.');
        if (ext && strcmp(ext, ".tsv") == 0)
            sep = '\t';
        else if (ext && strcmp(ext, ".csv") == 0)
            sep = ',';
    }

    if (output_file && !out_sep) {
        char *ext = strrchr(output_file, '.');
        if (ext && strcmp(ext, ".tsv") == 0)
            out_sep = '\t';
        else if (ext && strcmp(ext, ".csv") == 0)
            out_sep = ',';
    }

    VList *l = sep ? VListFReadCSV(input_file, header, sep)
                   : VListFReadBinary(input_file);
    VList *res = l;
    if (views) {
        res = VListNew();
        for (size_t i = 0; i < l->size; i++) {
            if (l->data[i].views >= views)
                VListPush(res, l->data[i]);
        }
    }
    if (output_file)
        if (out_sep)
            VListFWriteCSV(res, output_file, out_header, out_sep);
        else
            VListFWriteBinary(res, output_file);
    else
        VListPrint(res);

    if (res != l)
        VListFree(res);
    VListFree(l);
    return 0;
}
