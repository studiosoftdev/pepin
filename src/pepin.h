#ifndef PEPIN_H
#define PEPIN_H

//custom types

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
typedef unsigned char u8;

//classes

class Image {
public:
	int w, h;
	char path[255];
	int texID; //ID of image within tex array
	Image();
	void iniImage(char inipath[], int initexID);
	void getImageDims();
	void loadImg(char textures[255][255][3][255]);
};

class Sprite {
public:
	int w, h; //width and height of sprite box
	Pos pos; //initial position
	Col col; //initial colour
	Image img;
	bool hasImg = false;
	//reference to colour -> texture SoonTM
	void iniSprite(Pos initpos, Col initcol, int wt, int ht);	
	void iniSprite(Pos initpos, Image image, int wt, int ht);
	Sprite();	
};


#endif //PEPIN_H