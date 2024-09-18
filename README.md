# C Compiler

## Todo

- [ ] [低レイヤを知りたい人のためのCコンパイラ作成入門](https://www.sigbus.info/compilerbook) を読んで実装する
	- [x] [はじめに](https://www.sigbus.info/compilerbook#%E3%81%AF%E3%81%98%E3%82%81%E3%81%AB)
	- [ ]

## Environment

- macOS, M1
	- Docker インストール済み

## Log

### 2024-09-19: 作成したDocker環境に簡単に入るためのShellスクリプトを作成

次を毎回入力するのが面倒くさいので．
```bash
docker run -it --rm -v .:/c-compiler -w /c-compiler compilerbook
```

### 2024-09-19: Dockerを使ったLinux環境（x86-64）を作成

Dockerfileを次のように作成した
`linux/amd64`アーキテクチャを指定した

```Dockerfile
FROM --platform=linux/amd64 ubuntu:latest

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

### 2024-09-18: このリポジトリを作成



