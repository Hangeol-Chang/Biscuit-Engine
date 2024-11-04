
### Thinkbox
- 풀 스크립트로 제어되지만, 초기 init에 vertex 등의 데이터가 필요함.

- 초기화될 때 children을 등록해야 함.
- parent에서 transform 이벤트가 발생할 때, child의 transform을 업데이트할 수 있어야함.

#### components 구조


-> 우리의 컨셉은 "굉장히 raw하게 내부 정보들을 컨트롤할 수 있는 api를 우선 제공한다."임.