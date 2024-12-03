#include <stdio.h>
#include <ctype.h>

int Sudoko[3][3][3][3];
int Candidate[9][3][3][3][3];
int Empty = 81;

int Print_Candidate()
{
    int value;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                for (int l = 0; l < 3; l++){
                    printf("[");
                    for (int e = 0; e < 9; e++){
                        printf("%d ", Candidate[e][i][k][j][l]);
                    }
                    printf("] ");
                }
                if (k!=2){
                    printf("| ");
                }
            }
            printf("\n");
        }
        if (i!=2){
            printf("- - - - - - - - - - -\n");
        }
    }
    printf("%i\n", Empty);
    return 0;
}

int Print_Sudoko()
{
    int value;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                for (int l = 0; l < 3; l++){
                    value = Sudoko[i][k][j][l];
                    if (value == 0){
                        printf("X ");
                    }
                    else{
                        printf("%i ", value);
                    }
                }
                if (k!=2){
                    printf("| ");
                }
            }
            printf("\n");
        }
        if (i!=2){
            printf("- - - - - - - - - - -\n");
        }
    }
    printf("%i\n", Empty);
    return 0;
}

int Check_Validity(int i,int j,int k,int l, int e)
{
    for (int a = 0; a < 3; a++){
        for (int b = 0; b < 3; b++){
            if (e == Sudoko[i][j][a][b]){
                return 2;
            }
            else if (e == Sudoko[i][a][k][b]){
                return 3;
            }
            else if (e == Sudoko[a][j][b][l]){
                return 4;
            }
        } 
    }
    return 1;
}

int Input_Validity(int v,int r,int c,int e)
{
    char correct;
    char in[512];
    // v != 3 || r>9 || r<1 || c>9 || c<1 || e>9 || e<1
    if (v==3 && r<10 && c<10 && e<10 && r>0 && c>0 && e>=0){
        int i, j, k, l;
        i = (r-1)/3;
        j = (c-1)/3;
        k = (r-1)%3;
        l = (c-1)%3;
        
        if (Sudoko[i][j][k][l] != 0){
            if (e == 0){
                Empty += 2;
                return 1;
            }
            printf("There is already a value in the cell.\n");
            printf("Do you want to add the value to it?[y/n]: ");
            while (1)
            {
                fgets(in, 512, stdin);
                correct = tolower(in[0]);
                if(correct == 'y'){
                    break;
                }
                else if(correct == 'n'){
                    printf("Not Added.\n");
                    return 5;
                }
                else{
                    printf("Incorrect! [y/n]: ");
                }
            }
        }

        if (e == Sudoko[i][j][k][l]){
            return 5;
        }

        return Check_Validity(i, j, k, l, e);
    }
    else if (v==3 && r==0 && c==0 && e==0){
        Print_Sudoko();
        printf("Is the Input Sudoko correct?[y/n]: ");
        while (1)
        {
            fgets(in, 512, stdin);
            correct = tolower(in[0]);
            if(correct == 'y'){
                return 0;
            }
            else if(correct == 'n'){
                return 5;
            }
            else{
                printf("Incorrect! [y/n]: ");
            }
        }
    }
    else{
        return 10;
    }
}

int Sudoko_Input()
{
    char input[512];
    int r, c, e, v;
    int i, j, k, l;
    int n = 1;

    printf("Enter value as showed below.\n");
    printf("Example: 2 5 4\n");

    while (n!=0)
    {
        printf("Enter '0 0 0' when finished.\n");
        printf("[Row Column Value]: ");

        fgets(input, 512, stdin);
        v = sscanf(input, "%i %i %i", &r, &c, &e);
        n = Input_Validity(v, r, c, e);

        switch (n)
        {
        case 0:
            break;
        case 1:
            i = (r-1)/3;
            j = (c-1)/3;
            k = (r-1)%3;
            l = (c-1)%3;
            Sudoko[i][j][k][l] = e;
            Empty -= 1;
            // printf("%i%i%i%i\n", i,j,k,l);
            Print_Sudoko();
            break;
        case 2:
            printf("There is similar value in the same box!\n");
            break;
        case 3:
            printf("There is similar value in the same row!\n");
            break;
        case 4:
            printf("There is similar value in the same column!\n");
            break;
        case 5:
            break;
        case 10:
            printf("Invalid Input!\n");
            break;
        
        default:
            printf("System Error!!\n");
            break;
        }
    }
    
    return 0;
}

int Remove_Candidates(int i,int j,int k,int l, int e)
{
    for (int a = 0; a < 3; a++){
        for (int b = 0; b < 3; b++){
            Candidate[e][i][j][a][b] = 0;
            Candidate[e][i][a][k][b] = 0;
            Candidate[e][a][j][b][l] = 0;
        } 
    }
    for (int m = 0; m < 9; m++){
        Candidate[m][i][j][k][l] = 0;
    }
    
    return 1;
}

int Set_Cell(int i,int j,int k,int l, int e)
{
    Sudoko[i][j][k][l] = e;
    Empty -= 1;
    Print_Sudoko();
    Remove_Candidates(i, j, k, l, e-1);
    return 1;
}

int Initiate_Candidates()
{
    int valid;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                for (int l = 0; l < 3; l++){
                    if (Sudoko[i][j][k][l] == 0){
                        for (int m = 0; m < 9; m++){
                            valid = Check_Validity(i, j, k, l, m+1);
                            if (valid == 1){
                                // printf("%i\n", Candidate[m][i][j][k][l]);
                                Candidate[m][i][j][k][l] = m+1;
                            }
                        }
                    }
                }
            }
        }
    }
}

int Check_Candidates(int i,int j,int k,int l, int e)
{
    if (Candidate[e][i][j][k][l] != 0){
        return 1;
    }
    return 0;
}

int Check_For_Single_Candidate()
{
    int no, value,  answered = 0;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                for (int l = 0; l < 3; l++){
                    if (Sudoko[i][j][k][l] == 0){
                        // printf("Found One\n");
                        no = 0;
                        for (int m = 0; m < 9; m++){
                            if (Candidate[m][i][j][k][l] != 0){
                                no += 1;
                                value = Candidate[m][i][j][k][l];
                            }
                            if (no >= 2){
                                break;
                            }
                        }
                        if (no == 1){
                            answered += Set_Cell(i, j, k, l, value); 
                        }
                    }
                }
            }
        }
    }
    return answered;
}

int Check_For_Sole_Valid_In_Box_Row_Col(int p)
{
    int k = 0, l = 0, n, answered = 0;
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int e = 1; e < 10; e++){
                k = 3, l = 3, n = 0;
                for (int a = 0; a < 3; a++){
                    for (int b = 0; b < 3; b++){
                        switch (p)
                        {
                        case 1:
                            n += Check_Candidates(i, j, a, b, e-1);
                            break;
                        case 2:
                            n += Check_Candidates(i, a, j, b, e-1);
                            break;
                        case 3:
                            n += Check_Candidates(a, i ,b, j, e-1);
                            break;
                        default:
                            printf("System Error!!!\n");
                            break;
                        }

                        if (n == 1 && k == 3 && l == 3){
                            k = a, l = b;
                        }
                        else if(n > 1){
                            a = 3, b = 3;
                        }
                    }
                }
                if (n == 1){
                    switch (p)
                    {
                    case 1:
                        answered += Set_Cell(i, j, k, l, e);
                        break;
                    case 2:
                        answered += Set_Cell(i, k, j, l, e);
                        break;
                    case 3:
                        answered += Set_Cell(k, i ,l, j, e);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
    return answered;
}

int Box_Line_Reduction()
{
    int b_r, b_c, r_b, c_b, removed = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int e = 0; e < 10; e++){
                b_r = 3, b_c = 3, r_b = 3, c_b = 3;
                for (int a = 0; a < 3; a++){
                    for (int b = 0; b < 3; b++){
                        // Box_Row/Col
                        if ((b_r != 4 || b_c != 4) && Candidate[e][i][j][a][b] != 0){
                            // Box_Row
                            if (b_r == 3){
                                b_r = a;
                            }
                            if (a != b_r){
                                b_r = 4;
                            }
                            // Box_Col
                            if (b_c == 3){
                                b_c = b;
                            }
                            if (b != b_c){
                                b_c = 4;
                            }
                        }
                        // Row_Box
                        if (r_b != 4 && Candidate[e][i][a][j][b] != 0){
                            if (r_b == 3){
                                r_b = a;
                            }
                            if (a != r_b){
                                r_b = 4;
                            }
                        }
                        // Col_Box
                        if (c_b != 4 && Candidate[e][a][i][b][j] != 0){
                            if (c_b == 3){
                                c_b = a;
                            }
                            if (a != c_b){
                                c_b = 4;
                            }
                        }
                    }
                }
                if (b_r < 3){
                    for (int k = 0; k < 3; k++){
                        for (int l = 0; l < 3; l++){
                            if (k == j){
                                k += 1;
                            }
                            if (Candidate[e][i][k][b_r][l] != 0){                            
                                Candidate[e][i][k][b_r][l] = 0;
                                removed += 1;
                            }
                        }
                    }
                }
                if (b_c < 3){
                    for (int k = 0; k < 3; k++){
                        for (int l = 0; l < 3; l++){
                            if (k == i){
                                k += 1;
                            }
                            if (Candidate[e][k][j][l][b_c] != 0){                            
                                Candidate[e][k][j][l][b_c] = 0;
                                removed += 1;
                            }
                        }
                    }
                }
                if (r_b < 3){
                    for (int k = 0; k < 3; k++){
                        for (int l = 0; l < 3; l++){
                            if (k == j){
                                k += 1;
                            }
                            if (Candidate[e][i][r_b][k][l] != 0){                            
                                Candidate[e][i][r_b][k][l] = 0;
                                removed += 1;
                            }
                        }
                    }
                }
                if (c_b < 3){
                    for (int k = 0; k < 3; k++){
                        for (int l = 0; l < 3; l++){
                            if (l == j){
                                l += 1;
                            }
                            if (Candidate[e][c_b][i][k][l] != 0){                            
                                Candidate[e][c_b][i][k][l] = 0;
                                removed += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return removed;
}

int Solve_Sudoko()
{
    Initiate_Candidates();
    int n;
    while(Empty > 0)
    {
        printf("Called\n");
        n = 0;
        n += Check_For_Single_Candidate();
        if (n > 0){
            continue;
        }

        for (int i = 1; i < 4; i++){
            n += Check_For_Sole_Valid_In_Box_Row_Col(i);
        }
        if (n > 0){
            continue;
        }

        n += Box_Line_Reduction();
        if (n > 0){
            continue;
        }


        if (n == 0){
            break;
        }
    }
    
    return 0;
}

int main()
{
    Sudoko_Input();
    Solve_Sudoko();
    printf("Solved\n");
    Print_Sudoko();
    // Print_Candidate();


    return 0;
}