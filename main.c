#include "employee.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h> 

typedef enum { false, true } bool;

void ClearCSL();
int MainMenu();
void AddToListUI();
void ShowListUI();
void FindByNameListUI();
void FindByAgeListUI();
void FindByProfessionListUI();
void FindByExpListUI();
void ReplaceInListUI();
void DeleteFromListUI();
void LoadFromFile();
void SaveToFile();
void FreeAll();
int ReadLine(char* str, int lenght);
void removeChar(char* str, char chr);
int getch();

EmpList database;

int main() {
    database = *CreateList();   
    LoadFromFile();
    while(1){
        int choice = MainMenu();
        switch (choice)
        {
        case 1: AddToListUI(); break;
        case 2: ShowListUI(); break;
        case 3: FindByNameListUI(); break;
        case 4: FindByAgeListUI(); break;
        case 5: FindByProfessionListUI(); break;
        case 6: FindByExpListUI(); break;
        case 7: ReplaceInListUI(); break;
        case 8: DeleteFromListUI(); break;
        case 9: SaveToFile(); FreeAll(); return 0;        
        }
    }
    return 0;
}

int MainMenu() {
    int input = -1;   
    do {
        ClearCSL();
        printf("Employee database\n\n");
        printf("1 - Add to list\n");
        printf("2 - Show list\n");
        printf("3 - Find by name\n");
        printf("4 - Find by age\n");
        printf("5 - Find by profession\n");
        printf("6 - Find by work exp\n");
        printf("7 - Replace item in list\n");
        printf("8 - Delete from list\n");
        printf("9 - Exit\n");
        scanf("%d", &input);
    } while (input < 1 && input > 8);
    return input;
}

void AddToListUI() {
    ClearCSL();
    bool isCorrect = false;
    char name[50];
    char prof[60];
    int age = 0;
    int exp = 0;
    printf("Appending:\n");
    do {
        printf("Type name of your employee: ");        
        if (ReadLine(name,50) == 0) {
            ClearCSL();
            printf("You tryed to type wrong data, try not to...\n");
            continue;
        }
        printf("Type profession of your employee: ");        
        if (ReadLine(prof, 60) == 0) {
            ClearCSL();
            printf("You tryed to type wrong data, try not to...\n");
            continue;
        }
        printf("Type age of your employee: ");        
        if (!scanf("%d", &age)) {
            ClearCSL();
            printf("You tryed to type wrong data, try not to...\n");
            continue;
        }
        printf("Type work experience of your employee: ");        
        if (!scanf("%d", &exp)) {
            ClearCSL();
            printf("You tryed to type wrong data, try not to...\n");
            continue;
        }
        isCorrect = true;
    } while (!isCorrect);
    ListAdd(&database, NewEmp(name, prof, age, exp));
    printf("\nYour employee added to database!\n");
    printf("\nPress any key to go back");
    getchar();
}

void ShowListUI() {
    ClearCSL();
    ShowList(&database);    
    printf("\nPress any key to go back");
    getch();
}

void FindByNameListUI() {
    ClearCSL();
    printf("Type search request to find items by name");
    char name[50];
    ReadLine(name, 50);
    ListFindByName(&database, name);
    printf("\nPress any key to go back");
    getch();
}

void FindByAgeListUI() {
    ClearCSL();
    printf("Type search request to find items by age");
    int age = -1;
    scanf("%d", &age);
    ListFindByAge(&database, age);
    printf("\nPress any key to go back");
    getch();
}

void FindByProfessionListUI() {
    ClearCSL();
    printf("Type search request to find items by profession");
    char prof[50];
    ReadLine(prof, 50);
    ListFindByProf(&database, prof);
    printf("\nPress any key to go back");
    getch();
}

void FindByExpListUI() {
    ClearCSL();
    printf("Type search request to find items by experience");
    int exp = -1;
    scanf("%d", &exp);
    ListFindByExp(&database, exp);
    printf("\nPress any key to go back");
    getch();
}

void DeleteFromListUI() {
    ClearCSL();
    printf("Type index of element you want to delete");
    printf("\nrange is 0-%d:\n", database.length -1);
    int index = -1;
    scanf("%d", &index);
    if (ListRemoveAt(&database, index)) {
        printf("\nElement successfully deleted");
    }
    else
    {
        printf("\nNone existing index");
    }
    printf("\nPress any key to go back");
    getch();
}

void ReplaceInListUI() {
    ClearCSL();
    bool isCorrect = false;
    char name[50];
    char prof[60];
    int age = 0;
    int exp = 0;
    printf("Replacing with:\n");
    do {
        printf("Type name of your employee: ");
        if (ReadLine(name, 50) == 0) {
            ClearCSL();
            printf("You tryed to type wrong data, try not to...\n");
            continue;
        }
        printf("Type profession of your employee: ");
        if (ReadLine(prof, 60) == 0) {
            ClearCSL();
            printf("You tryed to type wrong data, try not to...\n");
            continue;
        }
        printf("Type age of your employee: ");
        if (!scanf("%d", &age)) {
            ClearCSL();
            printf("You tryed to type wrong data, try not to...\n");
            continue;
        }
        printf("Type work experience of your employee: ");
        if (!scanf("%d", &exp)) {
            ClearCSL();
            printf("You tryed to type wrong data, try not to...\n");
            continue;
        }
        isCorrect = true;
    } while (!isCorrect);

    printf("Type index of element you want to delete");
    printf("\nrange is 0-%d", database.length);
    int index = -1;
    scanf("%d", index);
    if (ListReplaceAt(&database,NewEmp(name, prof, age, exp), index)) {
        printf("\nElement successfully replaced");
    }
    else
    {
        printf("\nNone existing index");
    }
    printf("\nPress any key to go back");
    getch();
}

void LoadFromFile() {
    printf("Loading database");
    FILE* file;
    if ((file = fopen64("datafile.bin", "rb")) != 0) {
        printf("\n\nFailed to open a file");
        return;
    }
    for (int n = 0; !feof(file); ++n)
    {
        Employee emp;
        if (fread(&emp, sizeof(Employee), 1, file) != 1) break;
        ListAdd(&database, emp);
    }
    fclose(file);
    printf("\nDatabase loaded");
}

void SaveToFile() {
    ClearCSL();
    printf("\nSaving database");
    FILE* file;
    if ((file = fopen64("datafile.bin", "wb")) != 0) {
        printf("\n\nFailed to open and write to a file");
        return;
    }
    fwrite(database.items, sizeof(Employee), database.length, file);
    fclose(file);
    printf("\n\nDatabase saved\n");
}

void FreeAll() {
    printf("Freeing memory");
    free(database.items);
    printf("\nPress any key to close");
    getch();
}

void ClearCSL() {
    system("cls");
}

int ReadLine(char * str, int lenght) {
    int c, i = 0;
    scanf("%c", &c, sizeof(char));
    while (c != '\n' && c != EOF) {
        str[i] = c;
        c = getchar();
        i++;
    }
    str[i] = '\0';
    removeChar(str, '\n');
    return i;
}

void removeChar(char* str, char chr) {
    int writer = 0, reader = 0;
    while (str[reader])    {
        if (str[reader] != chr)        {
            str[writer++] = str[reader];
        }
        reader++;
    }
    str[writer] = 0;
}

int getch()
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}