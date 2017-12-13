#include "pipe_networking.h"
#include <ctype.h>

int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
  char input_string[256];
  read(from_client, input_string, 256);
  printf("Recieved: %s\n", input_string);
  int index = 0;
  while (index < strlen(input_string)) {
    toupper(input_string[index]);
    index++;
  }
  write(to_client, input_string, strlen(input_string));
}
