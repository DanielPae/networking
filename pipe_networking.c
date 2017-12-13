#include "pipe_networking.h"
#define FIFO "eiofndkl"

/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo(FIFO, 0644);
  int FIFO1 = open(FIFO, O_RDONLY);
  char from_client[50];
  printf("Waiting for message from client\n");
  read(FIFO1, from_client, 50);
  printf("%s\n", from_client);
  *to_client = open(from_client, O_WRONLY);
  write(*to_client, "confirmation\n", 50);
  if(0 >= read(FIFO1, from_client, 50)){
    printf("no confirmation from client\n");
  }
  else printf("%s\n", from_client);
  unlink(FIFO);
  return FIFO1;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  *to_server = open(FIFO, O_WRONLY);
  mkfifo("Yes?", 0644);
  printf("Sending FIFO name to sever\n");
  write(*to_server, "Yes?", 5);
  int FIFO2 = open("Yes?", O_RDONLY);
  char from_server[50];
  printf("Waiting for message from server\n");
  read(FIFO2, from_server, 50);
  printf("%s\n", from_server);
  write(*to_server, "confirmation\n", 50);
  unlink("Yes?");
  return FIFO2;
}
