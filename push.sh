#!/bin/zsh

norminette | grep Error

if (( $? == 0 )); then
  exit
fi

make re

if (( $? != 0 )); then
  exit
else
  echo "Make error!"
fi

make fclean

git add .
git commit
git push