
#pragma once
#include "../../lib/appEnv.hpp"
#include <vector>

//
// システム（数値関係）
//


class DispNumber {
  std::unique_ptr<Texture> number;
  std::vector<short> val;
  std::vector<short>::iterator it;
  short i;

  enum CutSize {
    Num_W = 64,
    Num_H = 128
  };

public:
  DispNumber() : number(std::make_unique<Texture>("res/graph/number.png")) {}

  // 数値の表示
  void disp_value(float x, float y, float scale, Color num_color) {
    for (it = val.begin(), i = 0; it != val.end(); ++it, ++i) {
      drawTextureBox(x - i * (Num_W * scale), y, Num_W, Num_H,
        (*it) * Num_W, 0, Num_W, Num_H,
        *number, num_color,
        0, Vec2f(scale, scale), Vec2f(Num_W / 2, Num_H / 2));
    }
  }

  // データの桁ごとに値を抽出
  void init_value(int n) {
    // 呼び出した時にデータが残っていたらリセット
    if (val.size()) { val.clear(); }
    do {
      val.emplace_back(n % 10);
      n /= 10;
    } while (n > 0);
  }
};
