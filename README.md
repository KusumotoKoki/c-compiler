# C Compiler

## Todo

- [ ] [低レイヤを知りたい人のためのCコンパイラ作成入門](https://www.sigbus.info/compilerbook) を読んで実装する
	- [x] [はじめに](https://www.sigbus.info/compilerbook#%E3%81%AF%E3%81%98%E3%82%81%E3%81%AB)
	- [ ]

## Environment

- macOS, M1
	- Docker インストール済み

## Log

### 2024-09-18

#### このリポジトリを作成

#### Dockerを使ったLinux環境を作成

compilerbookの通りに次を実行した．

```bash
$ docker build -t compilerbook https://www.sigbus.info/compilerbook/Dockerfile
```

エラーが出てしまったので，Dockerfileを次のように作成した

```Dockerfile
FROM ubuntu:latest

# Update package lists and install necessary packages in one step
RUN apt-get update && \
	DEBIAN_FRONTEND=noninteractive apt-get install -y gcc make git binutils libc6-dev gdb sudo && \
	apt-get clean

# Add a new user without a password and give sudo access
RUN adduser --disabled-password --gecos '' user && \
	echo 'user ALL=(root) NOPASSWD:ALL' > /etc/sudoers.d/user

# Switch to the new user
USER user

# Set the working directory
WORKDIR /home/user
```

Docker.app を再起動して，次を実行した．
```bash
$  docker build -t compilerbook .
```




