#include <unistd.h>
#include "pepin.h"

/*typedef struct Position {
    int x, y;
} Pos;
typedef struct Colour {
    unsigned char r, g, b; //will specify rgb vals
} Col;*/

Sprite::Sprite(Pos initpos, Col initcol, int wt, int ht){
	pos = initpos;
	col = initcol;
	w = wt;
	h = ht;
}
