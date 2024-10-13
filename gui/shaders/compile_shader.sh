#!/bin/bash

# 셰이더 파일 경로
VERTEX_SHADER="shader.vert"
FRAGMENT_SHADER="shader.frag"

# 출력 경로 (SPIR-V 바이너리)
VERTEX_SHADER_OUTPUT="shader.vert.spv"
FRAGMENT_SHADER_OUTPUT="shader.frag.spv"

# glslangValidator를 사용하여 셰이더 파일을 컴파일
glslangValidator -V $VERTEX_SHADER -o $VERTEX_SHADER_OUTPUT
glslangValidator -V $FRAGMENT_SHADER -o $FRAGMENT_SHADER_OUTPUT

echo "셰이더 컴파일 완료: $VERTEX_SHADER_OUTPUT, $FRAGMENT_SHADER_OUTPUT"
