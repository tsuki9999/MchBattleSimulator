#ifndef COMMON_HPP
#define COMMON_HPP

#include <algorithm>
#include <functional>
#include <random>
#include <cassert>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>
#include <cstdlib>


using namespace std;

typedef int ID;

typedef int ACTIVE_SKILL_ID;
typedef int ACTION_VALUE;
typedef int ACTION_STAGE; // 次に何番目のアクティブスキルを使うか(0~2)


const ACTIVE_SKILL_ID ART_EDIT_SKILL = 100000;

/*
Legendary 5xxxx
Epic      4xxxx
Rare      3xxxx
Uncommon  2xxxx
Novice    1xxxx
*/

const int LEGENDARY = 5000;
const int EPIC = 4000;
const int RARE = 3000;
const int UNCOMMON = 2000;
const int NOVICE = 1000;
const int COMMON = 1000;

/*
replica
rep.S     70xxxx
rep.A     60xxxx
rep.B     50xxxx
rep.C     40xxxx
rep.D     30xxxx
rep.E     20xxxx
rep.F     10xxxx
*/
const ACTIVE_SKILL_ID REP_S = 70000;
const ACTIVE_SKILL_ID REP_A = 60000;
const ACTIVE_SKILL_ID REP_B = 50000;
const ACTIVE_SKILL_ID REP_C = 40000;
const ACTIVE_SKILL_ID REP_D = 30000;
const ACTIVE_SKILL_ID REP_E = 20000;
const ACTIVE_SKILL_ID REP_F = 10000;

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
xxxx28    Rapier      レイピア
xxxx29    Revolver    リボルバー
xxxx30    Goblet      ゴブレット
xxxx31    Boots       ブーツ
*/

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!エクステンションが追加されたら変更すること!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
const int n_extension_type = 31;

const int n_replica_rank = 7; // F ~ S
const int n_original_rank = 5; // common ~ legendary
const int n_extension_rarity = n_replica_rank + n_original_rank;

const int extension_type_mask = 1000; // ACTIVE_SKILL_IDに対してこれの剰余をとると下４ケタが残り、エクステンションの種類がわかる

// アートエディットスキル
const int n_art_edit_skill = 29;

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!エクステンションが追加されたら追加すること!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
enum ExtensionType {
    DUMMY, BLADE, MUSKET, QUILL, ARMOR, HORSE, KATANA, CUTIE, BOOK, RING,
    SHIELD, AXE, ETHEREMON, YUMI, SPEAR, HALBERD, SCROLLS, NECKLACE, KABUTO, TURTLE,
    ROOSTLER, TIGER, DRAGON, BULL, ELEPHANT, MONKEY, SNAKE, DOG, RAPIER, REVOLVER, GOBLET, BOOTS,
};

enum ActiveSkillType {
    ORIGINAL, REPLICA, ARTEDIT, ELSE
};




// それぞれのレアリティのヒーロー数
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!ヒーローが追加されたら変更すること!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
const int n_novice = 8;
const int n_uncommon = 15;
const int n_rare = 24;
const int n_epic = 27;
const int n_legendary = 16;

// この index に ID の下４ケタを足した値が、Passive Skill 関数の index
const int novice_index = 0;
constexpr int uncommon_index = novice_index + n_novice;
constexpr int rare_index = uncommon_index + n_uncommon;
constexpr int epic_index = rare_index + n_rare;
constexpr int legendary_index = epic_index + n_epic;

enum Attr {
    HP, PHY, INT, AGI, ATTR_END
};
inline Attr& operator += (Attr& lhs, const int rhs) { return lhs  = static_cast<Attr>(static_cast<Attr>(lhs) + rhs); }
inline Attr operator ++ (Attr& lhs) { lhs += 1; return lhs; } /* 前置 */
inline Attr operator ++ (Attr& lhs, int) { const Attr temp = lhs; lhs += 1; return temp; } /* 後置 */


enum Status {
    Normal, // 通常状態
    Confusion, // 混乱
    Sleep, // 睡眠
    Poison // 毒
};

enum Side {
    Attack,
    Defence,
    Side_End
};
inline Side& operator += (Side& lhs, const int rhs) { return lhs  = static_cast<Side>(static_cast<Side>(lhs) + rhs); }
inline Side operator ++ (Side& lhs) { lhs += 1; return lhs; } /* 前置 */
inline Side operator ++ (Side& lhs, int) { const Side temp = lhs; lhs += 1; return temp; } /* 後置 */


enum Order {
    // 前衛、中衛、後衛
    Front, Middle, Back, Order_End
};
inline Order& operator += (Order& lhs, const int rhs) { return lhs  = static_cast<Order>(static_cast<Order>(lhs) + rhs); }
inline Order operator ++ (Order& lhs) { lhs += 1; return lhs; } /* 前置 */
inline Order operator ++ (Order& lhs, int) { const Order temp = lhs; lhs += 1; return temp; } /* 後置 */

// スキル対象
enum Target {
    OneSelf, // 自分自身
    AllAlly, // 味方すべて
    AllEnemy, // 敵すべて
    AllHero, // 敵味方すべて
    FrontAlly, // 味方の先頭
    FrontEnemy, // 敵の先頭
    Random
};


/* ---------------------- スキル関数に渡す引数に使う ---------------------- */

const bool BUFF = true;
const bool DEBUFF = false;

const bool ACTIVE_DAMAGE = true;
const bool NOT_ACTIVE_DAMAGE = false;

const bool HIGH = true;
const bool LOW = false;

const bool ALLY = true;
const bool ENEMY = false;







typedef struct Position {
    Side side;
    Order order;

    // ソートするための演算子のオーバーロード
    // 攻撃側前衛 → 攻撃側中衛 → 攻撃側後衛
    // → 防御側前衛 → 防御側中衛 → 防御側後衛
    // 数字が小さい方が行動順では優先されるので、逆向きになっている
    bool Position::operator < ( const Position& rhs ) const {

        int l = side*10 + order;
        int r = rhs.side*10 + order;

        return l > r;
    }
    bool Position::operator > ( const Position& rhs ) const {
        
        int l = side*10 + order;
        int r = rhs.side*10 + order;

        return l < r;
    }
    bool Position::operator <= ( const Position& rhs ) const {
        
        int l = side*10 + order;
        int r = rhs.side*10 + order;

        return l >= r;
    }
    bool Position::operator >= ( const Position& rhs ) const {
        
        int l = side*10 + order;
        int r = rhs.side*10 + order;

        return l <= r;
    }

    bool Position::operator == ( const Position& rhs ) const {
        return ( ( side == rhs.side ) && ( order == rhs.order ) );
    }
    bool Position::operator != ( const Position& rhs ) const {
        return !( *this == rhs );
    }


} Position;



vector<string> split(const string &str, char sep);

// ID → hero_name_array / パッシブスキル関数 の index
int convertIDToHeroIndex( ID id );



string convertIDToHeroName( ID id );


string convertIDToExtensionName( ACTIVE_SKILL_ID id );
bool isValidActiveSkillID( ACTIVE_SKILL_ID id );

string orderToName( Order o );
string sideToName( Side s );
string statusToName( Status s );
string attributeToName( Attr a );

ActiveSkillType IDToActiveSkillType( ACTIVE_SKILL_ID id );

string uniformStringLength( string s, unsigned int length );

void init();
void initHeroNameToID();
void initExtensionNameToID();


Side oppositeSide( Side s );
bool isValidPosition( Position p );


int Dice( int a, int b );
bool determineByDice( int p );

#endif