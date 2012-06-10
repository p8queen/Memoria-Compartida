#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/types.h>


void vsignal(int semid,int incremento){
    struct sembuf data;
    data.sem_num = 0;
    data.sem_flg = 0;
    data.sem_op = incremento;
    if(semop(semid,&data,1) == -1){
        perror("error semop");exit(-1);
        }
    }

int main(int argc, const char *argv[])
{
    //memoria litros int
    //crear memoria
    key_t key  = ftok("/temp",40);
	int shmid = shmget(key, sizeof(int), 0660|IPC_CREAT);  //crear mem 4 byte
    //attach y declaracion puntero
    int *litros = (int*)shmat(shmid, NULL, 0);
    //escribir
	*litros = 100;

    //crear semaf de 2 accesos 
    key_t keys  = ftok("/temp",50);
    int semid = semget(keys,1,IPC_CREAT|0660);
    semctl(semid,0,SETVAL,0); //en cero, no hay acceso
    //abro 2 lugares
    vsignal(semid,2);
    
    char buffer[25];
    printf("escribir para cerrar\n");
    scanf("%s",buffer);
    
    //cerrar
    shmdt(&litros);  //detach
	shmctl(shmid,IPC_RMID,NULL); //liberar
    semctl(semid,0,IPC_RMID); //liberar semaforo
    return 0;
}
