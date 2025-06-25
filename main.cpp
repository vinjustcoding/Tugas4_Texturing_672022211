#include <GL/freeglut.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint textures[6];
float angle = 0.0f;

const char* imagePaths[6] = {
    "D:/Texturing/jdm_images/1.png",
    "D:/Texturing/jdm_images/2.png",
    "D:/Texturing/jdm_images/3.png",
    "D:/Texturing/jdm_images/4.png",
    "D:/Texturing/jdm_images/5.png",
    "D:/Texturing/jdm_images/6.png"
};

void loadTextures() {
    glGenTextures(6, textures);
    for (int i = 0; i < 6; ++i) {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(imagePaths[i], &width, &height, &nrChannels, STBI_rgb_alpha);
        if (data) {
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            stbi_image_free(data);
        } else {
            std::cerr << "Failed to load image: " << imagePaths[i] << std::endl;
        }
    }
}

void drawCube() {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0); glVertex3f( 1, -1, 1);
    glTexCoord2f(1, 1); glVertex3f( 1,  1, 1);
    glTexCoord2f(0, 1); glVertex3f(-1,  1, 1);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( 1, -1, -1);
    glTexCoord2f(1, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 1); glVertex3f(-1,  1, -1);
    glTexCoord2f(0, 1); glVertex3f( 1,  1, -1);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0); glVertex3f(-1, -1,  1);
    glTexCoord2f(1, 1); glVertex3f(-1,  1,  1);
    glTexCoord2f(0, 1); glVertex3f(-1,  1, -1);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( 1, -1,  1);
    glTexCoord2f(1, 0); glVertex3f( 1, -1, -1);
    glTexCoord2f(1, 1); glVertex3f( 1,  1, -1);
    glTexCoord2f(0, 1); glVertex3f( 1,  1,  1);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1,  1,  1);
    glTexCoord2f(1, 0); glVertex3f( 1,  1,  1);
    glTexCoord2f(1, 1); glVertex3f( 1,  1, -1);
    glTexCoord2f(0, 1); glVertex3f(-1,  1, -1);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0); glVertex3f( 1, -1, -1);
    glTexCoord2f(1, 1); glVertex3f( 1, -1,  1);
    glTexCoord2f(0, 1); glVertex3f(-1, -1,  1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0, 0, 5,
              0, 0, 0,
              0, 1, 0);

    glRotatef(angle, 1, 1, 0);
    drawCube();
    glutSwapBuffers();
}

void timer(int) {
    angle += 0.5f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    loadTextures();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Textured Rotating Cube");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
