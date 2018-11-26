/**
 * Uno.c
 *
 * Juego de UNO clásico escrito en C.
 *
 * Daniel Morales
 */

/**
 * Librerías
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Constantes
 */
#define MAX_CARDS 108
#define MAX_PLAYERS 3

// Nombres de las cartas.
char *card_name[15] = {
    "Cero - 0",
    "Uno - 1",
    "Dos - 2",
    "Tres - 3",
    "Cuatro - 4",
    "Cinco - 5",
    "Seis - 6",
    "Siete - 7",
    "Ocho - 8",
    "Nueve - 9",
    "Reversa - R",
    "No Juega - N",
    "Toma 2 - T2",
    "Toma 4 - T4",
    "Cambio de Color - W",
};

// Colores de las Cartas.
char *card_color[5] = {
    "Rojo",
    "Amarillo",
    "Verde",
    "Azul",
    "Comodín",
};

// Estructuras relevantes.

/**
 * Estructura de Tarjeta.
 */
typedef struct card
{
  int value; // El valor de la carta.
  int color; // El color de la carta.
} Card;

/**
 * Estructura de Mazo.
 */
typedef struct deck
{
  Card cards[MAX_CARDS]; // Las tarjetas en el deck.
  int noCards;           // El número de tarjetas en el deck.
  int begin;
} Deck;

/**
 * Estructura de Jugador.
 */
typedef struct player
{
  int score; // Puntaje del jugador.
  Deck cards;
} Player;

// Funciones de utilidades.

/**
 * Intercambiar dos cartas.
 *
 * Intercambia dos cartas en diferentes posiciones de memoria.
 */
void swapC(Card *, Card *);

// Funciones de Estructuras.

/**
 * Añadir carta a Mazo.
 */
void pushC(Deck *d, Card);

/**
 * Extraer una carta del Mazo.
 *
 * Saca una carta del Mazo en la posición indicada.
 */
void popAtPos(Deck *, int);

/**
 * Sacar primer Carta del Mazo.
 *
 * Saca la primera carta de un Mazo.
 */
void popC(Deck *);

/**
 * Revolver un Mazo
 */
void shuffle(Deck *deck);

// Funciones de impresión de datos.

/**
 * Imprimir vista de juego para jugador.
 */
void printPlayer(Player);

/**
 * Imprimir un Mazo.
 */
void printDeck(Deck);

/**
 * Imprimir una Carta.
 */
void printCard(Card);

/**
 * Imprimir Ganador.
 */
void printWinner(Player, int);

// Funciones de lógica de juego.

/**
 * Inicializar Mazo.
 */
void initDeck(Deck *);

/**
 * Main
 * Función principal de juego
 */
int main(int argc, char const *argv[])
{
  Deck pile_game, pile_remaining; // La pila de juego y de cartas sobrantes.
  Player players[MAX_PLAYERS];    // Los jugadores.
  int noPlayers = 0;              // El número de jugadores.
  int currPlayer = 1;             // Jugador Actual.
  int ronda = 0;                  // La ronda actual del juego.
  int winner = 0;                 // Si hay un ganador.

  // Inicializar estructuras.
  pile_game.noCards = 0;
  pile_remaining.noCards = 0;

  // Saludo inicial.
  printf("¡Hola!\nBienvenid@ al clásico juego de UNO.\n");

  // Lectura de datos con validación.
  do
  {
    printf("Ingresa el número de jugadores (máximo 3): ");
    scanf("%i", &noPlayers);
  } while (noPlayers <= 0 || noPlayers > MAX_PLAYERS);

  printf("¡Excelente! Jugarán %d personas.\n", noPlayers);

  // Inicializar el Juego
  initDeck(&pile_remaining);
  printDeck(pile_remaining);

  // Revolver el mazo.

  // Repartir las cartas. (7 para cada jugador)

  // Sacar carta inicial.

  // Generar Mazo de robo.

  // Ciclo de juego principal
  do
  {
    winner = 1;
    // Cambiar al siguiente jugador.
    if (currPlayer + 1 >= noPlayers)
    {
      currPlayer = 1;
    }
    else
    {
      currPlayer++;
    }
  } while (!winner);

  // Anunciar Ganador

  // Despedida
  printf("Gracias por jugar UNO.\n¡Esperamos verte pronto!\n");
  return 0;
}

// Implementación de Funciones.

/**
 * Añadir una carta al final de un Mazo.
 */
void pushC(Deck *d, Card c)
{
  if (d->noCards >= MAX_CARDS)
  {
    printf("No es posible añadir más tarjetas a este mazo.");
  }
  else
  {
    d->cards[d->noCards] = c;
    d->noCards++;
  }
}

/**
 * Imprimir una Carta.
 */
void printCard(Card a)
{
  printf("(%s | %s)", card_name[a.value], card_color[a.color]);
}

/**
 * Imprimir un Mazo.
 */
void printDeck(Deck a)
{
  printf("Contenido del Mazo:\n");
  if (!a.noCards)
  {
    printf("Mazo vacío.\n");
    return;
  }

  for (int i = 0; i < a.noCards; i++)
  {
    printf("%i) ", i);
    printCard(a.cards[i]);
    printf("\n");
  }
  printf("\n");
}

// Funciones de Lógica del Juego.

/**
 * Inicializar el Mazo.
 */
void initDeck(Deck *a)
{
  // 18 cartas de cada color del 1 al 9.
  for (int i = 1; i <= 9; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      Card temp = {i, j};
      pushC(a, temp);
      pushC(a, temp);
    }
  }

  // 1 cero por cada color
  for (int i = 0; i < 4; i++)
  {
    Card temp = {0, i};
    pushC(a, temp);
  }

  // 2 cartas de Reversa, No Juega y Toma 2 para cada color
  for (int i = 0; i < 4; i++)
  {
    for (int j = 10; j <= 12; j++)
    {
      Card temp = {j, i};
      pushC(a, temp);
      pushC(a, temp);
    }
  }

  // 4 comodines de Toma 4 y 4 de Cambio de Color.
  for (int i = 0; i < 4; i++)
  {
    Card comodinT4 = {13, 4};
    Card comodinCC = {14, 4};
    pushC(a, comodinT4);
    pushC(a, comodinCC);
  }
}