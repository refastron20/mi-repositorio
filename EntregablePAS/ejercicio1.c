//para getopt, optind, opterr, optopt, optarg
#include <unistd.h>
//para salida y entrada estándar
#include <stdio.h>
//librería estándar de c
#include <stdlib.h>
//para getopt_long
#include <getopt.h>
//estructuras y funciones para info de usuarios
#include <pwd.h>
//estructuras y funciones para info de grupos
#include <grp.h>
//para usar isdigit()
#include <ctype.h>
//para las cadena
#include <string.h>


int main(int argc, char *argv[]) {
  //El siguiente código se usaría si se permitiesen solo opciones de un sólo caracter
/*  int uflag=0;

    while((c=getopt(argc, argv, "u"))!=-1){
    switch (c) {
      case 'u':
        //activamos el flag de u si esta ha sido escrita por comandos
        uflag=1;
      break;
      default:
        abort();
    }
  }*/

  //variable para ir guardando los comandos
  int c;

  //estructuras para información de usuario y grupos
  struct passwd *pw;
  struct group *gp;

  //estructura para las opciones
  static struct option opciones[] =
	{
		//"opcion", recibe o no un argumento, 0, identificador de la opción
		{"username",required_argument, 0, 'u'},
    {"useruid", required_argument, 0, 'i'},
    {"groupname", required_argument, 0, 'g'},
    {"groupuid", required_argument, 0, 'd'},
    {"allgroups", no_argument, 0, 's'},
    {"allinfo", required_argument, 0, 'a'},
    {"bactive", no_argument, 0, 'b'},
    {"help", no_argument, 0, 'h'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};
  //opterr es una variable externa incluida en unistd
  //se inicializa opterr a 0 para especificar que no hay errores
  opterr=0;

  //flags y variables para las ordenes de la línea de comandos
  char* uValue=NULL;
  char* iValue=NULL;
  char* gValue=NULL;
  char* dValue=NULL;
  char* aValue=NULL;
  int sFlag=0;
  int hFlag=0;
  int bFlag=0;
  //variable para errores
  int error=0;
  //Para guardar el índice de la orden
  int indice_opciones=0;
  //para controlar que no se introduzcan más argumentos de la cuenta
  int index;
  while((c=getopt_long(argc, argv, "u:i:g:sa:bhd:", opciones, &indice_opciones))!=-1){
    if (c==-1)
      break;
    switch (c) {
      case 'u':
        //le asignamos el valor de argumento a la variable de u
        //optarg guarda el argumento de la orden
        uValue=optarg;
        break;
      case 'i':
        iValue=optarg;
      break;
      case 'g':
        gValue=optarg;
      break;
      case 'd':
        dValue=optarg;
      break;
      case 's':
        sFlag=1;
      break;
      case 'a':
        aValue=optarg;
      break;
      case 'b':
        bFlag=1;
      break;
      case 'h':
        hFlag=1;
      break;
      case '?':
        //optopt recoge el valor de la opción cuando es desconocida
        if(optopt=='u'||optopt=='i'||optopt=='g'||optopt=='d'||optopt=='a')
          error=1;
      break;
      default:
        abort();
    }
  }

  if (hFlag!=0||error==1) {
    if (error==1) {
      printf("Error al introducir algún comando\n");
    }
    printf(" Lista de opciones válidas: \n");
    printf("-u/--username: información del usuario especificando el nombre\n");
    printf("-i/--useruid: información del usuario especificando el ID\n");
    printf("-g/--groupname: información del grupo especificando el nombre\n");
    printf("-d/--groupuid: información del grupo especificando el ID\n");
    printf("-s/--allgroups: información de todos los grupos del sistema\n");
    printf("-a/--allinfo: información del usuario y grupo al que pertenece especificando el nombre\n");
    printf("-b/--bactive: información del grupo actual\n");
    printf("-h/--help: información de las funcionalidades del programa\n");
  }else{
    if ((uValue!=NULL)&&(iValue==NULL)) {
      //getpwnam() devuelve una estructura con la info del usuario pasado (nombre de usuario) o NULL si no existe
      if ((pw=getpwnam(uValue))==NULL)
        fprintf(stderr, "-u: No existe el usuario \n" );
      else{
        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Password: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Home: %s\n", pw->pw_dir);
        printf("Número de grupo principal: %d\n", pw->pw_gid);
      }
    }
    if (iValue!=NULL&&uValue==NULL) {
      //getpwuid() devuelve una estructura con la info del usuario pasado (id de usuario) o NULL si no existe
      if(!isdigit(*iValue))
        fprintf(stdout, "'%s' no es un UID válido\n", iValue );
      else if ((pw=getpwuid(atoi(iValue)))==NULL)
        fprintf(stdout, "-i: No hay ningún usuario con ese identificador \n" );
      else{
        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Password: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Home: %s\n", pw->pw_dir);
        printf("Número de grupo principal: %d\n", pw->pw_gid);
      }
    }
    if (gValue!=NULL&&dValue==NULL) {
      if ((gp=getgrnam(gValue))==NULL)
        fprintf(stdout, "-g: No hay ningún grupo con ese nombre \n" );
      else{
        printf("Nombre: %s\n", gp->gr_name);
        printf("GID: %d\n", gp->gr_gid);
      }
    }
    if (dValue!=NULL&&gValue==NULL) {
      if(!isdigit(*dValue))
        fprintf(stdout, "'%s' no es un GID válido\n", dValue );
      else if (((gp=getgrgid(atoi(dValue)))==NULL))
        fprintf(stdout, "-d: No hay ningún grupo con ese nombre \n" );
      else{
        printf("Nombre: %s\n", gp->gr_name);
        printf("GID: %d\n", gp->gr_gid);
      }
    }
    if(sFlag!=0&&(dValue==NULL||gValue==NULL||uValue==NULL||iValue==NULL||aValue==NULL||bFlag==0)){
      FILE* f;
      char aux[50], *aux2;
      if((f=fopen( "/etc/group", "r"))==NULL)
        fprintf(stderr, "Error al abrir el archivo\n");

      while (fgets(aux, 50, f)!=NULL) {
        aux2=strtok(aux, ":");
        gp=getgrnam(aux2);
        printf("Nombre: %s\n", gp->gr_name);
        printf("GID: %d\n", gp->gr_gid);
      }

      fclose(f);
    }
    if (aValue!=NULL&&(dValue==NULL||gValue==NULL||uValue==NULL||iValue==NULL||sFlag==0||bFlag==0)) {
      if ((pw=getpwnam(aValue))==NULL)
        fprintf(stdout, "-a: No existe el usuario \n" );
      else{
        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Password: %s\n", pw->pw_passwd);
        printf("Home: %s\n", pw->pw_dir);
        gp=getgrgid(pw->pw_gid);
        printf("Nombre de grupo: %s\n", gp->gr_name);
        printf("GID: %d\n", gp->gr_gid);
      }
    }
    if (bFlag!=0&&(dValue==NULL||gValue==NULL||uValue==NULL||iValue==NULL||sFlag==0||aValue==NULL)) {
      pw=getpwnam(getenv("USER"));
      gp=getgrgid(pw->pw_uid);
      printf("Nombre de grupo: %s\n", gp->gr_name);
      printf("GID: %d\n", gp->gr_gid);
    }
  }
  for (index = optind; index < argc; index++)
      printf ("Argumento \"%s\" de la línea de comandos que NO ES UNA OPCIÓN.\n", argv[index]);
  return 0;
}
