#include <stdio.h>

#define QUEENS 7 /*皇后数量、棋盤邊長*/
#define IS_OUTPUT_TABLE 1 /*是否輸出具體解，1為輸出，0為不輸出*/

FILE *fp;

// global的array的elements會全部初始化成0
int A[QUEENS], B[QUEENS * 2 - 1], C[QUEENS * 2 - 1], k[QUEENS + 1][QUEENS + 1]; // 棋盤使用1-indexing
/* k是棋盤大小，不過k[0][:](row 0)和k[:][0](col 0)貌似不會用到 */
int inc, *a = &A[1], *b = &B[QUEENS], *c = &C[-2]; // 這邊看不懂，目前猜測是用來檢查Q是否有和其他Q在同一條線上
// a,b,c 分別用來記錄上面、左上、右上是否已有放置皇后
/*
Q1: a為什麼是設一個pointer指在array尾端(array尾端element的address+1)?
Q2: A,B,C代表的意義是什麼? 為什麼B, C的空間大小是QUEEN*3+1?
Q3: b,c為什麼是指向第QUEENS的element的記憶體addr?
*/

// lay()代表的意義是?
// 目前推測是放置皇后位置的意思，lay(x): 代表放置第x個皇后在棋盤第x列
void lay(int i) {
  int j = 0, t, u;  // t,u只是為了print出table的2層for迴圈的counter
  // i代表? j代表?

  while (++j <= QUEENS)
    // a[j]代表? b[j-i]代表? c[j+i]代表?
    // a[j]不會超出陣列範圍嗎?
    // 陣列空間是連續配置的，所以，初步假設a有可能會access到B，b有B可能會access到A、C，c有可能會access到B?
    if (a[j] + b[j - i] + c[j + i] == 0) {
      k[i][j] = a[j] = b[j - i] = c[j + i] = 1; // 設成1，代表放置皇后
      // a[j], b[j - i], c[j + i]設成1的意義是?
      if (i < QUEENS) lay(i + 1);   // 進行下一個皇后的放置
      else {    // i等於QUEENS的時候才會進來這個else
        ++inc;  // 用來記錄是第幾個八皇后棋盤
        if (IS_OUTPUT_TABLE) {
            // print出一個table
          for (fprintf(fp, ">\n"), u = QUEENS + 1; --u; fprintf(fp, "\n"))    
            for (t = QUEENS + 1; --t; ) k[t][u] ? fprintf(fp, "1 ") : fprintf(fp, "0 ");  
        }
      }
      a[j] = b[j - i] = c[j + i] = k[i][j] = 0; // 還原成0，給其他node分支使用
    }
}

int main(void) {
  fp = fopen("myans.txt", "w");
  lay(1);
  printf("%d queens: %d solutions", QUEENS, inc);
//   getchar();
  fprintf(fp, "$");
  fclose(fp);
  return 0;
}