# zForth メモ

```
emit: c ---
```

  0 sys
  ASCII文字 c を出力デバイスに創出する(xputs(c))。

```
.:    n ---
```
  1 sys, 
  セルの値を出力デバイスに送出する(xprintf(ZF_CELL_FMT " ",zf_pop()))

```
tell:  top len --- 
```
  2 sys,
  dict[top] から len バイトを出力デバイスに送出する(xputs(*p++))

```
quit:  --- (exit)
```
  128 sys
  インタプリタをexit(0)する。

```
include: str --- 
```
  130 sys,
  ファイルをインクルードする。

```
save:        ---
```
  131 sys,
  zforth.saveにsaveする。

```
!:      d1 addr  ---
```
  0 !! と同義。d2が0ということ、ZF_MEM_SIZE_VAR、cell d1をaddrに書き込む。

```
!!:     d1 addr d2 --- 
```
  PRIM_POKE, ユーザ変数または辞書に書き込む。
  addr が userver領域なら、d1をaddrに書き込む
  それ以後の通常の辞書領域なら、d1を(zf_mem_size)大きさd2で書き込む。
  d2 == 0なら、d1を可変長cellとみなして書き込む(1,2, or 5バイト)

  ※小さい定数で4バイト使わないようにして辞書領域を節約するということかな。

```
@:      addr  ---
```
  0 @@ と同義。
```
@@:     addr len --- cell
```
  PRIM_PEEK、ユーザ変数または辞書からlen(zf_mem_size)で示す長さのデータを読み込む。
```
##:    addr len --- 
```
  PRIM_LEN, ユーザ変数または辞書領域addrから(zf_mem_size)lenの長さで1単位とみなし、そのバイト長を返す。
```
[:     ---
```
  コンパイルを中断する(compilingをゼロにする)。'['の後ろのワードはコンパイルされずに実行される。
```
]:     ---
```
  コンパイルを再開する。'[', ']'で囲まれた領域のワードは実行される。
```
postpone:   val ---
```
  変数'_postpone'に1を代入する。immediateワード(postponeはコンパイル中でも実行される)。

  コンパイル中にユーザ変数POSTPONEがtrueの場合、
  次のワード1個に限りimmediateワードもコンパイルされる。
  postponeは次のワード1つに掛かると考える。
```
1+:

1-:
```
```
over:  
```
  1 pickと同義。
```
pick:     addr --- val
```
  PRIM_PICK, データスタックのaddr個前の値をpushする。
```
+!:       n addr ---
```
  addr の値に n を足す。"plus-store"と読む。
```
inc:      addr ---
```
  addrの値に 1 を足す。
```
dec:      addr ---
```
  addrの値を1減らす。
```
<:        n1 n2 ---  f
```
  n1 < n2 のとき true をpushする。
```
>:      n1 n2 --- f
```
  n1 > n2 のときtrueをpushする。trueはC言語の論理式の値(ゼロ以外)。
```
<=:     n1 n2 --- f
```
  n1 n2 < の結果と、n1 n2 = の結果を足して結果をpushする。n1,n2を保持するためにリターンスタックを一時的に使っている。
```
>=:     n1 n2 --- f
```
  n2 n1 <= に同じ。
```
=0:     n --- f
```
  n 0 = に同じ。
```
=:     n1 n2 --- f
```
  n0 == n1(C言語的に)の結果をプッシュする。
```
not:   n --- f
```
  n == 0 の結果をプッシュする。
```
!=:    n1 n2 --- f
```
  n1 == n2の結果がゼロならtrue, trueならゼロをプッシュする。
```
cr:    ---
```
  '\r'を出力デバイスに送出する。
```
br:    ---
```
  ' 'を出力デバイスに送出する。
```
..:    n --- n
```
  n の値を出力デバイスに送出するが、nを残したままにする。
```
here:  --- v
```
  変数hの値をプッシュする。
```
h:  --- v
```
  ユーザ変数HEREの値をプッシュする。
```
allot:     n ---
```
  ユーザ変数HEREの値にnを足す。
```
var:   cccc ---
```

  変数ccccを定義する。ユーザ変数とは別の場所にあるようだ。一旦定義すると、

  cccc:    --- addr

  変数のアドレスを返し、!で書き込み、@ で読み出しができるようになる。


```
: var : ' lit , here 5 allot here swap ! 5 allot postpone ; ;
```

'()
```
::
```
次の単語文字列をcreateし、compilingを1にする。
createは、
```
+-------------------+
| 文字列長さ | flags |
| LATEST            |(前のエントリを指す)
|n | a| m| e| ...   |
```
を辞書に書き込み、LATESTにHEREを代入する。
```
':
```
  PRIM_TICK, コンパイル中は、次のセルをスタックにプッシュする。
  実行中は次のワードを入力から読み取り、辞書からfind_wordし、その結果をプッシュする。
  ワードが辞書になければinternal error.

```
lit:     --- cell
```
  PRIM_LIT, 
  lit(0x01)の次のセルを定数としてスタックに積む。機械語でいうイミディエイト命令らしい。
```
: const : ' lit , , postpone ; ;
```
定数を定義するワード定義を読み解く。
```
const :     ... constの次のワード(foo)を入力から読み取り辞書エントリを作る
      ' lit ... lit(イミディエイト命令)をスタックに積む
      ,     ... スタックに積んだもの(lit命令)を辞書に書き込む
      ,     ... スタックに積んだもの(constの前の定数値)を辞書に書き込む
      postpone ; ... ';'を辞書に書き込む。
      ;     ... constの定義終わり。
```
```
,:     d1 ---
```
  0 ,, と同義。セルを辞書エンコードして書き込む。      
```
,,:     d1 d2 --- 
```
  PRIM_COMMA、辞書にセルを書き込む。
  HEREにd1 (zf_mem_size)d2を書き込み、HEREをインクリメントする。

# dict

dictはバイト配列。userverはdict先頭を指している。

 zf_cells are encoded in the dictionary with a variable length:

 セルは(処理系内部では固定長だが)、辞書内では可変長で表現される。小さな値を
 
encode:
```
    integer   0 ..   127  0xxxxxxx
    integer 128 .. 16383  10xxxxxx xxxxxxxx
    else                  11111111 <raw copy of zf_cell>
```

# TinySeq ... シーケンサ実現メモ

## C言語レベルの実現

* グローバル変数 sequencer を一つ定義して、それへの書き込みシステムコールを作る。ワード ladderの辞書上アドレスを保持する。
```
zf_cell sequencer = 0;
```
* ラダー１サイクルを定義するワードを定義して、zf_cellに書き込むと、タイマ内でsequencerをみて、非ゼロならそれを呼び出す。

* 関数runを呼び出す。インストラクションポインタipを保存しておいて、完了後に戻す。dstack, rstackはladderワード内部でバランスをとるはずなのでとりあえず保存しない。run関数自体にreturn(exit)機能があるかどうかの調査が必要。

* タイマ関数自体はフラグを立てるだけで、呼び出しは メインループのgetline/getchar からリターンしてきてrunを呼び出してgetline/getcharに戻る。

* 開発時は繰り返しladderを定義する。zForthは同じワードを定義すると、以前のエントリはゴミとして残るので、ladderを定義する際は、辞書領域後半を固定的に確保しておき、そこを使う。

* ladder ワードを定義する専用のコロンワード `:seq`, `;seq` を用意する。この定義の間は、HEADをワード配列末尾の固定領域に移し、定義終了時に HEADを戻す。

* find_wordがLATESTからサーチを開始すること、シーケンサ用辞書をサーチしてから標準辞書をサーチする仕組みとする。シーケンサ用辞書に最初に定義したワードのnextリンクは標準辞書を指しているが、それ以後に標準辞書に追加したワードが参照されなくなるので、そこはnextリンクの書き換えまたはサーチを賢く行う必要がある。多分サーチを賢くした方が良い。

* core以外に複数のzfファイルをフラッシュに焼き込む仕組みが欲しい。

# TinySeq ... シーケンサ表現方法

```
:seq ladder
|-  X000.a   -|1
|-  M000.b   -|1
              |1- X001.b --- M000 -|
|-  M000.a  ---              Y000 -|
;seq
```
自己保持回路をラダーで書いた。スイッチX000を押すと、出力Y000がONになり、
スイッチX001を押すとOFFになる。

```
: |- ( --- 1) 1 ;
: |--         1 ;
```
P24ラインを表す。1 をプッシュする。

```
: --- ;
```
この線は何もしない。見栄えだけ。

```
: -| pop ;
: --| pop ;
```

COM側単点はvalをキャンセルするだけ。


```
: X000.a  0 1001 sys ;
: X001.a  1 1001 sys ;
: X001.b  not X001.a ;
: M000.a  0 1003 sys ;
: M000.b  not M000.a ;
: M000    0 1006 sys ;
: Y000    0 1005 sys ;
```

リレーコイル、スイッチは以下のシステムコールを使う。

```
 * Xnnn.a ... val nnn 1001 sys --> val' // refer Xnnn.a (inport) contact
 * Xnnn.b ... val nnn 1002 sys --> val' // refer Xnnn.b (inport) contact(negate switch)
 * Mnnn.a ... val nnn 1003 sys --> val' // refer Mnnn.a (internal) contact
 * Mnnn.b ... val nnn 1004 sys --> val' // refer Mnnn.b (internal) contact
 * Ynnn ... val nnn 1005 sys --> val    // set Ynnn(outport) coil
 * Mnnn ... val nnn 1006 sys --> val    // set Mnnn(internal) coil
 * Nnnn ... val delay nnn 1007 sys --> val    // set ON-Delay coil
 * Fnnn ... val delay nnn 1008 sys --> val    // set OFF-Delay coil

```

```
var |1     (単点全て変数として定義する)
1 |1 !     (サイクル先頭で初期化が必要)
: -|1 (変数|1にvalをOR set)  |1 @ OR |1 ! ;
: |1- (変数|1の値をvalに置く) |1 @ ;
: -|1- -|1 |1- ;
```
単点は全て自分で番号付けして管理する。

