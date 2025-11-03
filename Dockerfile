##
## ACHTUNG:
##   aktuell ist die App auf Qt6 => wenn ich also mal den Code erneuere, muss ich ein anderes Basis-Image nutzen und andere Packages installieren
##

FROM debian:bookworm

RUN apt update && apt install -y g++ cmake build-essential git openssl ca-certificates \
    qtbase5-dev qttools5-dev-tools libqt5svg5-dev qttools5-dev \
    libqt5dbus5 libqt5network5 libqt5core5a libqt5widgets5 libqt5gui5 libqt5svg5 libkf5guiaddons-dev

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