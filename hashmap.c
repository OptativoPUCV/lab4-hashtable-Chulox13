#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) 
{
  int index = hash(key, map->capacity);

  while (map->buckets[index] != NULL && map->buckets[index]->key != NULL)
    {
      index = (index +1) % map->capacity;
    }

  map->buckets[index] = createPair(key, value);

  map->current = index;
  map->size++;

}


void enlarge(HashMap * map) {
  

  enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
  HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  if (map == NULL)
    return NULL;

  map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
  if (map->buckets == NULL)
  {
    free(map);
    return NULL;
  }

  for (int i = 0; i < capacity; i++)
    {
      map->buckets[i] = NULL;
    }


  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  
  return map;
}

void eraseMap(HashMap * map,  char * key) 
{    
  int index = hash(key, map->capacity);

  while (map->buckets[index] != NULL) 
  {
      if (strcmp(map->buckets[index]->key, key) == 0) 
      {
          
          map->buckets[index]->key = NULL;
          
          map->current = index;
         
          map->size--;
          
          return;
      }
      
      index = (index + 1) % map->capacity;
  }

}

Pair * searchMap(HashMap * map,  char * key) 
{
  int index = hash(key, map->capacity);

  // Buscar la clave
  while (map->buckets[index] != NULL) {
      // Verificar si la clave coincide
      if (strcmp(map->buckets[index]->key, key) == 0) {
          // Actualizar el índice current
          map->current = index;
          // Devolver el par asociado a la clave
          return map->buckets[index];
      }
      // Avanzar al siguiente índice circularmente
      index = (index + 1) % map->capacity;
  }

    return NULL;
}

Pair * firstMap(HashMap * map) 
{
  for (int i = 0; i < map->capacity; i++) 
  {
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) 
    {
      map->current = i;
          
      return map->buckets[i];
    }
  }

  return NULL;
}

Pair * nextMap(HashMap * map) 
{
  if (map->current == -1) {
    return NULL;
  }

  // Avanzar al siguiente índice circularmente a partir del índice current
  int index = (map->current + 1) % map->capacity;

  // Buscar el siguiente par válido a partir del nuevo índice
  while (index != map->current) {
    // Verificar si la casilla en el nuevo índice contiene un par válido
    if (map->buckets[index] != NULL && map->buckets[index]->key != NULL) {
        // Actualizar el índice current
        map->current = index;
        // Devolver el siguiente par válido encontrado
        return map->buckets[index];
    }
    // Avanzar al siguiente índice circularmente
    index = (index + 1) % map->capacity;
  }

  // Si no se encontró ningún par válido después del índice actual, devolver NULL
  return NULL;
}
