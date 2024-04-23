#include "db.h"

void WriteToBinaryFile(CommandsVARKT* arr, int length, char *fileName) {
    FILE *f = fopen(fileName, "w+");
    if (f == NULL){
        exit(-1);
    }
    fwrite(arr, sizeof(CommandsVARKT), length, f);

    fclose(f);
}

int ReadFromBinaryFile(CommandsVARKT* arr, int MaxObject, char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (f == NULL){
        exit(-1);
    }
    fread(arr, sizeof(CommandsVARKT), MaxObject, f);
    fclose(f);
}

void WriteToCsv(CommandsVARKT* arr, int length, char *fileName) {
    FILE *f = fopen(fileName, "w+");
    if (f == NULL){
        exit(-1);
    }
    for (int i = 0; i < length; i++) {
        fprintf(f, "%s %s %d %d %d %d\n", arr[i].commandName, arr[i].titleProject, arr[i].participants, arr[i].createResearchDoc, arr[i].checkReqsearchDoc, arr[i].passedProject);
    }

    fclose(f);
}


int ReadFromCsv(CommandsVARKT* arr, int MaxObject, char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (f == NULL){
        exit(-1);
    }

    for (int i = 0; i < MaxObject; i++) {
        fscanf(f, "%s %s %d %d %d %d", arr[i].commandName, arr[i].titleProject, &arr[i].participants, &arr[i].createResearchDoc, &arr[i].checkReqsearchDoc, &arr[i].passedProject);
    }
    fclose(f);
}
