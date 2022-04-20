#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; // Cualquiera
    int Duracion; // entre 10 – 100
} Tarea;

void IngresarTarea(Tarea** Tareas, int ID);
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

    printf("--- Todas las tareas ---\n");
    MostrarTareas(Tareas, CantidadTareas);

    printf("--- Tareas Hechas ---\n");
    MostrarTareas(TareasHechas, CantidadTareas);

    return 0;
}

void IngresarTarea(Tarea** Tareas, int ID){
    char *Buffer = (char *) malloc(100 * sizeof(char));

    (*Tareas + ID)->Duracion = rand() % 101 + 10;
    (*Tareas + ID)->TareaID = ID;

    printf("Ingrese la decripción\n");
    fgets(Buffer, 100, stdin);

    (*Tareas + ID)->Descripcion = (char*) malloc((strlen(Buffer) + 1) * sizeof(char));
    strcpy((*Tareas + ID)->Descripcion, Buffer);
}

void MostrarTareas(Tarea** Tareas, int CantidadTareas){

    for(unsigned int i = 0; i < CantidadTareas; i++){
        printf("--- Tareas %d ---\n", i);
        printf("ID: %d\n", (*Tareas)->TareaID);
        printf("Duracion: %d\n", (*Tareas)->Duracion);
        printf("Descripción: %s\n", (*Tareas)->Descripcion);
        (*Tareas)++;
    }
}

void RealizarTareas(Tarea** Tareas, Tarea** TareasHechas, int CantidadTareas){

    int temporal;

    for(unsigned int i = 0; i < CantidadTareas; i++){
        printf("--- Tarea %d ---\n", i);
        printf("¿Esta hecha la tarea? (1 - Si, 0 - No)\n");
        scanf(" %i", &temporal);

        if(temporal != 0){
            TareasHechas[i] = (Tarea*) malloc(sizeof(Tarea));
            *(TareasHechas + i) = *(Tareas + i);
        }
        else{
            *(TareasHechas + i) = NULL;
        }
    }
}