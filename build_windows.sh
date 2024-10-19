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


echo "=============================================="
echo "빌드 완료: 실행 파일은 $BUILD_DIR/BiscuitEditor와 $BUILD_DIR/BiscuitGUI에 생성되었습니다."
echo "=============================================="
