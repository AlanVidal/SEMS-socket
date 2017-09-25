#include "common.h"
#include <signal.h>
#include <pthread.h>


char *srv_name = "localhost";
int clt_sock;

int DFLAG;

/* Établie une session TCP vers srv_name sur le port srv_port
 * char *srv_name: nom du serveur (peut-être une adresse IP)
 * int srv_port: port sur lequel la connexion doit être effectuée
 *
 * renvoie: descripteur vers le socket
 */ 
int connect_to_server( int srv_port){
  //int clt_sock = -1;
  int s,sfd;
  
    printf("Client connect init\n");

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    memset(&hints, 0, sizeof(struct addrinfo));
           hints.ai_family = AF_UNSPEC;     
           hints.ai_socktype = SOCK_STREAM; 
           hints.ai_flags = 0;
           hints.ai_protocol = 0;          
   
  s = getaddrinfo(NULL,"5555", &hints, &result);
  
  if(s != 0){
    perror("Get add Error");
    return -1;
  }
    
  for(rp = result ; rp != NULL ; rp = rp->ai_next){
        sfd= socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if(sfd==-1){
        continue;
        }
    if(connect(sfd, rp->ai_addr, rp->ai_addrlen)==0){
         break;
         close(sfd);
        
        }

    }
  printf("Client connect \n");
    return sfd;

}


int authenticate(int clt_sock){

  /* Code nécessaire à l'authentification auprès du serveur :

     - attendre un paquet AUTH_REQ

     - répondre avec un paquet AUTH_RESP
     
     - attendre un paquet ACCESS_OK / ACCESS_DENIED / AUTH_REQ

     - agir en conséquence ...

  */

  return -1;
}

int instant_messaging(int clt_sock){
  
  while(1){
    /*    fd_set rset;
    unsigned char code;
    unsigned char size;
    char *data;

    FD_ZERO(&rset);
    FD_SET(clt_sock, &rset);
    FD_SET(STDIN_FILENO, &rset);
    */
    
    /* pour les étapes 2 à 4 se contenter de recevoir les messages
       envoyés par le serveur et les afficher à l'utilisateur
    */

    // if (select(clt_sock+1, &rset, NULL, NULL, NULL) < 0){
    //   PERROR("select");
    //   exit(EXIT_FAILURE);
    // }
    
    // if (FD_ISSET(STDIN_FILENO, &rset)){
    /* l'utilisateur a tapé un nouveau message */
    //   DEBUG("STDIN_FILENO isset");
    //   data = malloc(BUFFSIZE);
    //   if (fgets(data, BUFFSIZE, stdin) == NULL){
    	/* gérer feof et ferror */

   //   <COMPLÉTER>
    
    // 	return 0;
    //   }
    //   size = strlen(data)+1;
      
    //   DEBUG("sending MESG %s(%d)", data, size);

    //  <COMPLÉTER>

    //   free(data);
      
    // }

    //  if (FD_ISSET(clt_sock, &rset)){
      /* réception d'un message du serveur */
      /* expected: <code><datalen>[<data>] */

      //  <COMPLÉTER>
      
    //}
    
  } /* while (1) */

  return 0;
}

int main(int argc, char *argv[]){
    int srv_port = 5555;
    int serveur ;
    char buff[256];
    printf("Client main");
    
   serveur =  connect_to_server(srv_port);
    DFLAG = 1;
    char body[256];
    recv(serveur, body, sizeof(body, 0));
//     recv_msg(serveur, 1, sizeof(body),body );
    printf("%s",buff);

  // connect to the server

  // authenticate

  // start instant messaging app
  
  exit(EXIT_SUCCESS);
}
