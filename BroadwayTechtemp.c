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
