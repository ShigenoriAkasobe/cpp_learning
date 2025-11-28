#include <iostream>

// C++の基本: 標準入出力
// C言語の printf よりも型安全で拡張性が高い std::cout を使います。

int main() {
    // std::cout : 標準出力
    // << : 出力演算子
    // std::endl : 改行 + フラッシュ
    std::cout << "Hello, C++ World!" << std::endl;

    // C++20の機能が有効か確認（__cplusplus マクロ）
    std::cout << "C++ Standard Version: " << __cplusplus << std::endl;

    return 0;
}
