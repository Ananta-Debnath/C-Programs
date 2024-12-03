#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int valid = 1;
char Answer[64];

double To_Decimal(char Input[], int Base)
{
    double decimal = 0;
    int n, process = 1, valid = 1;
    int power = 0;
    char in;

    for (int i = 0; i < 32; i++)
    {
        in = Input[i];
        // printf("%i", in);

        if (in == 46){
            process = 2;
            // printf("dot");
        }
        else if (in >= 48 && in < 48 + Base){
            n = in - 48;
            // printf("%i", n);
        }
        else if (in >= 65 && in < 55 + Base){
            n = in - 55;
            // printf("%i", n);
        }
        else if (in >= 97 && in < 87 + Base){
            n = in - 87;
            // printf("%i", n);
        }
        else if (in == 0){
            // printf("End");
            break;
        }
        else{
            valid = 0;
            return 0;
        }


        if (!(in == 46)){
            if (process == 1)
            {
                decimal = (decimal * Base) + n;
            }
            else if (process == 2)
            {
                power -= 1;
                decimal += pow(Base, power) * n;
            }
        }

    }
    
    return decimal;
}

int From_Decimal(double Decimal, int Base)
{
    int Before_Radix = floor(Decimal);
    double After_Radix = Decimal - Before_Radix;
    int digit_no = 0;
    int digit;
    char reversed[32];

    int n = Before_Radix;
    while (n != 0)
    {
        digit = n % Base;
        n = floor(n/Base);

        if (digit <= 9){
            digit += 48;
        }
        else if (digit > 9){
            digit += 55;
        }
        reversed[digit_no] = digit;
        digit_no += 1;
    }
    
    for (int i = 0; i < digit; i++)
    {
        Answer[i] = reversed[digit_no - 1 - i];
    }

    Answer[digit_no] = '.';
    digit_no += 1;

    double m = After_Radix;
    for (int i = 0; i < 8; i++)
    {
        m = m * Base;
        digit = floor(m);
        m -= digit;
        if (digit <= 9){
            digit += 48;
        }
        else if (digit > 9){
            digit += 55;
        }
        Answer[digit_no] = digit;
        digit_no += 1;
    }
    
    return 0;
}

int main()
{
    char input[32], number[32];
    int base, run = 1;

    while (run == 1)
    {
        printf("Enter Base: ");
        fgets(input, 32, stdin);
        sscanf(input, "%i", &base);

        printf("Enter Number: ");
        fgets(input, 32, stdin);
        sscanf(input, "%s", &number);

        double decimal = To_Decimal(number, base);

        if (valid == 1)
        {
            printf("Enter Answer Base: ");
            fgets(input, 32, stdin);
            sscanf(input, "%i", &base);
            
            From_Decimal(decimal, base);
            printf("Answer = %s\n", Answer);
        }
        else if (valid == 0)
        {
            printf("Invalid Number!\n");
        }

        while(1)
        {
            printf("Any more task?[y/n]: ");
            fgets(input, 32, stdin);
            if (tolower(input[0]) == 'y'){
                run = 1;
                break;
            }
            else if (tolower(input[0]) == 'n'){
                run = 0;
                break;
            }
            else{
                printf("Incorrect input!\n");
            }
        }
    }
    
    return 0;
}
