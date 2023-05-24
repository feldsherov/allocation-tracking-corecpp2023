FROM ubuntu:20.04

# Update the package manager and install necessary dependencies
RUN apt-get update
RUN ln -fs /usr/share/zoneinfo/America/Los_Angeles /etc/localtime && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        clang cmake libgtest-dev libgoogle-perftools-dev git ca-certificates build-essential && \
    dpkg-reconfigure --frontend noninteractive tzdata

# Clone Google Benchmark repository
RUN git clone https://github.com/google/benchmark.git

# Build and install Google Benchmark
RUN git config --global advice.detachedHead false && cd benchmark && git checkout tags/v1.8.0 && \ 
    cmake -E make_directory build && \
    cmake -E chdir build cmake .. -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on && \
    cmake --build build --config Release --target install

# Clean up
RUN rm -rf benchmark

# Set the default working directory
WORKDIR /workdir