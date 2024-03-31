#include "list.h"


int size_memory_for_malloc = 40;

int main(int argc, char** argv) {

    struct List l;
    InitList(&l);
    
    //Reading

    FILE* ptr;
    ptr = fopen("test.txt", "r");

    if (!ptr) {

        printf("Don`t find file");
        exit(1);

    }

    struct Node person;
    person.second_name = (char*) malloc(size_memory_for_malloc);
    if (person.second_name == NULL) {
        exit(-1);
    }

    person.initials = (char*) malloc(size_memory_for_malloc);
    if (person.initials == NULL) {
        exit(-1);
    }

    while(fscanf(ptr,"%s %s %c %d %d %d %c", person.second_name, person.initials, &person.gender, &person.russian, &person.english, &person.mathematics, &person.group) != EOF) {

        PushBack(&l, person.second_name, person.initials, person.gender, person.russian, person.english, person.mathematics, person.group);
        person.second_name = (char*) malloc(size_memory_for_malloc);
        if (person.second_name == NULL) {
            exit(-1);
        }
        person.initials = (char*) malloc(size_memory_for_malloc);
        if (person.initials == NULL) {
            exit(-1);
        }

    }


    printf("All list:\n");
    printf("\n");
    Print(&l);

    printf("\nFemale students of group p with only one 5:\n");
    printf("\n");
    Func(&l);

    free(person.second_name);
    free(person.initials);
    FreeList(&l);

    fclose(ptr);

}
