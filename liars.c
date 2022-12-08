#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "gnl/get_next_line_bonus.h"

int main(int argc, char *argv[])
{
  pid_t child,  /* input reader process */
        // cmd,  /* command runner process */
        wres; /* wait() result */
  /* pipe for passing input from rdr to cmd */
  int pipefd[2] = {0};
  /* command and args to pass to execvp() */
  char *command = "cat";
  char *cmdargs[] = { "cat", NULL };
  /* end of input marker */
  char *endinp = "END\n";

  /* create a pipe: 
     - read end's fd will be pipefd[0], 
     - write end's fd will be pipefd[1] */
  pipe(pipefd);

  child = fork();
  if (!child) {  /* COMMAND RUNNER PROCESS */
    dup2(pipefd[0],0); /* set stdin to pipe's read end */
    close(pipefd[1]);  /* close pipe's write end */
    /* exec command (will read from stdin) */
    execvp(command, cmdargs);
  }

  child = fork();
  if (!child) {   /* INPUT READER PROCESS */
    close(pipefd[0]); /* close pipe's read end */

    /* read input from stdin until a line containing only
       the end of input marker is found */
    char *buf;
	while (1) {
      /* break when end of input marker is read */
	  buf = get_next_line(1);
      if (!strcmp(buf, endinp)) break;
      /* write data to pipe */
      write(pipefd[1],buf,strlen(buf));
    }
    return 0;
  }

  /* PARENT PROCESS */

  close(pipefd[0]); /* close pipe's read end */
  close(pipefd[1]); /* close pipe's write end */
	while (waitpid(-1, &child, 0) > 0)
		;
  /* wait for both children to exit */
//   do {
//     wres = wait(NULL);
//     if (wres == rdr) rdr = 0;
//     if (wres == cmd) cmd = 0;
//   } while (rdr || cmd);

  return 0;
}