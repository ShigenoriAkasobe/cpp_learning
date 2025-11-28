#include <iostream>
#include <string>
#include <vector>

// 1. クラス定義
// structとほぼ同じだが、デフォルトのアクセス権が private になる点が違う。
class Animal {
protected: // 継承先からはアクセス可能
    std::string name;

public:
    // 2. コンストラクタと初期化子リスト
    // : name(n) の部分が初期化子リスト。メンバ変数の初期化はここで行うのが基本。
    Animal(const std::string& n) : name(n) {
        std::cout << "Animal constructor: " << name << std::endl;
    }

    // 仮想デストラクタ: 継承を使う場合は必須に近い
    virtual ~Animal() {
        std::cout << "Animal destructor: " << name << std::endl;
    }

    // 3. 仮想関数 (virtual function)
    // 派生クラスでオーバーライドすることで多態性（ポリモーフィズム）を実現。
    virtual void speak() const {
        std::cout << "..." << std::endl;
    }

    void introduce() const {
        std::cout << "I am " << name << "." << std::endl;
    }
};

// 4. 継承
class Dog : public Animal {
public:
    Dog(const std::string& n) : Animal(n) {
        std::cout << "Dog constructor" << std::endl;
    }

    ~Dog() override {
        std::cout << "Dog destructor" << std::endl;
    }

    // override キーワード: オーバーライドを明示（ミスを防ぐため推奨）
    void speak() const override {
        std::cout << "Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    Cat(const std::string& n) : Animal(n) {}

    void speak() const override {
        std::cout << "Meow!" << std::endl;
    }
};

class Bird : public Animal {
public:
    Bird(const std::string& n) : Animal(n) {}

    void speak() const override {
        std::cout << "Chun!Chun!" << std::endl;
    }
};


int main() {
    std::cout << "--- Stack allocation ---" << std::endl;
    {
        Dog dog("Pochi");
        dog.introduce();
        dog.speak();
    } // ここで dog のデストラクタが呼ばれる（スコープを抜けるため）

    std::cout << "\n--- Polymorphism ---" << std::endl;
    // 基底クラスのポインタで派生クラスを扱う
    Animal* myPet = new Cat("Tama");
    myPet->introduce();
    myPet->speak(); // Cat::speak() が呼ばれる
    
    // delete を忘れるとメモリリーク（次の章でスマートポインタを使って解決します）
    delete myPet; 
    
    std::cout << "\n--- Listing ---" << std::endl;
    std::vector<Animal*> zoo;
    zoo.push_back(new Dog("Shiro"));
    zoo.push_back(new Cat("Kuro"));
    zoo.push_back(new Bird("Piyo"));

    for (const Animal* animal : zoo) {
        animal->introduce();
        animal->speak();
    }

    return 0;
}
