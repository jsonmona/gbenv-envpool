FROM nvidia/cuda:12.5.1-cudnn-devel-ubuntu22.04

ARG DEBIAN_FRONTEND=noninteractive
ARG HOME=/root
ARG PATH=$PATH:$HOME/go/bin

RUN apt-get update \
    && apt-get install -y python3-pip python3-dev golang-1.18 git wget curl zsh tmux vim clang-format clang-tidy swig qtdeclarative5-dev sudo
RUN ln -s /usr/bin/python3 /usr/bin/python
RUN ln -sf /usr/lib/go-1.18/bin/go /usr/bin/go
WORKDIR $HOME

RUN useradd -ms /usr/bin/bash dev \
    && echo 'dev ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
USER dev
ARG HOME=/home/dev
WORKDIR /home/dev

RUN go install github.com/bazelbuild/bazelisk@latest && ln -sf $HOME/go/bin/bazelisk $HOME/go/bin/bazel \
    && go install github.com/bazelbuild/buildtools/buildifier@latest \
    && $HOME/go/bin/bazel version \
    && git config --global core.editor "code --wait"
ENV PATH="$PATH:/$HOME/go/bin"
