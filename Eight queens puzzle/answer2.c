#include <stdio.h>

#define QUEENS 8 /*皇后数量、棋盤邊長*/
#define IS_OUTPUT_TABLE 1 /*是否輸出具體解，1為輸出，0為不輸出*/

// global的array的elements會全部初始化成0
int up[QUEENS], upLeft[QUEENS * 2], upRight[QUEENS * 2], chess[QUEENS][QUEENS]; // 棋盤使用1-indexing
/* k是棋盤大小，不過k[0][:](row 0)和k[:][0](col 0)貌似不會用到 */
int inc; // 這邊看不懂，目前猜測是用來檢查Q是否有和其他Q在同一條線上

// lay()代表的意義是?
// 目前推測是放置皇后位置的意思，lay(x): 代表放置第x個皇后在棋盤第x列
void lay(int i) {
  int j = 0, t, u;  // t,u只是為了print出table的2層for迴圈的counter

  while (j < QUEENS) {
    // a[j]代表? b[j-i]代表? c[j+i]代表?
    // a[j]不會超出陣列範圍嗎?
    // 陣列空間是連續配置的，所以，初步假設a有可能會access到B，b有B可能會access到A、C，c有可能會access到B?
    if (up[j] + upLeft[j - i + QUEENS] + upRight[j + i] == 0) {
      chess[i][j] = up[j] = upLeft[j - i + QUEENS] = upRight[j + i] = 1; // 設成1，代表放置皇后/該排有皇后
      // a[j], b[j - i], c[j + i]設成1的意義是?
      if (i < QUEENS-1) lay(i + 1);   // 進行下一個皇后的放置
      else {    // i等於QUEENS的時候才會進來這個else
        ++inc;  // 用來記錄是第幾個八皇后棋盤
        if (IS_OUTPUT_TABLE) {
            // print出一個table
          for (printf("(%d)\n", inc), u = 0; u < QUEENS; u++, printf("\n"))
            for (t = 0; t < QUEENS; t++) chess[t][u] ? printf("Q ") : printf("+ ");
          printf("\n\n");
        }
      }
      up[j] = upLeft[j - i + QUEENS] = upRight[j + i] = chess[i][j] = 0; // 還原成0，給其他遞迴分支使用
    }
    j++;
  }
}

int main(void) {
  lay(0);
  printf("%d queens: %d solutions", QUEENS, inc);
//   getchar();
  return 0;
}