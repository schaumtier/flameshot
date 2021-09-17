FROM vookimedlo/ubuntu-qt:5.15_gcc_focal

RUN apt update && apt install -y qt5-default qttools5-dev-tools libqt5svg5-dev qttools5-dev \
    libqt5dbus5 libqt5network5 libqt5core5a libqt5widgets5 libqt5gui5 libqt5svg5

RUN groupadd -g 1000 conners
RUN useradd -m -u 1000 -g 1000 conners

RUN mkdir /scripts; chown conners.conners /scripts

USER conners

RUN echo '#!/bin/bash' > /scripts/compile.sh
RUN echo '\
    if [[ "$1" == "rebuild" ]]; then \n\
        rm -Rf build \n\
    fi \n\
    \
    if [[ -d "build" ]]; then \n\
        cd build \n\
    else \n\
        mkdir build \n\
        cd build \n\
        cmake ../ \n\
    fi \n\
    \
    make \n\
    ' >> /scripts/compile.sh

RUN chmod +x /scripts/compile.sh

ENTRYPOINT ["/scripts/compile.sh"]