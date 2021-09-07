# multi-thread-toggle
多线程的并发服务器

### 编译
```
gcc -o toggle_client toggle_client.c
gcc -o toggle_server toggle_server.c -lpthread
```

### 开启服务器端与客户端
打开一个服务段终端，输入`./toggle_server 12345`开启服务器和12345端口进行监听  
打开第一个客户端终端，输入`./toggle_client localhost 12345`开启客户端与localhost：12345进行连接  
打开第二个客户端终端，输入`./toggle_client localhost 12345`开启客户端与localhost：12345进行连接  

### 示例
![image](https://user-images.githubusercontent.com/49566726/118386954-a44a4580-b64d-11eb-8e88-898639eb23bb.png)
![image](https://user-images.githubusercontent.com/49566726/118386957-b330f800-b64d-11eb-9a47-e66c5baf2f0a.png)
![image](https://user-images.githubusercontent.com/49566726/118386960-bf1cba00-b64d-11eb-8c34-7ed6a648f88c.png)
