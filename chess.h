#ifndef _CHESS_H_
#define _CHESS_H_

#include <stdint.h>

/* Mode: 1 for mate in one, 2 for mate in two */
typedef int	Mode;

/* Types for position, board, error and boolean */
typedef unsigned int 		Pos;
#define UNKNOWN_POS			((unsigned int) (-1))

typedef uint8_t 		Flags;
typedef uint64_t  		Board;
typedef unsigned int 	Error;
typedef unsigned int	Bool;

#define TRUE			1
#define FALSE			0

enum _piece {UNKNOWN=0,KING, QUEEN, ROOK, BISHOP, NIGHT, PAWN};
typedef enum _piece Piece;

/* Player structure. Each player has a board to represent Rook, Bishop, Night, Queen, King and Pawns.
 * It also contains a bit vector to represent possible castling options. */
struct player_state {
	Flags castle_flags;
	Board r, n, b, q, k, p;
};
typedef struct player_state PlayerState;

enum _PlayerColor {WHITE=1, BLACK=0};
typedef enum _PlayerColor PlayerColor;

#define NO_CASTLE		0
#define CASTLE_KING 	1
#define CASTLE_QUEEN	2

struct move {
	Pos from; /* Starting position of a piece on board that is being moved */
	Pos to;   /* Ending position of a piece on the board that is being moved */
	Piece piece; /* Piece that is being moved */
	Piece promotion_choice;  /* If this is a promotion move, what is the choice for promotion */
	struct move *next_move;  /* What is the next move in the list */
};
typedef struct move Move;

#define MAX_STR_SIZE	255
#define WKING_START_POS BIT(61) /* : Starting position for the white king */
#define BKING_START_POS	BIT(5) /* : Starting position for the black king */

#define BIT(n) 			(1UL << (n))
#define SET_BIT(x, n)	((x) |= BIT((n)))
#define RESET_BIT(x, n) ((x) &= ~BIT(n))
#define IS_SET(x, n) 	((x) & BIT((n)))
#define BOARD(x) 		x.r | x.n | x.b | x.q | x.k | x.p /* given a player x, this macro evaluates to the player's board, i.e., 1 in dicates presense of any piece of the same color on the board, 0 indicates absense */
#define FULL_BOARD		(BOARD(player[WHITE]) | BOARD(player[BLACK]))   /* Full board comprising of both players */
#define OCCUPIED(n)		IS_SET(FULL_BOARD, n)/*  Macro to tell if a square is occupied by a piece of any color */
#define UNOCCUPIED(n)	(!(OCCUPIED(n)))

#define OCCUPIED_S(c,n)	IS_SET(BOARD(player[c]), n)
#define OCCUPIED_D(c,n)	IS_SET(BOARD(player[1-c]), n)
#define OCCUPIED_SAVED(s,n)	IS_SET(BOARD(s), n)

#define NORTH_OF(sq)	(((sq) > 63 || (sq) < 8)? UNKNOWN_POS : ((sq)-8))
#define SOUTH_OF(sq)	(((sq) > 55)? UNKNOWN_POS: ((sq)+8))
#define EAST_OF(sq)		(((sq) > 63 || (sq) == 7 || (sq) == 15 || (sq) == 23 || (sq) == 31 || (sq) == 39 || (sq) == 47 || (sq) == 55 || (sq) == 63)? UNKNOWN_POS : (sq)+1)
#define WEST_OF(sq)		(((sq) > 63 || (sq) == 0 || (sq) == 8 || (sq) == 16  || (sq) == 24 || (sq) == 32 || (sq) == 40 || (sq) == 48 || (sq) == 56)? UNKNOWN_POS : (sq)-1)
#define NE_OF(sq)		NORTH_OF(EAST_OF(sq))
#define NW_OF(sq)		NORTH_OF(WEST_OF(sq))
#define SE_OF(sq)		SOUTH_OF(EAST_OF(sq))
#define SW_OF(sq)		SOUTH_OF(WEST_OF(sq))

/* The below macros replace notation_to_id and id_to_notation functons */
#define RANK_OF(pos)			(8 - (pos/8) + '0') /* Obtain the rank of a square given its pos */
#define FILE_OF(pos)			((pos % 8) + 'a')   /* Obtain the file of a square given its pos */
#define TO_POS(file,rank)		(((8 - (rank - '0')) * 8) + (file) - 'a') /* Obtain the pos of a square given its file and rank */

/* This macro tells if a move is a promotion move */
/* Move must already be validated. If pawn is going to 1st or 8th rank, this is a promotion move */
#define IS_PROMOTION(m)			(((m).piece == PAWN) && ((RANK_OF((m).to) == '1') || (RANK_OF((m).to) == '8')))

/* The enpassant square */
extern Pos ep_square;

/* The player structures. One each for black and white */
extern PlayerState player[2];

/* The color of the current player */
extern PlayerColor CurrentPlayer;

/* The mode in which the chess engine is operating */
extern Mode mode;

/* Given a position, find a mate in 2. */
Bool run_mate2(Move *soln);

/* Given a position, find a mate in 1. */
Bool run_mate1(Move *soln);


#endif
