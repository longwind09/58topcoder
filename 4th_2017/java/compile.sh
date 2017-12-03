#!/bin/sh

. JDK jdk1.8.0_66
rm *.class -rf


files=""

for file in *.java; do
  files=$files' '$file
done

javac -verbose $files > compile_result 2>&1
