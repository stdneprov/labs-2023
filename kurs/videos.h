#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <stdbool.h>
#include <stddef.h>

/*
Табличка роликов на YouTube, поля:
Название, канал, дата (сделайте структуру с полями день, месяц год), количество
просмотров, число 8 байт
*/
typedef struct {
    char day;
    char month;
    short year;
} Date;

typedef struct {
    char channel[126];
    char title[126];
    Date date;
    unsigned long views;
} Video;

void VideoPrint(const Video *v);

typedef struct {
    Video *data;
    size_t size;
    size_t capacity;
} VList;

VList *VListFReadCSV(const char *filename, bool header, char sep);
VList *VListFReadBinary(const char *filename);
VList *VListNew(void);
VList *VListWithCapacity(size_t capacity);
void VListFWriteBinary(const VList *l, const char *filename);
void VListFWriteCSV(const VList *l, const char *filename, bool header,
                    char sep);
void VListPrint(const VList *l);
void VListPush(VList *l, const Video v);
void VListPop(VList *l);
Video *VListLast(const VList *l);
void VListFree(VList *l);

#endif //_VIDEO_H_
