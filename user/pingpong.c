#include "kernel/types.h"                                                                          
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char* argv[])
{
	int pid;
	int p[2];

	pipe(p);

	if ((pid = fork()) == 0){
		int buffer;
		read(p[0], &buffer, sizeof(buffer));
		printf("%d: received ping\n", buffer);
		exit(0);
	}else{
		write(p[1], &pid, sizeof(pid));
		wait(0);
		printf("%d: received pong\n", getpid());
	}
	exit(0);
}
