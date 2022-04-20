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

struct Nodo{
    Tarea T;
    struct Nodo* Siguiente;
};
typedef struct Nodo* Lista;

void IngresarTareas(Lista Tareas, int CantidadTareas);
void MostrarTareas(Tarea* Tareas, int CantidadTareas);
void RealizarTareas(Tarea* Tareas, Tarea** TareasHechas, int CantidadTareas);
Tarea* BusquedaPorPalabra(Tarea* Tareas, int CantidadTareas, char* PalabraClave);
Tarea* BusquedaPorId(Tarea* Tareas, int CantidadTareas, int ID);
void MostrarTarea(Tarea* Tarea);
int EsListaVacia(Lista* Tarea);

int main()
{
    int CantidadTareas;
    Lista Tareas = NULL;
    Lista TareasHechas = NULL;

    srand(time(NULL));

    printf("Ingrese la cantidad de tareas\n");
    scanf("%d", &CantidadTareas);
    getchar();

//    for(unsigned int i = 0; i < CantidadTareas; i++){
//        Tareas->Siguiente = (Tarea*) malloc(sizeof(Tarea));
//        IngresarTarea(Tareas, i);
//    }
    IngresarTareas(Tareas, CantidadTareas);

    RealizarTareas(Tareas, TareasHechas, CantidadTareas);

    printf("--------- Tareas Pendientes ---------\n");
    MostrarTareas(Tareas, CantidadTareas);

    printf("\n--------- Tareas Hechas ---------\n");
    MostrarTareas(TareasHechas, CantidadTareas);

    printf("\n--------- Tareas Buscada ---------\n");
    MostrarTarea(BusquedaPorPalabra(Tareas, CantidadTareas, "perrito"));
    MostrarTarea(BusquedaPorId(Tareas, CantidadTareas, 1));

    return 0;
}

void IngresarTareas(Lista Tareas, int CantidadTareas){

    for (unsigned int i = 0; i < CantidadTareas; i++){
        printf("Ingrese Tarea %d\n", i);

        char *Buffer = (char *) malloc(100 * sizeof(char));

        Tareas->T.Duracion = rand() % 101 + 10;
        Tareas->T.TareaID = i;

        printf("Ingrese la decripción\n");
        fgets(Buffer, 100, stdin);

        Tareas->T.Descripcion = (char*) malloc((strlen(Buffer) + 1) * sizeof(char));
        strcpy(Tareas->T.Descripcion, Buffer);

        Tareas->Siguiente = (Lista) malloc(sizeof(struct Nodo));
        Tareas = Tareas->Siguiente;
    }
}

void MostrarTareas(Tarea* Tareas, int CantidadTareas){

    for(unsigned int i = 0; i < CantidadTareas; i++){
        if(Tareas[i] != NULL){
            printf("ID: %d\n", (*(Tareas + i))->TareaID);
            printf("Duracion: %d\n", (*(Tareas + i))->Duracion);
            printf("Descripción: %s\n", (*(Tareas + i))->Descripcion);
        }
    }
}

void MostrarTarea(Tarea* Tarea){

    if(Tarea != NULL){
        printf("ID: %d\n", Tarea->TareaID);
        printf("Duracion: %d\n", Tarea->Duracion);
        printf("Descripción: %s\n", Tarea->Descripcion);
    }
    else{
        printf("Tarea vacia\n");
    }
}

void RealizarTareas(Lista Tareas, Lista TareasHechas, int CantidadTareas){

    int temporal;

    for(unsigned int i = 0; i < CantidadTareas; i++){
        printf("--- Tarea %d ---\n", i);
        printf("¿Esta hecha la tarea? (1 - Si, 0 - No)\n");
        scanf(" %i", &temporal);

        if(temporal){
            TareasHechas->T = Tareas->T;
            Tareas->T = NULL;
        }
        else{
            TareasHechas->T = NULL;
        }
    }
}

Tarea* BusquedaPorPalabra(Tarea* Tareas, int CantidadTareas, char* PalabraClave){

    for(unsigned int i = 0; i < CantidadTareas; i++){
        if(strstr((*(Tareas + i))->Descripcion, PalabraClave) != NULL){
            return (*(Tareas + i));
        }
    }

    return NULL;
}

Tarea* BusquedaPorId(Tarea* Tareas, int CantidadTareas, int ID){

    for(unsigned int i = 0; i < CantidadTareas; i++){
        if((*(Tareas + i))->TareaID == ID){
            return (*(Tareas + i));
        }
    }

    return NULL;
}

int EsListaVacia(Lista* Tarea){
    return Tarea == NULL;
}