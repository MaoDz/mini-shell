#include "advanced.h"
#include "shell.h"

int execEsperluette(char buffer[], int* pidtokill, int * pospid){
  char *argv1[N_ARG];

  // traitement du buffer
  separate(buffer, argv1, "\n &");

  // appel de la fonction exit_fork
  signal(SIGCHLD, exit_fork);

  int retour = fork();
  switch (retour) {
    case -1:
      puts("Erreur");
      exit(-1);

    case 0: // enfant

      execvp(argv1[0], argv1);
      perror("pas executé ");
      exit(0);

    default: // parent
      // enregistrement de l'enfant à tuer plus tard
      pidtokill[*pospid++]=retour;
      waitpid(retour, NULL, WNOHANG);
      //fputs(buffer, stdout);

      break;
  }

  return 1;
}


int execPipe(char buffer[]){
  int desc[2]; // futur entree et sortie du pipe
  char *args1[N_ARG];
  char *args2[N_ARG];

  // traitement du buffer
  separate2(buffer, args1, args2, "|");


  int pid1, pid2, status;
  if(pipe(desc))
  {
      perror("pipe creation failed");
      return(1);
  }
  // fork pour executer la commande avant '|'
  pid1 = fork();
  if(pid1 == -1){
    perror("PID1 failed");
    exit(1);
  }
  else if (pid1 == 0){
      // on redirige stdout
      dup2(desc[1], STDOUT_FILENO);
      close(desc[0]);
      close(desc[1]);
      execvp(args1[0], args1);
      perror("pid1 failed");
      exit(0);
  }
  else {
    // fork pour executer la commande après '|'
    pid2 = fork();
    if(pid2 == -1){
      perror("PID2 failed");
      exit(1);
    }
    else if(pid2 == 0){
      // on redirige stdin
      dup2(desc[0], STDIN_FILENO);
      close(desc[1]);
      close(desc[0]);
      execvp(args2[0], args2);
      perror("pid2 failed");
      exit(0);
    }
    else{
      // fermeture du pipe dans le parent
      close(desc[1]);
      close(desc[0]);
      waitpid(pid2, &status, 0);
    }
    waitpid(pid1, &status, 0);
  }
  return 1;
}


int execRedirect(char buffer[]){
  int retour;
  char *args1[N_ARG];
  char *args2[N_ARG];

  // traitement du buffer
  separate2(buffer, args1, args2, ">");

  retour = fork();
  if(retour == -1){
    perror("PID1 failed");
    exit(1);
  }
  else if (retour == 0){
    // ouverture du fichier de sortie
    FILE * f_sortie = fopen(args2[0], "w+");
    // redirection de stdout vers le fichier
    dup2(fileno(f_sortie), STDOUT_FILENO);
    fclose(f_sortie);
    execvp(args1[0], args1);
    perror("execvp failed");
    exit(0);
  }
  else {
    waitpid(retour, NULL, 0);
  }
  return 1;
}
