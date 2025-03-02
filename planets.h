#include <stddef.h>
#include <time.h>
#include <stdlib.h>

#define DAY_TO_ROT_SPEED(day) ((360.0 / (day)) * 0.1)

extern void drawRectangle(float);
extern void drawEllipse(float);

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

Planet moon = (Planet) {
        .name = "moon",
        .color = 0xC2C5CC,
        .sun_distance = 0.11,
        .rotation_speed = 0,
        .translation_speed = -3.0,
        .size = 0.02,
};

Planet iss = (Planet) {
        .name = "iss",
        .color = 0xDDDDDD,
        .sun_distance = 0.06,
        .rotation_speed = 0.2,
        .translation_speed = 0,
        .size = 0.01,
        .draw = drawRectangle,
};

Planet earth = (Planet) {
        .name = "earth",
        .color = 0x008000,
        .sun_distance = 0.7,
        .rotation_speed = 2,
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

Planet SaturnBelt = (Planet) {
        .name = "saturno",
        .color = 0xcda056,
        .sun_distance = 0,
        .rotation_speed = 0,
        .translation_speed = 0,
        .size = 1,
        .draw = drawEllipse,
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


void
add_attached_planet(Planet *parent, Planet *child)
{
        parent->attached_planet =
        (Planet **) realloc(parent->attached_planet,
                            sizeof(Planet *) * (parent->attached_planet_n + 1));

        parent->attached_planet[parent->attached_planet_n] = child;
        parent->attached_planet_n++;
}

__attribute__((constructor)) void
__init_planet_data__()
{
        add_attached_planet(&earth, &moon);
        add_attached_planet(&earth, &iss);
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
        saturno.translation_angle = rand() % 360;
        urano.translation_angle = rand() % 360;
        neptuno.translation_angle = rand() % 360;
}

