#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

float carX = 0.0f;
float carY = 0.0f;

float moveStep = 0.08f;

float carR = 0.0f;
float carG = 0.5f;
float carB = 1.0f;

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawCar()
{
    glColor3f(carR, carG, carB);
    glBegin(GL_QUADS);
        glVertex2f(carX - 0.4f, carY - 0.2f);
        glVertex2f(carX + 0.4f, carY - 0.2f);
        glVertex2f(carX + 0.4f, carY + 0.1f);
        glVertex2f(carX - 0.4f, carY + 0.1f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(carX - 0.25f, carY + 0.1f);
        glVertex2f(carX - 0.1f,  carY + 0.35f);
        glVertex2f(carX + 0.2f,  carY + 0.35f);
        glVertex2f(carX + 0.3f,  carY + 0.1f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(35.0f);
    glBegin(GL_POINTS);
        glVertex2f(carX - 0.25f, carY - 0.25f);
        glVertex2f(carX + 0.25f, carY - 0.25f);
    glEnd();
}

void display()
{
    glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.1f, 0.1f, 0.1f);

    drawText(-0.9f, 0.82f, "=== WAVY CAR CONTROLLER ===");
    drawText(-0.9f, 0.72f, "[A] / [D] - Wavy Move Left / Right");
    drawText(-0.9f, 0.62f, "[H]       - Home / Center Car");
    drawText(-0.9f, 0.52f, "[R] / [G] / [B] - Change Car Color");
    drawText(-0.9f, 0.42f, "[ESC]     - Exit Program");

    drawCar();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
        case 'A':
            carX -= moveStep;
            carY = 0.15f * sin(carX * 6.0f);
            break;

        case 'd':
        case 'D':
            carX += moveStep;
            carY = 0.15f * sin(carX * 6.0f);
            break;

        case 'h':
        case 'H':
            carX = 0.0f;
            carY = 0.0f;
            break;

        case 'r':
        case 'R':
            carR = 1.0f;
            carG = 0.0f;
            carB = 0.0f;
            break;

        case 'g':
        case 'G':
            carR = 0.0f;
            carG = 1.0f;
            carB = 0.0f;
            break;

        case 'b':
        case 'B':
            carR = 0.0f;
            carG = 0.0f;
            carB = 1.0f;
            break;

        case 27:
            exit(0);
    }

    if (carX > 0.55f)
        carX = 0.55f;

    if (carX < -0.55f)
        carX = -0.55f;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(900, 600);

    glutCreateWindow("Program 4 - Wavy Keyboard Car Controller");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}