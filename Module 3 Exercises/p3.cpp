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

int shape = 1;

float red = 1.0f;
float green = 0.7f;
float blue = 0.75f;

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawHeart()
{
    glBegin(GL_POLYGON);
    for (float angle = 0.0f; angle <= 2.0f * 3.14159265f; angle += 0.01f)
    {
        float x = 0.02f * (16.0f * pow(sin(angle), 3));
        float y = 0.02f * (13.0f * cos(angle) - 5.0f * cos(2.0f * angle) - 2.0f * cos(3.0f * angle) - cos(4.0f * angle));
        glVertex2f(x, y);
    }
    glEnd();
}

void drawSquare()
{
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, -0.3f);
        glVertex2f(0.3f, -0.3f);
        glVertex2f(0.3f, 0.3f);
        glVertex2f(-0.3f, 0.3f);
    glEnd();
}

void drawDiamond()
{
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.4f, 0.0f);
        glVertex2f(0.0f, -0.4f);
        glVertex2f(-0.4f, 0.0f);
    glEnd();
}

void display()
{
    glClearColor(0.95f, 0.92f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.3f, 0.3f, 0.35f);

    drawText(-0.9f, 0.82f, "=== PASTEL SHAPE & COLOR SELECTOR ===");
    drawText(-0.9f, 0.72f, "[1] - Heart     |  [R] - Pastel Pink");
    drawText(-0.9f, 0.62f, "[2] - Square    |  [G] - Pastel Mint Green");
    drawText(-0.9f, 0.52f, "[3] - Diamond   |  [B] - Pastel Blue");
    drawText(-0.9f, 0.42f, "[ESC] - Exit Program");

    glColor3f(red, green, blue);

    if (shape == 1)
        drawHeart();
    else if (shape == 2)
        drawSquare();
    else if (shape == 3)
        drawDiamond();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
            shape = 1;
            cout << "Heart selected" << endl;
            break;

        case '2':
            shape = 2;
            cout << "Square selected" << endl;
            break;

        case '3':
            shape = 3;
            cout << "Diamond selected" << endl;
            break;

        case 'r':
        case 'R':
            red = 1.0f;
            green = 0.7f;
            blue = 0.75f;
            cout << "Color: PASTEL PINK" << endl;
            break;

        case 'g':
        case 'G':
            red = 0.7f;
            green = 0.95f;
            blue = 0.8f;
            cout << "Color: PASTEL MINT GREEN" << endl;
            break;

        case 'b':
        case 'B':
            red = 0.7f;
            green = 0.85f;
            blue = 1.0f;
            cout << "Color: PASTEL BLUE" << endl;
            break;

        case 27:
            exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(800, 600);

    glutCreateWindow("Program 3 - Interactive Pastel Heart Selector");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}