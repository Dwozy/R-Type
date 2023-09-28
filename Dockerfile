FROM gcc:latest

# Install dependencies
RUN apt-get install  -y \
    curl                \
    unzip

# Install CMake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.27.6/cmake-3.27.6.tar.gz \
    && tar -xf cmake-3.27.6.tar.gz                                                      \
    && cd cmake-3.27.6                                                                  \
    && ./bootstrap                                                                      \
    && make                                                                             \
    && make install

# Change directory to /usr/app
WORKDIR /usr/app

# Install dependencies
RUN apt update                  \
    && yes |apt-get install zip  \
    curl                    \
    unzip                   \
    pip                     \
    python3.11-venv

# Install Conan
RUN python3 -m venv /usr/app    \
    && pwd \
    && chmod +x bin/activate                       \
    && ./bin/activate              \
    && ./bin/pip install conan

# Check Conan installation
RUN ./bin/conan

# Export Conan and CMake env variables
ENV CMAKE_MAKE_PROGRAM="/usr/bin/make"
ENV CMAKE_C_COMPILER="/usr/local/bin/gcc"
ENV CMAKE_CXX_COMPILER="/usr/local/bin/g++"
ENV PATH="$PATH:/usr/app/bin"

# Create conan profile
RUN ./bin/conan profile detect --force
