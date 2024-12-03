#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

char*** suggestedProducts(char** products, int productsSize, char* searchWord, int* returnSize, int** returnColumnSizes) {
    char first = searchWord[0];

    for(int i = 0, j = 0; i < productsSize; i++)
    {
        if(products[i][0] == first)
        {
            
        }
    }
}




char ** commonChars(char ** words, int wordsSize, int* returnSize){
    int minFreq[26];
    for (int i = 0; i < 26; i++)
    {
        minFreq[i] = INT_MAX;
    }

    for (int i = 0; i < wordsSize; i++)
    {
        int* freq = (int*) calloc(26, sizeof(int));
        int j = 0;
        while (words[i][j] != 0)
        {
            freq[words[i][j] - 'a'] += 1;
            j++;
        }

        for (int k = 0; k < 26; k++)
        {
            if (minFreq[k] > freq[k])
            {
                minFreq[k] = freq[k];
            }
        }
        free(freq);
    }

    *returnSize = 0;
    char** result = (char**)malloc(sizeof(char*));
    for (int i = 0; i < 26; i++)
    {
        for(int j = 0; j < minFreq[i]; j++)
        {
            result = (char**)realloc(result, (*returnSize + 1) * sizeof(char*));
            result[*returnSize] = (char*)malloc(2 * sizeof(char));
            result[*returnSize][0] = i + 'a';
            result[*returnSize][1] = 0;
            *returnSize += 1;
        }
    }

    return result;
}

int b_search(int* bloomDay, int bloomDaySize, int m, int k, int* bloomSort)
{
    int low = 0;
    int high = bloomDaySize - 1;
    int mid, p;

    do
    {
        mid = low + (high - low) / 2;
        // p = check(bloomDay, bloomDaySize, m, k, bloomSort[mid]);

        if (p == 1)
            low = mid + 1;

        else if(p == -1)
            high = mid;
            
    }while (mid != low);

    return high;
}


struct ListNode
{
    int val;
    struct ListNode *next;
};

int* nodesBetweenCriticalPoints(struct ListNode* head, int* returnSize) {
    int a, b, c;
    struct ListNode* ptr = head;
    a = ptr->val;
    ptr = ptr->next;
    b = ptr->val;
    ptr = ptr->next;
    c = b;
    if (ptr != NULL)
    {
        c = ptr->val;
        ptr = ptr->next;
    }

    int* dist = (int*)malloc(2 * sizeof(int));
    dist[0] = INT_MAX;
    dist[1] = 0;
    int ini = 0, final = 0, d = -1;
    while (1)
    {
        if ((b > a && b > c) || (b < a && b < c))
        {
            if (ini == 0)
            {
                ini = final;
            }
            else
            {
                d = final - ini;
                ini = final;
                if (d < dist[0])
                {
                    dist[0] = d;
                }
                dist[1] += d;
            }
        }

        if (ptr == NULL)
        {
            break;
        }
        else
        {
            a = b;
            b = c;
            c = ptr->val;
            ptr = ptr->next;
        }
        final++;
    }

    if(dist[0] == INT_MAX) dist[0] = -1;
    if(dist[1] == 0) dist[1] = -1;

    return dist;
}


long long dividePlayers(int* skill, int skillSize) {
    long long sum = 0;
    for (int i = 0; i < skillSize; i++) sum += skill[i];

    if (sum % (skillSize/2)) return -1;

    int cSum = sum / (skillSize/2);
    sum = 0;
    // int v;

    for (int i = 0; i < skillSize; i++)
    {
        if (skill[i] == -cSum) continue;
        // v = 0;
        for (int j = i+1; j < skillSize; j++)
        {
            if (skill[i] + skill[j] == cSum)
            {
                sum += skill[i] * skill[j];
                skill[j] = -cSum;
                // v = 1;
                break;
            }
        }
        // if (v == 0) return -1;
    }

    return sum;
}


char* compressedString(char* word) {
    char* comp = malloc(20*8);
    int a = 0;
    int n = 0;
    int k;
    char c;
    while (word[n] != 0)
    {
        k = 0;
        c = word[n];
        while (word[n] == c && k <= 9)
        {
            k++;
            n++;
        }
        comp = realloc(comp, (a+3)*sizeof(char));
        comp[a] = k + '0';
        comp[a+1] = c;
        a += 2;
    }
    comp[a] = 0;


    return comp;
}







/*
int main()
{
    char word[] = "abcde";
    char* comp = compressedString(word);
    printf("%s", comp);
}


int main()
{
    int skill[] = {2, 2, 2, 2};
    int n = dividePlayers(skill, sizeof(skill)/sizeof(int));
    printf("%d\n", n);
}


int main()
{
    int n;
    printf("Number of Elements: ");
    scanf("%d", &n);
    struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));;
    struct ListNode* ptr = tmp;
    
    for (int i = 0; i < n; i++)
    {
        ptr->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        ptr = ptr->next;
        ptr->next = NULL;
        printf("Number %d: ", i + 1);
        scanf("%d", &(ptr->val));
    }
    struct ListNode* head = tmp->next;
    free(tmp);

    int* dist = nodesBetweenCriticalPoints(head, &n);
    
    printf("%d %d\n", dist[0], dist[1]);

    return 0;
}
*/