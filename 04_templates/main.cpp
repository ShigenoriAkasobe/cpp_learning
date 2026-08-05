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


// ミニ演習
// 演習1: print_twice の作成
template <typename T>
T print_twice(T value) {
    std::cout << value << " " << value << std::endl;
    return value;
}
template <typename T>
T print_twice2(const T& value) {
    std::cout << value << " " << value << std::endl;
    return value;
}

// 演習2: PairBox<T> の作成
template <typename T>
class PairBox {
private:
    T first_value;
    T second_value;
public:
    PairBox(const T& f, const T& s) : first_value(f), second_value(s) {}
    const T& first() const { return first_value; }
    const T& second() const { return second_value; }
};

// 演習3: Multipliable コンセプトの作成
template <typename T>
concept Multipliable = requires(T a, T b) {
    { a * b } -> std::convertible_to<T>;
};
template <Multipliable T>
T safe_multiply(T a, T b) {
    return a * b;
}

int main() {
    // 関数テンプレートの使用
    std::cout << "Int add: " << add(10, 20) << std::endl;
    std::cout << "Double add: " << add(1.5, 2.5) << std::endl;
    std::cout << "Double add: " << add<double>(1, 2.5) << std::endl;
    // std::cout << add("Hello", "World") << std::endl; // エラー: const char* 同士の + は不可
    std::cout << "String add: " << add(std::string("Hello "), std::string("World")) << std::endl;

    // クラステンプレートの使用
    Box<int> intBox(123);
    Box<int> intBox2{456};
    std::cout << "Box value: " << intBox.get() << std::endl;
    std::cout << "Box value: " << intBox2.get() << std::endl;

    Box<std::string> strBox("Hello Template");
    std::cout << "Box value: " << strBox.get() << std::endl;

    // コンセプトの使用
    std::cout << "Safe add: " << safe_add(5, 10) << std::endl;
    std::cout << "Safe add: " << safe_add(2.5, 3.6) << std::endl;
    
    // 以下のコードはコンパイルエラーになる（わかりやすいエラーメッセージが出る）
    // safe_add((void*)0, (void*)0);

    // ミニ演習
    // 演習1: print_twice の使用
    print_twice(10);
    print_twice(std::string("Hello"));
    print_twice2(20);
    print_twice2(std::string("World"));

    // 演習2: PairBox<T> を作る
    PairBox<int> intPair{1, 2};
    std::cout << "First: " << intPair.first() << ", Second: " << intPair.second() << std::endl;

    // 演習3: Multipliable コンセプトの使用
    std::cout << "Safe multiply: " << safe_multiply(3, 4) << std::endl;
    std::cout << "Safe multiply: " << safe_multiply(2.5, 4.1) << std::endl;
    // std::cout << "Safe multiply: " << safe_multiply(std::string("Hello"), std::string("World")) << std::endl;  // エラー: std::string は Multipliable ではない

    return 0;
}
