#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>
#include <string_view>

// 02_1_structs: struct と class の基礎
// - struct と class の違いは「デフォルトのアクセス権」
// - struct は「ただのデータ」の表現に向く
// - class は「不変条件を守る」設計に向く

// 典型的な struct: ただのデータ（集成体）
struct Point {
    double x;
    double y;

    double squared_length() const {
        return x * x + y * y;
    }
};

// 典型的な class: 不変条件（invariant）を守る
class BankAccount {
    int balance_;

public:
    explicit BankAccount(int initial_balance) : balance_(initial_balance) {}

    int balance() const {
        return balance_;
    }

    void deposit(int amount) {
        if (amount <= 0) {
            throw std::invalid_argument("deposit amount must be positive");
        }
        balance_ += amount;
    }

    bool withdraw(int amount) {
        if (amount <= 0) {
            throw std::invalid_argument("withdraw amount must be positive");
        }
        if (amount > balance_) {
            return false;
        }
        balance_ -= amount;
        return true;
    }
};

class Counter {
    int value_ = 0;

public:
    void inc() {
        ++value_;
    }

    int value() const {
        return value_;
    }
};

// --- ミニ演習（解答例） ---

// 演習1: struct を「データ」として使う
struct Config {
    std::string host;
    int port;

    std::string endpoint() const {
        return host + ":" + std::to_string(port);
    }
};

// 演習2: class を「不変条件を守る」ために使う
class Username {
    std::string value_;

    static bool contains_space(std::string_view s) {
        for (unsigned char ch : s) {
            if (std::isspace(ch)) {
                return true;
            }
        }
        return false;
    }

public:
    explicit Username(std::string value) : value_(std::move(value)) {
        if (value_.empty()) {
            throw std::invalid_argument("username must not be empty");
        }
        if (contains_space(value_)) {
            throw std::invalid_argument("username must not contain whitespace");
        }
    }

    std::string_view value() const {
        return value_;
    }
};

int main() {
    std::cout << "--- struct basics (data) ---" << std::endl;
    {
        Point p{3.0, 4.0};
        std::cout << "Point(" << p.x << ", " << p.y << ") squared_length=" << p.squared_length() << std::endl;
    }

    std::cout << "\n--- class basics (encapsulation) ---" << std::endl;
    {
        BankAccount account(100);
        account.deposit(50);
        const bool ok = account.withdraw(120);
        std::cout << "withdraw ok? " << (ok ? "yes" : "no") << ", balance=" << account.balance() << std::endl;

        Counter c;
        c.inc();
        c.inc();
        std::cout << "Counter value=" << c.value() << std::endl;
    }

    std::cout << "\n--- mini exercises (solutions) ---" << std::endl;
    {
        Config cfg{"localhost", 8080};
        std::cout << "Config endpoint=" << cfg.endpoint() << std::endl;

        try {
            Username u1("alice");
            std::cout << "Username=" << u1.value() << std::endl;

            // 例外確認（空白を含むのでNG）
            Username u2("bad name");
            std::cout << "Username=" << u2.value() << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Username error: " << e.what() << std::endl;
        }
    }

    return 0;
}
