#ifndef ACTIVESKILL_HPP
#define ACTIVESKILL_HPP


#include "Battle.hpp"

/*
original
Legendary 5xxxx
Epic      4xxxx
Rare      3xxxx
Uncommon  2xxxx
Common    1xxxx

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
xxxxx2    musket  　  マスケット
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



/* アートエディットスキル */
// 100xxxx

/*
順番を決める基準がないので効果の種類ごとにまとめる
新しく発見されたら最後に追加する

xxxxxx0   休む
xxxxxx1   レッドストライク
xxxxxx2   ハット・トリック
xxxxxx3   Punks Not Dead
xxxxxx4   マゼンタマッシュルーム
xxxxxx5   ゴロゴロパンチ
xxxxxx6   無垢なる忠誠
xxxxxx7   サイドワインダー
xxxxxx8   女神のウインク
xxxxxx9   自由の女神
xxxxx10   ブラックシャウト
xxxxx11   モンキー・マジック
xxxxx12   ガールズ・トーク
xxxxx13   ダンディズム
xxxxx14   中二病
xxxxx15   万里の長城
xxxxx16   霊峰富士
xxxxx17   イエローブラスト
xxxxx18   グリーンリース
xxxxx19   シアンフロスト
xxxxx20   ハード・トレーニング
xxxxx21   ハイ・フライヤー
xxxxx22   フル・スロットル
xxxxx23   ブルーブロッサム
xxxxx24   眼鏡効果
xxxxx25   ホワイトキャンディー
xxxxx26   森林浴
xxxxx27   無条件幸福
xxxxx28   紳士の品格
*/


class ActiveSkill {

    private:

    // ACTIVE_SKILL_ID　→　functionPointerTable の index
    int convertIDToFunctionIndex( ACTIVE_SKILL_ID id );

    public:

    ActiveSkill();

    void dummy( Battle* b, Position p ); // functionPointerTable の index が 0 のときはエラーにする　そのためのダミー


    // 引数の Position は Passive Skill を 発動するヒーローの Position
    
    // xxxxx1    blade     ブレード
    // replica
    void repB_blade( Battle* b, Position p );
    void repA_blade( Battle* b, Position p );
    void repS_blade( Battle* b, Position p );
    // original
    void novice_blade( Battle* b, Position p );
    void elite_blade( Battle* b, Position p );
    void brave_blade( Battle* b, Position p );
    void imperial_blade( Battle* b, Position p );
    void mch_blade( Battle* b, Position p );
    
    // xxxxx2    musket  　  マスケット
    // replica
    void repB_musket( Battle* b, Position p );
    void repA_musket( Battle* b, Position p );
    void repS_musket( Battle* b, Position p );
    // original
    void novice_musket( Battle* b, Position p );
    void elite_musket( Battle* b, Position p );
    void brave_musket( Battle* b, Position p );
    void the_three_musketeers_musket( Battle* b, Position p );
    void grande_armee( Battle* b, Position p );

    // xxxxx3    Quill       ペン
    // replica
    void repB_quill( Battle* b, Position p );
    void repA_quill( Battle* b, Position p );
    void repS_quill( Battle* b, Position p );
    // original
    void novice_quill( Battle* b, Position p );
    void elite_quill( Battle* b, Position p );
    void wizdom_quill( Battle* b, Position p );
    void master_musicians_quill( Battle* b, Position p );
    void playwrights_quill( Battle* b, Position p );

    // xxxxx4    Armor       アーマー
    // replica
    void repB_armor( Battle* b, Position p );
    void repA_armor( Battle* b, Position p );
    void repS_armor( Battle* b, Position p );
    // original
    void novice_armor( Battle* b, Position p );
    void elite_armor( Battle* b, Position p );
    void brave_armor( Battle* b, Position p );
    void fluted_armor( Battle* b, Position p );
    void mch_armor( Battle* b, Position p );
    
    // xxxxx5    Horse       ホース
    // replica
    void repB_horse( Battle* b, Position p );
    void repA_horse( Battle* b, Position p );
    void repS_horse( Battle* b, Position p );
    // original
    void novice_horse( Battle* b, Position p );
    void elite_horse( Battle* b, Position p );
    void brave_horse( Battle* b, Position p );
    void red_hare( Battle* b, Position p );
    void bucephalus( Battle* b, Position p );
    
    // xxxxx6    Katana      カタナ
    // replica
    void repB_katana( Battle* b, Position p );
    void repA_katana( Battle* b, Position p );
    void repS_katana( Battle* b, Position p );
    // original
    void novice_katana( Battle* b, Position p );
    void elite_katana( Battle* b, Position p );
    void brave_katana( Battle* b, Position p );
    void izuminokami_kanesada( Battle* b, Position p );
    void heshikiri_hasebe( Battle* b, Position p );
    
    // xxxxx7    Cutie       キューティー
    // original
    void cutie_cat( Battle* b, Position p );
    void cutie_kyubi( Battle* b, Position p );
    void cutie_alien( Battle* b, Position p );

    // xxxxx8    Book        ブック
    // replica
    void repB_book( Battle* b, Position p );
    void repA_book( Battle* b, Position p );
    void repS_book( Battle* b, Position p );
    // original
    void novice_book( Battle* b, Position p );
    void elite_book( Battle* b, Position p );
    void wizdom_book( Battle* b, Position p );
    void crime_and_punishment( Battle* b, Position p );
    void codex_atlanticus( Battle* b, Position p );
    
    // xxxxx9    Ring        リング
    // replica
    void repB_ring( Battle* b, Position p );
    void repA_ring( Battle* b, Position p );
    void repS_ring( Battle* b, Position p );
    // original
    void novice_ring( Battle* b, Position p );
    void elite_ring( Battle* b, Position p );
    void wizdom_ring( Battle* b, Position p );
    void mysterious_stone_glow( Battle* b, Position p );
    void ring_of_the_queen( Battle* b, Position p );
    
    // xxxx10    Shield      シールド
    // replica
    void repB_shield( Battle* b, Position p );
    void repA_shield( Battle* b, Position p );
    void repS_shield( Battle* b, Position p );
    // original
    void novice_shield( Battle* b, Position p );
    void elite_shield( Battle* b, Position p );
    void brave_shield( Battle* b, Position p );
    void prytwen( Battle* b, Position p );
    void aegis( Battle* b, Position p );
    
    // xxxx11    Axe         アックス
    // replica
    void repB_axe( Battle* b, Position p );
    void repA_axe( Battle* b, Position p );
    void repS_axe( Battle* b, Position p );
    // original
    void novice_axe( Battle* b, Position p );
    void elite_axe( Battle* b, Position p );
    void brave_axe( Battle* b, Position p );
    void tecumsehs_tomahawk( Battle* b, Position p );
    void viking_axe( Battle* b, Position p );
    
    // xxxx12    Etheremon   イーサエモン
    // original
    void etheremon_ekopi( Battle* b, Position p );
    void etheremon_malakele( Battle* b, Position p );    
    void etheremon_mapla( Battle* b, Position p );
    void etheremon_siberizen( Battle* b, Position p );
    void eheremon_zedakazm( Battle* b, Position p );

    // xxxx13    Yumi        ユミ
    // replica
    void repB_yumi( Battle* b, Position p );
    void repA_yumi( Battle* b, Position p );
    void repS_yumi( Battle* b, Position p );
    // original
    void novice_yumi( Battle* b, Position p );
    void elite_yumi( Battle* b, Position p );
    void brave_yumi( Battle* b, Position p );
    void raijyodo( Battle* b, Position p );
    void yoichi_no_yumi( Battle* b, Position p );
    
    // xxxx14    Cross Spear       クロススピア
    // replica
    void repB_cross_spear( Battle* b, Position p );
    void repA_cross_spear( Battle* b, Position p );
    void repS_cross_spear( Battle* b, Position p );
    // original
    void novice_cross_spear( Battle* b, Position p );
    void elite_cross_spear( Battle* b, Position p );
    void brave_cross_spear( Battle* b, Position p );
    void bone_piercing_cross_spear( Battle* b, Position p );
    void tonbokiri( Battle* b, Position p );
    
    // xxxx15    Halberd     ハルバード
    // replica
    void repB_halberd( Battle* b, Position p );
    void repA_halberd( Battle* b, Position p );
    void repS_halberd( Battle* b, Position p );
    // original
    void novice_halberd( Battle* b, Position p );
    void elite_halberd( Battle* b, Position p );
    void brave_halberd( Battle* b, Position p );
    void zhang_eight_snake_halberd( Battle* b, Position p );
    void lu_bus_helberd( Battle* b, Position p );
    
    // xxxx16    Scrolls     スクロール
    // replica
    void repB_scrolls( Battle* b, Position p );
    void repA_scrolls( Battle* b, Position p );
    void repS_scrolls( Battle* b, Position p );
    // original
    void novice_scrolls( Battle* b, Position p );
    void elite_scrolls( Battle* b, Position p );
    void wizdom_scrolls( Battle* b, Position p );
    void the_art_of_war( Battle* b, Position p );
    void da_tang_western_region( Battle* b, Position p );
    
    // xxxx17    Necklace    ネックレス
    // replica
    void repB_necklace( Battle* b, Position p );
    void repA_necklace( Battle* b, Position p );
    void repS_necklace( Battle* b, Position p );
    // original
    void novice_necklace( Battle* b, Position p );
    void elite_necklace( Battle* b, Position p );
    void wizdom_necklace( Battle* b, Position p );
    void siberian_cedar_necklace( Battle* b, Position p );
    void necklace_of_the_sun_god( Battle* b, Position p );
    
    // xxxx18    Kabuto      カブト
    // replica
    void repB_kabuto( Battle* b, Position p );
    void repA_kabuto( Battle* b, Position p );
    void repS_kabuto( Battle* b, Position p );
    // original
    void novice_kabuto( Battle* b, Position p );
    void elite_kabuto( Battle* b, Position p );
    void brave_kabuto( Battle* b, Position p );
    void shingens_kabuto( Battle* b, Position p );
    void crescent_moon_kabuto( Battle* b, Position p );
    
    // xxxx19    Turtle      タートル
    // replica
    void repB_turtle( Battle* b, Position p );
    void repA_turtle( Battle* b, Position p );
    void repS_turtle( Battle* b, Position p );
    // original
    void novice_turtle( Battle* b, Position p );
    void elite_turtle( Battle* b, Position p );
    void wizdom_turtle( Battle* b, Position p );
    void akeron( Battle* b, Position p );
    void akupara( Battle* b, Position p );
    
    // xxxx20    Roostler    ルースター
    // replica
    void repB_roostler( Battle* b, Position p );
    void repA_roostler( Battle* b, Position p );
    void repS_roostler( Battle* b, Position p );
    // original
    void novice_roostler( Battle* b, Position p );
    void elite_roostler( Battle* b, Position p );
    void brave_roostler( Battle* b, Position p );
    void hotspur( Battle* b, Position p );
    void golden_rooster( Battle* b, Position p );
    
    // xxxx21    Tiger       タイガー
    // replica
    void repB_tiger( Battle* b, Position p );
    void repA_tiger( Battle* b, Position p );
    void repS_tiger( Battle* b, Position p );
    // original
    void novice_tiger( Battle* b, Position p );
    void elite_tiger( Battle* b, Position p );
    void brave_tiger( Battle* b, Position p );
    void amur_tiger( Battle* b, Position p );
    void saber_toothed_tiger( Battle* b, Position p );
    
    // xxxx22    Dragon      ドラゴン
    // replica
    void repB_dragon( Battle* b, Position p );
    void repA_dragon( Battle* b, Position p );
    void repS_dragon( Battle* b, Position p );
    // original
    void novice_dragon( Battle* b, Position p );
    void elite_dragon( Battle* b, Position p );
    void wizdom_dragon( Battle* b, Position p );
    void wyvern_dragon( Battle* b, Position p );
    void golden_dragon( Battle* b, Position p );
    
    // xxxx23    Bull        ブル
    // replica
    void repB_bull( Battle* b, Position p );
    void repA_bull( Battle* b, Position p );
    void repS_bull( Battle* b, Position p );
    // original
    void novice_bull( Battle* b, Position p );
    void elite_bull( Battle* b, Position p );
    void brave_bull( Battle* b, Position p );
    void bison( Battle* b, Position p );
    void golden_bull( Battle* b, Position p );
    
    // xxxx24    Elephant    エレファント
    // replica
    void repB_elephant( Battle* b, Position p );
    void repA_elephant( Battle* b, Position p );
    void repS_elephant( Battle* b, Position p );
    // original
    void novice_elephant( Battle* b, Position p );
    void elite_elephant( Battle* b, Position p );
    void brave_elephant( Battle* b, Position p );
    void mammoth( Battle* b, Position p );
    void hannibals_war_elephant( Battle* b, Position p );
    
    // xxxx25    Monkey      モンキー
    // replica
    void repB_monkey( Battle* b, Position p );
    void repA_monkey( Battle* b, Position p );
    void repS_monkey( Battle* b, Position p );
    // original
    void novice_monkey( Battle* b, Position p );
    void elite_monkey( Battle* b, Position p );
    void wizdom_monkey( Battle* b, Position p );
    void silver_back( Battle* b, Position p );
    void hihi( Battle* b, Position p );
    
    // xxxx26    Snake       スネーク
    // replica
    void repB_snake( Battle* b, Position p );
    void repA_snake( Battle* b, Position p );
    void repS_snake( Battle* b, Position p );
    // original
    void novice_snake( Battle* b, Position p );
    void elite_snake( Battle* b, Position p );
    void wizdom_snake( Battle* b, Position p );
    void king_cobra( Battle* b, Position p );
    void quetzalcoatl( Battle* b, Position p );
    
    // xxxx27    Dog         ドッグ
    // replica
    void repB_dog( Battle* b, Position p );
    void repA_dog( Battle* b, Position p );
    void repS_dog( Battle* b, Position p );
    // original
    void novice_dog( Battle* b, Position p );
    void elite_dog( Battle* b, Position p );
    void wizdom_dog( Battle* b, Position p );
    void molossus( Battle* b, Position p );
    void shippei_taro( Battle* b, Position p );
    

    // アートエディットスキル
    // 英名を調べるのが面倒なので適当につける
    
    // xxxxxx0   休む
    void rest( Battle* b, Position p );
    // xxxxxx1   レッドストライク
    void red_strike( Battle* b, Position p );
    // xxxxxx2   ハット・トリック
    void hat_trick( Battle* b, Position p );
    // xxxxxx3   Punks Not Dead
    void punks_not_dead( Battle* b, Position p );
    // xxxxxx4   マゼンタマッシュルーム
    void magenta_mushroom( Battle* b, Position p );
    // xxxxxx5   ゴロゴロパンチ
    void cat_punch( Battle* b, Position p );
    // xxxxxx6   無垢なる忠誠
    void dogs_loyalty( Battle* b, Position p );
    // xxxxxx7   サイドワインダー
    void side_winder( Battle* b, Position p );
    // xxxxxx8   女神のウインク
    void goddess_wink( Battle* b, Position p );
    // xxxxxx9   自由の女神
    void goddess_of_liberty( Battle* b, Position p );
    // xxxxx10   ブラックシャウト
    void black_shout( Battle* b, Position p );
    // xxxxx11   モンキー・マジック
    void monkey_magic( Battle* b, Position p );
    // xxxxx12   ガールズ・トーク
    void girls_talk( Battle* b, Position p );
    // xxxxx13   ダンディズム
    void dandyism( Battle* b, Position p );
    // xxxxx14   中二病
    void fatal_desease( Battle* b, Position p );
    // xxxxx15   万里の長城
    void chinese_wall( Battle* b, Position p );
    // xxxxx16   霊峰富士
    void mt_fuji( Battle* b, Position p );
    // xxxxx17   イエローブラスト
    void yellow_blast( Battle* b, Position p );
    // xxxxx18   グリーンリース
    void green_wreath( Battle* b, Position p );
    // xxxxx19   シアンフロスト
    void cyan_frost( Battle* b, Position p );
    // xxxxx20   ハード・トレーニング
    void hard_training( Battle* b, Position p );
    // xxxxx21   ハイ・フライヤー
    void high_flyer( Battle* b, Position p );
    // xxxxx22   フル・スロットル
    void full_throttle( Battle* b, Position p );
    // xxxxx23   ブルーブロッサム
    void blue_blossom( Battle* b, Position p );
    // xxxxx24   眼鏡効果
    void grasses_effect( Battle* b, Position p );
    // xxxxx25   ホワイトキャンディー
    void white_candy( Battle* b, Position p );
    // xxxxx26   森林浴
    void forest_bath( Battle* b, Position p );
    // xxxxx27   無条件幸福
    void happiness_in_life( Battle* b, Position p );
    // xxxxx28   紳士の品格
    void gentlemans_dignity( Battle* b, Position p );


    void execFunc( ACTIVE_SKILL_ID id, Battle* b, Position p );


};



#endif