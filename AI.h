#ifndef AI_H
#define AI_H
#include <iostream>
#include "Player.h"

class AI
{
private:
	// The player currently taking their turn.
	int currentPlayer;

	// The limit used to compare the total number of spaces that the ships are sunk on a board
	int totalXs;

	// Number of ships for the game
	int numShips;

	// A heap allocated object of the player class
	// The first player of the game
	Player *player1;

    Player *opponent;

    int difficulty;

	int AiHitCounter;

	int mediumHit[2];
	bool adjacentHit;

	//For the added feature to the game. Determines after how many atacks to switch turns.
	int attackNum;

	//For the custom addition that gives a bonus move to AI and player after 
	//the fifth move during a standard (1-attack) mode
	int bonusAI = 0;
	int bonusPlayer = 0;

	int countPlayer = 1; //Keeps track of how many attacks the player has used in a turn
    int countAI = 1; //Keeps track of how many attacks AI has used in a turn


public:
	/*
	 * @pre none
	 * @post Initializes both the players and sets totalXs to zero.
	 * @param none
	 * @return None
	 */
	AI();

	/*
	 * @pre none
	 * @post deletes both players
	 * @param none
	 * @return None
	 */
	~AI();
	/*
	 * @pre none
	 * @post the number of ships is obtained, and the boards are completely set up
	 * @param none
	 * @return none
	 */
	void setup();

	/*
	 * @pre none
	 * @post the current player's Board is completely set up
	 * @param Player *currentPlayer is the Player taking the turn for setting up
	 * @return none
	 */
	void setupPlayer();

    void setupAI();

	/*
	 * @pre none
	 * @post an appropriate integer is obtained from the user
	 * @param none
	 * @return the integer they correctly inputted
	 */
	int getInt();

	/*
	 * @pre none
	 * @post the whole string is checked if it's all digits or not
	 * @param string str is the string to check
	 * @return true if it's all integers, false otherwise
	 */
	bool isDigit(string str);

	/*
	 * @pre none
	 * @post an appropriate character is obtained from the user
	 * @param none
	 * @return the character they correctly inputted
	 */
	char getChar();

	/*
	 * @pre none
	 * @post Confirms the current player is done with their turn and clears the screen.
	 * 	Double checks with the next person if they are ready for their turn.
	 * @param none
	 * @return None
	 */
	void clear();

	/*
	 * @pre none
	 * @post The player played their turn.
	 * @param an int representing whose turn it was
	 * @return None
	 */
	void turn(int currentPlayer);

	/*
	 * @pre none
	 * @post Actually goes through a player's turn where they see their board and ships lives, attack, and
	 * 	see whether their attack missed or hit
	 * @param Two player objects- the one taking their turn and the other player
	 * @return None
	 */
	void takeTurnPlayer();
	void takeTurnAI(int difficulty);
	void attack(Player *attackingPlayer, Player *defendingPlayer, int row, int col);

	/*
	 * @pre row and col values between 0 and 9 (representing the indexes of the board 2d array)
	 * @post Tells whether or not a player has already fired at that location.
	 * @param the row and col of the attack location and the player firing the attack
	 * @return a bool representing if that target can be fired upon
	 */
	bool validAttack(Player *attackingPlayer, int row, int col);
	bool validAttackAI( int row, int col);

	/*
	 * @pre none
	 * @post Goes through the currentPlayer's firing board tallying the number of sunk spots.
	 * 	If they sunk all their opponent's ships, it's the end of the game.
	 * @param none
	 * @return a bool representing whether the game is over or not
	 */
	bool gameover();

	/*
	 * @pre none
	 * @post runs the entire game and calls upon a host of functions to do so.
	 * @param none
	 * @return None
	 */
	void play();

	void playAI();
};
#endif
