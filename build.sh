IMAGE_NAME=flameshot-builder
BUILDER=$(docker images -f reference=$IMAGE_NAME --format {{.ID}})

if [[ "$1" == "help" || "$1" == "--help" || "$1" == "-h" ]]; then
    echo
    echo "[Options]"
    echo
    echo "   image   - rebuilds the docker image"
    echo "   rebuild - rebuilds the source code (deletes old build)"
    echo
    exit 0
fi

if [[ "$1" == "image" && "$BUILDER" != "" ]]; then
    docker rmi $IMAGE_NAME
    BUILDER=""
fi

if [[ "$BUILDER" == "" ]]; then
    docker build -t $IMAGE_NAME .
fi

docker run --rm -it -v $(pwd):/flameshot -w /flameshot $IMAGE_NAME $@