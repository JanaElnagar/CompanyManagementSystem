#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int saved=1;

typedef struct
{
    int day,month,year;
} Date;
void Print_Date(Date d)
{
    printf("%d/%d/%d",d.day,d.month,d.year);
}
typedef struct
{
    int id;
    char l_name[100],f_name[100],address[100],phone_no[100],email[100];
    float salary;
    Date DOB;
} Employee;

Employee emps[200];

void Print_Employee (Employee e)
{
    printf("id:%d",e.id);
    printf("\nLast name: %s \t\tDate of Birth:",e.l_name);Print_Date(e.DOB);
    printf("\nFirst name: %s \t\tPhone number: %s",e.f_name,e.phone_no);
    printf("\nSalary: %f \t\tE-mail: %s",e.salary,e.email);
    printf("\nAddress: %s \n\n",e.address);

}

void Get_File_name(char *file_name)
{
    printf("Enter text file name(please enter in filename.txt format):");
    gets(file_name);
}
void Deserialize (char*str,Employee*e)
{
    char *token;
    int i=0;
    token=strtok(str,",-\n");
    while (token)
    {
        switch (i)
        {
        case 0:
            e->id=atoi(token);
            break;
        case 1:
            strcpy(e->l_name,token);
            break;
        case 2:
            strcpy(e->f_name,token);
            break;
        case 3:
            e->salary=atof(token);
            break;
        case 4:
            e->DOB.day=atoi(token);
            break;
        case 5:
            e->DOB.month=atoi(token);
            break;
        case 6:
            e->DOB.year=atoi(token);
            break;
        case 7:
            strcpy(e->address,token);
            break;
        case 8:
            strcpy(e->phone_no,token);
            break;
        case 9:
            strcpy(e->email,token);
            break;
        }
        i++;
        token=strtok(NULL,",-\n");

    }
}
int Load(char*file_name)
{
    char str[500][500];
    int i=0;
    FILE*f=fopen(file_name,"r");
    if(!f)
    {
        printf("Error: File doesn't exist.\n\t\tExit Program");
        exit(-1);
    }
    while (!feof(f))
    {
        fgets(str[i],499,f);
        Deserialize(str[i],&emps[i]);
        i++;
    }
    fclose(f);
    return i;
}
int validNum(char *num)
{
    int i;
    for(i=0; num[i]; i++)
        if((strlen(num)!=11)||(num[0]!='0')||!isdigit(num[i]))
        {
            printf("Phone Number is not valid\n");
            return 0;
        }
    return 1;
}
int validDOB(Date DOB)
{
    int flag=1;
    if(DOB.year < 1952 || DOB.year > 2003)
    {
        printf("Employee is too young or too old to be an employee\n");
        flag = 0;
    }
    if (DOB.month >12 || DOB.month<1)
    {
        printf("Invalid Month.Enter number between 1 and 12\n");
        flag = 0;
    }
    if(DOB.month == 11||DOB.month == 4||DOB.month == 6||DOB.month ==9)
    {
        if(DOB.day>30 || DOB.day<1)
        {
            printf("Invalid day.Enter number between 1 and 30\n");
            flag = 0;
        }
    }
    else if(DOB.month == 1||DOB.month == 3||DOB.month == 5||DOB.month ==7||DOB.month ==8||DOB.month ==10||DOB.month ==12)
    {
        if(DOB.day>31 || DOB.day<1)
        {
            printf("Invalid day.Enter number between 1 and 31\n");
            flag = 0;
        }
    }
    else if(DOB.month ==2)
    {
        if(DOB.day > 29)
        {
            printf("Invalid day.Enter number between 1 and 29\n");
            flag = 0;
        }
    }
    return flag;
}
int Valid_email(char*email)
{
    int count_at=0,count_pt=0,at,pt,i;
    for(i=0 ; i<strlen(email) ; i++)
        if(email[i]=='@')
        {
            count_at +=1;
            at=i;
        }
    if (count_at!=1)
    {
        printf("Invalid email \n");
        return 0;
    }
    for(i=0; i<at; i++)
        if(email[i]!='_' && email[i]!='.' && !isalnum(email[i]))
        {
            printf("Invalid email \n");
            return 0;
        }
    for (i=at+1; i<strlen(email); i++)
        if(email[i]=='.')
        {
            count_pt +=1;
            pt=i;
        }
    if (count_pt!=1)
    {
        printf("Invalid email \n");
        return 0;
    }
    for(i=at+1; i<pt; i++)
        if (!isalpha(email[i]))
        {
            printf("Invalid email \n");
            return 0;
        }
    for(i=pt+1; i<strlen(email); i++)
        if (!isalpha(email[i]))
        {
            printf("Invalid email \n");
            return 0;
        }
    return 1;

}
int validDigit(char *str)
{
    int i;
    for(i=0; i<strlen(str); i++)
    {
        if(!isdigit(str[i]))
        {
            printf("Invalid Format. Please enter a correct number:\n");
            return 0;
        }
    }
    return 1;
}
int validFloat(char *str)
{
    int i,pt=0;
    for(i=0; i<strlen(str); i++)
    {
        if (str[i]=='.')
        {
            pt++;
            if(pt>1)
            {
                printf("Invalid. Please enter a correct number:\n");
                return 0;
            }
        }
        else if (!isdigit(str[i]))
        {
            printf("Invalid. Please enter a correct number:\n");
            return 0;
        }
    }
    return 1;
}
void Correct_Address(char*address)
{
    int i;
    for (i=0; address[i]; i++)
        if (address[i]==','|| address[i]=='-')
            address[i]=' ';
}
void Capitalize(char*name) //Capitalizes first letter in the name
{
    name[0]=toupper(name[0]);
}
void SortBySalary (Employee* employees, int num)
{
    int i,j;
    Employee temp;
    int sorted=0;
    for (i=1; i<num&&!sorted; i++)
    {
        sorted=1;
        for(j=0; j<num-1; j++)
            if(employees[j].salary > employees[j+1].salary)
            {
                sorted=0;
                temp=employees[j];
                employees[j]=employees[j+1];
                employees[j+1]=temp;
            }
    }
}
void SortByLastName (Employee* employees, int num)
{
    int i, j;
    Employee temp;
    int sorted=0;
    for(i=0; i<num&&!sorted; i++)
    {
        sorted=1;
        for(j=0; j<num-1-i; j++)
            if(strcasecmp(employees[j].l_name, employees[j+1].l_name) > 0)
            {
                sorted=0;
                temp= employees[j];
                employees[j]= employees[j+1];
                employees[j+1]= temp;
            }
    }


}
void SortByDOB (Employee* employees, int num)
{
    int i,j;
    Employee temp;
    int sorted=0;
    for (i=1; i<num&&!sorted; i++)
    {
        sorted=1;
        for(j=0; j<num-1; j++)
            if(employees[j].DOB.year > employees[j+1].DOB.year)
            {
                sorted=0;
                temp=employees[j];
                employees[j]=employees[j+1];
                employees[j+1]=temp;
            }
            else if((employees[j].DOB.year == employees[j+1].DOB.year)&&(employees[j].DOB.month > employees[j+1].DOB.month))
            {
                sorted=0;
                temp=employees[j];
                employees[j]=employees[j+1];
                employees[j+1]=temp;
            }
            else if ((employees[j].DOB.year == employees[j+1].DOB.year)&&(employees[j].DOB.month == employees[j+1].DOB.month)&&(employees[j].DOB.day > employees[j+1].DOB.day))
            {
                sorted=0;
                temp=employees[j];
                employees[j]=employees[j+1];
                employees[j+1]=temp;
            }
    }


}
void Read_Employee(Employee* e)
{
    printf("Enter employee id: ");
    char ID[10],salary[10];
    do
    {
        gets(ID);
    }
    while(!validDigit(ID));
    e->id=atoi(ID);
    printf("Enter employee last name: ");
    gets(e->l_name);
    Capitalize(e->l_name);
    printf("Enter employee first name: ");
    gets(e->f_name);
    Capitalize(e->f_name);
    printf("Enter employee salary: ");
    do gets(salary);
    while (!validFloat(salary));
    e->salary=atof(salary);
    do
    {
        printf("Enter employee birth day: ");
        scanf("%d",&e->DOB.day);
        printf("Enter employee birth month: ");
        scanf("%d",&e->DOB.month);
        printf("Enter employee birth year: ");
        scanf("%d",&e->DOB.year);
    }
    while (!validDOB(e->DOB));

    getchar();
    printf("Enter employee address: ");
    gets(e->address);
    Correct_Address(e->address);

    do
    {
        printf("Enter employee phone number: ");
        gets(e->phone_no);
    }
    while (!validNum(e->phone_no));
    do
    {
        printf("Enter employee e-mail: ");
        gets(e->email);
    }
    while(!Valid_email(e->email));
}

void Query(int num)
{
    char l_name[100];
    int i,found=0;
    getchar();
    printf("Enter Employee's last name: ");
    gets(l_name);
    Capitalize(l_name);
    for(i=0; i<num; i++)
        if (!(strcasecmp(l_name,emps[i].l_name)))
        {
            found=1;
            Print_Employee(emps[i]);
        }
    if (!found)
        printf("There's no Employee with entered last name\n");
}
void Add_Employee (Employee *e)
{
    saved=0;
    getchar();
    Read_Employee(e);
}
void Delete_Employee (int*num)
{
    saved=0;
    char l_name[100],f_name[100];
    int i,j,found=0;
    getchar();
    printf("Enter Employee last name: ");
    gets(l_name);
    Capitalize(l_name);
    printf("Enter Employee first name: ");
    gets(f_name);
    Capitalize(f_name);
    for(i=0; i<*num; i++)
        if(!(strcasecmp(l_name,emps[i].l_name))&&!(strcasecmp(f_name,emps[i].f_name)))
        {
            found=1;
            for(j=i; j<(*num)-1; j++)
                emps[j]=emps[j+1];
            i--;
            (*num)--;
        }
    if (!found)
        printf("There's no Employee with entered first name and last name\n");
}
void Modify_Employee (int*num)
{
    saved=0;
    int i,found=0;
    getchar();
    printf("Enter Employee id:");
    char ID[10];
    do gets(ID);    while(!validDigit(ID));
    int id=atoi(ID);
    for (i=0; i<*num; i++)
        if (emps[i].id==id)
        {
            found=1;
            printf("Enter the modified data:\n");
            Read_Employee(&emps[i]);
        }
    if (!found)
        printf("There's no employee with entered id.\n ");
}
void Print_Sorted (int num)
{
    int i,x;
    Employee employees[500];
    for (i=0; i<num; i++)
    {
        employees[i]=emps[i];
    }
    printf("In what order do you want the employees sorted\n1.By last name\n2.By date of birth\n3.By salary\nEnter number: ");
    scanf("%d",&x);
    printf("Employees Sorted:\n");

    switch (x)
    {
    case 1:
        SortByLastName(employees,num);
        break;
    case 2:
        SortByDOB(employees,num);
        break;
    case 3:
        SortBySalary(employees,num);
        break;
    default:
        printf("Invalid Number. Enter Number between 1 and 3:\n");
        Print_Sorted(num);
        break;
    }
    for (i=0; i<num; i++)
    {
        Print_Employee(employees[i]);
    }
}
void Save (char*file_name,int num)
{
    int i;
    FILE *f=fopen(file_name,"w");
    for(i=0; i<num; i++)
    {
        if(i==num-1)
            fprintf(f,"%d,%s,%s,%f,%d-%d-%d,%s,%s,%s",emps[i].id,emps[i].l_name,emps[i].f_name,emps[i].salary,emps[i].DOB.day,emps[i].DOB.month,emps[i].DOB.year,emps[i].address,emps[i].phone_no,emps[i].email);
        else
            fprintf(f,"%d,%s,%s,%f,%d-%d-%d,%s,%s,%s\n",emps[i].id,emps[i].l_name,emps[i].f_name,emps[i].salary,emps[i].DOB.day,emps[i].DOB.month,emps[i].DOB.year,emps[i].address,emps[i].phone_no,emps[i].email);

    }
    fclose(f);
    saved=1;
    printf("Your changes have been saved successfully.\n");
}
void Menu (int*,char*);
void Quit (int *num,char*fname)
{
    int x;
    if (saved)
        exit (0);
    printf("\nYou didn't save your changes. They will be discarded.\nAre you sure you want to exit?\n1.Yes\n2.No\nEnter number: ");
    scanf("%d",&x);
    if (x==1)
        exit (0);
    else if(x==2)
        Menu(num,fname);
    else
        Quit(*num,*fname);

}

void Menu (int *num,char*fname)
{
    int x;
    printf("What do you want to do:");
    printf("\n1.Query\n2.Add\n3.Delete\n4.Modify\n5.Print\n6.Save\n7.Quit\n");
    printf("Enter number of operation: ");
    scanf("%d",&x);

    switch (x)
    {
    case 1:
        Query(*num);
        break;
    case 2:
        Add_Employee(&emps[(*num)++]);
        break;
    case 3:
        Delete_Employee(num);
        break;
    case 4:
        Modify_Employee(num);
        break;
    case 5:
        Print_Sorted(*num);
        break;
    case 6:
        Save(fname,*num);
        break;
    case 7:
        Quit(num,fname);
        break;
    default:
        printf("Invalid Operation. Please enter a number from 1 to 7");
        Menu(num,fname);
        break;
    }
    Menu(num,fname);
}
int main()
{
    int num;
    char fname[50];

    Get_File_name(fname);
    num=Load(fname);

    Menu(&num,fname);
    return 0;
}
