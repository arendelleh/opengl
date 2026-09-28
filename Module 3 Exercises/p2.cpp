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

float starX = 0.0f;
float starY = 0.0f;

float moveStep = 0.1f;

void drawText(float x, float y, const string& text)
{
    glRasterPos2f(x, y);
    for (char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void drawStar(float cx, float cy, float outerRadius, float innerRadius)
{
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy); 
        for (int i = 0; i <= 10; ++i)
        {
            float angle = i * 3.14159265f / 5.0f;
            float r = (i % 2 == 0) ? outerRadius : innerRadius;
            glVertex2f(cx + r * sin(angle), cy + r * cos(angle));
        }
    glEnd();
}

void display()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    drawText(-0.9f, 0.82f, "=== STAR CONTROLLER ===");
    drawText(-0.9f, 0.72f, "[W] / [S] - Move Up / Down (Step: 0.1)");
    drawText(-0.9f, 0.62f, "[A] / [D] - Move Left / Right (Step: 0.1)");
    drawText(-0.9f, 0.52f, "[R]       - Reset Position");
    drawText(-0.9f, 0.42f, "[ESC]     - Exit Program");

    glColor3f(1.0f, 0.84f, 0.0f); // Gold color
    drawStar(starX, starY, 0.15f, 0.06f);

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            starY += moveStep;
            break;

        case 's':
        case 'S':
            starY -= moveStep;
            break;

        case 'a':
        case 'A':
            starX -= moveStep;
            break;

        case 'd':
        case 'D':
            starX += moveStep;
            break;

        case 'r':
        case 'R':
            starX = 0.0f;
            starY = 0.0f;
            break;

        case 27:
            exit(0);
    }

    if (starX > 0.85f)
        starX = 0.85f;

    if (starX < -0.85f)
        starX = -0.85f;

    if (starY > 0.85f)
        starY = 0.85f;

    if (starY < -0.85f)
        starY = -0.85f;

    cout << "Position: "
         << starX << ", "
         << starY << endl;

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(700, 700);

    glutCreateWindow("Program 2 - Keyboard Controlled Star with Text");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}