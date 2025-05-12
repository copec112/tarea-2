# tarea-2

# Spotifind 🎵

Spotifind es una aplicación de consola escrita en C que permite cargar una base de datos de canciones desde un archivo `.csv` y realizar búsquedas por género, artista o tempo.

---

## ¿Cómo compilar y ejecutar?
### Compilar

```bash
gcc -o spotifind tarea2.c list.c map.c extra.c
````

###ejecutar
````bash
.\spotifind.exe   #
````

### funcionalidad y errores
Cargar Canciones	
Buscar por Artista	
Buscar por Género	
Buscar por Tempo	

cosas que no estan en Spotifind:

Crear listas personalizadas	
Guardar resultados
esto se debe que en esta version no fue obligacion tenerlas, ya que trabajo solo


posibles errores:

dependiendo del tamaño del archivo, puede que el computador, no pueda procesar todo el archivo o que este se demore mucho(esto me paso con un camputador menos potente y varios personas tuvieron la misma experiencia)


ejemplo

============= Spotifind =============
1) Cargar Canciones
2) Buscar por Artista
3) Buscar por Tempo
4) Buscar por Género
5) Salir
Ingrese su opción: 1
Ingrese la ruta del archivo CSV: song_dataset_.csv
Canciones cargadas exitosamente.

Ingrese su opción: 2
Ingrese el nombre del artista: Jason Mraz
[Se muestran todas las canciones de Jason Mraz]

Ingrese su opción: 3
Seleccione el tipo de tempo:
1) Lentas (< 80 BPM)
2) Moderadas (80 - 120 BPM)
3) Rápidas (> 120 BPM)
2
[Se muestran canciones con tempo moderado]

Ingrese su opción: 5
Saliendo de Spotifind...



