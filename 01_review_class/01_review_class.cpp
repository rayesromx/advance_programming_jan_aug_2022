// 01_review_class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<string>
	//input output stream

using namespace std;
const float PI = 3.1415921234567890;
int valores[100];

float calificaciones[] = { 90.5, 69.5, 100 };

float modelo3D[100][3][3];

struct Punto {
	float X;
	float Y;
	float Z;
};

struct Persona {
	short mes_de_nacimiento;
	short anio_de_nacimiento;
	short dia_de_nacimiento;
	char nombre[100];
	float estatura;
};

struct Alumno {
	int matricula;
	Persona datos_personales;
	float calificaciones_de_entregas_de_Avances[3];

	void imprimirInfoDeAlumno()
	{
		float promedio = calificaciones_de_entregas_de_Avances[0]
			+ calificaciones_de_entregas_de_Avances[1]
			+ calificaciones_de_entregas_de_Avances[2];
		promedio /= 3;

		cout << endl << "Alumno " << datos_personales.nombre << " con matricula "
			<< matricula << " obtuvo un promedio de" << promedio;
	}

	void inicializarDatos(char nombreParam[100], int matriculaParam)
	{
		strcpy_s(datos_personales.nombre, nombreParam);
		//datos_personales.nombre = "Ray Espinosa";
		matricula = matriculaParam;
		datos_personales.anio_de_nacimiento = 1995;
		datos_personales.estatura = 1.60;
		calificaciones_de_entregas_de_Avances[0] = 85;
		calificaciones_de_entregas_de_Avances[1] = 70;
		calificaciones_de_entregas_de_Avances[2] = 70;
	}
};


void imprimirMensaje(int contador);
int sumar(int x, int y);



void main()
{

	int valor1 = 10;
	imprimirMensaje(valor1);

	cout << valor1 << endl;

	Punto punto1;
	punto1.X = 10;
	punto1.Y = 20;
	punto1.Z = 30;

	Alumno alumno1, alumno2, alumno3;

	Alumno alumnos[100];

	char n1[] = "Hugo";
	char n2[] = "Paco";
	char n3[] = "Luis";


	alumnos[1].inicializarDatos(n1, 123);
	alumnos[2].inicializarDatos(n2, 456);
	alumnos[3].inicializarDatos(n3, 789);

	for (int i = 0; i < 100; i++)
	{
		alumnos[i].imprimirInfoDeAlumno();
	}
}

void imprimirMensaje(int contador)
{
	contador *= 100;
	cout << contador << endl;
}

/// <summary>
/// esta funcion suma dos parametros enteros
/// </summary>
/// <param name="x">Operando 1</param>
/// <param name="y">Operando 2</param>
/// <returns>Retorna la suma de la x mas la y</returns>
int sumar(int x, int y)
{
	return x + y;
}