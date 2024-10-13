
vulkan이 msys에 이상하게 설치되는 경우가 종종 있음.
-> cmake에서 맞춰줘야 할 수도 있음

Vulkan API 새로 만들어야 함.
사양이 기존에 만들던것과는 좀 다름.
https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Base_code


glfw 사용

- req
-- vulkan low level api
vertex를 자유롭게 추가할 수 있어야 함.
index는... 음 어카지
텍스쳐 임포트. 매핑 방식 설정 기능
오프스크린 렌더링 당연히 가능해야함.
--- 그래픽 버퍼에 다이렉트로 쓰는걸 지원.
target frame 설정 기능.
프레임버퍼 수 제어 기능.
glfw창을 여러개 띄울 수 있어야함. VulkanAPI가 하나의 gui 앱이 되고, 이 앱을 여러개 실행할 수 있는 형태.

-- gui high level api
engine에서 transform 데이터를 받아서 vertex를 수정.

- Debug 모듈은 별도로 분리

-- 언젠가 들어와야 하는 것들.
3d 모델 임포트
프레임버퍼 파일로 뽑을 수 있는 기능.


### Dependencies
- c++ >= 17
- vulkan
- glfw3
- glm
