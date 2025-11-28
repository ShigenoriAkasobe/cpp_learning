#include <iostream>
#include <string>
#include <vector>
#include <stdexcept> // 例外用

// 1. 名前空間 (namespace)
// 名前の衝突を防ぐための仕組み。C言語のプレフィックス（my_lib_funcなど）の代わり。
namespace MyLib {
    void print_message(const std::string& msg) {
        std::cout << "[MyLib] " << msg << std::endl;
    }
}

int main() {
    // 2. std::string
    // C言語の char* と違い、メモリ管理を自動で行う文字列クラス。
    std::string name = "User";
    name += " Name"; // 結合も簡単
    
    // 3. auto と型推論
    // コンパイラが右辺から型を推論します。
    auto age = 25; // int
    auto height = 175.5; // double
    
    std::cout << "Name: " << name << ", Age: " << age << std::endl;

    // 4. 範囲 for 文 (Range-based for loop)
    // Pythonの for item in list: に近い書き方。
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Numbers: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 5. 参照 (Reference)
    // ポインタに似ているが、NULLにならず、構文が変数と同じで扱いやすい。
    int x = 100;
    int& ref_x = x; // x への参照
    ref_x = 200;    // x も 200 になる
    std::cout << "x: " << x << std::endl;

    // const 参照: コピーコストを避けつつ、書き換えを禁止する（関数の引数でよく使う）
    const std::string& read_only_name = name;
    // read_only_name = "New Name"; // エラーになる

    // 6. エラー処理（例外）
    // C言語の戻り値チェックよりも強制力があり、コードがすっきりする。
    try {
        int divisor = 0;
        if (divisor == 0) {
            throw std::runtime_error("Division by zero error!");
        }
        int result = 10 / divisor;
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    MyLib::print_message("Basics completed.");

    return 0;
}
