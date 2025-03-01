#include <GL/freeglut_std.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "sphere.h"

#include <math.h>

#define INCREMENTO .1
#define PI 3.1416

const int W_WIDTH = 500;
const int W_HEIGHT = 500;

float DISTANCIA = 1.5;
float alpha = 0;
float beta = 0;


void
myCamara()
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-DISTANCIA, DISTANCIA, -DISTANCIA, DISTANCIA, -10 * DISTANCIA, 10 * DISTANCIA);
        gluLookAt(((float) DISTANCIA * (float) sin(alpha) * cos(beta)),
                  ((float) DISTANCIA * (float) sin(beta)),
                  ((float) DISTANCIA * cos(alpha) * cos(beta)), 0, 0, 0, 0,
                  (cos(beta) >= 0 ? 1 : -1), 0);
}

void
myTeclado(unsigned char tras, int x, int y)
{
        switch (tras) {
        case 'j':
                DISTANCIA += 0.1;
                break;
        case 'k':
                DISTANCIA -= 0.1;
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
                beta += INCREMENTO;
                break;
        case GLUT_KEY_DOWN:
                beta -= INCREMENTO;
                break;
        case GLUT_KEY_RIGHT:
                alpha -= INCREMENTO;
                break;
        case GLUT_KEY_LEFT:
                alpha += INCREMENTO;
                break;
        default:
                break;
        }
        if (alpha > PI * 2.0)
                alpha = 0;
        if (alpha < 0)
                alpha = PI * 2.0;
        if (beta > PI * 2.0)
                beta = 0;
        if (beta < 0)
                beta = PI * 2.0;

        glutPostRedisplay();
}

#define glHexColor(hex_color)                             \
        glColor3f(((hex_color & 0xFF0000) >> 16) / 256.0, \
                  ((hex_color & 0xFF00) >> 8) / 256.0, (hex_color & 0xFF) / 256.0);

void
DrawEllipse(float scale)
{
        int i, x = 0, y = 0;
        double radius = 0.10;
        double twicePi = 2.0 * 3.142;
        glPushMatrix();
        glScalef(scale, scale, scale);
        glBegin(GL_TRIANGLE_FAN); // BEGIN CIRCLE
        glVertex3f(x, y, 0.48f); // center of circle
        for (i = 0; i <= 20; i++) {
                glVertex3f((x + (radius * cos(i * twicePi / 20))),
                           (y + (radius * sin(i * twicePi / 20))), 0.48f);
        }
        glEnd(); // END
        glBegin(GL_TRIANGLE_FAN); // BEGIN CIRCLE
        glVertex3f(x, y, 0.475f); // center of circle
        for (i = 0; i <= 20; i++) {
                glVertex3f((y + (radius * sin(i * twicePi / 20))),
                           (x + (radius * cos(i * twicePi / 20))), 0.475f);
        }
        glEnd(); // END
        glPopMatrix();
}

typedef struct Planet {
        char name[16];
        int color; // as hex rgb (0xRRGGBB)
        float sun_distance;
        float rotation_speed;
        float translation_speed;
        float size;
        float rotation_angle;
        float translation_angle;
        struct Planet **attached_planet;
        size_t attached_planet_n;
        void (*draw)(float scale);
} Planet;

Planet SaturnBelt = (Planet) {
        .name = "saturno",
        .color = 0xcda056,
        .sun_distance = 0,
        .rotation_speed = 0,
        .translation_speed = 0,
        .size = 1,
        .draw = DrawEllipse,
};

void
add_attached_planet(Planet *parent, Planet *child)
{
        parent->attached_planet =
        (Planet **) realloc(parent->attached_planet,
                            sizeof(Planet *) * (parent->attached_planet_n + 1));

        parent->attached_planet[parent->attached_planet_n] = child;
        parent->attached_planet_n++;
}

#define INC 0.1
#define DAY_TO_ROT_SPEED(day) ((360.0 / (day)) * INC)

Planet moon = (Planet) {
        .name = "moon",
        .color = 0xC2C5CC,
        .sun_distance = 0.1,
        .rotation_speed = 0,
        .translation_speed = DAY_TO_ROT_SPEED(28),
        .size = 0.02,
};

Planet earth = (Planet) {
        .name = "earth",
        .color = 0x008000,
        .sun_distance = 0.7,
        .rotation_speed = 0.3,
        .translation_speed = DAY_TO_ROT_SPEED(365),
        .size = 0.05,
};

Planet mercurio = (Planet) {
        .name = "mercurio",
        .color = 0xe7e8ec,
        .sun_distance = 0.35,
        .rotation_speed = 0.3,
        .translation_speed = DAY_TO_ROT_SPEED(88),
        .size = 0.03,
};

Planet venus = (Planet) {
        .name = "venus",
        .color = 0xd3a5d7,
        .sun_distance = 0.5,
        .rotation_speed = 0.3,
        .translation_speed = DAY_TO_ROT_SPEED(225),
        .size = 0.04,
};

Planet marte = (Planet) {
        .name = "marte",
        .color = 0xc1440e,
        .sun_distance = 0.9,
        .rotation_speed = 0.3,
        .translation_speed = DAY_TO_ROT_SPEED(686),
        .size = 0.04,
};

Planet jupiter = (Planet) {
        .name = "earth",
        .color = 0x008000,
        .sun_distance = 1,
        .rotation_speed = 0.3,
        .translation_speed = DAY_TO_ROT_SPEED(365 * 12),
        .size = 0.07,
};

Planet saturno = (Planet) {
        .name = "saturno",
        .color = 0xc4bcaa,
        .sun_distance = 1.20,
        .rotation_speed = 0.3,
        .translation_speed = DAY_TO_ROT_SPEED(365 * 29.5),
        .size = 0.06,
};

Planet urano = (Planet) {
        .name = "urano",
        .color = 0xd1e7e7,
        .sun_distance = 1.35,
        .rotation_speed = 0.3,
        .translation_speed = DAY_TO_ROT_SPEED(365 * 84),
        .size = 0.05,
};

Planet neptuno = (Planet) {
        .name = "neptuno",
        .color = 0x1f4fa1,
        .sun_distance = 1.50,
        .rotation_speed = 0.3,
        .translation_speed = DAY_TO_ROT_SPEED(365 * 165),
        .size = 0.05,
};

Planet sun = (Planet) {
        .name = "sun",
        .color = 0xFF6600,
        .size = 0.2,

};

__attribute__((constructor)) void
__init_planet_data__()
{
        add_attached_planet(&earth, &moon);
        add_attached_planet(&sun, &mercurio);
        add_attached_planet(&sun, &venus);
        add_attached_planet(&sun, &earth);
        add_attached_planet(&sun, &marte);
        add_attached_planet(&sun, &saturno);
        add_attached_planet(&sun, &urano);
        add_attached_planet(&sun, &neptuno);
        add_attached_planet(&saturno, &SaturnBelt);

        // set random seed
        srand(time(NULL));
        mercurio.translation_angle = rand() % 360;
        venus.translation_angle = rand() % 360;
        earth.translation_angle = rand() % 360;
        marte.translation_angle = rand() % 360;
        urano.translation_angle = rand() % 360;
        neptuno.translation_angle = rand() % 360;
}

void
displayObject(Planet *o)
{
        glPushMatrix();

        // First Electron Orbit
        // Save viewing transformation
        glHexColor(o->color);

        // Rotate by angle of revolution
        // Sumamos a la translacion
        o->translation_angle += o->translation_speed;
        if (o->translation_angle >= 360.0)
                o->translation_angle -= 360.0;

        o->rotation_angle += o->rotation_speed;
        if (o->rotation_angle >= 360.0)
                o->rotation_angle -= 360.0;

        glRotatef(o->translation_angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, o->sun_distance, 0.0f);
        glRotatef(o->rotation_angle, 0.0f, 0.0f, 1.0f);

        if (o->draw)
                o->draw(o->size);
        else
                myEsfera(o->size);

        for (int i = 0; i < o->attached_planet_n; i++) {
                displayObject(o->attached_planet[i]);
        }


        glPopMatrix();
}

// Función de display
void
Display(void)
{
        // Clear the window with current clearing color

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Se activa la matriz del modelador
        glMatrixMode(GL_MODELVIEW);
        // Inicializamos la matriz del modelo a la identidad
        glLoadIdentity();

        glTranslatef(0.0f, 0.0f, -0.5f);

        myCamara();

        displayObject(&sun);

        // Se limpian los buffers
        glutSwapBuffers();
        glFlush();
}

void
openGlInit()
{
        // Habilito aqui el depth en vez de arriba para los usuarios de linux y
        // mac mejor arriba Incializaciones varias
        glClearDepth(1.0f); // Valor z-buffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // valor limpieza buffer color
        glEnable(GL_DEPTH_TEST); // z-buffer
        glEnable(GL_CULL_FACE); // ocultacion caras back
        glCullFace(GL_BACK);
}


int
main(int argc, char **argv)
{
        glutInit(&argc, argv);
        // Posicion de la ventana
        glutInitWindowPosition(100, 100);
        // Tamano de la ventana
        glutInitWindowSize(W_WIDTH, W_HEIGHT);
        // Tipo de color y buffer
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        // Crear la ventana
        glutCreateWindow("Ventana con el Visual C++ y glut");

        // Funcion de dibujo
        glutDisplayFunc(Display);
        glutIdleFunc(Display);
        // Funcion que mira el teclado
        glutKeyboardFunc(myTeclado);
        glutSpecialFunc(myTeclasespeciales);

        openGlInit();

        // Lazo principal
        glutMainLoop();
        return 0;
}
