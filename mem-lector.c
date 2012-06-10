#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>



int main(int argc, const char *argv[])
{
    
    //attach
    key_t key  = ftok("/temp",40);
	int shmid = shmget(key, sizeof(int), 0660);  //leer mem 4 byte
    int *litros = (int*)shmat(shmid, NULL, 0);
    printf("cant litros: %d, litros fue attached, ingrese algo para continuar\n",*litros);
    char buffer[25];
    scanf("%s",buffer);
    
    //pedir 30 litros o los disponibles
    int cargados = 30;
    int disponibles;
    while(*litros>0){
      disponibles = *litros;
      if(*litros>=30)
          *litros -= 30;
      else{
          cargados = *litros;
          *litros = 0;
      }
      printf("litros, disponibles en memoria: %d cargados: %d\n",disponibles, cargados);
    }
    
    //esperar para detached
    printf("esperando detached, ingrese algo\n");
    scanf("%s",buffer);
    //detach
    shmdt(&litros);


    return 0;
}
