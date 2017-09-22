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
int BUF_SIZE = 500;

int create_a_listening_socket(char *srv_port){
  int srv_sock = -1;
    int s, sfd;
    ssize_t nread;
    char buf[BUF_SIZE];
    socklen_t peer_addr_len;
    struct sockaddr_storage peer_addr;


    struct addrinfo hints;
    struct addrinfo *result, *rp;
    memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;     
           hints.ai_socktype = SOCK_STREAM; 
           hints.ai_flags = 0;
           hints.ai_protocol = 0;          

    printf("Test");
    fflush(stdout);
    s = getaddrinfo(NULL,srv_port, &hints, &result);
    printf("Test2");
    fflush(stdout);
    
    if(s != 0){
        perror("Get add Error");
    }
    
    for(rp = result ; rp != NULL ; rp = rp->ai_next){
        sfd= socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        
        if(sfd==-1){
            continue;
        }
        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1){
            break;                 
            close(sfd);
        }        
    }
    
    if(bind(rp->ai_socktype, rp->ai_addr, rp->ai_addrlen)){
            perror("binding pb");
    }
    
    


  
 //   int socket(int AF_INET, int SOCK_STREAM, 8);

  

  /* Code nécessaires à la création d'une socket en
     écoute : 

     - appel à socket() 

     - appel à bind()

     - appel à listen()

     avec les bons paramètres et contrôles d'erreurs.

     La fonction retourne l'identifiant de la socket serveur ou -1 en
     cas d'erreur.
  */

  return srv_sock;
}

int accept_clt_conn(int srv_sock, struct sockaddr_in *clt_sockaddr){
  int clt_sock =-1;

  /* Code nécessaire à l'acception d'une connexion sur
     la socket en écoute (passée en argument via le paramètre srv_sock :
     
     - appel à accept()
     
     avec les bons paramètres et contrôles d'erreurs.
     
     La fonction retourne l'identifiant de la socket cliente ou -1 en
     cas d'erreur.
     
  */

  DEBUG("connexion accepted");

  return clt_sock;
}

int main(void) 
{
  
    DFLAG = 1;
    if( ! create_a_listening_socket("5555")){
        perror("pb init socket");
        
        
    }
  /* create a listening socket */
  
  /* initialize the chat room with no client */
    
  while (1){
    
    /* wait for new incoming connection */
    
    /* register new buddies in the chat room */
    
  } /* while */

  return EXIT_SUCCESS;
}
