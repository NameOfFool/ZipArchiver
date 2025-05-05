#/bin/sh

interruptfn(){
  trap SIGINT
  cd ..
  rm -rf build
  rm -rf install
  echo "Interrupted"
  exit
}
echo "WARNING! IF YOU RUN THIS SCRIPT, YOU WILL DELETE build AND install FOLDERS"
read -r -p "Proceed? [y/N]" response
case "$response" in
  [yY][eE][sS]|[yY])
  rm -rf build
  rm -rf install
  mkdir install
  mkdir build && cd build
  trap "interruptfn" INT
  cmake ..
  cd build
  cmake --build .
  find . -maxdepth 1 -type f -executable -exec bash -c 'mv $1 ../install' - {} \;
  echo "Success! result saved in install dir."
  trap SININT
  ;;
*)
  echo "Building was cancelled"
  ;;
esac
