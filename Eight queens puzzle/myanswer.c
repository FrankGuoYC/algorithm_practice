#include <stdio.h>

#define QUEENS 8 /*皇后数量、棋盤邊長*/
#define IS_OUTPUT_TABLE 1 /*是否輸出具體解，1為輸出，0為不輸出*/

// 棋盤使用0-indexing
/**
 * up用來記錄同一行是否已有皇后，upLeft紀錄左上-右下斜行是否已有皇后，upRight紀錄右上-左下斜行是否已有皇后，chess則為棋盤
 * **/
int up[QUEENS], upLeft[QUEENS * 2], upRight[QUEENS * 2], chess[QUEENS][QUEENS]; 
int inc; // 用來記錄目前已經有幾個符合條件的棋盤

// lay()代表的意義是?
// 目前推測是放置皇后位置的意思，lay(x): 代表放置第x個皇后在棋盤第x列
void lay(int i) {
  int j = 0, t, u;  // temp var for the nested for-loop

  while (j < QUEENS) {
    if (up[j] + upLeft[j - i + QUEENS] + upRight[j + i] == 0) {
      chess[i][j] = up[j] = upLeft[j - i + QUEENS] = upRight[j + i] = 1; // 設成1，代表放置皇后/該排有皇后
      if (i < QUEENS-1) lay(i + 1);   // 進行下一個皇后的放置
      else {    // i等於QUEENS-1的時候才會進來這個else
        ++inc;  // 用來記錄是第幾個八皇后棋盤
        if (IS_OUTPUT_TABLE) {
          // print出符合條件的table
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
  printf("%d queens: %d solutions\n", QUEENS, inc);
//   getchar();
  return 0;
}