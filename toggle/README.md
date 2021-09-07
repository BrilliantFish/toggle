# toggle
单进程的网络服务器

### 编译
```
gcc -o toggle_client toggle_client.c
gcc -o toggle_server toggle_server.c
```

### 开启服务器端与客户端
打开一个终端，输入`./toggle_server 12345`开启服务器和12345端口进行监听  
打开另一个终端，输入`./toggle_client localhost 12345`开启客户端与localhost：12345进行连接  

### 示例
![image](https://user-images.githubusercontent.com/49566726/112716052-02e12600-8f1f-11eb-8243-ea6f6b111786.png)  
![image](https://user-images.githubusercontent.com/49566726/112716037-f0ff8300-8f1e-11eb-8a5c-68762ec34a4a.png)

### 缺点
单进程的服务器只能处理当个连接请求，过于普通！  
