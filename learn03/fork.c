#include<stdio.h>
#include<unistd.h>

int gval = 10;
int main(int argc, char *argv[])
{
	pid_t pid;
	int lval = 20;
	gval++, lval += 5;

	pid=fork();
	if(pid==0) //if child Process
		gval += 2, lval += 2;
	else
		gval -= 2, lval -= 2;

	printf("%d \n", pid);

	if(pid == 0)
		printf("Child Proc: [%d, %d] \n", gval, lval);
	else
		printf("Parant Proc: [%d, %d] \n", gval, lval);

	printf("oh!\n");
	return 0;
}
