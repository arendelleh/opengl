#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

enum ShapeType { CONCENTRIC_SQUARES, DIAMOND_LATTICE, STARBURST_TRIANGLES };

struct Burst {
    float x, y;
    ShapeType shape;
    float scale;
    float alpha;
    float color[3];
    float speed;
    bool active;
};

vector<Burst> bursts;
ShapeType currentMode = CONCENTRIC_SQUARES;

void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

const char* getShapeName(ShapeType type) {
    switch (type) {
        case CONCENTRIC_SQUARES: return "Concentric Squares";
        case DIAMOND_LATTICE: return "Diamond Lattice";
        case STARBURST_TRIANGLES: return "Starburst Triangles";
        default: return "Unknown";
    }
}

void createBurst(float x, float y, ShapeType shape) {
    Burst b;
    b.x = x;
    b.y = y;
    b.shape = shape;
    b.scale = 0.05f;
    b.alpha = 1.0f;
    b.speed = 0.015f;
    b.active = true;

    b.color[0] = (rand() % 70 + 30) / 100.0f;
    b.color[1] = (rand() % 70 + 30) / 100.0f;
    b.color[2] = (rand() % 70 + 30) / 100.0f;

    bursts.push_back(b);
}

void drawConcentricSquares(const Burst& b) {
    for (int i = 1; i <= 3; i++) {
        float r = b.scale * i * 0.5f;
        glBegin(GL_LINE_LOOP);
            glVertex2f(b.x - r, b.y - r);
            glVertex2f(b.x + r, b.y - r);
            glVertex2f(b.x + r, b.y + r);
            glVertex2f(b.x - r, b.y + r);
        glEnd();
    }
}

void drawDiamondLattice(const Burst& b) {
    for (int i = 1; i <= 4; i++) {
        float r = b.scale * i * 0.4f;
        glBegin(GL_LINE_LOOP);
            glVertex2f(b.x, b.y + r);
            glVertex2f(b.x + r, b.y);
            glVertex2f(b.x, b.y - r);
            glVertex2f(b.x - r, b.y);
        glEnd();
    }
}

void drawStarburstTriangles(const Burst& b) {
    int numTriangles = 8;
    float radius = b.scale * 1.2f;

    for (int i = 0; i < numTriangles; i++) {
        float angle = i * (2.0f * 3.1415926f / numTriangles);
        float x1 = b.x + radius * cosf(angle);
        float y1 = b.y + radius * sinf(angle);

        float x2 = b.x + (radius * 0.3f) * cosf(angle + 0.3f);
        float y2 = b.y + (radius * 0.3f) * sinf(angle + 0.3f);

        glBegin(GL_TRIANGLES);
            glVertex2f(b.x, b.y);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        glEnd();
    }
}

void drawHUD() {
    char buffer[128];

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.95f, 0.9f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "DYNAMIC FIREWORKS STUDIO");

    snprintf(buffer, sizeof(buffer), "Active Bursts: %d", (int)bursts.size());
    glRasterPos2f(-0.95f, 0.82f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, buffer);

    snprintf(buffer, sizeof(buffer), "Current Mode: %s", getShapeName(currentMode));
    glRasterPos2f(-0.95f, 0.76f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, buffer);

    glColor3f(0.7f, 0.7f, 0.8f);
    glRasterPos2f(-0.95f, 0.66f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "CONTROLS:");
    glRasterPos2f(-0.95f, 0.60f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[1] - Concentric Squares");
    glRasterPos2f(-0.95f, 0.54f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[2] - Diamond Lattice");
    glRasterPos2f(-0.95f, 0.48f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[3] - Starburst Triangles");
    glRasterPos2f(-0.95f, 0.42f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[SPACE] - Random Burst");
    glRasterPos2f(-0.95f, 0.36f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[C] - Clear All");
    glRasterPos2f(-0.95f, 0.30f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "[ESC] - Exit");
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (size_t i = 0; i < bursts.size(); i++) {
        const Burst& b = bursts[i];
        if (!b.active) continue;

        glColor3f(b.color[0] * b.alpha, b.color[1] * b.alpha, b.color[2] * b.alpha);

        switch (b.shape) {
            case CONCENTRIC_SQUARES:
                drawConcentricSquares(b);
                break;
            case DIAMOND_LATTICE:
                drawDiamondLattice(b);
                break;
            case STARBURST_TRIANGLES:
                drawStarburstTriangles(b);
                break;
        }
    }

    drawHUD();

    glFlush();
}

void updateGame() {
    for (size_t i = 0; i < bursts.size(); i++) {
        if (bursts[i].active) {
            bursts[i].scale += bursts[i].speed;
            bursts[i].alpha -= 0.015f;

            if (bursts[i].alpha <= 0.0f) {
                bursts[i].active = false;
            }
        }
    }

    vector<Burst> activeBursts;
    for (size_t i = 0; i < bursts.size(); i++) {
        if (bursts[i].active) {
            activeBursts.push_back(bursts[i]);
        }
    }
    bursts = activeBursts;
}

void timer(int value) {
    updateGame();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '1') {
        currentMode = CONCENTRIC_SQUARES;
        float rx = (rand() % 120 - 40) / 100.0f;
        float ry = (rand() % 140 - 70) / 100.0f;
        createBurst(rx, ry, CONCENTRIC_SQUARES);
    }
    else if (key == '2') {
        currentMode = DIAMOND_LATTICE;
        float rx = (rand() % 120 - 40) / 100.0f;
        float ry = (rand() % 140 - 70) / 100.0f;
        createBurst(rx, ry, DIAMOND_LATTICE);
    }
    else if (key == '3') {
        currentMode = STARBURST_TRIANGLES;
        float rx = (rand() % 120 - 40) / 100.0f;
        float ry = (rand() % 140 - 70) / 100.0f;
        createBurst(rx, ry, STARBURST_TRIANGLES);
    }
    else if (key == ' ') {
        ShapeType randomShape = static_cast<ShapeType>(rand() % 3);
        float rx = (rand() % 120 - 40) / 100.0f;
        float ry = (rand() % 140 - 70) / 100.0f;
        createBurst(rx, ry, randomShape);
    }
    else if (key == 'c' || key == 'C') {
        bursts.clear();
    }
    else if (key == 27) {
        exit(0);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    srand(time(0));

    glutInit(&argc, argv);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Machine Problem 3 - Dynamic Fireworks & Shape Burst Studio");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}