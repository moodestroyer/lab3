#include <stdio.h>
#include <employee.h>

struct {
	char name[50];
	char profession[60];
	int age;
	int expInYears;
} typedef Employee;

struct {
	int length;
	Employee * items;
}typedef EmpList;

Employee NewEmp(char* name, char* prof, int age, int exp) {
	Employee newemp;
	strcpy(newemp.name, name);
	strcpy(newemp.profession, prof);
	newemp.age = age;
	newemp.expInYears = exp;
	return newemp;
}

EmpList * CreateList() {
	EmpList list = {
		0,
		NULL
	};
	printf("CREATE");
	return &list;
}
void ListAdd(EmpList * list, Employee emp) {
	if (list == NULL) {
		return;
	}
	if (list->items == NULL || list->length == 0) {
		list->items = malloc(sizeof(Employee));
		*list->items = emp;
		list->length++;
	}
	else
	{
		list->length++;
		Employee * newloc = realloc(list->items, list->length * sizeof(Employee));
		if (newloc != NULL) {
			list->items = newloc;
			*(list->items + (list->length - 1)) = emp;
		}
		else
		{
			newloc = calloc(list->length, sizeof(Employee));
			memcpy(newloc, list->items, (list->length - 1) * sizeof(Employee));
			*(newloc + (list->length - 1)) = emp;
			free(list->items);
			list->items = newloc;
		}
	}
}

int ListPop(EmpList * list) {
	if (list->length == 0) {
		return 0;
	}
	list->length--;
	list->items = realloc(list->items, list->length * sizeof(Employee));	
	return 1;
}

int ListRemoveAt(EmpList * list, int index) {
	if (list->length <= index || index < 0) {
		return 0;
	}	
	if (list->length-1 == index) {
		return ListPop(list);
	}
	memmove(list->items + index, list->items + (index + 1), list->length * sizeof(Employee));
	list->length--;
	return 1;
}

int ListReplaceAt(EmpList * list, Employee emp, int index) {
	if (list->length <= index || index < 0)
		return 0;
	*(list->items + index) = emp;
	return 1;
}

void ShowList(EmpList * list) {
	printf("LIST\n");
	for (int i = 0; i < list->length; i++) {
		printf("\n--------------------------------\n");
		printf("Name: ");
		printf((list->items + i)->name);
		printf(" ,age: %d", (list->items + i)->age);		
		printf("\nprofession: ");
		printf((list->items + i)->profession);
		printf(" ,work experience: %d years\n", (list->items + i)->expInYears);		
	}
}

Employee * ListFindByName(EmpList * list, char* name) {
	printf("LIST | search for names: %s\n", name);
	for (int i = 0; i < list->length; i++) {
		if (strstr(list->items->name, name) != NULL) {
			printf("\n--------------------------------\n");
			printf("Name: ");
			printf((list->items + i)->name);
			printf(" ,age: %d", (list->items + i)->age);
			printf("\nprofession: ");
			printf((list->items + i)->profession);
			printf(" ,work experience: %d years\n", (list->items + i)->expInYears);
		}
	}
}

Employee * ListFindByAge(EmpList * list, int age) {
	printf("LIST | search for age: %s\n", age);
	for (int i = 0; i < list->length; i++) {
		if (list->items->age == age) {
			printf("\n--------------------------------\n");
			printf("Name: ");
			printf((list->items + i)->name);
			printf(" ,age: %d", (list->items + i)->age);
			printf("\nprofession: ");
			printf((list->items + i)->profession);
			printf(" ,work experience: %d years\n", (list->items + i)->expInYears);
		}
	}
}


Employee * ListFindByProf(EmpList * list, char* profession) {
	printf("LIST | search for profession: %s\n", profession);
	for (int i = 0; i < list->length; i++) {
		if (strstr(list->items->profession, profession) != NULL) {
			printf("\n--------------------------------\n");
			printf("Name: ");
			printf((list->items + i)->name);
			printf(" ,age: %d", (list->items + i)->age);
			printf("\nprofession: ");
			printf((list->items + i)->profession);
			printf(" ,work experience: %d years\n", (list->items + i)->expInYears);
		}
	}
}


Employee * ListFindByExp(EmpList* list, int exp) {
	printf("LIST | search for age: %s\n", exp);
	for (int i = 0; i < list->length; i++) {
		if (list->items->expInYears == exp) {
			printf("\n--------------------------------\n");
			printf("Name: ");
			printf((list->items + i)->name);
			printf(" ,age: %d", (list->items + i)->age);
			printf("\nprofession: ");
			printf((list->items + i)->profession);
			printf(" ,work experience: %d years\n", (list->items + i)->expInYears);
		}
	}
}