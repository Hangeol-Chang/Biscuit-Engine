@echo off
:: 셰이더 파일 경로
set VERTEX_SHADER=vert.vert
set FRAGMENT_SHADER=frag.frag

:: 출력 경로 (SPIR-V 바이너리)
set VERTEX_SHADER_OUTPUT=vert.spv
set FRAGMENT_SHADER_OUTPUT=frag.spv

:: Vulkan SDK의 glslangValidator로 셰이더 파일 컴파일
:: Vulkan SDK 경로가 환경 변수로 설정되어 있어야 함
glslangValidator -V %VERTEX_SHADER% -o %VERTEX_SHADER_OUTPUT%
if %errorlevel% neq 0 (
    echo Vertex shader compilation failed!
    exit /b %errorlevel%
)
glslangValidator -V %FRAGMENT_SHADER% -o %FRAGMENT_SHADER_OUTPUT%
if %errorlevel% neq 0 (
    echo Fragment shader compilation failed!
    exit /b %errorlevel%
)

echo Shader compilation successful: %VERTEX_SHADER_OUTPUT%, %FRAGMENT_SHADER_OUTPUT%
