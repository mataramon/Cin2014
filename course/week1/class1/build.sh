#!/usr/bin/env bash
echo "BUILD SCRIPT";
export BUILD_DIR="build";

if [ -d $BUILD_DIR ]
   then 
   echo "1- Removing previous build ....";
   rm -R $BUILD_DIR;
fi

echo "2- Creating new build directory ....";
mkdir $BUILD_DIR;
echo "3- Starting compilation ...";

for file in *.c;
do
   echo "   -> compiling $file";
   out=${file%.*}
   gcc $file -o "$BUILD_DIR/$out";

done
cp token $BUILD_DIR/;

echo "   Done";
