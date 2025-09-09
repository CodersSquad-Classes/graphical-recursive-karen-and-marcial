#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

ofstream archivoSalida;

//aqui la funcion va a generar los segmentos de la curva Koch entre el punto 
void dibujarCurva(double inicioX, double inicioY, double finX, double finY, int nivel) {
    if (nivel == 0) {//caso base de la recursiòn, el nivel es 0 entonces ya no subdividimos mas 
        // Caso base: línea directa
        archivoSalida << "(" << (int)inicioX << "," << (int)inicioY << ")"
                      << "(" << (int)finX << "," << (int)finY << ")" << endl;
        return;
    }//aqui esto escribe el archivo en .txt por medio de una salida de dos puntos seguidos. . Tambien convierte las coordenadas double a int 

    //Comenzamos a calcular las divisiones 
    double deltaX = (finX - inicioX) / 3.0;
    double deltaY = (finY - inicioY) / 3.0;
//lo dividimos entre tres para calcular el tercio del vector desde el inicio hasta el fin. Para que sean 3 partes iguales. 
    double puntoA_X = inicioX + deltaX;
    double puntoA_Y = inicioY + deltaY;
//coordenadas del punto A que es 1/3
    double puntoB_X = inicioX + 2 * deltaX;
    double puntoB_Y = inicioY + 2 * deltaY;
//Coordenadas del punto B que es 2/3
    // Punto del triángulo
 
    double giroX = (puntoB_X - puntoA_X) * cos(M_PI / 3) - (puntoB_Y - puntoA_Y) * sin(M_PI / 3);
    double giroY = (puntoB_X - puntoA_X) * sin(M_PI / 3) + (puntoB_Y - puntoA_Y) * cos(M_PI / 3);
//Aqui se rota el vector que va de A a B por /pi/3 radianes) 
    double picoX = puntoA_X + giroX;
    double picoY = puntoA_Y + giroY;

    // Recursión en las 4 partes
    dibujarCurva(inicioX, inicioY, puntoA_X, puntoA_Y, nivel - 1);
    dibujarCurva(puntoA_X, puntoA_Y, picoX, picoY, nivel - 1);
    dibujarCurva(picoX, picoY, puntoB_X, puntoB_Y, nivel - 1);
    dibujarCurva(puntoB_X, puntoB_Y, finX, finY, nivel - 1);
}
//Aqui se separa el segmento en 4 partes y se van llamando recursivamente con nivel-1.Esto es la regla de construccion del fractal de Koch. 
//aqui ya tambien se cerro la funcion de dibujar CUrva
int main(int argc, char* argv[]) {//inicio de otro main; argc. argc es el numero de argumentos y argv el arreglo 
    if (argc != 6) {//Aqui comprobamos que el programa recibe 5 argumentos por eso argc !=6
        cerr << "Forma de uso: " << argv[0] << " <x1> <y1> <x2> <y2> <nivel>" << endl;
        return 1;
    }

    //Aqui lee los datos de entrada
    double inicioX = atof(argv[1]);//aqui vamos a convertir los argumentos de double a int usando atof. y atoi. 
    double inicioY = atof(argv[2]);
    double finX    = atof(argv[3]);
    double finY    = atof(argv[4]);
    int nivel      = atoi(argv[5]);
//argv 5 esta en atoi y no en atof porque es ya el nivel rcurisvo. Lo malo es que atof y atoi no detectan errorres. 
    // Validar dentro del área de dibujo
    if (inicioX < 0 || inicioX > 1024 || inicioY < 0 || inicioY > 1024 ||//Aqui esto fue para validar que las coordenadas estan dentro de un area valida 
        finX < 0 || finX > 1024 || finY < 0 || finY > 1024) {
        cerr << "Los puntos deben estar dentro del área 1024x1024." << endl;
        return 1;
    }

    // Creamos un archivo llamado resultado.txt
    archivoSalida.open("resultado.txt");
    if (!archivoSalida) {
        cerr << "No se pudo crear resultado.txt" << endl; //aqui nos avisa si paso un error 
        return 1;
    }

    // dibuja
    dibujarCurva(inicioX, inicioY, finX, finY, nivel);

    archivoSalida.close();
    cout << "Archivo resultado.txt creado con éxito." << endl;//todo salio bien si se imprime esto. 
    return 0;
    }