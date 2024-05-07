#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "videos.h"

void VideoPrint(const Video *v) {
    printf("\"%s\": \"%s\"\n", v->channel, v->title);
    printf("\tdate: %02d/%02d/%04d\t\t%lu views\n", v->date.day, v->date.month,
           v->date.year, v->views);
}

VList *VListNew(void) {
    return VListWithCapacity(0);
}

VList *VListWithCapacity(size_t capacity) {
    VList *vlist = malloc(sizeof(VList));
    if (vlist == NULL) {
        fprintf(stderr, "ERROR: buy more ram\n");
        exit(EXIT_FAILURE);
    }
    vlist->size = 0;
    if (capacity > 0) {
        capacity = pow(2, ceil(log2(capacity)));
        vlist->capacity = capacity;
        vlist->data = malloc(capacity * sizeof(Video));
        if (vlist->data == NULL) {
            fprintf(stderr, "ERROR: buy more ram\n");
            exit(EXIT_FAILURE);
        }
    } else {
        vlist->capacity = 0;
        vlist->data = NULL;
    }
    return vlist;
}

int FReadCSVField(FILE *fp, char *buf, char sep) {
    char c;
    int i = 0;
    c = fgetc(fp);
    if (c == EOF)
        return -1;
    if (c == sep || c == '\n')
        return 0;
    if (c == '"') {
        while (true) {
            c = fgetc(fp);
            if (c == EOF) {
                fprintf(stderr, "ERROR: unclosed field\n");
                exit(EXIT_FAILURE);
            }
            if (c == '"') {
                c = fgetc(fp);
                if (c == EOF || c == sep)
                    break;
                if (c == '"') {
                    buf[i++] = '"';
                    continue;
                }
                fprintf(stderr,
                        "ERROR: single \" must be at the end of the field\n");
                exit(EXIT_FAILURE);
            }
            buf[i++] = c;
        }
    } else {
        buf[i++] = c;
        while (c = fgetc(fp), c != sep && c != '\n' && c != EOF) {
            buf[i++] = c;
        }
    }
    return i;
}

VList *VListFReadCSV(const char *filename, bool header, char sep) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    VList *l = VListNew();
    Video v = {0};

    // skip first line containing header
    char c;
    if (header) {
        while (c = fgetc(fp), c != '\n' && c != EOF)
            continue;
    }
    char buf[256] = {0};
    // format   channel     title    dd/mm/yyyy  views
    while (true) {
        // read channel
        int size = FReadCSVField(fp, buf, sep);
        if (size == EOF)
            break;
        memcpy(v.channel, buf, size);

        // read title
        size = FReadCSVField(fp, buf, sep);
        if (size > 0)
            memcpy(v.title, buf, size);

        // read date
        size = FReadCSVField(fp, buf, sep);
        buf[size] = 0;
        char *end;
        if (size > 0) {
            v.date.day = strtol(buf, &end, 10);
            if (v.date.day < 1 || v.date.day > 31) {
                fprintf(stderr, "ERROR: day must be in range [1;31]: %d\n",
                        v.date.day);
                exit(EXIT_FAILURE);
            }
            if (*end != '/') {
                fprintf(stderr, "ERROR: date must be in dd/mm/yyyy: %s\n", buf);
                exit(EXIT_FAILURE);
            }
            v.date.month = strtol(end + 1, &end, 10);
            if (v.date.month < 1 || v.date.month > 12) {
                fprintf(stderr, "ERROR: month must be in range [1;12]: %d\n",
                        v.date.month);
                exit(EXIT_FAILURE);
            }
            if (*end != '/') {
                fprintf(stderr, "ERROR: date must be in dd/mm/yyyy: %s\n", buf);
                exit(EXIT_FAILURE);
            }
            v.date.year = strtol(end + 1, &end, 10);
            // year cannot be zero; It can only occur if year is omitted
            if (*end || !v.date.year) {
                fprintf(stderr, "ERROR: year must be a number: %s\n", buf);
                exit(EXIT_FAILURE);
            }
        }

        // read view count
        size = FReadCSVField(fp, buf, sep);
        buf[size] = 0;
        // use strtoll, as views is unsigned long
        long long views = strtoll(buf, &end, 10);
        if (*end) {
            fprintf(stderr, "ERROR: invalid number: %s\n", buf);
            exit(EXIT_FAILURE);
        }
        if (views < 0) {
            fprintf(stderr, "ERROR: views value must not be negative\n");
            exit(EXIT_FAILURE);
        }
        v.views = views;
        VListPush(l, v);
        memset(&v, 0, sizeof(v));
    }

    fclose(fp);
    return l;
}

void VWriteCSVField(FILE *fp, const char *str, char sep) {
    if (strchr(str, '"')) {
        fputc('"', fp);
        for (const char *c = str; *c != 0; c++) {
            fputc(*c, fp);
            if (*c == '"')
                fputc(*c, fp);
        }
        fputc('"', fp);
    } else if (strchr(str, sep))
        fprintf(fp, "\"%s\"", str);
    else {
        fprintf(fp, "%s", str);
    }
}

void VListFWriteCSV(const VList *l, const char *filename, bool header,
                    char sep) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    if (header)
        fprintf(fp, "channel%ctitle%cdd/mm/yyyy%cviews\n", sep, sep, sep);
    for (size_t i = 0; i < l->size; i++) {
        Video v = l->data[i];
        VWriteCSVField(fp, v.channel, sep);
        fputc(sep, fp);
        VWriteCSVField(fp, v.title, sep);
        fprintf(fp, "%c%02d/%02d/%04d%c%lu\n", sep, v.date.day, v.date.month,
                v.date.year, sep, v.views);
    }
    fclose(fp);
}

VList *VListFReadBinary(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    size_t size;
    if (fread(&size, sizeof(size), 1, fp) != 1) {
        fprintf(stderr, "ERROR: failed to read list size from file: %s\n",
                filename);
        exit(EXIT_FAILURE);
    }
    VList *l = VListWithCapacity(size);
    l->size = size;
    if (fread(l->data, sizeof(Video), size, fp) != size) {
        fprintf(stderr, "ERROR: failed to read list from file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    return l;
}

void VListFWriteBinary(const VList *l, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: failed to create or open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    size_t res = fwrite(&l->size, sizeof(l->size), 1, fp);
    res += fwrite(l->data, l->size * sizeof(Video), 1, fp);
    if (res != 2) {
        fprintf(stderr, "ERROR: failed to write to file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

void VListPrint(const VList *l) {
    for (size_t i = 0; i < l->size; i++) {
        if (i > 0)
            printf("-----------------------------------------------\n");
        VideoPrint(&l->data[i]);
    }
}

void VListPush(VList *l, const Video v) {
    if (l->capacity == 0) {
        l->capacity = 1;
        l->data = malloc(l->capacity * sizeof(Video));
        if (l->data == NULL) {
            fprintf(stderr, "ERROR: buy more ram\n");
            exit(EXIT_FAILURE);
        }
    } else if (l->capacity < l->size + 1) {
        l->capacity *= 2;
        l->data = realloc(l->data, l->capacity * sizeof(Video));
        if (l->data == NULL) {
            fprintf(stderr, "ERROR: buy more ram\n");
            exit(EXIT_FAILURE);
        }
    }
    l->data[l->size++] = v;
}

void VListPop(VList *l) {
    if (l->size == 0)
        return;
    if (--l->size <= l->capacity / 4) {
        l->capacity /= 4;
        l->data = malloc(l->capacity / 4 * sizeof(Video));
        if (l->data == NULL) {
            fprintf(stderr, "ERROR: buy more ram\n");
            exit(EXIT_FAILURE);
        }
    }
}

Video *VListLast(const VList *l) {
    if (l->size > 0)
        return &l->data[l->size - 1];
    return NULL;
}

void VListFree(VList *l) {
    if (l->data)
        free(l->data);
    free(l);
}
