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

    if(send(sock,&body,msg.size,1) <= 0){
        perror("pb msg");
        return -1;
    }else{printf("Msg ok");}

  
  
    
  return 0;
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
	if(recv(sock, &code,HEADSIZE, 0)){	
		perror("pb recv head");
	}
	
		if(recv(sock, &body,&size, 0)){	
		perror("pb recv body");
	}
	
        
  return 0;
}
