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
  int newCapacity = HashMap->capacity * 2;
  hashElem** newHashArray = (hashElem**)malloc(sizeof(hashElem*) * newCapacity);
  for (int i = 0; i < newCapacity; i++) {
      newHashArray[i] = NULL;
  }
  for (int i = 0; i < HashMap->capacity; i++) {
      if (HashMap->hashArray[i] != NULL && HashMap->hashArray[i]->key != -1) {
          int position = hash(hashMap->hashArray[i]->key, newCapacity);
          newHashArray[position] = HashMap->hashArray[i];
      }
  }
  free(hashMap->hashArray);
  HashMap->hashArray = newHashArray;
  HashMap->capacity = newCapacity;
  enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
  HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  if (map == NULL)
    return NULL;

  map->bucktes = (Pair **)calloc(capacity, sizeof(Pair *));
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

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
