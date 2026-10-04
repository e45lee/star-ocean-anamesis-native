#!/bin/bash
# build.sh SRC NDK(r11c|r16b) CC(clang|gcc) OUT FLAGS...
set -u
SRC=$1; NDKV=$2; CCK=$3; OUT=$4; shift 4
REPO=$(cd "$(dirname "$0")/../../../.." && pwd)
T=${SOA_TOOLCHAINS:-$REPO/work/toolchains}
export LD_LIBRARY_PATH=$T/compat-lib
N=$T/android-ndk-$NDKV
GT=$N/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64
if [ $NDKV = r16b ]; then
  SYS="--sysroot=$N/sysroot -isystem $N/sysroot/usr/include/aarch64-linux-android -D__ANDROID_API__=21"
  CXXI="-isystem $N/sources/cxx-stl/llvm-libc++/include -isystem $N/sources/android/support/include -isystem $N/sources/cxx-stl/llvm-libc++abi/include"
else
  SYS="--sysroot=$N/platforms/android-21/arch-arm64"
  CXXI="-isystem $N/sources/cxx-stl/llvm-libc++/libcxx/include -isystem $N/sources/android/support/include"
fi
if [ $CCK = clang ]; then
  CXX="$N/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ -target aarch64-none-linux-android -gcc-toolchain $GT"
else
  CXX="$GT/bin/aarch64-linux-android-g++"
fi
mkdir -p $OUT
fail=0
for f in $(cd $SRC/src && find LinearMath BulletCollision BulletDynamics -name '*.cpp'); do
  o=$OUT/$(echo $f | tr / _ ).o
  $CXX $SYS $CXXI -I$SRC/src -fPIC -DANDROID -DNDEBUG -c $SRC/src/$f -o $o "$@" 2>>$OUT/err.log || fail=$((fail+1))
done
echo "fail=$fail"
