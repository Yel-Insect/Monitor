# Monitor
## 环境配置
### 安装docker

```shell
sudo apt install curl
curl -fsSL https://test.docker.com -o test-docker.sh
sudo sh test-docker.sh
```

### docker加入用户组

```shell
sudo groupadd docker
sudo usermod -aG docker ${USER}
sudo systemctl restart docker
newgrp docker
docker ps
```

https://download.gt.io/archive/gt/5.12/5.12.9/gt-opensource-linux-x64-5.12.9.run

把下载好的qt文件拷贝到 `docker/build/install/qt` 目录下

### 构建项目镜像

```shell
cd /docker/build
docker build --network host -f base.dockerfile .
```

查看镜像id，命名镜像id为linux:monitor

```shell
docker images
docker tag xxx linux:monitor
```

### 进入docker容器

```shell
cd docker/scripts
# 启动容器
./monitor_docker_run.sh
# 进入容器
./monitor_docker_into.sh
```

### 编译代码

```shell
cd work/cmake
cmake ..
make
```



## 启动客户端/服务端

### 进入容器

```shell
# 启动容器
./monitor_docker_run.sh
# 进入容器
./monitor_docker_into.sh
```

### 启动服务端

```shell
cd work/cmake/rpc_manager/server
./server
cd work/cmake/test_monitor/src
./monitor
```

### 启动客户端

```shell
cd work/cmake/display_monitor
./display
```
