#include "shell.h"


int execution(char buffer[]){
  char *argv1[N_ARG];
  separate(buffer, argv1, "\n ");
  if (!strcmp(argv1[0],"exit")){
    return 0;
  }
  else if (!strcmp(argv1[0],"pwd")) {
    char buff_path[N_BUFF];
    getcwd(buff_path, N_BUFF);
    printf("Chemin absolu : %s\n", buff_path);
  }
  else if (!strcmp(argv1[0],"cd")) {
    if(argv1[1] == NULL){
      chdir(getenv("HOME"));
    }
    else if(chdir(argv1[1]) == -1)
      perror("Chemin non valide");
  }
  else {
    int retour =  fork();
    switch (retour) {
      case -1:
        puts("Erreur");
        exit(-1);

      case 0: // enfant

        execvp(argv1[0], argv1);
        perror("pas executé ");
        exit(0);

      default: // parent
        waitpid(retour,NULL,0);
        break;
    }
  }
  return 1;
}
