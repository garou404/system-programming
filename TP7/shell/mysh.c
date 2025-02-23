#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

enum command_mode {
  mode_background,
  mode_foreground
};

struct command{
  int argc;
  char**argv;
  char* cmdline;
  enum command_mode mode;
};

pid_t* backgrnd_processes;

/* create a command structure from a command line  */
struct command* extract_command(char* cmdline) {
  struct command* c = malloc(sizeof(struct command));
  c->argc = 0;
  c->argv = NULL;
  c->cmdline = malloc(sizeof(char)*(strlen(cmdline)+1));
  strcpy(c->cmdline, cmdline);

  /* first, let's count the number of parameters */
  char* token = strtok(cmdline, " ");
  while(token) {
    c->argc++;
    token = strtok(NULL, " ");
  }
  /* strtok modified cmdline, so let's restore it */
  strcpy(cmdline, c->cmdline);

  /* now, extract the parameters */
  c->argv = malloc(sizeof(char*) * (c->argc+1));
  c->argv[0] = strtok(cmdline, " ");
  int i;
  for(i=1; i<c->argc; i++) {
    c->argv[i] = strtok(NULL, " ");
  }

  if(c->argc && strcmp("&", c->argv[c->argc-1]) == 0) {
    c->argc--;
    c->mode = mode_background;
  } else {
    c->mode = mode_foreground;
  }
  c->argv[c->argc] = NULL;

  return c;
}

/* execute a command */
void execute_command(struct command* c) {
  if(c->argc == 0) {
    /* empty command, nothing to do */
    return;
  }
  pid_t res_fork = fork();

  if(!res_fork) {
    execvp(c->argv[0], c->argv);
  }else {
    if(c->mode == mode_foreground) {
      waitpid(res_fork, NULL, 0);
    }else{
      printf("(in the background: process %d)\n", getpid());
      // sleep(1);
    }
  }

  pid_t res_wait = waitpid(res_fork, NULL, WNOHANG);
  if(res_wait > 0) {
    printf("[%d] Completed\n", res_wait);
  }else{
    int i = 0;
    while(backgrnd_processes[i] != 0) {
      pid_t pid = waitpid(res_fork, NULL, WNOHANG);
      if (pid > 0) {
        printf("[%d] Completed\n", pid);
      }
      i++;
    }
  }
}

int main(int argc, char** argv){
  backgrnd_processes = malloc(sizeof(pid_t)*10);
  backgrnd_processes[0] = 0;
  do {
    char *cmdline = NULL;
    /* print a prompt, and return a buffer that contains the user command */
    cmdline = readline("mysh $ ");

    if(! cmdline) {
      /* received EOF */
      return EXIT_SUCCESS;
    }

    /* extract the command, and execute it */
    struct command* cmd = extract_command(cmdline);
    execute_command(cmd);

    if(cmd->argc > 0 && strcmp(cmd->argv[0] , "exit") == 0) {
      free(cmd->cmdline);
      free(cmd->argv);
      free(cmd);
      free(cmdline);
      return EXIT_SUCCESS;
    }


    /* cleanup */
    free(cmd->cmdline);
    free(cmd->argv);
    free(cmd);
    free(cmdline);
    cmdline = NULL;
  } while(1);

  return EXIT_SUCCESS;
}
