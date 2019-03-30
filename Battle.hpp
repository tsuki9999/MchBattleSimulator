#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "common.hpp"
#include "Hero.hpp"


class Battle {
    

    private:

    Hero heroes[2][3];

    mt19937 mt{ random_device{}() };

    // ログ出力するときは true になる
    // ログ出力ファイルを開くのに成功したら true 閉じたときに false に戻す
    bool print_battle_log = true;

    // アクション数
    int n_action = 0;

    // アクティブ時のヒーローの Position
    Position p_active = { Side_End, Order_End };

    // バトル開始時かどうか
    // バトル開始時にパッシブスキルが発動するかチェックする前に true にし、チェックが終了したら false にする    
    bool pre_battle;

    // バトルログを出力するファイルストリーム
    ofstream ofs_battle_log;

    void increaseActionValue();

    // 戦闘が終了したら true そうでなければ false を返す
    bool useSkills();    // アクティブスキル発動フェイズ → パッシブスキル発動フェイズ
    bool usePassiveSkills();   // パッシブスキル発動フェイズ

    // 睡眠か混乱なら true を返す
    bool isSleepOrCofusion( Status s );
    // 状態異常（通常状態以外）なら true を返す
    bool isAilment( Status s );
    // p の位置にいるヒーローが毒ダメージを受ける
    void poisonDamage( Position p );
    // p の位置にいるヒーローが混乱によるランダム攻撃をする
    void confusionRandomAttack( Position p );
    // p の位置にいるヒーローが死んでいたら true を返す
    bool isDead( Position p );
    
    // PHY/INT攻撃のダメージ計算
    int calcDamage( int attack, int rate, int attacked );
    // 回復効果の計算
    int calcHeal( int inte, int phy, int rate );
    // 回復効果の計算（サンタクロースのパッシブ用）
    int calcHeal( int inte, int phy, double rate );
    // value の rate% 回復
    int calcHeal( int value, int rate );
    // 状態異常になるかどうか、確率で決定
    bool determineStatusAilment( int int_attack, int int_attacked );
    // 状態異常が回復するかどうか、確率で決定
    bool determineNormalization();

    // p の位置にいるヒーローのある能力値が初期値より下がっている分の数値を返す（下がっていなかったら０を返す）
    int calcDebuff( Position p, Attr a );
    // ある Side のヒーローたちのある能力値が初期値より下がっている分の合計値を返す（下がっていなかったら０を返す）
    int calcDebuff( Side s, Attr a );


    // アクティブスキルを使用
    void useActiveSkill( Position p );
    // パッシブスキルを使用
    bool usePassiveSkill( Position p );

    
    /* ---------------------- 対象のヒーローを探す ---------------------- */

    // ある Side の（生存している）すべてのヒーローの Positon を返す
    vector<Position> searchAll( Side s );
    // （生存している）敵味方すべてのヒーローの Position を返す
    vector<Position> searchAll( Position p );

    // ある Side の（生存している中で）先頭のヒーローを探す
    Position searchFrontHero( Side s );
    // ある Side の（生存している中で）最も能力値の高いヒーローを探す
    Position searchHighestAttrHero( Side s, Attr a );
    // ある Side の（生存している中で）最も能力値の低いヒーローを探す
    Position searchLowestAttrHero( Side s, Attr a );

    // （生存している中で）ランダムなヒーローの Position を返す
    Position randomHero();

    // Target にあてはまるヒーローの Positon を返す
    // 引数の Position はスキルを発動するヒーローのもの
    vector<Position> searchTarget( Position p, Target t );


    /* -------------------------- ステータス変化 -------------------------- */

    
    // p の位置にいるヒーローの HP を damage 分減らす
    void giveDamage( Position p, int damage, bool is_active );   // is_active が true : アクティブスキルによるダメージ
    // p の位置にいるヒーローの HP を heal 分回復する
    void giveHeal( Position p, int heal );

    // p の位置にいるヒーローの 能力値（HP以外） を buff 分増やす
    void giveBuff( Position p, Attr a, int buff );
    // p の位置にいるヒーローの 能力値（HP以外） を debuff 分減らす
    void giveDebuff( Position p, Attr a, int debuff );

    // p の位置にいるヒーローの HP 以外の能力値とステータスを初期値に戻す（行動値はそのまま）
    void resetOtherThanHP( Position p );

    // p の位置にいるヒーローを（混乱・睡眠・毒）にする
    void giveStatusAilment( Position p, Status s );

    // p の位置にいるヒーローを HP が per % の状態で復活させる
    void comeBack( Position p, int per );


    /* ---------------------- ダメージを与える ---------------------- */

    // is_active が true : アクティブスキルによるダメージ

    
    // p の位置にいるヒーローが、Target に rate% の PHY/INT ダメージを与える
    void damageSkill( Position p, Target t, int rate, Attr a_damage, bool is_active );
    // p の位置にいるヒーローが、Target に rateA ~ rateB% の PHY/INT ダメージを与える    
    void damageSkill( Position p, Target t, int rateA, int rateB, Attr a_damage, bool is_active );

    // p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） に rate% の PHY/INT ダメージを与える
    void damageSkill( Position p, Attr a_target, bool is_high, bool is_ally, int rate, Attr a_damage, bool is_active );
    // p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） に rateA ~ rateB% の PHY/INT ダメージを与える
    void damageSkill( Position p, Attr a_target, bool is_high, bool is_ally, int rateA, int rateB, Attr a_damage, bool is_active );

    /* ---------------------- バフ、デバフ ---------------------- */
    
    
    // p の位置にいるヒーローが、Target の a_change に対して、 a_ref の値の rate% の （バフ・デバフ）を与える
    void changeAttrSkill( Position p, Target t, Attr a_change, Attr a_ref, int rate, bool is_buff );
    void changeAttrSkill( Position p, Target t, vector<Attr> a_change, Attr a_ref, int rate, bool is_buff );
    // p の位置にいるヒーローが、Target の a_change に対して、 a_ref の値の rateA ~ rateB% の （バフ・デバフ）を与える
    void changeAttrSkill( Position p, Target t, Attr a_change, Attr a_ref, int rateA, int rateB, bool is_buff );
    void changeAttrSkill( Position p, Target t, vector<Attr> a_change, Attr a_ref, int rateA, int rateB, bool is_buff );

    // p の位置にいるヒーローが、Target の a_change に対して value の rate% の （バフ・デバフ）を a_change に与える
    void changeAttrSkill( Position p, Target t, Attr a_change, int value, int rate, bool is_buff );
    void changeAttrSkill( Position p, Target t, vector<Attr> a_change, int value, int rate, bool is_buff );
    void changeAttrSkill( Position p, Target t, vector<Attr> a_change, int value, int rate, int rateB, bool is_buff );


    // p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方）の a_change に対して、 a_ref の値の rate% の （バフ・デバフ）を与える
    void changeAttrSkill( Position p, Attr a_target, bool is_high, bool is_ally, Attr a_change, Attr a_ref, int rate, bool is_buff );
    void changeAttrSkill( Position p, Attr a_target, bool is_high, bool is_ally, vector<Attr> a_change, Attr a_ref, int rate, bool is_buff );
    // p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） の a_change に対して、 a_ref の値の rateA ~ rateB% の （バフ・デバフ）を与える
    void changeAttrSkill( Position p, Attr a_target, bool is_high, bool is_ally, Attr a_change, Attr a_ref, int rateA, int rateB, bool is_buff );
    void changeAttrSkill( Position p, Attr a_target, bool is_high, bool is_ally, vector<Attr> a_change, Attr a_ref, int rateA, int rateB, bool is_buff );

    /* ---------------------- 回復効果 ---------------------- */

    // p の位置にいるヒーローが、Target に rate% の 回復効果を与える
    void healSkill( Position p, Target t, int rate );
    // p の位置にいるヒーローが、Target に rate% の 回復効果を与える
    void healSkill( Position p, Target t, double rate );
    // p の位置にいるヒーローが、Target に rateA ~ rateB% の 回復効果を与える
    void healSkill( Position p, Target t, int rateA, int rateB );

    // p の位置にいるヒーローが、Target に value の rate% の回復効果を与える
    void healSkillException( Position p, Target t, int value, int rate );

    // p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） に rate% の 回復効果を与える
    void healSkill( Position p, Attr a_target, bool is_high, bool is_ally, int rate );
    // p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） に rateA ~ rateB% の 回復効果を与える
    void healSkill( Position p, Attr a_target, bool is_high, bool is_ally, int rateA, int rateB );


    /* ---------------------- 状態異常付与 ---------------------- */
    // p の位置にいるヒーローが、Target を （混乱・睡眠・毒）状態にすることがある
    void statusAilmentSkill( Position p, Target t, Status s );
    // p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） を （混乱・睡眠・毒）状態にすることがある
    void statusAilmentSkill( Position p, Attr a_target, bool is_high, bool is_ally, Status s );


    /* ---------------------- Passive Skill の発動条件 ---------------------- */
    /* 返り値が true なら発動、 false なら発動せず */

    // アクティブ時、prob% の確率で
    bool usePassiveInActiveByChance( Position p, int prob );
    // バトル開始時、prob% の確率で一度だけ
    bool usePassiveInBattleStart( Position p, int prob );
    // Active Skill によるダメージを受けたとき、prob% の確率で
    bool usePassiveDamaged( Position p, int prob );
    // 自分の HP が rate% 未満になったとき一度だけ prob% の確率で
    bool usePassiveHPLessThan( Position p, int rate, int prob );
    // 味方全体の合計 HP が rate% 未満になったとき一度だけ prob% の確率で
    bool usePassiveTeamHPLessThan( Position p, int rate, int prob );
    // 死亡時に一度だけ prob% の確率で
    bool usePassiveDying( Position p, int prob );




    // アクティブスキルによってダメージを受けたときに立つフラグをリセットする
    void resetAllDamaged();



    /* ---------------------- ログに出力 ---------------------- */

    // ログに罫線を出力
    void printLine();

    // Attack側 / Defence側をログに出力
    void printSide( Side s );
    // 前衛 / 中衛 / 後衛 をログに出力
    void printOrder( Order o );
    // p にいるヒーロー名をログに出力
    void printHeroName( Position p );


    // p にいるヒーローの Side Order ヒーロー名 をログに出力
    void printPositionHero( Position p );
    // アクティブになったヒーローの Position
    void printAction( Position p );
    // アクティブスキル名をログに出力
    void printActiveSkill( ACTIVE_SKILL_ID id );
    // パッシブスキルをログに出力
    void printPassiveSkill( Position p );
    // ヒーロー全員の状態をログに出力
    void printAllHeroInfo();
    // 能力値の変化をログに出力
    void printChangeAttributeValue( Attr a, int delta, bool sign );
    // 状態異常をログに出力
    void printStatusAilment( Status s );
    // バトル開始前に、ヒーローの情報をログに出力
    void printHeroes();

    void printInfo();
    



    // p にいるヒーローの、バトル中のステータスを返す
    int getBattleAttr( Position p, Attr a );
    // p にいるヒーローの、初期ステータスを返す
    int getInitAttr( Position p, Attr a );
    // p にいるヒーローが、あるアクティブスキルによって受けたダメージ量を返す
    int getDamaged( Position p );


    
    public:

    Battle() {}

    // p の位置にいるヒーローの ID、能力値、アクティブスキルのIDをセット
    void setHero( Position p, ID i,  int attr[], ACTIVE_SKILL_ID active_skill_index[] ) {
        heroes[p.side][p.order].set( i, p.side, p.order, attr, active_skill_index );
    }

    // 戦闘開始して、200アクション経過するかどちらかのチームが全滅するまでループ
    void startBattle();
    // s の側のチームが全滅しているかどうか
    bool isEndGameByDead( Side s );
    
    // ログ出力用ファイルを開く
    // ファイルを正しく開けたら true を返す
    bool fileOpen(); 
    // ログ出力用ファイルを閉じる
    void fileClose();
    
    // すべてのヒーローを初期状態に戻す
    void resetBattle();



    /* ---------------------- Active Skill ---------------------- */

    // ACTIVE_SKILL_ID　→　functionPointerTable の index
    int convertIDToFunctionIndex( ACTIVE_SKILL_ID id );


    void active_skill( ACTIVE_SKILL_ID id, Position p );

    void dummy_active( Position p ); // functionPointerTable の index が 0 のときはエラーにする　そのためのダミー


    // 引数の Position は Passive Skill を 発動するヒーローの Position
    
    // xxxxx1    blade     ブレード
    // replica
    void repB_blade( Position p );
    void repA_blade( Position p );
    void repS_blade( Position p );
    // original
    void novice_blade( Position p );
    void elite_blade( Position p );
    void brave_blade( Position p );
    void imperial_blade( Position p );
    void mch_blade( Position p );
    
    // xxxxx2    musket  　  マスケット
    // replica
    void repB_musket( Position p );
    void repA_musket( Position p );
    void repS_musket( Position p );
    // original
    void novice_musket( Position p );
    void elite_musket( Position p );
    void brave_musket( Position p );
    void the_three_musketeers_musket( Position p );
    void grande_armee( Position p );

    // xxxxx3    Quill       ペン
    // replica
    void repB_quill( Position p );
    void repA_quill( Position p );
    void repS_quill( Position p );
    // original
    void novice_quill( Position p );
    void elite_quill( Position p );
    void wizdom_quill( Position p );
    void master_musicians_quill( Position p );
    void playwrights_quill( Position p );

    // xxxxx4    Armor       アーマー
    // replica
    void repB_armor( Position p );
    void repA_armor( Position p );
    void repS_armor( Position p );
    // original
    void novice_armor( Position p );
    void elite_armor( Position p );
    void brave_armor( Position p );
    void fluted_armor( Position p );
    void mch_armor( Position p );
    
    // xxxxx5    Horse       ホース
    // replica
    void repB_horse( Position p );
    void repA_horse( Position p );
    void repS_horse( Position p );
    // original
    void novice_horse( Position p );
    void elite_horse( Position p );
    void brave_horse( Position p );
    void red_hare( Position p );
    void bucephalus( Position p );
    
    // xxxxx6    Katana      カタナ
    // replica
    void repB_katana( Position p );
    void repA_katana( Position p );
    void repS_katana( Position p );
    // original
    void novice_katana( Position p );
    void elite_katana( Position p );
    void brave_katana( Position p );
    void izuminokami_kanesada( Position p );
    void heshikiri_hasebe( Position p );
    
    // xxxxx7    Cutie       キューティー
    // original
    void cutie_cat( Position p );
    void cutie_kyubi( Position p );
    void cutie_alien( Position p );

    // xxxxx8    Book        ブック
    // replica
    void repB_book( Position p );
    void repA_book( Position p );
    void repS_book( Position p );
    // original
    void novice_book( Position p );
    void elite_book( Position p );
    void wizdom_book( Position p );
    void crime_and_punishment( Position p );
    void codex_atlanticus( Position p );
    
    // xxxxx9    Ring        リング
    // replica
    void repB_ring( Position p );
    void repA_ring( Position p );
    void repS_ring( Position p );
    // original
    void novice_ring( Position p );
    void elite_ring( Position p );
    void wizdom_ring( Position p );
    void mysterious_stone_glow( Position p );
    void ring_of_the_queen( Position p );
    
    // xxxx10    Shield      シールド
    // replica
    void repB_shield( Position p );
    void repA_shield( Position p );
    void repS_shield( Position p );
    // original
    void novice_shield( Position p );
    void elite_shield( Position p );
    void brave_shield( Position p );
    void prytwen( Position p );
    void aegis( Position p );
    
    // xxxx11    Axe         アックス
    // replica
    void repB_axe( Position p );
    void repA_axe( Position p );
    void repS_axe( Position p );
    // original
    void novice_axe( Position p );
    void elite_axe( Position p );
    void brave_axe( Position p );
    void tecumsehs_tomahawk( Position p );
    void viking_axe( Position p );
    
    // xxxx12    Etheremon   イーサエモン
    // original
    void etheremon_ekopi( Position p );
    void etheremon_malakele( Position p );    
    void etheremon_mapla( Position p );
    void etheremon_siberizen( Position p );
    void eheremon_zedakazm( Position p );

    // xxxx13    Yumi        ユミ
    // replica
    void repB_yumi( Position p );
    void repA_yumi( Position p );
    void repS_yumi( Position p );
    // original
    void novice_yumi( Position p );
    void elite_yumi( Position p );
    void brave_yumi( Position p );
    void raijyodo( Position p );
    void yoichi_no_yumi( Position p );
    
    // xxxx14    Cross Spear       クロススピア
    // replica
    void repB_cross_spear( Position p );
    void repA_cross_spear( Position p );
    void repS_cross_spear( Position p );
    // original
    void novice_cross_spear( Position p );
    void elite_cross_spear( Position p );
    void brave_cross_spear( Position p );
    void bone_piercing_cross_spear( Position p );
    void tonbokiri( Position p );
    
    // xxxx15    Halberd     ハルバード
    // replica
    void repB_halberd( Position p );
    void repA_halberd( Position p );
    void repS_halberd( Position p );
    // original
    void novice_halberd( Position p );
    void elite_halberd( Position p );
    void brave_halberd( Position p );
    void zhang_eight_snake_halberd( Position p );
    void lu_bus_helberd( Position p );
    
    // xxxx16    Scrolls     スクロール
    // replica
    void repB_scrolls( Position p );
    void repA_scrolls( Position p );
    void repS_scrolls( Position p );
    // original
    void novice_scrolls( Position p );
    void elite_scrolls( Position p );
    void wizdom_scrolls( Position p );
    void the_art_of_war( Position p );
    void da_tang_western_region( Position p );
    
    // xxxx17    Necklace    ネックレス
    // replica
    void repB_necklace( Position p );
    void repA_necklace( Position p );
    void repS_necklace( Position p );
    // original
    void novice_necklace( Position p );
    void elite_necklace( Position p );
    void wizdom_necklace( Position p );
    void siberian_cedar_necklace( Position p );
    void necklace_of_the_sun_god( Position p );
    
    // xxxx18    Kabuto      カブト
    // replica
    void repB_kabuto( Position p );
    void repA_kabuto( Position p );
    void repS_kabuto( Position p );
    // original
    void novice_kabuto( Position p );
    void elite_kabuto( Position p );
    void brave_kabuto( Position p );
    void shingens_kabuto( Position p );
    void crescent_moon_kabuto( Position p );
    
    // xxxx19    Turtle      タートル
    // replica
    void repB_turtle( Position p );
    void repA_turtle( Position p );
    void repS_turtle( Position p );
    // original
    void novice_turtle( Position p );
    void elite_turtle( Position p );
    void wizdom_turtle( Position p );
    void akeron( Position p );
    void akupara( Position p );
    
    // xxxx20    Roostler    ルースター
    // replica
    void repB_roostler( Position p );
    void repA_roostler( Position p );
    void repS_roostler( Position p );
    // original
    void novice_roostler( Position p );
    void elite_roostler( Position p );
    void brave_roostler( Position p );
    void hotspur( Position p );
    void golden_rooster( Position p );
    
    // xxxx21    Tiger       タイガー
    // replica
    void repB_tiger( Position p );
    void repA_tiger( Position p );
    void repS_tiger( Position p );
    // original
    void novice_tiger( Position p );
    void elite_tiger( Position p );
    void brave_tiger( Position p );
    void amur_tiger( Position p );
    void saber_toothed_tiger( Position p );
    
    // xxxx22    Dragon      ドラゴン
    // replica
    void repB_dragon( Position p );
    void repA_dragon( Position p );
    void repS_dragon( Position p );
    // original
    void novice_dragon( Position p );
    void elite_dragon( Position p );
    void wizdom_dragon( Position p );
    void wyvern_dragon( Position p );
    void golden_dragon( Position p );
    
    // xxxx23    Bull        ブル
    // replica
    void repB_bull( Position p );
    void repA_bull( Position p );
    void repS_bull( Position p );
    // original
    void novice_bull( Position p );
    void elite_bull( Position p );
    void brave_bull( Position p );
    void bison( Position p );
    void golden_bull( Position p );
    
    // xxxx24    Elephant    エレファント
    // replica
    void repB_elephant( Position p );
    void repA_elephant( Position p );
    void repS_elephant( Position p );
    // original
    void novice_elephant( Position p );
    void elite_elephant( Position p );
    void brave_elephant( Position p );
    void mammoth( Position p );
    void hannibals_war_elephant( Position p );
    
    // xxxx25    Monkey      モンキー
    // replica
    void repB_monkey( Position p );
    void repA_monkey( Position p );
    void repS_monkey( Position p );
    // original
    void novice_monkey( Position p );
    void elite_monkey( Position p );
    void wizdom_monkey( Position p );
    void silver_back( Position p );
    void hihi( Position p );
    
    // xxxx26    Snake       スネーク
    // replica
    void repB_snake( Position p );
    void repA_snake( Position p );
    void repS_snake( Position p );
    // original
    void novice_snake( Position p );
    void elite_snake( Position p );
    void wizdom_snake( Position p );
    void king_cobra( Position p );
    void quetzalcoatl( Position p );
    
    // xxxx27    Dog         ドッグ
    // replica
    void repB_dog( Position p );
    void repA_dog( Position p );
    void repS_dog( Position p );
    // original
    void novice_dog( Position p );
    void elite_dog( Position p );
    void wizdom_dog( Position p );
    void molossus( Position p );
    void shippei_taro( Position p );
    

    // アートエディットスキル
    // 英名を調べるのが面倒なので適当につける
    
    // xxxxxx0   休む
    void rest( Position p );
    // xxxxxx1   レッドストライク
    void red_strike( Position p );
    // xxxxxx2   ハット・トリック
    void hat_trick( Position p );
    // xxxxxx3   Punks Not Dead
    void punks_not_dead( Position p );
    // xxxxxx4   マゼンタマッシュルーム
    void magenta_mushroom( Position p );
    // xxxxxx5   ゴロゴロパンチ
    void cat_punch( Position p );
    // xxxxxx6   無垢なる忠誠
    void dogs_loyalty( Position p );
    // xxxxxx7   サイドワインダー
    void side_winder( Position p );
    // xxxxxx8   女神のウインク
    void goddess_wink( Position p );
    // xxxxxx9   自由の女神
    void goddess_of_liberty( Position p );
    // xxxxx10   ブラックシャウト
    void black_shout( Position p );
    // xxxxx11   モンキー・マジック
    void monkey_magic( Position p );
    // xxxxx12   ガールズ・トーク
    void girls_talk( Position p );
    // xxxxx13   ダンディズム
    void dandyism( Position p );
    // xxxxx14   中二病
    void fatal_desease( Position p );
    // xxxxx15   万里の長城
    void chinese_wall( Position p );
    // xxxxx16   霊峰富士
    void mt_fuji( Position p );
    // xxxxx17   イエローブラスト
    void yellow_blast( Position p );
    // xxxxx18   グリーンリース
    void green_wreath( Position p );
    // xxxxx19   シアンフロスト
    void cyan_frost( Position p );
    // xxxxx20   ハード・トレーニング
    void hard_training( Position p );
    // xxxxx21   ハイ・フライヤー
    void high_flyer( Position p );
    // xxxxx22   フル・スロットル
    void full_throttle( Position p );
    // xxxxx23   ブルーブロッサム
    void blue_blossom( Position p );
    // xxxxx24   眼鏡効果
    void grasses_effect( Position p );
    // xxxxx25   ホワイトキャンディー
    void white_candy( Position p );
    // xxxxx26   森林浴
    void forest_bath( Position p );
    // xxxxx27   無条件幸福
    void happiness_in_life( Position p );
    // xxxxx28   紳士の品格
    void gentlemans_dignity( Position p );



    /* ---------------------- Passive Skill ---------------------- */

    bool passive_skill( ID id, Position p );

    bool dummy_passive( Position p );

    // Novice
    // MCHウォーリアー
    bool MCH_Warrior( Position p );
    // MCHタクティシャン
    bool MCH_Tactician( Position p );
    // MCHアーティスト
    bool MCH_Artist( Position p );
    // 福沢諭吉
    bool Fukuzawa_Yukichi( Position p );
    // 孫尚香
    bool Sun_Shangxiang( Position p );
    // パスカル
    bool Blaise_Pascal( Position p );
    // ダビデ
    bool David( Position p );
    // 雷電為右衛門
    bool Raniden_Tameemon( Position p );
    
    // Uncommon
    // ライト兄弟
    bool Wright_Brothers( Position p );
    // スパルタクス
    bool Spartacus( Position p );
    // ジャック・ザ・リッパー
    bool Jack_the_Ripper( Position p );
    // シューベルト
    bool Franza_Schubert( Position p );
    // グリム兄弟
    bool Brothers_Grimm( Position p );
    // アルキメデス
    bool Archimedes( Position p );
    // サンタクロース
    bool Santa_Claus( Position p );
    // シュレディンガー
    bool Erwin_Schrodinger( Position p );
    // 森蘭丸
    bool Mori_Ranmaru( Position p );
    // カフカ
    bool Franz_Kafka( Position p );
    // 孫子
    bool Sun_Tzu( Position p );
    // 石田三成
    bool Ishida_Mitsunari( Position p );
    // 許褚
    bool Xu_Chu( Position p );
    // 徳川慶喜
    bool Tokugawa_Yoshinobu( Position p );
    // モンテスキュー
    bool Montesquieu( Position p );

    // Rare
    // イーサエモン・レッド
    bool Etheremon_Red( Position p );
    // ダルタニャン
    bool Dartagnan( Position p );
    // 平賀源内
    bool Gennai_Hiraga( Position p );
    // マタ・ハリ
    bool Mata_Hari( Position p );
    // イーサエモン・ブルー
    bool Etheremon_Blue( Position p );
    // イーサエモン・グリーン
    bool Etheremon_Green( Position p );
    // 皇帝ネロ
    bool Emperor_Nero( Position p );
    // ノストラダムス
    bool Michel_Nostradamus( Position p );
    // 太公望
    bool Jiang_Ziya( Position p );
    // 服部半蔵
    bool Hanzo_Hattroi( Position p );
    // 前田慶次
    bool Keiji_Maeda( Position p );
    // 天草四郎
    bool Amakusa_Shiro( Position p );
    // 石川五右衛門
    bool Goemon_Ishikawa( Position p );
    // 直江兼続
    bool Naoe_Kanetsugu( Position p );
    // イワン雷帝
    bool Ivan_the_Terrible( Position p );
    // 松尾芭蕉
    bool Matsuo_Basho( Position p );
    // 三蔵法師
    bool Xuanzang( Position p );
    // 武蔵坊弁慶
    bool Benkei( Position p );
    // 黄忠
    bool Huang_Zhong( Position p );
    // 貂蝉
    bool Diao_Chan( Position p );
    // ヴァレンティヌス
    bool Saint_Valentine( Position p );
    // ポカホンタス
    bool Pocahontas( Position p );
    // 孫堅
    bool Sun_Jian( Position p );
    // ルーベンス
    bool Peter_Paul_Rubens( Position p );

    //Epic
    // 張飛
    bool Zhang_Fei( Position p );
    // ナイチンゲール
    bool Florence_Nightingale( Position p );
    // ベートーヴェン
    bool Ludwig_van_Beethoven( Position p );
    // 佐々木小次郎
    bool Kojiro_Sasaki( Position p );
    // 勝海舟
    bool Kaishu_Katsu( Position p );
    // ビリー・ザ・キッド
    bool Billy_the_Kid( Position p );
    // トーマス・エジソン
    bool Thomas_Edison( Position p );
    // マルコ・ポーロ
    bool Marco_Polo( Position p );
    // 伊達政宗
    bool Masamune_Date( Position p );
    // 王キ
    bool Wang_Ki( Position p );
    // マルクス
    bool Karl_Marx( Position p );
    // 沖田総司
    bool Soji_Okita( Position p );
    // チャイコフスキー
    bool Pyotr_Tchaikovsky( Position p );
    // マリー・アントワネット
    bool Marie_Antoinette( Position p );
    // 楊貴妃
    bool Yang_Guifei( Position p );
    // 呂布
    bool Lu_Bu( Position p );
    // キュリー夫人
    bool Marie_Curie( Position p );
    // 孫権
    bool Sun_Quan( Position p );
    // カメハメハ大王
    bool Kamehameha_1( Position p );
    // カラミティ・ジェーン
    bool Calamity_Jane( Position p );
    // ゴッホ
    bool Vincent_van_Gogh( Position p );
    // 巴御前
    bool Tomoe_Gozen( Position p );
    // 趙雲
    bool Zhao_Yun( Position p );
    // 岳飛
    bool Yue_Fei( Position p );
    // 武田信玄
    bool Takeda_Shinge( Position p );
    // カエサル
    bool Gaius_Iulius_Caesar( Position p );
    // 土方歳三
    bool Hijikata_Toshizo( Position p );

    // Legendary
    // 織田信長
    bool Nobunaga_Oda( Position p );
    // ナポレオン・ボナパルト
    bool Napoleon_Bonaparte( Position p );
    // 曹操
    bool Cao_Cao( Position p );
    // ジョージ・ワシントン
    bool George_Washington( Position p );
    // レオナルド・ダ・ビンチ
    bool Leonardo_da_Vinci( Position p );
    // アーサー王
    bool King_Arthur( Position p );
    // ジャンヌ・ダルク
    bool Joan_of_Arc( Position p );
    // 坂本龍馬
    bool Ryoma_Sakamoto( Position p );
    // 劉備
    bool Liu_Bei( Position p );
    // アインシュタイン
    bool Albert_Einstein( Position p );
    // 卑弥呼
    bool Himiko( Position p );
    // バッハ
    bool Johann_Sebastian_Bach( Position p );
    // チンギス・ハン
    bool Genghis_Khan( Position p );
    // カール大帝
    bool Charles_the_Great( Position p );
    // 諸葛亮
    bool Zhuge_Liang( Position p );
    // クレオパトラ
    bool Cleopatra( Position p );


    /* ---------------------- Enemy Active Skill ---------------------- */

    // スパミング1.0
    void spamming_1_0( Position p );
    // スパミング1.2
    void spamming_1_2( Position p );
    // スパミング2.0
    void spamming_2_0( Position p );

    // リファクタリング1.0
    void refactoring_1_0( Position p );
    // リファクタリングボム2.0
    void refactoring_bomb_2_0( Position p );

    // フィッシング1.0
    void phishing_1_0( Position p );    
    // フィッシング1.2
    void phishing_1_2( Position p );
    // フィッシング2.0
    void phishing_2_0( Position p );

    // ディープラーニング1.0
    void deep_learning_1_0( Position p );
    // ディープラーニング1.5
    void deep_learning_1_5( Position p );
    // ディープラーニングボム2.0
    void deep_learning_bomb_2_0( Position p );

    // ロールバック1.0
    void rollback_1_0( Position p );
    // ロールバック1.5
    void rollback_1_5( Position p );

    // コードインジェクション1.0
    void code_injection_1_0( Position p );
    // コードインジェクション1.5
    void code_injection_1_5( Position p );


    /* ---------------------- Enemy Passive Skill ---------------------- */

    // スパムボム2.0
    bool spam_bomb_2_0( Position p );
    // ロールバックボム2.0
    bool rollback_bomb_2_0( Position p );
    // フィッシングボム2.0
    bool phishing_bomb_2_0( Position p );
    // スミッシング1.0
    bool smishing_1_0( Position p );
    // スミッシング2.0
    bool smishing_2_0( Position p );
    // コードインジェクション2.0
    bool code_injection_2_0( Position p );
    



};




#endif