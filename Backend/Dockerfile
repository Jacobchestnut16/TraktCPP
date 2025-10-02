FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential cmake git \
    libssl-dev qtbase5-dev \
    libcurl4-openssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy only build files first for caching
COPY ../Cal/CMakeLists.txt ./
COPY ../Cal/include/ include/
COPY ../Cal/src/ src/
COPY ../Cal/config/ config/


RUN cmake -B build -S . && cmake --build build --config Release

EXPOSE 8080
CMD ["./build/Backend"]
