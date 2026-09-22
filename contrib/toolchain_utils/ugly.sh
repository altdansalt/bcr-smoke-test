#!/usr/bin/env bash
if [ -z "$1" ]
then
echo   "usage: $0 NAME"
	exit 1
fi
echo "hi, $1"
