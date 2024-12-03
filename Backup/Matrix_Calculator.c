#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int Mat_num = 0;
int Dimensions[20][2];
double Mat_List[20][100][100];
int c_mat_dim[3][2];
double c_mat[3][100][100];

int Instruction(int sl)
{
    if (sl == 1)
    {
        printf("Enter 'i' for matrix input\n");
        printf("Enter 'c' for calculator\n");
        printf("Enter 'q' to exit\n");
    }

    if (sl == 2)
    {
        printf("m --> Matrix\n");
        printf("t --> Transpose\n");
        printf("c --> Co-factor\n");
        printf("a --> Adjoint\n");
        printf("i --> Inverse\n");
        printf("d --> Determinant\n");
        printf("! --> User Manual\n");
        printf("Input Example: t1\n");
    }
}

int Clear_c_mat(int dest)
{
    int row = c_mat_dim[dest][0];
    int column = c_mat_dim[dest][1];

    for (int i = 0; i < 2; i++){
        c_mat_dim[dest][i] = 0;
    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            c_mat[dest][i][j] = 0;
            // printf("%.2f,%.2f\n", c_mat[0][i][j], c_mat[1][i][j]);
        }
    }

    return 0;
}

int Clear_Calculator()
{
    for (int i = 0; i < 3; i++){
        Clear_c_mat(i);
    }
    return 0;
}

int Save_Answer_in_Mat_List()
{
    char input[512];
    char y_n;
    printf("Save the answer in the list?[y/n]: ");
    while (1)
    {
        fgets(input, 512, stdin);
        y_n = tolower(input[0]);
        if (y_n == 'y')
        {
            int Matrix = Mat_num + 1;
            Dimensions[Matrix][0] = Dimensions[0][0];
            Dimensions[Matrix][1] = Dimensions[0][1];
            // printf("%i,%i", Dimensions[Matrix][0], Dimensions[Matrix][1]);
            for(int i = 0; i < Dimensions[0][0]; i++){
                for(int j = 0; j < Dimensions[0][1]; j++){
                    Mat_List[Matrix][i][j] = Mat_List[0][i][j];
                    // printf(" %.2lf  ", Mat_List[Matrix][i][j]);
                }
                // printf("\n");
            }
            Mat_num += 1;
            break;
        }
        else if (y_n == 'n')
        {
            break;
        }
        else
        {
            printf("Invalid Input![y/n]: ");
        }
    }
    return 0;
}

int Save_Answer(int row, int column, double Answer[100][100])
{
    for(int i = 0; i < Dimensions[0][0]; i++){
        for(int j = 0; j < Dimensions[0][1]; j++){
            Mat_List[0][i][j] = 0;
        }
    }

    Dimensions[0][0] = row;
    Dimensions[0][1] = column;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            Mat_List[0][i][j] = Answer[i][j];
            // printf("%.2f,%.2f\n", Answer[i][j], Mat_List[0][i][j]);
        }
    }
    if (row != 1 || column != 1)
    {
        Save_Answer_in_Mat_List();
    }
    return 0;
}

int Add_or_Subtract(int Task)
{
    if (c_mat_dim[0][0] == c_mat_dim[1][0] && c_mat_dim[0][1] == c_mat_dim[1][1])
    {
        int row = c_mat_dim[0][0];
        int column = c_mat_dim[0][1];
        // printf("%lf,%lf\n", row, column);
        double answer[100][100];

        for (int i = 0; i < row; i++){
            for (int j = 0; j < column; j++){
                if (Task == 0){
                    answer[i][j] = c_mat[0][i][j] + c_mat[1][i][j];
                }else if (Task == 1){
                    answer[i][j] = c_mat[0][i][j] - c_mat[1][i][j];
                }else{
                    printf("Something is wrong!\n");
                }
                
                printf("  %.2f   ", answer[i][j]);
            }
            printf("\n");
        }

        Save_Answer(row, column, answer);

        for (int i = 0; i < row; i++){
            for (int j = 0; j < column; j++){
                answer[i][j] = 0;
            }
        }
    }
    else{
        printf("The two matrixes have different dimensions!\n");
    }
    return 0;
}

int Scalar_Multiply(double scalar, int sl)
{
    int row = c_mat_dim[sl][0];
    int column = c_mat_dim[sl][1];
    double answer[100][100];
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            answer[i][j] = scalar * c_mat[sl][i][j];
            printf("  %.2f   ", answer[i][j]);
        }
        printf("\n");
    }
    Save_Answer(row, column, answer);
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            answer[i][j] = 0;
        }
    }
    return 0;
}

int Multiply()
{
    if (c_mat_dim[0][1] == c_mat_dim[1][0])
    {
        int row = c_mat_dim[0][0];
        int column = c_mat_dim[1][1];
        int elemants = c_mat_dim[0][1];
        double answer[100][100];

        for (int i = 0; i < row; i++){
            for (int j = 0; j < column; j++){
                for (int k = 0; k < elemants; k++){
                    answer[i][j] += c_mat[0][i][k] * c_mat[1][k][j];
                }
                printf("  %.2f   ", answer[i][j]);
            }
            printf("\n");
        }

        Save_Answer(row, column, answer);

        for (int i = 0; i < row; i++){
            for (int j = 0; j < column; j++){
                answer[i][j] = 0;
            }
        }
    }
    else{
        if (c_mat_dim[0][0] == 1 && c_mat_dim[0][1] == 1){
            Scalar_Multiply(c_mat[0][0][0], 1);
        }
        else if (c_mat_dim[1][0] == 1 && c_mat_dim[1][1] == 1){
            Scalar_Multiply(c_mat[0][1][0], 0);
        }
        else{
            printf("Condition not fulfilled!\n");
        }
    }
    return 0;
}

int Equal()
{
    int row = c_mat_dim[0][0];
    int column = c_mat_dim[0][1];

    for (int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            printf("  %.2f   ", c_mat[0][i][j]);
        }
        printf("\n");
    }
    Save_Answer(row, column, c_mat[0]);
    return 0;
}

int Save_Matrix_for_Calculator(int dest, int row, int column, double Matrix[100][100])
{
    c_mat_dim[dest][0] = row;
    c_mat_dim[dest][1] = column;

    for (int i = 0; i < c_mat_dim[dest][0]; i++){
        for (int j = 0; j < c_mat_dim[dest][1]; j++){
            c_mat[dest][i][j] = Matrix[i][j];
        }
    }
    return 0;
}

int Transpose(int dest, int row, int column, double Matrix[100][100])
{
    c_mat_dim[dest][0] = column;
    c_mat_dim[dest][1] = row;

    for (int i = 0; i < c_mat_dim[dest][0]; i++){
        for (int j = 0; j < c_mat_dim[dest][1]; j++){
            c_mat[dest][i][j] = Matrix[j][i];
        }
    }
    return 0;
}

double Determinant(int dim, double Matrix[100][100])
{
    double a, sign, answer;
    double minor[100][100];

    for (int k = 0; k < dim; k++){
        for (int i = 0; i < dim - 1; i++){
            for (int j = 0; j < dim - 1; j++){
                if(j < k){
                    minor[i][j] = Matrix[i + 1][j];
                }
                else if(j >= k){
                    minor[i][j] = Matrix[i + 1][j + 1];
                }
                // printf("  %.2f   ", minor[i][j]);
            }
            // printf("\n");
        }

        sign = pow(-1, k + 2);
        if(dim == 1){
            a = sign * Matrix[0][0];
            answer = a;
        }
        else{
            a = sign * Determinant(dim - 1, minor);
            answer += Matrix[0][k] * a;
        }
        // printf("%.2f\n", a);
        // printf("%.2f\n", answer);
    }

    return answer;
}

int Cofactor_Matrix(int dest, int dim, double Matrix[100][100])
{
    c_mat_dim[dest][0] = dim;
    c_mat_dim[dest][1] = dim;
    double minor[100][100];

    for (int i = 0; i < c_mat_dim[dest][0]; i++){
        for (int j = 0; j < c_mat_dim[dest][1]; j++){
            int p, q = 0;
            for (int x = 0; x < c_mat_dim[dest][0] - 1; x++){
                for (int y = 0; y < c_mat_dim[dest][1] - 1; y++){
                    p = x;
                    q = y;
                    if (x >= i){
                        p = x + 1;
                    }
                    if (y >= j){
                        q = y + 1;
                    }

                    minor[x][y] = Matrix[p][q];
                }
            }
            c_mat[dest][i][j] = pow(-1, i + j) * Determinant(dim - 1, minor);
        }
    }
    return 0;
}

int Adjoint_Matrix(int dest, int dim, double Matrix[100][100])
{
    Cofactor_Matrix(2, dim, Matrix);
    Transpose(dest, dim, dim, c_mat[2]);
    return 0;
}

int Inverse_Matrix(int dest, int dim, double Matrix[100][100], double d)
{
    Adjoint_Matrix(dest, dim, Matrix);
    c_mat_dim[dest][0] = dim;
    c_mat_dim[dest][1] = dim;
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            c_mat[dest][i][j] = c_mat[dest][i][j] / d;
        }
    }
    return 0;
}

int Mat_Element_Input(int Matrix)
{
    char c[512];
    int v;
    int row = Dimensions[Matrix][0];
    int column = Dimensions[Matrix][1];
    double Temp_Mat[row][column];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("[%i x %i]: ", i + 1, j + 1);
            do
            {
                fgets(c, 512, stdin);
                v = sscanf(c, "%lf", &Temp_Mat[i][j]);
                if (v != 1)
                {
                    printf("Invalid Input!\n[%i x %i]: ", i+1, j+1);
                }
            } while (v != 1);
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("  %.2f   ", Temp_Mat[i][j]);
        }
        printf("\n");
    }

    printf("Is the matrix correct?[y/n]: ");
    char correct;
    while (1)
    {
        fgets(c, 512, stdin);
        correct = tolower(c[0]);
        if(correct == 'y')
        {
            for (int i = 0; i < row; i++){
                for (int j = 0; j < column; j++){
                    Mat_List[Matrix][i][j] = Temp_Mat[i][j];
                }
            }
            Mat_num += 1;
            // printf("Success\n");
            break;
        }
        else if(correct == 'n')
        {
            printf("Deleted!\n");
            break;
        }
        else
        {
            printf("Incorrect! [y/n]: ");
        }
    }
    return 0;
}

int Mat_Input(int Matrix)
{
    int a, b, v = 0;
    char valid;
    char c[512];

    printf("[Row, Column]: ");
    do
    {
        valid = 'y';
        fgets(c, 512, stdin);
        v = sscanf(c, "%i,%i", &a, &b);
        if (v != 2 || a < 1 || b < 1 || (a == 1 && b == 1))
        {
            printf("Invalid Input!\nEnter positive integars!!\n[Row, Column]: ");
            valid = 'n';
        }
    } while (valid == 'n');

    Dimensions[Matrix][0] = a;
    Dimensions[Matrix][1] = b;
    // printf("%i, %i\n", Dimensions[Matrix][0], Dimensions[Matrix][1]);

    Mat_Element_Input(Matrix);

    return 0;
}

int Obtain_Mat_for_Calulator(char c_command, char c_input[512], char* valid_input, int dest)
{
    *valid_input = 'y';
    int mat_sl = -2;

    if (isdigit(c_command) != 0)
    {
        c_mat[dest][0][0] = atof(c_input);
        c_mat_dim[dest][0] = 1;
        c_mat_dim[dest][1] = 1;
        c_command = 'q';
    }
    else if (isdigit(c_input[1]) != 0){
        c_input[0] = '0';
        mat_sl = atoi(c_input);
    }

    int row = Dimensions[mat_sl][0];
    int column = Dimensions[mat_sl][1];

    switch (c_command)
    {
        case 'q':
            break;
        case 'm':
            if (mat_sl >= 0 && mat_sl <= Mat_num){
                Save_Matrix_for_Calculator(dest, row, column, Mat_List[mat_sl]);
            }
            else{
                printf("Invalid Input!\n");
                *valid_input = 'n';
            }
            break;
        case 't':
            if (mat_sl >= 0 && mat_sl <= Mat_num){
                Transpose(dest, row, column, Mat_List[mat_sl]);
            }
            else{
                printf("Invalid Input!\n");
                *valid_input = 'n';
            }
            break;
        case 'c':
            if (mat_sl >= 0 && mat_sl <= Mat_num && row == column){
                Cofactor_Matrix(dest, row, Mat_List[mat_sl]);
            }
            else{
                printf("It isn't a square matrix!\n");
                *valid_input = 'n';
            }
            break;
        case 'a':
            if (mat_sl >= 0 && mat_sl <= Mat_num && row == column){
                Adjoint_Matrix(dest, row, Mat_List[mat_sl]);
            }
            else{
                printf("It isn't a square matrix!\n");
                *valid_input = 'n';
            }
            break;
        case 'i':
            if (mat_sl >= 0 && mat_sl <= Mat_num && row == column){
                double d = Determinant(row, Mat_List[mat_sl]);
                if (d != 0){
                    Inverse_Matrix(dest, row, Mat_List[mat_sl], d);
                }
                else{
                    printf("It is an Exceptional Matrix!");
                    *valid_input = 'n';
                }
            }
            else{
                printf("It isn't a square matrix!\n");
                *valid_input = 'n';
            }
            break;
        case 'd':
            if (mat_sl >= 0 && mat_sl <= Mat_num && row == column)
            {
                c_mat_dim[dest][0] = 1;
                c_mat_dim[dest][1] = 1;
                c_mat[dest][0][0] = Determinant(row, Mat_List[mat_sl]);
            }
            else{
                printf("It isn't a square matrix!\n");
                *valid_input = 'n';
            }
            break;
        case '!':
            Instruction(2);
            break;
        
        default:
            printf("Invalid Input!\n");
            *valid_input = 'n';
            break;
    }

    return 0;
}

int Calculator()
{
    char c_command = '0';
    Instruction(2);
    while (c_command != 'q')
    {
        Clear_Calculator();
        char c_input[512] = "n";
        char valid_input = 'y';
        char operator = 'n';
        char op[] = "+-*/=";
        char valid_op = 'n';

        do
        {
            printf("Enter First Input: ");
            fgets(c_input, 512, stdin);
            c_command = tolower(c_input[0]);
            Obtain_Mat_for_Calulator(c_command, c_input, &valid_input, 0);
        } while (valid_input == 'n');

        if (c_command == 'q'){
            break;
        }
        Clear_c_mat(2);

        do
        {
            printf("Enter Operator: ");
            fgets(c_input, 512, stdin);
            operator = c_input[0];
            for (size_t i = 0; i < strlen(op); i++)
            {
                if (operator == op[i])
                {
                    valid_op = 'y';
                    break;
                }
            }
            if (valid_op == 'n')
            {
                printf("Invalid Operator!\n");
            }
        } while (valid_op == 'n');
        
        if (operator != '=')
        {
            do
            {
                printf("Enter Second Input: ");
                fgets(c_input, 512, stdin);
                c_command = tolower(c_input[0]);
                Obtain_Mat_for_Calulator(c_command, c_input, &valid_input, 1);
            } while (valid_input == 'n');
        }

        switch (operator)
        {
        case '=':
            Equal();
            break;
        case '+':
            Add_or_Subtract(0);
            break;
        case '-':
            Add_or_Subtract(1);
            break;
        case '*':
            Multiply();
            break;
        
        default:
            break;
        }
    }

    return 0;
}

int main()
{
    Instruction(1);
    int quit = 0;
    while (quit == 0)
    {
        char input[512] = "0";
        char command = '0';

        printf("Enter Command: ");
        fgets(input, 512, stdin);
        sscanf(input, "%c", &command);

        switch(tolower(command))
        {
            case 'q':
                quit = 1;
                break;
            case 'c':
                Calculator();
                break;
            case 'i':
                Mat_Input(Mat_num + 1);
                break;
            case '!':
                Instruction(1);
                break;
            default:
                printf("Invalid Command!\n");
        }
    }

    return 0;
}
