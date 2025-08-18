#include "kernel/types.h"                                                                          
#include "kernel/stat.h"
#include "user/user.h"

void pipeline(int p[2]){
	int prime;
	read(p[0], &prime, sizeof(prime));
	if (prime == -1) exit(0);
	printf("prime %d\n", prime);

	int n[2];
	pipe(n);

	if (fork() == 0){
		close(n[1]);
		close(p[0]);
		pipeline(n);
		exit(0);
	}else{
		close(n[0]);
		int buffer;
		for (read(p[0], &buffer, sizeof(buffer)); buffer != -1; read(p[0], &buffer, sizeof(buffer))){
			if (buffer % prime != 0){
				write(n[1], &buffer, sizeof(buffer));
			}
		}
		buffer = -1;
		write(n[1], &buffer, sizeof(buffer));
	}
	wait(0);
	exit(0);
}

int
main(int argc, char* argv[])
{
	int p[2];
	pipe(p);

	if (fork() != 0){
		close(p[0]);
		int i;
    for (i = 2; i <= 35; i++){
      write(p[1], &i, sizeof(i));
    }
    i = -1;
    write(p[1], &i, sizeof(int));
	}else{
		close(p[1]);
		pipeline(p);
		exit(0);
	}
	wait(0);
	exit(0);
}
