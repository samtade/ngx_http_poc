#-------------------------------------------------------------------------------------------------------------
# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License. See https://go.microsoft.com/fwlink/?linkid=2090316 for license information.
#-------------------------------------------------------------------------------------------------------------

FROM debian:9

# Avoid warnings by switching to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# This Dockerfile adds a non-root 'vscode' user with sudo access. However, for Linux,
# this user's GID/UID must match your local user UID/GID to avoid permission issues
# with bind mounts. Update USER_UID / USER_GID if yours is not 1000. See
# https://aka.ms/vscode-remote/containers/non-root-user for details.
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Configure apt and install packages
RUN apt-get update \
    && apt-get -y install --no-install-recommends apt-utils dialog 2>&1 \
    # 
    # Verify git, process tools, lsb-release (useful for CLI installs) installed
    && apt-get -y install git iproute2 procps lsb-release curl \
    #
    # Install C++ tools
    && apt-get -y install build-essential cmake cppcheck valgrind \
    #
    # Install ngx_http_consule_backend_module need
    && apt-get -yqq install build-essential curl git libpcre3 libpcre3-dev libssl-dev zlib1g-dev \
    #
    # Create a non-root user to use if preferred - see https://aka.ms/vscode-remote/containers/non-root-user.
    && groupadd --gid $USER_GID $USERNAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
    # [Optional] Add sudo support for the non-root user
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    #
    # Clean up
    && apt-get autoremove -y \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

# Install Go
RUN cd /tmp \
    && curl -O https://dl.google.com/go/go1.12.5.linux-amd64.tar.gz \
    && tar xvf go1.12.5.linux-amd64.tar.gz \
    && chown -R root:root ./go \
    && mv go /usr/local \
    && export PATH="/usr/local/go/bin:$PATH" \
    && go version

ENV GOPATH /go

ENV GOBIN /usr/local/go/bin

ENV PATH $GOPATH/bin:/usr/local/go/bin:$PATH

# Install dep
RUN curl https://raw.githubusercontent.com/golang/dep/master/install.sh | sh

# Install Go for IntelliSense
RUN go get -u -v github.com/ramya-rao-a/go-outline \
    && go get -u -v github.com/acroca/go-symbols \
    && go get -u -v github.com/mdempsky/gocode \
    && go get -u -v github.com/rogpeppe/godef \
    && go get -u -v golang.org/x/tools/cmd/godoc \
    && go get -u -v github.com/zmb3/gogetdoc \
    && go get -u -v golang.org/x/lint/golint \
    && go get -u -v github.com/fatih/gomodifytags \
    && go get -u -v golang.org/x/tools/cmd/gorename \
    && go get -u -v sourcegraph.com/sqs/goreturns \
    && go get -u -v golang.org/x/tools/cmd/goimports \
    && go get -u -v github.com/cweill/gotests/... \
    && go get -u -v golang.org/x/tools/cmd/guru \
    && go get -u -v github.com/josharian/impl \
    && go get -u -v github.com/haya14busa/goplay/cmd/goplay \
    && go get -u -v github.com/uudashr/gopkgs/cmd/gopkgs \
    && go get -u -v github.com/davidrjenni/reftools/cmd/fillstruct \
    && go get -v github.com/ramya-rao-a/go-outline

# Download nginx source
RUN cd /tmp \
    && curl -sLo nginx.tgz https://nginx.org/download/nginx-1.12.2.tar.gz \
    && tar -xzvf nginx.tgz

ENV NGX_DIR /tmp/nginx-1.12.2

# Download ndk source
RUN cd /tmp \
    && curl -sLo ngx_devel_kit-0.3.0.tgz https://github.com/simpl/ngx_devel_kit/archive/v0.3.0.tar.gz \
    && tar -xzvf ngx_devel_kit-0.3.0.tgz

ENV NDK_DIR /tmp/ngx_devel_kit-0.3.0

# Create workspace
RUN mkdir -p /go/src

ENV WORK_DIR /go/src/app

# Create custom module directory
RUN mkdir -p /usr/local/nginx/ext

ENV EXT_DIR /usr/local/nginx/ext

ENV LD_LIBRARY_PATH /usr/local/nginx/ext:$LD_LIBRARY_PATH

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=
