#!/bin/zsh

norminette | grep Error

if (( $? == 0 )); then
  exit
fi

make both_re

if (( $? != 0 )); then
  echo "Make error!"
  exit
fi

make fclean

git add .
git commit
git push