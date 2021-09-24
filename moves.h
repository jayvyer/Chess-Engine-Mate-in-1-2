#ifndef _MOVES_H_
#define _MOVES_H_

#include "chess.h"
#include "io.h"

Pos king_pos();
Bool is_king_under_check(PlayerColor c);
Board save_state(Board orig_pos);
void simulate(PlayerColor c, Pos move, Pos orig_pos);
void restore_state(Board *current, Board original);
void freeList(Move* head);

/* Given a color, this function returns a singly linked list of all legal Moves with the head at *m.
 * The function returns TRUE if at least 1 legal move is available.
 * The total number of moves found is stored in the address pointed to by pcount. */
Bool legal_moves(Move **m, PlayerColor c, unsigned int *pcount);

/* Returns TRUE if specified player is under checkmate, FALSE otherwise. */
Bool is_checkmate(PlayerColor c);

/* Validate a move and make it. Returns TRUE if successful, FALSE if not.
 *  Error message if any, are stored in *msg.
 * ep_square (if any) is stored in *ep_sq
 */
Bool validate_and_move(Move *move, PlayerColor c, Pos *ep_sq);

/* Function to decide whether the current position is a draw */
/* Draw can be due to stalemate */
Bool is_draw();

/* Returns the piece on a square belonging to player color c.
 * If there is no piece with color c, UNKNOWN is returned. */
Piece get_piece_at(Pos pos, PlayerColor c); /* orig param was Board pos */

/* Check if this move is trying to castle */
unsigned int detect_castle_move(Move move, PlayerColor c);

/* Perform castling. Moves king and rook and resets castle flags */
void perform_castle(unsigned int castle, PlayerColor c);

#endif
