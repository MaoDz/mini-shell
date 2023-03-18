#include "utile.h"

// SIGNAL POUR PROCESSUS ARRIERE PLAN
void exit_fork(){
  pid_t pid;
  // permet d'obtenir une adresse a chaque appel de exit_fork
  int stat;
  while(1){
    pid = wait3(&stat, WNOHANG, NULL);
    if((pid == -1) || (pid == 0)){
      break;
    }
    else{
      //printf("PID : %d mort\n", pid);
    }
  }
}

// OBTENTION DE LA CHAINE EN ENTREE
void getBuff(char buffer[]){
// Affiche le chemin courant
  char buff_path[N_BUFF];
  getcwd(buff_path, N_BUFF);
  printf("%s: ", buff_path);
  printf("$ ");

// recuperation de l entree stdin
  fgets(buffer, N_BUFF, stdin);
}

// FONCTIONS DE SEPARATIONS
void separate(char buffer[], char *argv1[], const char * separators){

  char * strToken = strtok (buffer, separators);

  int i = 0;
  while ( strToken != NULL ) {
      argv1[i] = strToken;
      //printf("%d, %s\n",i, argv1[i]);
      i++;

      // On demande le token suivant.
      strToken = strtok ( NULL, separators );
  }
  // le dernier argument en entrée de execvp doit etre NULL
  argv1[i] = NULL;
}

void separate2(char buffer[], char *args1[], char *args2[], const char* separators){
  // copie du buffer pour le conserver identique a l entree
  // char buff_temp[N_BUFF];
  // strcpy(buff_temp, buffer);

  char *arg_temp[N_ARG];

  // On cherche à récupérer, un à un, tous les mots (token) de la phrase
  // et on commence par le premier.
  char * strToken = strtok (buffer, separators);

  int i = 0;
  while ( strToken != NULL ) {
      arg_temp[i] = strToken;
      //printf("%d, %s\n",i, arg_temp[i]);
      i++;

      // On demande le token suivant.
      strToken = strtok ( NULL, separators );
  }

  /****************************
  ************ARGS1************
  ****************************/
    // Separateurs
    const char * separators_bis = "\n ";

    char * strToken1 = strtok (arg_temp[0], separators_bis);

    i = 0;
    while ( strToken1 != NULL ) {
        args1[i] = strToken1;
        //printf("1 : %d, %s\n",i, args1[i]);
        i++;
        strToken1 = strtok ( NULL, separators_bis );
    }
    // le dernier argument en entrée de execvp doit etre NULL
    args1[i] = NULL;

    /****************************
    ************ARGS2************
    ****************************/
    char * strToken2 = strtok (arg_temp[1], separators_bis);

    i = 0;
    while ( strToken2 != NULL ) {
        args2[i] = strToken2;
        //printf("2 : %d, %s\n",i, args2[i]);
        i++;
        strToken2 = strtok ( NULL, separators_bis );
    }
    args2[i] = NULL;
}
