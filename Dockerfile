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
