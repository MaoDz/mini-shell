#include "shell.h"
#include "advanced.h"
#include "utile.h"

int main() {
  //char *argv1[N_ARG];

  char *buffer;
  buffer = (char*) malloc(sizeof(char)* N_BUFF);

  int esperluette = 0;
  int pipe = 0;
  int fleche = 0;

  int quit=1; // vaut 1 pour rester dans le while 0 pour le quitter
  int * pidtokill=calloc(N_PID,sizeof(int)); // tableau des pid à kill
  int pospid=0; // indice courant de la case pidtokill
  while (quit) {
    // Affiche le prompt et demande la commande à effectuer
    getBuff(buffer);

    if (buffer[0]!='\n') {
      for(int i=0; buffer[i]!='\0'; i++){
        //printf("%c\n",buffer[i]);
        if(buffer[i]=='&'){
          esperluette=1;
          //printf("esperluette\n");
          break;
        }
        if(buffer[i]=='|'){
          pipe=1;
          //printf("pipe\n");
          break;
        }
        if(buffer[i]=='>'){
          fleche=1;
          //printf("fleche\n");
          break;
        }
      }

      if(esperluette){
        //execution pour esperluette
        quit = execEsperluette(buffer, pidtokill, &pospid);
        //quit = execEsperluette(buffer);

        esperluette = 0;
      }

      else if(pipe){
        // execution pour pipe
        quit = execPipe(buffer);
        pipe = 0;
      }

      else if(fleche){
        // execution pour fleche
        quit = execRedirect(buffer);
        fleche = 0;
      }
      // execution standard
      else quit=execution(buffer);
    }
    else{
      // ne rien faire
    }
    fflush(stdout);
  }

  // tuer les enfants
  for(int j = 0; pidtokill[j]!=0; j++){
    //printf("pid %d tué\n",pidtokill[j] );
    kill(pidtokill[j], SIGKILL);
  }
  
// liberation de l'espace alloué
  free(buffer);
  free(pidtokill);

  return EXIT_SUCCESS;
}
