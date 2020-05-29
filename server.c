#include <netinet/in.h>
#include <stdio.h>
#include <string.h> /* strlen */
#include <sys/socket.h>
#include <arpa/inet.h> /* inet_addr */
#include <unistd.h> /* close */

int main(int argc, char *argv[])
{
    int socket_desc, c, new_socket;
    struct sockaddr_in server, client;

    /* abre um socket */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 
    if (socket_desc == -1)
    {
        printf("Não foi possível criar o socket\n");
        return 1;
    }

    /* onde quero ouvir ? */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; /* escute em qualquer IP da máquina */
    server.sin_port = htons(8888);

    /* vincula o socket à porta e ao endereço informados */
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        printf("Erro ao fazer o bind\n");
        return 1;
    }

    printf("Bind efetuado.\n");

    /* escutar */
    listen(socket_desc, 3);

    /* aceitar conexões entrantes */
    printf("Aguardando conexões...\n");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c);
    if (new_socket < 0) 
    {
        printf("Erro ao aceitar conexão\n");
        return 1;
    }

    char *client_ip = inet_ntoa(client.sin_addr);
    int client_port = ntohs(client.sin_port);

    printf("conexão aceita do client %s:%d\n", client_ip, client_port);


    return 0;
}