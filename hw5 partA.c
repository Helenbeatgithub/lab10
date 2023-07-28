/**

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 10

typedef struct pair{
    char *key;
    int value;
} pair_t;

typedef struct node{
    struct node* next;
    pair_t kv;
}node_t;

//Hash function to be used - k mod size.
int stringHash(char* myKey, int numberOfBuckets){
    int sum = 0;
    for(int i = 0; i < strlen(myKey); i++){
        sum += myKey[i];
    }
    
    return sum % numberOfBuckets;
}

//function pointer type definition
typedef int(*hashFunctionPointer)(char*, int);

typedef struct hashmap{
    int buckets;
    node_t** arrayOfLists;
    hashFunctionPointer hashFunction;
}hashmap_t;


hashmap_t* hashmap_create(int buckets){
    hashmap_t* map = (hashmap_t*)malloc(sizeof(hashmap_t));
    
    map -> buckets = buckets;
    
    map -> arrayOfLists = (node_t**)malloc(sizeof(node_t*)* buckets);
    for(int i=0; i < buckets; i++){
        map->arrayOfLists[i] = NULL;
    }
    
    map -> hashFunction = stringHash;
    
    return map;
}

void hashmap_insert(hashmap_t* in, char* key_in, int value){
    pair_t newpair;
    newpair.key = (char*)malloc(sizeof(char) * (strlen(key_in) + 1));
    strcpy(newpair.key, key_in);
    newpair.value = value;
    
    node_t* newnode = (node_t*)malloc(sizeof(node_t));
    newnode->next = NULL;
    newnode->kv = newpair;
    
    unsigned int bucket = in->hashFunction(key_in, in->buckets);
    
    if(in->arrayOfLists[bucket] == NULL){
        in->arrayOfLists[bucket] = newnode;
    }else{
        node_t* current =in ->arrayOfLists[bucket];
        while(current->next != NULL){
            current = current -> next;
        }
        current->next = newnode;
    }
}

void hashmap_printKeyValues(hashmap_t* in){
    for(int i=0; i < in -> buckets; i++){
        printf("Chain [%d]->", i);
        node_t* iter = in -> arrayOfLists[i];
        while(iter != NULL){
            printf(" %d -> ", iter->kv.value);
            iter = iter->next;
        }
        printf("NULL\n");
    }
}

int main(){
    int bucketSize;
    printf("Chain Size:");
    scanf("%d", &bucketSize);
    
    hashmap_t *map = hashmap_create(bucketSize);
    
    printf("Number of values:");
    int valueCount;
    scanf("%d", &valueCount);
    
    printf("Input Values:\n");
    char buffer[10];
    for (int i = 0; i < valueCount; i++){
        int value;
        scanf("%d", &value);
        snprintf(buffer, 10, "%d", value);
        hashmap_insert(map, buffer, value);
    }
    
    hashmap_printKeyValues(map);
    
    //free memory
        for (int i = 0; i < bucketSize; i++) {
        node_t *node = map->arrayOfLists[i];
        while (node) {
            node_t *tmp = node;
            node = node->next;
            free(tmp->kv.key);
            free(tmp);
        }
    }
    free(map->arrayOfLists);
    free(map);
    
    return 0;
    
}








