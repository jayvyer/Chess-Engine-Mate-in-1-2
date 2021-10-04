#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chess.h"
#include "moves.h"
#include "io.h"

/* The enpassant square */
Pos ep_square;
/* The player structures. One each for black and white */
PlayerState player[2];
/* The color of the current player */
PlayerColor CurrentPlayer;
/* The mode in which the chess engine is operating */
Mode mode;
/* usage: ./chess puzzles.txt solutions.txt <mode> */    

/*
	Create the legal moves for current player
	Store stale
	Traverse through legal moves for current player
	For each legal move current player can make, make it and then check if it puts enemy into checkmate
	If it does, free the linked list and return the move
	If it does not, then restore the state and go to next legal move in list

 Given a position, find a mate in 1.
   Given a Move, see if that move puts enemy in check mate  */

Bool run_mate1(Move *soln) {
	Pos temp_ep_square;
	unsigned int count = 0;
	unsigned int *pcount = &count;
	int num_nodes = 0;
	Move *head = (Move *) malloc(1 * sizeof(Move));
	PlayerState saved_state = player[CurrentPlayer];
	PlayerState saved_state2 = player[1 - CurrentPlayer];
	if(legal_moves(&head, CurrentPlayer, pcount) == FALSE) {
		freeList(head);
		return FALSE;
	}
	Move *current = head->next_move;
	while(current != NULL) {
		if(validate_and_move(current, CurrentPlayer, &temp_ep_square)){
			ep_square = temp_ep_square;
			if(is_checkmate(1 - CurrentPlayer) == TRUE){
				*soln = *current;
				freeList(head);
				return TRUE;
			}
			if(is_draw()) {
				printf("STALEMATE DETECTED\n");
			}
			player[CurrentPlayer] = saved_state;
			player[1 - CurrentPlayer] = saved_state2;
			current = current->next_move;
			num_nodes += 1;
		}
		else{
			/* didn't move so no need to restore states */
			current = current->next_move;
			num_nodes += 1;
		}
	}
	if(num_nodes != count){
		printf("error: num nodes != count");
	}
	freeList(head);
	return FALSE;
}

/*
/* Given a position, find an absolute mate in 2. */
Bool run_mate2(Move *soln) {
	/*
	For each move m1 that current player can make:
		Make move m1
		If there exists mate in 1 for current player for each and every legal move other player can make:
			M1 is the solution
	*/
	Pos temp_ep_square;

	PlayerState saved_state = player[CurrentPlayer];
	PlayerState saved_state2 = player[1 - CurrentPlayer];

	Move *first_move_head = (Move *) malloc(1 * sizeof(Move));
	Move *second_move_head = (Move *) malloc(1 * sizeof(Move));
	Move *third_move = (Move *) malloc (1 * sizeof(Move));

	unsigned int count = 0;
	unsigned int *pcount = &count;

	if(legal_moves(&first_move_head, CurrentPlayer, pcount) == FALSE) { /* generate list of legal moves for current player */
		freeList(first_move_head);
		second_move_head->next_move = NULL;
		third_move->next_move = NULL;
		freeList(second_move_head);
		freeList(third_move);

		printf("current player under checkmate");
		return FALSE;
	}

	Move *first_move_current = first_move_head->next_move;
	while(first_move_current != NULL) { /* for each move that current player can make */
		if(validate_and_move(first_move_current, CurrentPlayer, &temp_ep_square) == TRUE){ /* make move */
			ep_square = temp_ep_square;
			unsigned int count_other = 0;
			unsigned int *ppcount = &count_other;

			/* see if move results in sure checkmate after any opponent move */
			int m1_found = 0;
			legal_moves(&second_move_head, 1 - CurrentPlayer, ppcount);
			Move *second_move_current = second_move_head->next_move;
			while(second_move_current != NULL) { /* iterate through list, and if mate in 1 exists for each and every move of opponent, then current move is the solution */
				PlayerState ps1 = player[CurrentPlayer];
				PlayerState ps2 = player[1 - CurrentPlayer];
				if(validate_and_move(second_move_current, 1 - CurrentPlayer, &temp_ep_square)) { /* make other player move */
					/* search for a mate in 1 */
					if(run_mate1(third_move) == TRUE) {
						m1_found = 1;
					}
					else{
						/*there is no checkmate in 1 in this instance of the second move */
						m1_found = 0;
						break;
					}
					player[CurrentPlayer] = ps1;
					player[1 - CurrentPlayer] = ps2;
				}
				second_move_current = second_move_current->next_move;
			}
			player[CurrentPlayer] = saved_state;
			player[1 - CurrentPlayer] = saved_state2;
			if(m1_found == 1){
				break;
			}
		}
		first_move_current = first_move_current->next_move;
	}
	if(first_move_current == NULL){
		third_move->next_move = NULL;
		freeList(first_move_head);
		freeList(second_move_head);
		freeList(third_move);
		return FALSE;
	}
	*soln = *first_move_current;
	third_move->next_move = NULL;
	freeList(first_move_head);
	freeList(second_move_head);
	freeList(third_move);
	return TRUE;
}
*/
