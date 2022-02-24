#include <unistd.h>
#include "pepin.h"

/*typedef struct Position {
    int x, y;
} Pos;
typedef struct Colour {
    unsigned char r, g, b; //will specify rgb vals
} Col;*/

Sprite::Sprite(){

}

void Sprite::iniSprite(Pos initpos, Col initcol, int wt, int ht){
	pos = initpos;
	col = initcol;
	w = wt;
	h = ht;
}

void Sprite::iniSprite(Pos initpos, Image image, int wt, int ht){
	pos = initpos;
	img = image;
	w = wt;
	h = ht;
	hasImg = true;
}
