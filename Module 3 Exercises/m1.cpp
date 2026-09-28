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
#include <ctime>

using namespace std;

enum ColorState { RED, GREEN, BLUE };

ColorState playerColor = RED;
ColorState barrierColor = GREEN;

float barrierY = 1.2f;
float barrierSpeed = 0.01f;
float baseSpeed = 0.01f;

int score = 0;
bool gameOver = false;

void drawBitmapString(void* font, const char* str)
{
    for (const char* c = str; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void setColor(ColorState color)
{
    switch (color)
    {
        case RED:
            glColor3f(1.0f, 0.2f, 0.2f);
            break;
        case GREEN:
            glColor3f(0.2f, 1.0f, 0.2f);
            break;
        case BLUE:
            glColor3f(0.2f, 0.5f, 1.0f);
            break;
    }
}

const char* getColorName(ColorState color)
{
    switch (color)
    {
        case RED: return "RED";
        case GREEN: return "GREEN";
        case BLUE: return "BLUE";
        default: return "UNKNOWN";
    }
}

void drawPlayer()
{
    setColor(playerColor);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, -0.1f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(-0.1f, 0.1f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.105f, -0.105f);
        glVertex2f(0.105f, -0.105f);
        glVertex2f(0.105f, 0.105f);
        glVertex2f(-0.105f, 0.105f);
    glEnd();
}

void drawBarrier()
{
    setColor(barrierColor);
    glBegin(GL_POLYGON);
        glVertex2f(-0.8f, barrierY - 0.04f);
        glVertex2f(0.8f, barrierY - 0.04f);
        glVertex2f(0.8f, barrierY + 0.04f);
        glVertex2f(-0.8f, barrierY + 0.04f);
    glEnd();
}

void drawDashboard()
{
    char buffer[100];

    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.9f, 0.9f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    snprintf(buffer, sizeof(buffer), "Player Color: %s", getColorName(playerColor));
    glRasterPos2f(-0.9f, 0.82f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    glColor3f(0.7f, 0.7f, 0.8f);
    glRasterPos2f(-0.9f, 0.72f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "CONTROLS:");
    glRasterPos2f(-0.9f, 0.66f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[R] - Change to RED");
    glRasterPos2f(-0.9f, 0.60f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[G] - Change to GREEN");
    glRasterPos2f(-0.9f, 0.54f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[B] - Change to BLUE");
    glRasterPos2f(-0.9f, 0.48f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[SPACE] - Restart Game");
    glRasterPos2f(-0.9f, 0.42f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[ESC] - Exit");

    glColor3f(1.0f, 0.8f, 0.2f);
    glRasterPos2f(-0.9f, -0.85f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "RULE: Match barrier color! Mismatch = Game Over.");

    if (gameOver)
    {
        glColor3f(1.0f, 0.2f, 0.2f);
        glRasterPos2f(-0.4f, 0.0f);
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "GAME OVER - Press SPACE to Restart");
    }
}

void resetBarrier()
{
    barrierY = 1.2f;
    barrierColor = static_cast<ColorState>(rand() % 3);
}

void resetGame()
{
    score = 0;
    barrierSpeed = baseSpeed;
    playerColor = RED;
    gameOver = false;
    resetBarrier();
}

void updateGame()
{
    if (gameOver) return;

    barrierY -= barrierSpeed;

    if (barrierY <= 0.1f && barrierY >= -0.1f)
    {
        if (playerColor == barrierColor)
        {
            score++;
            barrierSpeed += 0.002f;
            resetBarrier();
        }
        else
        {
            gameOver = true;
        }
    }
    else if (barrierY < -1.1f)
    {
        resetBarrier();
    }
}

void display()
{
    glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!gameOver)
    {
        drawBarrier();
        drawPlayer();
    }

    drawDashboard();

    glFlush();
}

void timer(int value)
{
    updateGame();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (!gameOver)
    {
        if (key == 'r' || key == 'R') playerColor = RED;
        if (key == 'g' || key == 'G') playerColor = GREEN;
        if (key == 'b' || key == 'B') playerColor = BLUE;
    }

    if (key == ' ')
    {
        resetGame();
    }
    else if (key == 27)
    {
        exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    srand(time(0));

    glutInit(&argc, argv);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Machine Problem 2 - Chroma-Shift: The Color-Matching Gate");

    resetGame();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}