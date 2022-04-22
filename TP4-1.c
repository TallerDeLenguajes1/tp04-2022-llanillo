/*
 *  PUNTEROS DOBLES ARITMETICA
 *  arr[i][j] == *(arr[i] + j) == *(*(arr + i) + j)
 *  arr[i] == (*(arr + i))
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea {
    int TareaID;
    char *Descripcion;
    int Duracion;
} Tarea;

void IngresarTarea(Tarea** Tareas, int Indice);
void MostrarTareas(Tarea** Tareas, int CantidadTareas);
void RealizarTareas(Tarea** Tareas, Tarea** TareasHechas, int CantidadTareas);
void BusquedaPorPalabra(Tarea** Tareas, int CantidadTareas, char* PalabraClave);
void BusquedaPorId(Tarea** Tareas, int CantidadTareas, int ID);
void MostrarTarea(Tarea* Tarea);

int main()
{
    int CantidadTareas;
    Tarea** Tareas;
    Tarea** TareasHechas;
    
    srand(time(NULL)); // Línea necesaria para randomizar dígitos

    printf("Ingrese la cantidad de tareas\n");
    scanf("%d", &CantidadTareas);
    getchar(); // IMPORTANTE: Evita que tome el ENTER en las siguientes partes que se pidan más entrada

    Tareas = (Tarea**) malloc(CantidadTareas * sizeof(Tarea*));
    TareasHechas = (Tarea**) malloc(CantidadTareas * sizeof(Tarea));

    for(unsigned int i = 0; i < CantidadTareas; i++){
        Tareas[i] = (Tarea*) malloc(sizeof(Tarea)); // Equivalente: (*(Tareas + i)) = (Tarea*) malloc...
        IngresarTarea(Tareas, i);
    }

    RealizarTareas(Tareas, TareasHechas, CantidadTareas);

    printf("--------- Tareas Pendientes ---------\n");
    MostrarTareas(Tareas, CantidadTareas);

    printf("\n--------- Tareas Hechas ---------\n");
    MostrarTareas(TareasHechas, CantidadTareas);

    printf("\n--------- Tareas Buscadas ---------\n");
    BusquedaPorPalabra(Tareas, CantidadTareas, "perrito");
    BusquedaPorId(Tareas, CantidadTareas, 1);

    for(unsigned int i = 0; i < CantidadTareas; i++){
//        free((*(Tareas + i))->Descripcion);  NO ES NECESARIO, pues ese espacio de memoria no se creó dinámicamente con malloc
        free((*(Tareas + i)));
        (*(Tareas + i))->Descripcion = NULL;
        (*(Tareas + i)) = NULL;
//        free((*(TareasHechas + i))->Descripcion);  NO ES NECESARIO, pues ese espacio de memoria no se creó dinámicamente con malloc
        free((*(TareasHechas + i)));
        (*(TareasHechas + i))->Descripcion = NULL;
        (*(TareasHechas + i)) = NULL;
    }

    free(Tareas);
    free(TareasHechas);

    return 0;
}

void IngresarTarea(Tarea** Tareas, int Indice){
    char *Buffer = (char *) malloc(100 * sizeof(char));

    (*(Tareas + Indice))->Duracion = rand() % 101 + 10;
    (*(Tareas + Indice))->TareaID = Indice;

    printf("Ingrese la decripcion\n");
    fgets(Buffer, 100, stdin);

    (*(Tareas + Indice))->Descripcion = (char*) malloc((strlen(Buffer) + 1) * sizeof(char));
    strcpy((*(Tareas + Indice))->Descripcion, Buffer);

    free(Buffer); // Liberar cualquier memoria alocada dinámicante, incluso en funciones, pues está se guarda en el HEAP
}

void MostrarTareas(Tarea** Tareas, int CantidadTareas){

    for(unsigned int i = 0; i < CantidadTareas; i++){
        if(Tareas[i]){
            printf("ID: %d\n", (*(Tareas + i))->TareaID);
            printf("Duracion: %d\n", (*(Tareas + i))->Duracion);
            printf("Descripcion: %s\n", (*(Tareas + i))->Descripcion);
        }
    }
}

void MostrarTarea(Tarea* Tarea){

    if(Tarea){
        printf("ID: %d\n", Tarea->TareaID);
        printf("Duracion: %d\n", Tarea->Duracion);
        printf("Descripcion: %s\n", Tarea->Descripcion);
    }
    else{
        printf("Tarea vacia\n");
    }
}

void RealizarTareas(Tarea** Tareas, Tarea** TareasHechas, int CantidadTareas){

    int temporal;

    for(unsigned int i = 0; i < CantidadTareas; i++){
        printf("--- Tarea %d ---\n", i);
        printf("¿Esta hecha la tarea? (1 - Si, 0 - No)\n");
        scanf(" %i", &temporal);

        if(temporal){
            (*(TareasHechas + i)) = (*(Tareas + i));
            (*(Tareas + i)) = NULL;
        }
        else{
            (*(TareasHechas + i)) = NULL;
        }
    }
}

void BusquedaPorPalabra(Tarea** Tareas, int CantidadTareas, char* PalabraClave){
    
    for(unsigned int i = 0; i < CantidadTareas; i++){
        if((*(Tareas + i)) && strstr((*(Tareas + i))->Descripcion, PalabraClave)){
                MostrarTarea((*(Tareas + i)));
        }
    }

    return NULL;
}

void BusquedaPorId(Tarea** Tareas, int CantidadTareas, int ID){

    for(unsigned int i = 0; i < CantidadTareas; i++){
        if((*(Tareas + i)) && (*(Tareas + i))->TareaID == ID){
                MostrarTarea((*(Tareas + i)));
        }
    }    
}