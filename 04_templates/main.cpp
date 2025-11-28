#include <iostream>
#include <vector>
#include <concepts> // C++20

// 1. 関数テンプレート
// 型に依存しない処理を書く。
template <typename T>
T add(T a, T b) {
    return a + b;
}

// 2. クラステンプレート
template <typename T>
class Box {
private:
    T value;
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
    void set(T v) { value = v; }
};

// 3. コンセプト (C++20)
// テンプレート引数に対する制約を記述できる。
// ここでは「加算可能であること」を制約とする例（簡易版）
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

template <Addable T>
T safe_add(T a, T b) {
    return a + b;
}

int main() {
    // 関数テンプレートの使用
    std::cout << "Int add: " << add(10, 20) << std::endl;
    std::cout << "Double add: " << add(1.5, 2.5) << std::endl;
    // std::cout << add("Hello", "World") << std::endl; // エラー: const char* 同士の + は不可

    // クラステンプレートの使用
    Box<int> intBox(123);
    std::cout << "Box value: " << intBox.get() << std::endl;

    Box<std::string> strBox("Hello Template");
    std::cout << "Box value: " << strBox.get() << std::endl;

    // コンセプトの使用
    std::cout << "Safe add: " << safe_add(5, 10) << std::endl;
    
    // 以下のコードはコンパイルエラーになる（わかりやすいエラーメッセージが出る）
    // safe_add((void*)0, (void*)0); 

    return 0;
}
