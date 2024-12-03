#include <stdio.h>

void print_byte_as_binary(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%c", (byte & (1 << i)) ? '1' : '0');
    }
    printf("\n");
}

int main()
{
    FILE *pic = fopen("pic.jpg", "r");
    printf("%p\n\n\n", pic);

    if (pic == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    unsigned char *num = (char*)pic;

    for(int i = 0; i < 100; i++){
        // print_byte_as_binary(num[i]);
        if(i%3 == 0) printf("\n%i: ", i/3);
        printf("%02x", num[i + 10000]);
    }

    return 0;
}