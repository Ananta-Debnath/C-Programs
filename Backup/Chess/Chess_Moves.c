#include <stdio.h>
#include <string.h>

int main() {
    FILE *fptr;
    

    fptr = fopen("Chess_Moves.txt", "r");
    if (fptr == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    fseek(fptr, 0L, SEEK_END);
    long size = ftell(fptr);
    fseek(fptr, 0L, 0);

    char line[size]; // Adjust the buffer size as needed

    for (int i = 0; i < size; ++i) {
        if (line[i] == ' ') {
            line[i] = '\n';
        }
        else if(line[i] == '\0'){
            fgets(&line[i], size, fptr);
        }
    }
    fclose(fptr);

    fptr = fopen("Chess_Moves.txt", "a");
    char final[size], p;
    int i = 2, v = 0, j = 0;
    while(line[i] != 0){
        p = line[i];
        if(p == '.' || p == '+' || p == '#'){
        }
        else if(v == 1 && ((p >= '0' && p <= '9') || p == '\n')){
        }
        else
        {
            v = 0;
            if(p == '\n'){
                v = 1;
            }
            final[j] = p;
            j++;
        }

        i++;
    }

    fprintf(fptr, '\n');
    fprintf(fptr, final);

    fclose(fptr);
    printf("Spaces replaced with newlines in the file.\n");
    return 0;
}
