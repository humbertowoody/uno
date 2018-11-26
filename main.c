//
//  main.c
//
//  Created by Daniel Morales on 11/20/18.
//  Copyright © 2018 Daniel Morales. All rights reserved.
//


/**
 La letra de a lado de los numeros es el color
 14 es tomo 4 y va con A porque es All
    15 es cambio de color y viene por cada color
 13  es come 2 por cada color
 11 es reversa
 12 es no juega

 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct deck{
    char color[1];
    int numero;
    struct deck *next;
}deck;

deck d[108];
typedef struct queue{
    struct deck *head;
    struct deck *tail;

    int size;
}queue;

void readData(){
    int i=0;
    //printf("Aqui entre");
    char line[5];
    struct deck *deck =(struct deck*)malloc(sizeof(struct deck)*108);
    struct queue *queue= (struct queue*)malloc(sizeof(struct queue)*108);
    FILE *pf = NULL;

    if ( ( pf = fopen ( "archivouno.txt", "r")) == NULL) {
        printf ( "could not open file\n");
       // return 1;
    }
    while ( ( fgets ( line, sizeof ( line), pf))) {
        //struct deck *deck =(struct deck*)malloc(sizeof(struct deck)*108);
        if ( ( sscanf ( line, "%d %1[^\n]"
                       , &deck->numero, deck->color)) == 2) {
            //printf ( "%d %s\n", deck->numero, deck->color);
            d[i] = *deck;
            if(queue->head ==NULL) {
                queue->head=deck;
                //printf("Imprime empieza %d\n", queue->head->numero);
            }
            else {
                queue->tail->next=deck;
                // printf("Imprime empieza %d\n", queue->tail->next->numero);
            }

            queue->tail=deck;
            queue->size++;
            i++;

        }

    }
    fclose ( pf);
}

void imprimirDeck(){
    for(int l=0; l<108; l++){
        printf("Deck es numero %d con color %s\n", d[l].numero, d[l].color);
    }
}

//deck * Dequeue(queue *pQueue) {
//    /*the queue is empty or bad param*/
//    deck *item;
//    if (isEmpty(pQueue))
//        return NULL;
//    item = pQueue->head;
//    pQueue->head = (pQueue->head)->next;
//    pQueue->size--;
//    return item;
//}

void playersDeck(queue **play, int n, int *array){


     queue *players = (queue*) malloc(sizeof(queue)*108);
    for (int i = 0; i < 108; i++) {     // fill array
        array[i] = i;
        //printf("%d,", array[i]);
    }
    for (int i = 0; i < 108; i++) {
        // shuffle array
        int temp = array[i];

        int randomIndex = rand() % 108;

        array[i]           = array[randomIndex];
        array[randomIndex] = temp;
    }
    int newN=0;
    for (int i = 0; i < n; i++) {    // print array
       for (int x = newN; x < 7*(i+1); x++) {

           d[array[x]].next = NULL;
           if(players[i].size == 0) {
               players[i].head=&d[array[x]];
               players[i].tail=&d[array[x]];
               //printf("Imprime empieza %d\n", queue->head->numero);
           }
           else {
               players[i].tail->next=&d[array[x]];
               players[i].tail=&d[array[x]];
               // printf("Imprime empieza %d\n", queue->tail->next->numero);
           }

           players[i].size++;

       }
        newN=7*(i+1);
       }

    for(int l=0; l<n; l++){
        //printf("Deck es numero %d con color %s\n", players[l].head->numero, players[l].head->color);
        //deck temp =*players[l].tail;
        deck current =*(struct deck*)malloc(sizeof(struct deck)*108);
        current = *players[l].head;
        int counter = 0;
        while( counter != players[l].size)
        {
            printf("Deck es numero %d con color %s\n", current.numero, current.color);
            if(current.next != NULL){
                current = *current.next;
            }
            counter++;
        }

    }
    (*play) = players;
}

void printDecks(queue *players, int n){

        //printf("Deck es numero %d con color %s\n", players[l].head->numero, players[l].head->color);
        //deck temp =*players[l].tail;
    //players = (queue*) malloc(sizeof(queue)*108);

     for(int l=0; l<n; l++){
        deck *current1 =(struct deck*)malloc(sizeof(struct deck)*108);
         current1 = players[l].head;
        int counter = 0;
         //players[l]->size

         while( counter != players[l].size)
    {
            printf("Deck es numero %d con color %s\n", current1->numero, current1->color);
            if(current1->next != NULL){
                current1 = current1->next;
            }
            counter++;
        }
     }

}

void tirar(queue **playT, deck *move){
   queue *playTable = (struct queue*)malloc(sizeof(struct queue));

    if(playTable->head==NULL){
        playTable->head=move;
        playTable->tail=move;
        //printf("Imprime empieza %d\n", queue->head->numero);
    }else {
        if(playTable->tail->color == move->color || playTable->tail->numero == move->numero){
            playTable->tail->next=move;
            playTable->tail=move;
        }
        //printf("Imprime empieza %d\n", queue->tail->next->numero);
    }
    playTable->size++;
     (*playT) = playTable;
//    deck curr =*(struct deck*)malloc(sizeof(struct deck)*108);
//    curr = *playTable->head;
//    int counter = 0;
//    while( counter != playTable->size)
//    {
//        printf("Deck es numero %d con color %s\n", curr.numero, curr.color);
//        if(curr.next!=NULL){
//            curr = *curr.next;
//        }
//        counter++;
//    }
//
//

}
void checkPlay(){

}
int main() {
    readData();
    srand(time(NULL));
    int n;
    printf("Numero de jugadores: ");
    scanf("%d", &n);
    printf("Numero es %d\n", n);

    queue *players;
    players = (queue*) malloc(sizeof(queue)*n);
    queue *playTable;
    playTable= (queue*)malloc(sizeof(queue));
    int array[108];

    playersDeck(&players, n, (int *)array);
    printf("Ojala %d\n", players[0].size);
    printDecks((queue *)players, n);


    deck *move;
    move = (struct deck*)malloc(sizeof(struct deck)*108);
    *move = *players[1].head;

    tirar(&playTable, move);
    printf("Ojala %d\n", playTable->size);
    //int player =1;

    checkPlay();
//    int i=0;
//    //printf("Aqui entre");
//    char line[5];
//    struct deck *deck =(struct deck*)malloc(sizeof(struct deck)*108);
//    struct queue *queue= (struct queue*)malloc(sizeof(struct queue)*108);
//    FILE *pf = NULL;
//
//    if ( ( pf = fopen ( "archivouno.txt", "r")) == NULL) {
//        printf ( "could not open file\n");
//        return 1;
//    }
//    while ( ( fgets ( line, sizeof ( line), pf))) {
//        //struct deck *deck =(struct deck*)malloc(sizeof(struct deck)*108);
//        if ( ( sscanf ( line, "%d %1[^\n]"
//                       , &deck->numero, deck->color)) == 2) {
//            //printf ( "%d %s\n", deck->numero, deck->color);
//            d[i] = *deck;
//            if(queue->head ==NULL) {
//                queue->head=deck;
//                //printf("Imprime empieza %d\n", queue->head->numero);
//            }
//            else {
//                queue->tail->next=deck;
//              // printf("Imprime empieza %d\n", queue->tail->next->numero);
//            }
//
//            queue->tail=deck;
//            queue->size++;
//            i++;
//
//        }
//        for(int l=0; l<108; l++){
//            printf("Deck es numero %d con color %s\n", d[l].numero, d[l].color);
//        }
//    }
//    fclose ( pf);
    return 0;

           /*
            if(queue->head ==NULL) {
                queue->head=n;
                 printf("Imprime empieza %d", queue->head->numero);
            }
            else {
                queue->tail->next=n;
                printf("Imprime empieza %d", queue->tail->next->numero);
            }

            queue->tail=n;
            queue->size++;

        }
    }*/
    //return 0;
}
    // insert code here...
    //    persona per;


/**
int main() {
    printf("Aqui entre");
    struct queue *q= (struct queue*)malloc(sizeof(struct queue));
    read_file(q);
    return 0;
    //printf("Imprime empieza %d", q->head->numero);
}**/

