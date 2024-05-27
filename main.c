#include "list.h"
#include <string.h>

static const char DELIMITERS[] = " \r\t\n";

int main() {
	fputs("Print 'help' for all commands\n", stdout);
    bool running = true;
    char* line = NULL;
    size_t len = 0;
    List* new_list = NULL;
    while (running) {
        fputs("> ", stdout);
        // сначала считываем 0 элементов новой строки чтоб понять, а не является ли она вообще концом ввода
        ssize_t read = getline(&line, &len, stdin);

        if (read == EOF) {
            fputc('\n', stdout);
            break;
        }

        char* ptr = NULL;
        // strtok_r - продолжает считывать текущую строку вплось до разделителей DELIMETERS
        // ptr помогает обрабатывать эту же строку
        // action - строка с командой, которую мы вводим
		char* action = strtok_r(line, DELIMITERS, &ptr);
	// strncpm - сравнивает первые n символов 1 и 2 строки. Если = 0, то строки идентичны
        if (strncmp(action, "help", 4) == 0) {
        	// fputs выводит сообщение, обычно в файл, но у нас это поток вывода, терминал (stdout)
            fputs("create\t\tCreate empty linked list\n" //Создать пустой связанный список
            "help\t\tprint this help message\n" //распечатать типо справочное сообщение
            "size\t\tget list size\n" //получить размер списка
            "insert-f <value>\t\tinsert value to front\n" //вставить значение вперед
            "insert-b <value>\t\tinsert value to back\n" //вставить значение назад
            "remove-f\t\tremove the front element\n" //убрать передний элемент
            "remove-b\t\tremove the last element\n" //удалить последний элемент
            "clear\t\tlist becomes empty\n" //список станоquitвится пустым
            "quit\t\tend this program\n" //выйти из программы
            "print\t\tprint the whole list\n" //вывести весь список
            "first\t\tprint first element\n" //печать первого элемента
            "last\t\tprint last element\n" //печать последнего элемента
            "copy <k>\t\tcopy k last elements to front\n", stdout); //скопировать k последних элементов вперед
        } else if (strncmp(action, "create", 6) == 0) {
            if (new_list != NULL) {
                ListDestroy(&new_list);
            }
            new_list = ListCreate();
        } else if (strncmp(action, "size", 4) == 0) {
            fprintf(stdout, "size = %d\n", ListSize(new_list));
        } else if (strncmp(action, "insert-f", 8) == 0) {
            char* val_str = strtok_r(NULL, DELIMITERS, &ptr);
            double value;
            sscanf(val_str, "%lf", &value);
            ListInsertFront(new_list, value);
        } else if (strncmp(action, "insert-b", 8) == 0) {
            char* val_str = strtok_r(NULL, DELIMITERS, &ptr);
            double value;
            sscanf(val_str, "%lf", &value);
            ListInsertBack(new_list, value);
        } else if (strncmp(action, "clear", 5) == 0) {
            ListClear(new_list);
        } else if (strncmp(action, "quit", 4) == 0) {
            ListDestroy(&new_list);
            running = false;
        } else if (strncmp(action, "print", 5) == 0) {
            ListPrint(new_list);
        } else if (strncmp(action, "first", 5) == 0) {
            ListIterator first_val = ListBegin(new_list);
            if ((first_val.current) && (first_val.list)) {
                fprintf(stdout, "first value = %lf\n", ListIteratorData(first_val));
            }
        } else if (strncmp(action, "last", 4) == 0) {
            ListIterator last_val = ListLast(new_list);
            if ((last_val.current) && (last_val.list)) {
                fprintf(stdout, "last value = %lf\n", ListIteratorData(last_val));
            }
        } else if (strncmp(action, "remove-f", 8) == 0) {
            ListRemoveFront(new_list);
        } else if (strncmp(action, "remove-b", 8) == 0) {
            ListRemoveBack(new_list);
        } else if (strncmp(action, "copy", 4) == 0) {
            char* k_str = strtok_r(NULL, DELIMITERS, &ptr);
            int k = atoi(k_str);
            CopyLastToFront(new_list, k);
            //free(k_str);
        } else {
            continue;
        }
	// подготовка к чтению новой команды
        free(line);
        line = NULL;
    }
	return 0;
}
