#include "gui.h"


GUI::GUI(int *argcp, char **argv, int width, int height, Graph graph)
    : argcp(argcp), argv(argv), width(width), height(height), graph(graph)
{
}


void GUI::run() {
    // initialization
    glutInit(&this->argc, this->argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(this->width, this->height);
    glutCreateWindow("Graph plotter");
 
    graph.calculate()

    glutDisplayFunc(this->renderScene);               // set display callback
    glutMouseFunc(this->mouseButton);                 // graph scale change callback 
    glutReshapeFunc(this->changeSize);                // window size change callback

    // glutMotionFunc(MouseMove);
    // glutIdleFunc(RenderScene);
    
    glutMainLoop();                             // run main GLUT loop
}


void GUI::renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    // background
    glColor3ub(33, 33, 33);
    glBegin(GL_QUADS);
        glVertex3d(-100.0, -100.0, -1.0);
        glVertex3d(-100.0, 100.0, -1.0);
        glVertex3d(100.0, 100.0, -1.0);
        glVertex3d(100.0, -100.0, -1.0);
    glEnd();
    this->makeDefaultColor();

    // axis
    glColor3ub(180, 180, 180);
    glBegin(GL_LINES);
        
        glVertex3d(0.0, -100.0, -1.0);          // axis OX and OY respectively
        glVertex3d(0.0, 100.0, -1.0);
        glVertex3d(-100.0, 0.0, -1.0);
        glVertex3d(100.0, 0.0, -1.0);
        
        glVertex3d(1.0, 0.0, -1.0);             // OX axis direction
        glVertex3d(0.97, -0.015, -1.0);
        glVertex3d(0.97, 0.015, -1.0);
        glVertex3d(1.0, 0.0, -1.0);
        
        glVertex3d(0.0, 1.0, -1.0);             // OY axis direction
        glVertex3d(-0.015, 0.97, -1.0);
        glVertex3d(0.015, 0.97, -1.0);
        glVertex3d(0.0, 1.0, -1.0);

    glEnd();
    this->makeDefaultColor();

    // scale designations
    glBegin(GL_LINES);
        for (double cod = this->scale; cod < this->MAX_VIEW; cod += scale) {
            
            glColor3ub(50, 50, 50);
            glVertex3d(cod, 100.0, -1.0);
            glVertex3d(cod, -100.0, -1.0);

            glVertex3d(-cod, 100.0, -1.0);
            glVertex3d(-cod, -100.0, -1.0);

            glVertex3d(100.0, cod, -1.0);
            glVertex3d(-100.0, cod, -1.0);

            glVertex3d(100.0, -cod, -1.0);
            glVertex3d(-100.0, -cod, -1.0);  
        }
    glEnd();
    this->makeDefaultColor();

    glBegin(GL_LINES);
        for (double cod = this->scale_sep * this->scale; cod < this->MAX_VIEW; cod += this->scale_sep * this->scale) {
            
            glColor3ub(80, 80, 80);
            glVertex3d(cod, 100.0, -1.0);
            glVertex3d(cod, -100.0, -1.0);

            glVertex3d(-cod, 100.0, -1.0);
            glVertex3d(-cod, -100.0, -1.0);

            glVertex3d(100.0, cod, -1.0);
            glVertex3d(-100.0, cod, -1.0);

            glVertex3d(100.0, -cod, -1.0);
            glVertex3d(-100.0, -cod, -1.0);


            glColor3ub(180, 180, 180);
            glVertex3d(cod, 0.01, -1.0);
            glVertex3d(cod, -0.01, -1.0);

            glVertex3d(-cod, 0.01, -1.0);
            glVertex3d(-cod, -0.01, -1.0);

            glVertex3d(0.01, cod, -1.0);
            glVertex3d(-0.01, cod, -1.0);

            glVertex3d(0.01, -cod, -1.0);
            glVertex3d(-0.01, -cod, -1.0);  
        }
    glEnd();
    this->makeDefaultColor();

    // scale output as numbers
    glColor3ub(180, 180, 180);
    
    double num = this->scale_sep;
    double cod = this->scale_sep * this->scale;
    
    while (cod < this->MAX_VIEW) {
        std::string str_num;

        str_num = std::to_string(num);
        this->renderBitmapString(cod + 0.01 , 0.015, -1.0, FONT_2, str_num.c_str());
        this->renderBitmapString(0.015, cod + 0.01, -1.0, FONT_2, str_num.c_str());
        
        str_num = std::to_string(-num);
        this->renderBitmapString(-cod + 0.01 , 0.015, -1.0, FONT_2, str_num.c_str());
        this->renderBitmapString(0.015, -cod + 0.01, -1.0, FONT_2, str_num.c_str());

        cod += this->scale_sep * scale;
        num += this->scale_sep;
    }

    // some information on top of the graph
    glColor3ub(100, 100, 100);
    this->renderBitmapString(0.5, 0.95, -0.995, FONT_1, (char*) "Made by alexandr-gnrk");
    this->makeDefaultColor();


    // draw the function graph
    std::vector<double> xValues = this->graph.getxValues();
    std::vector<double> yValues = this->graph.getyValues();

    glBegin(GL_LINE_STRIP);
        for (int i = 0; i < xValues.size(); i++) {
            glVertex3d(xValues[i] * this->scale, yValues[i] * this->scale, -1.0);
        }
    glEnd();


    glutSwapBuffers();
}


void Graph::mouseButton(int button, int state, int x, int y) {

    if (state == GLUT_UP) {
        switch (button) {
        case 4:
            this->graph.setOXRange(this->graph.getOXRange() + 1);
            break;
        case 3:
            this->graph.setOXRange(this->graph.getOXRange() - 1);
            break;
        }
    }

    // if (x_min > -8) { x_min = -8; }
    // if (x_max < 8) { x_max = 8; }
    graph.calculate();
}


void Graph::changeSize(int w, int h) {
    // prevent division by zero
    if(h == 0) {
        h = 1;
    }

    double ratio = 1.0* w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(90, ratio, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
}


void Graph::renderBitmapString(double x, double y, double z, void *font, char *string) {
    glRasterPos3d(x, y,z);
    for (char *c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


void Graph::makeDefaultColor()
{
    glColor3ub(255, 255, 255);
}