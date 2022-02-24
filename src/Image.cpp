#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include "pepin.h"

Image::Image(){}

void Image::iniImage(char inipath[], int initexID){
	//assign unique texID
	texID = initexID;

	for(int i = 0; i < 255; i++){
		path[i] = inipath[i];
	}
}

void Image::getImageDims(){
	char header[18];
	//11th byte X, 12th byte Y
	std::cout << path << std::endl;
	FILE* pFile = fopen(path, "rb");
	fseek(pFile, 0, SEEK_END);
    unsigned long lSize = ftell(pFile);
    rewind(pFile);
    // Allocate memory to contain the whole file
    char* buffer = (char*)malloc(sizeof(char) * lSize);
    if(buffer == NULL){
    	std::cout << "Big rip memory error in loading file" << std::endl;
    }
    //copy buffer in
    size_t result = fread(buffer, 1, lSize, pFile);
    if (result != lSize)
    {
        fputs("Reading error", stderr);
        //Sleep(30000);
        return;
    }
    //copy header in
    for(int i = 0; i < 18; i++){
    	header[i] = buffer[i];
    }
    //extract width and height
    w = header[12]; //|| (header[13] << 8); //imgs are restricted to 256x256 anyway i guess
    h = header[14]; //|| (header[15] << 8);
    std::cout << "w : " << w << " | h : " << h << std::endl;
    //close file
    free(buffer);
    fclose(pFile);
}

void Image::loadImg(char textures[255][255][3][255]){
	//only supports TGA 1.0
	FILE* pFile = fopen(path, "rb");
	fseek(pFile, 0, SEEK_END);
    unsigned long lSize = ftell(pFile);
    rewind(pFile);
    // Allocate memory to contain the whole file
    char* buffer = (char*)malloc(sizeof(char) * lSize);
    if(buffer == NULL){
    	std::cout << "Big rip memory error in loading file" << std::endl;
    }
    int bpp = (buffer[16]/8); //Bytes Per Pixel : buffer[16] says bits per pixel (24 by default)
    int imgsize = (w*h*bpp) - 18; //num bytes
    std::cout << "w : " << w << " | h : " << h << " | bpp : " << bpp << std::endl;
    for(int i = 0; i < imgsize; i+=bpp){
    	for(int x = 0; x < 3; x++){
    		//std::cout << "i: " << i << " | i % w: " << i%w << " | x: " << x << " | texID: " << texID << " | buffer[i+x]: " << (int)buffer[i+x] << std::endl;
    		textures[(i/bpp)%w][(i/bpp)/h][x][texID] = buffer[i+x+18];
    	}
    }
    free(buffer);
    fclose(pFile);
    std::cout << "reached end" << std::endl;
}