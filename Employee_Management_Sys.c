#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define Red "\033[1;31m"
#define Green "\033[1;32m"
#define Yellow "\033[1;33m"
#define Magenta "\033[1;35m"
#define Reset "\033[1;37m"

struct Employee
{
    char Emp_Name[50];
    char Emp_ID[50];
    char Emp_Department[50];
    char Emp_Designation[100];
    char Emp_Joining_Date[50];
    float Yearly_Sal;
    float Emp_Net_Sal;
};

struct Resign_Employee
{
    char Resign_Emp_Name[50];
    char Resign_Emp_ID[50];
    char Resign_Emp_Department[50];
    char Resign_Emp_Designation[100];
    char Resign_Emp_Joining_Date[50];
    char Resign_Date[50];
    char Reason[2000];
};

void Add_New_Employee(struct Employee employees[], int *num_emp);
void Emp_Resigned(struct Resign_Employee Resign_emp[], struct Employee employees[], int *resign_num_ep, int *num_emp);
void Display_All_Employee(struct Employee employees[], int num_emp);
void Display_Resigned_Employee(struct Resign_Employee Resign_emp[], int resign_num_emp);
void Search_Employee(struct Employee employees[], int num_emp);
void Update_Employee(struct Employee employees[], int num_emp);
void Delete_Employee(struct Employee employees[], int *num_emp);
void Save_Employees(struct Employee employees[], int num_emp);
void Save_Resign_Employee(struct Resign_Employee Resign_emp[], int *resign_num_emp);
void Load_Employees(struct Employee employees[], int *num_emp);
void Load_Resign_Employees(struct Resign_Employee Resign_emp[], int *resign_num_emp);
void Net_Sal(struct Employee employees[], int num_emp);
void Sort_Emp_ID(struct Employee employees[], int num_emp);
void Sort_Emp_Sal(struct Employee employees[], int num_emp);
void Export_To_CSV(struct Employee employees[], int num_emp);
void Export_Resigned_To_CSV(struct Resign_Employee Resign_emp[], int resign_num_emp);
void Ask_Save_Changes(struct Employee employees[], int num_emp);

int main()
{
    struct Employee employees[100];
    struct Resign_Employee Resign_emp[100];
    int num_emp = 0, resign_num_emp = 0, choice;
    char Auth[100] = "24ITB079_24ITB091";
    char password[100] = "Nirma@123";
    char password_veri[100];
    char auth_veri[100];

    printf("\n========================== %sAuthentication%s ========================== \n\n", Magenta, Reset);
    printf("Enter your ID: ");
    scanf("%s", auth_veri);
    if (strcmp(auth_veri, Auth) == 0)
    {
        printf("Enter Password: ");
        scanf("%s", password_veri);

        if (strcmp(password, password_veri) == 0)
        {
            printf(Green "Password Verified Successfully..\n\n" Reset);
            printf("================== %sEMPLOYEE MANAGEMENT SYSTEM%s ==================\n\n", Magenta, Reset);

            Load_Employees(employees, &num_emp);
            Load_Resign_Employees(Resign_emp, &resign_num_emp);

            while (1)
            {
                printf("\n----------------------------------------------------------------\n");
                printf("Total Number of Employees' Data available: %d\n", num_emp + resign_num_emp);
                printf(Green "Total Number of Employees Currently working: %d\n" Reset, num_emp);
                printf(Red "Total number of Resigned Employees are: %d\n" Reset, resign_num_emp);
                printf("----------------------------------------------------------------\n");
                printf("1. Add New Employee.\n");
                printf("2. Display All Employees.\n");
                printf("3. Search for an Employee.\n");
                printf("4. Update Employee Details.\n");
                printf("5. Delete an Employee Record.\n");
                printf("6. Enter the Data of Resigned Employees.\n");
                printf("7. Display Resigned Employees.\n");
                printf("8. Save and Exit.\n");
                printf("----------------------------------------------------------------\n\n");

                printf("Enter your Choice (1-8): ");
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
                    Emp_Resigned(Resign_emp, employees, &resign_num_emp, &num_emp);
                    break;
                case 7:
                    Display_Resigned_Employee(Resign_emp, resign_num_emp);
                    break;
                case 8:
                    Save_Employees(employees, num_emp);
                    Ask_Save_Changes(employees, num_emp);
                    printf(Yellow "Exiting.....\n" Reset);
                    return 0;
                default:
                    printf("Invalid choice. Please try again.\n");
                }
            }
        }

        for (int i = 0; i < 5; i++)
        {
            if (strcmp(password, password_veri) != 0)
            {
                printf(Red "Incorrect Password...\n" Reset);
                printf("Enter Password: ");
                scanf("%s", password_veri);
                if (i == 4)
                {
                    printf(Red "Sorry...\nYou entered incorrect password %d times.\n" Reset, i + 1);
                    printf("Please try after sometime.\n");
                }
            }
        }
    }
    printf(Red "Incorrect Authentication ID.\n" Reset);
}

void Add_New_Employee(struct Employee employees[], int *num_emp)
{
    printf("\nEnter Name: ");
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
    printf("Employee added successfully.\n\n");
    Net_Sal(employees, *num_emp);
}

void Display_All_Employee(struct Employee employees[], int num_emp)
{
    if (num_emp == 0)
    {
        printf("No Employees to Display.\n");
        return;
    }

    char sort;
    printf("Sort Employees according to Employee's Salary(S) or ID(I): \n");
    while ((getchar()) != '\n')
        ;
    scanf("%c", &sort);
    sort = toupper(sort);
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

void Display_Resigned_Employee(struct Resign_Employee Resign_emp[], int resign_num_emp)
{
    if (resign_num_emp == 0)
    {
        printf("No Employees to Display.\n");
        return;
    }

    printf("Displaying all Employees: \n\n");

    for (int i = 0; i < resign_num_emp; i++)
    {
        printf("\n\nEmployee %d:\n", i + 1);
        printf("Employee's Name: %s\n", Resign_emp[i].Resign_Emp_Name);
        printf("Employee's ID: %s\n", Resign_emp[i].Resign_Emp_ID);
        printf("Employee's Department: %s\n", Resign_emp[i].Resign_Emp_Department);
        printf("Employee's Designation: %s\n", Resign_emp[i].Resign_Emp_Designation);
        printf("Employee's Date of Joining: %s\n", Resign_emp[i].Resign_Emp_Joining_Date);
        printf("Employee's Date of Resignation: %s\n", Resign_emp[i].Resign_Date);
        printf("Employee's %sResignation%s reason: %s\n", Red, Reset, Resign_emp[i].Reason);
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
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            scanf("%s", employees[i].Emp_Designation);
            printf("Enter New Yearly Salary:Rs. ");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
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
            Export_To_CSV(employees, *num_emp);
            return;
        }
    }
    printf("Employee Not Found.\n");
}

void Save_Employees(struct Employee employees[], int num_emp)
{
    FILE *file = fopen("Employees.dat", "wb");
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
    FILE *file = fopen("Employees.dat", "rb");
    if (file == NULL)
    {
        printf(Red "No saved employee data found.\n" Reset);
        return;
    }
    fread(num_emp, sizeof(int), 1, file);
    fread(employees, sizeof(struct Employee), *num_emp, file);
    fclose(file);
    printf(Green "Employee data loaded successfully.\n" Reset);
}

void Load_Resign_Employees(struct Resign_Employee Resign_emp[], int *resign_num_emp)
{
    FILE *file = fopen("Resigned Employees.dat", "rb");
    if (file == NULL)
    {
        printf(Red "No Resigned employee's data found.\n" Reset);
        return;
    }
    fread(resign_num_emp, sizeof(int), 1, file);
    fread(Resign_emp, sizeof(struct Resign_Employee), *resign_num_emp, file);
    fclose(file);
    printf(Green "Resigned Employees' data loaded successfully.\n" Reset);
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
        fprintf(file, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%.3f\",\"%.3f\n",
                employees[i].Emp_Name,
                employees[i].Emp_ID,
                employees[i].Emp_Department,
                employees[i].Emp_Designation,
                employees[i].Emp_Joining_Date,
                employees[i].Yearly_Sal,
                employees[i].Emp_Net_Sal);
    }
    fclose(file);
    printf("Employee data has been %ssuccessfully%s backed up to 'EmployeesBackup.csv'.\n", Green, Reset);
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

void Emp_Resigned(struct Resign_Employee Resign_emp[], struct Employee employees[], int *resign_num_emp, int *num_emp)
{
    char resign_employee[50];
    printf("Enter the Employee's ID who Resigned: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    scanf("%[^\n]", resign_employee);

    for (int i = 0; i < *num_emp; i++)
    {
        if (strcmp(employees[i].Emp_ID, resign_employee) == 0)
        {
            strcpy(Resign_emp[*resign_num_emp].Resign_Emp_Name, employees[i].Emp_Name);
            strcpy(Resign_emp[*resign_num_emp].Resign_Emp_ID, employees[i].Emp_ID);
            strcpy(Resign_emp[*resign_num_emp].Resign_Emp_Department, employees[i].Emp_Department);
            strcpy(Resign_emp[*resign_num_emp].Resign_Emp_Designation, employees[i].Emp_Designation);
            strcpy(Resign_emp[*resign_num_emp].Resign_Emp_Joining_Date, employees[i].Emp_Joining_Date);

            printf("Enter the reason for Resignation: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            scanf("%[^\n]", Resign_emp[*resign_num_emp].Reason);

            printf("Enter Date of Resignation: ");
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            scanf("%[^\n]", Resign_emp[*resign_num_emp].Resign_Date);

            (*resign_num_emp)++;

            for (int j = i; j < *num_emp - 1; j++)
            {
                employees[j] = employees[j + 1];
            }
            (*num_emp)--;

            Save_Resign_Employee(Resign_emp, resign_num_emp);
            printf(Green "Employee resignation recorded successfully.\n" Reset);
            return;
        }
    }

    printf(Red "Employee not found.\n" Reset);
}

void Save_Resign_Employee(struct Resign_Employee Resign_emp[], int *resign_num_emp)
{
    FILE *file = fopen("Resigned Employees.dat", "wb");
    if (file == NULL)
    {
        printf(Red "Error: Unable to save resigned employees' data.\n" Reset);
        return;
    }
    fwrite(resign_num_emp, sizeof(int), 1, file);
    fwrite(Resign_emp, sizeof(struct Resign_Employee), *resign_num_emp, file);
    fclose(file);
    printf(Green "Resignation details saved successfully.\n" Reset);
}

void Export_Resigned_To_CSV(struct Resign_Employee Resign_emp[], int resign_num_emp)
{
    FILE *file = fopen("ResignedEmployeesBackup.csv", "w");
    if (file == NULL)
    {
        printf(Red "Error: Unable to create resigned backup file.\n" Reset);
        return;
    }
    fprintf(file, "Resign_Emp_Name,Resign_Emp_ID,Resign_Emp_Department,Resign_Emp_Designation,Resign_Emp_Joining_Date,Resign_Date,Reason\n");
    for (int i = 0; i < resign_num_emp; i++)
    {
        fprintf(file, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
                Resign_emp[i].Resign_Emp_Name,
                Resign_emp[i].Resign_Emp_ID,
                Resign_emp[i].Resign_Emp_Department,
                Resign_emp[i].Resign_Emp_Designation,
                Resign_emp[i].Resign_Emp_Joining_Date,
                Resign_emp[i].Resign_Date,
                Resign_emp[i].Reason);
    }
    fclose(file);
    printf(Green "Resigned employees' data has been successfully backed up to 'ResignedEmployeesBackup.csv'.\n" Reset);
}