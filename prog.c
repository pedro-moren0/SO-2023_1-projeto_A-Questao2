#include <sys/wait.h> /* system call - wait */
#include <stdint.h> /* system call - wait */
#include <stdlib.h> /* system call - exit */
#include <unistd.h> /* system call - fork, exec, sleep */
#include <stdio.h>
#include <signal.h>

#define true 1
#define false 0

void interruption_handler(int signum);
void terminate_handler(int signum);
void polite_exit_setup();

// Variaveis globais
int file1Open = true; /* Arquivo hipotetico 1 */
int file2Open = true; /* Arquivo hipotetico 2 */
int valor1 = 500;

int main()
{
pid_t pid;
    signal(SIGINT, interruption_handler);
    signal(SIGTERM, terminate_handler);

    pid = fork();
    if (!pid)
    {
        printf( "Sou o FILHO. %d\n", getpid() );
        return 0;
    }
    else if (pid)
    {
        printf( "Sou o PAI. %d\n", getpid() );
        valor1 /= 20;
        wait(NULL);
        while (1);
        printf("O status do file1Open eh %d e o file2Open eh %d \n", file1Open,
        file2Open);
        printf(" O valor1 = %d\n",valor1);
        return 0;
    }
}

/*
 * Handler function for the interruption signal.
 *
 * Params: The signal number
 * Return: None
 */
void interruption_handler(int signum){
    char response;
    printf("\nDeseja realmente interromper o processo? ");
    scanf("%c", &response);
    
    if(response == 'x' || response == 'X') {
        polite_exit_setup();
        exit(EXIT_FAILURE);
    }
}

/*
 * Handler function for the terminate signal.
 *
 * Params: The signal number
 * Return: None
 */
void terminate_handler(int signum){
    polite_exit_setup();
    exit(EXIT_FAILURE);
}

/*
 * Routine to soft exit this program.
 * Closes the open files and informs the value of valor1.
 *
 * Params: None
 * Return: None
 */
void polite_exit_setup(){
    file1Open = false;
    file2Open = false;
    printf("Closed all files.\n");
    printf("Value of valor1 before closing = %d\n", valor1);
}