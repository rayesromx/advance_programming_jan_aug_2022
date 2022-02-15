// 04_linked_lists.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

struct Grupo {
    char nombre[10];
    int numero_salon;
};

struct Alumno {
    //Datos
    int matricula;
    char nombre[20];
    //Grupo grupos[8];
    //Enlace/link
    Alumno* siguienteNodo;
};

Alumno* origenLista;

Alumno* crearNuevoAlumno(int matricula, const char nombre[])
{
    Alumno* nuevoAlumno = new Alumno;
    nuevoAlumno->matricula = matricula;//123456;
    strcpy_s(nuevoAlumno->nombre, nombre);
    nuevoAlumno->siguienteNodo = NULL;
    return nuevoAlumno;
}

void insertarNodoAlFinalDeLaLista(Alumno* nuevoAlumno)
{
    if (origenLista == NULL)//PARA SABER QUE LA LISTA ESTA VACIA
    {
        origenLista = nuevoAlumno;
    }
    else
    {
        Alumno* nodoTemporal = origenLista;
        //recorremos al final de la lista
        while (nodoTemporal->siguienteNodo != NULL)
            nodoTemporal = nodoTemporal->siguienteNodo;
        //en la cola de la lista asignamos el nuevo nodo
        nodoTemporal->siguienteNodo = nuevoAlumno;
    }
}

int main()
{
    origenLista = NULL;

    //CREANDO UN NUEVO NODO
    Alumno* nuevoAlumno = crearNuevoAlumno(123456, "Ray");
    insertarNodoAlFinalDeLaLista(nuevoAlumno);

    Alumno* nuevoAlumno2 = crearNuevoAlumno(7982, "Rey");
    insertarNodoAlFinalDeLaLista(nuevoAlumno2);

    Alumno* nuevoAlumno3 = crearNuevoAlumno(87978, "Roy");
    insertarNodoAlFinalDeLaLista(nuevoAlumno3);

    Alumno* nuevoAlumno4 = crearNuevoAlumno(1425367, "Ryu");
    insertarNodoAlFinalDeLaLista(nuevoAlumno4);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
