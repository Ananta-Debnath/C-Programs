#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const char anagram_word_1[] = "listen";
const char anagram_word_2[] = "earth";
const char anagram_word_3[] = "binary";

const char cipher_line_1[] = "There is a secret code";
const char cipher_line_2[] = "Attack at dawn";
const char cipher_line_3[] = "Meet me at the park";

const char guess_word_1[] = "program";
const char guess_word_2[] = "network";
const char guess_word_3[] = "science";


int str_len(const char a[])
{
    int n = 0;
    while (1)
    {
        if (a[n] == 0) return n;
        n++;
    }
}

int str_cmp(const char a[], const char b[])
{
    int n = 0;
    while (a[n] == b[n])
    {
        if (a[n] == 0) return 0;
        n++;
    }
    return a[n] - b[n];
}

int str_cpy(char t[], const char a[])
{
    int n = 0;
    while (a[n] != 0)
    {
        t[n] = a[n];
        n++;
    }
    t[n] = 0;
    return n;
}

void obtain_string(char a[], int game)
{
    int k = ((rand() % 3) + 1) + (3 * (game-1));

    switch (k)
    {
    case 1:
        str_cpy(a, anagram_word_1);
        break;
    
    case 2:
        str_cpy(a, anagram_word_2);
        break;
    
    case 3:
        str_cpy(a, anagram_word_3);
        break;

    case 4:
        str_cpy(a, cipher_line_1);
        break;
        
    case 5:
        str_cpy(a, cipher_line_2);
        break;
        
    case 6:
        str_cpy(a, cipher_line_3);
        break;
    
    case 7:
        str_cpy(a, guess_word_1);
        break;
        
    case 8:
        str_cpy(a, guess_word_2);
        break;
        
    case 9:
        str_cpy(a, guess_word_3);
        break;
    
    default:
        break;
    }
}

int show_menu()
{
    printf("Welcome to the Game World!\n");
    printf("1. Start Game\n");
    printf("2. Exit\n");
    int n = 0;
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &n);
        while (getchar() != '\n');
        if (n == 1 || n == 2) break;
        printf("Select a valid option!\n");
    }
    return n;
}

int anagram_scrambler(char a[])
{
    int l = str_len(a);
    int idx;
    char tmp;
    for (int i = 0; i < 15; i++)
    {
        idx = rand() % l;
        tmp = a[0];
        a[0] = a[idx];
        a[idx] = tmp;
    }
    return 0;
}

int anagram_challenge()
{
    printf("Starting Anagram Challenge...\n");

    char anagram_word[10], a[10];
    int k = (rand() % 3) + 1;
    obtain_string(anagram_word, 1);
    
    str_cpy(a, anagram_word);
    anagram_scrambler(a);
    printf("Scrambled word: %s\n", a);

    int n = 0, invalid = 1;
    char in[10];
    while (n < 3)
    {
        n++;
        in[0] = 0;
        printf("Your Guess: ");
        gets(in);
        invalid = str_cmp(in, anagram_word);
        if (invalid == 0 || n == 3) break;
        printf("Incorrect! Try again.\n");
    }

    int score = 0;
    if (invalid == 0)
    {
        printf("Correct! You solved it in %d attempt(s).\n", n);
        score = 10 + 10*(3-n);
    }
    else printf("No attempts left!\nThe correct answer was '%s'.\n", anagram_word);
    printf("\n\n");

    return score;
}

int caesar_encrypt(char a[], int shift)
{
    int l = str_len(a);
    for (int i = 0; i < l; i++)
    {
        if (a[i] >= 'A' && a[i] <= 'Z')
            a[i] = ((a[i] - 'A' + shift) % 26) + 'A';

        else if (a[i] >= 'a' && a[i] <= 'z')
            a[i] = ((a[i] - 'a' + shift) % 26) + 'a';
    }
    return 0;
}

int caesar_decrypt(char a[], int shift)
{
    caesar_encrypt(a, 26-shift);
    return 0;
}

int caeser_cipher_challange()
{
    int shift = 3;
    // shift += rand() % 5; // un-comment this to add randomness
    printf("Starting Caesar Cipher Challenge (Shift: %d)...\n", shift);

    int k = (rand() % 3) + 1;
    char cipher_line[30];
    obtain_string(cipher_line, 2);

    caesar_encrypt(cipher_line, shift);
    printf("Encrypted phrase: %s\n", cipher_line);
    caesar_decrypt(cipher_line, shift);

    int n = 0, invalid = 1;
    char in[30];
    while (n < 3)
    {
        n++;
        in[0] = 0;
        printf("Your Guess: ");
        gets(in);
        invalid = str_cmp(in, cipher_line);
        if (invalid == 0 || n == 3) break;
        printf("Incorrect! Try again.\n");
    }

    int score = 0;
    if (invalid == 0)
    {
        printf("Correct! You decrypted it in %d attempt(s).\n", n);
        score = 10 + 10*(3-n);
    }
    else printf("No attempts left!\nThe correct answer was '%s'.\n", cipher_line);
    printf("\n\n");

    return score;
}

int check_substring(char a[], char t[])
{
    int l = str_len(a);
    int n;

    for (int i = 0; i < l; i++)
    {
        n = 0;
        while (a[i+n] == t[n])
        {
            n++;
            if (t[n] == 0) return 1;
        }
    }
    return 0;
}

int word_guessing_challange()
{
    printf("Starting Word Guessing Challenge...\n");

    int utility[4] = {0};

    int k = (rand() % 3) + 1;
    char guess_word[10];
    obtain_string(guess_word, 3);

    printf("Hint: ");
    for (int i = 0; i < 3; i++) printf("%c", guess_word[i]);
    printf("_______\n");

    printf("Select an option:\n");
    printf("1. Write Answer\n");
    printf("2. Check Substring\n");
    printf("3. Check Length\n");

    int n = 0, p, invalid = 1;
    char in[10];
    while (n < 3 && invalid != 0)
    {
        p = 0;
        printf("Your option: ");
        scanf("%d", &p);
        while (getchar() != '\n');

        if (!(p < 4 && p > 0))
        {
            printf("Select a valid option!\n");
            continue;
        }
        if (utility[p] != 0)
        {
            printf("Error: Utility function already used.\n");
            continue;
        }

        in[0] = 0;
        switch (p)
        {
        case 1:
            n++;
            printf("Enter your Guess: ");
            gets(in);
            invalid = str_cmp(in, guess_word);
            if (invalid == 0 || n == 3) break;
            printf("Incorrect! Try again.\n");
            break;

        case 2:
            utility[p] = 1;
            printf("Enter substring: ");
            gets(in);
            if (check_substring(guess_word, in) == 1) printf("Yes!\n");
            else printf("No!\n");
            break;

        case 3:
            utility[p] = 1;
            printf("Enter length: ");
            int l;
            scanf("%d", &l);
            while (getchar() != '\n');
            if (l == str_len(guess_word)) printf("Yes!\n");
            else printf("No!\n");
            break;
        
        default:
            printf("Fatal Error!!!\n");
            break;
        }
    }

    int util_used = 0;
    for (int i = 0; i < 4; i++) util_used += utility[i];
    int score = 0;
    if (invalid == 0)
    {
        printf("Correct! You guessed it in %d attempt(s) using %d utility function(s).\n", n, util_used);
        score = 10 + 10*(3-n) - 2*util_used;
    }
    else printf("No attempts left!\nThe correct answer was '%s'.\n", guess_word);
    printf("\n\n");

    return score;
}


int main()
{
    srand(time(NULL));
    int score = 0;
    int k, passed = 0;

    // Menu Display
    k = show_menu();
    if (k == 2) return 0;

    // Anagram
    k = anagram_challenge();
    if (k > 0) passed++;
    score += k;

    // Caeser Cipher
    k = caeser_cipher_challange();
    if (k > 0) passed++;
    score += k;

    // Word Guessing
    k = word_guessing_challange();
    if (k > 0) passed++;
    score += k;

    if (passed == 3) score += 5;

    printf("Game Over!\n");
    printf("Your total score: %d points.\n", score);

    // getchar();
    return 0;
}