#!/bin/bash

# 빌드 디렉토리 생성
BUILD_DIR="build"
mkdir -p $BUILD_DIR/editor
mkdir -p $BUILD_DIR/gui

# 각 프로젝트 빌드
# Editor 빌드
cmake -B $BUILD_DIR/editor -S ./editor -G "MinGW Makefiles"
mingw32-make -C $BUILD_DIR/editor

# GUI 빌드
cmake -B $BUILD_DIR/gui -S ./gui -G "MinGW Makefiles"
mingw32-make -C $BUILD_DIR/gui

# 실행 파일 생성
cat << EOF > $BUILD_DIR/Biscuit
#!/bin/bash
./editor/BiscuitEditor &
./gui/BiscuitGUI &
EOF

# 실행 파일에 실행 권한 추가
chmod +x $BUILD_DIR/Biscuit


# copy/make public file/folder
## shaders
mkdir -p $BUILD_DIR/shaders
cp -r ./gui/shaders/*.spv $BUILD_DIR/shaders

## gui config datas
cp -r ./engine/data/* $BUILD_DIR/data

## mkae public files
cp -r ./editor/public/* $BUILD_DIR/public
cp -r ./gui/public/* $BUILD_DIR/public


echo "=============================================="
echo "빌드 완료: 실행 파일은 $BUILD_DIR/Biscuit에 생성되었습니다."
echo "=============================================="
