#ifndef PEPIN_H
#define PEPIN_H

typedef struct Rectangle {
    int x1, y1, x2, y2; //two points make a rectangle
    unsigned char r, g, b; //will specify rgb vals
} Rect;
typedef struct Colour {
    unsigned char r, g, b; //will specify rgb vals
} Col;
typedef struct Position {
    int x, y;
} Pos;
typedef struct ActorT {
    Rect sprite;
    Pos pos; //points to bottom left ?
} Actor;

class Sprite {
	public:
		int w, h; //width and height of sprite box
		Pos pos; //initial position
		Col col; //initial colour
		//reference to colour -> texture SoonTM
		Sprite(Pos initpos, Col initcol, int wt, int ht);		
};
#endif //PEPIN_H