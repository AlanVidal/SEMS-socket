#include "common.h"

/* send_msg send a message on socket sock
   sock: the socket
   code: message's protocol code
   size: message's size
   msg: message to be sent
*/
int send_msg(int sock, unsigned char code, unsigned char size, char *body) 
{
  msg_t msg;
  
  msg.code = code;
  msg.size = size;

  /* sending message head */
  if ( send(sock, &msg, HEADSIZE, 0) == -1) 
    {
      PERROR("sending message head failed");
      return -1;
    }
  
  /* sending message body if any */
  if ( (size != 0) && ((send(sock, body, size, 0)) == -1) ) 
    {
      PERROR("sending message body failed");
      DEBUG("error sending %s(%d)", body, size);
      return -1;
    }
  
  return size+HEADSIZE;
}

/* recv_msg recv a message from the socket sock
   sock: the socket
   code: message's protocol code
   size: message's size
   msg: message to be received
*/
int recv_msg(int sock, unsigned char *code, unsigned char *size, char **body) 
{
  msg_t msg;
  
  /* sending message head */
  if ( recv(sock, &msg, HEADSIZE, 0) <= 0) 
    {
      PERROR("receiving message head failed");
      return -1;
    }

  *code = msg.code;
  *size = msg.size;

  /* receiving message body if any */
  if ( *size == 0 ) 
    {
      DEBUG("body is empty");
      return HEADSIZE;
    }

  if (body == NULL) {
    PERROR("body is not empty but body pointer is NULL")
      return HEADSIZE;
  }

  *body = malloc((*size) * sizeof(char));
 
  /* sending message data if any */
  if ( (recv(sock, *body, *size, 0) <= 0) ) 
    {
      PERROR("receiving message body failed");
      free(*body);
      return -1;
    }
  
  return *size+HEADSIZE;
}
