#include "extra.h"
#include "list.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char id[100];
  List *artists;
  char album_name[200];
  char track_name[200];
  float tempo;
  char genre[100];
} Song;

void mostrarCancion(Song *s) {
  printf("ID: %s\n", s->id);
  printf("Nombre: %s\n", s->track_name);
  printf("Artistas:\n");
  for (char *a = list_first(s->artists); a != NULL; a = list_next(s->artists))
    printf("  - %s\n", a);
  printf("album: %s\n", s->album_name);
  printf("Genero: %s\n", s->genre);
  printf("Tempo: %.2f BPM\n", s->tempo);
  puts("---------------------------");
}

void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("============= Spotifind =============");
  puts("1) Cargar Canciones");
  puts("2) Buscar por Artista");
  puts("3) Buscar por Tempo");
  puts("4) Buscar por Genero");
  puts("5) Salir");
}

// Mapas globales
Map *canciones_por_artista;
Map *canciones_por_genero;
List *todas_las_canciones;
List *tempos_lentos;
List *tempos_moderados;
List *tempos_rapidos;

int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

void cargar_canciones() {
  char ruta[200];
  printf("Ingrese la ruta del archivo CSV: ");
  scanf(" %[^\n]", ruta);

  FILE *archivo = fopen(ruta, "r");
  if (!archivo) {
    perror("No se pudo abrir el archivo");
    return;
  }

  leer_linea_csv(archivo, ','); // saltar encabezado
  char **campos;

  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    Song *s = malloc(sizeof(Song));
    strcpy(s->id, campos[0]);
    s->artists = split_string(campos[2], ";");
    strcpy(s->album_name, campos[3]);
    strcpy(s->track_name, campos[4]);
    s->tempo = atof(campos[18]);
    strcpy(s->genre, campos[20]);

    list_pushBack(todas_las_canciones, s);

    // Insertar en mapas por artista
    for (char *a = list_first(s->artists); a != NULL; a = list_next(s->artists)) {
      MapPair *pair = map_search(canciones_por_artista, a);
      List *lista = pair ? pair->value : NULL;

      if (!lista) {
        lista = list_create();
        map_insert(canciones_por_artista, strdup(a), lista);
      }
      list_pushBack(lista, s);
    }

    // Insertar en mapas por género
    MapPair *pair_gen = map_search(canciones_por_genero, s->genre);
    List *lista_genero = pair_gen ? pair_gen->value : NULL;

    if (!lista_genero) {
      lista_genero = list_create();
      map_insert(canciones_por_genero, strdup(s->genre), lista_genero);
    }
    list_pushBack(lista_genero, s);

    // Clasificación por tempo
    if (s->tempo < 80)
      list_pushBack(tempos_lentos, s);
    else if (s->tempo <= 120)
      list_pushBack(tempos_moderados, s);
    else
      list_pushBack(tempos_rapidos, s);
  }

  fclose(archivo);
  printf("Canciones cargadas exitosamente.\n");
}

void buscar_por_artista() {
  char artista[200];
  printf("Ingrese el nombre del artista: ");
  scanf(" %[^\n]", artista);

  MapPair *pair = map_search(canciones_por_artista, artista);
  List *resultados = pair ? pair->value : NULL;

  if (!resultados) {
    printf("No se encontraron no se encontro al artista '%s'\n", artista);
    return;
  }

  for (Song *s = list_first(resultados); s != NULL; s = list_next(resultados))
    mostrarCancion(s);
}

void buscar_por_genero() {
  char genero[100];
  printf("Ingrese el genero: ");
  scanf(" %[^\n]", genero);

  MapPair *pair = map_search(canciones_por_genero, genero);
  List *resultados = pair ? pair->value : NULL;

  if (!resultados) {
    printf("No se encontraron canciones del genero '%s'\n", genero);
    return;
  }

  for (Song *s = list_first(resultados); s != NULL; s = list_next(resultados))
    mostrarCancion(s);
}

void buscar_por_tempo() {
  int opcion;
  puts("Seleccione el tipo de tempo:");
  puts("1) Lentas (< 80 BPM)");
  puts("2) Moderadas (80 - 120 BPM)");
  puts("3) Rápidas (> 120 BPM)");
  scanf("%d", &opcion);

  if (opcion == 1) 
  {
    for (Song *s = list_first(tempos_lentos); s != NULL; s = list_next(tempos_lentos))
      mostrarCancion(s);
  } 
  else if (opcion == 2) 
  {
    for (Song *s = list_first(tempos_moderados); s != NULL; s = list_next(tempos_moderados))
      mostrarCancion(s);
  } 
  else if (opcion == 3) 
  {
    for (Song *s = list_first(tempos_rapidos); s != NULL; s = list_next(tempos_rapidos))
      mostrarCancion(s);
  }
}

int main() {
  canciones_por_artista = map_create(is_equal_str);
  canciones_por_genero = map_create(is_equal_str);
  todas_las_canciones = list_create();
  tempos_lentos = list_create();
  tempos_moderados = list_create();
  tempos_rapidos = list_create();

  char opcion;
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_canciones();
      break;
    case '2':
      buscar_por_artista();
      break;
    case '3':
      buscar_por_tempo();
      break;
    case '4':
      buscar_por_genero();
      break;
    case '5':
      puts("Saliendo de Spotifind...");
      break;
    default:
      puts("Opcion invalida.");
    }

    if (opcion != '5')
      presioneTeclaParaContinuar();

  } while (opcion != '5');

  return 0;
}