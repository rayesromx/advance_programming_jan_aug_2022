
#include <iostream>
using namespace std;


void ejecutar_DeclaracionInicializacionEIndireccionDePunteros();
void ejecutar_Punteroapunteros();
void ejecutar_PunterosNULL();
void ejecutar_PunterosVoid();
void ejecutar_PunterosyArreglos();
void ejecutar_AritmeticaDepunteros();
void ejecutar_PunterosComoArgumentosDeFunciones();
void ejecutar_PunterosDeEstructuras();

void sumar(int sumaTotalParam, int xParam, int yParam);
void sumar(int* sumaTotalPtrParam, int xParam, int yParam);

int main()
{
    ejecutar_DeclaracionInicializacionEIndireccionDePunteros();
    //ejecutar_PunterosNULL();
    //ejecutar_PunterosVoid();
    //ejecutar_Punteroapunteros();
    //ejecutar_PunterosyArreglos();
    //ejecutar_AritmeticaDepunteros();
    //ejecutar_PunterosComoArgumentosDeFunciones();
    //ejecutar_PunterosDeEstructuras();
}

void ejecutar_Punteroapunteros()
{
    int valor_e = 100;
    int* ptr1 = &valor_e;
    int** ptr2 = &ptr1;

    cout << "ptr1: " << ptr1 << endl;
    cout << "&ptr1: " << &ptr1 << endl;
    cout << "*ptr1: " << *ptr1 << endl;
    cout << "ptr2: " << ptr2 << endl;
    cout << "&ptr2: " << &ptr2 << endl;
    cout << "*ptr2: " << *ptr2 << endl;
    cout << "**ptr2: " << **ptr2 << endl;
}

void ejecutar_DeclaracionInicializacionEIndireccionDePunteros()
{

   
    int n = 75;
    int* p = &n;

    cout << " n  = " << n << endl;
    cout << " &n = " << &n << endl;
    cout << " p  = " << p << endl;
    cout << " &p = " << &p << endl;
    cout << " *p = " << *p << endl;

}

void ejecutar_PunterosNULL()
{
   
    float* f;
    f = NULL;
    //float pi = 3.141592;
    //f = &pi;

    if (f == NULL)
        cout << "f es igual a NULL" << endl;

    if (f)//if(f != NULL)
        cout << "f es diferente a NULL" << endl;

}

void ejecutar_PunterosVoid()
{
   
    void* pointer = NULL;
    int n = 7;
    float pi = 3.141592;

    pointer = &n;//puntero tipo void apunta a una direccion de un entero
    cout << " &pointer = " << pointer << endl;
    pointer = &pi;//puntero tipo void apunta a una direccion de un flotante
    cout << " &pointer = " << pointer << endl;

    // explicit cast, casteo explicito
    float* ptrToVoid = (float*)pointer;
    cout << *ptrToVoid;
    //casting
}

void ejecutar_PunterosyArreglos()
{
   

    short numbers[/*10*/] = { 2,4,6,8,10, 12, 14, 16, 18, 20 };

    cout << "Impresion de elementos del arreglo a traves de corchetes" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << numbers[i] << endl;
    }
    //el nombre de un arreglo es un puntero a la direccion de memoria 
    //del primer elemento de ese arreglo
    cout << "Impresion de elementos del arreglo a traves de punteros" << endl;
    cout << *numbers << endl; // 2
    cout << numbers << endl; // &numbers[0]
    cout << numbers + 1 << endl; //&numbers[1]
    cout << *(numbers + 1) << endl; //4
    cout << *(numbers + 0) << endl; //2
    cout << *(numbers + 9) << endl; //20
    cout << *(numbers + 9) + 5 << endl; //25
    cout << *(numbers + 10) << endl; //en el mejor de los casos imprimer basura
    cout << *(numbers - 1) << endl; //en el peor truena la app


   //int numbers[/*10*/] = {2,4,6,8,10, 12, 14, 16, 18, 20};
    for (int i = 0; i < 10; i++)
    {
        cout << "iteracion " << i + 1 << " = " << numbers[i] << endl;
        cout << "iteracion " << i + 1 << " = " << *(numbers + i) << endl;
        cout << "iteracion " << i + 1 << " = " << (numbers + i) << endl;
        cout << "iteracion " << i + 1 << " = " << *numbers + i << endl;
    }
}

void ejecutar_AritmeticaDepunteros()
{
   
    char mensaje2[] = "Pumteros???...No Puedem Ser! :C";
    /*  for (char* ptr = &mensaje2[0]; *ptr != 0; ptr = ptr + 1)
    {
        printf("%c", *ptr);
        ///cout << *ptr;
    }*/

    char mensaje1[] = "Pumteros???...No Puedem Ser! :C ";
    char* puntero1 = &mensaje1[0];
    //char* puntero1 = mensaje1;
    //char* puntero2 = mensaje;

    cout << mensaje1 << endl;
    *puntero1 = 'W';
    cout << mensaje1 << endl;
    puntero1 = puntero1 + 1;
    *puntero1 = 'U';

    cout << mensaje1 << endl;
    puntero1 += 1;
    *puntero1 = 'M';

    cout << mensaje1 << endl;
    puntero1++;
    *puntero1 = '+';

    cout << mensaje1 << endl;
    *(puntero1 + 1) = '3';

    cout << mensaje1 << endl;
    *(puntero1 + 2) = 'R';

    cout << mensaje1 << endl;

    puntero1 += 4;
    *(++puntero1) = '!';
    cout << mensaje1 << endl;
    *(++puntero1) = '@';
    cout << mensaje1 << endl;

    cout << endl;

    cout << endl;

    //como imprimir el mensaje al reves????

    cout << endl;

    for (char* ptr = mensaje2; *ptr != 0; ptr++) //char* ptr = mensaje ==>> char* ptr = &mensaje[0]
    {
        if (isalpha(*ptr))
        {
            if (*ptr >= 'a' && *ptr <= 'z')
                *ptr -= 32;
            else
                if (*ptr >= 'A' && *ptr <= 'Z')
                    *ptr += 32;
        }
        //"Pumteros???...No Puedem Ser!D:< ";
        if (*ptr == ':')
        {
            *(ptr - 1) = 'D';
            *(ptr + 1) = '<';
        }
        printf("%c", *ptr);
    }

    cout << endl;

    char* ptr = mensaje2;
    (*ptr) -= 32;
    cout << mensaje2 << endl;
    *(ptr + 2) = 'n';
    cout << mensaje2 << endl;


    //como imprimir el mensaje al reves????
}

void ejecutar_PunterosComoArgumentosDeFunciones()
{
    int suma = 100;
    cout << "suma = " << suma << endl;
    sumar(suma, 7, 8);
    cout << "suma = " << suma << endl;
    sumar(&suma, 7, 8);
    cout << "suma = " << suma << endl;

    int suma2 = 11;
    int* ptrSuma = &suma2;
    cout << "suma2 = " << suma2 << endl;
    sumar(suma2, 7, 8);
    cout << "suma2 = " << suma2 << endl;
    sumar(ptrSuma, 7, 8);
    cout << "suma2 = " << suma2 << endl;
}
//paso por copia o paso por valor
void sumar(int sumaTotal, int x, int y)
{
    sumaTotal += x + y;
    cout << "\tsumaTotal = " << sumaTotal << endl;
}
//paso por referencia
void sumar(int* sumaTotalPtr, int x, int y)
{
    *sumaTotalPtr = *sumaTotalPtr + x + y;
    cout << "sumaTotalPtr = " << *sumaTotalPtr << endl;
}


void ejecutar_PunterosDeEstructuras()
{

    struct persona {
        char nombre[10];
        int edad;
        float altura;
        float peso;
    };

    persona empleado = { "Raymundo", 30, 1.81, 81.5 };
    persona* ptr = &empleado;

    cout << "Acceso a estructura tipica" << endl;
    cout << "nombre = " << empleado.nombre << endl;
    cout << "edad = " << empleado.edad << endl;
    cout << "altura = " << empleado.altura << endl;
    cout << "peso = " << empleado.peso << endl;

    cout << "Acceso a estructura a traves de un puntero" << endl;
    cout << "nombre = " << ptr->nombre << endl;
    cout << "edad = " << ptr->edad << endl;
    cout << "altura = " << ptr->altura << endl;
    cout << "peso = " << ptr->peso << endl;

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
/*







Heap
Stack

*/