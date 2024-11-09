#version 450

layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform BoolBlock {
    int useTexture;  // bool을 int로 변경
} boolBlock;

void main() {
    outColor = texture(texSampler, fragTexCoord); 

    // if (boolBlock.useTexture == 1) {
    //    outColor = texture(texSampler, fragTexCoord);  // 텍스처 사용
    // } else {
    //     outColor = vec4(1.0);  // 텍스처를 사용하지 않으면 흰색 (기본 색)
    // }
}
