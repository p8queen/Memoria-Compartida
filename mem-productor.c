#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>

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

    printf("ingrese presiona una tecla y enter para cerrar la app\n");
    char buffer[25];
    scanf("%s",buffer);
    //cerrar
    shmdt(&litros);  //detach
	shmctl(shmid,IPC_RMID,NULL); //liberar
    return 0;
}
