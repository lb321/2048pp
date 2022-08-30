FROM alpine:3.16.2

RUN apk update && \
    apk upgrade && \
    apk --update add \
        g++ \
        clang-dev \
        llvm \
        compiler-rt \
        alsa-lib-dev \
        mesa-dev \
        libx11-dev \
        libxrandr-dev \
        libxi-dev \
        libxcursor-dev \
        libxinerama-dev \
        libatomic \
        make \
        valgrind \
        git && \
    rm -rf /var/cache/apk/*