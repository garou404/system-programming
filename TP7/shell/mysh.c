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

struct background_pro{
  char* cmd;
  pid_t pid;
  struct background_pro* next;
};

struct background_pro* list_processes;

// pid_t* backgrnd_processes;
int proc_nb = 0;

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

void print_linked_list(struct background_pro* linked_list){
  if(linked_list == NULL) { 
    printf("EMPTY LIST\n");
    return;
  }
  struct background_pro* cur_node = linked_list;
  while(cur_node->next != NULL) {
    printf("[%d]/%s -- ", cur_node->pid, cur_node->cmd);
    cur_node = cur_node->next;
  }
  printf("[%d]/%s\n", cur_node->pid, cur_node->cmd);
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
      printf("(in the background: process %d)\n", res_fork);
    }
  }
  
  struct background_pro* cur_node = list_processes;
  // printf("1.");
  // print_linked_list(list_processes);
  if(cur_node != NULL) {
    // printf("CUR_NODE != NULL\n");
    struct background_pro* next_node = list_processes->next;
    
    if(cur_node->next == NULL) {
      if (waitpid(cur_node->pid, 0, WNOHANG) > 0)
      {
        printf("[%d] Completed - %s\n", cur_node->pid, cur_node->cmd);
        free(cur_node->cmd);
        free(cur_node);
        list_processes = NULL;
      }
    }else {
      while((waitpid(cur_node->pid, 0, WNOHANG) > 0)) {
        printf("[%d] Completed - %s\n", cur_node->pid, cur_node->cmd);
        list_processes = next_node;
        free(cur_node->cmd);
        free(cur_node);
        cur_node = next_node;
        if(cur_node == NULL) {
          break;
        }
        next_node = cur_node->next;
      }
    }
    
    // printf("2.");
    // print_linked_list(list_processes);
    if(list_processes != NULL){
      while(cur_node->next != NULL) // to remove intermediate element in linked list
      {
        pid_t res_waitpid = waitpid(cur_node->next->pid, 0, WNOHANG);
        // printf("result wait pid : %d", res_waitpid);
        if (res_waitpid > 0) {
          printf("[%d] Completed - %s\n", cur_node->next->pid, cur_node->next->cmd);
          struct background_pro*node_to_del = cur_node->next;
          cur_node->next = cur_node->next->next;
          free(node_to_del);
        }else {
          cur_node = cur_node->next;
        }
      }
      // printf("3.");
      // print_linked_list(list_processes);
    }
    
  }

  if(c->mode == mode_background){
    // printf("waitpid : %d\n", res_fork);
    pid_t cur_res_wait = waitpid(res_fork, 0, WNOHANG);
    // printf("cur_res_wait : %d\n", cur_res_wait);
    if(cur_res_wait > 0) {
      printf("[%d] Completed - %s\n", res_fork, c->cmdline);
    }else {
      // create new struct
      struct background_pro* new_process = malloc(sizeof(struct background_pro));
      int i = 0;
      while(c->cmdline[i] != '\0'){
        i++;
      }
      new_process->cmd = malloc(sizeof(char)*(i+1));
      strcpy(new_process->cmd, c->cmdline);
      // printf("new_process->cmd %s\n", new_process->cmd);
      new_process->pid = res_fork;
      new_process->next = NULL;
      // printf("address cur_node: %p and new_process %p\n", cur_node, new_process);
      if(list_processes == NULL){
        list_processes = new_process;
        // printf("list_processes->pid %d\n", list_processes->pid);
        // printf("list_processes->cmd %s\n", list_processes->cmd);
      }else{
        // printf("cur_node->pid: %d\n",cur_node->pid);
        cur_node->next = new_process;
      }
    }
    // printf("address list_processes: %p\n", list_processes);
    // printf("4.");
    // print_linked_list(list_processes);
  }
}

// void free_linked_list(struct background_pro*list){
//   if(list != NULL){
//     while(list->next != NULL){

//     }
//   }
// }



int main(int argc, char** argv){
  // list_processes = malloc(sizeof(struct background_pro));
  list_processes = NULL;
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
      free(list_processes);
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
