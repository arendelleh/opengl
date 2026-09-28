#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

float moonX = 0.0f;
float moonY = 0.0f;

float starsX = 0.0f;
float starsY = 0.0f;

int score = 0;

void drawBitmapString(void* font, const char* str)
{
    for (const char* c = str; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void drawMoon(float cx, float cy, float radius)
{
    glColor3f(0.95f, 0.95f, 0.8f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10)
    {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(cx + cos(rad) * radius, cy + sin(rad) * radius);
    }
    glEnd();

    glColor3f(0.08f, 0.08f, 0.12f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10)
    {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(cx + 0.03f + cos(rad) * (radius * 0.85f), cy + 0.02f + sin(rad) * (radius * 0.85f));
    }
    glEnd();
}

void drawSingleStar(float cx, float cy, float outerR, float innerR)
{
    glColor3f(1.0f, 0.9f, 0.3f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 10; ++i)
    {
        float angle = i * 3.14159265f / 5.0f;
        float r = (i % 2 == 0) ? outerR : innerR;
        glVertex2f(cx + r * sin(angle), cy + r * cos(angle));
    }
    glEnd();
}

void drawStarCluster()
{
    drawSingleStar(starsX + 0.5f, starsY + 0.4f, 0.06f, 0.025f);
    drawSingleStar(starsX + 0.65f, starsY + 0.2f, 0.05f, 0.02f);
    drawSingleStar(starsX + 0.4f, starsY - 0.3f, 0.07f, 0.03f);
    drawSingleStar(starsX - 0.5f, starsY + 0.3f, 0.06f, 0.025f);
    drawSingleStar(starsX - 0.6f, starsY - 0.4f, 0.05f, 0.02f);
    drawSingleStar(starsX + 0.0f, starsY - 0.6f, 0.06f, 0.025f);
}

void drawHUD()
{
    char buffer[50];

    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.9f, 0.9f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    glColor3f(0.8f, 0.8f, 0.8f);
    glRasterPos2f(-0.9f, 0.76f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "=== MOON & STARS CONTROLS ===");
    glRasterPos2f(-0.9f, 0.66f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "[W][A][S][D] - Move Moon");
    glRasterPos2f(-0.9f, 0.56f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "[I][J][K][L] - Move Star Cluster");
    glRasterPos2f(-0.9f, 0.46f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "[R]          - Reset Positions");
    glRasterPos2f(-0.9f, 0.36f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "[ESC]        - Exit Program");
}

bool collision()
{
    float dx = moonX - (starsX + 0.5f);
    float dy = moonY - (starsY + 0.4f);
    return (dx * dx + dy * dy) < (0.12f * 0.12f);
}

void display()
{
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawMoon(moonX, moonY, 0.09f);
    drawStarCluster();
    drawHUD();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
        case 'W':
            moonY += 0.08f;
            break;

        case 's':
        case 'S':
            moonY -= 0.08f;
            break;

        case 'a':
        case 'A':
            moonX -= 0.08f;
            break;

        case 'd':
        case 'D':
            moonX += 0.08f;
            break;

        case 'i':
        case 'I':
            starsY += 0.08f;
            break;

        case 'k':
        case 'K':
            starsY -= 0.08f;
            break;

        case 'j':
        case 'J':
            starsX -= 0.08f;
            break;

        case 'l':
        case 'L':
            starsX += 0.08f;
            break;

        case 'r':
        case 'R':
            moonX = 0.0f;
            moonY = 0.0f;
            starsX = 0.0f;
            starsY = 0.0f;
            score = 0;
            cout << "Game restarted." << endl;
            break;

        case 27:
            exit(0);
    }

    if (moonX > 0.9f) moonX = 0.9f;
    if (moonX < -0.9f) moonX = -0.9f;
    if (moonY > 0.85f) moonY = 0.85f;
    if (moonY < -0.85f) moonY = -0.85f;

    if (starsX > 0.3f) starsX = 0.3f;
    if (starsX < -0.3f) starsX = -0.3f;
    if (starsY > 0.3f) starsY = 0.3f;
    if (starsY < -0.3f) starsY = -0.3f;

    if (collision())
    {
        score++;
        cout << "Star collected by Moon! Score: " << score << endl;
        starsX = ((rand() % 40) - 20) / 50.0f;
        starsY = ((rand() % 40) - 20) / 50.0f;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Program 5 - Movable Moon and Stars");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}