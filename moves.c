#include "moves.h"
#include <stdlib.h>
#include <stdio.h>

void freeList(Move* head){
	Move* tmp;
	while(head != NULL){
		tmp = head;
		head = head->next_move;
		free(tmp);
	}
}

Pos king_pos(PlayerColor c){
	Pos pos = 0;
	int i;
	for(i = 0; i < 64; i++){
		if(IS_SET(player[c].k,i)){
			pos = i;
		}
	}
	return pos;
}

/* is king under check:
for each of opponent's pieces:
for each square an opponent's piece can move to:
if king occupies the square
return TRUE;
return FALSE;
*/
/* returns TRUE if CurrentPlayer's King is under check, FALSE otherwise */
Bool is_king_under_check(PlayerColor c) {
	PlayerState opponent = player[1 - c]; /* PlayerState of opponent */
	Pos curr_king_pos = king_pos(c);
	/* for each of opponent's pieces:
	check each possible move to see if it matches current king position */
	int i;
	for(i = 0; i < 64; i++) {
		/* rook */
		if(IS_SET(opponent.r, i)) {
			Pos start_pos = i;
			Pos temp_pos = start_pos;

			while(NORTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NORTH_OF(temp_pos)) || temp_pos - 8 == curr_king_pos)) {
				if(temp_pos - 8 == curr_king_pos) {
					return TRUE;
				}
				temp_pos -= 8;
			}
			temp_pos = start_pos;

			while(SOUTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SOUTH_OF(temp_pos)) || temp_pos + 8 == curr_king_pos)) {
				if(temp_pos + 8 == curr_king_pos) {
					return TRUE;
				}
				temp_pos += 8;
			}
			temp_pos = start_pos;

			while(WEST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(WEST_OF(temp_pos)) || temp_pos - 1 == curr_king_pos)) {
				if(temp_pos - 1 == curr_king_pos) {
					return TRUE;
				}
				temp_pos -= 1;
			}
			temp_pos = start_pos;

			while(EAST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(EAST_OF(temp_pos)) || temp_pos + 1 == curr_king_pos)) {
				if(temp_pos + 1 == curr_king_pos) {
					return TRUE;
				}
				temp_pos += 1;
			}
			temp_pos = start_pos;
			continue;
		}

		/* knight */
		if(IS_SET(opponent.n, i)) {
			Pos temp_pos = i;
			if(NORTH_OF(NE_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(NORTH_OF(NE_OF(temp_pos))) || temp_pos - 15 == curr_king_pos)) {
				if(temp_pos - 15 == curr_king_pos) {
					return TRUE;
				}
			}
			if(NORTH_OF(NW_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(NORTH_OF(NW_OF(temp_pos))) || temp_pos - 17 == curr_king_pos)) {
				if(temp_pos - 17 == curr_king_pos) {
					return TRUE;
				}
			}
			if(WEST_OF(NW_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(WEST_OF(NW_OF(temp_pos))) || temp_pos - 10 == curr_king_pos)) {
				if(temp_pos - 10 == curr_king_pos) {
					return TRUE;
				}
			}
			if(WEST_OF(SW_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(WEST_OF(SW_OF(temp_pos))) || temp_pos + 6 == curr_king_pos)) {
				if(temp_pos + 6 == curr_king_pos) {
					return TRUE;
				}
			}
			if(SOUTH_OF(SW_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(SOUTH_OF(SW_OF(temp_pos))) || temp_pos + 15 == curr_king_pos)) {
				if(temp_pos + 15 == curr_king_pos) {
					return TRUE;
				}
			}
			if(SOUTH_OF(SE_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(SOUTH_OF(SE_OF(temp_pos))) || temp_pos + 17 == curr_king_pos)) {
				if(temp_pos + 17 == curr_king_pos) {
					return TRUE;
				}
			}
			if(EAST_OF(SE_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(EAST_OF(SE_OF(temp_pos))) || temp_pos + 10 == curr_king_pos)) {
				if(temp_pos + 10 == curr_king_pos) {
					return TRUE;
				}
			}
			if(EAST_OF(NE_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(EAST_OF(NE_OF(temp_pos))) || temp_pos - 6 == curr_king_pos)) {
				if(temp_pos - 6 == curr_king_pos) {
					return TRUE;
				}
			}
			continue;
		}

		/* bishop */
		if(IS_SET(opponent.b, i)) {
			Pos start_pos = i;
			Pos temp_pos = start_pos;

			while(NE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NE_OF(temp_pos)) || temp_pos - 7 == curr_king_pos)) {
				if(temp_pos - 7 == curr_king_pos) {
					return TRUE;
				}
				temp_pos -= 7;
			}
			temp_pos = start_pos;

			while(NW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NW_OF(temp_pos)) || temp_pos - 9 == curr_king_pos)) {
				if(temp_pos - 9 == curr_king_pos) {
					return TRUE;
				}
				temp_pos -= 9;
			}
			temp_pos = start_pos;

			while(SW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SW_OF(temp_pos)) || temp_pos + 7 == curr_king_pos)) {
				if(temp_pos + 7 == curr_king_pos) {
					return TRUE;
				}
				temp_pos += 7;
			}
			temp_pos = start_pos;

			while(SE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SE_OF(temp_pos)) || temp_pos + 9 == curr_king_pos)) {
				if(temp_pos + 9 == curr_king_pos) {
					return TRUE;
				}
				temp_pos += 9;
			}
			temp_pos = start_pos;
			continue;
		}

		/* queen NOTE: DIRECT COPY OF ROOK AND BISHOP */
		if(IS_SET(opponent.q, i)) {
			Pos start_pos = i;
			Pos temp_pos = start_pos;

			/* rook logic */
			while(NORTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NORTH_OF(temp_pos)) || temp_pos - 8 == curr_king_pos)) {
				if(temp_pos - 8 == curr_king_pos) {
					return TRUE;
				}
				temp_pos -= 8;
			}
			temp_pos = start_pos;

			while(SOUTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SOUTH_OF(temp_pos)) || temp_pos + 8 == curr_king_pos)) {
				if(temp_pos + 8 == curr_king_pos) {
					return TRUE;
				}
				temp_pos += 8;
			}
			temp_pos = start_pos;

			while(WEST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(WEST_OF(temp_pos)) || temp_pos - 1 == curr_king_pos)) {
				if(temp_pos - 1 == curr_king_pos) {
					return TRUE;
				}
				temp_pos -= 1;
			}
			temp_pos = start_pos;

			while(EAST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(EAST_OF(temp_pos)) || temp_pos + 1 == curr_king_pos)) {
				if(temp_pos + 1 == curr_king_pos) {
					return TRUE;
				}
				temp_pos += 1;
			}
			temp_pos = start_pos;

			/* bishop logic */
			while(NE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NE_OF(temp_pos)) || temp_pos - 7 == curr_king_pos)) {
				if(temp_pos - 7 == curr_king_pos) {
					return TRUE;
				}
				temp_pos -= 7;
			}
			temp_pos = start_pos;

			while(NW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NW_OF(temp_pos)) || temp_pos - 9 == curr_king_pos)) {
				if(temp_pos - 9 == curr_king_pos) {
					return TRUE;
				}
				temp_pos -= 9;
			}
			temp_pos = start_pos;

			while(SW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SW_OF(temp_pos)) || temp_pos + 7 == curr_king_pos)) {
				if(temp_pos + 7 == curr_king_pos) {
					return TRUE;
				}
				temp_pos += 7;
			}
			temp_pos = start_pos;

			while(SE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SE_OF(temp_pos)) || temp_pos + 9 == curr_king_pos)) {
				if(temp_pos + 9 == curr_king_pos) {
					return TRUE;
				}
				temp_pos += 9;
			}
			temp_pos = start_pos;
			continue;
		}

		if(IS_SET(opponent.k, i)) {
			Pos temp_pos = i;
			if(EAST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(EAST_OF(temp_pos)) || temp_pos + 1 == curr_king_pos)) {
				if(temp_pos + 1 == curr_king_pos) {
					return TRUE;
				}
			}
			if(NE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NE_OF(temp_pos)) || temp_pos - 7 == curr_king_pos)) {
				if(temp_pos - 7 == curr_king_pos) {
					return TRUE;
				}
			}
			if(NORTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NORTH_OF(temp_pos)) || temp_pos - 8 == curr_king_pos)) {
				if(temp_pos - 8 == curr_king_pos) {
					return TRUE;
				}
			}
			if(NW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NW_OF(temp_pos)) || temp_pos - 9 == curr_king_pos)) {
				if(temp_pos - 9 == curr_king_pos) {
					return TRUE;
				}
			}
			if(WEST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(WEST_OF(temp_pos)) || temp_pos - 1 == curr_king_pos)) {
				if(temp_pos - 1 == curr_king_pos) {
					return TRUE;
				}
			}
			if(SW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SW_OF(temp_pos)) || temp_pos + 7 == curr_king_pos)) {
				if(temp_pos + 7 == curr_king_pos) {
					return TRUE;
				}
			}
			if(SOUTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SOUTH_OF(temp_pos)) || temp_pos + 8 == curr_king_pos)) {
				if(temp_pos + 8 == curr_king_pos) {
					return TRUE;
				}
			}
			if(SE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SE_OF(temp_pos)) || temp_pos + 9 == curr_king_pos)) {
				if(temp_pos + 9 == curr_king_pos) {
					return TRUE;
				}
			}
			continue;
		}

		/* pawn */
		if(IS_SET(opponent.p, i)) {
			/* regular pawn moves */
			Pos temp_pos = i;
			if(c == BLACK) { /* if current player is black, check where white pawns can move */
				if(NE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NE_OF(temp_pos)) || temp_pos - 7 == curr_king_pos)) {
					if(temp_pos - 7 == curr_king_pos) {
						return TRUE;
					}
				}
				if(NW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NW_OF(temp_pos)) || temp_pos - 9 == curr_king_pos)) {
					if(temp_pos - 9 == curr_king_pos) {
						return TRUE;
					}
				}
			}
			if(c == WHITE) { /* if current player is white, check where black pawns can move */
				if(SW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SW_OF(temp_pos)) || temp_pos + 7 == curr_king_pos)) {
					if(temp_pos + 7 == curr_king_pos) {
						return TRUE;
					}
				}
				if(SE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SE_OF(temp_pos)) || temp_pos + 9 == curr_king_pos)) {
					if(temp_pos + 9 == curr_king_pos) {
						return TRUE;
					}
				}
			}
			continue;
		}
	}
	return FALSE;
}

Board save_state(Board orig_pos){
	return orig_pos;
}

void simulate(PlayerColor c, Pos move, Pos orig_pos){
	if(get_piece_at(orig_pos,c) == ROOK){
		SET_BIT(player[c].r, move);
		RESET_BIT(player[c].r, orig_pos);
		if(OCCUPIED_D(c, move)){
			if(get_piece_at(move,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move);
			}
			if(get_piece_at(move,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move);
			}
			if(get_piece_at(move,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move);
			}
			if(get_piece_at(move,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move);
			}
			if(get_piece_at(move,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move);
			}
		}
	}
	if(get_piece_at(orig_pos,c) == BISHOP){
		SET_BIT(player[c].b, move);
		RESET_BIT(player[c].b, orig_pos);
		if(OCCUPIED_D(c, move)){
			if(get_piece_at(move,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move);
			}
			if(get_piece_at(move,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move);
			}
			if(get_piece_at(move,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move);
			}
			if(get_piece_at(move,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move);
			}
			if(get_piece_at(move,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move);
			}
		}
	}
	if(get_piece_at(orig_pos,c) == NIGHT){
		SET_BIT(player[c].n, move);
		RESET_BIT(player[c].n, orig_pos);
		if(OCCUPIED_D(c, move)){
			if(get_piece_at(move,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move);
			}
			if(get_piece_at(move,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move);
			}
			if(get_piece_at(move,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move);
			}
			if(get_piece_at(move,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move);
			}
			if(get_piece_at(move,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move);
			}
		}
	}
	if(get_piece_at(orig_pos,c) == QUEEN){
		SET_BIT(player[c].q, move);
		RESET_BIT(player[c].q, orig_pos);
		if(OCCUPIED_D(c, move)){
			if(get_piece_at(move,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move);
			}
			if(get_piece_at(move,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move);
			}
			if(get_piece_at(move,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move);
			}
			if(get_piece_at(move,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move);
			}
			if(get_piece_at(move,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move);
			}
		}
	}
	if(get_piece_at(orig_pos,c) == PAWN){
		SET_BIT(player[c].p, move);
		RESET_BIT(player[c].p, orig_pos);
		if(OCCUPIED_D(c, move)){
			if(get_piece_at(move,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move);
			}
			if(get_piece_at(move,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move);
			}
			if(get_piece_at(move,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move);
			}
			if(get_piece_at(move,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move);
			}
			if(get_piece_at(move,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move);
			}
		}
	}
	if(get_piece_at(orig_pos,c) == KING){
		SET_BIT(player[c].k, move);
		RESET_BIT(player[c].k, orig_pos);
		if(OCCUPIED_D(c, move)){
			if(get_piece_at(move,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move);
			}
			if(get_piece_at(move,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move);
			}
			if(get_piece_at(move,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move);
			}
			if(get_piece_at(move,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move);
			}
			if(get_piece_at(move,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move);
			}
		}
	}
}

void restore_state(Board *current, Board original){
	*current = original;
}

/* legal_moves:
for each of CurrentPlayer's pieces:
for each square an CurrentPlayer piece can move to:
save_state
make_move
if(king is under check) this is not a legal move, so restore state and skip it
else create a move structure and add it to the list.
restore state
*/

/* Given a color, this function returns a singly linked list of all legal Moves with the head at *m.
* The function returns TRUE if at least 1 legal move is available.
* The total number of moves found is stored in the address pointed to by pcount for verification of full traversal. */

Bool legal_moves(Move **m, PlayerColor c, unsigned int *pcount) {
	/*Iterate through each piece of PlayerColor, and check the possible TO positions of each piece,
	and for every TO position of each piece, if the TO position is not occupied on the full board or
	is occupied by an opposite color, add it to the linked list.*/
	Move *end_of_list = *m;
	/* Conditions:
	1. square not occupied by same color piece or
	2. move is within board limits i.e. 0 <= newPos < 64
	3. king is not put under check after move
	*/
	/* r, n, b, q, k, p */
	PlayerState saved_state2 = player[1 - c];
	int i;
	for(i = 0; i < 64; i++) {
		/* note: for rook, bishop, and queen, condition (1) includes opposite color piece */
		if(IS_SET(player[c].r, i)) {
			Pos temp_pos = i;
			Board saved_state = save_state(player[c].r);

			while(NORTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NORTH_OF(temp_pos)))) {
				simulate(c,NORTH_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = NORTH_OF(temp_pos);
					new_move->piece = ROOK;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2,NORTH_OF(temp_pos))) { /* means we have taken a piece and cannot move any further */
					break;
				}
				temp_pos -= 8;
			}
			temp_pos = i;
			restore_state(&player[c].r, saved_state);
			player[1-c] = saved_state2;


			while(WEST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, WEST_OF(temp_pos)))) {
				simulate(c,WEST_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = WEST_OF(temp_pos);
					new_move->piece = ROOK;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, WEST_OF(temp_pos))) {
					break;
				}
				temp_pos -= 1;
			}
			temp_pos = i;
			restore_state(&player[c].r, saved_state);
			player[1-c] = saved_state2;

			while(SOUTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SOUTH_OF(temp_pos)))) {
				simulate(c,SOUTH_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = SOUTH_OF(temp_pos);
					new_move->piece = ROOK;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, SOUTH_OF(temp_pos))) {
					break;
				}
				temp_pos += 8;
			}
			temp_pos = i;
			restore_state(&player[c].r, saved_state);
			player[1-c] = saved_state2;

			while(EAST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, EAST_OF(temp_pos)))) {
				simulate(c,EAST_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = EAST_OF(temp_pos);
					new_move->piece = ROOK;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, EAST_OF(temp_pos))) {
					break;
				}
				temp_pos += 1;
			}
			temp_pos = i;
			restore_state(&player[c].r, saved_state);
			player[1-c] = saved_state2;
			continue;
		}
		/* end of ROOK -------------------------------------------------------------------------------------------*/

		if(IS_SET(player[c].n, i)) {
			Board saved_state = save_state(player[c].n);

			if(EAST_OF(NE_OF(i)) != UNKNOWN_POS && (!OCCUPIED_S(c, EAST_OF(NE_OF(i))))) {
				simulate(c,EAST_OF(NE_OF(i)),i);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = EAST_OF(NE_OF(i));
					new_move->piece = NIGHT;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				restore_state(&player[c].n,saved_state);
				player[1-c] = saved_state2;
			}

			if(NORTH_OF(NE_OF(i)) != UNKNOWN_POS && (!OCCUPIED_S(c, NORTH_OF(NE_OF(i))))) {
				simulate(c,NORTH_OF(NE_OF(i)),i);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = NORTH_OF(NE_OF(i));
					new_move->piece = NIGHT;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				restore_state(&player[c].n,saved_state);
				player[1-c] = saved_state2;
			}

			if(NORTH_OF(NW_OF(i)) != UNKNOWN_POS && (!OCCUPIED_S(c, NORTH_OF(NW_OF(i))))) {
				simulate(c,NORTH_OF(NW_OF(i)),i);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = NORTH_OF(NW_OF(i));
					new_move->piece = NIGHT;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				restore_state(&player[c].n,saved_state);
				player[1-c] = saved_state2;
			}

			if(WEST_OF(NW_OF(i)) != UNKNOWN_POS && (!OCCUPIED_S(c, WEST_OF(NW_OF(i))))) {
				simulate(c,WEST_OF(NW_OF(i)),i);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = WEST_OF(NW_OF(i));
					new_move->piece = NIGHT;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				restore_state(&player[c].n,saved_state);
				player[1-c] = saved_state2;
			}

			if(WEST_OF(SW_OF(i)) != UNKNOWN_POS && (!OCCUPIED_S(c, WEST_OF(SW_OF(i))))) {
				simulate(c,WEST_OF(SW_OF(i)),i);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = WEST_OF(SW_OF(i));
					new_move->piece = NIGHT;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				restore_state(&player[c].n,saved_state);
				player[1-c] = saved_state2;
			}

			if(SOUTH_OF(SW_OF(i)) != UNKNOWN_POS && (!OCCUPIED_S(c, SOUTH_OF(SW_OF(i))))) {
				simulate(c,SOUTH_OF(SW_OF(i)),i);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = SOUTH_OF(SW_OF(i));
					new_move->piece = NIGHT;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				restore_state(&player[c].n,saved_state);
				player[1-c] = saved_state2;
			}

			if(SOUTH_OF(SE_OF(i)) != UNKNOWN_POS && (!OCCUPIED_S(c, SOUTH_OF(SE_OF(i))))) {
				simulate(c,SOUTH_OF(SE_OF(i)),i);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = SOUTH_OF(SE_OF(i));
					new_move->piece = NIGHT;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				restore_state(&player[c].n,saved_state);
				player[1-c] = saved_state2;
			}

			if(EAST_OF(SE_OF(i)) != UNKNOWN_POS && (!OCCUPIED_S(c, EAST_OF(SE_OF(i))))) {
				simulate(c,EAST_OF(SE_OF(i)),i);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = EAST_OF(SE_OF(i));
					new_move->piece = NIGHT;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				restore_state(&player[c].n,saved_state);
				player[1-c] = saved_state2;
			}
			continue;
		}
		/* end of KNIGHT  ----------------------------------------------------------------------------------------*/

		if(IS_SET(player[c].b, i)) {
			Pos temp_pos = i;
			Board saved_state = save_state(player[c].b);

			while(NE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NE_OF(temp_pos)))) {
				simulate(c,NE_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = NE_OF(temp_pos);
					new_move->piece = BISHOP;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, NE_OF(temp_pos))) {
					break;
				}
				temp_pos -= 7;
			}
			temp_pos = i;
			restore_state(&player[c].b, saved_state);
			player[1-c] = saved_state2;

			while(NW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NW_OF(temp_pos)))) {
				simulate(c,NW_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = NW_OF(temp_pos);
					new_move->piece = BISHOP;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, NW_OF(temp_pos))) {
					break;
				}
				temp_pos -= 9;
			}
			temp_pos = i;
			restore_state(&player[c].b, saved_state);
			player[1-c] = saved_state2;

			while(SW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SW_OF(temp_pos)))) {
				simulate(c,SW_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = SW_OF(temp_pos);
					new_move->piece = BISHOP;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, SW_OF(temp_pos))){
					break;
				}
				temp_pos += 7;
			}
			temp_pos = i;
			restore_state(&player[c].b, saved_state);
			player[1-c] = saved_state2;

			while(SE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SE_OF(temp_pos)))) {
				simulate(c,SE_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = SE_OF(temp_pos);
					new_move->piece = BISHOP;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, SE_OF(temp_pos))){
					break;
				}
				temp_pos += 9;
			}
			temp_pos = i;
			restore_state(&player[c].b, saved_state);
			player[1-c] = saved_state2;
			continue;
		}
		/* end of BISHOP -----------------------------------------------------------------------------------------*/

		if(IS_SET(player[c].q,i)){
			Pos temp_pos = i;
			Board saved_state = save_state(player[c].q);

			while(EAST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, EAST_OF(temp_pos)))) {
				simulate(c,EAST_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = EAST_OF(temp_pos);
					new_move->piece = QUEEN;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, EAST_OF(temp_pos))) {
					break;
				}
				temp_pos += 1;
			}
			temp_pos = i;
			restore_state(&player[c].q, saved_state);
			player[1-c] = saved_state2;

			while(NE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NE_OF(temp_pos)))) {
				simulate(c,NE_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = NE_OF(temp_pos);
					new_move->piece = QUEEN;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, NE_OF(temp_pos))) {
					break;
				}
				temp_pos -= 7;
			}
			temp_pos = i;
			restore_state(&player[c].q, saved_state);
			player[1-c] = saved_state2;

			while(NORTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NORTH_OF(temp_pos)))) {
				simulate(c,NORTH_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = NORTH_OF(temp_pos);
					new_move->piece = QUEEN;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, NORTH_OF(temp_pos))) {
					break;
				}
				temp_pos -= 8;
			}
			temp_pos = i;
			restore_state(&player[c].q, saved_state);
			player[1-c] = saved_state2;

			while(NW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NW_OF(temp_pos)))) {
				simulate(c,NW_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = NW_OF(temp_pos);
					new_move->piece = QUEEN;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, NW_OF(temp_pos))) {
					break;
				}
				temp_pos -= 9;
			}
			temp_pos = i;
			restore_state(&player[c].q, saved_state);
			player[1-c] = saved_state2;

			while(WEST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, WEST_OF(temp_pos)))) {
				simulate(c,WEST_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = WEST_OF(temp_pos);
					new_move->piece = QUEEN;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, WEST_OF(temp_pos))) {
					break;
				}
				temp_pos -= 1;
			}
			temp_pos = i;
			restore_state(&player[c].q, saved_state);
			player[1-c] = saved_state2;

			while(SW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SW_OF(temp_pos)))) {
				simulate(c,SW_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = SW_OF(temp_pos);
					new_move->piece = QUEEN;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, SW_OF(temp_pos))) {
					break;
				}
				temp_pos += 7;
			}
			temp_pos = i;
			restore_state(&player[c].q, saved_state);
			player[1-c] = saved_state2;

			while(SOUTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SOUTH_OF(temp_pos)))) {
				simulate(c,SOUTH_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = SOUTH_OF(temp_pos);
					new_move->piece = QUEEN;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, SOUTH_OF(temp_pos))) {
					break;
				}
				temp_pos += 8;
			}
			temp_pos = i;
			restore_state(&player[c].q, saved_state);
			player[1-c] = saved_state2;

			while(SE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SE_OF(temp_pos)))) {
				simulate(c,SE_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = i;
					new_move->to = SE_OF(temp_pos);
					new_move->piece = QUEEN;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
				if(OCCUPIED_SAVED(saved_state2, SE_OF(temp_pos))) {
					break;
				}
				temp_pos += 9;
			}
			temp_pos = i;
			restore_state(&player[c].q, saved_state);
			player[1-c] = saved_state2;
			continue;
		}
		/* end of QUEEN ------------------------------------------------------------------------------------------*/

		if(IS_SET(player[c].k, i)) {
			Pos temp_pos = i;
			Board saved_state = save_state(player[c].k);

			/* kingside castles */
			if(c == WHITE && temp_pos == 60) {
				if(!OCCUPIED(EAST_OF(EAST_OF(temp_pos))) && !OCCUPIED(EAST_OF(temp_pos)) && IS_SET(player[c].r, 63)) {
					simulate(c, EAST_OF(temp_pos), temp_pos);
					if(is_king_under_check(c) == FALSE) {
						restore_state(&player[c].k, saved_state);
						player[1-c] = saved_state2;
						simulate(c, EAST_OF(EAST_OF(temp_pos)), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = EAST_OF(EAST_OF(temp_pos));
							new_move->piece = KING;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
					}
					temp_pos = i;
					restore_state(&player[c].k, saved_state);
					player[1-c] = saved_state2;
				}
			}

			if(c == BLACK && temp_pos == 4) {
				if(!OCCUPIED(EAST_OF(EAST_OF(temp_pos))) && !OCCUPIED(EAST_OF(temp_pos)) && IS_SET(player[c].r, 7)) {
					simulate(c, EAST_OF(temp_pos), temp_pos);
					if(is_king_under_check(c) == FALSE) {
						restore_state(&player[c].k, saved_state);
						player[1-c] = saved_state2;
						simulate(c, EAST_OF(EAST_OF(temp_pos)), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = EAST_OF(EAST_OF(temp_pos));
							new_move->piece = KING;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
					}
					temp_pos = i;
					restore_state(&player[c].k, saved_state);
					player[1-c] = saved_state2;
				}
			}

			/* queenside castles */
			if(c == WHITE && temp_pos == 60) {
				if(!OCCUPIED(WEST_OF(WEST_OF(temp_pos))) && !OCCUPIED(WEST_OF(temp_pos)) && IS_SET(player[c].r, 56)) {
					simulate(c, WEST_OF(temp_pos), temp_pos);
					if(is_king_under_check(c) == FALSE) {
						restore_state(&player[c].k, saved_state);
						player[1-c] = saved_state2;
						simulate(c, WEST_OF(WEST_OF(temp_pos)), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = WEST_OF(WEST_OF(temp_pos));
							new_move->piece = KING;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
					}
					temp_pos = i;
					restore_state(&player[c].k, saved_state);
					player[1-c] = saved_state2;
				}
			}

			if(c == BLACK && temp_pos == 4) {
				if(!OCCUPIED(WEST_OF(WEST_OF(temp_pos))) && !OCCUPIED(WEST_OF(temp_pos)) && IS_SET(player[c].r, 0)) {
					simulate(c, WEST_OF(temp_pos), temp_pos);
					if(is_king_under_check(c) == FALSE) {
						restore_state(&player[c].k, saved_state);
						player[1-c] = saved_state2;
						simulate(c, WEST_OF(WEST_OF(temp_pos)), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = WEST_OF(WEST_OF(temp_pos));
							new_move->piece = KING;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
					}
					temp_pos = i;
					restore_state(&player[c].k, saved_state);
					player[1-c] = saved_state2;
				}
			}
			/**/

			if(EAST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, EAST_OF(temp_pos)))) {
				simulate(c,EAST_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = temp_pos;
					new_move->to = EAST_OF(temp_pos);
					new_move->piece = KING;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
			}
			temp_pos = i;
			restore_state(&player[c].k, saved_state);
			player[1-c] = saved_state2;

			if(NE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NE_OF(temp_pos)))) {
				simulate(c,NE_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = temp_pos;
					new_move->to = NE_OF(temp_pos);
					new_move->piece = KING;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
			}
			temp_pos = i;
			restore_state(&player[c].k, saved_state);
			player[1-c] = saved_state2;

			if(NORTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NORTH_OF(temp_pos)))) {
				simulate(c,NORTH_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = temp_pos;
					new_move->to = NORTH_OF(temp_pos);
					new_move->piece = KING;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
			}
			temp_pos = i;
			restore_state(&player[c].k, saved_state);
			player[1-c] = saved_state2;

			if(NW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, NW_OF(temp_pos)))) {
				simulate(c,NW_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = temp_pos;
					new_move->to = NW_OF(temp_pos);
					new_move->piece = KING;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
			}
			temp_pos = i;
			restore_state(&player[c].k, saved_state);
			player[1-c] = saved_state2;

			if(WEST_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, WEST_OF(temp_pos)))) {
				simulate(c,WEST_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = temp_pos;
					new_move->to = WEST_OF(temp_pos);
					new_move->piece = KING;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
			}
			temp_pos = i;
			restore_state(&player[c].k, saved_state);
			player[1-c] = saved_state2;

			if(SW_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SW_OF(temp_pos)))) {
				simulate(c,SW_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = temp_pos;
					new_move->to = SW_OF(temp_pos);
					new_move->piece = KING;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
			}
			temp_pos = i;
			restore_state(&player[c].k, saved_state);
			player[1-c] = saved_state2;

			if(SOUTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SOUTH_OF(temp_pos)))) {
				simulate(c,SOUTH_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = temp_pos;
					new_move->to = SOUTH_OF(temp_pos);
					new_move->piece = KING;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
			}
			temp_pos = i;
			restore_state(&player[c].k, saved_state);
			player[1-c] = saved_state2;

			if(SE_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED_S(c, SE_OF(temp_pos)))) {
				simulate(c,SE_OF(temp_pos),temp_pos);
				if(is_king_under_check(c) == FALSE) {
					Move *new_move = (Move *) malloc(1 * sizeof(Move));
					new_move->from = temp_pos;
					new_move->to = SE_OF(temp_pos);
					new_move->piece = KING;
					new_move->promotion_choice = UNKNOWN;
					new_move->next_move = NULL;
					end_of_list->next_move = new_move;
					end_of_list = end_of_list->next_move;
					*pcount += 1;
				}
			}
			temp_pos = i;
			restore_state(&player[c].k, saved_state);
			player[1-c] = saved_state2;
			continue;
		}
		/* end of KING -------------------------------------------------------------------------------------------*/

		if(IS_SET(player[c].p, i)) {
			Pos temp_pos = i;
			Board saved_state = save_state(player[c].p);

			if(c == WHITE) {
				if(i >= 48 && i <= 55){ /* if pawn is on rank 2 */
					if(NORTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NORTH_OF(temp_pos)))) {
						simulate(c,NORTH_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = NORTH_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(NORTH_OF(NORTH_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(NORTH_OF(NORTH_OF(temp_pos)))) && (!OCCUPIED(NORTH_OF(temp_pos)))) {
						simulate(c,NORTH_OF(NORTH_OF(temp_pos)),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = NORTH_OF(NORTH_OF(temp_pos));
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
							/*ep_square = NORTH_OF(temp_pos);*/
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(NE_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, NE_OF(temp_pos)))) {
						simulate(c, NE_OF(temp_pos), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = NE_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(NW_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, NW_OF(temp_pos)))) {
						simulate(c, NW_OF(temp_pos), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = NW_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
				}
				else if(i >= 8 && i <= 15){ /* if pawn is on rank 7, consider promotions when moving forward*/
					if(NORTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NORTH_OF(temp_pos)))) {
						simulate(c,NORTH_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							/*Move *new_move0 = (Move *) malloc(1 * sizeof(Move));
							new_move0->from = temp_pos;
							new_move0->to = NORTH_OF(temp_pos);
							new_move0->piece = PAWN;
							new_move0->promotion_choice = UNKNOWN;
							new_move0->next_move = NULL;
							end_of_list->next_move = new_move0;
							end_of_list = end_of_list->next_move;
							*pcount += 1;*/

							Move *new_move1 = (Move *) malloc(1 * sizeof(Move));
							new_move1->from = temp_pos;
							new_move1->to = NORTH_OF(temp_pos);
							new_move1->piece = PAWN;
							new_move1->promotion_choice = QUEEN;
							new_move1->next_move = NULL;
							end_of_list->next_move = new_move1;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move2 = (Move *) malloc(1 * sizeof(Move));
							new_move2->from = temp_pos;
							new_move2->to = NORTH_OF(temp_pos);
							new_move2->piece = PAWN;
							new_move2->promotion_choice = ROOK;
							new_move2->next_move = NULL;
							end_of_list->next_move = new_move2;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move3 = (Move *) malloc(1 * sizeof(Move));
							new_move3->from = temp_pos;
							new_move3->to = NORTH_OF(temp_pos);
							new_move3->piece = PAWN;
							new_move3->promotion_choice = BISHOP;
							new_move3->next_move = NULL;
							end_of_list->next_move = new_move3;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move4 = (Move *) malloc(1 * sizeof(Move));
							new_move4->from = temp_pos;
							new_move4->to = NORTH_OF(temp_pos);
							new_move4->piece = PAWN;
							new_move4->promotion_choice = NIGHT;
							new_move4->next_move = NULL;
							end_of_list->next_move = new_move4;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(NE_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, NE_OF(temp_pos)))) {
						simulate(c,NE_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							/*Move *new_move0 = (Move *) malloc(1 * sizeof(Move));
							new_move0->from = temp_pos;
							new_move0->to = NE_OF(temp_pos);
							new_move0->piece = PAWN;
							new_move0->promotion_choice = UNKNOWN;
							new_move0->next_move = NULL;
							end_of_list->next_move = new_move0;
							end_of_list = end_of_list->next_move;
							*pcount += 1;*/

							Move *new_move1 = (Move *) malloc(1 * sizeof(Move));
							new_move1->from = temp_pos;
							new_move1->to = NE_OF(temp_pos);
							new_move1->piece = PAWN;
							new_move1->promotion_choice = QUEEN;
							new_move1->next_move = NULL;
							end_of_list->next_move = new_move1;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move2 = (Move *) malloc(1 * sizeof(Move));
							new_move2->from = temp_pos;
							new_move2->to = NE_OF(temp_pos);
							new_move2->piece = PAWN;
							new_move2->promotion_choice = ROOK;
							new_move2->next_move = NULL;
							end_of_list->next_move = new_move2;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move3 = (Move *) malloc(1 * sizeof(Move));
							new_move3->from = temp_pos;
							new_move3->to = NE_OF(temp_pos);
							new_move3->piece = PAWN;
							new_move3->promotion_choice = BISHOP;
							new_move3->next_move = NULL;
							end_of_list->next_move = new_move3;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move4 = (Move *) malloc(1 * sizeof(Move));
							new_move4->from = temp_pos;
							new_move4->to = NE_OF(temp_pos);
							new_move4->piece = PAWN;
							new_move4->promotion_choice = NIGHT;
							new_move4->next_move = NULL;
							end_of_list->next_move = new_move4;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(NW_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, NW_OF(temp_pos)))) {
						simulate(c,NW_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							/*Move *new_move0 = (Move *) malloc(1 * sizeof(Move));
							new_move0->from = temp_pos;
							new_move0->to = NW_OF(temp_pos);
							new_move0->piece = PAWN;
							new_move0->promotion_choice = UNKNOWN;
							new_move0->next_move = NULL;
							end_of_list->next_move = new_move0;
							end_of_list = end_of_list->next_move;
							*pcount += 1;*/

							Move *new_move1 = (Move *) malloc(1 * sizeof(Move));
							new_move1->from = temp_pos;
							new_move1->to = NW_OF(temp_pos);
							new_move1->piece = PAWN;
							new_move1->promotion_choice = QUEEN;
							new_move1->next_move = NULL;
							end_of_list->next_move = new_move1;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move2 = (Move *) malloc(1 * sizeof(Move));
							new_move2->from = temp_pos;
							new_move2->to = NW_OF(temp_pos);
							new_move2->piece = PAWN;
							new_move2->promotion_choice = ROOK;
							new_move2->next_move = NULL;
							end_of_list->next_move = new_move2;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move3 = (Move *) malloc(1 * sizeof(Move));
							new_move3->from = temp_pos;
							new_move3->to = NW_OF(temp_pos);
							new_move3->piece = PAWN;
							new_move3->promotion_choice = BISHOP;
							new_move3->next_move = NULL;
							end_of_list->next_move = new_move3;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move4 = (Move *) malloc(1 * sizeof(Move));
							new_move4->from = temp_pos;
							new_move4->to = NW_OF(temp_pos);
							new_move4->piece = PAWN;
							new_move4->promotion_choice = NIGHT;
							new_move4->next_move = NULL;
							end_of_list->next_move = new_move4;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
				}
				else{ /* consider ep square, and also regular pawn moves and captures */
					if(i >= 24 && i <= 31){
						if(NE_OF(temp_pos) == ep_square){
							simulate(c, NE_OF(temp_pos), temp_pos);
							if(is_king_under_check(c) == FALSE) {
								Move *new_move = (Move *) malloc(1 * sizeof(Move));
								new_move->from = temp_pos;
								new_move->to = NE_OF(temp_pos);
								new_move->piece = PAWN;
								new_move->promotion_choice = UNKNOWN;
								new_move->next_move = NULL;
								end_of_list->next_move = new_move;
								end_of_list = end_of_list->next_move;
								*pcount += 1;
							}
							temp_pos = i;
							restore_state(&player[c].p, saved_state);
							player[1-c] = saved_state2;
						}
						if(NW_OF(temp_pos) == ep_square){
							simulate(c, NW_OF(temp_pos), temp_pos);
							if(is_king_under_check(c) == FALSE) {
								Move *new_move = (Move *) malloc(1 * sizeof(Move));
								new_move->from = temp_pos;
								new_move->to = NW_OF(temp_pos);
								new_move->piece = PAWN;
								new_move->promotion_choice = UNKNOWN;
								new_move->next_move = NULL;
								end_of_list->next_move = new_move;
								end_of_list = end_of_list->next_move;
								*pcount += 1;
							}
							temp_pos = i;
							restore_state(&player[c].p, saved_state);
							player[1-c] = saved_state2;
						}
					}
					if(NORTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(NORTH_OF(temp_pos)))) {
						simulate(c,NORTH_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = NORTH_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(NE_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, NE_OF(temp_pos)))) {
						simulate(c, NE_OF(temp_pos), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = NE_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(NW_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, NW_OF(temp_pos)))) {
						simulate(c, NW_OF(temp_pos), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = NW_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
				}
			}
			if(c == BLACK){
				if(i >= 8 && i <= 15){ /* if pawn is on rank 7 */
					if(SOUTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SOUTH_OF(temp_pos)))) {
						simulate(c,SOUTH_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = SOUTH_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(SOUTH_OF(SOUTH_OF(temp_pos)) != UNKNOWN_POS && (!OCCUPIED(SOUTH_OF(SOUTH_OF(temp_pos)))) && (!OCCUPIED(SOUTH_OF(temp_pos)))) {
						simulate(c,SOUTH_OF(SOUTH_OF(temp_pos)),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = SOUTH_OF(SOUTH_OF(temp_pos));
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
							/*ep_square = SOUTH_OF(temp_pos);*/
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(SE_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, SE_OF(temp_pos)))) {
						simulate(c, SE_OF(temp_pos), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = SE_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(SW_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, SW_OF(temp_pos)))) {
						simulate(c, SW_OF(temp_pos), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = SW_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
				}
				else if(i >= 48 && i <= 55){ /* if pawn is on rank 2, consider promotions when moving forward */
					if(SOUTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SOUTH_OF(temp_pos)))) {
						simulate(c,SOUTH_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							/*Move *new_move0 = (Move *) malloc(1 * sizeof(Move));
							new_move0->from = temp_pos;
							new_move0->to = SOUTH_OF(temp_pos);
							new_move0->piece = PAWN;
							new_move0->promotion_choice = UNKNOWN;
							new_move0->next_move = NULL;
							end_of_list->next_move = new_move0;
							end_of_list = end_of_list->next_move;
							*pcount += 1;*/

							Move *new_move1 = (Move *) malloc(1 * sizeof(Move));
							new_move1->from = temp_pos;
							new_move1->to = SOUTH_OF(temp_pos);
							new_move1->piece = PAWN;
							new_move1->promotion_choice = QUEEN;
							new_move1->next_move = NULL;
							end_of_list->next_move = new_move1;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move2 = (Move *) malloc(1 * sizeof(Move));
							new_move2->from = temp_pos;
							new_move2->to = SOUTH_OF(temp_pos);
							new_move2->piece = PAWN;
							new_move2->promotion_choice = ROOK;
							new_move2->next_move = NULL;
							end_of_list->next_move = new_move2;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move3 = (Move *) malloc(1 * sizeof(Move));
							new_move3->from = temp_pos;
							new_move3->to = SOUTH_OF(temp_pos);
							new_move3->piece = PAWN;
							new_move3->promotion_choice = BISHOP;
							new_move3->next_move = NULL;
							end_of_list->next_move = new_move3;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move4 = (Move *) malloc(1 * sizeof(Move));
							new_move4->from = temp_pos;
							new_move4->to = SOUTH_OF(temp_pos);
							new_move4->piece = PAWN;
							new_move4->promotion_choice = NIGHT;
							new_move4->next_move = NULL;
							end_of_list->next_move = new_move4;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(SE_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, SE_OF(temp_pos)))) {
						simulate(c,SE_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							/*Move *new_move0 = (Move *) malloc(1 * sizeof(Move));
							new_move0->from = temp_pos;
							new_move0->to = SE_OF(temp_pos);
							new_move0->piece = PAWN;
							new_move0->promotion_choice = UNKNOWN;
							new_move0->next_move = NULL;
							end_of_list->next_move = new_move0;
							end_of_list = end_of_list->next_move;
							*pcount += 1;*/

							Move *new_move1 = (Move *) malloc(1 * sizeof(Move));
							new_move1->from = temp_pos;
							new_move1->to = SE_OF(temp_pos);
							new_move1->piece = PAWN;
							new_move1->promotion_choice = QUEEN;
							new_move1->next_move = NULL;
							end_of_list->next_move = new_move1;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move2 = (Move *) malloc(1 * sizeof(Move));
							new_move2->from = temp_pos;
							new_move2->to = SE_OF(temp_pos);
							new_move2->piece = PAWN;
							new_move2->promotion_choice = ROOK;
							new_move2->next_move = NULL;
							end_of_list->next_move = new_move2;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move3 = (Move *) malloc(1 * sizeof(Move));
							new_move3->from = temp_pos;
							new_move3->to = SE_OF(temp_pos);
							new_move3->piece = PAWN;
							new_move3->promotion_choice = BISHOP;
							new_move3->next_move = NULL;
							end_of_list->next_move = new_move3;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move4 = (Move *) malloc(1 * sizeof(Move));
							new_move4->from = temp_pos;
							new_move4->to = SE_OF(temp_pos);
							new_move4->piece = PAWN;
							new_move4->promotion_choice = NIGHT;
							new_move4->next_move = NULL;
							end_of_list->next_move = new_move4;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(SW_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, SW_OF(temp_pos)))) {
						simulate(c,SW_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							/*Move *new_move0 = (Move *) malloc(1 * sizeof(Move));
							new_move0->from = temp_pos;
							new_move0->to = SW_OF(temp_pos);
							new_move0->piece = PAWN;
							new_move0->promotion_choice = UNKNOWN;
							new_move0->next_move = NULL;
							end_of_list->next_move = new_move0;
							end_of_list = end_of_list->next_move;
							*pcount += 1;*/

							Move *new_move1 = (Move *) malloc(1 * sizeof(Move));
							new_move1->from = temp_pos;
							new_move1->to = SW_OF(temp_pos);
							new_move1->piece = PAWN;
							new_move1->promotion_choice = QUEEN;
							new_move1->next_move = NULL;
							end_of_list->next_move = new_move1;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move2 = (Move *) malloc(1 * sizeof(Move));
							new_move2->from = temp_pos;
							new_move2->to = SW_OF(temp_pos);
							new_move2->piece = PAWN;
							new_move2->promotion_choice = ROOK;
							new_move2->next_move = NULL;
							end_of_list->next_move = new_move2;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move3 = (Move *) malloc(1 * sizeof(Move));
							new_move3->from = temp_pos;
							new_move3->to = SW_OF(temp_pos);
							new_move3->piece = PAWN;
							new_move3->promotion_choice = BISHOP;
							new_move3->next_move = NULL;
							end_of_list->next_move = new_move3;
							end_of_list = end_of_list->next_move;
							*pcount += 1;

							Move *new_move4 = (Move *) malloc(1 * sizeof(Move));
							new_move4->from = temp_pos;
							new_move4->to = SW_OF(temp_pos);
							new_move4->piece = PAWN;
							new_move4->promotion_choice = NIGHT;
							new_move4->next_move = NULL;
							end_of_list->next_move = new_move4;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
				}
				else{
					if(i >= 32 && i <= 39){ /* consider rest of pawn moves including en passant captures */
						if(SE_OF(temp_pos) == ep_square){
							simulate(c, SE_OF(temp_pos), temp_pos);
							if(is_king_under_check(c) == FALSE) {
								Move *new_move = (Move *) malloc(1 * sizeof(Move));
								new_move->from = temp_pos;
								new_move->to = SE_OF(temp_pos);
								new_move->piece = PAWN;
								new_move->promotion_choice = UNKNOWN;
								new_move->next_move = NULL;
								end_of_list->next_move = new_move;
								end_of_list = end_of_list->next_move;
								*pcount += 1;
							}
							temp_pos = i;
							restore_state(&player[c].p, saved_state);
							player[1-c] = saved_state2;
						}
						if(SW_OF(temp_pos) == ep_square){
							simulate(c, SW_OF(temp_pos), temp_pos);
							if(is_king_under_check(c) == FALSE) {
								Move *new_move = (Move *) malloc(1 * sizeof(Move));
								new_move->from = temp_pos;
								new_move->to = SW_OF(temp_pos);
								new_move->piece = PAWN;
								new_move->promotion_choice = UNKNOWN;
								new_move->next_move = NULL;
								end_of_list->next_move = new_move;
								end_of_list = end_of_list->next_move;
								*pcount += 1;
							}
							temp_pos = i;
							restore_state(&player[c].p, saved_state);
							player[1-c] = saved_state2;
						}
					}
					if(SOUTH_OF(temp_pos) != UNKNOWN_POS && (!OCCUPIED(SOUTH_OF(temp_pos)))) {
						simulate(c,SOUTH_OF(temp_pos),temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = SOUTH_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(SE_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, SE_OF(temp_pos)))) {
						simulate(c, SE_OF(temp_pos), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = SE_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
					if(SW_OF(temp_pos) != UNKNOWN_POS && (OCCUPIED_D(c, SW_OF(temp_pos)))) {
						simulate(c, SW_OF(temp_pos), temp_pos);
						if(is_king_under_check(c) == FALSE) {
							Move *new_move = (Move *) malloc(1 * sizeof(Move));
							new_move->from = temp_pos;
							new_move->to = SW_OF(temp_pos);
							new_move->piece = PAWN;
							new_move->promotion_choice = UNKNOWN;
							new_move->next_move = NULL;
							end_of_list->next_move = new_move;
							end_of_list = end_of_list->next_move;
							*pcount += 1;
						}
						temp_pos = i;
						restore_state(&player[c].p, saved_state);
						player[1-c] = saved_state2;
					}
				}
			}
			continue;
		}
		/* end of PAWN -------------------------------------------------------------------------------------------*/
	}
	/* if no legal moves exist, return FALSE, else return TRUE */
	end_of_list->next_move = NULL;
	if(*pcount == 0) {
		return FALSE;
	}
	return TRUE;
}

/* Returns TRUE if the CurrentPlayer is under checkmate, FALSE otherwise. */
Bool is_checkmate(PlayerColor c) {
	/* if CurrentPlayer's king is currently under check, AND
	* legal moves list is empty, then
	* checkmate is TRUE */
	if(is_king_under_check(c) == FALSE) {
		return FALSE;
	}

	unsigned int count = 0;
	unsigned int *pcount = &count;
	Move *moves_head = (Move *) malloc (1*sizeof(Move));
	if(legal_moves(&moves_head, c, pcount) == TRUE) {
		freeList(moves_head);
		return FALSE;
	}
	freeList(moves_head);
	return TRUE;
}

/* Validate a move and make it, change CurrentPlayer. Returns TRUE if successful, FALSE if not.
*  Error message if any, are stored in *msg.
* ep_square (if any) is stored in *ep_sq
*/

Bool validate_and_move(Move *move, PlayerColor c, Pos *ep_sq) {
	/*	Conditions we have to "validate": rook, pawn,castle */
	/* validate and make castling moves */
	if(detect_castle_move(*move, c) != 0) {
		if(player[c].castle_flags == 0) {
			return FALSE;
		}
		if(player[c].castle_flags == 1 && detect_castle_move(*move, c) == 1) {
			perform_castle(1, c);
			return TRUE;
		}
		if(player[c].castle_flags == 2 && detect_castle_move(*move, c) == 2) {
			perform_castle(2, c);
			return TRUE;
		}
		if(player[c].castle_flags == 3 && (detect_castle_move(*move, c) == 1 || (detect_castle_move(*move, c) == 2))) {
			perform_castle(detect_castle_move(*move, c),c);
			return TRUE;
		}
		return FALSE;
	}
	/* If the move piece is a ROOK, then we do the following:
		Move the rook on the player's board and update it
		Check if it captures, and if it does, update the opponents board
		Update castle flags depending on which side the rook moved from
	*/
	if(move->piece == ROOK) {
		RESET_BIT(player[c].r, move->from);
		SET_BIT(player[c].r, move->to);
		if(OCCUPIED_D(c, move->to)){
			if(get_piece_at(move->to,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move->to);
			}
			if(get_piece_at(move->to,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move->to);
			}
			if(get_piece_at(move->to,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move->to);
			}
			if(get_piece_at(move->to,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move->to);
			}
			if(get_piece_at(move->to,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move->to);
			}
		}
		if(c == WHITE){
			if(move->from == 56){
				if(player[c].castle_flags == 3){
					player[c].castle_flags = 1;
				}
				if(player[c].castle_flags == 2){
					player[c].castle_flags = 0;
				}
			}
			if(move->from == 63){
				if(player[c].castle_flags == 3){
					player[c].castle_flags = 1;
				}
				if(player[c].castle_flags == 1){
					player[c].castle_flags = 0;
				}
			}
		}
		else if(c == BLACK){
			if(move->from == 0){
				if(player[c].castle_flags == 3){
					player[c].castle_flags = 1;
				}
				if(player[c].castle_flags == 2){
					player[c].castle_flags = 0;
				}
			}
			else if(move->from == 7){
				if(player[c].castle_flags == 3){
					player[c].castle_flags = 2;
				}
				if(player[c].castle_flags == 1){
					player[c].castle_flags = 0;
				}
			}
		}
		return TRUE;
	}
	if(move->piece == KING) {
		RESET_BIT(player[c].k, move->from);
		SET_BIT(player[c].k, move->to);
		if(OCCUPIED_D(c, move->to)){
			if(get_piece_at(move->to,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move->to);
			}
			if(get_piece_at(move->to,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move->to);
			}
			if(get_piece_at(move->to,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move->to);
			}
			if(get_piece_at(move->to,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move->to);
			}
			if(get_piece_at(move->to,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move->to);
			}
		}
		player[c].castle_flags = 0;
		return TRUE;
	}
	if(move->piece == BISHOP){
		RESET_BIT(player[c].b, move->from);
		SET_BIT(player[c].b, move->to);
		if(OCCUPIED_D(c, move->to)){
			if(get_piece_at(move->to,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move->to);
			}
			if(get_piece_at(move->to,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move->to);
			}
			if(get_piece_at(move->to,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move->to);
			}
			if(get_piece_at(move->to,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move->to);
			}
			if(get_piece_at(move->to,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move->to);
			}
		}
		return TRUE;
	}
	if(move->piece == NIGHT){
		RESET_BIT(player[c].n, move->from);
		SET_BIT(player[c].n, move->to);
		if(OCCUPIED_D(c, move->to)){
			if(get_piece_at(move->to,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move->to);
			}
			if(get_piece_at(move->to,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move->to);
			}
			if(get_piece_at(move->to,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move->to);
			}
			if(get_piece_at(move->to,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move->to);
			}
			if(get_piece_at(move->to,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move->to);
			}
		}
		return TRUE;
	}
	if(move->piece == QUEEN){
		RESET_BIT(player[c].q, move->from);
		SET_BIT(player[c].q, move->to);
		if(OCCUPIED_D(c, move->to)){
			if(get_piece_at(move->to,1-c) == ROOK){
				RESET_BIT(player[1-c].r,move->to);
			}
			if(get_piece_at(move->to,1-c) == BISHOP){
				RESET_BIT(player[1-c].b,move->to);
			}
			if(get_piece_at(move->to,1-c) == NIGHT){
				RESET_BIT(player[1-c].n,move->to);
			}
			if(get_piece_at(move->to,1-c) == QUEEN){
				RESET_BIT(player[1-c].q,move->to);
			}
			if(get_piece_at(move->to,1-c) == PAWN){
				RESET_BIT(player[1-c].p,move->to);
			}
		}
		return TRUE;
	}
	if(move->piece == PAWN){
		/* If it is an attempted ep_sq capture, we have to first validate.
			Depending on the color, the piece directly above or below the ep_sq
			should be occupied by the enemy's pawn board
	*/
		if(move->to == *ep_sq){
			if(c == BLACK){
				if(IS_SET(player[1-c].p,*ep_sq - 8)){
					SET_BIT(player[c].p, move->to);
					RESET_BIT(player[c].p,move->from);
					RESET_BIT(player[1-c].p,*ep_sq - 8);
					*ep_sq = UNKNOWN_POS;
					return TRUE;
				}
				else{
					return FALSE;
				}
			}
			if(c == WHITE){
				if(IS_SET(player[1-c].p, *ep_sq + 8)){
					SET_BIT(player[c].p, move->to);
					RESET_BIT(player[c].p,move->from);
					RESET_BIT(player[1-c].p,*ep_sq + 8);
					*ep_sq = UNKNOWN_POS;
					return TRUE;
				}
				else{
					return FALSE;
				}
			}
		}
		/* If pawn moves forward two spaces,
			then set the ep_sq one space directly behind pawn to
			*/
		if(c == BLACK){
			if(move->from >=  8 && move->from <= 15){
				if(move->to == move->from + 16){
					*ep_sq = move->from + 8;
				}
			}
		}
		if(c == WHITE){
			if(move->from >= 48 && move->from <= 55){
				if(move->to == move->from - 16){
					*ep_sq = move->from - 8;
				}
			}
		}
		/* Update board depending on promotion option */
		if((move->promotion_choice != UNKNOWN)) {
			RESET_BIT(player[c].p, move->from);
			if(OCCUPIED_D(c, move->to)) {
				if(get_piece_at(move->to,1-c) == ROOK) {
					RESET_BIT(player[1-c].r,move->to);
				}
				if(get_piece_at(move->to,1-c) == BISHOP) {
					RESET_BIT(player[1-c].b,move->to);
				}
				if(get_piece_at(move->to,1-c) == NIGHT) {
					RESET_BIT(player[1-c].n,move->to);
				}
				if(get_piece_at(move->to,1-c) == QUEEN) {
					RESET_BIT(player[1-c].q,move->to);
				}
				if(get_piece_at(move->to,1-c) == PAWN) {
					RESET_BIT(player[1-c].p,move->to);
				}
			}
			if(move->promotion_choice == ROOK) {
				SET_BIT(player[c].r, move->to);
			}
			if(move->promotion_choice == BISHOP) {
				SET_BIT(player[c].b, move->to);
			}
			if(move->promotion_choice == NIGHT) {
				SET_BIT(player[c].n, move->to);
			}
			if(move->promotion_choice == QUEEN) {
				SET_BIT(player[c].q, move->to);
			}
			if(move->promotion_choice == ROOK) {
				SET_BIT(player[c].r, move->to);
			}
			return TRUE;
		}
		/* Normal capture */
		RESET_BIT(player[c].p, move->from);
		SET_BIT(player[c].p, move->to);
		if(OCCUPIED_D(c, move->to)){
			if(get_piece_at(move->to,1-c) == ROOK) {
				RESET_BIT(player[1-c].r,move->to);
			}
			if(get_piece_at(move->to,1-c) == BISHOP) {
				RESET_BIT(player[1-c].b,move->to);
			}
			if(get_piece_at(move->to,1-c) == NIGHT) {
				RESET_BIT(player[1-c].n,move->to);
			}
			if(get_piece_at(move->to,1-c) == QUEEN) {
				RESET_BIT(player[1-c].q,move->to);
			}
			if(get_piece_at(move->to,1-c) == PAWN) {
				RESET_BIT(player[1-c].p,move->to);
			}
		}
		return TRUE;
	}
	return FALSE;
}


/* Function to decide whether the current position is a draw
 Draw can be due to insufficient material, 3 move repetition or stalemate
3 move repetition also covers perpetual check */

Bool is_draw() {
	Move *moves_head = (Move *) malloc(1 * sizeof(Move));
	unsigned int count = 0;
	unsigned int *pcount = &count;

	/* if king is not under check, but has no legal moves left, it is a draw */
	if(is_king_under_check(CurrentPlayer) == FALSE && legal_moves(&moves_head, CurrentPlayer, pcount) == FALSE) {
		freeList(moves_head);
		return TRUE;
	}
	/* if both players only have a single king each left on the board, it is a draw */
	if(player[CurrentPlayer].r == 0 && player[CurrentPlayer].n == 0 && player[CurrentPlayer].b == 0 &&
		player[CurrentPlayer].q == 0 && player[CurrentPlayer].k != 0 && player[CurrentPlayer].p == 0 &&
		player[1 - CurrentPlayer].r == 0 && player[1 - CurrentPlayer].n == 0 && player[1 - CurrentPlayer].b == 0 &&
		player[1 - CurrentPlayer].q == 0 && player[1 - CurrentPlayer].k != 0 && player[1 - CurrentPlayer].p == 0) {
			freeList(moves_head);
			return TRUE;
	}

	freeList(moves_head);
	return FALSE;
}

/* Returns the piece on a square belonging to player color c.
 If there is no piece with color c, UNKNOWN is returned. */
Piece get_piece_at(Pos pos, PlayerColor c) {
	/*player = [BLACK,WHITE]*/
	/*player[BLACK] = struct of black player_state*/
	/*player[WHITE] = struct of white player_state*/
	if(IS_SET(player[c].r, pos)) return ROOK;
    if(IS_SET(player[c].q, pos)) return QUEEN;
    if(IS_SET(player[c].b, pos)) return BISHOP;
    if(IS_SET(player[c].p, pos)) return PAWN;
    if(IS_SET(player[c].k, pos)) return KING;
    if(IS_SET(player[c].n, pos)) return NIGHT;

	return UNKNOWN;
}

/* Check if this move is trying to castle */
unsigned int detect_castle_move(Move move, PlayerColor c) {
	if(move.piece != KING){
		return 0;
	}
	if(move.to == EAST_OF(EAST_OF(move.from))) {
		return 1;
	} else if(move.to == WEST_OF(WEST_OF(move.from))) {
		return 2;
	}
	return 0;
}

/* Perform castling. Moves king and rook and resets castle flags */
void perform_castle(unsigned int castle, PlayerColor c) {
	if(c == WHITE){
		if(castle == 1){
			RESET_BIT(player[c].k,king_pos(c));
			SET_BIT(player[c].k,62);
			SET_BIT(player[c].r,61);
			RESET_BIT(player[c].r,63);
		}
		if(castle == 2){
			RESET_BIT(player[c].k,king_pos(c));
			SET_BIT(player[c].k,58);
			SET_BIT(player[c].r,59);
			RESET_BIT(player[c].r,56);
		}
	}
	if(c == BLACK){
		if(castle == 1){
			RESET_BIT(player[c].k,king_pos(c));
			SET_BIT(player[c].k,6);
			SET_BIT(player[c].r,5);
			RESET_BIT(player[c].k,7);
		}
		if(castle == 2){
			RESET_BIT(player[c].k,king_pos(c));
			SET_BIT(player[c].k,2);
			SET_BIT(player[c].r,3);
			RESET_BIT(player[c].r,0);
		}
	}
}
