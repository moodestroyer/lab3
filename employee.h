struct {
	char name[50];
	char profession[60];
	int age;
	int expInYears;
} typedef Employee;

struct {
	int length;
	Employee* items;
}typedef EmpList;

Employee NewEmp(char* name, char* prof, int age, int exp);

EmpList * CreateList();

void ListAdd(EmpList * list, Employee emp);

int ListPop(EmpList * list);

int ListRemoveAt(EmpList * list, int index);

int ListReplaceAt(EmpList * list, Employee emp, int index);

void ShowList(EmpList * list);

Employee* ListFindByName(EmpList * list, char* name);

Employee* ListFindByAge(EmpList * list, int age);

Employee* ListFindByProf(EmpList * list, char* profession);

Employee* ListFindByExp(EmpList * list, int exp);