This is a mangala game which has different rules than it has in usual.

Game Setup
-Placing n stones in each of the small cups, leaving the large cups empty.
-Designating one side of the board as player and the other as the computer’s.

Gameplay
-Player take turn selecting a cup from its own side.
-The player then distributes the stones from the selected cup counterclockwise, placing one stone in each cup, including their own large cup but excluding the computer’s large cup.Distribution restarts from the cup where the last stone lands if the cup isn’t empty.
-If the last stone lands in the player's own large cup, it gets another turn.
-If the last stone lands in an empty cup, then the computer takes the turn.
-The computer plays the game on its own by obeying the same rules as the player.
-Player and the computer continue taking turns until one side of the board is empty.

Scoring
-When one side of the board is empty, the game ends.
-The stones in the large cups are counted.
-The player (or computer) with the most stones in their large cup wins the game.

Functions
initializeGame()
-This function initializes the game board, which includes placing stones in each of the small cups
and leaving the large cups empty. Additionally, it will designate one side of the board as the
player's and the other side as the computer's. I have used a 2D array for implementing the
game board. The function takes parameters such as the number of stones n to place in each cup,
and the board will be initialized.

printBoard()
-The print board function displays the contents of each cup on the board, including the number of
stones in each cup and the designated large cups for the player and the computer. This function
will help players make informed decisions during gameplay by allowing them to see the
distribution of stones on the board.

gamePlay()
-This function controls the flow of the game, allowing players and the computer to take turns
selecting cups and distributing stones. This function will handle player input, validate moves,
employ the move, switching the turn between player and computer, check for the end condition
of the game (i.e., when one side of the board is empty), and determine the winner based on the
final state of the game board. The function returns the winner along with the score.

move()
-The move function takes parameters such as the selected cup and the board. This function will
distribute stones from the selected cup counterclockwise, following the rules of the game. The
state of the board has to be updated at each change during the distribution. Printing the board after
each distribution sequence is done. The distribution continues until special cases occur, such as
when the last stone lands in the player's large cup, or when the last stone lands in an empty cup.
The gamePlay() function takes action based on the return value from this function.

main() function is as follows:
int main()
{
/* Declare the needed variables. */
/* Call the initializeGame() function to setup the game.*/
/* Call the printBoard() function.*/
/* Call the gameplay() function to start the game.*/
/* Print the winner along with the obtained score.*/
}
