#include <sys/wait.h> /* system call - wait */
#include <stdint.h> /* system call - wait */
#include <stdlib.h> /* system call - exit */
#include <unistd.h> /* system call - fork, exec, sleep */
#include <stdio.h>

#define true 1
#define false 0

// Variaveis globais
int file1Open = true; /* Arquivo hipotetico 1 */
int file2Open = true; /* Arquivo hipotetico 2 */
int valor1 = 500;
int main()
{
pid_t pid;
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