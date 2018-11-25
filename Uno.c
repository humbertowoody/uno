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
    "No Juega - N"
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
} Deck;

/**
 * Estructura de Jugador.
 */
typedef struct player
{
  int score; // Puntaje del jugador.
  Deck *cards;
} Player;

// Funciones de utilidades.

/**
 * Intercambiar dos cartas.
 */
void swap(Card *a, Card *b);

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
 * Imprimir Ganador.
 */
void printWinner(Player, int);

// Funciones de lógica de juego.

/**
 * Main
 * Función principal de juego
 */
int main(int argc, char const *argv[])
{
  Deck pile_game, pile_remaining; // La pila de juego y de cartas sobrantes.
  Player players[MAX_PLAYERS];    // Los jugadores.
  int noPlayers = 0;              // El número de jugadores.
  int currPlayer = 1;             // Jugador Actual
  int ronda = 0;                  // La ronda actual del juego
  int winner = 0;                 // Si hay un ganador

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

  // Llenar el mazo inicial.

  // 18 cartas de cada color del 1 al 9.
  // 1 cero por cada color
  // 2 cartas de Reversa, No Juega y Toma 2 para cada color
  // 4 comodines de Toma 4
  // 4 comodines de Cambio de Color

  // Revolver el mazo.

  // Repartir las cartas. (7 para cada jugador)

  // Sacar carta inicial.

  // Generar Mazo de robo.

  // Ciclo de juego principal
  do
  {

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
  printf("Gracias por jugar UNO.\n¡Esperamos verte pronto!.");
  return 0;
}
