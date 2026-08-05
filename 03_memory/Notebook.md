1. [メモリ管理 (Memory Management) ノート](#メモリ管理-memory-management-ノート)
   1. [スマートポインタの実務的な使い分け](#スマートポインタの実務的な使い分け)
      1. [1. `std::unique_ptr` (基本はこれ！)](#1-stdunique_ptr-基本はこれ)
      2. [2. `std::shared_ptr` (特別な場合のみ)](#2-stdshared_ptr-特別な場合のみ)
         1. [`shared_ptr` が有用な具体的シーン: ゲーム開発の「アセット管理」](#shared_ptr-が有用な具体的シーン-ゲーム開発のアセット管理)
      3. [まとめ](#まとめ)
   2. [デザインパターン補足](#デザインパターン補足)
      1. [1. Factory パターン (工場)](#1-factory-パターン-工場)
      2. [2. コンポジション (Composition)](#2-コンポジション-composition)

---

# メモリ管理 (Memory Management) ノート

## スマートポインタの実務的な使い分け

C++11 以降、生の `new` / `delete` は基本的に使わず、以下のスマートポインタを使い分けるのが標準です。

### 1. `std::unique_ptr` (基本はこれ！)

**「所有権を独占する」** ポインタです。

*   **特徴**:
    *   コピー禁止 (所有者は常に一人)。
    *   スコープを抜けると自動で `delete` される。
    *   オーバーヘッド (処理コスト) がゼロ (生のポインタと同じ速度)。
*   **使いどころ**:
    *   **90% のケースはこれで OK。**
    *   関数内で一時的にオブジェクトを作るとき。
    *   クラスのメンバ変数としてオブジェクトを持つとき (コンポジション)。
    *   `std::vector` でオブジェクトを管理するとき。

```cpp
// 例: 工場 (Factory) パターン
std::unique_ptr<Animal> createAnimal() {
    return std::make_unique<Cat>(); // 所有権を呼び出し元に移動 (move) して返す
}
```

### 2. `std::shared_ptr` (特別な場合のみ)

**「所有権を共有する」** ポインタです。

*   **特徴**:
    *   コピー可能 (参照カウントが増える)。
    *   **「最後の所有者」** がいなくなった瞬間に `delete` される。
    *   参照カウントの管理コストがかかるため、`unique_ptr` より少し重い。
*   **使いどころ**:
    *   **「誰が最後まで生き残るかわからない」** 場合。
    *   **グラフ構造** や **キャッシュ** の実装。
    *   複数のクラスから同じリソースを参照し、どのクラスが先に消えるか不明な場合。
    *   非同期処理 (スレッド) でデータを共有する場合。

#### `shared_ptr` が有用な具体的シーン: ゲーム開発の「アセット管理」

例えば、テクスチャ (画像) データを管理する場合を考えます。

1.  `Player` と `Enemy` が同じ `Texture` ("fire.png") を使いたい。
2.  `Player` が死んでも、`Enemy` が生きているなら `Texture` は消してはいけない。
3.  `Enemy` も死んで、**誰もその画像を使わなくなったら** メモリから消したい。

こういう時に `unique_ptr` だと「誰が持ち主か？」で揉めますが、`shared_ptr` なら「みんなで持つ」ことができ、全員がいなくなったら勝手に消えてくれます。

```cpp
class Character {
    std::shared_ptr<Texture> tex; // みんなで共有
public:
    Character(std::shared_ptr<Texture> t) : tex(t) {}
};

// マネージャーがテクスチャをロード
auto fireTex = std::make_shared<Texture>("fire.png");

Player p(fireTex); // 参照カウント 2
Enemy e(fireTex);  // 参照カウント 3

// fireTex, p, e がすべて消滅した時点で、Texture も解放される
```

### まとめ

| ポインタ | 所有権 | コスト | 推奨度 | イメージ |
| :--- | :--- | :--- | :--- | :--- |
| **unique_ptr** | **独占** (1人) | ゼロ | **高 (デフォルト)** | 「俺のもの」 (貸すときは `get()` で生のポインタを見せる) |
| **shared_ptr** | **共有** (複数) | あり | **中 (必要な時だけ)** | 「みんなのもの」 (最後の1人が電気を消す) |

## デザインパターン補足

### 1. Factory パターン (工場)

**「オブジェクトの生成を専門の関数（工場）に任せる」** 考え方です。

*   **メリット**:
    *   使う側は `new Cat()` なのか `new Dog()` なのかを知らなくていい。
    *   「条件によって作るものを変える」ロジックを一箇所にまとめられる。

**例: モンスター生成工場**
```cpp
// 使う側は「モンスターをくれ」と言うだけ
std::unique_ptr<Monster> createMonster(string type) {
    if (type == "slime") return std::make_unique<Slime>();
    if (type == "dragon") return std::make_unique<Dragon>();
    return nullptr;
}

// main側
auto m = createMonster("dragon"); // 何が返ってくるかはお楽しみ
```

### 2. コンポジション (Composition)

**「クラスの中に別のクラスのオブジェクトを持つ」** ことです。
継承 (`is-a` 関係) ではなく、**「持っている (`has-a`) 関係」** を表します。

*   **メリット**:
    *   継承よりも柔軟に機能を組み合わせられる。
    *   部品の入れ替えが簡単。

**例: 車とエンジン**
車はエンジンを「継承」するのではなく、「持っている」のが自然です。

```cpp
class Engine {
public:
    void start() { cout << "Vroom!" << endl; }
};

class Car {
    // Car は Engine を「所有」している (コンポジション)
    // Car が廃棄されたら Engine も一緒に廃棄される運命共同体
    std::unique_ptr<Engine> engine; 

public:
    Car() : engine(std::make_unique<Engine>()) {}

    void drive() {
        cout << "Car starts: ";
        engine->start(); // 持っているエンジンを使う
    }
};

// main関数での使用イメージ
{
    Car myCar;
    myCar.drive(); 
} // ここで myCar が破棄される -> engine も自動的に破棄される
```
ここで `unique_ptr` を使うことで、「車が壊れたらエンジンも一緒にスクラップ」という**所有権と寿命の連動**を表現できます。
