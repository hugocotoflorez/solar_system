#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

#include "draw.h"
#include "planets.h"
#include "sphere.h"

#define CAM_ROT_INC 0.1
#define PI 3.1416

#define glHexColor(hex_color)                             \
        glColor3f(((hex_color & 0xFF0000) >> 16) / 256.0, \
                  ((hex_color & 0xFF00) >> 8) / 256.0, (hex_color & 0xFF) / 256.0);


const int W_WIDTH = 500;
const int W_HEIGHT = 500;

float cam_dist = 3.0;
float cam_rot_alpha = 0;
float cam_rot_beta = 0;

enum TipoCamara {
        CAM_LIBRE = 0,
        CAM_LOOKAT_PLANET = 1,
} tipo_camara;

glm::vec3
get_position(Planet p)
{
        return glm::vec3(p.modelviewMatrix[12], p.modelviewMatrix[13],
                         p.modelviewMatrix[14]);
}


void
myCamara()
{
        glm::vec3 cameraPosition;
        glm::vec3 cameraTarget;
        glm::vec3 cameraUp;

        switch (tipo_camara) {
        case CAM_LIBRE:
                cameraPosition =
                glm::vec3(((float) cam_dist * (float) sin(cam_rot_alpha) * cos(cam_rot_beta)),
                          ((float) cam_dist * (float) sin(cam_rot_beta)),
                          ((float) cam_dist * cos(cam_rot_alpha) * cos(cam_rot_beta)));

                cameraTarget = glm::vec3(0, 0, 0);
                cameraUp = glm::vec3(0, (cos(cam_rot_beta) >= 0 ? 1 : -1), 0);
                break;

        case CAM_LOOKAT_PLANET:

                /* FROM (earth) */
                cameraPosition = get_position(earth);
                /* TO (marte) */
                cameraTarget = get_position(marte);

                cameraUp = glm::vec3(0, (cos(cam_rot_beta) >= 0 ? 1 : -1), 0);
                break;
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (float) W_WIDTH / W_HEIGHT, 0.1, 100.0);
        gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z,
                  cameraTarget.x, cameraTarget.y, cameraTarget.z, cameraUp.x,
                  cameraUp.y, cameraUp.z);

        glMatrixMode(GL_MODELVIEW);
}

void
myTeclado(unsigned char tras, int x, int y)
{
        switch (tras) {
        case 'j':
                cam_dist += 0.1;
                break;
        case 'k':
                cam_dist -= 0.1;
                break;
        case 'c':
                if (tipo_camara == CAM_LIBRE)
                        tipo_camara = CAM_LOOKAT_PLANET;
                else if (tipo_camara == CAM_LOOKAT_PLANET)
                        tipo_camara = CAM_LIBRE;
                break;
        case 27:
                exit(0);
        }
}


void
myTeclasespeciales(int cursor, int x, int y)
{
        switch (cursor) {
                // Giros:
        case GLUT_KEY_UP:
                cam_rot_beta += CAM_ROT_INC;
                break;
        case GLUT_KEY_DOWN:
                cam_rot_beta -= CAM_ROT_INC;
                break;
        case GLUT_KEY_RIGHT:
                cam_rot_alpha -= CAM_ROT_INC;
                break;
        case GLUT_KEY_LEFT:
                cam_rot_alpha += CAM_ROT_INC;
                break;
        default:
                break;
        }
        if (cam_rot_alpha > PI * 2.0)
                cam_rot_alpha = 0;
        if (cam_rot_alpha < 0)
                cam_rot_alpha = PI * 2.0;
        if (cam_rot_beta > PI * 2.0)
                cam_rot_beta = 0;
        if (cam_rot_beta < 0)
                cam_rot_beta = PI * 2.0;

        glutPostRedisplay();
}

void
displayObject(Planet *o)
{
        glPushMatrix();

        glHexColor(o->color);

        // Translation mevement
        o->translation_angle += o->translation_speed;
        if (o->translation_angle >= 360.0)
                o->translation_angle -= 360.0;

        // Rotation movement
        o->rotation_angle += o->rotation_speed;
        if (o->rotation_angle >= 360.0)
                o->rotation_angle -= 360.0;

        /* Translate SUN_DISTANCE units with TRANSLATION_ANGLE degrees and
         * then rotate ROTATION_ANGLE over itself. */
        glRotatef(o->translation_angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, o->sun_distance, 0.0f);
        glRotatef(o->rotation_angle, 0.0f, 0.0f, 1.0f);

        glGetFloatv(GL_MODELVIEW_MATRIX, o->modelviewMatrix);

        /* If custom draw funtion is null, use myEsfera */
        if (o->draw)
                o->draw(o->size);
        else
                myEsfera(o->size);

        /* Call recursivelly for each attached child */
        for (int i = 0; i < o->attached_planet_n; i++) {
                displayObject(o->attached_planet[i]);
        }

        glPopMatrix();
}

void
idle()
{
        glutPostRedisplay();
}

// Función de display
void
Display(void)
{
        // Clear the window with current clearing color

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        myCamara();

        /* Every planet is attached to sun as they orbit around it */
        displayObject(&sun);

        glutSwapBuffers();
        glFlush();
}

void
openGlInit()
{
        glClearDepth(1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
}


int
main(int argc, char **argv)
{
        glutInit(&argc, argv);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(W_WIDTH, W_HEIGHT);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutCreateWindow("SolarSystem or it would looks like that.");
        glutFullScreen();

        glutDisplayFunc(Display);

        /* Criminal esto pero sin la idle function no me tira */
        glutIdleFunc(idle);

        glutKeyboardFunc(myTeclado);
        glutSpecialFunc(myTeclasespeciales);
        openGlInit();

        glutMainLoop();
        return 0;
}
