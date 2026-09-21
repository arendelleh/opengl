#include <GL/glut.h>
#include <string>
#include <vector>
#include <cmath>

struct Schedule {
    std::string course;
    std::string title;
    std::string section;
    std::string day;
    std::string time;
    std::string room;
};

std::vector<Schedule> schedules = {
    {"CS0053", "Programming Tools and Techniques", "TN35", "Monday", "7:00 - 8:50 AM", "F702"},
    {"CS0011", "Mobile Programming", "TN35", "Monday", "11:00 - 12:50 PM", "F608"},
    {"CS0045", "Computer Graphics and Visual Computing", "TN35", "Monday", "13:00 - 14:50 PM", "E601"},
    {"CS0019", "Modeling and Simulation", "TN35", "Tuesday", "11:00 - 12:50 PM", "ONLINE"},
    {"CS0016", "Network and Communications 2A", "TN35", "Tuesday", "17:00 - 18:50 PM", "ONLINE"},
    {"CS0011", "Mobile Programming", "TN35", "Wednesday", "11:00 - 12:50 PM", "F1209"},
    {"CS0016", "Network and Communications 2A", "TN35", "Wednesday", "17:00 - 18:50 PM", "F1101"},
    {"CS0053", "Programming Tools and Techniques", "TN35", "Thursday", "7:00 - 8:50 AM", "F609"},
    {"CS0045", "Computer Graphics and Visual Computing", "TN35", "Thursday", "13:00 - 14:50 PM", "E610"},
    {"CS0025", "Software Engineering 1", "TN35", "Thursday", "15:00 - 16:50 PM", "E609"},
    {"CS0019", "Modeling and Simulation", "TN35", "Friday", "11:00 - 12:50 PM", "ONLINE"},
    {"CS0025", "Software Engineering 1", "TN35", "Friday", "15:00 - 16:50 PM", "ONLINE"}
};

void renderText(float x, float y, const std::string& text, void* font = GLUT_BITMAP_HELVETICA_12) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }
}

void drawRoundedRect(float x, float y, float width, float height, float radius, float r, float g, float b, float a = 1.0f) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(r, g, b, a);

    int numSegments = 16;
    float x1 = x + radius;
    float x2 = x + width - radius;
    float y1 = y - radius;
    float y2 = y - height + radius;

    glBegin(GL_POLYGON);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 3.14159f * 0.5f + (float)i / numSegments * (3.14159f * 0.5f);
        glVertex2f(x1 + cos(angle) * radius, y1 + sin(angle) * radius);
    }
    for (int i = 0; i <= numSegments; i++) {
        float angle = (float)i / numSegments * (3.14159f * 0.5f);
        glVertex2f(x2 + cos(angle) * radius, y1 + sin(angle) * radius);
    }
    for (int i = 0; i <= numSegments; i++) {
        float angle = 3.14159f * 1.5f + (float)i / numSegments * (3.14159f * 0.5f);
        glVertex2f(x2 + cos(angle) * radius, y2 + sin(angle) * radius);
    }
    for (int i = 0; i <= numSegments; i++) {
        float angle = 3.14159f + (float)i / numSegments * (3.14159f * 0.5f);
        glVertex2f(x1 + cos(angle) * radius, y2 + sin(angle) * radius);
    }
    glEnd();
    glDisable(GL_BLEND);
}

void drawCircle(float cx, float cy, float r, float red, float green, float blue, float a = 1.0f) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(red, green, blue, a);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(cx + cos(rad) * r, cy + sin(rad) * r);
    }
    glEnd();
    glDisable(GL_BLEND);
}

void drawBunnyHeader(float cx, float cy) {
    drawCircle(cx - 0.04f, cy + 0.08f, 0.025f, 0.98f, 0.95f, 0.95f);
    drawCircle(cx + 0.04f, cy + 0.08f, 0.025f, 0.98f, 0.95f, 0.95f);
    drawCircle(cx - 0.04f, cy + 0.08f, 0.015f, 0.95f, 0.85f, 0.90f);
    drawCircle(cx + 0.04f, cy + 0.08f, 0.015f, 0.95f, 0.85f, 0.90f);

    drawCircle(cx, cy, 0.065f, 0.98f, 0.96f, 0.96f);

    drawCircle(cx - 0.07f, cy + 0.01f, 0.03f, 0.82f, 0.75f, 0.82f);
    drawCircle(cx + 0.07f, cy + 0.01f, 0.03f, 0.82f, 0.75f, 0.82f);
    glLineWidth(3.0f);
    glColor3f(0.82f, 0.75f, 0.82f);
    glBegin(GL_LINES);
        glVertex2f(cx - 0.07f, cy + 0.01f);
        glVertex2f(cx + 0.07f, cy + 0.01f);
    glEnd();

    drawCircle(cx - 0.02f, cy + 0.01f, 0.005f, 0.2f, 0.1f, 0.2f);
    drawCircle(cx + 0.02f, cy + 0.01f, 0.005f, 0.2f, 0.1f, 0.2f);

    drawCircle(cx - 0.035f, cy - 0.01f, 0.012f, 1.0f, 0.75f, 0.82f, 0.5f);
    drawCircle(cx + 0.035f, cy - 0.01f, 0.012f, 1.0f, 0.75f, 0.82f, 0.5f);
}

void drawGradientBackground() {
    glBegin(GL_QUADS);
        glColor3f(0.98f, 0.92f, 0.95f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glColor3f(0.92f, 0.85f, 0.92f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGradientBackground();

    drawRoundedRect(-0.95f, 0.95f, 1.90f, 0.18f, 0.03f, 1.0f, 0.88f, 0.93f, 0.85f);
    drawBunnyHeader(0.0f, 0.86f);

    glColor3f(0.12f, 0.08f, 0.20f);
    renderText(-0.85f, 0.87f, "STUDENT INFORMATION SYSTEM", GLUT_BITMAP_HELVETICA_18);
    renderText(0.35f, 0.87f, "FEU INSTITUTE OF TECHNOLOGY", GLUT_BITMAP_HELVETICA_12);

    drawRoundedRect(-0.95f, 0.74f, 1.90f, 0.32f, 0.03f, 1.0f, 1.0f, 1.0f, 0.85f);

    glColor3f(0.10f, 0.08f, 0.18f);
    renderText(-0.90f, 0.68f, "Student Number: 202410846");
    renderText(-0.90f, 0.63f, "First Name: ERIN DALE");
    renderText(-0.90f, 0.58f, "Middle Name: TORRES");
    renderText(-0.90f, 0.53f, "Last Name: GAETOS");
    renderText(-0.90f, 0.48f, "Personal Email: arendelleh@gmail.com");

    renderText(0.05f, 0.68f, "School Email: etgaetos@fit.edu.ph");
    renderText(0.05f, 0.63f, "Enrollment Status: Term 1 SY 20262027", GLUT_BITMAP_HELVETICA_12);
    renderText(0.05f, 0.58f, "Program / Year: BSCSSE / Year 3");
    renderText(0.05f, 0.53f, "Registration Status: 18 UNITS ENROLLED");
    renderText(0.05f, 0.48f, "Student Type: REGULAR");

    drawRoundedRect(-0.95f, 0.39f, 0.16f, 0.055f, 0.02f, 0.78f, 0.82f, 0.67f, 1.0f);
    drawRoundedRect(-0.78f, 0.39f, 0.48f, 0.055f, 0.02f, 0.80f, 0.34f, 0.51f, 1.0f);
    drawRoundedRect(-0.29f, 0.39f, 0.18f, 0.055f, 0.02f, 0.78f, 0.85f, 0.85f, 1.0f);
    drawRoundedRect(-0.10f, 0.39f, 0.23f, 0.055f, 0.02f, 0.94f, 0.93f, 0.95f, 1.0f);
    drawRoundedRect(0.14f, 0.39f, 0.38f, 0.055f, 0.02f, 0.86f, 0.82f, 0.67f, 1.0f);
    drawRoundedRect(0.53f, 0.39f, 0.42f, 0.055f, 0.02f, 0.78f, 0.85f, 0.85f, 1.0f);

    glColor3f(0.05f, 0.05f, 0.12f);
    renderText(-0.93f, 0.355f, "Course");
    renderText(-0.76f, 0.355f, "Title");
    renderText(-0.27f, 0.355f, "Section");
    renderText(-0.08f, 0.355f, "Day");
    renderText(0.16f, 0.355f, "Time");
    renderText(0.55f, 0.355f, "Room");

    float startY = 0.31f;
    float rowHeight = 0.08f;

    for (size_t i = 0; i < schedules.size(); ++i) {
        float currentY = startY - (i * rowHeight);

        drawRoundedRect(-0.95f, currentY + 0.01f, 0.16f, 0.065f, 0.02f, 0.95f, 0.94f, 0.96f, 0.95f);
        drawRoundedRect(-0.78f, currentY + 0.01f, 0.48f, 0.065f, 0.02f, 0.82f, 0.88f, 0.88f, 0.95f);
        drawRoundedRect(-0.29f, currentY + 0.01f, 0.18f, 0.065f, 0.02f, 0.88f, 0.84f, 0.70f, 0.95f);
        drawRoundedRect(-0.10f, currentY + 0.01f, 0.23f, 0.065f, 0.02f, 0.82f, 0.40f, 0.55f, 0.95f);
        drawRoundedRect(0.14f, currentY + 0.01f, 0.38f, 0.065f, 0.02f, 0.95f, 0.94f, 0.96f, 0.95f);
        drawRoundedRect(0.53f, currentY + 0.01f, 0.42f, 0.065f, 0.02f, 0.82f, 0.88f, 0.88f, 0.95f);

        glColor3f(0.08f, 0.05f, 0.15f);
        renderText(-0.93f, currentY - 0.028f, schedules[i].course);
        renderText(-0.76f, currentY - 0.028f, schedules[i].title);
        renderText(-0.27f, currentY - 0.028f, schedules[i].section);
        renderText(-0.08f, currentY - 0.028f, schedules[i].day);
        renderText(0.16f, currentY - 0.028f, schedules[i].time);
        renderText(0.55f, currentY - 0.028f, schedules[i].room);
    }

    glFlush();
}

void init() {
    glClearColor(0.98f, 0.92f, 0.95f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280, 960);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Student Information System - Bunny Header");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}