#include "wrapper.h"

/**
 * 返回值：
 *     若成功，则为描述符；
 *     若UNIX出错，则为-1；
 *     若DNS出错，则为-2。
 */
int open_client_sock(char *hostname, int port){
    int client_sock;
    struct hostent *host_ip;
    struct sockaddr_in server_addr;

    //采用TCP协议进行通信
    if((client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){	
        return -1;
    }

    //域名解析
    if((host_ip = gethostbyname(hostname)) == NULL){	
        return -2;
    }

    //填写服务器的IP地址和端口
    bzero((char*)&server_addr, sizeof(server_addr));	//初始化，将字符串server_addr，前sizeof(server_addr)置为0
    server_addr.sin_family = AF_INET;
    bcopy((char*)host_ip->h_addr_list[0], (char*)&server_addr.sin_addr.s_addr, host_ip->h_length);
    server_addr.sin_port = htons(port);			//将端口从主机序变成网络序，sin_port只接受网络序
    
    //与服务器进行连接
    if(connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        return -1;
    }

    return client_sock;
}

int main(int argc, char **argv){
    int client_sock;
    int port;
    char *host;
    char buf[MAXLINE];

    if(argc != 3){
        fprintf(stderr, "usage:%s <host> <port>\n", argv[0]);
        return 1;
    }

    host = argv[1];
    port = atoi(argv[2]);

    client_sock = open_client_sock(host, port);

    while(fgets(buf, MAXLINE, stdin) != NULL){
        send(client_sock, buf, strlen(buf), 0);
        recv(client_sock, buf, MAXLINE, 0);
        fprintf(stdout, "%s\n", buf);
    }

    close(client_sock);

    return 0;
}
