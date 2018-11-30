#!/bin/bash

echo "WRITE COMMENT"
var = "$(cat)"
git add .

git status

git commit -m "var"

git push
