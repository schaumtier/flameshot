FROM vookimedlo/ubuntu-qt:5.15_gcc_focal

RUN apt update && apt install -y qt5-default qttools5-dev-tools libqt5svg5-dev qttools5-dev \
    libqt5dbus5 libqt5network5 libqt5core5a libqt5widgets5 libqt5gui5 libqt5svg5

RUN groupadd -g 1000 conners
RUN useradd -m -u 1000 -g 1000 conners

USER conners

RUN echo "alias l='ls -al --color'" > ~/.bashrc