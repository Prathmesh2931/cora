# Used Ubuntu 22.04 to match modern Jetson Orin deployments (JetPack 6)
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libeigen3-dev \
    liblapack-dev \
    libblas-dev \
    libsuitesparse-dev \
    libgoogle-perftools-dev \
    google-perftools \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY . .

RUN git submodule update --init

RUN mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release \
          -DENABLE_VISUALIZATION=OFF \
          -DENABLE_PROFILING=ON \
          -DBUILD_EXAMPLES=ON .. && \
    make -j3 cora_vis

CMD ["/bin/bash", "-c", "cd build && /usr/bin/time -v ./bin/cora_vis"]