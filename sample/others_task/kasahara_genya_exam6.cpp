//学籍番号：1201201034
//ポータルID：seb01034
//氏名：笠原絃矢
//プログラム名：kasahara_genya_exam6.cpp
# include<stdio.h> // ファイル等の入出力操作のための標準入出力ヘッダーファイルの読込み
#include<stdlib.h> // EOF の処理ができるための標準ライブラリヘッダーファイルの読込み
# define _USE_MATH_DEFINES // 数値演算定数(円周率等) を 定義
# include<math.h> //数値演算定数が定義されたヘッダファイルの読込み
#include<time.h> // 処理時間を計る処理を行うためのヘッダーファイルの読み込み
// #define を利用して、解の探索間隔 Δx を 0.001 に設定するプログラムを作成
#define delta_x 0.001
// 引数付き関数形式マクロを利用した，非線形方程式 f(x) の定義・作成
#define f(x) (log(x)-cos(x))
// 非線形方程式の近似解の探索結果をファイル出力するためのファイルポインタの定義
FILE* fp;

// 再帰関数呼び出しを利用した自作関数(値渡し・戻り値あり)の定義(プロトタイプ宣言)
// 仮引数(入力情報)の定義 double x1, int n
double direct_recursion(double x1, int n);

int main(void){
	//処理時間を計るための時間変数の定義
	clock_t start, end;
	//処理開始直前の時間を保存
	start = clock();

	double a;
	double x1; // 非線型方程式の解の近似式を格納するための実数型変数定義
	int n; // 反復回数
	// Step 1 : 解の探索開始点 a を 0.001 に 設定
	a = 0.001;

	// step 2 - start -
	x1 = a; // x1 を a に 初期化
	n = 1;// 反復回数 n を 1 に初期化
    // step 2 - end -
	// 入力情報となる実引数として、x1, n の値を値渡しで自作関数 direct_recursion を 呼び出す
	x1 = direct_recursion(x1, n); // (エ)に実引数を入力してください。

	// step 5 - 実行結果のcsvファイルへのファイル出力の準備
	// Open for write (csvファイルに追記書込みモードで保存し、ファイル出力するファイルオープン処理)
	fopen_s(&fp, "kasahara_genya_exam6.csv", "a");
	// step 5 - 探索結果をPC 画面上に表示
	printf("\nf(x)=log(x)-cos(x)=0\n\n");
	printf("直接探索法による近似解：%.8lf\n\n", x1);
	// 探索結果 を csv ファイルへ出力(追記書込みモードに設定したcsv ファイル)
	fprintf(fp, "\nf(x)=log(x)-cos(x)=0\n\n");
	fprintf(fp, "直接探索法による近似解：%.8lf\n\n", x1);
	
	// 全ての処理終了直後の時間を保存
	end = clock();
	
	// 探索処理時間(秒)を PC 画面表示
	printf("処理時間：%lf秒\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	// 探索処理時間(秒)を csv ファイルへ出力(追記書込みモードに設定したcsv ファイル)
	fprintf(fp, "処理時間：%lf秒\n", (double)(end - start) / CLOCKS_PER_SEC);
	
	// FILEポインタ fp でオープンしたファイルをクローズする
	fclose(fp);
	return(0);
}
//step3～step4を自作関数化
double direct_recursion(double x1, int n)//仮引数x1と反復回数n
{
	fopen_s(&fp, "kasahara_genya_exam6.csv", "a");//ファイルをオープン
	double x2, y1, y2;
	//引数付き関数形式マクロを利用してx1に対する関数値y1を計算
	y1 = f(x1);
	//x2の算出
	x2 = x1 + delta_x;
	//引数付き関数形式マクロを利用してx2に対する関数値y2を計算
	y2 = f(x2);

	if (n == 1) {
		printf("反復回数n\tx1\tf(x1)\n");//途中経過表示タイトルをPC画面表示
		printf("%d\t%.8lf\t%.8lf\n", n, x1, f(x1));//n=1の時のそれぞれの値をPC画面表示
		fprintf(fp, "反復回数n,x1,y1\n");//途中経過表示タイトルをファイル出力
		fprintf(fp, "%d,%.8lf,%.8lf\n", n, x1, y1);//n=1の時のそれぞれの値をPC画面表示
	}
	else {
		printf("%d\t%.8lf\t%.8lf\n", n, x1, y1);//探索途中経過の値をPC画面表示
		fprintf(fp, "%d,%.8lf,%.8lf\n", n, x1, y1);//探索途中経過の値をファイル出力
	}
	x1 = x2;//x1をx2更新
	n++;//nを更新
	if (y1 * y2 <= 0) //近似解x1の探索処理の繰り返しループの脱出条件
	{
		fclose(fp);//ファイルをクローズ
		x1 = x1 - delta_x;//余分なΔxをx1から引いて正しい近似解x1に求めなおす
		return x1;//非線形方程式の近似解x1の値を自作関数呼び出し側 main 関数に戻す
	}
	else //x1を非線形方程式の近似解として判定できなかった場合
	{
		fclose(fp);//ファイルをクローズ
		return direct_recursion(x1, n);//現在のx1とnを実引数として、再帰関数呼び出しに戻り、非線形方程式の近似解の探索を続ける
	}
}