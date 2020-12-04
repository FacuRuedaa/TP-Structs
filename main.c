#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <conio.h>
#include <string.h>

#define arAlumno "alumnos.dat"

#define ESC 27

typedef struct {
    int matricula;
    char nombre[30];
    char genero; //m, f, o
} stAlumno;

const int DIM=20;

void menu ();
stAlumno cargaUnAlumno ();
int cargaAlumno (stAlumno al[], int dimension);
void mostarUnAlumno (stAlumno al);
void muestraAlumnos (stAlumno a[], int validos);
int buscaAlumno (stAlumno a[], int validos, int matricula);
void imprimeAlumnoBuscado (stAlumno a[], int val, int matr);
int posicionMenor (stAlumno a[], int validos, int c);
void ordenaPorSeleccion (stAlumno a[], int validos);
void buscaPorGenero (stAlumno a[], int validos, char sexo);
int insertarAlumno (stAlumno a[], int validos, stAlumno b);
int cuentaAlumnosPorGenero (stAlumno a[], int validos, char genero);
void guardaUnAlumno (stAlumno a);
void cargaAlumnoEnArchivos ();
void muestraArchAlumnos ();
int cuentaRegistros ();
void cargarAlumnoAlFinal ();
void pasarPilaLegajo (Pila *p);



int main()
{
    stAlumno alumno;
    stAlumno alumnos[DIM];
    int cantidad, ejercicio, option;
    char masculino = 'm';
    char femenino = 'f';
    alumno.matricula = 154;
    strcpy(alumno.nombre, "Perez");
    alumno.genero = 'm';
    Pila dada;
    inicpila(&dada);

    do {
        system("cls");
        menu();
        scanf("%d", &ejercicio);
        switch (ejercicio) {
            case 1:
                cantidad = cargaAlumno(alumnos, DIM);
                break;
            case 2:
                muestraAlumnos(alumnos, cantidad);
                break;
            case 3:
                imprimeAlumnoBuscado(alumnos, cantidad, 150);
                break;
            case 4:
                printf("\nLos alumnos ordenados segun la matricula\n");
                ordenaPorSeleccion(alumnos, cantidad);
                muestraAlumnos(alumnos, cantidad);
                break;
            case 5:
                printf("\nLos alumnos masculinos son: \n");
                buscaPorGenero(alumnos, cantidad, masculino);
                break;
            case 6:
                printf("\nLas alumnas son: \n");
                buscaPorGenero(alumnos, cantidad, femenino);
                break;
            case 7:
                cantidad = insertarAlumno(alumnos, cantidad, alumno);
                muestraAlumnos(alumnos, cantidad);
                break;
            case 8:
                printf("\nLa cantidad de alumnos son: %d\n", cuentaAlumnosPorGenero(alumnos, cantidad, masculino));
                printf("\nLa cantidad de alumnas son: %d\n", cuentaAlumnosPorGenero(alumnos, cantidad, femenino));
                break;
            case 9:
                cargaAlumnoEnArchivos();
                break;
            case 10:
                muestraArchAlumnos();
                break;
            case 11:
                printf("\nLa cantidad de registros en el archivo es de: %d\n", cuentaRegistros());
                break;
            case 12:
                cargarAlumnoAlFinal();
                break;
            case 13:
                pasarPilaLegajo(&dada);
                mostrar(&dada);
                break;
            default:
                printf("\nOpcion incorrecta\n");
            }
        printf("\nDesea continuar? Presione ESC para salir...");
        option=getch();
    }   while(option!=ESC);

    return 0;
}

void menu ()
{
    printf("\n\t\t\tTRABAJO PRACTICO ESTRUCTURAS\n");
    printf("\n1) Cargar un arreglo de alumnos\n");
    printf("2) Mostrar el arreglo de alumnos\n");
    printf("3) Buscar el alumno segun su matricula\n");
    printf("4) Ordenar el arreglo de alumnos segun su matricula\n");
    printf("5) Imprimir en pantalla los alumnos\n");
    printf("6) Imprimir en pantalla las alumnas\n");
    printf("7) Insertar un alumno\n");
    printf("8) Cantidad de alumnos y alumnas\n");
    printf("9) Cargar un alumno en el archivo\n");
    printf("10) Mostrar el archivo\n");
    printf("11) Cuenta registros de archivo\n");
    printf("12) Cargar un alumno al final del archivo\n");
    printf("13) Pasar a pila los nombres de los legajos mayores a 150\n");

}

/// EJERCICIO 1. CARGAR ARREGLO DE ALUMNOS

stAlumno cargaUnAlumno ()
{
    stAlumno a;

    printf("\nIngrese la matricula del alumno:\n");
    scanf("%d", &a.matricula);

    printf("\nIngrese el nombre del alumno: \n");
    fflush(stdin);
    gets(a.nombre);

    printf("\nIngrese el genero del alumno: (m o f)\n");
    fflush(stdin);
    scanf("%c", &a.genero);

    while (a.genero!='m' && a.genero!='f'){
        printf("\nSexo erroneo, ingrese nuevamente\n");
        fflush(stdin);
        scanf("%c", &a.genero);
    }
    return a;
}

int cargaAlumno (stAlumno al[], int dimension)
{
    int i=0;
    char opcion;

    while (i<dimension && opcion!=ESC){
        al[i] = cargaUnAlumno();
        i++;
        printf("\nDesea cargar otro alumno? Presione ESC para salir..\n");
        opcion = getch();
        system("cls");
    }
    return i;
}

/// EJERCICIO 2.

void muestraAlumnos (stAlumno a[], int validos)
{
    for(int i=0; i<validos; i++){
        mostarUnAlumno(a[i]);
    }
}


void mostarUnAlumno (stAlumno al)
{
    printf("\n-------------------------------------\n");
    printf("\nMatricula:......:%d\n", al.matricula);
    printf("Nombre:.........:%s\n", al.nombre);
    printf("Genero:.........:%c\n", al.genero);
}

/// EJERCICIO 3.

int buscaAlumno (stAlumno a[], int validos, int matricula)
{
    int flag=0;
    int i=0;

    while (i<validos && flag == 0) {
        if (matricula == a[i].matricula) {
            flag = 1;
        }
        i++;
    }
    return flag;
}

void imprimeAlumnoBuscado (stAlumno a[], int val, int matr)
{
    int bandera;
    int i=0;
    int pos = -1;

    bandera = buscaAlumno(a, val, matr);

    if (bandera == 1) {
        while (i<val && pos == -1){
            if (a[i].matricula == matr){
                pos = i;
            }
            i++;
        }
        printf("\nEl alumno buscado es:\n");
        mostarUnAlumno(a[pos]);
    } else {
        printf("\nEl alumno no existe\n");
    }
}

/// EJERCICIO 4. Ordenar por seleccion segun matricula.

int posicionMenor (stAlumno a[], int validos, int c)
{
    int i=c+1;
    int posMenor=c;
    stAlumno menor = a[c];

    while (i<validos){
        if (a[i].matricula < menor.matricula){
            menor= a[i];
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}

void ordenaPorSeleccion (stAlumno a[], int validos)
{
    int i=0;
    int pos;
    stAlumno aux;

    while (i<validos){
        pos = posicionMenor(a, validos, i);
        aux = a[i];
        a[i] = a[pos];
        a[pos] = aux;
        i++;
    }
}

/// EJERCICIO 5. Imprimir por pantalla los nombres segun el genero

void buscaPorGenero (stAlumno a[], int validos, char sexo)
{
    int i=0;

    while (i<validos){
        if (sexo == a[i].genero){
            mostarUnAlumno(a[i]);
        }
        i++;
    }
}

/// EJERCICIO 6. Insertar un alumno por matricula.

int insertarAlumno (stAlumno a[], int validos, stAlumno b)
{
    int i=validos-1;

    ordenaPorSeleccion(a, validos);

    while (i>=0 && a[i].matricula > b.matricula){
        a[i+1] = a[i];
        i--;
    }
    a[i] = b;

    return validos+1;
}

/// EJERCICIO 8. Funcion que cuente los alumnos de un genero y los retorne.

int cuentaAlumnosPorGenero (stAlumno a[], int validos, char genero)
{
    int i=0;
    int numero=0;

    while (i<validos) {
        if (a[i].genero == genero){
            numero++;
        }
        i++;
    }
    return numero;
}

void guardaUnAlumno (stAlumno a) /// Funcion que utlizo cuando cargo el alumno luego.
{
    FILE * pArchAlumno = fopen(arAlumno, "ab");
    if (pArchAlumno){
        fwrite(&a, sizeof(stAlumno), 1, pArchAlumno); /// como es un puntero void, necesita saber cuanto pesa el tipo de dato.
        fclose(pArchAlumno); /// lo cierro solo si se abrio.
    }
}

void cargaAlumnoEnArchivos ()
{
    char opcion;

    while (opcion!=ESC){
        printf("\n Carga de alumnos en archivo \n");
        guardaUnAlumno(cargaUnAlumno());
        printf("\nDesea cargar otro alumno? Presione ESC para salir..\n");
        opcion = getch();
        system("cls");
    }
}

void muestraArchAlumnos ()
{
    stAlumno a;

    FILE * pArchAlumno = fopen(arAlumno, "rb"); /// rb pone el cursor al principio para leer

    if (pArchAlumno){
        while (fread(&a, sizeof(stAlumno), 1, pArchAlumno) > 0){
           mostarUnAlumno(a);
        }
        fclose(pArchAlumno);
    }
}

int cuentaRegistros ()
{
    int i=0;
    stAlumno a;
    FILE * pArchAlumno = fopen(arAlumno, "rb");
    if (pArchAlumno)
    {
        while (fread(&a, sizeof(stAlumno), 1, pArchAlumno) > 0)
        {
            i++;
        }
        fclose(pArchAlumno);
    }
    return i;
}

void cargarAlumnoAlFinal ()
{
    stAlumno a = cargaUnAlumno();
    FILE * pArchAlumno = fopen(arAlumno, "ab");
    if (pArchAlumno){
        fwrite(&a, sizeof(stAlumno), 1, pArchAlumno);
        fclose(pArchAlumno);
    }
}

void pasarPilaLegajo (Pila *p)
{
    FILE * pArchAlumno = fopen(arAlumno, "rb");
    stAlumno a;
    if (pArchAlumno){
        while (fread(&a, sizeof(stAlumno), 1, pArchAlumno)>0) {
            if (a.matricula>149){
                apilar(p, a.matricula);
            }
        }
        fclose(pArchAlumno);
    }
}

/// EJERCICIO 8
