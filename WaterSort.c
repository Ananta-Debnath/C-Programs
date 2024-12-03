#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printBottles(int** bottles, int bottleNum, int perBottle, char** colors)
{
    for (int i = 0; i < bottleNum; i++)
    {
        printf("%d -> ", i+1);
        for (int j = 0; j < perBottle; j++)
        {
            printf("%s | ", colors[bottles[i][j]]);
        }
        printf("\n");
    }
}

int randomizeBottles(int** bottles, int bottleNum, int perBottle)
{
    int colorNum = bottleNum - 2;
    for (int i = 0; i < colorNum; i++)
    {
        for (int j = 0; j < perBottle; j++)
        {
            bottles[i][j] = i + 1;
        }
    }

    return 0;
}

int bottleInput(int** bottles, int bottleNum, int perBottle, char** colors)
{
    int colorNum = bottleNum - 2;
    for (int i = 0; i < colorNum; i++)
    {
        printf("Tube/Bottle %d: ", i+1);
        for (int j = 0; j < perBottle; j++)
        {
            scanf("%d", &bottles[i][j]);
        }
        printBottles(&bottles[i], 1, perBottle, colors);
        printf("\n");
    }

    for (int i = colorNum; i < bottleNum; i++)
    {
        for (int j = 0; j < perBottle; j++)
        {
            bottles[i][j] = 0;
        }
    }

    return 0;
}

int** bottleInitilize(int bottleNum, int perBottle, char** colors)
{
    int** bottles = malloc(bottleNum * sizeof(int*));
    if (bottles == NULL) return NULL;

    size_t mem = perBottle * sizeof(int);
    for (int i = 0; i < bottleNum; i++)
    {
        bottles[i] = malloc(mem);
        if (bottles[i] == NULL) return NULL;
    }

    bottleInput(bottles, bottleNum, perBottle, colors);

    return bottles;
}

char** colorConstant()
{
    char** colors = malloc(14 * sizeof(char**));
    if (colors == NULL) return NULL;

    colors[0] = "     ";
    colors[1] = "Violet";
    colors[2] = "Brown";
    colors[3] = "Green";
    colors[4] = "D. Green";
    colors[5] = "Magenta";
    colors[6] = "Sea";
    colors[7] = "Blue";
    colors[8] = "L. Blue";
    colors[9] = "Lime";
    colors[10] = "Red";
    colors[11] = "Orange";
    colors[12] = "Skin";
    colors[13] = "Sky";

    return colors;
}

char** colorInput(int colorNum)
{
    char** colors = malloc((colorNum + 1) * sizeof(char*));
    if (colors == NULL) return NULL;
    colors[0] = "    ";

    printf("Enter the name of the colors: \n");
    
    const int charLimit = 30;
    int count;
    char cin[charLimit];
    fgets(cin, charLimit, stdin);
    for (int i = 1; i <= colorNum; i++)
    {
        printf("Color %d: ", i);
        fgets(cin, charLimit, stdin);
        
        count = 0;
        while (cin[count] != '\n') count++;
        cin[count] = 0;
        count += 1;

        colors[i] = malloc(count * sizeof(char));
        if (colors[i] == NULL) return NULL;
        for (int j = 0; j < count; j++) colors[i][j] = cin[j];
    }

    return colors;
}

int** initialize(int* bottleNum, int* perBottle, int* colorNum, char*** colors)
{
    printf("Number of Tubes/Bottles: ");
    scanf("%d", bottleNum);
    *colorNum = *bottleNum - 2;
    if (colorNum <= 0) return NULL;

    printf("Stripes per Tube/Bottle: ");
    scanf("%d", perBottle);

    //*colors = colorInput(*colorNum);
    *colors = colorConstant();
    
    int** bottles = bottleInitilize(*bottleNum, *perBottle, *colors);
    if (bottles == NULL || *colors == NULL)
    {
        printf("Memory Allocation Error!!");
        return NULL;
    }

    return bottles;
}

int freeAll(int** bottles, char** colors, int bottleNum, int* moves)
{
    if (bottles != NULL)
    {
        for (int i = 0; i < bottleNum; i++) free(bottles[i]);
        free(bottles);
    }

    int colorNum = bottleNum - 2;
    if (colors != NULL)
    {
        for (int i = 0; i <= colorNum; i++) free(colors[i]);
        free(colors);
    }

    free(moves);
}


int appendMove(int from, int to, int depth, int moveNum, int** moveList)
{
    moveList[moveNum] = malloc(3 * sizeof(int));
    moveList[moveNum][0] = from;
    moveList[moveNum][1] = to;
    moveList[moveNum][2] = depth;
    
    return 0;
}

int move(int from, int to, int bottleNum, int perBottle, int** bottles, char** colors, int* moveNum, int** moveList)
{
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < perBottle; i++)
    {
        if (bottles[from][i] != 0 && fromIndex == -1) fromIndex = i;
        if (bottles[to][i] != 0 && toIndex == -1) toIndex = i; 
    }

    if (fromIndex == -1) return -1;
    if (toIndex != -1 && bottles[from][fromIndex] != bottles[to][toIndex]) return -1;

    if (toIndex == -1) toIndex = perBottle;
    int color = bottles[from][fromIndex];

    int depth = 0;
    toIndex--;
    while (fromIndex < perBottle && bottles[from][fromIndex] == color && toIndex >= 0)
    {
        bottles[to][toIndex] = color;
        bottles[from][fromIndex] = 0;
        fromIndex++;
        toIndex--;
        depth++;
    }
    moveNum += 1;

    printBottles(bottles, bottleNum, perBottle, colors);

    return 0;
}

int moveInput(int bottleNum, int perBottle, int** bottles, char** colors, int* moveNum, int** moveList)
{
    int input[] = {0, 0};
    int in;

    for (int i = 0; i < 2; i++)
    {
        while (input[i] == 0)
        {
            printf("Bottle/Tube %d: ", i+1);
            scanf("%d", &in);
            if (in <= bottleNum && in > 0)
            {
                input[i] = in - 1;
                break;
            } 
            printf("Bottle/Tube doesn't exist\n");
            getchar();
        }
    }
    
    int n = move(input[0], input[1], bottleNum, perBottle, bottles, colors, moveNum, moveList);

    return n;
}


int main()
{
    int bottleNum;
    int perBottle; // Stripes per Bottle/Tube
    int colorNum;
    char** colors;
    int** bottles;
    int* moves;
    int moveNum = 0;
    int** moveList = malloc(50 * sizeof(int*));

    bottles = initialize(&bottleNum, &perBottle, &colorNum, &colors);

    printBottles(bottles, bottleNum, perBottle, colors);

    // while(1) moveInput(bottleNum, perBottle, bottles, colors, moveList);

    freeAll(bottles, colors, bottleNum, moves);

    return 0;
}