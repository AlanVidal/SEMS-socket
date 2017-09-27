#include "common.h"
#include <signal.h>

char *srv_name = "localhost";
int clt_sock;

int DFLAG;

/* Établie une session TCP vers srv_name sur le port srv_port
 * char *srv_name: nom du serveur (peut-être une adresse IP)
 * int srv_port: port sur lequel la connexion doit être effectuée
 *
 * renvoie: descripteur vers le socket
 */ 
int connect_to_server(char *srv_name, char *srv_port){
  //struct hostent *host;
  //struct sockaddr_in sock_addr;
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int ret_code;
  
    
  //struct in_addr ip_addr;
  int clt_sock;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;     /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM; /* Stream socket */

  ret_code = getaddrinfo(srv_name, srv_port, &hints, &result);
  if ( ret_code != 0 ) 
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret_code));
      return -1;
    }

  for (rp = result; rp != NULL; rp = rp->ai_next) {
    clt_sock = socket(rp->ai_family, rp->ai_socktype,
		 rp->ai_protocol);
    if (clt_sock == -1) 
      continue; // 
    
    if (connect(clt_sock, rp->ai_addr, rp->ai_addrlen) != -1)
      break;         /* Connection succeeded */

    /* else try next entry */
    close(clt_sock);
  }
  
  if (rp == NULL){  /* No address succeeded */
    PERROR("socket");
    freeaddrinfo(result); /* no longer needed */
    return -1;
  }

  freeaddrinfo(result); /* no longer needed */

  return clt_sock;
}

int authenticate(int clt_sock){
  
//   while (1){
//     //unsigned char code;
//     unsigned char size;
//     char login[BUFFSIZE];
//     
//     // - attendre un paquet AUTH_REQ
// 
//     // - répondre avec un paquet AUTH_RESP
//      
//     // - attendre un paquet ACCESS_OK / ACCESS_DENIED / AUTH_REQ
// 
//     // - agir en conséquence ...
// 
//     
//     DEBUG("Login sent: %s(%d)", login, size);
//     
//   } /* while */
}

int instant_messaging(int clt_sock){
  
  while(1){
      
//       char test[256];
//       fgets(test, 256, stdin);
//       DEBUG("%s", test);
//       
//       if(!(send_msg(clt_sock,12, test, 256,0))){
//             perror("zaazea");
//     }
      
    fd_set rset;
    unsigned char code;
    unsigned char size;
    char *data;

    FD_ZERO(&rset);
    FD_SET(clt_sock, &rset);
    FD_SET(STDIN_FILENO, &rset);
    
    
    /* pour les étapes 2 à 4 se contenter de recevoir les messages
       envoyés par le serveur et les afficher à l'utilisateur
    */

    if (select(clt_sock+1, &rset, NULL, NULL, NULL) < 0){
        PERROR("select");
        exit(EXIT_FAILURE);
    }
    
    if (FD_ISSET(STDIN_FILENO, &rset)){
        /* l'utilisateur a tapé un nouveau message */
        DEBUG("STDIN_FILENO isset");
        data = malloc(BUFFSIZE);
        if (fgets(data, BUFFSIZE, stdin) == NULL){
            perror("Erreur stdin");
            return 0;
       }
        size = strlen(data)+1;
        DEBUG("sending MESG %s(%d)", data, size);
        
        free(data);
     }

      if (FD_ISSET(clt_sock, &rset)){
        
    }
 
    
  } /* while (1) */

  return 0;
}

int main(int argc, char *argv[]){
  // char srv_name[BUFFSIZE];
  char *srv_port = SRV_PORT;

  DFLAG = 1;

  clt_sock = connect_to_server(srv_name, srv_port);
  if (clt_sock < 0)
    exit(EXIT_FAILURE);

//   if (authenticate(clt_sock) < 0){
//     close(clt_sock);
//     eprintf("connexion closed\n");
//     exit(EXIT_FAILURE);
//   }

  if (instant_messaging(clt_sock) < 0){
    close(clt_sock);
    eprintf("connexion closed\n");
    exit(EXIT_FAILURE);
    }

  close(clt_sock);
  eprintf("connexion closed\n");
  exit(EXIT_SUCCESS);
}
