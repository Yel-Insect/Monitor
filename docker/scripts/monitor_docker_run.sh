#!/usr/bin/env bash

display=""
if [ -z ${DISPLAY} ];then
    display=":1"
else
    display="${DISPLAY}"
fi

local_host="$(hostname)"
user="${USER}"
uid="$(id -u)"
group="$(id -g -n)"
gid="$(id -g)"


docker run -it \
-e DISPLAY=$display \
-e DOCKER_USER="${user}" \
-e USER="${user}" \
-e DOCKER_USER_ID="${uid}" \
-e DOCKER_GRP="${group}" \
-e DOCKER_GRP_ID="${gid}" \
-e XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR \
-v /home/cargo/work/test_monitor:/work \
-v /home/cargo/Downloads/exmpl-cmake-grpc-master:/grpc \
-v ${XDG_RUNTIME_DIR}:${XDG_RUNTIME_DIR} \
-v "/tmp/.X11-unix:/tmp/.X11-unix:rw" \
--net host \
test111:monitor