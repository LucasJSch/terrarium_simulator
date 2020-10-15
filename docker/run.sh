#!/bin/bash

CONTAINER=cppcourse-image
IMAGE_NAME=cppcourse-image

SCRIPTS_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
REPO_DIR=`readlink -f ${SCRIPTS_DIR}/../`

DOCKER_MOUNT_ARGS="-v ${REPO_DIR}/course:/course"

xhost +
docker run --name ${IMAGE_NAME} --privileged --rm \
    ${DOCKER_MOUNT_ARGS} \
    -e USER=$USER -e USERID=$UID \
    --net=host \
    -it ${CONTAINER}
