# [Choice] Debian / Ubuntu version: debian-10, debian-9, ubuntu-20.04, ubuntu-18.04
ARG VARIANT=ubuntu-20.04
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0.154.1-${VARIANT}

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    # Install dependencies
    && apt-get -y install --no-install-recommends libboost-all-dev libwebsocketpp-dev ninja-build nlohmann-json3-dev \
    #
    # Install tools
    && apt-get -y install --no-install-recommends nano doxygen graphviz valgrind
