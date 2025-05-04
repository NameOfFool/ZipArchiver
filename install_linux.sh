#/bin/sh

rm -rf build
rm -rf install
mkdir install
mkdir build && cd build
cmake ..
cd build
cmake --build .
find . -maxdepth 1 -type f -executable -exec bash -c 'mv $1 ../install' - {} \;
echo "Success! result saved in install dir."
