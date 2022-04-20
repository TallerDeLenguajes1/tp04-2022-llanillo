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

void IngresarTarea(Lista Tareas, int Indice);
void InsertarTarea(Lista* Principal, Lista Tarea);
void RealizarTareas(Lista Tareas, Lista TareasHechas);
Lista BusquedaPorPalabra(Lista Tareas, char* PalabraClave);
Lista BusquedaPorId(Lista Tareas, int ID);
void MostrarTareas(Lista Tareas);
void MostrarTarea(Lista Tarea);
int EsListaVacia(Lista Tarea);

int main()
{
    int CantidadTareas;
    Lista Tareas = NULL;
    Lista TareasHechas = NULL;
    Lista Auxiliar = NULL;

    srand(time(NULL));

    printf("Ingrese la cantidad de tareas\n");
    scanf("%d", &CantidadTareas);
    getchar();

    for(unsigned int i = 0; i < CantidadTareas; i++){
        Auxiliar = (Lista) malloc(sizeof(struct Nodo));
        IngresarTarea(Auxiliar, i);
        InsertarTarea(&Tareas, Auxiliar);
    }

    //    RealizarTareas(Tareas, TareasHechas);

    printf("--------- Tareas Pendientes ---------\n");
    MostrarTareas(Tareas);

    printf("\n--------- Tareas Hechas ---------\n");
    //    MostrarTareas(TareasHechas);

    printf("\n--------- Tareas Buscada ---------\n");
    //    MostrarTarea(BusquedaPorPalabra(Tareas, "perrito"));
    //    MostrarTarea(BusquedaPorId(Tareas, 1));

    return 0;
}

void IngresarTarea(Lista Tareas, int Indice){

    printf("Ingrese Tarea %d\n", Indice);
    char *Buffer = (char *) malloc(100 * sizeof(char));

    Tareas->T.Duracion = rand() % 101 + 10;
    Tareas->T.TareaID = Indice;

    printf("Ingrese la decripción\n");
    fgets(Buffer, 100, stdin);

    Tareas->T.Descripcion = (char*) malloc((strlen(Buffer) + 1) * sizeof(char));
    strcpy(Tareas->T.Descripcion, Buffer);

    Tareas->Siguiente = NULL;
}

void MostrarTareas(Lista Tareas){

    while(!EsListaVacia(Tareas)){
        printf("ID: %d\n", Tareas->T.TareaID);
        printf("Duracion: %d\n", Tareas->T.Duracion);
        printf("Descripción: %s\n", Tareas->T.Descripcion);
        Tareas = Tareas->Siguiente;
    }
}

void MostrarTarea(Lista Tarea){

    if(!EsListaVacia(Tarea)){
        printf("ID: %d\n", Tarea->T.TareaID);
        printf("Duracion: %d\n", Tarea->T.Duracion);
        printf("Descripción: %s\n", Tarea->T.Descripcion);
    }
    else{
        printf("Tarea vacia\n");
    }
}

void RealizarTareas(Lista* Tareas, Lista* TareasHechas){

    Lista Auxiliar = NULL;
    int temporal;

    while(!EsListaVacia(Tareas)){
        printf("--- Tarea %d ---\n", (*Tareas)->T.TareaID);
        printf("¿Esta hecha la tarea? (1 - Si, 0 - No)\n");
        scanf(" %i", &temporal);

        if(temporal){
            Auxiliar = *Tareas;
            Auxiliar->Siguiente = NULL;
            (*TareasHechas) = Auxiliar;
            (*TareasHechas)->Siguiente = NULL;
            Tareas = Tareas->Siguiente;
            free(Tareas);
            Tareas = NULL;
        }
        else{

        }

        Tareas = Tareas->Siguiente;
    }
}

Lista BusquedaPorPalabra(Lista Tareas , char* PalabraClave){

    while(!EsListaVacia(Tareas)){
        if(strstr(Tareas->T.Descripcion, PalabraClave) != NULL){
            return Tareas;
        }
        Tareas++;
    }

    return NULL;
}

Lista BusquedaPorId(Lista Tareas, int ID){

    while(!EsListaVacia(Tareas)){
        if(Tareas->T.TareaID == ID){
            return Tareas;
        }
        Tareas++;
    }

    return NULL;
}

int EsListaVacia(Lista Tarea){
    return Tarea == NULL;
}

void InsertarTarea(Lista* Principal, Lista Tarea){
    Tarea->Siguiente = *Principal;
    *Principal = Tarea;
}

Lista BorrarTarea()