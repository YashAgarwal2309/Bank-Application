#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct customer
{
    int acno, balance;
    char name[40], actype[20];
} cust;

void openAccount()
{
    cust c;
    FILE *fp;
    fp = fopen("bank.dat", "ab");
    printf("\n Enter account number : ");
    scanf("%d", &c.acno);
    printf("\n Enter name : ");
    fflush(stdin);
    gets(c.name);
    printf("\n Enter account type : ");
    gets(c.actype);
    printf("\n Enter balance : ");
    scanf("%d", &c.balance);
    fwrite(&c, 1, sizeof(c), fp);
    fclose(fp);
    printf("\nRecord added");
}

void displayAll()
{
    cust c;
    int k;
    FILE *fp;
    fp = fopen("bank.dat", "rb");
    while (1)
    {
        k = fread(&c, 1, sizeof(c), fp);
        if (k == 0)
        {
            break;
        }
        printf("\n Account number : %d", c.acno);
        printf("\n Acount owner name  : %s", c.name);
        printf("\n Acount type : %s", c.actype);
        printf("\n Acount balance : %d", c.balance);
        printf("\n==========================================\n");
    }
    fclose(fp);
}

void searchAccount()
{
    cust c;
    int k, acno, f = 0;
    FILE *fp;
    fp = fopen("bank.dat", "rb");
    printf("\n Enter account number to be searched : ");
    scanf("%d", &acno);
    while (1)
    {
        k = fread(&c, 1, sizeof(c), fp);
        if (k == 0)
        {
            break;
        }
        if (acno == c.acno)
        {
            f = 1;
            printf("\n Account number : %d", c.acno);
            printf("\n Acount owner name  : %s", c.name);
            printf("\n Acount type : %s", c.actype);
            printf("\n Acount balance : %d", c.balance);
            break;
        }
    }
    if (f == 0)
    {
        printf("\n Account not found");
    }
    fclose(fp);
}

void deleteAccount()
{
    cust c;
    int k, acno, f = 0;
    FILE *fp1, *fp2;
    fp1 = fopen("bank.dat", "rb");
    fp2 = fopen("temp.dat", "wb");
    printf("\n Enter account number to be deleted : ");
    scanf("%d", &acno);
    while (1)
    {
        k = fread(&c, 1, sizeof(c), fp1);
        if (k == 0)
        {
            break;
        }
        if (acno == c.acno)
        {
            f = 1;
        }
        else
        {
            fwrite(&c, 1, sizeof(c), fp2);
        }
    }
    if (f == 0)
    {
        printf("\n Account not found");
    }
    fclose(fp1);
    fclose(fp2);
    remove("bank.dat");
    rename("temp.dat", "bank.dat");
}

void modifyAccount()
{

    cust c;
    char newname[40];
    int k, acno, f = 0, cur;
    FILE *fp;
    fp = fopen("bank.dat", "r+b");
    printf("\n Enter account number to be modified : ");
    scanf("%d", &acno);
    printf("\n Enter new name : ");
    fflush(stdin);
    gets(newname);
    while (1)
    {
        cur = ftell(fp);
        k = fread(&c, 1, sizeof(c), fp);
        if (k == 0)
        {
            break;
        }
        if (acno == c.acno)
        {
            f = 1;
            strcpy(c.name, newname);
            fseek(fp, cur, 0);
            fwrite(&c, 1, sizeof(c), fp);
            break;
        }
    }
    if (f == 0)
    {
        printf("\n Account not found");
    }
    fclose(fp);
}

void main()
{
    int k, choice;
    do
    {
        printf("\n 1. open account");
        printf("\n 2. display all account");
        printf("\n 3. search account");
        printf("\n 4. delete account");
        printf("\n 5. modify account");
        printf("\n 6. exit");
        printf("\n Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            openAccount();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchAccount();
            break;
        case 4:
            deleteAccount();
            break;
        case 5:
            modifyAccount();
            break;
        case 6:
            exit(0);
        default:
            printf("\n invalid choice");
        }
        printf("\n do you want to cont press 1 for no : ");
        scanf("%d", &k);
    } while (k != 1);
}