#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

unsigned char* data;
int width, height, nrChannels;
unsigned int texture;

void init() {
    // Fondo de ventana de visualizacion
    glClearColor(0.4, 0.4, 0.4, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    if (w <= h)
        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w,
            1.0 * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(-1.0 * (GLfloat)w / (GLfloat)h,
            1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void Draw(void)
{
    //Definicion y activacion de la textura
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //Parametros de aplicacion y ajuste de resolucion de la textura 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Carga de imagen y acoplamiento a profundidad
    unsigned char* data = stbi_load("C:\\Users\\Public\\Pictures\\ImagenPrueba.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture");
    }
    stbi_image_free(data);

    //Aplicacion de la textura
    glBegin(GL_POLYGON);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.5, -0.5, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glEnd();
    //	glTraslate(0.8,0.8,0.0);
    glDisable(GL_TEXTURE_2D);
    glFlush();
}

int
main(int argc, char** argv)
{
    glutInit(&argc, argv);
    init();
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 600);
    glutCreateWindow("Texturas modo inmediato");
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("glewInit failed: %s", glewGetErrorString(err));
        exit(1);
    }
    glutDisplayFunc(Draw);
    glutReshapeFunc(reshape);
    glutMainLoop();
}