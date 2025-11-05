FROM debian:trixie

RUN apt update && apt install -y g++ cmake build-essential git openssl ca-certificates \
    qt6-base-dev qt6-tools-dev-tools qt6-svg-dev qt6-tools-dev \
    libkf6guiaddons-dev libqt6dbus6 libqt6network6 libqt6core6 libqt6widgets6 libqt6gui6 libqt6svg6 qt6-qpa-plugins

RUN groupadd -g 1000 conners
RUN useradd -m -u 1000 -g 1000 conners

RUN mkdir /scripts; chown conners.conners /scripts

USER conners

RUN echo '#!/bin/bash' > /scripts/compile.sh
RUN echo 'if [[ "$1" == "rebuild" ]] || [[ "$1" == "image" ]]; then' >> /scripts/compile.sh
RUN echo '    rm -Rf build' >> /scripts/compile.sh
RUN echo 'fi' >> /scripts/compile.sh
RUN echo 'if [[ -d "build" ]]; then' >> /scripts/compile.sh
RUN echo '    cd build' >> /scripts/compile.sh
RUN echo 'else' >> /scripts/compile.sh
RUN echo '    mkdir build' >> /scripts/compile.sh
RUN echo '    cd build' >> /scripts/compile.sh
RUN echo '    cmake ../ -DUSE_WAYLAND_CLIPBOARD=1' >> /scripts/compile.sh
RUN echo 'fi' >> /scripts/compile.sh
RUN echo 'make' >> /scripts/compile.sh

RUN chmod +x /scripts/compile.sh

ENTRYPOINT ["/scripts/compile.sh"]