//Programa que implementa el cambio de color y formas en función del click.
//Programador: León Emiliano García Pérez (A00573074).
//Fecha de entrega: 16.11.2022.

//Forma de compilar:
//  g++ main.cpp -o main -lfreeglut -lglew32 -lopengl32 -lglu32

//Inclusión de librerías.
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>

//Ajuste a estandar.
using namespace std;

//Declaración de variables globales.
const double dosVecesPI = 6.2831853;
GLsizei dimensionVentanaX = 400;
GLsizei dimensionVentanaY = 400;
GLuint poligono;
float n = 5;

//Definición de clase.
class puntoEnPantalla {

    private:
        GLint x;
        GLint y;

    public:

        puntoEnPantalla() {
            x = 0;
            y = 0;
        }

        //Función que establece las coordenadas del punto, toma coordenadaX y toma coordenada en Y.
        void establecerCoordenadas(GLint coordenadaX, GLint coordenadaY) {
            x = coordenadaX;
            y = coordenadaY;
        }

        //Función que retorna el valor x del punto.
        GLint getX() const {
            return x;
        }

        //Función que retorna el valor y del punto.
        GLint getY() const {
            return y;
        }
};

//Función de inicialización.
static void init (void) {

    puntoEnPantalla poligonoVertex;
    puntoEnPantalla  centroDelCirculo;

    GLdouble theta;
    GLint k;

    centroDelCirculo.establecerCoordenadas(dimensionVentanaX / 2, dimensionVentanaY / 2);

    glClearColor(1.0, 1.0, 1.0, 0.0);

    poligono = glGenLists(1);

    glNewList(poligono, GL_COMPILE);

    srand((unsigned int)time(NULL));

    float a = 1.0;

    float flotante1 = (float(rand()) / float((RAND_MAX)) * a * 1.0);
    float flotante2 = (float(rand()) / float((RAND_MAX)) * a * 1.0);
    float flotante3 = (float(rand()) / float((RAND_MAX)) * a * 1.0);

    glColor3f(flotante1, flotante2, flotante3);
    glBegin(GL_POLYGON);

    for (k = 0; k < n; k++) {
        theta = dosVecesPI * k / n;
        poligonoVertex.establecerCoordenadas(centroDelCirculo.getX() + 150 * cos(theta), centroDelCirculo.getY() + 150 * sin(theta));
        glVertex2i(poligonoVertex.getX(), poligonoVertex.getY());
    }
    glEnd();
    glEndList();
}

//Función que forma el polígono.
void formarPoligono(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glCallList(poligono);
    glFlush();
}

//Función que redimensionana una ventana.
void redimensionar(int nuevoAncho, int nuevoAlto)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)nuevoAncho, 0.0, (GLdouble)nuevoAlto);
    glClear(GL_COLOR_BUFFER_BIT);

}

//Función que plotea un punto.
void ponerPunto(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

//Función que toma el punto en función del Mouse.
void puntoDelMouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
        if (n + 1 == 13) {
            n = 5;
        }
        else {
            n++;
        }
    }

    init();
    glutDisplayFunc(formarPoligono);
    glFlush();
}

//Función main de ejecución.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(dimensionVentanaX, dimensionVentanaY);
    glutCreateWindow("Reshape-Function & Display-List Example");
    init();
    glutDisplayFunc(formarPoligono);
    glutReshapeFunc(redimensionar);
    glutMouseFunc(puntoDelMouse);
    glutMainLoop();
    return 0;
}
