- [クラスと構造体（struct/class）ノート](#クラスと構造体structclassノート)
  - [レッスン本文（統合版）](#レッスン本文統合版)
  - [結論：struct と class の違いは「デフォルトの公開範囲」だけ](#結論struct-と-class-の違いはデフォルトの公開範囲だけ)
  - [アクセス修飾子（public / protected / private）](#アクセス修飾子public--protected--private)
    - [「外から触れるもの」を最小化する（重要）](#外から触れるものを最小化する重要)
  - [初期化：集成体初期化（aggregate）とコンストラクタ](#初期化集成体初期化aggregateとコンストラクタ)
    - [struct の典型：データ構造（集成体）として使う](#struct-の典型データ構造集成体として使う)
    - [class の典型：不変条件（invariant）を守る](#class-の典型不変条件invariantを守る)
  - [メンバ関数と const](#メンバ関数と-const)
  - [static（クラスに属するもの）](#staticクラスに属するもの)
  - [使い分けの現実的な指針](#使い分けの現実的な指針)
  - [次に繋がるポイント（この章の先）](#次に繋がるポイントこの章の先)
  - [動くサンプル](#動くサンプル)
  - [ミニ演習](#ミニ演習)
    - [演習1: `struct Config` を作る（データとして素直に公開）](#演習1-struct-config-を作るデータとして素直に公開)
    - [演習2: `class Username` を作る（不変条件を守る）](#演習2-class-username-を作る不変条件を守る)
    - [実行方法（例）](#実行方法例)

# クラスと構造体（struct/class）ノート

## レッスン本文（統合版）

このレッスンは「クラス/構造体の基本が曖昧」な状態から、次の段階（継承・仮想関数・スマートポインタ）に進むための土台を作ることが目的です。

## 結論：struct と class の違いは「デフォルトの公開範囲」だけ

C++ の `struct` と `class` は機能的には同じものです。
違いは **デフォルトのアクセス権** と **継承のデフォルト** だけです。

- `struct`:
  - メンバのデフォルトアクセス権が `public`
  - 継承のデフォルトが `public`
- `class`:
  - メンバのデフォルトアクセス権が `private`
  - 継承のデフォルトが `private`

つまり「`struct` だから軽い」「`class` だから重い」みたいな違いはありません。

## アクセス修飾子（public / protected / private）

- `public`:
  - 外からアクセスできる（API）
- `private`:
  - クラスの外からアクセスできない（内部実装・不変条件の維持に使う）
- `protected`:
  - 継承先からはアクセスできる（継承設計の時だけ使うことが多い）

### 「外から触れるもの」を最小化する（重要）

クラス設計の基本は「壊されると困る状態を `private` に隠す」ことです。

例：残高がマイナスになってはいけないなら、残高を `public` にすると破綻します。

## 初期化：集成体初期化（aggregate）とコンストラクタ

### struct の典型：データ構造（集成体）として使う

```cpp
struct Point {
    double x;
    double y;
};

Point p{3.0, 4.0}; // 集成体初期化（C++らしい）
```

`Point p; p.x = ...;` でも書けますが、`{}` 初期化は「作ると同時に値を入れる」ので安全です。

### class の典型：不変条件（invariant）を守る

```cpp
class BankAccount {
    int balance_;

public:
    explicit BankAccount(int initial) : balance_(initial) {}
    int balance() const { return balance_; }
};
```

- `balance_` を `private` にすることで、外部から直接書き換えできなくなります
- `explicit` は「意図しない暗黙変換」を防ぐための保険です

## メンバ関数と const

`const` メンバ関数は「この関数はオブジェクトの状態を書き換えません」を意味します。

```cpp
class Counter {
    int value_ = 0;

public:
    void inc() { ++value_; }
    int value() const { return value_; }
};
```

- `value()` を `const` にしておくと、`const Counter` からも呼べます
- 「読むだけの関数には `const` を付ける」が基本です

## static（クラスに属するもの）

- `static` メンバ変数：インスタンスに依存しない共有データ
- `static` メンバ関数：`this` を持たず、インスタンスなしで呼べる関数

学習初期は「必要になったら導入する」くらいでOKです。

## 使い分けの現実的な指針

- `struct` を選ぶことが多いケース
  - ただのデータ（DTO / 設定 / 座標 / 結果）
  - メンバを素直に公開して良い
  - 例：`Point{ x, y }`, `Config{ host, port }`

- `class` を選ぶことが多いケース
  - ルールや制約（不変条件）を守りたい
  - 外に見せるAPIを絞りたい
  - 例：`BankAccount`（残高管理）、`Logger`（ファイル保持）

## 次に繋がるポイント（この章の先）

- `new/delete` を使う設計は現代C++では避けることが多い
  - `03_memory` で **RAII** と **スマートポインタ** を学ぶと、OOP設計が一気に安全になります

関連：実際に動くコードは [main.cpp](main.cpp) を参照してください。

## 動くサンプル

- [main.cpp](main.cpp)

このステップは「クラス/構造体の基礎（アクセス修飾、初期化、constなど）」に集中します。
次の [02_2_oop](../02_2_oop) で継承・仮想関数・多態性へ進みます。

## ミニ演習

手を動かして定着させる用の小さな課題です。
解答例は [main.cpp](main.cpp) に入れてあります（まずは自分で書いてから見比べるのがおすすめ）。

### 演習1: `struct Config` を作る（データとして素直に公開）

要件:
- `host`（文字列）と `port`（整数）を持つ `struct Config` を定義
- `endpoint()` を `const` メンバ関数として実装し、`"host:port"` を返す
- `Config cfg{"localhost", 8080};` のように `{}` で初期化して使う

ヒント:
- `struct` は「ただのデータ」に向くので `public` のままでOK
- 文字列連結は `std::string` を使うと楽

### 演習2: `class Username` を作る（不変条件を守る）

要件:
- `Username` は「空文字NG」「空白を含む文字列NG」という不変条件を守る
- そのため、保持する文字列は `private` にする
- コンストラクタで検証し、NGなら `std::invalid_argument` を投げる
- `value()` は読み取り用なので `const` を付ける

ヒント:
- `std::isspace` を使う場合は `unsigned char` にキャストするのが安全

### 実行方法（例）

```bash
cmake --build build --target 02_1_structs
./build/02_1_structs/02_1_structs
```
