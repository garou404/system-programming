#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "server_code_etudiant.h"
#include <time.h>

// client_t *clients[MAX_CLIENTS];
struct linked_list* ll;

struct node {
  client_t* client;
  struct node* next;
};

struct linked_list {
  int length;
  struct node* root;
};

/* Strip CRLF */
void strip_newline(char *s) {
  while(*s != '\0'){
    if(*s == '\r' || *s == '\n'){
      *s = '\0';
    }
    s++;
  }
}

client_t *get_client_from_fd(int fd) {
  // printf("get_client_from_fd(int fd)---------------------------\n");
  if(ll->root){
    if(ll->root->client->fd == fd){
      return ll->root->client;
    }else{
      struct node* cur = ll->root;
      while(cur->next != NULL){
        if(cur->next->client->fd == fd){
          return cur->next->client;
        }
        cur = cur->next;
      }
      printf("Could not find the client with this fd %d\n", fd);
      return NULL;
    }
  }else{
    printf("cannot find client, client list is empty\n");
    return NULL;
  }


  // old get_client_from_fd
  // int i;
  // for(i=0; i<MAX_CLIENTS; i++) {
  //   if(clients[i] && clients[i]->fd == fd)
  //     return clients[i];
  // }
  // return NULL;
}

client_t *get_client_from_name(char* name) {
  // printf("get_client_from_name(char* name)---------------------------\n");

  if(ll->root){
    if(ll->root->client->name == name){
      return ll->root->client;
    }else{
      struct node* cur = ll->root;
      while(cur->next != NULL){
        if(cur->next->client->name == name){
          return cur->next->client;
        }
        cur = cur->next;
      }
      // printf("Could not find the client with this name %s\n", name);
      return NULL;
    }
  }else{
    // printf("cannot find client, client list is empty\n");
    return NULL;
  }


  // old get_client_from_name
  // int i;
  // for(i=0; i<MAX_CLIENTS; i++) {
  //   if(clients[i]) {
  //     if(strcmp(clients[i]->name, name) == 0) {
	// return clients[i];
  //     }
  //   }
  // }
  // return NULL;
}

void server_init() {
  // printf("server_init()---------------------------\n");

  // new init
  ll = malloc(sizeof(struct linked_list));
  ll->length = 0;
  ll->root = NULL;

  // old init
  // memset(clients, 0, sizeof(client_t*)*MAX_CLIENTS);
}

/* Add client to queue */
void queue_add(client_t *cl){
  // printf("queue_add(client_t *cl)-------------------\n");
  if(ll->root){
    struct node* cur = ll->root;
    while(cur->next){
      cur = cur->next;
    }
    cur->next = new_node(cl);
  }else{
    ll->root = new_node(cl);
  }
  ll->length++;
}

struct node* new_node(client_t* cl){
  // printf("new_node(client_t cli)\n");
  struct node* new_node = malloc(sizeof(struct node));
  new_node->client = cl;
  new_node->next = NULL;
  return new_node;
}

void free_clients_list(){
  if(ll->root) free_node(ll->root);
  free(ll);
}

void free_node(struct node* n){
  if(n->next){
    free_node(n->next);
  }
  free(n);
}

/* Delete client from queue */
void queue_delete(client_t *client){
  // printf("queue_delete(client_t *client)\n");
  if(ll->root){
    if(ll->root->client->uid == client->uid){
      struct node* del = ll->root;
      ll->root = ll->root->next;
      free(del);
      return;
    }else{
      struct node* cur = ll->root;
      while(cur->next->client->uid != client->uid){
        cur = cur->next;
      }
      struct node* del = cur->next;
      cur->next = cur->next->next;
      free(del);
      return;
    }
  }else{
    printf("cannot delete client, client list is empty\n");
    return;
  }
  

  // old queue delete
  // int i;
  // for(i=0;i<MAX_CLIENTS;i++){
  //   if(clients[i]){
  //     if(clients[i]->uid == client->uid){
	// clients[i] = NULL;
	// return;
  //     }
  //   }
  // }
}

/* Send a message to a client */
void send_message(char *s, client_t *client){
  fwrite(s, sizeof(char), strlen(s), client->client_conn);
}

/* Send message to all clients */
void send_message_all(char *s){
  // printf("send message(char* s)\n");
  if(ll->root){
    struct node*cur = ll->root;
    while(cur != NULL){
      send_message(s, cur->client);
      cur = cur->next;
    }
  }

  // old send_message_all
  // int i;
  // for(i=0;i<MAX_CLIENTS;i++){
  //   if(clients[i]){
  //     send_message(s, clients[i]);
  //   }
  // }
}

void assign_default_name(client_t* cli) {
  FILE* f = fopen("default_names.txt", "r");
  fseek(f, 0, SEEK_END); 
  long file_size = ftell(f);
  if(f){
    srand(time(NULL));
    char name[32];
    do
    {
      int offset = rand() % file_size/32;
      fseek(f, offset*32, SEEK_SET); // move the cursor to random location in file
      fgets(name, 32, f);
    } while (get_client_from_name(name));
    
    sprintf(cli->name, "%s", name);
  }else{
    printf("Could not open the file default_names.txt\n");
    sprintf(cli->name, "Anonymous_%d", cli->uid);
  }
  // int line = rand() % ;
}

/* this function is called when a client connects to the server */
void say_hello(client_t *cli) {
  // printf("SAY HELLO;\n");
  char buff_out[1024];
  /* choose a default name */
  assign_default_name(cli);
  sprintf(buff_out, "* %s joins the chatroom\n", cli->name);
  send_message_all(buff_out);
}

void process_cmd_me(client_t*client, char*param){
  // param: /me something ...
  char buff_out[1024]; 
  if(param){
    sprintf(buff_out, "* %s %s\n", client->name, param);
    send_message_all(buff_out);
  }else{
    sprintf(buff_out, "* %s doesn't feel anything anymore\n", client->name);
    send_message_all(buff_out);
  }
}

void process_cmd_msg(client_t*client,
		     char*param) {
  char*dest = strsep(&param, " ");
  if(!dest){
    send_message("* to who ?\n", client);
    return;
  }

  char buffer[1024];
  sprintf(buffer, "[PM][%s --> %s] %s\n", client->name, dest, param);
  client_t* to = get_client_from_name(dest);
  if(!to ){
    send_message("* %s does not exist!\n", client);
  } else {
    send_message(buffer, to);
    send_message(buffer, client);
  }
}

void process_cmd_help(client_t* client) {
  char buff_out[1024];
  sprintf(buff_out, "/help     Show help\n");
  strcat(buff_out, "/msg      <name> <message> Send private message\n");
  strcat(buff_out, "/ping     Server test\n");
  strcat(buff_out, "/quit     Quit chatroom\n");
  send_message(buff_out, client);
}

void process_cmd_ping(client_t* client,
		      char* param) {
  send_message("* pong\n", client);
}

void handle_incoming_cmd(client_t *cli) {
  char buff_out[1024];
  char buff_in[1024];

  if(fgets(buff_in, 1024*sizeof(char), cli->client_conn) == 0) {
    if(!feof(cli->client_conn)) {
      perror("read failed");
      abort();
    } else {
      printf("Client %s disconnected\n", cli->name);
      queue_delete(cli);
      return;
    }
  }

  strip_newline(buff_in);

  /* Ignore empty buffer */
  if(!strlen(buff_in)){
    printf("Empty message\n");
  }

  /* Special options */
  char *cmd_line = buff_in;
  if(buff_in[0] == '/'){
    char *command;
    command = strsep(&cmd_line," ");
    if(!strcmp(command, "/quit")){
      free_clients_list();
      return;
    } else if(!strcmp(command, "/ping")) {
      process_cmd_ping(cli, cmd_line);
    } else if(!strcmp(command, "/msg")) {
      process_cmd_msg(cli, cmd_line);
    } else if(!strcmp(command, "/me")) {
      process_cmd_me(cli, cmd_line);
    } else {
      /* /help or unknown command */
      process_cmd_help(cli);
    }
  }else{
    /* Send message */
    sprintf(buff_out, "[%s] %s\n", cli->name, cmd_line);
    send_message_all(buff_out);
  }
}
