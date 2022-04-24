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
    Tarea Objeto;
    struct Nodo* Siguiente;
};
typedef struct Nodo* Lista;

/*
 * Declaraciones de la lista enlzada
 */
Lista CrearLista();
Lista NuevoNodo(Tarea Objeto);
void InsertarNodo(Lista* Cabecera, Tarea Objeto);
Lista Eliminar(Lista Nodo);

/*
 * Declaraciones para operar con las tareas
 */
Tarea CrearTarea(int Indice);
void RealizarTareas(Lista* Tareas, Lista* TareasHechas);
Lista BuscarPorPalabra(Lista* Cabecera, char* PalabraClave);
Lista BuscarPorID(Lista* Cabecera, int ID);
void MostrarTareas(Lista Tareas);
void MostrarTarea(Lista Tarea);

int main()
{
    int CantidadTareas;
    Lista Tareas = CrearLista();
    Lista TareasHechas = CrearLista();

    srand(time(NULL));

    printf("Ingrese la cantidad de tareas\n");
    scanf("%d", &CantidadTareas);
    getchar();

    for(unsigned int i = 0; i < CantidadTareas; i++){
        Tarea Temporal = CrearTarea(i);
        InsertarNodo(&Tareas, Temporal);
    }

    RealizarTareas(&Tareas, &TareasHechas);

    printf("--------- Tareas Pendientes ---------\n");
    MostrarTareas(Tareas);

    printf("\n--------- Tareas Hechas ---------\n");
    MostrarTareas(TareasHechas);

    printf("\n--------- Tareas Buscada ---------\n");
//    MostrarTarea(BuscarPorPalabra(&Tareas, "perrito"));
//    MostrarTarea(BuscarPorID(&Tareas, 0));

    return 0;
}

#pragma region Operaciones Lista

/*
 * Crea una lista vacía
 */
Lista CrearLista(){
    return NULL;
}

/*
 * Devuelve un nuevo nodo con el objeto recibido.
 */
Lista NuevoNodo(Tarea Objeto){
    Lista Nuevo = (Lista) malloc(sizeof(struct Nodo));
    Nuevo->Objeto = Objeto;
    Nuevo->Siguiente = NULL;
    return Nuevo;
}

/*
 * Inserta el objeto al inicio de la lista recibida.
 */
void InsertarNodo(Lista* Cabecera, Tarea Objeto){
    Lista Nuevo = NuevoNodo(Objeto);
    Nuevo->Siguiente = *Cabecera;
    *Cabecera = Nuevo;
}

/*
 * Elimina el nodo y devuelve el siguiente de la lista
 */
Lista Eliminar(Lista Nodo){
    if(Nodo == NULL){
        return Nodo;
    }

    Lista Temporal = Nodo;
    Nodo = Nodo->Siguiente;
    free(Temporal);
    Temporal = NULL;
    return Nodo;
}

#pragma endregion

#pragma region Operaciones Tareas

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

    return Temporal;
}

void MostrarTareas(Lista Tareas){

    while(Tareas){
        printf("ID: %d\n", Tareas->Objeto.TareaID);
        printf("Duracion: %d\n", Tareas->Objeto.Duracion);
        printf("Descripcion: %s\n", Tareas->Objeto.Descripcion);
        Tareas = Tareas->Siguiente;
    }
}

void MostrarTarea(Lista Tarea){

    if(Tarea){
        printf("ID: %d\n", Tarea->Objeto.TareaID);
        printf("Duracion: %d\n", Tarea->Objeto.Duracion);
        printf("Descripción: %s\n", Tarea->Objeto.Descripcion);
    }
    else{
        printf("No se encuentra esta tarea\n");
    }
}

void RealizarTareas(Lista* Tareas, Lista* TareasHechas){

    Lista Auxiliar = *Tareas;
    Lista Anterior = NULL;

    int Opcion;

    while(Auxiliar){
        printf("--- Tarea %d ---\n", Auxiliar->Objeto.TareaID);
        printf("¿Esta hecha la tarea? (1 - Si, 0 - No)\n");
        scanf(" %i", &Opcion); // Se agrega espacio al scanf para que elimine el ENTER (Salto de línea)

        /*
         * Entra si Opcion es diferente de cero
         */
        if(Opcion){
            // Siempre se agrega a TareasHechas la Tarea actual
            InsertarNodo(TareasHechas,Auxiliar->Objeto);

            /*
             * Entrará solo en la primera iteración, es decir, si se selecciona que está hecha la primera Tarea.
             * Haremos que la cabecera apunte al siguiente y liberamos la memoria.
             */
            if(Anterior == NULL){
                Lista Temporal = *Tareas;
                *Tareas = Auxiliar->Siguiente;
                Auxiliar = Auxiliar->Siguiente;
                Eliminar(Temporal);
            }
            /*
             * Entrará si es diferente de la primeera iteración, es decir, si se selecciona que está hecha
             * cualquier Tarea menos la primera.
             * Haremos que auxiliar y el siguiente del anterior apunte al siguiente del auxiliar, es decir, que apunten
             * al siguiente nodo de la lista y liberamos la memoria.
             */
            else{
                Auxiliar = Auxiliar->Siguiente;
                Anterior->Siguiente = Eliminar(Auxiliar);
            }
        }
        /*
         * Si no se selecciona hecha, seguimos iterando.
         */
        else{
            Anterior = Auxiliar;
            Auxiliar = Auxiliar->Siguiente;
        }
    }
}

/*
 * Busca en la lista un objeto que contenga el mismo ID y lo devuelve.
 */
Lista BuscarPorID(Lista* Cabecera, int ID){
    Lista Auxiliar = *Cabecera;

    while(Auxiliar && Auxiliar->Objeto.TareaID != ID){
        Auxiliar = Auxiliar->Siguiente;
    }

    return Auxiliar;
}

Lista BuscarPorPalabra(Lista* Cabecera, char* PalabraClave){

    Lista Auxiliar = *Cabecera;

    while(Auxiliar && strstr(Auxiliar->Objeto.Descripcion, PalabraClave) == NULL){
        Auxiliar = Auxiliar->Siguiente;
    }

    return Auxiliar;
}

#pragma endregion