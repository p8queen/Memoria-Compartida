# Memoria Simple y con Semáforos

### Memoria Simple

En mem-productor.c crea una memoria para un integer.
carga 100 litros en memoria compartida 
Correr primero mem-productor.c y luego mem-lector.c
mem-lector resta 30 litros a la memoria compartida o 
toma todo, si hay menos de 30 litros. 

### Memoria carpeta semaforos

En mem-productor.c crea un semáforo contador, con 2 accesos. 
En mem-lector.c hay semáforo binario, para evitar que dos binarios, 
acceden al mismo tiempo a la memoria compartida. 

### Tips

#### Ver semáforo y Memoria

- $ ipcs -s
- $ ipcs -m

#### Borrar semáforo y Memoria

- $ ipcrm -s id-semaforo
- $ ipcrm -m id-memoria


