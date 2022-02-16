/* Header file that contains details
for each texture */
#ifndef MAT_H
#define MAT_H

#include <stdio.h>
typedef struct  {
    float matambient[3];
    float matdiffuse[3];
    float matspecular[3];
    float shininess;
} Material;

static Material woodMat = {
.matambient = {0.25f, 0.148f, 0.06475f},
.matdiffuse = {0.4f, 0.2368f, 0.1036f},
.matspecular = {0.774597f, 0.458561f, 0.200621f},
.shininess = 10.6f
};

static Material stoneMat = {
.matambient = {0.05375f, 0.05f, 0.06625f},
.matdiffuse = {0.18275f, 0.17f, 0.22525f},
.matspecular = {0.332741f, 0.328634f, 0.346435f},
.shininess = 11.0f
};

static Material glassMat = {
.matambient = {0.23125, 0.23125, 0.23125},
.matdiffuse = {0.2775, 0.2775, 0.2775},
.matspecular = {0.773911, 0.773911, 0.773911},
.shininess = 51.0f
};

static Material leafMat = {
.matambient = {0.0215f,0.1745f,0.0215f},
.matdiffuse = {0.07568f,0.61424f,0.07568f},
.matspecular = {0.633f,0.727811f,0.633f},
.shininess = 32.0f
};

static Material grassMat = {
.matambient = {0.105882, 0.058824, 0.113725},
.matdiffuse = {0.427451, 0.470588, 0.541176},
.matspecular = {0.333333, 0.333333, 0.521569},
.shininess = 25.0f
};

static Material waterMat = {
.matambient = {1.0f, 0.5f, 0.31f},
.matdiffuse = {1.0f, 0.5f, 0.31f},
.matspecular = {0.5f, 0.5f, 0.5f},
.shininess = 32.0f
};

static Material pigMat = {
.matambient = {1.0f, 0.5f, 0.31f},
.matdiffuse = {1.0f, 0.5f, 0.31f},
.matspecular = {0.5f, 0.5f, 0.5f},
.shininess = 5.0f
};

#endif