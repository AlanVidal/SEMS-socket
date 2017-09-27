#include "common.h"
#include "chatroom.h"
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_CONN 10            // nombre maximale de requêtes en attentes

int DFLAG;
int srv_sock;
int BUF_SIZE = 250;

int create_a_listening_socket(char *srv_port){
    int s, sfd;

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;     
           hints.ai_socktype = SOCK_STREAM; 
           hints.ai_flags = AI_PASSIVE | AI_ALL;
           hints.ai_protocol = 0;          

    s = getaddrinfo(NULL,srv_port, &hints, &result);
  
    if(s != 0){
        perror("Get add Error");
        return -1;
    }
    
    for(rp = result ; rp != NULL ; rp = rp->ai_next){
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        
        if(sfd==-1){
            continue;
        }
        if(bind(sfd, rp->ai_addr, rp->ai_addrlen)==0){
            break;
            close(sfd);
        }        
    }
    if (rp == NULL) {              
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }
    
    freeaddrinfo(result); 
    listen(sfd,10);
  return sfd;
}


int accept_clt_conn(int srv_sock, struct sockaddr_in clt_sockaddr){
  int clt_sock =-1;

    if(!(clt_sock = accept(srv_sock,NULL,NULL))){
        return -1;
    }
    return clt_sock;
}


int main(void){
  int sfd;
  struct sockaddr_in clt_sockaddr;  

  DFLAG = 1;
    if( ! (sfd = create_a_listening_socket("5555"))){
        perror("pb init socket");       
    }
    

  while (1){
    int clt_sock = -1;
     char body[256];
     
    if(! (clt_sock = accept_clt_conn(sfd,clt_sockaddr))){
            perror("Erreur acpt");
    }
    if(!(recv(clt_sock, body, 256,0))){
        perror("Err msg cli");
    }
    DEBUG("resul : %s", body);
 
    
    /* register new buddies in the chat room */
    
  } /* while */

  return EXIT_SUCCESS;
}
