FROM fedora:38

RUN dnf -y upgrade                          \
        && dnf -y install dnf-plugins-core  \
        && dnf -y --refresh install         \
        --setopt=tsflags=nodocs             \
        --setopt=deltarpm=false             \
        autoconf                            \
        automake                            \
        ca-certificates.noarch              \
        clang.x86_64                        \
        clang-analyzer                      \
        cmake.x86_64                        \
        curl.x86_64                         \
        gcc-c++.x86_64                      \
        gcc.x86_64                          \
        gdb.x86_64                          \
        git                                 \
        glibc-devel.x86_64                  \
        glibc-locale-source.x86_64          \
        glibc.x86_64                        \
        langpacks-en                        \
        libX11-devel.x86_64                 \
        libXext-devel.x86_64                \
        libXrandr-devel.x86_64              \
        libXinerama-devel.x86_64            \
        libXcursor-devel.x86_64             \
        libXi-devel.x86_64                  \
        libjpeg-turbo-devel.x86_64          \
        libtsan                             \
        libuuid libuuid-devel               \
        llvm.x86_64                         \
        llvm-devel.x86_64                   \
        ltrace.x86_64                       \
        make.x86_64                         \
        nasm.x86_64                         \
        net-tools.x86_64                    \
        nc                                  \
        openal-soft-devel.x86_64            \
        openssl-devel                       \
        patch                               \
        procps-ng.x86_64                    \
        python3.x86_64                      \
        python3-devel.x86_64                \
        strace.x86_64                       \
        sudo.x86_64                         \
        systemd-devel                       \
        tar.x86_64                          \
        tree.x86_64                         \
        unzip.x86_64                        \
        diffutils                           \
        valgrind.x86_64                     \
        wget.x86_64                         \
        which.x86_64                        \
        xcb-util-image-devel.x86_64         \
        xcb-util-image.x86_64               \
        xz.x86_64                           \
        zip.x86_64                          \
    && dnf clean all -y

RUN python3 -m pip install --upgrade pip \
    && python3 -m pip install -Iv gcovr==6.0 pycryptodome==3.18.0 requests==2.31.0 pyte==0.8.1 numpy==1.25.2 \
    && localedef -i en_US -f UTF-8 en_US.UTF-8

RUN cd /tmp \
    && curl -sSL "https://github.com/Snaipe/Criterion/releases/download/v2.4.2/criterion-2.4.2-linux-x86_64.tar.xz" -o /tmp/criterion.tar.xz \
    && tar xf criterion.tar.xz \
    && cp -r /tmp/criterion-2.4.2/* /usr/local/ \
    && echo "/usr/local/lib" > /etc/ld.so.conf.d/usr-local.conf \
    && ldconfig

ENV LANG=en_US.utf8 LANGUAGE=en_US:en LC_ALL=en_US.utf8 PKG_CONFIG_PATH=/usr/local/lib/pkgconfig

RUN cd /tmp \
    && rm -rf /tmp/* \
    && chmod 1777 /tmp

WORKDIR /usr/app
