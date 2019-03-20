//para fork y pipes
#include <unistd.h>
//para salida estándar
#include <stdio.h>
//para wait
#include <sys/wait.h>
//para exit
#include <stdlib.h>
//para operar con cadenas
#include <string.h>

#define MAX 50

int esprimo(int a);

int main(){
  pid_t pidh, flag;
  int status;
  //buffer para leer y escribir
  char buff[MAX];
  //tubería
  int tub1[2];
  int tub2[2];
  //número bytes del buffer
  ssize_t nbytes;
  //cadenas para operar los números que irán por la tubería
  char primero[MAX], segundo[MAX], caux[MAX];
  //entero auxiliar
  int aux;

  //creamos la tubería
  status=pipe(tub1);
  if (status==-1) {
    fprintf(stderr, "No se pudo crear la tubería 1\n" );
    exit(EXIT_FAILURE);
  }
  status=pipe(tub2);
  if (status==-1) {
    fprintf(stderr, "No se pudo crear la tubería 2\n" );
    exit(EXIT_FAILURE);
  }

  pidh=fork();

  switch(pidh){
    case -1:
      fprintf(stderr, "[PADRE]: no he podido crear el hijo, saliendo...\n");
      exit(EXIT_FAILURE);
    break;
    case 0:
      //cerramos la escritura de la tubería 1
      if (close(tub1[1])==-1) {
        fprintf(stderr, "[HIJO]: Error al cerrar la tubería 1, saliendo\n");
        exit(EXIT_FAILURE);
      }
      //cerramos la lectura de la tubería 2
      if (close(tub2[0])==-1) {
        fprintf(stderr, "[HIJO]: Error al cerrar la tubería 2, saliendo\n");
        exit(EXIT_FAILURE);
      }

      nbytes=read(tub1[0],buff,MAX);
      if (nbytes==-1) {
        fprintf(stderr,"[HIJO]:Error al leer de la tubería 1\n");
        exit(EXIT_FAILURE);
      }else if(nbytes==0){
        printf("[HIJO]:Mi padre ha cerrado la tubería\n");
      }else{
        printf("[HIJO]:He leido %s de la tubería 1\n", buff );
      }

      //cerramos la lectura de la tubería 1
      if (close(tub1[0])==-1) {
        fprintf(stderr, "[HIJO]: Error al cerrar la tubería 1, saliendo\n");
        exit(EXIT_FAILURE);
      }

      //operamos con los números
      strcpy(primero, strtok(buff, ";"));
      strcpy(segundo, strtok(NULL, ";"));
      if((esprimo(atoi(primero)))&&(esprimo(atoi(segundo)))){//se comprueba que son primos
        if ((atoi(primero)==atoi(segundo)-2)||(atoi(primero)==atoi(segundo)+2))//se comprueba si son primos gemelos
          strcpy(caux, "gemelos");
        else
          strcpy(caux, "primos");
      }else
          strcpy(caux, "no-primos");

      //escribimos en la tubería
      if (write(tub2[1],caux,MAX)==-1) {
        fprintf(stderr, "[HIJO]: Error al escribir en la tubería 2\n" );
        exit(EXIT_FAILURE);
      }
      printf("[HIJO]: He escrito el resultado en la tubería 2\n");

      //cerramos la escritura de la tubería 2
      if (close(tub2[1])==-1) {
        fprintf(stderr, "[HIJO]: Error al cerrar la tubería 2, saliendo\n");
        exit(EXIT_FAILURE);
      }

      exit(EXIT_SUCCESS);
    default:
      //cerramos la lectura de la tubería 1
      if (close(tub1[0])==-1) {
        fprintf(stderr, "[PADRE]: Error al cerrar la tubería 1, saliendo\n");
        exit(EXIT_FAILURE);
      }
      //cerramos la escritura de la tubería 2
      if (close(tub2[1])==-1) {
        fprintf(stderr, "[PADRE]: Error al cerrar la tubería 2, saliendo\n");
        exit(EXIT_FAILURE);
      }
      //obtenemos los números y operamos con las cadenas
      printf("[PADRE]: Escribe dos números\n");
      scanf("%d",&aux);
      sprintf(primero,"%d",aux);
      scanf("%d",&aux );
      sprintf(segundo, "%d", aux);
      strcat(primero, ";");
      strcat(primero, segundo);
      strcpy(buff,primero);

      if (write(tub1[1],buff,MAX)==-1){
        fprintf(stderr,"[PADRE]: Error al escribir en la tubería 1\n" );
        exit(EXIT_FAILURE);
      }
      printf("[PADRE]: He escrito los dos números en la tubería 1\n");

      //cerramos la escritura de la tubería 1
      if (close(tub1[1])==-1) {
        fprintf(stderr, "[PADRE]: Error al cerrar la tubería 1, saliendo\n");
        exit(EXIT_FAILURE);
      }

      nbytes=read(tub2[0],buff,MAX);
      if (nbytes==-1) {
        fprintf(stderr,"[PADRE]:Error al leer de la tubería 2\n");
        exit(EXIT_FAILURE);
      }else if(nbytes==0){
        printf("[PADRE]:Mi hijo ha cerrado la tubería\n");
      }else{
        printf("[PADRE]:He leido %s de la tubería 2\n", buff );
      }
      //cerramos la lectura de la tubería 2
      if (close(tub2[0])==-1) {
        fprintf(stderr, "[PADRE]: Error al cerrar la tubería 2, saliendo\n");
        exit(EXIT_FAILURE);
      }
  }

  while ((flag=wait(&status))>0){
      if (WIFEXITED(status))
        printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
      else if (WIFSIGNALED(status)) //Para señales como las de finalizar o matar
        printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
      else if (WIFSTOPPED(status)) //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
        printf("Proceso Padre, Hijo con PID %ld parado al recibir la señal %d\n", (long int)flag, WSTOPSIG(status));
      else if (WIFCONTINUED(status)) //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
        printf("Proceso Padre, Hijo con PID %ld reanudado\n",(long int) flag);
  }
}

int esprimo(int a){
  int aux=0;
  for (int i = 1; i<a ; i++) {
    if (a%i==0) {
      aux++;
    }
  }
  if(aux>1)
    return 0;
  else
    return 1;
}
