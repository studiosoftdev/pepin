#include <GL/glut.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>
#include <vector>

#define SCREENW 640
#define SCREENH 480
#define WINTITLE "2D Application"

typedef unsigned char u8;
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

using namespace std;


void setupTexture();
void updateTexture();

u8 screenData[SCREENH][SCREENW][3];
vector<Rect> rects;
vector<Actor> actors;


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void setupTexture()
{
    // Create a texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, SCREENW, SCREENH, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screenData);

    // Set up the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Enable textures
    glEnable(GL_TEXTURE_2D);
}

void updateTexture()
{
    // Update Texture
    glTexSubImage2D(GL_TEXTURE_2D, 0 ,0, 0, SCREENW, SCREENH, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)screenData);

    glBegin( GL_QUADS );
        glTexCoord2d(0.0, 0.0);     glVertex2d(0.0,             0.0);
        glTexCoord2d(1.0, 0.0);     glVertex2d((SCREENW * 1),  0.0);
        glTexCoord2d(1.0, 1.0);     glVertex2d((SCREENW * 1),  (SCREENH * 1));
        glTexCoord2d(0.0, 1.0);     glVertex2d(0.0,             (SCREENH * 1));
    glEnd();
}

//called each frame
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    updateTexture();
    glutSwapBuffers();

    for(int i = 0; i < rects.size(); ++i){
        int len = abs(rects[i].x2 - rects[i].x1);
        int hgt = abs(rects[i].y2 - rects[i].y1);
        for(int y = 0; y < hgt; y++){
            for(int x = 0; x < len; x++){
                screenData[y+min(rects[i].y1, rects[i].y2)][x+min(rects[i].x1, rects[i].x2)][0] = rects[i].r;
                screenData[y+min(rects[i].y1, rects[i].y2)][x+min(rects[i].x1, rects[i].x2)][1] = rects[i].g;
                screenData[y+min(rects[i].y1, rects[i].y2)][x+min(rects[i].x1, rects[i].x2)][2] = rects[i].b;
            }
        }
    }
    for(int i = 0; i < actors.size(); ++i){
        int ax1 = actors[i].sprite.x1;
        int ax2 = actors[i].sprite.x2;
        int ay1 = actors[i].sprite.y1;
        int ay2 = actors[i].sprite.y2;

        int len = abs(ax2 - ax1);
        int hgt = abs(ay2 - ay1);
        for(int y = 0; y < hgt; y++){
            for(int x = 0; x < len; x++){
                screenData[y+min(ay1, ay2)][x+min(ax1, ax2)][0] = actors[i].sprite.r;
                screenData[y+min(ay1, ay2)][x+min(ax1, ax2)][1] = actors[i].sprite.g;
                screenData[y+min(ay1, ay2)][x+min(ax1, ax2)][2] = actors[i].sprite.b;
            }
        }
    }
}

void keyboardDown(unsigned char key, int x, int y){
    return;
}

void keyboardUp(unsigned char key, int x, int y){
    return;
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(SCREENW * 1,SCREENH * 1);
    glutInitWindowPosition(640,300);
    glutCreateWindow(WINTITLE);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    //glutOverlayDisplayFunc(display);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, (double)SCREENW, (double)SCREENH, 0.0 );

    setupTexture();

    //testing guff

    Rect r1 = {0, 480, 640, 430, 50, 50, 50};
    rects.push_back(r1);
    Actor player = {Rect {50, 430, 80, 350, 0, 255, 255}, Pos {50, 430}};
    actors.push_back(player);

    //testing guff concludes

    glutMainLoop();

    return EXIT_SUCCESS;
}