#include <GL/glut.h>
#include <math.h>

void
drawRectangle(float scale)
{
        glPushMatrix();
        glScalef(scale, scale, scale);
        glBegin(GL_QUADS);
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);

        // Bottom face (y = -1.0f)
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        // Front face  (z = 1.0f)
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);

        // Back face (z = -1.0f)
        glVertex3f(1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        // Left face (x = -1.0f)
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);

        // Right face (x = 1.0f)
        glVertex3f(1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);

        glEnd();
        glPopMatrix();
}

void
drawEllipse(float scale)
{
        int i, x = 0, y = 0;
        float desp = 0;
        double radius = 0.10;
        double twicePi = 2.0 * 3.142;
        glPushMatrix();
        glScalef(scale, scale, scale);
        glBegin(GL_TRIANGLE_FAN); // BEGIN CIRCLE
        glVertex3f(x, y, desp); // center of circle
        for (i = 0; i <= 20; i++) {
                glVertex3f((x + (radius * cos(i * twicePi / 20))),
                           (y + (radius * sin(i * twicePi / 20))), desp);
        }
        glEnd(); // END
        glBegin(GL_TRIANGLE_FAN); // BEGIN CIRCLE
        glVertex3f(x, y, desp); // center of circle
        for (i = 0; i <= 20; i++) {
                glVertex3f((y + (radius * sin(i * twicePi / 20))),
                           (x + (radius * cos(i * twicePi / 20))), desp);
        }
        glEnd(); // END
        glPopMatrix();
}

