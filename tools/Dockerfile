FROM ubuntu:22.04

# Install necessary packages
RUN DEBIAN_FRONTEND=noninteractive \
	apt-get update \
	&& apt-get install -y wget bzip2 make unzip cppcheck clang-format git

# Create a non-root user named "ubuntu"
# But put in root group since Github actions needs perms to create tmp files
RUN useradd -rm -d /home/ubuntu -s /bin/bash -g root -G sudo -u 1001 ubuntu

USER ubuntu
WORKDIR /home/ubuntu

# Keep Docker container running
CMD ["tail", "-f", "/dev/null"]
