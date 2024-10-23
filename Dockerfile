FROM ubuntu

RUN apt-get update && apt-get -y install \
    git gcc clang clang-tools gdb \
    valgrind check make ffmpeg \
    shellcheck python3.12

WORKDIR /labs
