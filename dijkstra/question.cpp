#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
 
 #define LENGTH 8

 char map[LENGTH][LENGTH];

typedef struct
{
    int x;
    int y;
} Position;

typedef struct
{
    int money;
    int item;
} Omake;

typedef struct
{
    int      life;
    Position position;
    Omake    omake;
} Player;

char* createCharPointer()
{
    char* readData = (char*)malloc(87);
    strcpy(readData, "10\n****@***\n********\n********\n********\n***%****\n********\n********\n********\n\0");
    return readData;
}

Position getPosition(char code) {
    Position position;
    for(int i = 0; i < LENGTH; i++)
    {
        for(int j = 0; j < LENGTH; j++)
        {
            if(map[j][i] == code)
            {
                position.x = j;
                position.y = i;
                return position;
            }
        }
    }
    return position;
}

int main()
{
    Player player;

    /* データ読み込み */
    char* readData = createCharPointer();

    /* ライフ読み込み */
    char* line  = strtok(readData, "\n");
    player.life = atoi(line);

    /* 値を入れる */    
    int count = 0;
    while(1) 
    {
        line = strtok(NULL, "\n");
        if(line == NULL)
        {
            break;
        }
        strcpy(map[count], line);
        printf("%s\n", map[count]);
        count++;
    }
    
    player.position        = getPosition('@');
    Position stairPosition = getPosition('%');

    int result = abs((player.position.x - stairPosition.x)) + abs(player.position.y - stairPosition.y);
    if(player.life > result)
    {
        printf("%d\n", result);
    }

    return 0;
}