FROM ubuntu

RUN apt-get update && apt-get -y install \
    git gcc clang clng-tools gdb \
    valgrind check make ffmpeg \
    shellcheck python3.12

WORKDIR /labs