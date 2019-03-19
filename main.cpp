#include <iostream>

#include "common.hpp"
#include "Hero.hpp"
#include "Battle.hpp"

using namespace std;

int main() {

    init();


    
    ifstream ifs( "heroes.txt" );

    if ( !ifs ) {
        cout << "cannot open heroes.txt" << endl;
        return 0;
    }

    Battle battle;
    
    for ( Side s = Attack; s < Side_End; s++ ) {
    for ( Order o = Front; o < Order_End; o++ ) {

        string line;
        if ( !getline( ifs, line ) ) {
            cout << "heroes.txt error" << endl; 
            system("pause");
            return 0;
        }

        istringstream iss( line );

        Position p = { s, o };
        ID id;
        ACTIVE_SKILL_ID asi[3];
        int attr[4];
        
        string s;
        getline( iss, s, '\t' );
        id = stoi( s );

        if ( convertIDToHeroIndex(id) == 0 ) {
            cout << "hero ID error" << endl; 
            system("pause");
            return 0;
        }

        for ( int i = 0; i < 3; i++ ) {
            if ( ! getline( iss, s, '\t' ) ) {
                cout << "heroes.txt error" << endl; 
                system("pause");
                return 0;
            }
            asi[i] = stoi( s );
            if ( !isValidActiveSkillID( asi[i] ) ) { cout << "active skill ID error" << endl; return 0; }
        }

        if ( !getline( ifs, line ) ) {
            cout << "heroes.txt error" << endl; 
            system("pause");
            return 0;
        }
        istringstream iss2( line );

        for ( Attr a = HP; a <= AGI; a++ ) {
            if ( ! getline( iss2, s, '\t' ) ) {
                cout << "heroes.txt error" << endl; 
                system("pause");
                return 0;
            }
            attr[a] = stoi( s );
            if ( attr[a] < 0 || attr[a] > 999 ) {
                cout << "hero status error" << endl; 
                system("pause");
                return 0;
            }
        }


        battle.setHero( p, id, attr, asi );
    }
    }

    ifs.close();

    
    int n_battle = 0;
    cin >> n_battle;



    battle.fileOpen();

    int win,lose;
    win = lose = 0;

    for ( int i = 0; i < n_battle; i++ ) {
        battle.startBattle();

        if ( !battle.isEndGameByDead( Attack ) && battle.isEndGameByDead( Defence ) ) { win++; }
        else { lose++; }

        battle.resetBattle();

        if ( i == 9 ) { battle.fileClose(); }
    }
    
    if ( n_battle < 10 ) { battle.fileClose(); }

    cout << "win: " << win << " " << "lose: " << lose << endl;


    system("pause");

    return 0;
}


// デバッグ用
// 全ヒーロー、全エクステンション、全アートエディットスキルの中からランダムに選んで編成し、戦闘を繰り返す
#if 0

int main() {

    init();

    /* -------------------- Hero　の設定 -------------------- */


    int attr[ATTR_END] = { 300, 200, 200, 100 };

    int r[5] = { NOVICE, UNCOMMON, RARE, EPIC, LEGENDARY };
    int rep[3] = { REP_B, REP_A, REP_S };

    vector<ID> v_hero_id;
    for ( int i = 0; i < 5; i++ ) {
        for ( int j = 1; j <= 100; j++ ) {
            ID id = r[i] + j;
            if ( convertIDToHeroIndex(id) == 0 ) { break; }
            v_hero_id.push_back(id);
        }
    }

    vector<ACTIVE_SKILL_ID> v_extension_id;
    vector<ACTIVE_SKILL_ID> v_art_edit_skill_id;

    for ( int type = 1; type <= n_extension_type; type++ ) {
        int id;
        for ( int i = 0; i < 5; i++ ) {
            id = r[i] + type;
            if ( isValidActiveSkillID( id ) ) {
                v_extension_id.push_back( id );
            }
        }
        for ( int j = 0; j < 3; j++ ) {
            id = rep[j] + type;
            if ( isValidActiveSkillID( id ) ) {
                v_extension_id.push_back( id );
            }
        }
    }
    for ( int i = 0; i < n_art_edit_skill-1; i++ ) {
        v_art_edit_skill_id.push_back( ART_EDIT_SKILL + i );
    }



    /* -------------------- Battle　の設定 -------------------- */


    
    int n_battle = 0;
    cin >> n_battle;


    
    Battle battle;

    battle.switchBattleLog( false );

    for ( int i = 0; i < n_battle; i++ ) {


        for ( Side s = Attack; s < Side_End; s++ ) {
        for ( Order o = Front; o < Order_End; o++ ) {
            Position p = { s, o };
            int id = v_hero_id[ Dice(0,v_hero_id.size()-1) ];
            ACTIVE_SKILL_ID asi[3];
            asi[0] = v_extension_id[ Dice( 0, v_extension_id.size()-1 ) ];
            asi[2] = v_extension_id[ Dice( 0, v_extension_id.size()-1 ) ];
            asi[1] = v_art_edit_skill_id[ Dice( 0, v_art_edit_skill_id.size()-1 ) ];
            battle.setHero( p, id, attr, asi );
        }
        }

        for ( int j = 0; j < 10; j++ ) {
            battle.startBattle();
        
            battle.resetBattle();
        }
        
    }

    return 0;
}


#endif








// ヒーローが追加されたときに変更/追加する箇所
// common.hpp のそれぞれのレアリティのヒーロー数
// common.cpp


// エクステンションが追加されたときに変更/追加する箇所
// common.hpp const int n_extension_type = xx;
// enum EXTENSION_TYPE
// common.cpp







// メモ


// 最もステータスが高い/低いヒーローが対象のスキルで、同じ値のヒーローが複数いた場合、
// 前衛 → 中衛 → 後衛 という優先順位でスキル効果が適用されることにする（要検証）


// INT,PHY,AGIの下限は1?0?

// 復活時のステータス　バフ/デバフされた値は初期値にもどるらしい（ピプリクト情報）

// 確率分布
// とりあえず一様分布にしておく


// 状態異常になる確率の計算　INT / INT

// battle 終了判定 200アクションで終了


// 「バトル開始時」のパッシブスキルは行動値上昇より前（暫定）


// パッシブスキルの発動条件をチェックする順番（暫定）（推測）
/*
１
    A「アクティブ時」
    B「バトル開始時一度だけ」
    C「ダメージを受けたとき」
    D「初めて自分のHPがX%未満になったとき一度だけ」
    E「初めて味方全体の合計HPがX%未満になったとき一度だけ」
    F「初めての死亡時に一度だけ」
２
    「X%の確率で」
３
    「混乱していないかつ睡眠状態ではないとき」
*/

// 混乱（睡眠）が解除されたときにパッシブスキルが発動する仕組み（暫定）（推測）
/*
C、D、E の場合
３のチェックで混乱か睡眠だったとき、スキルは発動せずそこでチェックは終了するが、１と２をクリアしたフラグがたつ

それ以降に発動条件をチェックするとき、そのフラグが立っていると１と２のチェックを飛ばす

アクティブ時に混乱（睡眠）が解除されると、（１と２のチェックを飛ばして）３の条件を満たしてスキルが発動したとき、フラグもクリアされる

つまりこの仕組みであるとすると、確率判定は混乱（睡眠）時に行われているということになる。

２と３の順番が逆、すなわち確率判定が混乱（睡眠）解除時に行われている可能性もあるが、
この仕組みが適用されているであろうA以外のスキルには現状確率判定が存在しない（100%発動する）ため、
検証不可能だと思われる。

Aのスキルは非アクティブ時に発動していない（要検証）ので、Aはこの仕組みの適用外だと思われる

とりあえず上記の仕組みを実装する（暫定）


また、B、D、E、Fは「初めて条件を満たしたときに一度だけ」発動するスキルだが、
もし２の条件があった場合、２の条件にチャレンジするチャンスは一度なのか複数回チャレンジ可能なのかという問題がある
（現状では確率条件があるB、D、E、Fのスキルは存在せず、100%発動するので検証しようがないが）

とりあえずチャンスは一度ということにしておく（暫定）

また、Bのバトル開始時に混乱（睡眠）になっていることは現状あり得ない（クエストでもバトル間に状態異常は解除される）（要検証）
よってBでこの仕組みが適用されるのかは不明だが、適用されるということにする（暫定）

Fの死亡時に状態異常の扱いがどうなっているのかは要検証
とりあえず、死ぬと状態異常がクリアされて通常状態に戻る → パッシブスキル発動する　ということにする（暫定）

*/

// 混乱（睡眠）状態で死亡したときに、パッシブスキルは発動するのか？
// 状態異常はクリアされて通常状態になり、スキルは発動する（暫定）（要検証）


// 死亡時に能力値とステータスは初期値に戻るとして、行動値はどうなるのか？
// ０になる


// （敵・味方）全体に a ~ b% ダメージ(バフ、デバフ、回復効果) というスキルは、１体ごとに倍率が違うのか？
// 少なくともダメージは１体ごとに違う
// 信玄のバフも１体ごと、能力値ごとに違うという報告あり
// 能力値ごとに確率判定がありそうなので、そのように実装する todo

// etheremon zedakazm スキルは敵１体ごとにかかる状態異常が違うのか？

// カフカ　AGIバフは自分自身？味方全体？　自分自身で実装
// 松尾芭蕉　先頭の味方へのAGIバフは、自己バフで上がったAGIの値を元に計算するのか？それともバフされる前の値が元なのか？　バフされる前で実装
// ヴァレンティヌス　先頭の味方を回復→最もHPの低い味方回復　or　先頭の味方と最もHPの低い味方を同時に回復　後者で実装
// 劉備　日本語が意味不明　「最もHPが低い味方のHPを20%の回復効果を与える」　20%の回復効果　なのか　HP20%分回復　のどちらなのか不明　前者で実装
// 孫堅　パッシブスキル前半の自傷ダメージで自分が死んだ場合、後半のバフ効果は発動するのか　発動するということにして実装
// カメハメハ大王　アクティブスキルによって受けたダメージ量の20%回復　でいいはずだけど要検証
