#include <iostream>
#include <memory> // スマートポインタ用
#include <string>

class Resource {
public:
    Resource(const std::string& name) : name_(name) {
        std::cout << "Resource acquired: " << name_ << std::endl;
    }
    ~Resource() {
        std::cout << "Resource released: " << name_ << std::endl;
    }
    void use() {
        std::cout << "Using resource: " << name_ << std::endl;
    }
private:
    std::string name_;
};

// 1. RAII (Resource Acquisition Is Initialization)
// リソースの確保と解放をオブジェクトの寿命に紐付ける考え方。
// スコープを抜けるとデストラクタが呼ばれ、自動的に解放される。

void raw_pointer_risk() {
    // 危険: delete を忘れたり、例外が起きるとメモリリークする
    Resource* res = new Resource("Raw Pointer");
    res->use();
    delete res;
}

void smart_pointer_safety() {
    // 2. std::unique_ptr
    // 所有権を一人だけが持つポインタ。コピー不可、移動のみ可。
    // スコープを抜けると自動で delete される。
    std::cout << "--- unique_ptr ---" << std::endl;
    std::unique_ptr<Resource> res1 = std::make_unique<Resource>("Unique 1");
    res1->use();

    // 所有権の移動
    std::unique_ptr<Resource> res2 = std::move(res1);
    if (!res1) {
        std::cout << "res1 is empty." << std::endl;
    }
    res2->use();
} // ここで res2 (Unique 1) が解放される

void shared_pointer_demo() {
    // 3. std::shared_ptr
    // 参照カウント方式で所有権を共有する。
    std::cout << "--- shared_ptr ---" << std::endl;
    std::shared_ptr<Resource> resA = std::make_shared<Resource>("Shared A");
    
    {
        std::shared_ptr<Resource> resB = resA; // カウントが増える
        std::cout << "Ref count: " << resA.use_count() << std::endl;
        resB->use();
    } // resB が破棄されるが、resA が残っているのでリソースは解放されない

    std::cout << "Ref count: " << resA.use_count() << std::endl;
    resA->use();
} // ここで resA が破棄され、カウントが0になりリソース解放

int main() {
    // raw_pointer_risk(); // 比較用
    
    smart_pointer_safety();
    std::cout << std::endl;
    shared_pointer_demo();

    return 0;
}
