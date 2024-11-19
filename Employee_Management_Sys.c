#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Employee
{
    char Emp_Name[50];
    char Emp_ID[50];
    char Emp_Department[50];
    char Emp_Designation[50];
    char Emp_Joining_Date[50];
    float Yearly_Sal;
    float Emp_Net_Sal;
};

void Add_New_Employee(struct Employee employees[], int *num_emp);
void Display_All_Employee(struct Employee employees[], int num_emp);
void Search_Employee(struct Employee employees[], int num_emp);
void Update_Employee(struct Employee employees[], int num_emp);
void Delete_Employee(struct Employee employees[], int *num_emp);
void Save_Employees(struct Employee employees[], int num_emp);
void Load_Employees(struct Employee employees[], int *num_emp);
void Net_Sal(struct Employee employees[], int num_emp);
void Sort_Emp_ID(struct Employee employees[], int num_emp);
void Sort_Emp_Sal(struct Employee employees[], int num_emp);
void Export_To_CSV(struct Employee employees[], int num_emp);
void Ask_Save_Changes(struct Employee employees[], int num_emp);

int main()
{
    struct Employee employees[100];
    int num_emp = 0, choice;

    Load_Employees(employees, &num_emp);

    while (1)
    {
        printf("\n\nTotal Number of Employees: %d\n\n", num_emp);
        printf("1. Add New Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search for an Employee\n");
        printf("4. Update Employee Details\n");
        printf("5. Delete an Employee Record\n");
        printf("6. Save and Exit\n");
        printf("7. Export to CSV.\n\n");

        printf("Enter your Choice (1-7): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            Add_New_Employee(employees, &num_emp);
            break;
        case 2:
            Display_All_Employee(employees, num_emp);
            break;
        case 3:
            Search_Employee(employees, num_emp);
            break;
        case 4:
            Update_Employee(employees, num_emp);
            break;
        case 5:
            Delete_Employee(employees, &num_emp);
            break;
        case 6:
            Save_Employees(employees, num_emp);
            Ask_Save_Changes(employees, num_emp);
            printf("Exiting.....\n");
            return 0;
        case 7:
            Export_To_CSV(employees, num_emp);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void Add_New_Employee(struct Employee employees[], int *num_emp)
{
    printf("Enter Name: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    scanf("%[^\n]", employees[*num_emp].Emp_Name);
    printf("Enter ID: ");
    scanf("%s", employees[*num_emp].Emp_ID);
    printf("Employee's Department: ");
    scanf("%s", employees[*num_emp].Emp_Department);
    printf("Enter Designation: ");
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    scanf("%[^\n]", employees[*num_emp].Emp_Designation);
    printf("Employee's Date of Joining: ");
    scanf("%s", employees[*num_emp].Emp_Joining_Date);
    printf("Enter Yearly Salary:Rs. ");
    scanf("%f", &employees[*num_emp].Yearly_Sal);
    (*num_emp)++;
    printf("Employee added successfully.\n");
    Net_Sal(employees, *num_emp);
}

void Display_All_Employee(struct Employee employees[], int num_emp)
{
    if (num_emp == 0)
    {
        printf("No Employees to Display.\n");
        return;
    }

    char sort, Sort;
    printf("Sort Employees according to Employee's Salary(S) or ID(I): \n");
    while ((getchar()) != '\n')
        ;
    scanf("%c", &Sort);
    sort = toupper(Sort);
    printf("Displaying all Employees: \n\n");

    if (sort == 'I')
    {
        Sort_Emp_ID(employees, num_emp);
    }

    else if (sort == 'S')
    {
        Sort_Emp_Sal(employees, num_emp);
    }

    else
    {
        printf("Please enter a valid Input...\n");
    }

    for (int i = 0; i < num_emp; i++)
    {
        printf("\n\nEmployee %d:\n", i + 1);
        printf("Employee's Name: %s\n", employees[i].Emp_Name);
        printf("Employee's ID: %s\n", employees[i].Emp_ID);
        printf("Employee's Department: %s\n", employees[i].Emp_Department);
        printf("Employee's Designation: %s\n", employees[i].Emp_Designation);
        printf("Employee's Date of Joining: %s\n", employees[i].Emp_Joining_Date);
        printf("Employee's Yearly Salary:Rs. %.3f\n", employees[i].Yearly_Sal);
        printf("Employee's Net Salary:Rs. %.3f", employees[i].Emp_Net_Sal);
    }
}

void Sort_Emp_ID(struct Employee employee[], int num_emp)
{
    struct Employee temp;
    for (int i = 0; i < num_emp - 1; i++)
    {
        for (int j = 0; j < num_emp - i - 1; j++)
        {
            if (strcmp(employee[j].Emp_ID, employee[j + 1].Emp_ID) > 0)
            {
                temp = employee[j];
                employee[j] = employee[j + 1];
                employee[j + 1] = temp;
            }
        }
    }
}

void Sort_Emp_Sal(struct Employee employees[], int num_emp)
{
    struct Employee temp;
    for (int i = 0; i < num_emp - 1; i++)
    {
        for (int j = 0; j < num_emp - i - 1; j++)
        {
            if (employees[j].Yearly_Sal > employees[j + 1].Yearly_Sal)
            {
                temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

void Search_Employee(struct Employee employees[], int num_emp)
{
    char search[50];
    printf("Enter Employee ID to Search: ");
    scanf("%s", search);

    for (int i = 0; i < num_emp; i++)
    {
        if (strcmp(employees[i].Emp_ID, search) == 0)
        {
            printf("\n\nEmployee Found.\n");
            printf("Employee's Name: %s\n", employees[i].Emp_Name);
            printf("Employee's ID: %s\n", employees[i].Emp_ID);
            printf("Employee's Designation: %s\n", employees[i].Emp_Designation);
            printf("Employee's Yearly Salary:Rs. %.3f\n", employees[i].Yearly_Sal);
            printf("Employee's Net Salary:Rs. %.3f", employees[i].Emp_Net_Sal);
            return;
        }
    }
    printf("Employee Not Found.\n");
}

void Update_Employee(struct Employee employees[], int num_emp)
{
    char update_id[50];
    printf("Enter the ID of Employee to Update: ");
    scanf("%s", update_id);

    for (int i = 0; i < num_emp; i++)
    {
        if (strcmp(employees[i].Emp_ID, update_id) == 0)
        {
            printf("Enter New Designation: ");
            scanf("%s", employees[i].Emp_Designation);
            printf("Enter New Yearly Salary:Rs. ");
            scanf("%f", &employees[i].Yearly_Sal);
            printf("Employee details updated successfully.\n");
            Net_Sal(employees, num_emp);
            return;
        }
    }
    printf("Employee Not Found.\n");
}

void Delete_Employee(struct Employee employees[], int *num_emp)
{
    if (*num_emp == 0)
    {
        printf("Sorry...\nNothing to Delete.\n\n");
        return;
    }

    char delete_id[50];
    printf("Enter the Employee's ID to Delete: ");
    scanf("%s", delete_id);

    for (int i = 0; i < *num_emp; i++)
    {
        if (strcmp(employees[i].Emp_ID, delete_id) == 0)
        {
            for (int j = i; j < *num_emp - 1; j++)
            {
                employees[j] = employees[j + 1];
            }
            (*num_emp)--;
            printf("Employee deleted successfully.\n");
            return;
        }
    }
    Export_To_CSV(employees, *num_emp);
    printf("Employee Not Found.\n");
}

void Save_Employees(struct Employee employees[], int num_emp)
{
    FILE *file = fopen("Employees.txt", "wb");
    if (file == NULL)
    {
        printf("Error saving employees.\n");
        return;
    }
    fwrite(&num_emp, sizeof(int), 1, file);
    fwrite(employees, sizeof(struct Employee), num_emp, file);
    fclose(file);
    printf("Employee data saved successfully.\n");
}

void Load_Employees(struct Employee employees[], int *num_emp)
{
    FILE *file = fopen("Employees.txt", "rb");
    if (file == NULL)
    {
        printf("No saved employee data found.\n");
        return;
    }
    fread(num_emp, sizeof(int), 1, file);
    fread(employees, sizeof(struct Employee), *num_emp, file);
    fclose(file);
    printf("Employee data loaded successfully.\n");
}

void Net_Sal(struct Employee employees[], int num_emp)
{
    for (int i = 0; i < num_emp; i++)
    {
        float Insur = employees[i].Yearly_Sal * 0.05;
        float PF = employees[i].Yearly_Sal * 0.1;
        employees[i].Emp_Net_Sal = employees[i].Yearly_Sal - (Insur + PF);
    }
}

void Export_To_CSV(struct Employee employees[], int num_emp)
{
    FILE *file = fopen("EmployeesBackup.csv", "w");
    if (file == NULL)
    {
        printf("Error: Unable to create backup file.\n");
        return;
    }
    fprintf(file, "Emp_Name,Emp_ID,Emp_Department,Emp_Designation,Emp_Joining_Date,Yearly_Sal,Emp_Net_Sal\n");
    for (int i = 0; i < num_emp; i++)
    {
        fprintf(file, "%s,%s,%s,%s,%s,%.3f,%.3f\n",
                employees[i].Emp_Name,
                employees[i].Emp_ID,
                employees[i].Emp_Department,
                employees[i].Emp_Designation,
                employees[i].Emp_Joining_Date,
                employees[i].Yearly_Sal,
                employees[i].Emp_Net_Sal);
    }
    fclose(file);
    printf("Employee data has been successfully backed up to 'EmployeesBackup.csv'.\n");
}

void Ask_Save_Changes(struct Employee employees[], int num_emp)
{
    char choice;
    printf("Do you want to save the changes to CSV? (y/n): ");
    scanf(" %c", &choice); 
    if (choice == 'y' || choice == 'Y')
    {
        Export_To_CSV(employees, num_emp);
    }
}