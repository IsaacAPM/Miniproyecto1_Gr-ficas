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

static void Textura(char dir[]){
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
    unsigned char* data = stbi_load(dir, &width, &height, &nrChannels, 0);
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
    glVertex3f(1.0, -1.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glFlush();
}

static void Draw(void)
{
    // Fondo de ventana de visualizacion
    glClearColor(0.4, 0.4, 0.4, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    Textura("C:\\Users\\Public\\Pictures\\ImagenPrueba.jpg");
    
}

int
main(int argc, char** argv)
{
    glutInit(&argc, argv);
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
    glutMainLoop();
}