#!/bin/bash

git add .

git status
echo "WRITE COMMENT"
git commit -m "$(cat)"

git push
