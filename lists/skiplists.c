/* Author : Manish Katiyar <mkatiyar@gmail.com>
 *
 * Simple skip list implementation with a maxlevel of 3. Each
 * node can hold an integer value.
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXLVL 3

/* Each List node */
typedef struct node {
	int val;
	struct node *next[MAXLVL];
} node;

/* Begining of the list node */
typedef struct skiplist {
	int level;
	struct node *header;
} skiplist;

/* Our global skip list */
skiplist glist;
skiplist *glistP = &glist;

/* Initialize the global skiplist */
void list_init()
{
	node *dummy = malloc(sizeof(node));
	glistP->header = dummy;
	dummy->val = INT_MAX;

	for (int i = 0; i < MAXLVL; i++) {
		dummy->next[i] = glistP->header;
	}
}

/* Insert a node in skiplist. Find a random
 * level to insert to and then update all the
 * levels below that selected level.
 */
void insert(int value)
{
	node *update[MAXLVL];
	node *x = glistP->header;

	for (int i = glistP->level; i >= 0; i--) {
		while (x->next[i]->val < value) {
			x = x->next[i];
		}
		update[i] = x;
	}

	node *tmp = malloc(sizeof(node));
	tmp->val = value;

	int lvl = rand() % MAXLVL;

	if (lvl > glistP->level) {
		for (int i = glistP->level + 1; i <= lvl; i++) {
			update[i] = glistP->header->next[i];
		}
		glistP->level = lvl;
	}

	for (int i = 0; i <= lvl ;i++) {
		x = update[i];
		tmp->next[i] = x->next[i];
		x->next[i] = tmp;
	}
}

/* Print the global list */
void print_list()
{
	int i;
	node *x;

	for (i = glistP->level; i >= 0; i--) {
		x = glistP->header->next[i];
		printf("[LEVEL %d] : ", i);
		while (x != glistP->header) {
			printf("%d ", x->val);
			x = x->next[i];
			if (x != glistP->header) {
				printf(" => ");
			}
		}
		printf("\n");
	}
}

/* Search a node in skip list */
void search(int val)
{
	node *x = glistP->header;

	printf("Tracing path : ");
	for (int i = glistP->level; i >= 0; i--) {
		while (x->next[i]->val <= val) {
			x = x->next[i];
			printf("%d => ", x->val);
		}
	}

	if (x->val == val) {
		printf(" : NODE FOUND !!\n");
		return;
	}

	printf("%d ", x->next[0]->val);

	if (x->next[0]->val == val) {
		printf(" : NODE FOUND !!\n");
	} else {
		printf(" : NODE NOT FOUND !!\n");
	}
}

/* Delete a node from skip list */
void delete(int val)
{
	node *update[MAXLVL];
	node *x = glistP->header;
	int i;

	for (i = glistP->level; i >= 0 ; i--) {
		while (x->next[i]->val < val) {
			x = x->next[i];
		}
		update[i] = x;
	}

	x = update[0]->next[0];

	if (x->val != val) {
		return;
	}

	for (i = 0; i <= glistP->level; i++) {
		if (x != update[i]->next[i]) break;
		update[i]->next[i] = x->next[i];
	}

	while (glistP->level > 0 &&
	       glistP->header->next[glistP->level] == glistP->header) {
		glistP->level--;
	}

	free(x);
}

int main() {
	int n;

	list_init();

	printf("\nEnter elements of list. -1 to finish : \n");
	while (1) {
		scanf("%d", &n);
		if (n != -1) {
			insert(n);
		} else {
			break;
		}
	}

	printf("\nCurrent list elements are : \n");
	print_list();

	printf("\nSearch elements in list. -1 to finish : \n");
	while (1) {
		scanf("%d", &n);
		if (n != -1) {
			search(n);
		} else {
			break;
		}
	}

	printf("\nDelete elements from list. -1 to finish : \n");
	while (1) {
		scanf("%d", &n);
		if (n != -1) {
			delete(n);
			print_list();
		} else {
			break;
		}
	}
}
