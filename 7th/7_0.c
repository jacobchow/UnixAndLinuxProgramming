#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
volatile sig_atomic_t usr_interrupt = 0;

void sig_usr( int sig )
{
	usr_interrupt = 1;
}
void child_function()
{
	printf("i am child.\n");
	sleep(5);
	kill (getppid(), SIGUSR1);
	exit(0);
}
int main()
{
	pid_t child_id;
	signal(SIGUSR1, sig_usr);
	child_id = fork();
	if(child_id == 0)
		child_function();
	while(!usr_interrupt);
	puts("That's all.");
	return 0;
}
