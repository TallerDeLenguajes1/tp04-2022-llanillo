#ifndef TP04_2022_LLANILLO_LISTAENLAZADA_H
#define TP04_2022_LLANILLO_LISTAENLAZADA_H
#endif //TP04_2022_LLANILLO_LISTAENLAZADA_H

#include <stdlib.h>

typedef struct Objeto{
    int ID;
    char* Palabra;
}Objeto;

struct Nodo{
    Objeto Objeto;
    struct Nodo* Siguiente;
};
typedef struct Nodo* Lista;

Lista CrearLista();
Lista NuevoNodo(Objeto Dato);
void InsertarNodo(Lista* Cabecera, Objeto Dato);
void InsertarAlFinal(Lista* Cabecera, Objeto Dato);
Lista BuscarNodo(Lista* Cabecera, int ID);
Lista Eliminar(Lista Nodo);
void EliminarPorID(Lista* Cabecera, int ID);
void LiberarMemoria(Lista* Cabecera);

/*
 * Crea una lista vacía
 */
Lista CrearLista(){
    return NULL;
}

/*
 * Devuelve un nuevo nodo con el objeto recibido.
 */
Lista NuevoNodo(Objeto Dato){
    Lista Nuevo = (Lista) malloc(sizeof(struct Nodo));
    Nuevo->Objeto = Dato;
    Nuevo->Siguiente = NULL;
    return Nuevo;
}

/*
 * Inserta el objeto al inicio de la lista recibida.
 */
void InsertarNodo(Lista* Cabecera, Objeto Dato){
    Lista Nuevo = NuevoNodo(Dato);
    Nuevo->Siguiente = *Cabecera;
    *Cabecera = Nuevo;
}

/*
 * Inserta el objeto al final de la lista
 */

void InsertarAlFinal(Lista* Cabecera, Objeto Dato){
    Lista Nuevo = NuevoNodo(Dato);
    Lista Auxiliar = *Cabecera;

    while(Auxiliar->Siguiente){ // Equivalente a Auxiliar->Siguiente != NULL
        Auxiliar = Auxiliar->Siguiente;
    }

    Auxiliar->Siguiente = Nuevo;
}

/*
 * Busca un nodo que contenga el mismo ID
 */
Lista BuscarNodo(Lista* Cabecera, int ID){
    Lista Auxiliar = *Cabecera;

    while(Auxiliar && Auxiliar->Objeto.ID != ID){
        Auxiliar = Auxiliar->Siguiente;
    }

    return Auxiliar;
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
    return Nodo;
}

/*
 * Busca un nodo con el mismo ID y lo elimina
 */
void EliminarPorID(Lista* Cabecera, int ID){
    Lista Auxiliar = *Cabecera;
    Lista Anterior = *Cabecera;

    while(Auxiliar && Auxiliar->Objeto.ID != ID){
        Anterior = Auxiliar;
        Auxiliar = Auxiliar->Siguiente;
    }

    if(Auxiliar){
        Anterior->Siguiente = Auxiliar->Siguiente;
        free(Auxiliar);
    }
}

void LiberarMemoria(Lista* Cabecera){
    Lista Auxiliar = *Cabecera;

    while(Auxiliar){
        Auxiliar = Eliminar(Auxiliar);
    }
}

