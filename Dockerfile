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
    python3.11-venv         \
    libudev-dev             \
    libgl-dev               \
    libgl1-mesa-dev         \
    libx11-dev              \
    libx11-xcb-dev          \
    libfontenc-dev          \
    libice-dev              \
    libsm-dev               \
    libxau-dev              \
    libxaw7-dev             \
    libxcomposite-dev       \
    libxcursor-dev          \
    libxdamage-dev          \
    libxfixes-dev           \
    libxi-dev               \
    libxinerama-dev         \
    libxkbfile-dev          \
    libxmuu-dev             \
    libxrandr-dev           \
    libxres-dev             \
    libxss-dev              \
    libxtst-dev             \
    libxv-dev               \
    libxvmc-dev             \
    libxxf86vm-dev          \
    libxcb-render-util0-dev \
    libxcb-xkb-dev          \
    libxcb-icccm4-dev       \
    libxcb-image0-dev       \
    libxcb-keysyms1-dev     \
    libxcb-randr0-dev       \
    libxcb-shape0-dev       \
    libxcb-sync-dev         \
    libxcb-xfixes0-dev      \
    libxcb-xinerama0-dev    \
    libxcb-dri3-dev         \
    libxcb-cursor-dev       \
    libxcb-util-dev         \
    libxcb-util0-dev        \
    libopenal-dev           \
    libvorbis-dev           \
    libflac-dev

# Export CMake env variables
ENV CMAKE_MAKE_PROGRAM="/usr/bin/make"
ENV CMAKE_C_COMPILER="/usr/local/bin/gcc"
ENV CMAKE_CXX_COMPILER="/usr/local/bin/g++"
ENV PATH="$PATH:/usr/app/bin"
