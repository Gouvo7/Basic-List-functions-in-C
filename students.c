#include <stdio.h>
#include <stdlib.h>
#include "students.h"

void Init (struct List *MyList)
{
	MyList->head = NULL;
}

struct student *Search (struct List L, char elemAM[20], struct student **prevN)
{
	struct student *tmp;
	tmp = L.head;
	*prevN = NULL;
	while (tmp != NULL && (compare(tmp->am,elemAM) < 0))
	{
		*prevN = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL && (compare(tmp->am, elemAM) == 0 ) && strcmp(tmp->am,elemAM) == 0)
	{
		return tmp;
	}
	return NULL;
}


void Traverse(struct List L, int (*Func)(struct student*, struct student), struct student findS)
{
	struct student *tmp;
	tmp = L.head;
	struct  student tmp1;
	tmp1 = findS;
	int i = 0;
	while (tmp != NULL)
	{
		i = i + Func (tmp,tmp1);
		tmp = tmp->next;
	}
	if (i == 0)
		printf("No results were found.\n");
}

int Insert (struct List *L, struct student newStudent)
{
	struct student *tmp1, *tmp2;
	char tmpam[20];
	tmp1 = Search (*L, newStudent.am, &tmp2);
	if (tmp1) // tmp1 returns the ID value that has been found in the list or NULL if the value does not exist.
	{ 
		printf("Exists!\n");
		return 0;
	}	
	tmp1 = (struct student *) malloc (sizeof(struct student));
	*tmp1 = newStudent;
	if (tmp2 == NULL) 	// This means that the we will edit the first node either because there is no node in the list 
						// or the new node has to go in the place of the first node (change the List Head).
	{
		if (L->head == NULL) // This means that there is no node inside the list so we must enter the first node.
		{ 
			tmp1->next = NULL;
			L->head = tmp1;
			tmp1->prev = NULL;
		}
		else // In this case, we change the head and replace it with the new node.
		{
			tmp2 = L->head;
			L->head = tmp1;
			tmp1->prev = NULL;
			tmp1->next = tmp2;
			tmp2->prev = tmp1;
		}
	}
	else 	// If tmp2 has a value, that means that we either enter this value as the last value in the list or 
			// or somewhere in the middle
	{
		tmp1->next = tmp2->next;
		tmp2->next = tmp1;
		tmp1->prev = tmp2;
	}
	return 1;
}

int Delete (struct List *L, char delAM[20])
{
	struct student *tmp1, *tmp2;
	tmp1 = Search (*L, delAM, &tmp2);
	if (tmp1)
	{
		if (tmp1->next != NULL && tmp2 != NULL)
		{
			printf("Deleting middle node\n");
			tmp1->next->prev = tmp2;
			tmp2->next = tmp1->next;	
		}
		else
		{
			if (tmp1->prev == NULL)
			{
				printf("Deleting first node\n");
				if (tmp1->next)
				{
					L->head = tmp1->next;
					tmp1->next->prev = NULL;	
				}
				else
				{				
					L->head = NULL;
				}
			}
			else
			{
				printf("Deleting last node\n");
				tmp2->next = NULL;
			}
		}
		return 1;
	}
	else
	{
		printf("Doesn't Exist.\n");
		return 0;
	}
}
