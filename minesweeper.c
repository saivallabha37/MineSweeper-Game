#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8  //max size=16
#define MINES 10

char board[SIZE][SIZE];      //actual board
char display[SIZE][SIZE];    //board which is displayed

void initBoard()
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            board[i][j] = '0';      //initializes every tile to '0'
            display[i][j] = '-';    //initialises to every tile '-'
        }
    }
}

void placeMines()    //place mines randomly
{
    int count = 0;
    while (count < MINES)
    {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (board[x][y] != '*')
        {
            board[x][y] = '*';
            count++;

            // Update count around the mine
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int nx = x + i;
                    int ny = y + j;
                    if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] != '*')
                    {
                        board[nx][ny]++;     //update count by 1
                    }
                }
            }
        }
    }
}

void printBoard(char b[SIZE][SIZE])     //to print board
{
    printf("    ");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%02d ", i);
    }
    printf("\n");

    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%02d  ", i);

        for (int j = 0; j < SIZE; j++)
        {
            printf("%2c ", b[i][j]);
        }
        printf("\n");
    }
}

int reveal(int x, int y)    //reveals the entered coordinates
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || display[x][y] != '-')
        return 0;

    display[x][y] = board[x][y];
    if (board[x][y] == '*')
        return -1;  // Hit a mine

    if (board[x][y] == '0')
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                    reveal(x + i, y + j);   //recursive call
            }
        }
    }
    return 1;
}

int checkWin()   //checks win or not
{
    int revealed = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (display[i][j] != '-')
                revealed++;
        }
    }

    return (revealed == SIZE * SIZE - MINES);
}

int main()
{
    printf("=====================GAME STARTS=====================\n\n");

    int x, y;
    srand(time(NULL));   //seeds a random according to time
    initBoard();
    placeMines();

    clock_t start, end;
    double play_time;

    start = clock();   //start timer

    while(1)
    {
        printBoard(display);
        printf("\nEnter coordinates to reveal (row col) : ");
        scanf("%d %d", &x, &y);

        if (x >= SIZE || y >= SIZE)
            printf("\nPlease enter valid coordinates !!\n");

        printf("\n----------------------------------------------------\n\n");

        int result = reveal(x, y);
        if (result == -1)
        {
            printBoard(board);
            printf("\nGame Over! You hit a mine.\n\n");
            break;
        }
        else if (checkWin())
        {
            printBoard(board);
            printf("\nCongratulations! You cleared the board.\n\n");

            break;
        }
    }

    end = clock();   //end timer
    play_time = ((double)(end - start)) / CLOCKS_PER_SEC;   //calculation of play time

    printf("Time taken : %lf seconds\n", play_time);

    printf("\n=====================================================\n");

    return 0;
}

