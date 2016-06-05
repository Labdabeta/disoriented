#!/bin/bash

for IMAGE in *.png
do
    echo $IMAGE
    convert $IMAGE $IMAGE
done
