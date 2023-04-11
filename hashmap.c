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


void insertMap(HashMap * map, char * key, void * value) {
  long indiceH = hash(key, map->capacity);
  Pair *aux = createPair(key, value);
  while (1) {
    if (!map->buckets[indiceH] || !map->buckets[indiceH]->key) {
      map->buckets[indiceH] = aux;
      map->size++;
      map->current = indiceH;
      return;
    }
    indiceH++;
    if (indiceH == map->capacity)
      indiceH = 0;
  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *local = (HashMap*) malloc(sizeof(HashMap));
  local->buckets = (Pair**) calloc(capacity, sizeof(Pair*));
  local->size = 0;
  local->capacity = capacity;
  local->current = -1;
  return local;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   
  long indiceH = hash(key, map->capacity);
  while (1) {
    if (map->buckets[indiceH]->key == NULL)
      return NULL;
    if (is_equal(key, map->buckets[indiceH]->key)) {
      map->current = indiceH;
      return map->buckets[indiceH];
    }
    indiceH++;
    if (indiceH == map->capacity)
      indiceH = 0;
  }
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
