#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

int elapsedTime = 0;
double p1x, p1y, p2x, p2y;

void myInit(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // set background color
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void drawCircle(double x, double y, double r) {
    int n = 181;
    double step = 2 * 3.1416 / (n - 1);
    double angle = 0;
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < n; i++) {
        double tx = x + r * cos(angle);
        double ty = y + r * sin(angle);
        glVertex3d(tx, ty, 0.0);
        angle += step;
    }
	glEnd();
}

void drawArc(double x, double y, double r, double start, double end) {
    int n = 101;
    double step = (end - start) / (n - 1);
    glBegin(GL_LINE_STRIP);
    double tx = x + r * cos(start);
    double ty = y + r * sin(start) + 0.2;
    glVertex3d(tx, ty, 0.0);
    ty -= 0.2;
    glVertex3d(tx, ty, 0.0);
    for (int i = 0; i < n; i++) {
        tx = x + r * cos(start);
        ty = y + r * sin(start);
        glVertex3d(tx, ty, 0.0);
        start += step;
    }
    tx = x + r * cos(end);
    ty = y + r * sin(end) - 0.2;
    glVertex3d(tx, ty, 0.0);
    ty += 0.2;
    glVertex3d(tx, ty, 0.0);
	glEnd();
}

void drawLine(double startx, double starty, double endx, double endy) {
    glBegin(GL_LINES);
    glVertex3d(startx, starty, 0.0);
    glVertex3d(endx, endy, 0.0);
    glEnd();
}

void myDisplay(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // set background color
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(4);
    drawCircle(0, 0, 0.3);
    drawArc(0, 0, 0.65, 1.87, 4.41);
    drawArc(0, 0, 0.65, 1.27, -1.27);

    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(6);
    glPushMatrix();
        glTranslated(-0.473, 0.0, 0.0);
        glRotated(-90, 1, 0, 0);
        glutSolidCone(0.05, 0.1, 5, 5);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0.473, 0.0, 0.0);
        glRotated(-90, 1, 0, 0);
        glutSolidCone(0.05, 0.1, 5, 5);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 0.6, 0.0);
        glRotated(-90, 1, 0, 0);
        glutSolidCone(0.05, 0.1, 5, 5);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, -0.7, 0.0);
        glRotated(-90, 1, 0, 0);
        glutSolidCone(0.05, 0.1, 5, 5);
    glPopMatrix();
    drawCircle(0, 0, 0.475);
    drawLine(0.0, -0.8, 0.0, -0.475);
    drawLine(0.0, 0.475, 0.0, 0.8);

    glColor3f(1.0f, 0.0f, 0.0f); // set current draw color
	glPointSize(15.0);
	glBegin(GL_POINTS);
		glVertex3d(p1x, p1y, 0.0);
	glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // set current draw color
	glPointSize(15.0);
	glBegin(GL_POINTS);
		glVertex3d(p2x, p2y, 0.0);
	glEnd();

    glutSwapBuffers();
}

void move() {
    elapsedTime = (glutGet(GLUT_ELAPSED_TIME) / 100) % 50;
    //std::cout << elapsedTime << std::endl;
    if (elapsedTime >= 0 && elapsedTime < 10) {
        p1x = 0;
        p1y = -0.8 + 0.0325 * elapsedTime;
    }
    else if (elapsedTime >= 40 && elapsedTime < 50) {
        p1x = 0;
        p1y = 0.475 + 0.0325 * (elapsedTime-40);
    }
    else {
        double angle = 3.14/30.0*(elapsedTime-10);
        p1x = -0.475 * sin(angle);
        p1y = -0.475 * cos(angle);
    }

    if (elapsedTime >= 1 && elapsedTime < 11) {
        p2x = 0;
        p2y = -0.8 + 0.0325 * (elapsedTime-1);
    }
    else if (elapsedTime >= 11 && elapsedTime < 41) {
        double angle = 3.14/30.0*(elapsedTime-11);
        p2x = 0.475 * sin(angle);
        p2y = -0.475 * cos(angle);
    }
    else {
        p2x = 0;
        p2y = 0.475 + 0.0325 * ((elapsedTime+1)%10);
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv); // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set the display mode
	glutInitWindowSize(640, 600); // set the window size
	glutInitWindowPosition(10, 15); // set the window's right top corner position on screen
	glutCreateWindow(argv[0]); // open the creen with a name the same as the string store in argv[0]
	myInit();

	glutDisplayFunc(myDisplay); // register the redraw function (callbacks)
	glutIdleFunc(move);

	glutMainLoop(); // go into a perpetual loop
}