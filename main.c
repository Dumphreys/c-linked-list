#include <stdio.h>
#include <stdlib.h>

/* a simple linked list */

struct list_node {
	void *payload;
	struct list_node *next;
};

void list_append(struct list_node *head, void *val)
{
	/* adds an element on to the end of the list */
	
	struct list_node *current = head;

	while (current->next != NULL) {
		current = current->next;
	}

	current->next = malloc(sizeof(struct list_node));

        if (current->next == NULL) {
                fprintf(stderr, "linked list: malloc failed - not enough memory!");
                return;
        }

	current->next->payload = val;
	current->next->next = NULL;
}

void *list_pop(struct list_node *head)
{
	/* removes the final element in the list and returns it */

	struct list_node *current = head;

        if (current->next == NULL) {
                /* disallow popping a single element list */
                return NULL;
        }

        if (current->next->next != NULL)
                while (current->next->next != NULL)
	        	current = current->next;

	void *val = current->next->payload;

	free(current->next);

	current->next = NULL;

	return val;
}

void list_iter(struct list_node *head, void (*func)(int, void *))
{
	/* iterates through every element in the list, performing (func) on it. (int)
	is the index of the element, and (void*) is the payload of that element. */

	struct list_node *current = head;

	int i = 0;

	while (current != NULL) {
		(*func)(i++, current->payload);
		current = current->next;
	}
}

void list_insert(struct list_node *head, int index, void *val)
{
	/* inserts an item into the list at index 'index'. to insert an
        item at the end, use list_append */

	struct list_node *current = head;

        for (int i = 0; i < index; i++) {
                if (current->next == NULL)
                        return;
	        current = current->next;
        }

        struct list_node *new = malloc(sizeof(struct list_node));

        if (new == NULL) {
                fprintf(stderr, "linked list: malloc failed - not enough memory!");
                return;
        }

        new->payload = current->payload;
        new->next = current->next;

        current->next = new;
        current->payload = val;
}

void *list_remove(struct list_node *head, int index)
{
	/* removes an item from the list with index 'index', and returns it */

	struct list_node *current = head;

        for (int i = 0; i < index; i++) {
                if (current->next->next == NULL)
                        return NULL;
	        current = current->next;
        }

        struct list_node *tmp = current->next->next;
        current->payload = current->next->payload;

        free(current->next);

        current->next = tmp;

        return NULL;
}

void list_free(struct list_node *head)
{
	/* frees up all elements in the list */

	struct list_node *current = head;

        if (current == NULL) {
                return;
        }

	while (current != NULL) {
		struct list_node *tmp = current->next;

		free(current);
                current->next = NULL;
		current = tmp;
	}
}

void *list_get(struct list_node *head, int index)
{
	/* returns the payload of the element in the list at index 'index' */

	struct list_node *current = head;

	for (int i = 0; i < index; i++) {
                if (current->next == NULL) {
                        return NULL;
                }
		current = current->next;
	}

	return current->payload;
}

struct list_node *list_init(void *headvalue)
{
	/* 'creates' a new list by initialising the head. */
	
	struct list_node *head = malloc(sizeof(struct list_node));

        if (head == NULL) {
                fprintf(stderr, "linked list: malloc failed - not enough memory!");
                return NULL;
        }

	head->payload = headvalue;
	head->next = NULL;

	return head;
}

void print_list_item(int i, void *item)
{
        /* an example method, only works if strings are used. */

	printf("%d: %s\n", i, item);
}

int main(int argc, char *argv[])
{
	/* demo program */
	
	struct list_node *head = list_init("item one");

        list_append(head, "item two");
        list_append(head, "item three");
        list_append(head, "item four");

        list_remove(head, 0);

        list_insert(head, 2, "inserted at 2");
        list_insert(head, 3, "inserted at 3");

        list_append(head, "appended");
        printf("Popped element: %s\n", list_pop(head));

        list_iter(head, print_list_item);

        list_free(head);
}
