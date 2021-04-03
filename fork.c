#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void err_sys(char* message)
{
perror(message);
exit(EXIT_FAILURE);
}

void main(int argc,char* argv[] ){
pid_t pid,ppid,child_pid;
int i,status;

pid=getpid();
printf("Parent. My PID is : %d, procrate\n",pid);
fflush(stdout);

for(int i=0;i<3;i++){
child_pid=fork();
if(child_pid<0){
err_sys("fork");
}
if(child_pid==0){
break;
}
}

if(child_pid==0){
pid=getpid();
ppid=getppid();
printf("Child.My PID is : %d and my parent PID is : %d \n",pid,ppid);
sleep(1);
exit(i);
}
printf("Parent. Wait for my children\n");
while((child_pid=wait(&status))!=-1){
printf("Child %d is terminated status %d \n",child_pid,status);

if(WIFEXITED(status)){
printf("Termination normal exit status %d \n",WEXITSTATUS(status));
}
}
return EXIT_SUCCESS;
}
