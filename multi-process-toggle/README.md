# multi-progress-toggle
多进程的并发服务器

### 编译 
```
gcc -o toggle_client toggle_client.c
gcc -o toggle_server toggle_server.c
``` 

### 开启服务器端与客户端
打开一个服务段终端，输入`./toggle_server 12345`开启服务器和12345端口进行监听  
打开第一个客户端终端，输入`./toggle_client localhost 12345`开启客户端与localhost：12345进行连接   
打开第二个客户端终端，输入`./toggle_client localhost 12345`开启客户端与localhost：12345进行连接

### 示例
![image](https://user-images.githubusercontent.com/49566726/118362001-46bbe780-b5c0-11eb-9806-a70c11df0e0c.png)
![image](https://user-images.githubusercontent.com/49566726/118362033-63f0b600-b5c0-11eb-8574-8da18a87851a.png)
![image](https://user-images.githubusercontent.com/49566726/118362055-710da500-b5c0-11eb-86eb-fb2fdbac7fce.png)
