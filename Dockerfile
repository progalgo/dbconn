# syntax=docker/dockerfile:1

FROM fedora

# Install build tools and psql-odbc library
RUN dnf install -y psqlodbc unixODBC-devel g++ make git cmake

# Install nanodbc for C++ classes encapsulating ODBC model
RUN git clone https://github.com/nanodbc/nanodbc.git && \
    cd nanodbc && \
    mkdir build && \
    cd build && \
    cmake .. && \
    cmake --build . && \
    make install

WORKDIR /app
COPY . .
RUN make
