#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

// Variables para controlar la animación
double rotacion = 0.5, x = 0, velocidad = 180;
double delta;
int tiempoActual, tiempoAnterior;

// Variables para el manejo de la textura
unsigned char* data;
int width, height, nrChannels;
unsigned int texture;

// Se llama cuando se modifica el tamaño de la ventana de visualización
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

// Actualiza los valores de rotación y desplazamiento en el eje x del objeto
void animacionTiempo(double delta) {
    delta = delta / 1000;
    rotacion += velocidad * delta;
    if (x > 2) {
        x = -2;
    }
    else {
        x += 2 * delta;
    }
}

// Se invoca cuando no se está refrescando o renderizando (CPU ocioso)
void animar() {
    tiempoActual = glutGet(GLUT_ELAPSED_TIME);
    delta = (double)(tiempoActual - tiempoAnterior);
    if (delta > 20.0) {
        tiempoAnterior = tiempoActual;
        animacionTiempo(delta);
        glutPostRedisplay();
    }
}

// Es llamada cada vez que se debe refrescar la pantalla
void dibuja() {
    // Limpia y coloca color de fondo a la ventana de visulizacion
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

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

    // Operaciones de transformación sobre los objetos de la escena usando la pila
    glPushMatrix();
    glTranslatef(x, 0.0f, 0.0f);
    glRotatef(rotacion, 0.0f, 0.0f, 1.0f);

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
    glDisable(GL_TEXTURE_2D);

    // Se desempila la matriz para calcular una nueva transformacion
    glPopMatrix();

    // Se intercambian los buffers
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
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Animacion 2D");
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("glewInit failed: %s", glewGetErrorString(err));
        exit(1);
    }
    tiempoActual = tiempoAnterior = 0;

    // rutinas de servicio para manejo de eventos
    glutReshapeFunc(reshape);
    glutIdleFunc(animar);
    glutKeyboardFunc(teclas);
    glutDisplayFunc(dibuja),
    glutMainLoop();
    return 0;
}