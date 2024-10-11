
// editor, gui에서 사용할 api class
// static 하게 떠있어야함.
class BiscuitEngine {
public:
    static BiscuitEngine& GetInstance() {
        static BiscuitEngine instance;
        return instance;
    }
    BiscuitEngine(BiscuitEngine const&) = delete;
    void operator=(BiscuitEngine const&) = delete;

    // engine api


private:
    BiscuitEngine() {}
    ~BiscuitEngine() {}
};