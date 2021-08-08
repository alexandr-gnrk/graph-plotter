#ifndef GUI
#define GUI


// #include <vector>
#include<string>  

#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>

#include "graph.h"

#define FONT_1 GLUT_BITMAP_8_BY_13
#define FONT_2 GLUT_BITMAP_HELVETICA_10

class GUI
{
public:
    GUI(int *argcp, char **argv, int width, int height, Graph graph);
    
    void run();
    void renderScene();
    void mouseButton(int button, int state, int x, int y);
    void changeSize(int w, int h);
    void renderBitmapString(double x, double y, double z, void *font, char *string);
    void makeDefaultColor();

private:
    int *argcp;
    char **argv;
    int width;
    int height;
    Graph graph;
};


#endif