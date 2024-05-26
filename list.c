#include "list.h"

struct list_node {
	double value;
	struct list_node *next;
	struct list_node *prev;
};

// Список основан на динамических структурах (нодах)
struct list {
	struct list_node *head;
	struct list_node *tail;
	int32_t size;
};

List* ListCreate(void) {
	List *res = malloc(sizeof(List));
	res->head = NULL;
	res->tail = NULL;
	res->size = 0;
	return res;
}

int32_t ListSize(const List* const list) {
	if (list == NULL) {
		return 0;
	}
	return list->size;
}

ListIterator ListInsertFront(List* const list, double val) {
	ListIterator res;
	ListNode *node;
	if (list == NULL) {
		res.current = NULL;
		res.list = list;
		return res;
	}
	node = malloc(sizeof(ListNode));
	node->value = val;
	node->next = list->head;
	node->prev = NULL;
	if (list->size == 0) {
		list->tail = node;
	} else {
		list->head->prev = node;
	}
	
	list->head = node;
	res.current = node;
	res.list = list;
	list->size++;
	return res;
}

ListIterator ListInsertBack(List* const list, double val) {
	ListIterator res;
	ListNode *node;
	if (list == NULL) {
		res.current = NULL;
		res.list = list;
		return res;
	}
	node = malloc(sizeof(ListNode));
	node->value = val;
	node->next = NULL;
	node->prev = list->tail;
	if (list->size == 0) {
		list->head = node;
	} else {
		list->tail->next = node;
	}
	list->tail = node;
	res.current = node;
	res.list = list;
	list->size++;
	return res;
}


void ListDestroy(List** const list) {
	if ((*list) == NULL) {
		return;
	}
	ListClear(*list);
	free(*list);
	(*list) = NULL;
}

ListIterator ListInsertAfter(List* const list, const ListIterator iterator, double val) {
	ListNode *node;
	ListIterator res;
	if ((list == NULL) || (iterator.current == NULL) || (iterator.list != list)) {
		res.current = NULL;
		res.list = NULL;
		return res;
	}

	node = malloc(sizeof(ListNode));
	node->value = val;
	
	if (ListIteratorEqual(iterator, ListLast(list))) {
		free(node);
		return ListInsertBack(list, val);
	}
	node->next = iterator.current->next;
	node->prev = iterator.current;
	iterator.current->next->prev = node;
	iterator.current->next = node;
	
	res.current = node;
	res.list = list;
	list->size++;
	return res;
}

void ListRemoveFront(List* const list) {
	ListNode *to_delete;
	if ((list == NULL) || (ListSize(list) == 0)) {
		return;
	}

	to_delete = list->head;
	list->head = to_delete->next;
	if (ListSize(list) == 1) {
		list->tail = NULL;
	} else {
		to_delete->next->prev = NULL;
	}
	list->size--;
	free(to_delete);
}

void ListRemoveBack(List* const list) {
	ListNode *to_delete;
	if ((list == NULL) || (ListSize(list) == 0)) {
		return;
	}

	to_delete = list->tail;
	list->tail = to_delete->prev;
	if (ListSize(list) == 1) {
		list->head = NULL;
	} else {
		to_delete->prev->next = NULL;
	}
	list->size--;
	free(to_delete);
}


void ListRemoveAfter(List* const list, const ListIterator iterator) {
	ListNode *to_delete;
	if ((list == NULL) || (ListSize(list) == 0) || (iterator.current == NULL) || (iterator.list == NULL) || (list != iterator.list)) {
		return;
	}

	if (iterator.current == list->tail) {
		ListRemoveBack(list);
		return;
	}
	to_delete = iterator.current->next;
	iterator.current->next->prev = to_delete->prev;
	iterator.current->next = to_delete->next;
	list->size--;
	free(to_delete);
}

void ListClear(List* const list) {
	if (list == NULL) {
		return;
	}
	while (list->head) {
		ListRemoveFront(list);
	}
	list->head = NULL;
}

ListIterator ListBegin(const List* const list) {
	ListIterator res;
	if ((list == NULL) || (list->head == NULL)) {
		res.current = NULL;
		res.list = list;
		return res;
	}

	res.current = list->head;
	res.list = list;
	return res;
}

ListIterator ListLast(const List* const list) {
	ListIterator res;
	if ((list == NULL) || (list->tail == NULL)) {
		res.current = NULL;
		res.list = list;
		return res;
	}

	res.current = list->tail;
	res.list = list;
	return res;
}

ListIterator ListEnd(const List* const list) {
	ListIterator res;
	res.current = NULL;
	res.list = list;
	return res;
}

void ListPrint(const List* const list) {
	ListIterator it;
	int cnt = 0;
	if ((list == NULL) || (ListSize(list) == 0)) {
		printf("\n");
		return;
	}
	it = ListBegin(list);
	while ((ListIteratorEqual(it, ListEnd(list)) == false) || (cnt > ListSize(list))) {
		printf("%.2f ", it.current->value);
		ListIteratorIncrement(&it);
		cnt++;
	}
	printf("\n");
}

void* ListIteratorData(const ListIterator iterator) {
	if ((iterator.current == NULL) || (iterator.list == NULL)) {
		return NULL;
	}
	double value_iter = (iterator.current)->value;
	double *value_id = &value_iter;
	return value_id;
}

void ListIteratorIncrement(ListIterator* const iterator) {
	if ((iterator->current == NULL) || (iterator->list == NULL) || (ListSize(iterator->list) == 0)) {
		iterator->current = NULL;
		return;
	}
	iterator->current = iterator->current->next;
}

void ListIteratorDecrement(ListIterator* const iterator) {
	if ((iterator->current == NULL) || (iterator->list == NULL) || (ListSize(iterator->list) == 0)) {
		iterator->current = NULL;
		return;
	}
	iterator->current = iterator->current->prev;
}

bool ListIteratorEqual(const ListIterator lhs, const ListIterator rhs) {
	return ((lhs.list == rhs.list) && (lhs.current == rhs.current));
}

void CopyLastToFront(List* list, const int32_t k) {
	double value_to_insert;
    if ((list == NULL) || (k < 0) || (list->tail == NULL)) {
        return;
    }
    value_to_insert = ListLast(list).current->value;
    for (int32_t i = 0; i < k; i++) {
        ListInsertFront(list, value_to_insert);
    }
}
