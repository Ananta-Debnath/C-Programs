
// Student Structure
/*
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int e_num;
    char* name;
    int year;
    int d_num;
    float cgpa;
}
student;

student* Read_Stu_info(int* ptr)
{
    int n;
    printf("Number of Students: ");
    scanf("%d", &n);
    *ptr = n;

    student* stu_list = malloc(n * sizeof(student));
    char* name;
    for(int i = 0; i < n; i++)
    {
        printf("\nStudent %d: \n", i+1);

        printf("Enrollment Number: ");
        scanf("%d", &stu_list[i].e_num);
        
        stu_list[i].name = malloc(50 * sizeof(char));
        printf("Name: ");
        scanf("%s", stu_list[i].name);
        
        printf("Year: ");
        scanf("%d", &stu_list[i].year);
        
        printf("Department Number: ");
        scanf("%d", &stu_list[i].d_num);
        
        printf("CGPA: ");
        scanf("%f", &stu_list[i].cgpa);
    }

    return stu_list;
}

int Display_info(student* stu_list, int n)
{
    printf("Students with CGPA >= 9.0:\n");
    for(int i = 0; i < n; i++)
    {
        if(stu_list[i].cgpa >= 9)
        {
            printf("Enrollment Number: %d\n", stu_list[i].e_num);
            printf("Name: %s\n", stu_list[i].name);
            printf("Year: %d\n", stu_list[i].year);
            printf("Department Number: %d\n", stu_list[i].d_num);
            printf("CGPA: %.2f\n", stu_list[i].cgpa);
            printf("\n");
        }
    }
}


int main()
{
    int n;
    student* stu_list = Read_Stu_info(&n);
    printf("\n");
    Display_info(stu_list, n);

    for(int i = 0; i < n; i++)
    {
        free(stu_list[i].name);
    }
    free(stu_list);

    return 0;
}
*/





// Reverse_String
/*
#include <stdio.h>

int reverse(char* str, int l)
{
    l--;
    char tmp;
    for (int i = 0; i <= l/2; i++)
    {
        tmp = str[l-i];
        str[l-i] = str[i];
        str[i] = tmp;
    }
}

int main()
{
    char str[50];
    scanf("%s", str);
    int l = 0;
    while(str[l] != 0) l++;
    
    reverse(str, l);
    printf("%s", str);
    
    return 0;
}
*/





// max from 2d array
/*
#include <stdio.h>

int find_max(int* array, int x, int y, int* co_ord)
{
    int max = 0;
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            if(array[(i*x)+j] > max)
            {
                max = array[(i*x)+j];
                co_ord[0] = i;
                co_ord[1] = j;
            }
        }
    }
    return max;
}

int main()
{
    int x, y;
    scanf("%d %d", &x, &y);

    int array[x][y];
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            // printf("%d, %d ---> ", i+1, j+1);
            scanf("%d", &array[i][j]);
        }
    }

    int co_ord[2];
    int max = find_max(&array[0][0], x, y, co_ord);

    printf("value: %d\n", max);
    printf("x: %d\n", co_ord[0]);
    printf("y: %d\n", co_ord[1]);

    return 0;
}
*/