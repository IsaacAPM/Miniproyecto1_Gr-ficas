#include "GL/freeglut.h"
#include "GL/gl.h"
#include <stdio.h>

double rotacion = 0.5, x = 0, velocidad = 180;
double delta;
int tiempoActual, tiempoAnterior;

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Se actualizan los valores de la animación
void animacionTiempo(double delta) {
 
    delta = delta / 1000;
    rotacion += velocidad * delta;
    if (x > 5) {
        x = -5;
    }
    else {
        x += 5 * delta;
    }
}

void animar() {
    tiempoActual = glutGet(GLUT_ELAPSED_TIME);
    delta = (double)(tiempoActual - tiempoAnterior);
    if (delta > 20.0) {
        tiempoAnterior = tiempoActual;
        animacionTiempo(delta);
        glutPostRedisplay();
    }
}

void dibuja() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    /* Se guarda la matriz de transformación para no afectar
     * las siguientes primitivas dibujadas */
    glPushMatrix();
    glTranslatef(x, 0.0f, 0.0f);
    glRotatef(rotacion, 0.0f, 1.0f, 0.0f);
    glutSolidTeapot(1.0f);
    //glutWireTeapot(1.0f);
    /* Regresamos la matriz de transformación a su estado
     * anterior para volver a dibujar desde el origen */
    glPopMatrix();
    /* Se cambia al buffer con el nuevo contenido */
    glutSwapBuffers();
}

void teclas(unsigned char key, int x, int y) {
    printf("%d\n", key);
    switch (key) {
        /* Salir del programa */
    case 27:
        exit(0);
        break;
        /* Aumentar o disminuir velocidad de rotación */
    case 43:
        velocidad += 100;
        break;
    case 45:
        velocidad -= 100;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Animacion Tetera");

    glutReshapeFunc(reshape);
    glutIdleFunc(animar);
    glutKeyboardFunc(teclas);
    glutDisplayFunc(dibuja);
    glClearColor(0.3, 0.3, 0.3, 1.0);
    /* Luces y DEPTH_TEST para poder ver bien el modelo */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    /* posición y orientación */
    gluLookAt(0.0, 0.0, 10.0, /* eye point */
        0.0, 0.0, 0.0,  /* punto de referencia */
        0.0, 1.0, 0.0); /* vector que indica arriba, en este caso Y */
    tiempoActual = tiempoAnterior = 0;
    glutMainLoop();
    return 0;
}