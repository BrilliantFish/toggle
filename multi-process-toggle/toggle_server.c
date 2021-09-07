#include "wrapper.h"

/*
 * 接受客户端消息，并返回接受成功的消息"receive success"给客户端
 */
void toggle(int connect_sock){
    int n;
    int i;
    char buf[MAXLINE];
    char message[] = "receive success";

    while((n = recv(connect_sock, buf, MAXLINE, 0)) > 0){
        printf("toggle server received %d bytes : %s", n, buf);
        send(connect_sock, message, MAXLINE, 0);
        bzero((char*)&buf, sizeof(buf));
    }
}

/**
 * 返回值：
 *     若成功，则为描述符；
 *     若UNIX出错，则为-1；
 */
int open_listen_sock(int port){
    int server_sock;
    int optval = 1;
    struct sockaddr_in server_addr;

    //创建一个socket描述符
    if((server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        return -1;
    }

    //当使用close(server_sock)关闭socket时，并不会立刻关闭，而是经过一个TIME_WAIT的过程
    if(setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int)) < 0){
        return -1;
    }
    
    //设置服务器指定的端口port可以监听所有的请求
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   //INADDR_ANY指0.0.0.0
    server_addr.sin_port = htons((unsigned int)port);

    //将socket描述符与server_addr进行绑定
    if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        return -1;
    }

    //将socket描述符转化为监听状态，准备用于接受连接请求
    if(listen(server_sock, LISTENQ) < 0){
        return -1;
    }
    
    return server_sock;    
}


void sigchld_handler(int sig){
    while(waitpid(-1, 0, WNOHANG) > 0)
        ;
    
    return ;
}

int main(int argc, char **argv){
    int server_sock;
    int connect_sock;
    socklen_t client_len = sizeof(struct sockaddr_in);
    int port;
    struct sockaddr_in client_addr;	//记录客户端IP信息
    //struct hostent *client_host_ptr;	//查询客户端名称

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
    }

    port = atoi(argv[1]);

    signal(SIGCHLD, sigchld_handler);
    
    server_sock = open_listen_sock(port);
    
    while(1){
        connect_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);

        if(fork() == 0){	//子进程
            close(server_sock);
            toggle(connect_sock);
            close(connect_sock);
            exit(0);
        }
	//父进程
        close(connect_sock);
    }
    
    return 0;
}
