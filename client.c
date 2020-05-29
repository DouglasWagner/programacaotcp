#include <stdio.h>
#include <string.h> /* strlen */
#include <sys/socket.h>
#include <arpa/inet.h> /* inet_addr */

int main(int argc, char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char *message;

    /* AF_INET - IPv4, SOCK_STREAM - tcp, 0 - IP */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 

    if (socket_desc == -1)
    {
        printf("Não foi possível criar o socket\n");
        return 1;
    }

    /* 
    // IPv4 AF_INET sockets:
    struct sockaddr_in {
        short            sin_family;   // e.g. AF_INET, AF_INET6
        unsigned short   sin_port;     // e.g. htons(3490)
        struct in_addr   sin_addr;     // see struct in_addr, below
        char             sin_zero[8];  // zero this if you want to
    };

    struct in_addr {
        unsigned long s_addr;          // load with inet_pton()
    };

    struct sockaddr {
        unsigned short    sa_family;    // address family, AF_xxx
        char              sa_data[14];  // 14 bytes of protocol address
    };
    */
    /* informa os dados do servidor para onde vamos nos conectar */
    server.sin_addr.s_addr = inet_addr("172.217.28.132"); /* converte IP para long */
    server.sin_family = AF_INET; /* ip v4 */
    server.sin_port = htons(80);

    /* conecta-se ao servidor */
    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        printf("Erro ao conectar-se\n");
        return 1;
    }

    printf("Conectado.\n");

    /* envia dados */
    message = "GET / HTTP/1.1\r\n\r\n";
    if (send(socket_desc, message, strlen(message), 0) < 0)
    {
        printf("Erro ao enviar\n");
        return 1;
    }
    printf("Dados enviados.\n");

    return 0;
}