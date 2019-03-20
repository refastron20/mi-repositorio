#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <regex.h>
#include <getopt.h>
#include <time.h>
#include <signal.h>
#include "common.h"

// Apuntador al fichero de log
FILE *fLog = NULL;
// Cola del servidor
mqd_t mq_server = -1;
// Cola del cliente
mqd_t mq_client = -1;
// Nombre para las colas
char clientQueue[100];
char serverQueue[100];

// Función que procesará el final
void finPrograma(int value);

void funcionLog(char *mensaje);

void imprimir_uso()
{
    printf("Uso del programa: ejercicio4-servidor [opciones]\n");
    printf("Opciones:\n");
    printf("-h, --help\t	Imprimir esta ayuda\n");
    printf("-r, --regex=EXPR\t	Expresión regular a utilizar\n");
}

int main(int argc, char **argv)
{
	/* Variables para el getopt */
	int hflag = 0;
	char *regexValue = NULL;
	int c;
	int option_index;
	static struct option long_options[] =
	{
		/* Opciones que no van a actuar sobre un flag */
		/* "opcion", recibe o no un argumento, 0,
		   identificador de la opción */
		{"regex",  required_argument,	   0, 'r'},
		{"help",     no_argument,	   0, 'h'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};

	/* Variables para la regex */
   regex_t regex;
	int reti;
   char msgbuf[100];

	// Atributos de la cola
	struct mq_attr attr;

	// Buffer para intercambiar mensajes
	char buffer[MAX_SIZE];

	// flag que indica cuando hay que parar
	int must_stop = 0;

	// Inicializar los atributos de la cola
	attr.mq_maxmsg = 10;        // Maximo número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Maximo tamaño de un mensaje

	// Nombre para las colas
	sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));

  if (signal(SIGINT, mi_manejador_sigint) == SIG_ERR)
        printf("No puedo asociar la señal SIGINT al manejador!\n");
    if (signal(SIGTERM, mi_manejador_sigterm) == SIG_ERR)
        printf("No puedo asociar la señal SIGTERM al manejador!\n");

	opterr = 0;

	while ((c = getopt_long (argc, argv, "hr:",long_options, &option_index))!=-1)
		switch (c)
		{
			case 'h':
        hflag=1;
        funcionLog("Servidor ejecutó la función de ayuda");
				imprimir_uso();
        exit(EXIT_SUCCESS);
				break;
			case 'r':
				regexValue = optarg;
				break;
			case '?':
				if (optopt == 'r'){
					fprintf (stderr, "La opción -%c requiere un argumento.\n", optopt);
          funcionLog("Se intentó iniciar sin añadir un mensaje a regex");
				}else if (isprint (optopt)){
					fprintf (stderr, "Opción desconocida `-%c'.\n", optopt);
          sprintf(msgbuf,"Opción desconocida `-%c'", optopt);
          funcionLog(msgbuf);
				}else{
					fprintf (stderr, "Carácter de opción desconocido `\\x%x'.\n", optopt);
          sprintf(msgbuf,"Carácter de opción desconocido `\\x%x'.", optopt);
          funcionLog(msgbuf);
					imprimir_uso();
        }
			default:
				exit(EXIT_SUCCESS);
		}

	if((regexValue==NULL)&&(hflag==0))
	{
    funcionLog("Se inició servidor sin argumentos");
	   imprimir_uso();
	   exit(EXIT_SUCCESS);
	}

	printf("Valor de regexvalue en servidor:%s\n",regexValue);
  sprintf(msgbuf,"Valor de regexvalue en servidor:%s",regexValue);
  funcionLog(msgbuf);

	/* Compilar la expresión regular */
	reti = regcomp(&regex, regexValue, 0);
   if( reti )
   {
		fprintf(stderr, "No pude compilar la expresión regular\n");
    funcionLog("No se pudo compilar la expresión regular");
		exit(EXIT_FAILURE);
	}


	// Crear la cola de mensajes del servidor
	mq_server = mq_open(serverQueue, O_CREAT | O_RDONLY, 0644, &attr);
	if( mq_server == (mqd_t)-1)
	{
     	perror("Error al abrir la cola del servidor");
      funcionLog("Error al abrir la cola del servidor");
   	exit(EXIT_FAILURE);
	}

	// Crear la cola de mensajes del cliente
	mq_client = mq_open(clientQueue, O_CREAT | O_WRONLY, 0644, &attr);
	if( mq_client == (mqd_t)-1)
	{
     	perror("Error al abrir la cola del cliente");
      funcionLog("Error al abrir la cola del cliente");
   	exit(EXIT_FAILURE);
	}

	do {
		// Número de bytes leidos
		ssize_t bytes_read;

		// Recibir el mensaje
		bytes_read = mq_receive(mq_server, buffer, MAX_SIZE, NULL);
		// Comprar que la recepción es correcto (bytes leidos no son negativos)
		if(bytes_read < 0)
		{
			perror("Error al recibir el mensaje");
      funcionLog("Error al recibir el mensaje");
			exit(EXIT_FAILURE);
		}

		// Cerrar la cadena
		//buffer[bytes_read] = '\0';

		// Comprobar el fin del bucle
		if (strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
			must_stop = 1;
		else
		{
			printf("Recibido el mensaje: %s\n", buffer);
			sprintf(msgbuf,"Recibido el mensaje: %s", buffer);
      funcionLog(msgbuf);

			/* Comprobar la expresión regular sobre la cadena pasada como argumento */
			reti = regexec(&regex, buffer, 0, NULL, 0);

		   // Puede servirnos, UNA VEZ COMPROBADA LA EXPRESION, por si al hacer pruebas hemos cerrado nuestro
		   // cliente y servidor, y se han quedado caracteres en los bufferes de entrada/salida estandar
		   fflush(stdout);                  // Limpiar buffer de salida
		   memset(buffer, 0, MAX_SIZE);     // Poner a 0 el buffer

			if(reti == 0)
			{
				strcpy(buffer,"Empareja");
			}
			else if( reti == REG_NOMATCH )
			{
				strcpy(buffer,"No Empareja");
			}
			else
			{
				regerror(reti, &regex, msgbuf, sizeof(msgbuf));
				fprintf(stderr, "Falló el matching de la expresión regular: %s\n", msgbuf);
        sprintf(msgbuf,"Falló el matching de la expresión regular: %s\n", msgbuf );
        funcionLog(msgbuf);
				strcpy(buffer,MSG_STOP);
			}

			// Enviar y comprobar si el mensaje se manda
			if(mq_send(mq_client, buffer, MAX_SIZE, 0) != 0)
			{
				perror("Error al enviar el mensaje");
        funcionLog("Error al enviar el mensaje");
				exit(-1);
			}
			sprintf(msgbuf,"Enviado el mensaje: %s", buffer);
      funcionLog(msgbuf);
		}
	// Iterar hasta que llegue el código de salida
	} while (!must_stop);

	// Cerrar el programa
	finPrograma(-1);

	/* Liberar la expresión regular utilizada */
	regfree(&regex);

	mq_client = mq_server = -1;
	exit(EXIT_SUCCESS);
}

void finPrograma(int value)
{
   char msgbuf[100];

	if(mq_client!=-1)
	{
		// Buffer para intercambiar mensajes
		char buffer[MAX_SIZE];
		strcpy(buffer,MSG_STOP);

		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_client, buffer, MAX_SIZE, 0) != 0)
		{
			perror("Error al enviar el mensaje");
      funcionLog("Error al enviar el mensaje");
			exit(EXIT_FAILURE);
		}
		sprintf(msgbuf,"Enviado el mensaje: %s", buffer);
    funcionLog(msgbuf);

		// Cerrar la cola del servidor
		if(mq_close(mq_client) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del cliente");
      funcionLog("Error al cerrar la cola del cliente");
			exit(EXIT_FAILURE);
		}
		// Eliminar la cola del cliente
		if(mq_unlink(clientQueue) == (mqd_t)-1)
		{
			perror("Error al eliminar la cola del cliente");
      funcionLog("Error al eliminar la cola del cliente");
			exit(EXIT_FAILURE);
		}
	}

	if(mq_server!=-1)
	{
		// Cerrar la cola del servidor
		if(mq_close(mq_server) == (mqd_t)-1)
		{
			perror("Error al cerrar la cola del servidor");
      funcionLog("Error al cerrar la cola del servidor");
			exit(EXIT_FAILURE);
		}
		// Eliminar la cola del servidor
		if(mq_unlink(serverQueue) == (mqd_t)-1)
		{
			perror("Error al eliminar la cola del servidor");
      funcionLog("Error al eliminar la cola del servidor");
    	exit(EXIT_FAILURE);
		}
	}

	mq_client = mq_server = -1;

	exit(EXIT_SUCCESS);
}

//Función auxiliar, escritura de un log.
void funcionLog(char *mensaje)
{
	int resultado;
	char nombreFichero[100];
	char mensajeAEscribir[300];
	time_t t;

	// Abrir el fichero
	sprintf(nombreFichero,"log-servidor.txt");
	if(fLog==NULL)
	{
		fLog = fopen(nombreFichero,"at");
		if(fLog==NULL)
		{
			perror("Error abriendo el fichero de log");
			exit(1);
		}
	}

	// Obtener la hora actual
	t = time(NULL);
	struct tm * p = localtime(&t);
	strftime(mensajeAEscribir, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

	// Vamos a incluir la hora y el mensaje que nos pasan
	sprintf(mensajeAEscribir, "%s ==> %s\n", mensajeAEscribir, mensaje);

	// Escribir finalmente en el fichero
	resultado = fputs(mensajeAEscribir,fLog);
	if (resultado < 0)
		perror("Error escribiendo en el fichero de log");

	fclose(fLog);
	fLog=NULL;
}
