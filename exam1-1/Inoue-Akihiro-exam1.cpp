// 学籍番号 1201201010
// ポータルID : seb01010
// 氏名  井上明浩
// プログラム名 : Inoue-Akihiro_exam1.cpp


#include<stdio.h> /* C標準ライブラリ関数である標準入出力命令処理内容が保存された
					 ヘッダファイルをプログラムに読み込むプリプロセッサ */

int main(void) // main 関数の始まり
{

	printf("ポータルID   学籍番号   氏名   氏名のヨミカナ\n");  // 受講生の確認情報の項目タイトルを表示

	printf("seb01010   1201201010   井上明浩   イノウエ・アキヒロ\n");  // 受講生の確認情報を表示


	return(0);  /* main関数内の命令文が全て処理され、正常に終了すれば、0 を
			main関数の呼び出し側であるCPUに返し、プログラムを終了する。*/

} // main関数の終わり