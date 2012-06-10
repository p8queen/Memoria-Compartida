#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>


void vsignal(int semid,int incremento){
    struct sembuf data;
    data.sem_num = 0;
    data.sem_flg = 0;
    data.sem_op = incremento;
    if(semop(semid,&data,1) == -1){
        perror("error semop");exit(-1);
        }
    }
void pwait(int semid,int decremento){
    struct sembuf data;
    data.sem_num = 0;
    data.sem_flg = 0;
    data.sem_op = -decremento;
    if(semop(semid,&data,1) == -1){
        perror("error semop");exit(-1);
        }
    }

//Para ejecutar 
//   ./mem-lector numAuto 
int main(int argc, const char *argv[])
{
    
    //attach
    key_t key  = ftok("/temp",40);
	int shmid = shmget(key, sizeof(int), 0660);  //leer mem 4 byte
    int *litros = (int*)shmat(shmid, NULL, 0);
    printf("cant litros: %d, litros fue attached\n",*litros);
    
    //acceso a semaforo
    key_t keys  = ftok("/temp",50);
    int semid = semget(keys,1,0660);
    
    printf("soy auto %d esperando entrar a cargar\n", atoi(argv[1]));
    //resta un lugar para entrar
    pwait(semid,1);
    //pedir 40 litros o los disponibles
    int cargados = 40;
    int disponibles;
      disponibles = *litros;
      if(*litros>=cargados)
          *litros -= cargados;
      else{
          cargados = *litros;
          *litros = 0;
      }
      printf("litros, disponibles en memoria: %d cargados: %d\n",disponibles, cargados);
    sleep(15);
    //suma al semaforo un lugar al salir
    vsignal(semid,1);
    printf("final de carga\n\n");
    //detach
    shmdt(&litros);
    return 0;
}
