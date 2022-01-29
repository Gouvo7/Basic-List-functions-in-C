#ifndef STUDENTS_H
#include <string.h>
#define STUDENTS_H

struct student
{
	char am[20];
	char name[40];
	int sem;
	struct student *prev;
	struct student *next;
};

struct List
{
	struct student *head;
};

void Init (struct List *);
struct student *Search (struct List , char[20], struct student **);



#endif
//ean uparxei, to search sto tmp1 tha gurisei thn timh pou uparxei
// ean den yparxei, tha gurisei null
