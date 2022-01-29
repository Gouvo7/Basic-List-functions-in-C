#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"

int compare (char *, char *);
int SearchID (struct student *, struct student);
int SearchName (struct student *, struct student);
int ChangeAm (struct student *, struct student);
int ChangeName (struct student *, struct student);
int ChangeSem (struct student*, struct student);
void CreateL(struct List, int );
void print(struct List );
void printSem(struct List , int);


int main(int argc, char *argv[]) {
	printf("Welcome to the PADA students list program. Please choose one of the following options:");
	struct List MyList;
	struct student *tmp1, *tmp2, *tmp3,*tmp4;
	Init (&MyList);
	while (1){
		printf("Choose one of the following:\n1)Enter a student.\t\t\t\t\t2)Delete a student.\n"
		"3)Search a student with his/her ID.\t\t\t4)Search a student with his/her name.\n5)Change the credentials of a student.\t\t\t"
		"6)Create a new list with students of a given semester.\n7)Show all students.\t\t\t\t\t8)Show all students from a given semester.\n"
		"9)Clear screen.\t\t\t\t\t\t0)Exit program.\nPlease type your answer:");
		int a;
		scanf("%d",&a);
		switch (a){
			case 1:;
				char amt[20];
				char namet[40];
				int semt;
				struct student *s, *stmp;			
				s = (struct student*) malloc (sizeof(struct student));
				printf("\nPlease type the ID:");
				scanf("%s",amt);
				printf("\nPlease type the name:");
				getchar();
				gets(namet);
				printf("\nPlease type the semester:");
				scanf("%d", &semt);
				strcpy(s->am,amt);
				strcpy(s->name,namet);
				s->sem = semt;
				s->next = NULL;
				int t = Insert(&MyList,s);		
				if (t==1)
					printf("Insertion Done!\n");
				else
					printf("Could not insert student.\n");
				break;
			case 2:;
				printf("\nPlease type the ID of the student you want to delete:");
				char del[20];
				scanf("%s",del);
				int ans = Delete(&MyList,del);
				if (ans == 1)
					printf("Student deleted succesfully.\n");
				else
					printf("Couldn't delete student.\n");
				break;
			case 3:;
				printf("\nPlease type the ID of the student you want to search for: ");
				char tempID[20];
				scanf("%s", tempID);
				struct student t1;
				strcpy(t1.am,tempID);
				Traverse(MyList,SearchID,t1);
				break;
			case 4:;
				printf("\nPlease type the name of the student you want to search for: ");
				char tempname[40];
				getchar();
				gets(tempname);
				struct student t2;
				strcpy(t2.name,tempname);
				Traverse(MyList,SearchName,t2);
				break;				
			case 5:;
				printf("\nPlease type the ID of the student whose credentials you want to change: ");
				char cID[20];
				scanf("%s", cID);
				struct student t4;
				struct student *t5, *t6;
				t5 = (struct student*) malloc (sizeof(struct student));
				t6 = (struct student*) malloc (sizeof(struct student));
				t5 = Search(MyList,cID,&t6);
				if (t5 == NULL)
				{
					printf("There were no results for ID = %s.\n",cID);
				}
				else
				{
					char oldName[40];
					strcpy(oldName,t5->name);
					int oldSem = t5->sem;
					printf("Great. Now, please select one of the following options:\n1)Change is ID/AM.\n"
					"2)Change is name.\n3)Change his semster.\nPlease select from 1-3 or anything else to cancel the operation: ");
					int tans;
					scanf("%d",&tans);
					if (tans == 1)
					{
						printf("\nPlease type the new ID/Am of the student: ");
						char newAm[20];
						scanf("%s", newAm);
						t5 = NULL;
						t6 = NULL;
						t5 = Search(MyList,newAm,&t6);
						if (t5)
						{
							printf("Could not change ID/Am of the student. The new am already exists in the list.\n");
						}
						else
						{
							int ansd = Delete(&MyList,cID);
							if (ansd == 1)
							{
								struct student *t7;
								t7 = (struct student*) malloc (sizeof(struct student));
								strcpy(t7->am,newAm);
								strcpy(t7->name,oldName);
								t7->sem = oldSem;
								t7->next = NULL; 
								int ansi = Insert(&MyList,t7);
								free(t7);
								if (ansi == 1)
								{
									printf("Change of ID/Am completed.\n");
								}
								else
									printf("Could not change the ID/Am of the student.\n");
							}
							else
							{
								printf("Could not change the ID/Am of the student.\n");
							}
						}
					}
					else if (tans == 2)
					{
						printf("\nPlease type the new name of the student: ");
						char newName[40];
						getchar();
						gets(newName);
						strcpy(t4.am,cID);
						strcpy(t4.name,newName);
						t4.sem = t5->sem;
						Traverse(MyList,ChangeName,t4);
					}
					else if (tans == 3)
					{
						printf("\nPlease type the new semester of the student: ");
						int semester;
						scanf ("%d", &semester);
						strcpy(t4.am,cID);
						strcpy(t4.name,t5->name);
						t4.sem = semester;
						Traverse(MyList,ChangeSem,t4); 
					}
					else
					{
						break;
					}
				}
				break;
			case 6:;
				printf("\nPlease type the number of the semester to create a new list: ");
				int seme;
				scanf("%d",&seme);
				CreateL(MyList,seme);
				break;
			case 7:;
				print(MyList);
				break;
			case 8:;
				printf("\nPlease type the number of the semester to print the students from the same one: ");
				int semes;
				scanf("%d",&semes);
				printSem(MyList,semes);
				break;
			case 9:;
				system("cls");
				break;
			case 0:;
				return 0;		
		}
	}	
	return 0;
}

int compare (char *s1, char *s2) //  I have created a new function that compares strings, since strcmp was showing that 9 > 10.
{
	char am1[20];
	char am2[20]; 
	int i, y;
	int x = 0;
	int z = 0;
	for (i = 0; i < strlen(s1); i++)
	{
		if (isdigit(s1[i]))
		{
			am1[x] = s1[i];
			x++;
		}
	}
	for (y = 0; y < strlen(s2); y++)
	{
		if (isdigit(s2[y]))
		{
			am2[z] = s2[y];
			z++;
		} 		
	}
	int val1, val2;
	val1 = atoi(am1);
	val2 = atoi(am2);
	if (val1 > val2)
		return 1;
	else if (val2 > val1)
		return -1;
	else
		return 0;	
}

int SearchID (struct student *stud, struct student findS)
{
	if (strcmp(stud->am,findS.am) == 0)
	{
		printf("Student found with these credentials:\nName: %s\nAM/ID:  %s\nSemester: %d\n", stud->name, stud->am, stud->sem);
		return 1;
	}
	else
		return 0;
}

int SearchName(struct student *stud, struct student findS)
{
	if (strcmp(stud->name,findS.name) == 0)
	{
		printf("Student found with these credentials:\nName: %s\nAM/ID:  %s\nSemester: %d\n", stud->name, stud->am, stud->sem);
		return 1;
	}
	else
		return 0;	
}


int ChangeAm(struct student *stud, struct student findS)
{
	if (strcmp(stud->am,findS.am) == 0)
	{
		printf("Please type the new ID/Am of the student: ");
		return 1;
	}
	return 0;
}

int ChangeName(struct student *stud, struct student findS)
{
	if (strcmp(stud->am,findS.am) == 0)
	{
		strcpy(stud->name,findS.name);
		return 1;
	}
	else
		return 0;
}

int ChangeSem(struct student *stud, struct student findS)
{
	if (strcmp(stud->am,findS.am) == 0)
	{
		stud->sem = findS.sem;
		return 1;
	}
	else
		return 0;
}

void CreateL(struct List L, int semester) // Creating a temporary list that will store every student in the same (given by the user) semester.
{	
	struct List NL;
	Init(&NL);
	int c;
	struct student *tmp1, *tmp2;
	tmp1 = (struct student *) malloc (sizeof(struct student));
	tmp2 = (struct student *) malloc (sizeof(struct student));
	tmp1 = L.head;
	while (tmp1 != NULL){	
		if (tmp1->sem == semester)
		{
			Insert(&NL,tmp1);
			c = c + 1;
		}
		tmp1 = tmp1->next;
	}
	if (c!=0)
		print(NL);
	else
		printf("No results were found for semester no %d", semester);
}

void print(struct List L)
{
	struct student *tmp;
	tmp = L.head;
	while (tmp!=NULL)
	{
		printf("%s, %s, %d\n", tmp->am, tmp->name, tmp->sem);
		tmp = tmp->next;
	}
}

void printSem(struct List L, int ans)
{
	struct student *tmp;
	tmp = L.head;
	printf("The student that are currently in semester no. %d are:\n",ans);
	while(tmp!=NULL)
	{
		if (tmp->sem == ans)
			printf("Name: %s\nAM/ID:  %s\nSemester: %d\n", tmp->name, tmp->am, tmp->sem);
		tmp = tmp->next;
	}
}


// den pairnei eponuma
// polu megalh switch
// gia epeksergasia xreiazetai traverse?
// h diplodesmikh lista einai ok?
// sto erothma poy leei kataskevase lista me foithtes idiou sem, ftiaxnw mia kai thn tupwnw. Einai ok?
// exw ftiaksei diko mou compare gia strings epeidh h strcmp evgaze lathos apotelesmata px 9 > 10
