

// 유니티의 MonoBehaviour와 비슷한 역할을 하는 클래스
class BakeBehaviour {
public:
    BakeBehaviour() {
        // BiscuitEigne의 Add 등으로 스크립트를 등록해줘야함.
        // 업데이트를 사용할 떄와, 사용하지 않을 때의 등록을 나눌 것.
    }

    virtual void Awake();
    virtual void Start();
    virtual void Update();

private:


};