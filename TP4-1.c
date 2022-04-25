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

Tarea CrearTarea(int Indice);
void InsertarTarea(Tarea** Tareas, Tarea Objeto, int Indice);
void RealizarTareas(Tarea** Tareas, Tarea** TareasHechas, int CantidadTareas);
void BuscarPorPalabra(Tarea** Tareas, int CantidadTareas, char* PalabraClave);
void BuscarPorID(Tarea** Tareas, int CantidadTareas, int ID);
void MostrarTareas(Tarea** Tareas, int CantidadTareas);
void MostrarTarea(Tarea* Tarea);
void LiberarMemoria(Tarea** Puntero);

int main()
{
    int CantidadTareas;
    Tarea** Tareas;
    Tarea** TareasHechas;
    
    srand(time(NULL));

    printf("Ingrese la cantidad de tareas\n");
    scanf("%d", &CantidadTareas);
    getchar(); // IMPORTANTE: Elimina el ENTER

    Tareas = (Tarea**) malloc(CantidadTareas * sizeof(Tarea*));
    TareasHechas = (Tarea**) malloc(CantidadTareas * sizeof(Tarea));

    for(unsigned int i = 0; i < CantidadTareas; i++){
        Tarea Temporal = CrearTarea((int) i);
        InsertarTarea(Tareas, Temporal, (int) i);
    }

    RealizarTareas(Tareas, TareasHechas, CantidadTareas);

    printf("--------- Tareas Pendientes ---------\n");
    MostrarTareas(Tareas, CantidadTareas);

    printf("\n--------- Tareas Hechas ---------\n");
    MostrarTareas(TareasHechas, CantidadTareas);

    printf("\n--------- Tareas Buscadas ---------\n");
    BuscarPorPalabra(Tareas, CantidadTareas, "test");
    BuscarPorID(Tareas, CantidadTareas, 1);

    for(unsigned int i = 0; i < CantidadTareas; i++){
        LiberarMemoria(&(*(Tareas + i)));
        LiberarMemoria(&(*(TareasHechas + i)));
//        free((*(Tareas + i))->Descripcion);  NO ES NECESARIO, pues ese espacio de memoria no se creó dinámicamente con malloc
//        free((*(Tareas + i)));
//        (*(Tareas + i)) = NULL;
//        free((*(TareasHechas + i)));
//        (*(TareasHechas + i)) = NULL;
    }

    free(Tareas);
    free(TareasHechas);

    return 0;
}

Tarea CrearTarea(int Indice){

    Tarea Temporal;

    printf("\nIngrese Tarea %d\n", Indice);
    char *Buffer = (char *) malloc(100 * sizeof(char));

    Temporal.Duracion = rand() % 101 + 10;
    Temporal.TareaID = Indice;

    printf("Ingrese la decripcion\n");
    fgets(Buffer, 100, stdin);

    Temporal.Descripcion = (char*) malloc((strlen(Buffer) + 1) * sizeof(char));
    strcpy(Temporal.Descripcion, Buffer);

    free(Buffer);
    
    return Temporal;
}

void InsertarTarea(Tarea** Tareas, Tarea Objeto, int Indice){
    (*(Tareas + Indice)) = (Tarea*) malloc(sizeof(struct Tarea));
    (*(Tareas + Indice))->Duracion = Objeto.Duracion;
    (*(Tareas + Indice))->TareaID = Objeto.TareaID;
    (*(Tareas + Indice))->Descripcion = Objeto.Descripcion;
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

void BuscarPorPalabra(Tarea** Tareas, int CantidadTareas, char* PalabraClave){
    
    for(unsigned int i = 0; i < CantidadTareas; i++){
        if((*(Tareas + i)) && strstr((*(Tareas + i))->Descripcion, PalabraClave)){
                MostrarTarea((*(Tareas + i)));
        }
    }
}

void BuscarPorID(Tarea** Tareas, int CantidadTareas, int ID){

    for(unsigned int i = 0; i < CantidadTareas; i++){
        if((*(Tareas + i)) && (*(Tareas + i))->TareaID == ID){
                MostrarTarea((*(Tareas + i)));
        }
    }    
}

void LiberarMemoria(Tarea** Puntero){
    if(Puntero){
        free(*Puntero);
        *Puntero = NULL;
    }
}