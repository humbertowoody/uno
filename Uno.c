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
#include <time.h>

/**
 * Constantes
 */
#define MAX_CARDS 108
#define MAX_PLAYERS 6

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
} Deck;

/**
 * Estructura de Jugador.
 */
typedef struct player
{
  Deck deck;      // Mazo del jugador.
  char name[256]; // Nombre del jugador.
  int shoutUno;   // Si el jugador ha gritado UNO.
} Player;

// Funciones de utilidades.

/**
 * Intercambiar dos cartas.
 *
 * Intercambia dos cartas en diferentes posiciones de memoria.
 */
void swapCard(Card *, Card *);

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
Card popAtPos(Deck *, int);

/**
 * Sacar primer Carta del Mazo.
 *
 * Saca la primera carta de un Mazo.
 */
Card popC(Deck *);

/**
 * Revolver un Mazo
 *
 * Se utiliza el algorimto de Yates-Fisher:
 * https://es.wikipedia.org/wiki/Algoritmo_de_Fisher-Yates
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
void printWinner(Player);

// Funciones de lógica de juego.

/**
 * Inicializar Mazo.
 *
 * Inicializa el Mazo con la configuración dada para el juego de UNO.
 * 18 tarjetas del 1 al 9 para cada color.
 * 1 cero por color.
 * 2 Reversa, 2 Toma Dos y 2 No Juega para cada color.
 * 4 Comodines Toma Cuatro.
 * 4 Comodines Cambio de Color.
 */
void initDeck(Deck *);

/**
 * Tomar una Carta.
 *
 * Un jugador toma una carta del Mazo de Robo, si no quedan cartas disponibles,
 * se deja la última carta en el Mazo de Juego y las demás se ingresan en el
 * Mazo de Robo y se revuelve.
 */
void takeCard(Player *, Deck *, Deck *);

/**
 * Jugada Válida.
 *
 * Esta función determina si una carta puede, o no, ser añadida al mazo de juego.
 * Para esto compara la última carta del mazo con la carta que se desea agregar.
 * Si es válido regresa 1.
 * En caso contrario, 0.
 */
int validPlay(Card, Card);

/**
 * Avanzar Turno
 *
 * Esta función avanza un turno en el juego tomando en consideración el jugador actual,
 * el número máximo de jugadores y el sentido del juego.
 */
void anotherTurn(int *, int, int);

/**
 * Main
 * Función principal de juego
 */
int main(int argc, char const *argv[])
{
  Deck pile_game, pile_remaining; // La pila de juego y de cartas sobrantes.
  Player players[MAX_PLAYERS];    // Los jugadores.
  int noPlayers = 0;              // El número de jugadores.
  int currPlayer = 0;             // Jugador actual, inicializado en 0.
  int ronda = 0;                  // La ronda actual del juego.
  int winner = 0;                 // Si hay un ganador.
  int sentido = 1;                // El sentido de rotación de jugadores, 1 ascendente, -1 descendente.

  // Inicializar los mazos con su tamaño inicial (0).
  pile_game.noCards = 0;
  pile_remaining.noCards = 0;
  for (int i = 0; i < MAX_PLAYERS; i++)
  {
    players[i].deck.noCards = 0;
    players[i].shoutUno = 0;
  }

  // Saludo inicial.
  printf("¡Hola!\nBienvenid@ al clásico juego de UNO.\n");

  // Leer el número de jugadores.
  do
  {
    printf("¿Cuántos jugadores habrá (mínimo 3, máximo %i)?\n", MAX_PLAYERS - 1);
    printf("> ");
    scanf("%i", &noPlayers);
  } while (noPlayers <= 2 || noPlayers >= MAX_PLAYERS);

  printf("¡Excelente! Jugarán %d personas.\n", noPlayers);

  // Leer los nombres de los jugadores.
  for (int i = 0; i < noPlayers; i++)
  {
    printf("¿Cómo se llama el Jugador %i?\n", i + 1);
    printf("> ");
    scanf(" %s", players[i].name);
  }

  // Saludar a los jugadores e indicar número de jugador.
  printf("¡Perfecto! Bienvenidos:\n");
  for (int i = 0; i < noPlayers; i++)
  {
    printf("\tJugador %i - %s\n", i + 1, players[i].name);
  }

  // Inicializar el Juego
  printf("Inicializando juego...\n");
  initDeck(&pile_remaining);

  // Revolver el mazo.
  printf("Revolviendo Mazo...\n");
  shuffle(&pile_remaining);

  // Repartir las cartas. (7 para cada jugador)
  printf("Repartiendo cartas a los jugadores...\n");
  for (int i = 0; i < noPlayers; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      pushC(&players[i].deck, popC(&pile_remaining));
    }
  }

  // Sacar carta inicial.
  printf("Sacando carta inicial...\n");
  pushC(&pile_game, popC(&pile_remaining));

  // Mensaje de inicio de juego.
  printf("\n\n\n");
  printf("\t+---------------------+\n");
  printf("\t| ¡Comienza el Juego! |\n");
  printf("\t+---------------------+\n");
  printf("\n\n\n");

  // Ciclo de juego principal
  do
  {
    int menu1, pickedCard;
    printf("\t¡Es turno de %s!\n", players[currPlayer].name);
    printf("La carta actual de juego es: ");
    printCard(pile_game.cards[pile_game.noCards - 1]);
    printf("\n");

    // Si fue un Toma 2 o Toma 4, añadirlas a este jugador.
    // Siempre y cuando no sea la ronda inicial.
    if (pile_game.cards[pile_game.noCards - 1].value == 12 && ronda > 0)
    {
      printf("\n¡Rayos!\n");
      printf("El jugador anterior te ha lanzado un Toma 2. Se añadirán las cartas a tu Mazo.\n");
      // Toma 2.
      takeCard(&players[currPlayer], &pile_remaining, &pile_game);
      takeCard(&players[currPlayer], &pile_remaining, &pile_game);
    }
    else if (pile_game.cards[pile_game.noCards - 1].value == 13 && ronda > 0)
    {
      printf("\n¡Rayos!\n");
      printf("El jugador anterior te ha lanzado un Toma 4. Se añadirán las cartas a tu Mazo.\n");
      // Toma 4.
      takeCard(&players[currPlayer], &pile_remaining, &pile_game);
      takeCard(&players[currPlayer], &pile_remaining, &pile_game);
      takeCard(&players[currPlayer], &pile_remaining, &pile_game);
      takeCard(&players[currPlayer], &pile_remaining, &pile_game);
    }

    printf("Tu Mazo:\n");
    printDeck(players[currPlayer].deck);
    do
    {
      printf("¿Qué deseas hacer?\n");
      printf("\t1.- Tirar una carta de mi mazo.\n");
      printf("\t2.- Tomar una carta del mazo de robo.\n");
      printf("> ");
      scanf(" %i", &menu1);
    } while (menu1 < 1 || menu1 > 2);

    if (menu1 == 1) // Tirar una carta del Mazo propio.
    {
      do
      {
        do
        {
          printf("¿Qué carta deseas tirar (0 a %i)?\n", players[currPlayer].deck.noCards - 1);
          printf("> ");
          scanf(" %i", &pickedCard);
        } while (pickedCard < 0 || pickedCard > players[currPlayer].deck.noCards - 1);

        // Checar si es válido
        if (!validPlay(pile_game.cards[pile_game.noCards - 1], players[currPlayer].deck.cards[pickedCard]))
        {
          int menu2;
          do
          {
            printf("¡La carta que has seleccionado NO es válida!\n");
            printf("¿Qué deseas hacer?\n");
            printf("\t 1.- Intentar con otra carta de mi mazo.\n");
            printf("\t 2.- Tomar una carta del mazo de robo.\n");
            printf("> ");
            scanf(" %i", &menu2);
          } while (menu2 < 1 || menu2 > 2);

          // Si selecciona la opción 2, seguimos a siguiente segmento.
          if (menu2 == 2)
          {
            menu1 = 2;
          }
        }
      } while (menu1 == 1 && !validPlay(pile_game.cards[pile_game.noCards - 1], players[currPlayer].deck.cards[pickedCard]));

      // Tiró una carta válida.
      if (menu1 == 1)
      {
        // Validar acción.
        if (players[currPlayer].deck.cards[pickedCard].value > 9)
        {
          switch (players[currPlayer].deck.cards[pickedCard].value)
          {
          case 10: // Reversa
            printf("¡Se ha aplicado el Reversa correctamente!\n");
            sentido *= -1;
            break;
          case 11: // No Juega
            printf("¡Se ha saltado el turno del siguiente jugador!\n");
            anotherTurn(&currPlayer, noPlayers, sentido);
            break;
          case 12: // Toma 2
            printf("¡Se ha aplicado correctamente el Toma Dos!\n");
            break;
          case 13: // Toma 4 con Cambio de Color
            printf("¡Se ha aplicado correctamente el Toma Cuatro!\n");
            break;
          default: // Cambio de Color
            printf("Ahora puedes cambiar el color del juego, para esto, selecciona una carta de tu Mazo que tenga el color que deseas:\n");

            break;
          }
        }

        // Sacar carta de mazo de jugador y ponerla en el juego.
        pushC(&pile_game, popAtPos(&players[currPlayer].deck, pickedCard));
      }
    }

    if (menu1 == 2) // Tomar una Carta del Mazo de Robo.
    {
      takeCard(&players[currPlayer], &pile_remaining, &pile_game);
      printf("La carta que has tomado es: ");
      printCard(players[currPlayer].deck.cards[players[currPlayer].deck.noCards - 1]);
      printf("\n");
    }

    // Checar si el usuario desea gritar uno.
    char shout;
    do
    {
      printf("Antes de terminar tu turno, ¿Quieres gritar UNO? S/N: ");
      scanf(" %c", &shout);
    } while (shout != 'S' && shout != 's' && shout != 'N' && shout != 'n');

    if (shout == 'S' || shout == 's')
    {
      printf("***************************************************\n");
      printf("\t¡%s ha gritado UNO!\n", players[currPlayer].name);
      printf("***************************************************\n");
      players[currPlayer].shoutUno = 1;
    }

    // Mensaje de fin de turno.
    printf("Fin del turno de %s.\n\n", players[currPlayer].name);

    // Si no hay ganador, avanzar el juego.
    if (!winner)
    {
      anotherTurn(&currPlayer, noPlayers, sentido);
    }
    ronda++;
  } while (!winner);

  // Anunciar Ganador
  printWinner(players[currPlayer]);

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
  for (int i = 0; i < a.noCards; i++)
  {
    printf("%i) ", i);
    printCard(a.cards[i]);
    printf("\n");
  }
  printf("\n");
}

// Funciones de utilidades.

/**
 * Intercambiar dos cartas.
 */
void swapCard(Card *a, Card *b)
{
  Card temp = *a;
  *a = *b;
  *b = temp;
}

// Funciones de estructuras.

/**
 * Extraer una carta del Mazo.
 */
Card popAtPos(Deck *a, int pos)
{
  // TODO: validar posicion
  Card temp = a->cards[pos];
  for (int i = pos; i < (a->noCards - 1); i++)
  {
    a->cards[i] = a->cards[i + 1];
  }
  a->noCards--;
  return temp;
}

/**
 * Sacar primer Carta del Mazo.
 *
 * Saca la primera carta de un Mazo.
 */
Card popC(Deck *a)
{
  return popAtPos(a, 0);
}

/**
 * Revolver un Mazo.
 */
void shuffle(Deck *a)
{
  int j; // Variable que tendrá el índice aleatorio para intercambiar cartas.
  // Inicializar semilla de random.
  srand(time(NULL));

  // Revolver usando algoritmo de Fisher-Yates
  // https://es.wikipedia.org/wiki/Algoritmo_de_Fisher-Yates
  for (int i = 0; i < a->noCards; i++)
  {
    // Elegir un número aleatorio entre 0 e `i`.
    j = rand() % (i + 1);
    // Intercambiar cartas.
    swapCard(&a->cards[i], &a->cards[j]);
  }
}

// Funciones de impresión de datos.

/**
 * Imprimir Ganador.
 */
void printWinner(Player a)
{
  printf("+--------------------------------+\n");
  printf("|              UNO               |\n");
  printf("| ¡El Ganador es %-14s! |\n", a.name);
  printf("|     ¡Muchas Felicidades!       |\n");
  printf("|                                |\n");
  printf("+--------------------------------+\n");
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

/**
 * Tomar una Carta.
 */
void takeCard(Player *p, Deck *r, Deck *game)
{
  // Validar que el mazo de robo tenga cartas.
  if (r->noCards <= 1)
  {
    // Copiar todas las cartas en el mazo de robo menos la última.
    for (int i = 0; i < (game->noCards - 1); i++)
    {
      pushC(r, game->cards[i]);
    }
    game->cards[0] = game->cards[game->noCards - 1];
    game->noCards = 1;
  }
  // Sacar una tarjeta del mazo de robo y añadirla al mazo del jugador.
  pushC(&p->deck, popC(r));
}

/**
 * Jugada Válida.
 */
int validPlay(Card a, Card b)
{
  // Mismo color.
  if (a.color == b.color)
  {
    return 1;
  }

  // Comodín Cambio de Color
  if (b.value == 13 || b.value == 14)
  {
    return 1;
  }

  // No es válido.
  return 0;
}

/**
 * Avanzar Turno
 */
void anotherTurn(int *curr, int players, int sentido)
{
  // Que no sea mayor o igual al número máximo de jugadores.
  if ((*curr + sentido) >= players)
  {
    *curr = 0;
  }
  // Que no sea menor a 0.
  else if ((*curr + sentido) < 0)
  {
    *curr = players - 1;
  }
  else
  {
    *curr += sentido;
  }
}