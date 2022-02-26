#include <GL/glut.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>
#include <vector>
#include "pepin.h"

#define SCREENW 640
#define SCREENH 480
#define WINTITLE "2D Application"

using namespace std;


void setupTexture();
void updateTexture();

u8 screenData[SCREENH][SCREENW][3];
unsigned char textures [255][255][4][255]; //X, Y, RGB, texID
int texID = 0;
vector<Rect> rects;
vector<Sprite> actors;
int movement = 0;
Sprite player;
Sprite pep;
Sprite frog;


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

    //clear screen
    for(int x = 0; x < SCREENW; x++){
        for(int y = 0; y < SCREENH; y++){
            screenData[y][x][0] = screenData[y][x][1] = screenData[y][x][2] = 0;
        }
    }

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
        int len = actors[i].w;
        int hgt = actors[i].h;
        int iy = actors[i].pos.y;
        int ix = actors[i].pos.x;
        if(!actors[i].hasImg){
            for(int y = iy - hgt; y < iy; y++){
                for(int x = ix; x < ix + len; x++){
                    screenData[y][x][0] = actors[i].col.r;
                    screenData[y][x][1] = actors[i].col.g;
                    screenData[y][x][2] = actors[i].col.b;
                }
            }
        }
        else{
            for(int y = iy; y < iy + hgt; y++){
                for(int x = ix; x < ix + len; x++){
                    float alphaAmount = (textures[x-ix][y-(iy)][3][actors[i].img.texID])/255.0;
                    screenData[y][x][0] = (char)floorf((textures[x-ix][y-(iy)][0][actors[i].img.texID] * alphaAmount) + (screenData[y][x][0] * (1-alphaAmount)));
                    screenData[y][x][1] = (char)floorf((textures[x-ix][y-(iy)][1][actors[i].img.texID] * alphaAmount) + (screenData[y][x][1] * (1-alphaAmount)));
                    screenData[y][x][2] = (char)floorf((textures[x-ix][y-(iy)][2][actors[i].img.texID] * alphaAmount) + (screenData[y][x][2] * (1-alphaAmount)));

                    //screenData[y][x][0] = textures[x-ix][y-(iy)][0][actors[i].img.texID];
                    //screenData[y][x][1] = textures[x-ix][y-(iy)][1][actors[i].img.texID];
                    //screenData[y][x][2] = textures[x-ix][y-(iy)][2][actors[i].img.texID];
                }
            }
        }
    }
}

void keyboardDown(unsigned char key, int x, int y){
    if(key == 'd'){
        player.pos.x += 2;
        actors.at(2) = player;
    }
    return;
}

void keyboardUp(unsigned char key, int x, int y){
    if(key == 'a'){
        player.pos.x -= 2;
        actors.at(2) = player;
    }
    return;
}

/* Program entry point */

int main(int argc, char *argv[])
{
    unsigned char c = 0xFF;
    int i = floorf(c/255.0);
    cout << i << endl;
    //return 0;
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

    //add image for testing
    char path[] = "pep.tga";
    Image img;
    img.iniImage(path, texID);
    img.getImageDims();
    img.loadImg(textures);
    texID++;

    //add sprite with image
    pep.iniSprite(Pos{250, 250}, img, img.w, img.h);
    actors.push_back(pep);

    //add frog image for alpha testing
    char path2[] = "frog.tga";
    Image img2;
    img2.iniImage(path2, texID);
    img2.getImageDims();
    img2.loadImg(textures);
    texID++;

    //add frog sprite with frog image
    frog.iniSprite(Pos{250, 220}, img2, img2.w, img2.h);
    actors.push_back(frog);

    //add floor
    Rect r1 = {0, 480, 640, 430, 50, 50, 50};
    rects.push_back(r1);

    //add player
    player.iniSprite(Pos {50, 430}, Col {117, 254, 165}, 30, 80);
    actors.push_back(player);

    
    cout << "past addns" << endl;
    

    //testing guff concludes

    glutMainLoop();

    return EXIT_SUCCESS;
}