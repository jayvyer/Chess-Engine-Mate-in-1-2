#include "io.h"
#include <stdio.h>
#include "chess.h"
#include "moves.h"


char get_piece_char(Pos pos){
    /*player = [BLACK,WHITE]*/
    /*player[0] = struct of black player state*/
    /*player[1] = struct of white player state*/

    if(IS_SET(player[WHITE].r, pos)) return 'R';
    if(IS_SET(player[WHITE].q, pos)) return 'Q';
    if(IS_SET(player[WHITE].b, pos)) return 'B';
    if(IS_SET(player[WHITE].p, pos)) return 'P';
    if(IS_SET(player[WHITE].k, pos)) return 'K';
    if(IS_SET(player[WHITE].n, pos)) return 'N';

    if(IS_SET(player[BLACK].r, pos)) return 'r';
    if(IS_SET(player[BLACK].q, pos)) return 'q';
    if(IS_SET(player[BLACK].b, pos)) return 'b';
    if(IS_SET(player[BLACK].p, pos)) return 'p';
    if(IS_SET(player[BLACK].k, pos)) return 'k';
    if(IS_SET(player[BLACK].n, pos)) return 'n';
    return ' ';
}

void display_board() {
    unsigned int i = 0, j = 0;
    printf("\n −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");
    for(i = 0; i < 8; i++) {
        printf("%d |", 8 - i);
        for(j = 0; j < 8; j++) {
            printf(" %c |", get_piece_char(i * 8 + j));
        }
        printf("\n −−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");
    }
    printf("    a   b   c   d   e   f   g   h\n");
    printf("\n");
}

Bool parse_board(char *board) {
    /* parses the input string and sets the corresponding global variables.
    If the entire thing is set correctly, then return True as Bool. Otherwise, return False as Bool. */
    int R_Count = 0, Q_Count = 0, B_Count = 0, P_Count = 0, K_Count = 0, N_Count = 0;
    int r_Count = 0, q_Count = 0, b_Count = 0, p_Count = 0, k_Count = 0, n_Count = 0;
    int Count = 0;
    int i = 0;
    player[WHITE].r &= ~UNKNOWN_POS;
    player[WHITE].n &= ~UNKNOWN_POS;
    player[WHITE].b &= ~UNKNOWN_POS;
    player[WHITE].q &= ~UNKNOWN_POS;
    player[WHITE].k &= ~UNKNOWN_POS;
    player[WHITE].p &= ~UNKNOWN_POS;

    player[BLACK].r &= ~UNKNOWN_POS;
    player[BLACK].n &= ~UNKNOWN_POS;
    player[BLACK].b &= ~UNKNOWN_POS;
    player[BLACK].q &= ~UNKNOWN_POS;
    player[BLACK].k &= ~UNKNOWN_POS;
    player[BLACK].p &= ~UNKNOWN_POS;

    player[WHITE].castle_flags = NO_CASTLE;
    player[BLACK].castle_flags = NO_CASTLE;

    /* parse pieces on board */
    while(board[i] != ' ' && Count <= 63) {
        switch(board[i]){
            case 'R':
            R_Count += 1;
            Count += 1;
            SET_BIT(player[WHITE].r, Count - 1);
            break;
            case 'Q':
            Q_Count += 1;
            Count += 1;
            SET_BIT(player[WHITE].q, Count - 1);
            break;
            case 'B':
            B_Count += 1;
            Count += 1;
            SET_BIT(player[WHITE].b, Count - 1);
            break;
            case 'P':
            /*check that white pawns cannot be on the first rank*/
            if(Count < 8) {
                printf("white pawns on first rank\n");
                return FALSE;
            }
            P_Count += 1;
            Count += 1;
            SET_BIT(player[WHITE].p, Count - 1);
            break;
            case 'K':
            K_Count += 1;
            Count += 1;
            SET_BIT(player[WHITE].k, Count - 1);
            break;
            case 'N':
            N_Count += 1;
            Count += 1;
            SET_BIT(player[WHITE].n, Count - 1);
            break;
            /*lower cases*/
            case 'r':
            r_Count += 1;
            Count += 1;
            SET_BIT(player[BLACK].r, Count - 1);
            break;
            case 'q':
            q_Count += 1;
            Count += 1;
            SET_BIT(player[BLACK].q, Count - 1);
            break;
            case 'b':
            b_Count += 1;
            Count += 1;
            SET_BIT(player[BLACK].b, Count - 1);
            break;
            case 'p':
            /*check that black pawns cannot be on the eighth rank*/
            if(Count >= 56) {
                printf("black pawns on first rank\n");
                return FALSE;
            }
            p_Count += 1;
            Count += 1;
            SET_BIT(player[BLACK].p, Count - 1);
            break;
            case 'k':
            k_Count += 1;
            Count += 1;
            SET_BIT(player[BLACK].k, Count - 1);
            break;
            case 'n':
            n_Count += 1;
            Count += 1;
            SET_BIT(player[BLACK].n, Count - 1);
            break;
            /* non piece cases*/
            case '/':
            if(Count % 8 != 0 || board[i + 1] == '/'){
                printf("error: wrong number of squares in row\n");
                return FALSE;
            }
            break;
            case ' ':
            break;
            case '1':
            if(board[i+1] <= '9' && board[i+1] >= '0' ){
                return FALSE;
            }
            Count += 1;
            break;
            case '2':
            if(board[i+1] <= '9' && board[i+1] >= '0' ){
                return FALSE;
            }
            Count += 2;
            break;
            case '3':
            if(board[i+1] <= '9' && board[i+1] >= '0' ){
                return FALSE;
            }
            Count += 3;
            break;
            case '4':
            if(board[i+1] <= '9' && board[i+1] >= '0' ){
                return FALSE;
            }
            Count += 4;
            break;
            case '5':
            if(board[i+1] <= '9' && board[i+1] >= '0' ){
                return FALSE;
            }
            Count += 5;
            break;
            case '6':
            if(board[i+1] <= '9' && board[i+1] >= '0' ){
                return FALSE;
            }
            Count += 6;
            break;
            case '7':
            if(board[i+1] <= '9' && board[i+1] >= '0' ){
                return FALSE;
            }
            Count += 7;
            break;
            case '8':
            if(board[i+1] <= '9' && board[i+1] >= '0' ){
                return FALSE;
            }
            Count += 8;
            break;
            default:
            return 0;
        }
        i++;
    }
    /* done parsing pieces on board */

    if(Count != 64) {
        printf("Error: Not enough pieces or too many pieces\n");
        return FALSE;
    }

    i++; /*go to next char after space*/
    if( board[i] == 'w'){
        /*it is white's turn*/
        CurrentPlayer = WHITE;
    } else if( board[i] == 'b'){
        /*it is blacks's turn*/
        CurrentPlayer = BLACK;
    } else {
        printf("Error: not b or w\n");
    }

    /*CHECK CASTLING OPTIONS*/

    i+=2; /*i points to next char after space*/

    int t = i + 3; /*temporary int variable to make sure less than 4 castling options specified*/

    if(board[i] == '-') {
        /* no castling*/
        player[BLACK].castle_flags = NO_CASTLE;
        player[WHITE].castle_flags = NO_CASTLE;
    } else {
        while(board[i] != ' ' && i < t) {
            switch(board[i]) {
                /*if castling allowed, king is in starting position and rook on the castling side is in its starting position.*/
                case 'k':
                /*black can castle kingside*/
                if((!(IS_SET(player[BLACK].k,5))) && !(IS_SET(player[BLACK].r,7))){
                    printf("either black king is not in starting position or rook on kingside is not in starting position\n");
                    return FALSE;
                }
                player[BLACK].castle_flags = CASTLE_KING;
                i += 1;
		continue;
                case 'q':
                /*black can castle queenside*/
                if((!(IS_SET(player[BLACK].k,5))) && !(IS_SET(player[BLACK].r,0))){
                    printf("either black king is not in starting position or rook on queenside is not in starting position\n");
                    return FALSE;
                }
                player[BLACK].castle_flags = CASTLE_QUEEN;
                i +=1 ;
		continue;
                case 'K':
                /*white can castle kingside*/
                if((!(IS_SET(player[WHITE].k,60))) && !(IS_SET(player[WHITE].r,63))){
                    printf("either white king is not in starting position or rook on kingside is not in starting position\n");
                    return FALSE;
                }
                player[WHITE].castle_flags = CASTLE_KING;
                i += 1;
		continue;
                case 'Q':
                /*white can castle queenside*/
                if((!(IS_SET(player[WHITE].k,60))) && !(IS_SET(player[WHITE].r,56))){
                    printf("either white king is not in starting position or rook on queenside is not in starting position\n");
                    return FALSE;
                }
                player[WHITE].castle_flags = CASTLE_QUEEN;
                i += 1;
		continue;
                default:
                /*error*/
                printf("error: invalid castling option specified\n");
            }
            i += 1;
        } /*i is at a space rn if options are correct*/
    }
    if(board[i] != ' ') {
        return FALSE;
    }
    i += 1;

	/*CHECK EN PASSANT SQUARE*/
	if(board[i] == '-') {
		/*no ep square*/
		ep_square = -1;
	} else if(board[i+1] == '3' || board[i+1] == '6' ) {  /*check condition 7: ep should only be on 3rd or 6th rank*/
		if(CurrentPlayer == WHITE) { /*check that there is a black pawn on ep+8 and ep-8 is unoccupied if white to play*/
			/* check ep+8 has black pawn*/
			if(!IS_SET(player[BLACK].p,TO_POS(board[i],board[i+1] + 1))){
				return FALSE;
			}
			/* check ep-8 empty*/
			if(OCCUPIED(TO_POS(board[i],board[i+1] - 1))){
				return FALSE;
			}
		}
		if(CurrentPlayer == BLACK) { /* check that there is a white pawn on ep-8 and ep+8 is unoccupied if black to play*/
			/* check ep-8 has white pawn*/
			if(!IS_SET(player[WHITE].p,TO_POS(board[i],board[i+1] - 1))){
				return FALSE;
			}
			/* check ep+8 empty*/
			if(OCCUPIED(TO_POS(board[i],board[i+1] + 1))){
				return FALSE;
			}
		}
		/*ep square = file : board[i], rank : board[i+1]*/
		ep_square = TO_POS(board[i], board[i] + 1);
	} else {
		printf("error: the ep should only be on the third or sixth rank, or \n");
		return FALSE;
	}
    /*checks that there is exactly one king and there are only exactly 64 pieces on board, and that there are no more than eight pawns, and condition 5*/
    if(Count != 64 || R_Count > 10 || Q_Count > 9 || B_Count > 10 || P_Count > 8 || K_Count != 1 || N_Count > 10 || r_Count > 10 || q_Count > 9 || b_Count > 10 || p_Count > 8 || k_Count != 1 || n_Count > 10){
        return FALSE;
    }

    /*check number of pawns and pieces not including kings are <= 15*/
    if(p_Count + q_Count + b_Count + n_Count + r_Count > 15){
        return FALSE;
    }
    if(P_Count + Q_Count + B_Count + N_Count + R_Count > 15){
        return FALSE;
    }

	/*Condition 8) if white to play, black king not under check and vice versa. */
	if(is_king_under_check(1 - CurrentPlayer)){
		return FALSE;
	}

	/* If everything is satisfied, return TRUE; */
    return TRUE;
}
/* Parses the input move.
* This function repeatedly prompts for a move until a valid move is typed in.
* This function only validates that:
*	 1) from and to are valid squares on the board.
*	 2) from and to are separated by a '-'
* This function does not check the legality of the move.
*/
/*Move*/
void parse_move() {
    /* int valid_move = 0;
     * while(valid_move != 1){
     *   char input[6]; //f3-f7 should be 5 but just in case, we set extra
     *   fgets(input, 5, stdin);
     *   if(!IS_SET(TO_POS(input[0],input[1])) && !IS_SET(TO_POS(input[3],input[4])) && input[2] == '-'){
     *     struct Move new_move = {(TO_POS(input[0],input[1]), TO_POS(input[3],input[4], get_piece_char(TO_POS(input[3],input[4]), IS_PROMOTION(get_piece_char(TO_POS(input[3],input[4])), NULL};
     *     return new_move;
     *   }
     *   else{
     *     printf("Invalid move input. The format is supposed to be FROM-TO .");
     *   }
     * }
     */
}

/* This function accepts a move from the user. The move is not validated */
void prompt_move(Move *m, unsigned int move_number) {
    /*not necessary*/
}

/* This function prints a move on to the console */
void print_move(Move *m) {
    printf("%u:%c to %u:%c\n ----- Piece: %d",RANK_OF(m->from),FILE_OF(m->from),RANK_OF(m->to),FILE_OF(m->to), m->piece);
}
