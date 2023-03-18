#ifndef ADVANCED_H
#define ADVANCED_H

#include "utile.h"

// EXECUTION ESPERLUETTE
int execEsperluette(char buffer[], int * pidtokill, int *pospid);

// EXECUTION REDIRECTION VERS PROGRAMME
int execPipe(char buffer[]);

// EXECUTION REDIRECTION VERS FICHIER
int execRedirect(char buffer[]);


#endif
