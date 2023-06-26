#!/usr/bin/env bash

xhost +local:root 1>/dev/null 2>&1
docker exec \
    -u root \
    -it 4bf36d7083bf \
    /bin/bash
xhost -local:root 1>/dev/null 2>&1