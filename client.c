#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  char input_string[256];
  while (1) {
    printf("Input a string\n");
    fgets(input_string, sizeof(input_string), stdin);
    write(to_server, input_string, strlen(input_string));
    read(from_server, input_string, 256);
    printf("Received modification: %s\n", input_string);
  }
}
