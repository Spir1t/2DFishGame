#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "fish.h"
#include <iostream>

GLfloat t = 0;
GLfloat SunX = sin(t/100) * 1.7;
GLfloat SunY = cos(t/100) * 1.2 - 0.4;
GLfloat MoonX = -sin(t / 100) - 0.2;
GLfloat MoonY = -cos(t / 100) - 0.2;
GLfloat MinimumLight = 0.3;
GLfloat CurrentLight = 1;
bool DayLightCycle = true;

GoldenFish MyFish;

void init(void);
void render(void);
void Tick(int deltaTime);
void ProcessKeyboardInput(unsigned char Key, int x, int y);

int main(int argc, char* argv[]) {

    // initialize glut
    glutInit(&argc, argv);

    // setup a depth buffer, double buffer and rgba mode
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    // set the windows initial position and size
    glutInitWindowPosition(700, 300);
    glutInitWindowSize(1080, 720);

    // create the window
    glutCreateWindow("Test Glut Program");

    init();

    // register the callbacks to glut
    glutDisplayFunc(render);

    // register keyboard input
    glutKeyboardFunc(ProcessKeyboardInput);

    glutTimerFunc(10, Tick, 0);
    // run the program
    glutMainLoop();

    return 0;

}

void init(void)
{
    glClearColor(0, 210.0 / 255.0, 1.0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void Tick(int deltaTime)
{
    if (DayLightCycle)
    {
        t++;
    }
    //animation
    //sun
    SunX = sin(t/200) * 1.7;
    SunY = cos(t/200) * 1.2 - 0.4;
    //moon
    MoonX = -sin(t / 200) * 1.7;
    MoonY = -cos(t / 200) * 1.2 - 0.4;
    
    //light
    if (cos(t / 200) > 0)
    {
        CurrentLight = cos(t / 200) * 0.8 + MinimumLight;
    }
    float SkyLight = cos(t / 200);
    glClearColor(0, 240.0 / 255.0 * SkyLight, 1.0 * SkyLight, 0);

    //update display
    glutPostRedisplay();
    //Reset timer
    glutTimerFunc(10, Tick, 0);
}

void ProcessKeyboardInput(unsigned char Key, int x, int y)
{
    switch(Key)
    {
    case 'w': MyFish.Move(0, 0.01); break;
    case 'a': MyFish.Move(-0.01, 0); break;
    case 's': MyFish.Move(0, -0.01); break;
    case 'd': MyFish.Move(0.01, 0); break;
    case 27:
        if (DayLightCycle)
        {
            DayLightCycle = false;
        }
        else
        {
            DayLightCycle = true;
        }
    }
}

void DrawSun()
{
    float SunRadiusX = 0.2 / 2;
    float SunRadiusY = 0.3 / 2;
    float SegmentsNum = 90;

    GLfloat Vertices[90 * 2];
    for (int i = 0; i < SegmentsNum; i++)
    {
        Vertices[i * 2] = SunX + cos(2 * M_PI / SegmentsNum * i) * SunRadiusX;
        Vertices[i * 2 + 1] = SunY + sin(2 * M_PI / SegmentsNum * i) * SunRadiusY;
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1, 1, 0);
    glVertexPointer(2, GL_FLOAT, 0, Vertices);

    glDrawArrays(GL_POLYGON, 0, 90);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawMoon()
{
    float MoonRadiusX = 0.2 / 4;
    float MoonRadiusY = 0.3 / 4;
    float SegmentsNum = 90;

    GLfloat Vertices[90 * 2];
    for (int i = 0; i < SegmentsNum; i++)
    {
        Vertices[i * 2] = MoonX + cos(2 * M_PI / SegmentsNum * i) * MoonRadiusX;
        Vertices[i * 2 + 1] = MoonY + sin(2 * M_PI / SegmentsNum * i) * MoonRadiusY;
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(0.5, 0.5, 0.5);
    glVertexPointer(2, GL_FLOAT, 0, Vertices);

    glDrawArrays(GL_POLYGON, 0, 90);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void render(void) 
{
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat Colors[] = { 0, 0.65 * CurrentLight, 1 * CurrentLight,
                            0, 0.65 * CurrentLight, 1 * CurrentLight,
                            0, 0, 1 * CurrentLight,
                            0, 0, 1 * CurrentLight,
                            1 * CurrentLight, 220.0 / 255 * CurrentLight, 140.0 / 255 * CurrentLight,
                            1 * CurrentLight, 220.0 / 255 * CurrentLight, 140.0 / 255 * CurrentLight,
                            1 * CurrentLight, 220.0 / 255 * CurrentLight, 140.0 / 255 * CurrentLight,
                            1 * CurrentLight, 220.0 / 255 * CurrentLight, 140.0 / 255 * CurrentLight };

    GLfloat Vertices[] = { 1, 0.3 ,
                            -1, 0.3,
                            -1, -1,
                            1, -1,
                            1, -0.9,
                            1, -1,
                            -1, -1,
                            -1, -0.9 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, Vertices);
    glColorPointer(3, GL_FLOAT, 0, Colors);

    glDrawArrays(GL_QUADS, 0, 8);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    //sun
    DrawSun();

    //moon
    DrawMoon();

    //fish
    MyFish.Draw(CurrentLight);

    glEnd();

    glutSwapBuffers();
}
