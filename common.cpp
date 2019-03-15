#include "common.hpp"

Side oppositeSide( Side s ) {
    return static_cast<Side>(static_cast<int>(s) ^ 1);
}












/* ------------------ ID ← → 名前  の変換 ------------------ */


vector<string> split(const string &str, char sep) {
    vector<string> v;        // 分割結果を格納するベクター
    auto first = str.begin();              // テキストの最初を指すイテレータ
    while( first != str.end() ) {         // テキストが残っている間ループ
        auto last = first;                      // 分割文字列末尾へのイテレータ
        while( last != str.end() && *last != sep )       // 末尾 or セパレータ文字まで進める
            ++last;
        v.push_back(string(first, last));       // 分割文字を出力
        if( last != str.end() )
            ++last;
        first = last;          // 次の処理のためにイテレータを設定
    }
    return v;
}




map<string,ID> hero_name_to_ID;


string hero_name_array[ n_novice + n_uncommon + n_rare + n_epic + n_legendary + 1 ] = {
    "error",
    // Novice    1xxxx
    "MCHウォーリアー",
    "MCHタクティシャン",
    "MCHアーティスト",
    "福沢諭吉",
    "孫尚香",
    "パスカル",
    "ダビデ",
    // Uncommon  2xxxx
    "ライト兄弟",
    "スパルタクス",
    "ジャック・ザ・リッパー",
    "シューベルト",
    "グリム兄弟",
    "アルキメデス",
    "サンタクロース",
    "シュレディンガー",
    "森蘭丸",
    "カフカ",
    "孫子",
    "石田三成",
    "許チョ",
    "徳川慶喜",
    // Rare      3xxxx
    "イーサエモン・レッド",
    "ダルタニャン",
    "平賀源内",
    "マタ・ハリ",
    "イーサエモン・ブルー",
    "イーサエモン・グリーン",
    "皇帝ネロ",
    "ノストラダムス",
    "太公望",
    "服部半蔵",
    "前田慶次",
    "天草四郎",
    "石川五右衛門",
    "直江兼続",
    "イワン雷帝",
    "松尾芭蕉",
    "三蔵法師",
    "武蔵坊弁慶",
    "黄忠",
    "貂蝉",
    "ヴァレンティヌス",
    "ポカホンタス",
    "孫堅",
    // Epic    4xxxx
    "張飛",
    "ナイチンゲール",
    "ベートーヴェン",
    "佐々木小次郎",
    "勝海舟",
    "ビリー・ザ・キッド",
    "トーマス・エジソン",
    "マルコ・ポーロ",
    "伊達政宗",
    "王キ",
    "マルクス",
    "沖田総司",
    "チャイコフスキー",
    "マリー・アントワネット",
    "楊貴妃",
    "呂布",
    "キュリー夫人",
    "孫権",
    "カメハメハ大王",
    "カラミティ・ジェーン",
    "ゴッホ",
    "巴御前",
    "趙雲",
    "岳飛",
    "武田信玄",
    "カエサル",
    // Legendary 5xxxx,
    "織田信長",
    "ナポレオン・ボナパルト",
    "曹操",
    "ジョージ・ワシントン",
    "レオナルド・ダ・ビンチ",
    "アーサー王",
    "ジャンヌ・ダルク",
    "坂本龍馬",
    "劉備",
    "アインシュタイン",
    "卑弥呼",
    "バッハ",
    "チンギス・ハン"
};




int convertIDToHeroIndex( ID id ) {
    int n = id % NOVICE;

    int r = id / NOVICE;
    switch ( r ) {
        case 1: // Novice
            if ( n == 0 || n > n_novice ) { return 0; }
            return novice_index + n;
            break;
        case 2: // Uncommon
            if ( n == 0 || n > n_uncommon ) { return 0; }
            return uncommon_index + n;
            break;
        case 3: // Rare
            if ( n == 0 || n > n_rare ) { return 0; }
            return rare_index + n;
            break;
        case 4: // Epic
            if ( n == 0 || n > n_epic ) { return 0; }
            return epic_index + n;
            break;
        case 5: // Legendary
            if ( n == 0 || n > n_legendary ) { return 0; }
            return legendary_index + n;
            break;
        default: return 0;
    }
}

string convertIDToHeroName( ID id ) {
    return hero_name_array[ convertIDToHeroIndex( id ) ];
}




/* extension */
/*
original
Legendary 5xxxx
Epic      4xxxx
Rare      3xxxx
Uncommon  2xxxx
Novice    1xxxx

現状、レプリカF～Bのスキルはすべて同じだが、今後変わる可能性もあるので
番号だけは用意しておく
replica
rep.S     70xxxx
rep.A     60xxxx
rep.B     50xxxx
rep.C     40xxxx
rep.D     30xxxx
rep.E     20xxxx
rep.F     10xxxx
*/

/*
xxxxx1    blade       ブレード
xxxxx2    musket      マスケット
xxxxx3    Quill       ペン
xxxxx4    Armor       アーマー
xxxxx5    Horse       ホース
xxxxx6    Katana      カタナ
xxxxx7    Cutie       キューティー
xxxxx8    Book        ブック
xxxxx9    Ring        リング
xxxx10    Shield      シールド
xxxx11    Axe         アックス
xxxx12    Etheremon   イーサエモン
xxxx13    Yumi        ユミ
xxxx14    Cross Spear クロススピア
xxxx15    Halberd     ハルバード
xxxx16    Scrolls     スクロール
xxxx17    Necklace    ネックレス
xxxx18    Kabuto      カブト
xxxx19    Turtle      タートル
xxxx20    Roostler    ルースター
xxxx21    Tiger       タイガー
xxxx22    Dragon      ドラゴン
xxxx23    Bull        ブル
xxxx24    Elephant    エレファント
xxxx25    Monkey      モンキー
xxxx26    Snake       スネーク
xxxx27    Dog         ドッグ
*/


map<string,ID> extension_name_to_ID;
map<string, ACTIVE_SKILL_ID> ExtensionType_name_to_ID;
map<string, ACTIVE_SKILL_ID> extension_replica_rarity_to_ID;

void initExtensionNameToID() {
    
    // 使用するのはレプリカだけなのでキューティーとイーサエモンは入っていない
    ExtensionType_name_to_ID["ブレード"] = static_cast<ACTIVE_SKILL_ID>(BLADE);
    ExtensionType_name_to_ID["マスケット"] = static_cast<ACTIVE_SKILL_ID>(MUSKET);
    ExtensionType_name_to_ID["ペン"] = static_cast<ACTIVE_SKILL_ID>(QUILL);
    ExtensionType_name_to_ID["アーマー"] = static_cast<ACTIVE_SKILL_ID>(ARMOR);
    ExtensionType_name_to_ID["ホース"] = static_cast<ACTIVE_SKILL_ID>(HORSE);
    ExtensionType_name_to_ID["カタナ"] = static_cast<ACTIVE_SKILL_ID>(KATANA);
    ExtensionType_name_to_ID["ブック"] = static_cast<ACTIVE_SKILL_ID>(BOOK);
    ExtensionType_name_to_ID["リング"] = static_cast<ACTIVE_SKILL_ID>(RING);
    ExtensionType_name_to_ID["シールド"] = static_cast<ACTIVE_SKILL_ID>(SHIELD);
    ExtensionType_name_to_ID["アックス"] = static_cast<ACTIVE_SKILL_ID>(AXE);
    ExtensionType_name_to_ID["ユミ"] = static_cast<ACTIVE_SKILL_ID>(YUMI);
    ExtensionType_name_to_ID["クロススピア"] = static_cast<ACTIVE_SKILL_ID>(SPEAR);
    ExtensionType_name_to_ID["ハルバード"] = static_cast<ACTIVE_SKILL_ID>(HALBERD);
    ExtensionType_name_to_ID["スクロール"] = static_cast<ACTIVE_SKILL_ID>(SCROLLS);
    ExtensionType_name_to_ID["ネックレス"] = static_cast<ACTIVE_SKILL_ID>(NECKLACE);
    ExtensionType_name_to_ID["カブト"] = static_cast<ACTIVE_SKILL_ID>(KABUTO);
    ExtensionType_name_to_ID["タートル"] = static_cast<ACTIVE_SKILL_ID>(TURTLE);
    ExtensionType_name_to_ID["ルースター"] = static_cast<ACTIVE_SKILL_ID>(ROOSTLER);
    ExtensionType_name_to_ID["タイガー"] = static_cast<ACTIVE_SKILL_ID>(TIGER);
    ExtensionType_name_to_ID["ドラゴン"] = static_cast<ACTIVE_SKILL_ID>(DRAGON);
    ExtensionType_name_to_ID["ブル"] = static_cast<ACTIVE_SKILL_ID>(BULL);
    ExtensionType_name_to_ID["エレファント"] = static_cast<ACTIVE_SKILL_ID>(ELEPHANT);
    ExtensionType_name_to_ID["モンキー"] = static_cast<ACTIVE_SKILL_ID>(MONKEY);
    ExtensionType_name_to_ID["スネーク"] = static_cast<ACTIVE_SKILL_ID>(SNAKE);
    ExtensionType_name_to_ID["ドッグ"] = static_cast<ACTIVE_SKILL_ID>(DOG);

    extension_replica_rarity_to_ID["RepS"] = REP_S;
    extension_replica_rarity_to_ID["RepA"] = REP_A;
    extension_replica_rarity_to_ID["RepB"] = REP_B;
    extension_replica_rarity_to_ID["RepC"] = REP_C;
    extension_replica_rarity_to_ID["RepD"] = REP_D;
    extension_replica_rarity_to_ID["RepE"] = REP_E;
    extension_replica_rarity_to_ID["RepF"] = REP_F;

    // xxxxx1    blade       ブレード
    extension_name_to_ID["ノービスブレード"] = COMMON + static_cast<int>(BLADE);
    extension_name_to_ID["エリートブレード"] = UNCOMMON + static_cast<int>(BLADE);
    extension_name_to_ID["ブレイブブレード"] = RARE + static_cast<int>(BLADE);
    extension_name_to_ID["インペリアルブレード"] = EPIC + static_cast<int>(BLADE);
    extension_name_to_ID["MCHブレード"] = LEGENDARY + static_cast<int>(BLADE);
    // xxxxx2    musket      マスケット
    extension_name_to_ID["ノービスマスケット"] = COMMON + static_cast<int>(BLADE);
    extension_name_to_ID["エリートマスケット"] = UNCOMMON + static_cast<int>(BLADE);
    extension_name_to_ID["ブレイブマスケット"] = RARE + static_cast<int>(BLADE);
    extension_name_to_ID["三銃士のマスケット"] = EPIC + static_cast<int>(BLADE);
    extension_name_to_ID["グランダルメ"] = LEGENDARY + static_cast<int>(BLADE);


    extension_name_to_ID["休む"] = ART_EDIT_SKILL + 0;
    extension_name_to_ID["レッドストライク"] = ART_EDIT_SKILL + 1;
    extension_name_to_ID["ハット・トリック"] = ART_EDIT_SKILL + 2;
    extension_name_to_ID["Punks Not Dead"] = ART_EDIT_SKILL + 3;
    extension_name_to_ID["マゼンタマッシュルーム"] = ART_EDIT_SKILL + 4;
    extension_name_to_ID["ゴロゴロパンチ"] = ART_EDIT_SKILL + 5;
    extension_name_to_ID["無垢なる忠誠"] = ART_EDIT_SKILL + 6;
    extension_name_to_ID["サイドワインダー"] = ART_EDIT_SKILL + 7;
    extension_name_to_ID["女神のウインク"] = ART_EDIT_SKILL + 8;
    extension_name_to_ID["自由の女神"] = ART_EDIT_SKILL + 9;
    extension_name_to_ID["ブラックシャウト"] = ART_EDIT_SKILL + 10;
    extension_name_to_ID["モンキー・マジック"] = ART_EDIT_SKILL + 11;
    extension_name_to_ID["ガールズ・トーク"] = ART_EDIT_SKILL + 12;
    extension_name_to_ID["ダンディズム"] = ART_EDIT_SKILL + 13;
    extension_name_to_ID["中二病"] = ART_EDIT_SKILL + 14;
    extension_name_to_ID["万里の長城"] = ART_EDIT_SKILL + 15;
    extension_name_to_ID["霊峰富士"] = ART_EDIT_SKILL + 16;
    extension_name_to_ID["イエローブラスト"] = ART_EDIT_SKILL + 17;
    extension_name_to_ID["グリーンリース"] = ART_EDIT_SKILL + 18;
    extension_name_to_ID["シアンフロスト"] = ART_EDIT_SKILL + 19;
    extension_name_to_ID["ハード・トレーニング"] = ART_EDIT_SKILL + 20;
    extension_name_to_ID["ハイ・フライヤー"] = ART_EDIT_SKILL + 21;
    extension_name_to_ID["フル・スロットル"] = ART_EDIT_SKILL + 22;
    extension_name_to_ID["ブルーブロッサム"] = ART_EDIT_SKILL + 23;
    extension_name_to_ID["眼鏡効果"] = ART_EDIT_SKILL + 24;
    extension_name_to_ID["ホワイトキャンディー"] = ART_EDIT_SKILL + 25;
    extension_name_to_ID["森林浴"] = ART_EDIT_SKILL + 26;
    extension_name_to_ID["無条件幸福"] = ART_EDIT_SKILL + 27;
    extension_name_to_ID["紳士の品格"] = ART_EDIT_SKILL + 28;
}

string extension_name_array[ n_extension_type * n_original_rank + 1 + n_art_edit_skill ] = {
    "dummy",
    // xxxxx1    blade       ブレード
    "ノービスブレード",
    "エリートブレード",
    "ブレイブブレード",
    "インペリアルブレード",
    "MCHブレード",
    // xxxxx2    musket      マスケット
    "ノービスマスケット",
    "エリートマスケット",
    "ブレイブマスケット",
    "三銃士のマスケット",
    "グランダルメ",
    // xxxxx3    Quill       ペン
    "ノービスペン",
    "エリートペン",
    "ウィズダムペン",
    "楽聖の羽ペン",
    "劇作家の羽ペン",
    // xxxxx4    Armor       アーマー
    "ノービスアーマー",
    "エリートアーマー",
    "ブレイブアーマー",
    "フリューテッドアーマー",
    "MCHアーマー",
    // xxxxx5    Horse       ホース
    "ノービスホース",
    "エリートホース",
    "ブレイブホース",
    "赤兎馬",
    "ブケファロス",
    // xxxxx6    Katana      カタナ
    "ノービスカタナ",
    "エリートカタナ",
    "ブレイブカタナ",
    "和泉守兼定",
    "へし切長谷部",
    // xxxxx7    Cutie       キューティー
    "キューティー・キャット",
    "キューティー・九尾",
    "キューティー・エイリアン",
    "dummy",
    "dummy",
    // xxxxx8    Book        ブック
    "ノービスブック",
    "エリートブック",
    "ウィズダムブック",
    "罪と罰",
    "アトランティコ手稿",
    // xxxxx9    Ring        リング
    "ノービスリング",
    "エリートリング",
    "ウィズダムリング",
    "奇石の輝き",
    "王妃の指輪",
    // xxxx10    Shield      シールド
    "ノービスシールド",
    "エリートシールド",
    "ブレイブシールド",
    "プリトウェン",
    "アイギス",
    // xxxx11    Axe         アックス
    "アックス",
    "エリートアックス",
    "ブレイブアックス",
    "テカムセのトマホーク",
    "バイキングアックス",
    // xxxx12    Etheremon   イーサエモン
    "エコピー",
    "マラケレ",
    "マプラ",
    "シベリゼン",
    "ゼダカン",
    // xxxx13    Yumi        ユミ
    "ユミ",
    "エリートユミ",
    "ブレイブユミ",
    "雷上動",
    "与一の弓",
    // xxxx14    Cross Spear クロススピア
    "クロススピア",
    "エリートクロススピア",
    "ブレイブクロススピア",
    "人間無骨",
    "蜻蛉切",
    // xxxx15    Halberd     ハルバード
    "ハルバード",
    "エリートハルバード",
    "ブレイブハルバード",
    "丈八蛇矛",
    "方天画戟",
    // xxxx16    Scrolls     スクロール
    "スクロール",
    "エリートスクロール",
    "ウィズダムスクロール",
    "兵法書",
    "大唐西域記",
    // xxxx17    Necklace    ネックレス
    "ネックレス",
    "エリートネックレス",
    "ウィズダムネックレス",
    "シベリア杉の首飾り",
    "太陽神の首飾り",
    // xxxx18    Kabuto      カブト
    "カブト",
    "エリートカブト",
    "ブレイブカブト",
    "諏訪法性兜",
    "弦月形鍬形兜",
    // xxxx19    Turtle      タートル
    "タートル",
    "エリートタートル",
    "ウィズダムタートル",
    "アーケロン",
    "アクーパーラ",
    // xxxx20    Roostler    ルースター
    "ルースター",
    "エリートルースター",
    "ブレイブルースター",
    "ホットスパー",
    "金鶏",
    // xxxx21    Tiger       タイガー
    "タイガー",
    "エリートタイガー",
    "ブレイブタイガー",
    "アムールタイガー",
    "サーベルタイガー",
    // xxxx22    Dragon      ドラゴン
    "ドラゴン",
    "エリートドラゴン",
    "ウィズダムドラゴン",
    "ワイバーン",
    "金龍",
    // xxxx23    Bull        ブル
    "ブル",
    "エリートブル",
    "ブレイブブル",
    "バイソン",
    "金牛",
    // xxxx24    Elephant    エレファント
    "エレファント",
    "エリートエレファント",
    "ブレイブエレファント",
    "マンモス",
    "ハンニバルの軍象",
    // xxxx25    Monkey      モンキー
    "モンキー",
    "エリートモンキー",
    "ウィズダムモンキー",
    "シルバーバック",
    "狒々",
    // xxxx26    Snake       スネーク
    "スネーク",
    "エリートスネーク",
    "ウィズダムスネーク",
    "キングコブラ",
    "ケツァルコアトル",
    // xxxx27    Dog         ドッグ
    "ドッグ",
    "エリートドッグ",
    "ウィズダムドッグ",
    "モロッサス",
    "しっぺい太郎",

    // アートエディットスキル    
    "休む",
    "レッドストライク",
    "ハット・トリック",
    "Punks Not Dead",
    "マゼンタマッシュルーム",
    "ゴロゴロパンチ",
    "無垢なる忠誠",
    "サイドワインダー",
    "女神のウインク",
    "自由の女神",
    "ブラックシャウト",
    "モンキー・マジック",
    "ガールズ・トーク",
    "ダンディズム",
    "中二病",
    "万里の長城",
    "霊峰富士",
    "イエローブラスト",
    "グリーンリース",
    "シアンフロスト",
    "ハード・トレーニング",
    "ハイ・フライヤー",
    "フル・スロットル",
    "ブルーブロッサム",
    "眼鏡効果",
    "ホワイトキャンディー",
    "森林浴",
    "無条件幸福",
    "紳士の品格"
};

// キューティーとイーサエモンにレプリカはないので使用しないが、index がずれるので入れておく
string extension_type_name_array[ n_extension_type + 1 ] = {
    "dummy",
    "ブレード",
    "マスケット",
    "ペン",
    "アーマー",
    "ホース",
    "カタナ",
    "キューティー",
    "ブック",
    "リング",
    "シールド",
    "アックス",
    "イーサエモン",
    "ユミ",
    "クロススピア",
    "ハルバード",
    "スクロール",
    "ネックレス",
    "カブト",
    "タートル",
    "ルースター",
    "タイガー",
    "ドラゴン",
    "ブル",
    "エレファント",
    "モンキー",
    "スネーク",
    "ドッグ",
};

string IDToReplicaRankName[n_replica_rank+1] = {
    "dummy", "RepF", "RepE", "RepD", "RepC", "RepB", "RepA", "RepS",
};

// ACTIVE_SKILL_ID → ActiveSkillType（オリジナル、レプリカ、アートエディットスキル）
ActiveSkillType IDToActiveSkillType( ACTIVE_SKILL_ID id ) {
    if ( id >= ART_EDIT_SKILL + n_art_edit_skill ) { return ELSE; }
    else if ( id >= ART_EDIT_SKILL ) { return ARTEDIT; }
    else if ( id >= REP_F ) { return REPLICA; }
    else if ( id >= COMMON ) { return ORIGINAL; }
    else { return ELSE; }
}



ACTIVE_SKILL_ID convertExtensionNameToID( string s ) {

    ACTIVE_SKILL_ID ret;

    // replica
    if ( s.substr( s.length()-4, 3 ) == "Rep" ) {
        vector<string> vs;
        vs = split( s, '.' );
        assert( vs.size() == 2 );
        ret = ExtensionType_name_to_ID[ vs[0] ] + extension_replica_rarity_to_ID[ vs[1] ];        
    }
    //original
    else {
        ret = extension_name_to_ID[s];
    }

    return ret;
}


string convertIDToExtensionName( ACTIVE_SKILL_ID id ) {

    string ret = "";

    int type = id % extension_type_mask;

    switch ( IDToActiveSkillType(id) ) {
        case REPLICA:
            {                
                assert( static_cast<ExtensionType>(type) != ETHEREMON && static_cast<ExtensionType>(type) != CUTIE );

                ret += extension_type_name_array[type];
                ret += '.';

                int rank = id / ( extension_type_mask*10 );

                ret += IDToReplicaRankName[rank];
            }
            break;
        case ORIGINAL:
            {
                int rank = id / extension_type_mask;
                assert( type > 0 );
                ret += extension_name_array[ (type-1)*n_original_rank + rank];
            }
            break;
    
        case ARTEDIT:
            {
                ret += extension_name_array[ n_extension_type * n_original_rank + 1 + type ];                
            }
            break;

        default: assert( false );
    }

    return ret;
}

bool isValidActiveSkillID( ACTIVE_SKILL_ID id ) {

    int type = id % COMMON;
    
    switch ( IDToActiveSkillType(id) ) {
        case REPLICA:
            if ( type == 0 || type > n_extension_type ) { return false; }
            if ( !( 1 <= (id / REP_F) && (id / REP_F) <= 7 ) ) { return false; }
            if ( type == ETHEREMON || type == CUTIE ) { return false; }
            return true;

        case ORIGINAL:
            if ( type == 0 || type > n_extension_type ) { return false; }
            if ( !( 1 <= (id / COMMON) && (id / COMMON) <= 5 ) ) { return false; }
            if ( type == CUTIE && id >= EPIC ) { return false; }

            return true;
        case ARTEDIT:
            return true;
        default: return false;
    }


}




string orderName[3] = { "前衛", "中衛", "後衛" };
string sideName[2] = { "Attack側", "Defence側" };

string statusName[4] = { "", "混乱", "睡眠", "毒" };
string attributeName[4] = { "HP", "PHY", "INT", "AGI" };


string orderToName( Order o ) {
    return orderName[o];
}
string sideToName( Side s ) {
    return sideName[s];
}
string statusToName( Status s ) {
    return statusName[s];
}
string attributeToName( Attr a ) {
    return attributeName[a];
}

string uniformStringLength( string s, unsigned int length ) {
    string ret = s;
    while ( ret.length() < length ) {
        ret.push_back( ' ' );
    }
    return ret;
}




void init() {
    initExtensionNameToID();
}



// a 以上 b 以下の整数の中から等確率で選び、その整数を返す
int Dice( int a, int b ) {

    mt19937 mt{ random_device{}() };

    // a 以上 b 以下の値を等確率で発生させる
    uniform_int_distribution<> dist( a, b );
    return dist(mt);

}

// p % の確率で true、100-p%の確率で false を返す
bool determineByDice( int p ) {
    return ( Dice(1,100) <= p );
}
