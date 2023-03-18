#ifndef UTILE_H
#define UTILE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <signal.h>
#include <errno.h>


#define N_BUFF 2048
#define N_ARG 256
#define N_PID 2048

// SIGNAL
void exit_fork();


// FONCTIONS
void getBuff(char buffer[]);

// Permet de separer le buffer pour executer une ou deux commande(s)
void separate(char buffer[], char *argv1[], const char * separators);
void separate2(char buffer[], char *args1[], char *args2[], const char* separators);


#endif
