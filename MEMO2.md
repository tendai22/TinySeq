# zForth メモ

emit: c ---

  0 sys
  ASCII文字 c を出力デバイスに創出する(xputs(c))。

.:    n ---

  1 sys, 
  セルの値を出力デバイスに送出する(xprintf(ZF_CELL_FMT " ",zf_pop()))

tell:  top len --- 

  2 sys,
  dict[top] から len バイトを出力デバイスに送出する(xputs(*p++))

quit:  --- (exit)

  128 sys
  インタプリタをexit(0)する。

include: str --- 

  130 sys,
  ファイルをインクルードする。

save:        ---

  131 sys,
  zforth.saveにsaveする。

!:      d1 addr  ---

  0 !! と同義。d2が0ということ、ZF_MEM_SIZE_VAR、cell d1をaddrに書き込む。

!!:     d1 addr d2 --- 

  PRIM_POKE, ユーザ変数または辞書に書き込む。
  addr が userver領域なら、d1をaddrに書き込む
  それ以後の通常の辞書領域なら、d1を(zf_mem_size)大きさd2で書き込む。
  d2 == 0なら、d1を可変長cellとみなして書き込む(1,2, or 5バイト)
  ※小さい定数で4バイト使わないようにして辞書領域を節約するということかな。

@:      addr  ---

  0 @@ と同義。

@@:     addr len --- cell

  PRIM_PEEK、ユーザ変数または辞書からlen(zf_mem_size)で示す長さのデータを読み込む。

,:     d1 ---

  0 ,, と同義。セルを辞書エンコードして書き込む。      

,,:     d1 d2 --- 

  PRIM_COMMA、辞書にセルを書き込む。
  HEREにd1 (zf_mem_size)d2を書き込み、HEREをインクリメントする。

#:      

##:    addr len --- 

  PRIM_LEN, ユーザ変数または辞書領域addrから(zf_mem_size)lenの長さで1単位とみなし、そのバイト長を返す。

[:     ---

  コンパイルを中断する(compilingをゼロにする)。'['の後ろのワードはコンパイルされずに実行される。

]:     ---

  コンパイルを再開する。'[', ']'で囲まれた領域のワードは実行される。

postpone:   val ---

  変数'_postpone'に1を代入する。immediateワード(postponeはコンパイル中でも実行される)。

  コンパイル中にユーザ変数POSTPONEがtrueの場合、immediateワードもコンパイルされる。
  通常はimmediateワードはその場で実行されるが。

1+:

1-:

over:  

  1 pickと同義。

pick:     addr --- val

  PRIM_PICK, データスタックのaddr個前の値をpushする。

+!:       n addr ---

  addr の値に n を足す。"plus-store"と読む。

inc:      addr ---

  addrの値に 1 を足す。

dec:      addr ---

  addrの値を1減らす。

<:        n1 n2 ---  f

  n1 < n2 のとき true をpushする。

>:      n1 n2 --- f

  n1 > n2 のときtrueをpushする。trueはC言語の論理式の値(ゼロ以外)。

<=:     n1 n2 --- f

  n1 n2 < の結果と、n1 n2 = の結果を足して結果をpushする。n1,n2を保持するためにリターンスタックを一時的に使っている。

>=:     n1 n2 --- f

  n2 n1 <= に同じ。

=0:     n --- f

  n 0 = に同じ。

=:     n1 n2 --- f

  n0 == n1(C言語的に)の結果をプッシュする。

not:   n --- f

  n == 0 の結果をプッシュする。

!=:    n1 n2 --- f

  n1 == n2の結果がゼロならtrue, trueならゼロをプッシュする。

cr:    ---

  '\r'を出力デバイスに送出する。

br:    ---

  ' 'を出力デバイスに送出する。

..:    n --- n

  n の値を出力デバイスに送出するが、nを残したままにする。

here:  --- v

  変数hの値をプッシュする。

h:  --- v

  ユーザ変数HEREの値をプッシュする。

allot:     n ---

  ユーザ変数HEREの値にnを足す。

var:  var cccc ---

  変数ccccを定義する。ユーザ変数とは別の場所にあるようだ。一旦定義すると、

  cccc:    --- addr

  変数のアドレスを返し、!で書き込み、@ で読み出しができるようになる。

```
: var : ' lit , here 5 allot here swap ! 5 allot postpone ; ;
```

'()

::

次の単語文字列をcreateし、compilingを1にする。
createは、
```
+-------------------+
| 文字列長さ | flags |
| LATEST            |(前のエントリを指す)
|n | a| m| e| ...   |
```
を辞書に書き込み、LATESTにHEREを代入する。

lit:     --- cell

  PRIM_LIT, コンパイル中に書く。IP(インストラクションポインタ)が指すものを取り出し
  プッシュする。

':
  PRIM_TICK, 

# dict

dictはバイト配列。userverはdict先頭を指している。

 * zf_cells are encoded in the dictionary with a variable length:
 *
 * encode:
 *
 *    integer   0 ..   127  0xxxxxxx
 *    integer 128 .. 16383  10xxxxxx xxxxxxxx
 *    else                  11111111 <raw copy of zf_cell>


  