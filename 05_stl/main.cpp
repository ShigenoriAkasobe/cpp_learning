#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // sort, find, for_each
#include <string>
#include <filesystem> // C++17 ファイル操作

namespace fs = std::filesystem;

int main() {
    // 1. std::vector (動的配列)
    std::cout << "--- std::vector ---" << std::endl;
    std::vector<int> nums = {5, 2, 8, 1, 9};
    
    // 追加
    nums.push_back(3);

    // ソート (std::sort)
    std::sort(nums.begin(), nums.end());

    // 出力 (範囲for)
    for (int n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // 2. std::map (連想配列 / 辞書)
    std::cout << "\n--- std::map ---" << std::endl;
    std::map<std::string, int> scores;
    scores["Alice"] = 100;
    scores["Bob"] = 85;
    scores["Charlie"] = 95;

    for (const auto& [name, score] : scores) { // 構造化束縛 (C++17)
        std::cout << name << ": " << score << std::endl;
    }

    // 3. アルゴリズム (std::find)
    std::cout << "\n--- std::find ---" << std::endl;
    auto it = std::find(nums.begin(), nums.end(), 8);
    if (it != nums.end()) {
        std::cout << "Found 8 at index: " << std::distance(nums.begin(), it) << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    // 4. std::filesystem (ファイル操作)
    std::cout << "\n--- std::filesystem ---" << std::endl;
    fs::path current_path = fs::current_path();
    std::cout << "Current path: " << current_path << std::endl;

    // ディレクトリ内のファイルを列挙（エラー処理なしの簡易版）
    // 実行環境によってはファイルが多いので先頭3つだけ表示などの工夫が必要だが、
    // ここでは学習用としてシンプルに記述。
    /*
    for (const auto& entry : fs::directory_iterator(current_path)) {
        std::cout << entry.path().filename() << std::endl;
    }
    */

    return 0;
}
