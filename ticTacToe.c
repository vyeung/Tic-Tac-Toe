#include <stdio.h>

#define SIZE 3

//prototypes
void initialize(char board[SIZE][SIZE]);
void print_board(char board[SIZE][SIZE]);
int is_winner(char board[SIZE][SIZE]);
int is_full(char board[SIZE][SIZE]);
int check_move(char board[SIZE][SIZE], int x, int y);

int main()
{
    char board[SIZE][SIZE]; //create a board
    int turn = 2, x, y;  //x and y are coordinates
    char play;  //play will be X or O

    initialize(board);
    printf("Welcome to Tic-Tac-Toe! \n");
    printf("Player 1 will be X. \nPlayer 2 will be O. \n");
    printf("Make a move by entering an integer row and column. Ex:2 2 \n");

    //Alternate turns for the users until the board is full
    while(!is_full(board))
    {
        //Set user's turn
        if(turn == 2)
        {
            turn = 1;
            play = 'X';
        }
        else
        {
            turn = 2;
            play = 'O';
        }

        //Announce whose turn it is
        printf("\nIt is player %d's turn. \n", turn);

        //Print board
        print_board(board);

        //Ask user for their move. assume that they enter integers
        printf("Enter an integer row and column. \n");
        scanf("%d %d", &x, &y);

        //Verify the move is valid
        while(!check_move(board, x-1, y-1))
        {
            printf("\nSorry, that move was not valid.\n");
            print_board(board);
            printf("Where would you like to go?  row col \n");
            scanf("%d %d", &x, &y);
        }

        //Put user's move on the board
        board[x-1][y-1] = play;

        //Check to see if there is a winner
        if (is_winner(board))
            break;

        if(is_winner(board) == 0 && is_full(board) == 1)
            printf("\nGame is a draw! \n");
    }

    //Print the board a final time
    print_board(board);

    return 0;
}

/* Initialize Function
 * Pre-Condition:  This function takes in a SIZExSIZE board
 * Post-Condition: This function initializes the board
 *
 * set every index on the board to '-'
 */
void initialize(char board[SIZE][SIZE])
{
    int i,j;
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            board[i][j] = '-';
        }
    }

    return;
}

/* Print Function
 * Pre-Condition:  This function takes in a SIZExSIZE board
 * Post-Condition: This function prints the board
 *
 * print contents of the board for the user to see.
 */
void print_board(char board[SIZE][SIZE])
{
    int i,j;
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            printf("\t%c", board[i][j]); //Notice %c since we're dealing with characters
        }
        printf("\n");
    }
}

/* Winner Function
 * Pre-Condition:  This function takes in a SIZExSIZE board
 * Post-Condition: This function will return a 1 if there is
 * winner and 0 otherwise
 *
 * check each row, column and diagonal to see if all three in that direction
 * are equal to each other and not equal to the initialization character.
 *
 * If there is a winner, print out whether it is Player 1 (X) or Player 2 (O) and return 1.
 *
 * If there is not a winner yet, return 0.
 */
int is_winner(char board[SIZE][SIZE])
{
    int winner = 0; //flag
    int player = 0; //see if there's a winner
    char start;
    int i,j;

    //check rows
    for(i=0; i<SIZE; i++)
    {
        winner = 1;  //assume there's a winner.
        start = board[i][0]; //start is first value in a row.
        for(j=1; j<SIZE; j++)
        {
            //if all the values going across are not the same as start, don't have a winner.
            if(board[i][j] != start || board[i][j] == '-')
                winner = 0;
        }

        if(winner == 1)
        {
            if(start == 'X')
            {
                printf("\nPlayer 1 has won! \n");
                return 1;
            }

            else
            {
                printf("\nPlayer 2 has won! \n");
                return 1;
            }
        }
    }

    //check columns
    for (i=0; i<SIZE; i++)
    {
        winner = 1;
        start = board[0][i];
        for(j=1; j<SIZE; j++)
        {
            if(board[j][i] != start || board[j][i] == '-')
                winner = 0;
        }

        if(winner == 1)
        {
            if(start == 'X')
            {
                printf("\nPlayer 1 has won! \n");
                return 1;
            }

            else
            {
                printf("\nPlayer 2 has won! \n");
                return 1;
            }
        }
    }

    //check first diagonal. Similar to magic square example.
    winner = 1;
    start = board[0][0];
    for(i=1; i<SIZE; i++)
    {
        if(board[i][i] != start || board[i][i] == '-')
            winner = 0;
    }

    if(winner == 1)
    {
        if(start == 'X')
        {
            printf("\nPlayer 1 has won! \n");
            return 1;
        }

        else
        {
            printf("\nPlayer 2 has won! \n");
            return 1;
        }
    }

    //check second diagonal
    winner = 1;
    start = board[0][SIZE-1];
    for(i=1; i<SIZE; i++)
    {
        if(board[i][SIZE-i-1] != start || board[i][SIZE-i-1] == '-')
            winner = 0;
    }

    if(winner == 1)
    {
        if(start == 'X')
        {
            printf("\nPlayer 1 has won! \n");
            return 1;
        }

        else
        {
            printf("\nPlayer 2 has won! \n");
            return 1;
        }
    }

    return 0;
}

/* Full Function
 * Pre-Condition:  This function takes in a SIZExSIZE board
 * Post-Condition: This function will return a 1 if the board
 * if full and 0 otherwise
 *
 * Look through the board and return a 0 if any empty spaces are
 * found.  Empty spaces are denoted by the initialization character '-'.
 *
 * Return a 1 if no empty spaces are found.
 */
int is_full(char board[SIZE][SIZE])
{
    int i,j;
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            if(board[i][j] == '-')
                return 0;
        }
    }

    return 1;
}

/* Check Function
 * Pre-Condition:  This function takes in a SIZExSIZE board, and two
 * integers x and y that represent the user's intended move
 * Post-Condition: This function returns a 1 if the user's intended
 * move is valid and 0 otherwise.
 *
 * Verify that x and y are valid input.
 * Check that they represent a correct index for the board.
 * Then, check that the space intended by x and y has not already been played.
 */
int check_move(char board[SIZE][SIZE], int x, int y)
{
    if(x < 0 || x >= SIZE) //coordinates should be between 0 and SIZE-1
        return 0;

    if(y < 0 || y >= SIZE)
        return 0;

    if(board[x][y] != '-') //a space needs to be unused.  Can't override.
        return 0;

    return 1;
}
