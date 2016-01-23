#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
static volatile sig_atomic_t sigflag = 0;

void sig_usr(int signo)
{
	psignal(signo, "	received");
}
void sig_intr(int signo)
{
	psignal(signo, "	received");
	sigflag = 1;
}
void wait_for_signal(int sig, volatile sig_atomic_t *sflag)
{
	static sigset_t mask1, oldmask1;
	sigemptyset( &mask1 );
	sigaddset(&mask1, sig);
	sigprocmask(SIG_BLOCK, &mask1, &oldmask1 );
	// sigdelset( &oldmask1, SIGUSR1 );
	// sigdelset( &oldmask1, SIGUSR2 );
	while(!*sflag)
	{
		printf("Door opened\n");
		sigsuspend( &oldmask1 );
		printf("Door closed\n");
	}
	*sflag = 0;
	sigprocmask(SIG_UNBLOCK, &mask1, NULL );

}
int main()
{
	pid_t pid;
	static sigset_t mask, oldmask;
	signal(SIGUSR1, sig_usr);
	signal(SIGUSR2, sig_usr);
	signal(SIGINT, sig_intr);
	// sigemptyset( &mask );
	// sigaddset( &mask, SIGUSR1 );
	// sigaddset( &mask, SIGUSR2 );
	// sigprocmask(SIG_BLOCK, &mask, &oldmask );
	pid =  fork();
	if (pid == 0)
	{
		kill( getppid(), SIGUSR1);
		kill( getppid(), SIGUSR2);
		printf("Child OK\n");
		sleep(5);
		kill ( getppid(), SIGINT );
		while(1);
	}
	else
	{
		wait_for_signal(SIGINT, &sigflag);
		printf("Now, I can do my work\n");
		kill (pid, SIGTERM);
	}
	exit(0);
}
