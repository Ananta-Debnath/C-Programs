
int caesar_decrypt(char a[], int shift)
{
    int l = str_len(a);
    for (int i = 0; i < l; i++)
    {
        if (a[i] >= 'A' && a[i] <= 'Z')
            a[i] = ((a[i] - 'A' - shift) % 26) + 'A';

        else if (a[i] >= 'a' && a[i] <= 'z')
            a[i] = ((a[i] - 'a' - shift) % 26) + 'a';
    }
    return 0;
}
