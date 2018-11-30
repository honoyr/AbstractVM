#!/bin/bash

echo "WRITE COMMENT"
var = "$(echo)"
git add .

git status

git commit -m "$(date)"

git push
