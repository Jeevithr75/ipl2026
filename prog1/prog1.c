#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int id;
    char name[30];
};

void createFile()
{
    FILE *fp;
    struct Student s;
    int n;

    fp = fopen("student.dat", "wb");

    printf("Enter number of records: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("\nRecord %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &s.id);

        printf("Enter Name: ");
        scanf("%s", s.name);

        fwrite(&s, sizeof(struct Student), 1, fp);
    }

    fclose(fp);
}

void getRecord(int m)
{
    FILE *fp;
    struct Student s;

    fp = fopen("student.dat", "rb");

    fseek(fp, (m - 1) * sizeof(struct Student), SEEK_SET);

    if(fread(&s, sizeof(struct Student), 1, fp))
    {
        printf("\nRecord %d\n", m);
        printf("ID   : %d\n", s.id);
        printf("Name : %s\n", s.name);
    }
    else
    {
        printf("Record not found\n");
    }

    fclose(fp);
}

void deleteRecord(int del)
{
    FILE *fp, *temp;
    struct Student s;
    int count = 1;

    fp = fopen("student.dat", "rb");
    temp = fopen("temp.dat", "wb");

    while(fread(&s, sizeof(struct Student), 1, fp))
    {
        if(count != del)
        {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
        count++;
    }

    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    printf("Record %d deleted successfully\n", del);
}

int main()
{
    int m, d;

    createFile();

    printf("\nEnter record number to display: ");
    scanf("%d", &m);
    getRecord(m);

    printf("\nEnter record number to delete: ");
    scanf("%d", &d);
    deleteRecord(d);

    return 0;
}