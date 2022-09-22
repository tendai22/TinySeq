# TinySeqの仕様

#: ##と同じ。
##: PRIM_LEN: addr len --> peek結果をpush (addrからlenバイトを読込みstackにのせる)

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