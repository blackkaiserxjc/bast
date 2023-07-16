FROM ubuntu:23.10

ENV TZ=UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update -yqq \
    && apt-get install -yqq --no-install-recommends software-properties-common \
    curl wget cmake make pkg-config locales git gcc g++ \
    openssl libssl-dev unzip tar zip \
    && rm -rf /var/lib/apt/lists/* \
    && locale-gen en_US.UTF-8

RUN LANGUAGE=en_US:en \
    LC_ALL=en_US.UTF-8 \
    CC=gcc \
    CXX=g++ \
    AR=gcc-ar

RUN git clone https://github.com/Microsoft/vcpkg.git /opt/vcpkg
WORKDIR /opt/vcpkg

RUN ./bootstrap-vcpkg.sh && ./vcpkg integrate install && ./vcpkg integrate bash && echo 'export PATH=$PATH:/opt/vcpkg' >>~/.bashrc
ENV VCPKG_ROOT=/opt/vcpkg

CMD ["bash"]