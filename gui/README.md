
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

- Behaviour에서, Component를 어떻게 업데이트 해줘야함?
-- 일단, 뭘 업데이트 할 수 있어야함/>?
-- Model, Texture, Position, Rotation 싹 다
-- Behaviour 안에 Component가 들어가는게 깔끔해 보인다...
-- 아니면 Behaviour한테 Component를 주입해주고, Component의 Update로직을 뭔가가 바뀔 때 마다 호출.
---> 근데 이렇게 할려면, MM, TM을 Behaviour가 알고있어야함.
---> Update로직을 어떤 식으로 호출할 것인가.
-> Component가 Behaviour안에 들어가는게 맞는 형태임.
-> UpdateMmodel을 걸면, Dynamic|Static을 Behaciour가 알고있다가, 적당히 처리해줘야함.
--> 안됨. 안됨 Component가 Behaviour안에 들어가게 할 수 없음.
--> Behaviour는 딱 동작에 대한 것만 가지고 있어야 함.
-> 그러면 어떻게 Component를 Update해주지?
--> 일단 BuildComponent할 때, Behaviour 생성하고, Behaviour에 Component를 포인터로 주입해줄 것.
--> Update는 그 이후에 생각.

--> Component의 Model, Texture 등을 전부 public으로 오픈하고, Behaviour에서 직접 제어하도록 함.

-> Behaviour가 없는 정적 컴포넌트도 있을 수 있음.

-> UV랑 vertex랑 buffer 분리해야 함.
--> 갓갓gpt왈 : 분리 안하고 그냥 메모리에 묶어놓는게 그릴 떄 리소스 덜든다.

### Dependencies
- c++ >= 17
- vulkan
- glfw3
- glm

----
with gpt

Q. 어디까지 통합해서 사용할 수 있는가.
Vulkan에서는 여러 그래픽 파이프라인을 사용할 필요가 있는 상황이 자주 발생할 수 있습니다. 그래픽 파이프라인은 고정된 상태(state)와 셰이더 프로그램을 포함하고 있어서, 렌더링하려는 데이터에 따라 각기 다른 파이프라인을 사용할 수 있습니다.

여러 파이프라인을 사용하는 경우:

서로 다른 셰이더가 필요한 경우 (예: 기본 셰이딩 vs. 물리 기반 렌더링)
블렌딩, 깊이 테스트, 스텐실 테스트 같은 고정 상태가 달라야 할 때
렌더 타겟(프레임버퍼)이 다를 경우
파이프라인을 통합해서 사용할 수 있는 경우:

고정 상태나 셰이더가 거의 동일한 경우
유사한 객체나 메시에 대해 동일한 셰이더와 렌더링 상태를 사용할 때
일반적으로, 파이프라인 수가 많아질수록 초기 설정 비용이 증가하기 때문에, 가능한 한 동일한 파이프라인을 재사용하는 것이 효율적입니다. 각 파이프라인의 사용 사례에 따라 효율적인 구성이 필요하며, 동적 상태(dynamic state)를 통해 일부 상태를 런타임에서 변경할 수도 있습니다.

Conc. 그래픽 파이프라인의 분리는 일단 생각하지 않습니다.

----

vertices 를 -1부터 1까지 쓰지 않고, 해상도에 맞게 쓰고 노말라이징 하도록 해야 함.