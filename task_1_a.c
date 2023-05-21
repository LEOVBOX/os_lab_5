#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global_var = 3;

int main()
{
	int local_var = 1;

	printf("local_var address = %x; local_var value = %d\n", &local_var, local_var);
	printf("global_var address = %x; global_var value = %d\n", &global_var, global_var);
	pid_t pid = getpid();
	printf("pid = %d\n", pid);

	pid_t fork_pid = fork();
	if (fork_pid == -1)
	{
		printf("fork() error\n");
		return 1;
	}

	// Дочерний процесс
	else if (fork_pid == 0)
	{
		printf("I'm child process\n");
		pid_t pid = getpid();
		printf("pid = %d\n", pid);
		pid_t ppid = getppid();
		printf("ppid = %d\n", ppid);
		exit(5);
	}

	// Родительский процесс
	else
	{
		printf("I'm parent process\n"
			   "local_var address = %x; local_var value = %d\n"
			   "global_var address = %x; global_var value = %d\n",
				&local_var, local_var, &global_var, global_var);

		sleep(30);
		int status;
		pid_t childPid = wait(&status);

		if (WIFEXITED(status)) {
			printf("Дочерний процесс с идентификатором %d завершился с кодом %d\n", childPid, WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("Дочерний процесс с идентификатором %d завершился неперехватываемым сигналом %d\n", childPid, WTERMSIG(status));
		}

	}


	return 0;
}
