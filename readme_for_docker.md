# Запуск ЛР по си из-под докера

Для начала создадим Dockerfile
```docker
FROM ubuntu

RUN apt-get update && apt-get -y install \
    git gcc clang clng-tools gdb \
    valgrind check make ffmpeg \
    shellcheck python3.12

WORKDIR /labs
```
