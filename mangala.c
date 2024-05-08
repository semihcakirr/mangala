#include <stdio.h>

#define SIDE_SIZE 7

/* Function to initialize the game board */
void initializeGame(int n, int board[2][SIDE_SIZE])
{
    int i, j;
    for (i = 0; i < 2; i++) /* Loop through each player's side */
    {
        for (j = 0; j < SIDE_SIZE; j++) /* Loop through each cup */
        {
            if (j == 6) /* Means i am in a large cup */
            {
                board[i][j] = 0; /* Large cups has 0 stones */
            }
            else /* Means i am in a regular cup */
            {
                board[i][j] = n; /* Other cups have n stones */
            }
        }
    }
}

/* Function to print the game board */
void printBoard(int board[2][SIDE_SIZE])
{
    /* I am using %2d's because it helps me manageing the spaces in output */
    printf("\n+----+---+---+---+---+---+---+----+\n");
    printf("|    | %2d| %2d| %2d| %2d| %2d| %2d|    |\n", board[1][5], board[1][4], board[1][3], board[1][2], board[1][1], board[1][0]);
    printf("+ %2d +---+---+---+---+---+---+ %2d +\n", board[1][6], board[0][6]);
    printf("|    | %2d| %2d| %2d| %2d| %2d| %2d|    |\n", board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5]);
    printf("+----+---+---+---+---+---+---+----+\n");
}
/* Function to perform the moves in the game */
int move(int selected_cup, int board[2][SIDE_SIZE], int player)
{
    int side = player;                      /* Variable to know the current side */
    int stones;                             /* Variable to know the stone count */
    stones = board[side][selected_cup - 1]; /* Stone count will be [selected cup - 1]'s index (I get cup selections as 1-6 and perform them as 0-5 thats why it should be selected cup - 1) */
    board[side][selected_cup - 1] = 0;      /* Decreasing selected cups index to 0 */
    while (stones > 0)                      /* Loop till stone count becomes 0 */
    {
        if (selected_cup != SIDE_SIZE - 1) /* If next cup is not the last cup of any side, perform belowing actions */
        {
            board[side][selected_cup]++; /* Increasing next cup */
            selected_cup++;              /* Increasing selected_cup variable so it can go for next cup */
            stones--;                    /* Decreasing stone count */
        }
        else if (selected_cup == SIDE_SIZE - 1) /* If the next cup is the large cup of any side going in here */
        {
            if (player == 0 && side == 0) /* If the player is user and current side is 0 then i get that he/she is on his/her own side */
            {
                board[side][selected_cup]++; /* Increasing the large cups stone count */
                side = 1;                    /* Changing side */
                stones--;                    /* Decreasing stone count */
            }
            else if (player == 0 && side == 1) /* If the player is user and current side is computers, just change the side because we dont want to increase computers large cups stone count */
            {
                side = 0; /* Changing side */
            }
            else if (player == 1 && side == 1) /* Increasing the large cups stone count */
            {
                board[side][selected_cup]++;
                side = 0; /* Changing side */
                stones--; /* Decreasing stone count */
            }
            else if (player == 1 && side == 0) /* If the player is computer and current side is users, just change the side because we dont want to increase users large cups stone count */
            {
                side = 1; /* Changing side */
            }
            selected_cup = 0; /* I have changed side so i have to go for first cup of this side */
        }
        if (stones == 0) /* If there is no stones left go in here */
        {
            if (selected_cup == 0) /* Means last cup that took stone is a large cup. */
            {
                if (player == 0 && side == 1) /* The large cup is players cup, return 0 that indicates player will play next */
                {
                    return 0;
                }
                else if (player == 1 && side == 0) /* The large cup is computers cup, return 1 that indicates computer will play next */
                {
                    return 1;
                }
            }
            else if (selected_cup != 0) /* Means last cup that took stone is a regular cup. */
            {
                if (board[side][selected_cup - 1] - 1 == 0) /* Last cup that took stone is empty. Which means its time for opponents turn. Returning (player)' */
                {
                    return 1 - player; /* If the current player is 0 then 1 will be returned and vice versa */
                }
                else if (board[side][selected_cup - 1] != 0) /* The last cup that took stone is not an empty cup. Which means i have to perform REDISTRIBUTION */
                {
                    stones = board[side][selected_cup - 1]; /* Current cups stone count is becoming new stones count */
                    board[side][selected_cup - 1] = 0;      /* Decreasing current cups stone count to 0 */
                }
            }
        }
    }
    return -1;
}

/* Function to control the gameplay */
int gamePlay(int board[2][SIDE_SIZE])
{
    int i, j;                /* Variables to use in loops */
    int selected_cup;        /* Variable to track the current side */
    int computer_move_found; /* Variable to check if computer has decided its move or not */
    int player = 0;          /* 0 Means player, 1 means computer. */
    int end_counter = 0;     /* Variable to check if any players side is empty or not */
    int check_ending = 0;    /* Variable to check if the game should end or not */
    int cup_with_max_stones;
    do
    {
        if (player == 0) /* If current player is user go here */
        {
            do /* Loop until valid move has chosen */
            {
                printf("\nPlease choose a cup to play. (1-6, For 1st cup enter 1, for second cup enter 2 and etc): ");
                scanf("%d", &selected_cup);
                if (selected_cup < 1 || selected_cup > 6) /* If selected cup is not between 1-6 printing error message */
                {
                    printf("You did not choose a valid cup!\n");
                }
                else if (board[0][selected_cup - 1] == 0) /* If selected cup is empty printing error message */
                {
                    printf("This cup is empty. You must choose another cup!\n");
                }
            } while (selected_cup < 1 || selected_cup > 6 || board[0][selected_cup - 1] == 0);
        }
        else if (player == 1) /* If current player is computer go here */
        {
            computer_move_found = 0; /* Resetting flag */
            /* First, computer will try to end its move in its own large cup. If it is not possible then it will choose the first non-empty cup to play */
            for (selected_cup = 0; selected_cup < SIDE_SIZE - 1; selected_cup++) /* Loop through every cup on computers side */
            {
                if (SIDE_SIZE - 1 - board[1][selected_cup] == selected_cup) /* This formula checks if computer can finish its move on its own large cup */
                {
                    computer_move_found = 1; /* Move has founded. Setting flag to 1 and breaking the loop */
                    break;
                }
            }
            if (computer_move_found == 0) /* If move has not founded yet, go in this loop. NOW THE COMPUTER WILL CHOOSE THE CUP WITH MAX STONES */
            {
                cup_with_max_stones = 0;                                             /* Setting the cup with max stones as first cup of computers */
                for (selected_cup = 1; selected_cup < SIDE_SIZE - 1; selected_cup++) /* Loop through every cup on computers side, starting from second cup because i will compare every cup with the cup before it */
                {
                    if (board[1][selected_cup] > board[1][cup_with_max_stones]) /* If the current cup has more stone than the cup with the max stones go in here */
                    {
                        cup_with_max_stones = selected_cup; /* Update the cup with max stones as current cup */
                    }
                }
                selected_cup = cup_with_max_stones; /* Now set the selected cup as cup with max stones */
                computer_move_found = 1;            /* Move has founded. Actually this line is not necessary but i wanted it */
            }
            selected_cup += 1;                                        /* Increasing computers selected_cup because it chooses as 0-5 and user chooses as 1-6. I have designed the algoritm leaning on 1-6. So i must increase the computers choice. */
            printf("Computers selection is cup: %d\n", selected_cup); /* Printing computers choice */
        }

        player = move(selected_cup, board, player); /* Changing the player as move functions returned value */
        printBoard(board);                          /* Printing board */
        /* At this point i should check if the game should end or not */
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < SIDE_SIZE - 1; j++)
            {
                end_counter += board[i][j]; /* Checking sides every cup except large cups and adding them in end_counter variable */
            }
            if (end_counter == 0) /* If total value is 0 then game should end */
            {
                check_ending = 1; /* Setting ending flag to 1 and breaking the loop */
                break;
            }
            end_counter = 0; /* Resetting counter so i can count other side from zero */
        }
        if (check_ending == 0) /* If game is not ending printing turns */
        {
            if (player == 0)
            {
                printf("Your turn!\n");
            }
            else if (player == 1)
            {
                printf("Computers turn!\n");
            }
        }
    } while (check_ending == 0); /* Break the core game loop if game should end */

    if (check_ending == 1) /* Game is ending, time to determine winner */
    {
        if (board[0][SIDE_SIZE - 1] > board[1][SIDE_SIZE - 1]) /* If players large cup has more points, returning 0 that indicates player is the winner */
        {
            return 0;
        }
        else if (board[0][SIDE_SIZE - 1] < board[1][SIDE_SIZE - 1]) /* If computers large cup has more points, returning 1 that indicates computer is the winner */
        {
            return 1;
        }
        else if (board[0][SIDE_SIZE - 1] == board[1][SIDE_SIZE - 1]) /* If computers large cups are equal, returning 2 that indicates its a tie */
        {
            return 2;
        }
    }
    return -1;
}

int main()
{
    int board[2][SIDE_SIZE]; /* Creating the gameboard */
    int n;                   /* Variable to scan stone count on every cups from user and fill the board with this counts */
    int winner;
    printf("Enter the number of stones to place in each cup: ");
    scanf("%d", &n);
    initializeGame(n, board);
    printBoard(board);
    winner = gamePlay(board);
    if (winner == 1) /* If gameplay function has returned 1, it means computer has won, going in here */
    {
        printf("Computer has won!\n");                /* Printing winner */
        printf("Computers score: %d\n", board[1][6]); /* Printing scores */
        printf("Your score: %d\n", board[0][6]);
    }
    else if (winner == 0) /* If gameplay function has returned 0, it means user has won, going in here */
    {
        printf("You have won!\n");               /* Printing winner */
        printf("Your score: %d\n", board[0][6]); /* Printing scores */
        printf("Computers score: %d\n", board[1][6]);
    }
    else if (winner == 2) /* If gameplay function has returned 2, it means there is no winner, going in here */
    {
        printf("It is a tie!\n");                /* Printing message for draw */
        printf("Your score: %d\n", board[0][6]); /* Printing scores */
        printf("Computers score: %d\n", board[1][6]);
    }
    return 0;
}