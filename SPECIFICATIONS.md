# zForthの仕様

## 表記の定義

|notation|description|
|---|---|
addr|memory address
b|8 bit byte (i.e. hi 8 bits zero)
c|7 bit ascii character (hi 9 bits zero)
d|32 bit signed double integer, most significant portion with sign on top of stack
f|boolean flag. 0=false, non-zero=true
ff|boolean false flag=0
n|16 bit signed integer number
u|16 bit unsigned integer
tf|boolean true flag=non-zero

The capital letters on the right show definition
characteristics:
|||
|---|---|
C|May only be used within a colon definition. A digit indicates number of memory addresses used, if other than one.
E|Intended for execution only.
L0|Level Zero definition of FORTH-78.
L1|Level One definition of FORTH-78.
P|Has precedence bit set. Will execute even when compiling.
U|A user variable.

## プリミティブワード

C言語で記述されたワード。
> exit, lit, <0, :, _;,
> +, -, *, /, %, drop, dup, pickr,
> _immediate, @@, !!, swap, rot,
> jmp, jmp0, ', _(, >r, r>, 
> =, sys, pick, ,,, key, lits, 
> ##, &, |, <<, >>

からなる。

### exit
```
    addr ---
```
リターンスタックの一番上の値をIPに書き込む。ワード実行からのリターン。

### lit
```
    --- n          C2,L0
```
PRIM_LIT, 
lit(0x01)の次のセルを定数としてスタックに積む。機械語でいうイミディエイト命令らしい。

Within a colon-definition, LIT is 
automatically compiled before each 16 
bit literal number encountered in input 
text. Later execution of LIT causes the
contents of the next dictionary address 
to be pushed to the stack.

### <0 (ltz ... less than zero)
```
   n1 --- f 
```
n1 が負の値の場合、trueを返す、さもなくばfalseを返す。

### : (col)
次の単語文字列をcreateし、compilingを1にする。
createは、辞書エントリ
```
      +-------------------+
HERE->| 文字列長さ | flags |
      | LATEST            |(前のエントリを指す)
      |n | a| m| e| ...   |
```
を辞書に書き込み、LATESTにHEREを代入する。

Used in the form called a colon-definition:
```
 : cccc ... ;
```
Creates a dictionary entry defining cccc
as equivalent to the following sequence 
of Forth word definitions '...' until 
the next ';' or ';CODE'. The compiling 
process is done by the text interpreter 
as long as STATE is non-zero. Other 
details are that the CONTEXT vocabulary 
is set to the CURRENT vocabulary and 
that words with the precedence bit set 
(P) are executed rather than being 
compiled.


### _; (semicol)

exit命令を辞書に追加し、COMPILINGをゼロにする。

### + (add)
```
   n1 n2 --- n 
```
n1, n2の和nをプッシュする。

### - (sub)
```
   n1 n2 --- n 
```
n1, n2の差nをプッシュする。


### * (multiply)
```
   n1 n2 --- n 
```
n1, n2の積nをプッシュする。

### / (slash)
```
   n1 n2 --- n 
```
n1, n2の商nをプッシュする。


### % (mod)
```
   n1 n2 --- n 
```
n1, n2の剰余nをプッシュする。

### drop
```
   val --- 
```
スタック上のデータを捨てる。

### dup
```
   val --- val val
```
スタック上のデータと同じものをpushする。

### pickr
```
    n1 --- n
```
  PRIM_PICKR, リターンスタックのn1個前の値nをpushする。



### _immediate

最近の定義ワードにimmediate属性を付ける。コンパイル時でも実行されるようになる。

Mark the most recently made definition 
so that when encountered at compile 
time, it will be executed rather than 
being compiled. I.e. the precedence bit
in its header is set. This method 
allows definitions to handle unusual 
compiling situations, rather than build 
them into the fundamental compiler. The
user may force compilation of an 
immediate definition by preceding it 
with [COMPILE].


### @@ (peek)
```
@@:     addr len --- cell
```
  PRIM_PEEK、ユーザ変数または辞書からlen(zf_mem_size)で示す長さのデータを読み込む。

### !! (poke)

```
!!:     cell1 addr d2 --- 
```
PRIM_POKE, ユーザ変数または辞書にcell1を書き込む。
addr が userver領域なら、cell1をaddrに書き込む
それ以後の通常の辞書領域なら、cell1を(zf_mem_size)大きさd2で書き込む。
d2 == 0なら、cell1を可変長cell(定数)とみなして書き込む(1,2, or 5バイト)

  ※小さい定数で4バイト使わないようにして辞書領域を節約するということかな。


### swap
```
    n1 n2 --- n2 n1
```
スタック最上2個の値を入れ替える。

### rot
```
 n1 n2 n3 --- n2 n3 n1       L0
```
Rotate the top three values on the 
stack, bringing the third to the top.

### jmp
```
    addr ---
```
スタック上のaddrにジャンプする。

### jmp0
```
    n addr ---
```
nがゼロの場合addrにジャンプする。

### ' (tick)
```
 --- addr P,L0
```
PRIM_TICK, コンパイル中は、次のセルをスタックにプッシュする。
実行中は次のワードを入力から読み取り、辞書からfind_wordし、その結果をプッシュする。
ワードが辞書になければinternal error.

Used in the form:
>  ' nnnn

Leaves the parameter field address of 
dictionary word nnnn. As a complier 
directive, executes in a colon-definition
to compile the address as a literal. If
the word is not found after a search of 
CONTEXT and CURRENT, an appropriate 
error message is given. Pronounced 
"tick".


### _( (comment)

コメントの開始、文字')'が来るまで読み飛ばす。

### >r (pushr)

スタックトップの値をリターンスタックにプッシュする。

### r> (popr)

リターンスタックトップの値をスタックにプッシュする。

### = (equal)
```
=:     n1 n2 --- f
```
  n0 == n1(C言語的に)の結果をプッシュする。

### sys
```
    n1 sys --- (処理依存)
```

システムコール。番号n1 のC言語機能の呼び出し。

### pick
```
pick:     addr --- val
```
  PRIM_PICK, データスタックのaddr個前の値をpushする。

### ,, (comma)
```
    cell siz --- L0
```
Store cell into the next available 
dictionary memory cell as specified siz, advancing the 
dictionary pointer. (comma)

### key
```
 --- c L0
```
Leave the ascii value of the next 
terminal key struck.

### lits
```
    ---  (ip) (next ip) 
```
IPが指すcellをスタックにプッシュし、その次のアドレスをスタックにプッシュする。即値命令の一種。

### ## (len)
```
  addr len --- cell
```
addrの位置のセル(辞書表現)の長さを返す。

### & (and)
```
    n1 n2 --- n
```
n1, n2のビット積。

### | (or)
```
    n1 n2 --- n
```
n1, n2のビット和。

### ^ (xor)
```
    n1 n2 --- n
```
n1, n2のビット排他的和。

### << (shl)
```
    n1 d --- n
```
n1をdビットだけ左シフト。


### >> (shr)
```
    n1 d --- n
```
n1をdビットだけ右シフト。

## 内部実装

### セル

セル1つで4バイト(int32_t)である。型zf_cellをint16_tにするだけで動くような気配はなかった。

### 辞書表記(短縮形式)

辞書のCFA領域にセルを置く際には短縮形式を使う。
```
    integer   0 ..   127  0xxxxxxx
    integer 128 .. 16383  10xxxxxx xxxxxxxx
    else                  11111111 <raw copy of zf_cell>
```
小さい整数の長さを小さくして格納できる。

### 辞書エントリ
```
      +-------------------+          +-------------------+
HERE->| 文字列長さ | flags |    |---->|                   |
      | LATEST            |----|     |                   |
      |n | a| m| e| ...   |          |                   |
```
を辞書に書き込み、LATESTにHEREを代入する。

## zForth Core仕様

core.zfにより定義されるワード、普通はこのファイルを読み込むはず。TinySeqでは減らすことを考えている。

### emit    0 sys ;
### .       1 sys ;
### tell    2 sys ;
### quit    128 sys ;
### sin     129 sys ;
### include 130 sys ;
### save    131 sys ;

### !    0 !! ;
### @    0 @@ ;
### ,    0 ,, ;
### #    0 ## ;

### [ 0 compiling ! ; immediate
### ] 1 compiling ! ;
### postpone 1 _postpone ! ; immediate

: 1+ 1 + ;
: 1- 1 - ;
: over 1 pick ;
: +!   dup @ rot + swap ! ;
: inc  1 swap +! ;
: dec  -1 swap +! ;
: <    - <0 ;
: >    swap < ;
: <=   over over >r >r < r> r> = + ;
: >=   swap <= ;
: =0   0 = ;
: not  =0 ;
: !=   = not ;
: cr   10 emit ;
: br 32 emit ;
: ..   dup . ;
: here h @ ;

# TinySeqの仕様

find_word(const char *name, zf_addr *word, zf_addr *code)
// nameを検索し、wordにwをcodeにcを返す。
// wはLATESTから開始する。
// wの指す位置からcell2つ(d, link)をとる。
// lenはdの下5bitを入れる。
// d, linkの次のバイトが名前文字列(name2)
//
//    32bit(4byte)
//    +---------------+
//LATEST         lllll|
//    | (link0)       |
//    |name0...       |
//    |   |code0...   |
//link0+--------------+
//    |          lllll|
//       ...
//    +---------------+
// w  |          lllll| d
// w+4| (link)        | link
// w+8|n  |a  |m  |e  |
// w+C|x  |¥0 |<-- code (= w + 8 + len(==lllll))
//    ~               ~
//link +---------------+
//    w|          lllll|
//     | (link2)       |
//     | name...       |
//     |    |code ...  |
//link2+---------------+
//(最終エントリはlink==0)
//
## ユーザ変数

h:
latest: 
trace: 1 をセットするとトレースを開始する。
compiling: コンパイル中フラグ、内部処理で用いる。
postpone: 次のimmediate wordをコンパイルすべきことを示す。

exit: 

lit: 