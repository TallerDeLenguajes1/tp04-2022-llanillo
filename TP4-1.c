/*
 *  PUNTEROS DOBLES ARITMETICA
 *  arr[i][j] == *(arr[i] + j) == *(*(arr + i) + j)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; // Cualquiera
    int Duracion; // entre 10 – 100
} Tarea;

void IngresarTarea(Tarea** Tareas, int Indice);
void MostrarTareas(Tarea** Tareas, int CantidadTareas);
void RealizarTareas(Tarea** Tareas, Tarea** TareasHechas, int CantidadTareas);

int main()
{
    int CantidadTareas;
    Tarea** Tareas;
    Tarea** TareasHechas;

    srand(time(NULL));

    printf("Ingrese la cantidad de tareas\n");
    scanf("%d", &CantidadTareas);
    getchar();

    Tareas = (Tarea**) malloc(CantidadTareas * sizeof(Tarea*));
    TareasHechas = (Tarea**) malloc(CantidadTareas * sizeof(Tarea));

    for(unsigned int i = 0; i < CantidadTareas; i++){
        Tareas[i] = (Tarea*) malloc(sizeof(Tarea));
        IngresarTarea(Tareas, i);
    }

    RealizarTareas(Tareas, TareasHechas, CantidadTareas);

    printf("--------- Tareas Pendientes ---------\n");
    MostrarTareas(Tareas, CantidadTareas);

    printf("--------- Tareas Hechas ---------\n");
    MostrarTareas(TareasHechas, CantidadTareas);

    return 0;
}

void IngresarTarea(Tarea** Tareas, int Indice){
    char *Buffer = (char *) malloc(100 * sizeof(char));

    (*(Tareas + Indice))->Duracion = rand() % 101 + 10;
    (*(Tareas + Indice))->TareaID = Indice;

    printf("Ingrese la decripción\n");
    fgets(Buffer, 100, stdin);

    (*(Tareas + Indice))->Descripcion = (char*) malloc((strlen(Buffer) + 1) * sizeof(char));
    strcpy((*(Tareas + Indice))->Descripcion, Buffer);
}

void MostrarTareas(Tarea** Tareas, int CantidadTareas){

    for(unsigned int i = 0; i < CantidadTareas; i++){
        if(Tareas[i] != NULL){
            printf("ID: %d\n", (*(Tareas + i))->TareaID);
            printf("Duracion: %d\n", (*(Tareas + i))->Duracion);
            printf("Descripción: %s\n", (*(Tareas + i))->Descripcion);
        }
    }
}

void RealizarTareas(Tarea** Tareas, Tarea** TareasHechas, int CantidadTareas){

    int temporal;

    for(unsigned int i = 0; i < CantidadTareas; i++){
        printf("--- Tarea %d ---\n", i);
        printf("¿Esta hecha la tarea? (1 - Si, 0 - No)\n");
        scanf(" %i", &temporal);

        if(temporal != 0){
            (*(TareasHechas + i)) = (*(Tareas + i));
            (*(Tareas + i)) = NULL;
        }
        else{
            (*(TareasHechas + i)) = NULL;
        }
    }
}