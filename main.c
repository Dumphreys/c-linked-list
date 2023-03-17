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
	current->next->payload = val;
	current->next->next = NULL;
}

void *list_pop(struct list_node *head)
{
	/* removes the final element in the list and returns it */

	struct list_node *current = head;

	while (current->next->next != NULL) {
		current = current->next;
	}

	void *val = current->next->payload;

	free(current->next);

	current->next = NULL;

	return val;
}

void list_iter(struct list_node *head, void (*func)(int, void *))
{
	/* iterate through every element in the list, performing (func) on it. (int)
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
	/* inset an item into the list at index 'index' */

	struct list_node *current = head;

	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	struct list_node *newnode = malloc(sizeof(struct list_node));
	newnode->payload = current->payload;
	newnode->next = current->next;

	current->next = newnode;
	current->payload = val;
}

void *list_remove(struct list_node *head, int index)
{
	/* remove item from the list with index 'index', and returns it */

	struct list_node *current = head;

	for (int i = 0; i < index - 1; i++) {
		current = current->next;
	}

	struct list_node *tmpnext = current->next->next;
	void *payload = current->next->payload;

	free(current->next);
	current->next = tmpnext;

	return payload;
}

void list_free(struct list_node *head)
{
	/* free up all elements in the list */

	struct list_node *current = head;

	while (current != NULL) {
		struct list_node *tmp = current->next;
		free(current);
		current = tmp;
	}
}

void *list_get(struct list_node *head, int index)
{
	/* return the payload of the element in the list at index 'index' */

	struct list_node *current = head;

	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	return current->payload;
}

struct list_node *list_init(void *headvalue)
{
	struct list_node *head = malloc(sizeof(struct list_node));

	head->payload = headvalue;
	head->next = NULL;

	return head;
}

void print(int i, void *item)
{
	printf("%d: %s\n", i, item);
}

int main(int argc, char *argv[])
{
	/* demo program */
	
	struct list_node *head = list_init("goodbye");

	list_append(head, "hello");
	list_append(head, "i");
	list_append(head, "really");
	list_append(head, "love");
	list_append(head, "you");

	list_iter(head, (*print));
	printf("%s\n", list_get(head, 5));

	list_free(head);
}