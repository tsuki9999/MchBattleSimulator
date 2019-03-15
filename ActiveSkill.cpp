#include "Battle.hpp"


int Battle::convertIDToFunctionIndex( ACTIVE_SKILL_ID id ) {
    int type = id % extension_type_mask;

    int index = (type-1) * n_extension_rarity;

    
    int ret;
    switch ( IDToActiveSkillType(id) ) {
        case REPLICA:
            ret =  index + id / ( extension_type_mask * 10 );
            break;
        case ORIGINAL:
            ret = index + n_replica_rank + id / extension_type_mask;
        break;
        case ARTEDIT:
            ret = n_extension_type * 12 + 1 + type;
            break;
        default: assert(false);
    }

    return ret;
}


void (Battle::*functionPointerTableActive[])( Position p ) = {
    &Battle::dummy_active,

    // xxxxx1    blade     ブレード
    // replica
    &Battle::repB_blade, // F
    &Battle::repB_blade, // E
    &Battle::repB_blade, // D
    &Battle::repB_blade, // C
    &Battle::repB_blade,
    &Battle::repA_blade,
    &Battle::repS_blade,
    // original
    &Battle::novice_blade,
    &Battle::elite_blade,
    &Battle::brave_blade,
    &Battle::imperial_blade,
    &Battle::mch_blade,

    // xxxxx2    musket  　  マスケット
    // replica
    &Battle::repB_musket, // F
    &Battle::repB_musket, // E
    &Battle::repB_musket, // D
    &Battle::repB_musket, // C
    &Battle::repB_musket,
    &Battle::repA_musket,
    &Battle::repS_musket,
    // original
    &Battle::novice_musket,
    &Battle::elite_musket,
    &Battle::brave_musket,
    &Battle::the_three_musketeers_musket,
    &Battle::grande_armee,

    // xxxxx3    Quill       ペン
    &Battle::repB_quill, // F
    &Battle::repB_quill, // E
    &Battle::repB_quill, // D
    &Battle::repB_quill, // C
    &Battle::repB_quill,
    &Battle::repA_quill,
    &Battle::repS_quill,
    // original
    &Battle::novice_quill,
    &Battle::elite_quill,
    &Battle::wizdom_quill,
    &Battle::master_musicians_quill,
    &Battle::playwrights_quill,

    // xxxxx4    Armor       アーマー
    &Battle::repB_armor, // F
    &Battle::repB_armor, // E
    &Battle::repB_armor, // D
    &Battle::repB_armor, // C
    &Battle::repB_armor,
    &Battle::repA_armor,
    &Battle::repS_armor,
    // original
    &Battle::novice_armor,
    &Battle::elite_armor,
    &Battle::brave_armor,
    &Battle::fluted_armor,
    &Battle::mch_armor,
    
    // xxxxx5    Horse       ホース
    // replica
    &Battle::repB_horse,
    &Battle::repB_horse,
    &Battle::repB_horse,
    &Battle::repB_horse,
    &Battle::repB_horse,
    &Battle::repA_horse,
    &Battle::repS_horse,
    // original
    &Battle::novice_horse,
    &Battle::elite_horse,
    &Battle::brave_horse,
    &Battle::red_hare,
    &Battle::bucephalus,
        
    // xxxxx6    Katana      カタナ
    // replica
    &Battle::repB_katana,
    &Battle::repB_katana,
    &Battle::repB_katana,
    &Battle::repB_katana,
    &Battle::repB_katana,
    &Battle::repA_katana,
    &Battle::repS_katana,
    // original
    &Battle::novice_katana,
    &Battle::elite_katana,
    &Battle::brave_katana,
    &Battle::izuminokami_kanesada,
    &Battle::heshikiri_hasebe,

    // xxxxx7    Cutie       キューティー
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,

    // original
    &Battle::cutie_cat,
    &Battle::cutie_kyubi,
    &Battle::cutie_alien,
    &Battle::dummy_active,
    &Battle::dummy_active,

    // xxxxx8    Book        ブック
    // replica
    &Battle::repB_book,
    &Battle::repB_book,
    &Battle::repB_book,
    &Battle::repB_book,
    &Battle::repB_book,
    &Battle::repA_book,
    &Battle::repS_book,
    // original
    &Battle::novice_book,
    &Battle::elite_book,
    &Battle::wizdom_book,
    &Battle::crime_and_punishment,
    &Battle::codex_atlanticus,

    // xxxxx9    Ring        リング
    // replica
    &Battle::repB_ring,
    &Battle::repB_ring,
    &Battle::repB_ring,
    &Battle::repB_ring,
    &Battle::repB_ring,
    &Battle::repA_ring,
    &Battle::repS_ring,
    // original
    &Battle::novice_ring,
    &Battle::elite_ring,
    &Battle::wizdom_ring,
    &Battle::mysterious_stone_glow,
    &Battle::ring_of_the_queen,

    // xxxx10    Shield      シールド
    // replica
    &Battle::repB_shield,
    &Battle::repB_shield,
    &Battle::repB_shield,
    &Battle::repB_shield,
    &Battle::repB_shield,
    &Battle::repA_shield,
    &Battle::repS_shield,
    // original
    &Battle::novice_shield,
    &Battle::elite_shield,
    &Battle::brave_shield,
    &Battle::prytwen,
    &Battle::aegis,

    // xxxx11    Axe         アックス
    // replica
    &Battle::repB_axe,
    &Battle::repB_axe,
    &Battle::repB_axe,
    &Battle::repB_axe,
    &Battle::repB_axe,
    &Battle::repA_axe,
    &Battle::repS_axe,
    // original
    &Battle::novice_axe,
    &Battle::elite_axe,
    &Battle::brave_axe,
    &Battle::tecumsehs_tomahawk,
    &Battle::viking_axe,

    // xxxx12    Etheremon   イーサエモン
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,
    &Battle::dummy_active,
    // original
    &Battle::etheremon_ekopi,
    &Battle::etheremon_malakele,    
    &Battle::etheremon_mapla,
    &Battle::etheremon_siberizen,
    &Battle::eheremon_zedakazm,

    // xxxx13    Yumi        ユミ
    // replica
    &Battle::repB_yumi,
    &Battle::repB_yumi,
    &Battle::repB_yumi,
    &Battle::repB_yumi,
    &Battle::repB_yumi,
    &Battle::repA_yumi,
    &Battle::repS_yumi,
    // original
    &Battle::novice_yumi,
    &Battle::elite_yumi,
    &Battle::brave_yumi,
    &Battle::raijyodo,
    &Battle::yoichi_no_yumi,

    // xxxx14    Cross Spear       クロススピア
    // replica
    &Battle::repB_cross_spear,
    &Battle::repB_cross_spear,
    &Battle::repB_cross_spear,
    &Battle::repB_cross_spear,
    &Battle::repB_cross_spear,
    &Battle::repA_cross_spear,
    &Battle::repS_cross_spear,
    // original
    &Battle::novice_cross_spear,
    &Battle::elite_cross_spear,
    &Battle::brave_cross_spear,
    &Battle::bone_piercing_cross_spear,
    &Battle::tonbokiri,

    // xxxx15    Halberd     ハルバード
    // replica
    &Battle::repB_halberd,
    &Battle::repB_halberd,
    &Battle::repB_halberd,
    &Battle::repB_halberd,
    &Battle::repB_halberd,
    &Battle::repA_halberd,
    &Battle::repS_halberd,
    // original
    &Battle::novice_halberd,
    &Battle::elite_halberd,
    &Battle::brave_halberd,
    &Battle::zhang_eight_snake_halberd,
    &Battle::lu_bus_helberd,

    // xxxx16    Scrolls     スクロール
    // replica
    &Battle::repB_scrolls,
    &Battle::repB_scrolls,
    &Battle::repB_scrolls,
    &Battle::repB_scrolls,
    &Battle::repB_scrolls,
    &Battle::repA_scrolls,
    &Battle::repS_scrolls,
    // original
    &Battle::novice_scrolls,
    &Battle::elite_scrolls,
    &Battle::wizdom_scrolls,
    &Battle::the_art_of_war,
    &Battle::da_tang_western_region,

    // xxxx17    Necklace    ネックレス
    // replica
    &Battle::repB_necklace,
    &Battle::repB_necklace,
    &Battle::repB_necklace,
    &Battle::repB_necklace,
    &Battle::repB_necklace,
    &Battle::repA_necklace,
    &Battle::repS_necklace,
    // original
    &Battle::novice_necklace,
    &Battle::elite_necklace,
    &Battle::wizdom_necklace,
    &Battle::siberian_cedar_necklace,
    &Battle::necklace_of_the_sun_god,

    // xxxx18    Kabuto      カブト
    // replica
    &Battle::repB_kabuto,
    &Battle::repB_kabuto,
    &Battle::repB_kabuto,
    &Battle::repB_kabuto,
    &Battle::repB_kabuto,
    &Battle::repA_kabuto,
    &Battle::repS_kabuto,
    // original
    &Battle::novice_kabuto,
    &Battle::elite_kabuto,
    &Battle::brave_kabuto,
    &Battle::shingens_kabuto,
    &Battle::crescent_moon_kabuto,

    // xxxx19    Turtle      タートル
    // replica
    &Battle::repB_turtle,
    &Battle::repB_turtle,
    &Battle::repB_turtle,
    &Battle::repB_turtle,
    &Battle::repB_turtle,
    &Battle::repA_turtle,
    &Battle::repS_turtle,
    // original
    &Battle::novice_turtle,
    &Battle::elite_turtle,
    &Battle::wizdom_turtle,
    &Battle::akeron,
    &Battle::akupara,

    // xxxx20    Roostler    ルースター
    // replica
    &Battle::repB_roostler,
    &Battle::repB_roostler,
    &Battle::repB_roostler,
    &Battle::repB_roostler,
    &Battle::repB_roostler,
    &Battle::repA_roostler,
    &Battle::repS_roostler,
    // original
    &Battle::novice_roostler,
    &Battle::elite_roostler,
    &Battle::brave_roostler,
    &Battle::hotspur,
    &Battle::golden_rooster,

    // xxxx21    Tiger       タイガー
    // replica
    &Battle::repB_tiger,
    &Battle::repB_tiger,
    &Battle::repB_tiger,
    &Battle::repB_tiger,
    &Battle::repB_tiger,
    &Battle::repA_tiger,
    &Battle::repS_tiger,
    // original
    &Battle::novice_tiger,
    &Battle::elite_tiger,
    &Battle::brave_tiger,
    &Battle::amur_tiger,
    &Battle::saber_toothed_tiger,

    // xxxx22    Dragon      ドラゴン
    // replica
    &Battle::repB_dragon,
    &Battle::repB_dragon,
    &Battle::repB_dragon,
    &Battle::repB_dragon,
    &Battle::repB_dragon,
    &Battle::repA_dragon,
    &Battle::repS_dragon,
    // original
    &Battle::novice_dragon,
    &Battle::elite_dragon,
    &Battle::wizdom_dragon,
    &Battle::wyvern_dragon,
    &Battle::golden_dragon,

    // xxxx23    Bull        ブル
    // replica
    &Battle::repB_bull,
    &Battle::repB_bull,
    &Battle::repB_bull,
    &Battle::repB_bull,
    &Battle::repB_bull,
    &Battle::repA_bull,
    &Battle::repS_bull,
    // original
    &Battle::novice_bull,
    &Battle::elite_bull,
    &Battle::brave_bull,
    &Battle::bison,
    &Battle::golden_bull,

    // xxxx24    Elephant    エレファント
    // replica
    &Battle::repB_elephant,
    &Battle::repB_elephant,
    &Battle::repB_elephant,
    &Battle::repB_elephant,
    &Battle::repB_elephant,
    &Battle::repA_elephant,
    &Battle::repS_elephant,
    // original
    &Battle::novice_elephant,
    &Battle::elite_elephant,
    &Battle::brave_elephant,
    &Battle::mammoth,
    &Battle::hannibals_war_elephant,

    // xxxx25    Monkey      モンキー
    // replica
    &Battle::repB_monkey,
    &Battle::repB_monkey,
    &Battle::repB_monkey,
    &Battle::repB_monkey,
    &Battle::repB_monkey,
    &Battle::repA_monkey,
    &Battle::repS_monkey,
    // original
    &Battle::novice_monkey,
    &Battle::elite_monkey,
    &Battle::wizdom_monkey,
    &Battle::silver_back,
    &Battle::hihi,

    // xxxx26    Snake       スネーク
    // replica
    &Battle::repB_snake,
    &Battle::repB_snake,
    &Battle::repB_snake,
    &Battle::repB_snake,
    &Battle::repB_snake,
    &Battle::repA_snake,
    &Battle::repS_snake,
    // original
    &Battle::novice_snake,
    &Battle::elite_snake,
    &Battle::wizdom_snake,
    &Battle::king_cobra,
    &Battle::quetzalcoatl,

    // xxxx27    Dog         ドッグ
    // replica
    &Battle::repB_dog,
    &Battle::repB_dog,
    &Battle::repB_dog,
    &Battle::repB_dog,
    &Battle::repB_dog,
    &Battle::repA_dog,
    &Battle::repS_dog,
    // original
    &Battle::novice_dog,
    &Battle::elite_dog,
    &Battle::wizdom_dog,
    &Battle::molossus,
    &Battle::shippei_taro,

    // アートエディットスキル
        
    // xxxxxx0   休む
    &Battle::rest,
    // xxxxxx1   レッドストライク
    &Battle::red_strike,
    // xxxxxx2   ハット・トリック
    &Battle::hat_trick,
    // xxxxxx3   Punks Not Dead
    &Battle::punks_not_dead,
    // xxxxxx4   マゼンタマッシュルーム
    &Battle::magenta_mushroom,
    // xxxxxx5   ゴロゴロパンチ
    &Battle::cat_punch,
    // xxxxxx6   無垢なる忠誠
    &Battle::dogs_loyalty,
    // xxxxxx7   サイドワインダー
    &Battle::side_winder,
    // xxxxxx8   女神のウインク
    &Battle::goddess_wink,
    // xxxxxx9   自由の女神
    &Battle::goddess_of_liberty,
    // xxxxx10   ブラックシャウト
    &Battle::black_shout,
    // xxxxx11   モンキー・マジック
    &Battle::monkey_magic,
    // xxxxx12   ガールズ・トーク
    &Battle::girls_talk,
    // xxxxx13   ダンディズム
    &Battle::dandyism,
    // xxxxx14   中二病
    &Battle::fatal_desease,
    // xxxxx15   万里の長城
    &Battle::chinese_wall,
    // xxxxx16   霊峰富士
    &Battle::mt_fuji,
    // xxxxx17   イエローブラスト
    &Battle::yellow_blast,
    // xxxxx18   グリーンリース
    &Battle::green_wreath,
    // xxxxx19   シアンフロスト
    &Battle::cyan_frost,
    // xxxxx20   ハード・トレーニング
    &Battle::hard_training,
    // xxxxx21   ハイ・フライヤー
    &Battle::high_flyer,
    // xxxxx22   フル・スロットル
    &Battle::full_throttle,
    // xxxxx23   ブルーブロッサム
    &Battle::blue_blossom,
    // xxxxx24   眼鏡効果
    &Battle::grasses_effect,
    // xxxxx25   ホワイトキャンディー
    &Battle::white_candy,
    // xxxxx26   森林浴
    &Battle::forest_bath,
    // xxxxx27   無条件幸福
    &Battle::happiness_in_life,
    // xxxxx28   紳士の品格
    &Battle::gentlemans_dignity,
};

void Battle::active_skill( ACTIVE_SKILL_ID id, Position p )
{
    printActiveSkill( id );
    int index = convertIDToFunctionIndex( id );
    (this->*functionPointerTableActive[index])( p ); 
}


void Battle::dummy_active( Position p ) {}



// xxxxx1    blade     ブレード
// replica
void Battle::repB_blade( Position p ) {
    damageSkill( p, FrontEnemy, 60, PHY, ACTIVE_DAMAGE );
}
void Battle::repA_blade( Position p ) {
    damageSkill( p, FrontEnemy, 65, PHY, ACTIVE_DAMAGE );
}
void Battle::repS_blade( Position p ) {
    damageSkill( p, FrontEnemy, 70, PHY, ACTIVE_DAMAGE );
}
// original
void Battle::novice_blade( Position p ) {
    damageSkill( p, FrontEnemy, 50, 60, PHY, ACTIVE_DAMAGE );
}
void Battle::elite_blade( Position p ) {
    damageSkill( p, FrontEnemy, 55, 65, PHY, ACTIVE_DAMAGE );
}
void Battle::brave_blade( Position p ) {
    damageSkill( p, FrontEnemy, 60, 70, PHY, ACTIVE_DAMAGE );
}
void Battle::imperial_blade( Position p ) {
    damageSkill( p, FrontEnemy, 65, 75, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 5, BUFF );
}
void Battle::mch_blade( Position p ) {
    damageSkill( p, FrontEnemy, 70, 80, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 10, BUFF );
}


// xxxxx2    musket  　  マスケット
// replica
void Battle::repB_musket( Position p ) {
    damageSkill( p, AllEnemy, 30, INT, ACTIVE_DAMAGE );
}
void Battle::repA_musket( Position p ) {
    damageSkill( p, AllEnemy, 35, INT, ACTIVE_DAMAGE );
}
void Battle::repS_musket( Position p ) {
    damageSkill( p, AllEnemy, 40, INT, ACTIVE_DAMAGE );
}
// original
void Battle::novice_musket( Position p ) {
    damageSkill( p, AllEnemy, 25, 30, INT, ACTIVE_DAMAGE );
}
void Battle::elite_musket( Position p ) {
    damageSkill( p, AllEnemy, 30, 35, INT, ACTIVE_DAMAGE );
}
void Battle::brave_musket( Position p ) {
    damageSkill( p, AllEnemy, 35, 40, INT, ACTIVE_DAMAGE );
}
void Battle::the_three_musketeers_musket( Position p ) {
    damageSkill( p, AllEnemy, 40, 45, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, INT, INT, 5, BUFF );
}
void Battle::grande_armee( Position p ) {
    damageSkill( p, AllEnemy, 45, 50, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, INT, INT, 10, BUFF );
}

// xxxxx3    Quill       ペン
// replica
void Battle::repB_quill( Position p ) {
    healSkill( p, HP, LOW, ALLY, 40 );
}
void Battle::repA_quill( Position p ) {
    healSkill( p, HP, LOW, ALLY, 40 );
}
void Battle::repS_quill( Position p ) {
    healSkill( p, HP, LOW, ALLY, 40 );
}
// original
void Battle::novice_quill( Position p ) {
    healSkill( p, HP, LOW, ALLY, 30, 40 );
}
void Battle::elite_quill( Position p ) {
    healSkill( p, HP, LOW, ALLY, 40, 50 );
}
void Battle::wizdom_quill( Position p ) {
    healSkill( p, HP, LOW, ALLY, 50, 60 );
}
void Battle::master_musicians_quill( Position p ) {
    healSkill( p, HP, LOW, ALLY, 50, 70 );
    changeAttrSkill( p, OneSelf, INT, INT, 5, BUFF );
}
void Battle::playwrights_quill( Position p ) {
    healSkill( p, HP, LOW, ALLY, 70, 80 );
    changeAttrSkill( p, OneSelf, INT, INT, 10, BUFF );
}


// xxxxx4    Armor       アーマー
// replica
void Battle::repB_armor( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 10, BUFF );
}
void Battle::repA_armor( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 15, BUFF );
}
void Battle::repS_armor( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 20, BUFF );
}
// original
void Battle::novice_armor( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 5, 10, BUFF );
}
void Battle::elite_armor( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 10, 15, BUFF );
}
void Battle::brave_armor( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 15, 20, BUFF );
}
void Battle::fluted_armor( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 20, 25, BUFF );
    healSkill( p, OneSelf, 5 );
}
void Battle::mch_armor( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 25, 30, BUFF );
    healSkill( p, OneSelf, 10 );
}

// xxxxx5    Horse       ホース
// replica
void Battle::repB_horse( Position p ) {
    changeAttrSkill( p, OneSelf, AGI, AGI, 5, BUFF );
}
void Battle::repA_horse( Position p ) {
    changeAttrSkill( p, OneSelf, AGI, AGI, 5, 10, BUFF );
}
void Battle::repS_horse( Position p ) {
    changeAttrSkill( p, OneSelf, AGI, AGI, 5, 12, BUFF );
}
// original
void Battle::novice_horse( Position p ) {
    changeAttrSkill( p, OneSelf, AGI, AGI, 10, BUFF );
}
void Battle::elite_horse( Position p ) {
    changeAttrSkill( p, OneSelf, AGI, AGI, 5, 15, BUFF );
}
void Battle::brave_horse( Position p ) {
    changeAttrSkill( p, OneSelf, AGI, AGI, 5, 20, BUFF );
}
void Battle::red_hare( Position p ) {
    changeAttrSkill( p, AllAlly, AGI, AGI, 5, 10, BUFF );
}
void Battle::bucephalus( Position p ) {
    changeAttrSkill( p, AllAlly, AGI, AGI, 5, 15, BUFF );
}

// xxxxx6    Katana      カタナ
// replica
void Battle::repB_katana( Position p ) {
    damageSkill( p, FrontEnemy, 55, PHY, ACTIVE_DAMAGE );
}
void Battle::repA_katana( Position p ) {
    damageSkill( p, FrontEnemy, 60, PHY, ACTIVE_DAMAGE );
}
void Battle::repS_katana( Position p ) {
    damageSkill( p, FrontEnemy, 65, PHY, ACTIVE_DAMAGE );
}
// original
void Battle::novice_katana( Position p ) {
    damageSkill( p, FrontEnemy, 45, 55, PHY, ACTIVE_DAMAGE );
}
void Battle::elite_katana( Position p ) {
    damageSkill( p, FrontEnemy, 50, 60, PHY, ACTIVE_DAMAGE );
}
void Battle::brave_katana( Position p ) {
    damageSkill( p, FrontEnemy, 55, 65, PHY, ACTIVE_DAMAGE );
}
void Battle::izuminokami_kanesada( Position p ) {
    damageSkill( p, FrontEnemy, 60, 70, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, PHY, PHY, 5, DEBUFF );
    
}
void Battle::heshikiri_hasebe( Position p ) {
    damageSkill( p, FrontEnemy, 65, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, PHY, PHY, 10, DEBUFF );
}

// xxxxx7    Cutie       キューティー
// original
void Battle::cutie_cat( Position p ) {
    healSkill( p, OneSelf, 30 );
    statusAilmentSkill( p, FrontEnemy, Confusion );
}
void Battle::cutie_kyubi( Position p ) {
    damageSkill( p, FrontEnemy, 45, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Sleep );
}
void Battle::cutie_alien( Position p ) {
    damageSkill( p, FrontEnemy, 60, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Poison );
}

// xxxxx8    Book        ブック
// replica
void Battle::repB_book( Position p ) {
    damageSkill( p, AllEnemy, 30, INT, ACTIVE_DAMAGE );
}
void Battle::repA_book( Position p ) {
    damageSkill( p, AllEnemy, 35, INT, ACTIVE_DAMAGE );
}
void Battle::repS_book( Position p ) {
    damageSkill( p, AllEnemy, 40, INT, ACTIVE_DAMAGE );
}
// original
void Battle::novice_book( Position p ) {
    damageSkill( p, AllEnemy, 25, 30 , INT, ACTIVE_DAMAGE );
}
void Battle::elite_book( Position p ) {
    damageSkill( p, AllEnemy, 30, 35 , INT, ACTIVE_DAMAGE );
}
void Battle::wizdom_book( Position p ) {
    damageSkill( p, AllEnemy, 35, 40 , INT, ACTIVE_DAMAGE );
}
void Battle::crime_and_punishment( Position p ) {
    damageSkill( p, AllEnemy, 40, 45 , INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, INT, INT, 5, DEBUFF );
}
void Battle::codex_atlanticus( Position p ) {
    damageSkill( p, AllEnemy, 45, 50 , INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, INT, INT, 10, DEBUFF );
}

// xxxxx9    Ring        リング
// replica
void Battle::repB_ring( Position p ) {
    healSkill( p, HP, LOW, ALLY, 30 );
}
void Battle::repA_ring( Position p ) {
    healSkill( p, HP, LOW, ALLY, 35 );
}
void Battle::repS_ring( Position p ) {
    healSkill( p, HP, LOW, ALLY, 40 );
}
// original
void Battle::novice_ring( Position p ) {
    healSkill( p, HP, LOW, ALLY, 30, 40 );
}
void Battle::elite_ring( Position p ) {
    healSkill( p, HP, LOW, ALLY, 40, 50 );
}
void Battle::wizdom_ring( Position p ) {
    healSkill( p, HP, LOW, ALLY, 50, 60 );
}
void Battle::mysterious_stone_glow( Position p ) {
    healSkill( p, HP, LOW, ALLY, 60, 70 );
    changeAttrSkill( p, FrontAlly, INT, INT, 5, BUFF );
}
void Battle::ring_of_the_queen( Position p ) {
    healSkill( p, HP, LOW, ALLY, 70, 80 );
    changeAttrSkill( p, FrontAlly, INT, INT, 10, BUFF );
}

// xxxx10    Shield      シールド
// replica
void Battle::repB_shield( Position p ) {
    damageSkill( p, FrontEnemy, 30, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, AGI, PHY, 2, DEBUFF );
}
void Battle::repA_shield( Position p ) {
    damageSkill( p, FrontEnemy, 32, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, AGI, PHY, 2, DEBUFF );
}
void Battle::repS_shield( Position p ) {
    damageSkill( p, FrontEnemy, 35, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, AGI, PHY, 2, DEBUFF );
}
// original
void Battle::novice_shield( Position p ) {
    damageSkill( p, FrontEnemy, 25, 30, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, AGI, PHY, 5, DEBUFF );
}
void Battle::elite_shield( Position p ) {
    damageSkill( p, FrontEnemy, 27, 32, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, AGI, PHY, 5, DEBUFF );
}
void Battle::brave_shield( Position p ) {
    damageSkill( p, FrontEnemy, 30, 35, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, AGI, PHY, 5, DEBUFF );
}
void Battle::prytwen( Position p ) {
    damageSkill( p, FrontEnemy, 32, 37, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, AGI, PHY, 10, DEBUFF );
}
void Battle::aegis( Position p ) {
    damageSkill( p, FrontEnemy, 35, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, AGI, PHY, 15, DEBUFF );
}

// xxxx11    Axe         アックス
// replica
void Battle::repB_axe( Position p ) {
    damageSkill( p, FrontEnemy, 55, PHY, ACTIVE_DAMAGE );
}
void Battle::repA_axe( Position p ) {
    damageSkill( p, FrontEnemy, 60, PHY, ACTIVE_DAMAGE );
}
void Battle::repS_axe( Position p ) {
    damageSkill( p, FrontEnemy, 65, PHY, ACTIVE_DAMAGE );
}
// original
void Battle::novice_axe( Position p ) {
    damageSkill( p, FrontEnemy, 45, 55, PHY, ACTIVE_DAMAGE );
}
void Battle::elite_axe( Position p ) {
    damageSkill( p, FrontEnemy, 50, 60, PHY, ACTIVE_DAMAGE );
}
void Battle::brave_axe( Position p ) {
    damageSkill( p, FrontEnemy, 55, 65, PHY, ACTIVE_DAMAGE );
}
void Battle::tecumsehs_tomahawk( Position p ) {
    damageSkill( p, FrontEnemy, 60, 70, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, INT, PHY, 5, DEBUFF );
}
void Battle::viking_axe( Position p ) {
    damageSkill( p, FrontEnemy, 65, 75, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, INT, PHY, 10, DEBUFF );
}

// xxxx12    Etheremon   イーサエモン
// original
void Battle::etheremon_ekopi( Position p ) {
    damageSkill( p, FrontEnemy, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 3, BUFF );
}
void Battle::etheremon_malakele( Position p ) {
    damageSkill( p, FrontEnemy, 30, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Poison );
}    
void Battle::etheremon_mapla( Position p ) {
    healSkill( p, HP, LOW, ALLY, 25, 30 );
    healSkill( p, HP, LOW, ALLY, 25, 30 );
}
void Battle::etheremon_siberizen( Position p ) {
    damageSkill( p, PHY, LOW, ENEMY, 50, 55, INT, ACTIVE_DAMAGE );
}
void Battle::eheremon_zedakazm( Position p ) {
    // 要検証
}

// xxxx13    Yumi        ユミ
// replica
void Battle::repB_yumi( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 45, PHY, ACTIVE_DAMAGE );
}
void Battle::repA_yumi( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 50, PHY, ACTIVE_DAMAGE );
}
void Battle::repS_yumi( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 55, PHY, ACTIVE_DAMAGE );
}
// original
void Battle::novice_yumi( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 35, 45, PHY, ACTIVE_DAMAGE );
}
void Battle::elite_yumi( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 40, 50, PHY, ACTIVE_DAMAGE );
}
void Battle::brave_yumi( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 45, 55, PHY, ACTIVE_DAMAGE );
}
void Battle::raijyodo( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 50, 60, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 5, BUFF );
}
void Battle::yoichi_no_yumi( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 55, 75, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 10, BUFF );
}

// xxxx14    Cross Spear       クロススピア
// replica
void Battle::repB_cross_spear( Position p ) {
    damageSkill( p, FrontEnemy, 25, PHY, ACTIVE_DAMAGE );
    damageSkill( p, FrontEnemy, 25, PHY, ACTIVE_DAMAGE );
}
void Battle::repA_cross_spear( Position p ) {
    // 調査中
}
void Battle::repS_cross_spear( Position p ) {
    // 調査中
}
// original
void Battle::novice_cross_spear( Position p ) {
    damageSkill( p, FrontEnemy, 20, 25, PHY, ACTIVE_DAMAGE );
}
void Battle::elite_cross_spear( Position p ) {
    damageSkill( p, FrontEnemy, 22, 27, PHY, ACTIVE_DAMAGE );
}
void Battle::brave_cross_spear( Position p ) {
    damageSkill( p, FrontEnemy, 25, 30, PHY, ACTIVE_DAMAGE );
}
void Battle::bone_piercing_cross_spear( Position p ) {
    damageSkill( p, FrontEnemy, 30, 35, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontAlly, PHY, PHY, 5, BUFF );
}
void Battle::tonbokiri( Position p ) {
    damageSkill( p, FrontEnemy, 30, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontAlly, PHY, PHY, 10, BUFF );
}

// xxxx15    Halberd     ハルバード
// replica
void Battle::repB_halberd( Position p ) {
    damageSkill( p, FrontEnemy, 50, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
}
void Battle::repA_halberd( Position p ) {
    damageSkill( p, FrontEnemy, 55, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
}
void Battle::repS_halberd( Position p ) {
    damageSkill( p, FrontEnemy, 60, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
}
// original
void Battle::novice_halberd( Position p ) {
    damageSkill( p, FrontEnemy, 40, 50, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
}
void Battle::elite_halberd( Position p ) {
    damageSkill( p, FrontEnemy, 45, 55, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
}
void Battle::brave_halberd( Position p ) {
    damageSkill( p, FrontEnemy, 50, 60, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
}
void Battle::zhang_eight_snake_halberd( Position p ) {
    damageSkill( p, FrontEnemy, 55, 65, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
    changeAttrSkill( p, HP, LOW, ALLY, PHY, PHY, 5, BUFF );
}
void Battle::lu_bus_helberd( Position p ) {
    damageSkill( p, FrontEnemy, 60, 70, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
    changeAttrSkill( p, HP, LOW, ALLY, PHY, PHY, 10, BUFF );
}

// xxxx16    Scrolls     スクロール
// replica
void Battle::repB_scrolls( Position p ) {
    damageSkill( p, AllEnemy, 20, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Poison );
}
void Battle::repA_scrolls( Position p ) {
    damageSkill( p, AllEnemy, 25, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Poison );
}
void Battle::repS_scrolls( Position p ) {
    damageSkill( p, AllEnemy, 30, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Poison );
}
// original
void Battle::novice_scrolls( Position p ) {
    damageSkill( p, AllEnemy, 15, 20, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, AGI, HIGH, ENEMY, Poison );
}
void Battle::elite_scrolls( Position p ) {
    damageSkill( p, AllEnemy, 20, 25, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, AGI, HIGH, ENEMY, Poison );
}
void Battle::wizdom_scrolls( Position p ) {
    damageSkill( p, AllEnemy, 25, 30, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, AGI, HIGH, ENEMY, Poison );
}
void Battle::the_art_of_war( Position p ) {
    damageSkill( p, AllEnemy, 30, 35, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, AGI, HIGH, ENEMY, Poison );
    changeAttrSkill( p, HP, LOW, ALLY, INT, INT, 5, BUFF );
}
void Battle::da_tang_western_region( Position p ) {
    damageSkill( p, AllEnemy, 35, 40, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, AGI, HIGH, ENEMY, Poison );
    changeAttrSkill( p, HP, LOW, ALLY, INT, INT, 10, BUFF );
}

// xxxx17    Necklace    ネックレス
// replica
void Battle::repB_necklace( Position p ) {
    healSkill( p, HP, LOW, ALLY, 10 );
    healSkill( p, OneSelf, 10 );
}
void Battle::repA_necklace( Position p ) {
    healSkill( p, HP, LOW, ALLY, 15 );
    healSkill( p, OneSelf, 15 );
}
void Battle::repS_necklace( Position p ) {
    healSkill( p, HP, LOW, ALLY, 20 );
    healSkill( p, OneSelf, 20 );
}
// original
void Battle::novice_necklace( Position p ) {
    healSkill( p, HP, LOW, ALLY, 10 );
    healSkill( p, OneSelf, 10 );
}
void Battle::elite_necklace( Position p ) {
    healSkill( p, HP, LOW, ALLY, 10, 15 );
    healSkill( p, OneSelf, 10, 15 );
}
void Battle::wizdom_necklace( Position p ) {
    healSkill( p, HP, LOW, ALLY, 10, 20 );
    healSkill( p, OneSelf, 10, 20 );
}
void Battle::siberian_cedar_necklace( Position p ) {
    healSkill( p, HP, LOW, ALLY, 15, 25 );
    healSkill( p, OneSelf, 15, 25 );
    changeAttrSkill( p, OneSelf, INT, INT, 5, BUFF );
}
void Battle::necklace_of_the_sun_god( Position p ) {
    healSkill( p, HP, LOW, ALLY, 20, 30 );
    healSkill( p, OneSelf, 20, 30 );
    changeAttrSkill( p, OneSelf, INT, INT, 10, BUFF );
}

// xxxx18    Kabuto      カブト
// replica
void Battle::repB_kabuto( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 5, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 5, BUFF );
}
void Battle::repA_kabuto( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 6, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 6, BUFF );
}
void Battle::repS_kabuto( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 7, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 7, BUFF );
}
// original
void Battle::novice_kabuto( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 6, 11, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 6, 11, BUFF );
}
void Battle::elite_kabuto( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 7, 12, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 7, 12, BUFF );
}
void Battle::brave_kabuto( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 8, 13, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 8, 13, BUFF );
}
void Battle::shingens_kabuto( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 9, 14, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 9, 14, BUFF );
    changeAttrSkill( p, HP, LOW, ENEMY, INT, INT, 5, DEBUFF );
}
void Battle::crescent_moon_kabuto( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 10, 15, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 10, 15, BUFF );
    changeAttrSkill( p, HP, LOW, ENEMY, INT, INT, 10, DEBUFF );
}

// xxxx19    Turtle      タートル
// replica
void Battle::repB_turtle( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 2, 7, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 2, 7, BUFF );
    healSkill( p, OneSelf, 5 );
}
void Battle::repA_turtle( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 3, 8, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 3, 8, BUFF );
    healSkill( p, OneSelf, 10 );
}
void Battle::repS_turtle( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 7, 12, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 7, 12, BUFF );
    healSkill( p, OneSelf, 15 );
}
// original
void Battle::novice_turtle( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 3, 8, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 3, 8, BUFF );
    healSkill( p, OneSelf, 10 );
}
void Battle::elite_turtle( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 4, 9, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 4, 9, BUFF );
    healSkill( p, OneSelf, 15 );
}
void Battle::wizdom_turtle( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 5, 10, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 5, 10, BUFF );
    healSkill( p, OneSelf, 20 );
}
void Battle::akeron( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 9, 14, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 9, 14, BUFF );
    healSkill( p, OneSelf, 25 );
}
void Battle::akupara( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 10, 15, BUFF );
    changeAttrSkill( p, OneSelf, INT, INT, 10, 15, BUFF );
    healSkill( p, OneSelf, 30 );
}

// xxxx20    Roostler    ルースター
// replica
void Battle::repB_roostler( Position p ) {
    damageSkill( p, FrontEnemy, 15, 20, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, AGI, AGI, 5, BUFF );
}
void Battle::repA_roostler( Position p ) {
    damageSkill( p, FrontEnemy, 20, 25, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, AGI, AGI, 7, BUFF );
}
void Battle::repS_roostler( Position p ) {
    damageSkill( p, FrontEnemy, 25, 30, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, AGI, AGI, 9, BUFF );
}
// original
void Battle::novice_roostler( Position p ) {
    damageSkill( p, FrontEnemy, 20, 25, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, AGI, AGI, 7, BUFF );
}
void Battle::elite_roostler( Position p ) {
    damageSkill( p, FrontEnemy, 25, 30, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, AGI, AGI, 9, BUFF );
}
void Battle::brave_roostler( Position p ) {
    damageSkill( p, FrontEnemy, 30, 35, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, AGI, AGI, 11, BUFF );
}
void Battle::hotspur( Position p ) {
    damageSkill( p, FrontEnemy, 35, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, AGI, AGI, 13, BUFF );
}
void Battle::golden_rooster( Position p ) {
    damageSkill( p, FrontEnemy, 35, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, AGI, AGI, 15, BUFF );
}

// xxxx21    Tiger       タイガー
// replica
void Battle::repB_tiger( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, AGI, 15, BUFF );
    damageSkill( p, FrontEnemy, 35, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, AGI, 20, DEBUFF );
}
void Battle::repA_tiger( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, AGI, 15, BUFF );
    damageSkill( p, FrontEnemy, 35, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, AGI, 18, DEBUFF );
}
void Battle::repS_tiger( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, AGI, 15, BUFF );
    damageSkill( p, FrontEnemy, 35, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, AGI, 16, DEBUFF );
}
// original
void Battle::novice_tiger( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, AGI, 15, BUFF );
    damageSkill( p, FrontEnemy, 35, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, AGI, 18, DEBUFF );
}
void Battle::elite_tiger( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, AGI, 15, BUFF );
    damageSkill( p, FrontEnemy, 45, 50, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, AGI, 16, DEBUFF );
}
void Battle::brave_tiger( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, AGI, 15, BUFF );
    damageSkill( p, FrontEnemy, 45, 50, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, AGI, 14, DEBUFF );
}
void Battle::amur_tiger( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, AGI, 15, BUFF );
    damageSkill( p, FrontEnemy, 45, 50, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, AGI, 12, DEBUFF );
}
void Battle::saber_toothed_tiger( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, AGI, 20, BUFF );
    damageSkill( p, FrontEnemy, 45, 50, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, AGI, 10, DEBUFF );
}

// xxxx22    Dragon      ドラゴン
// replica
void Battle::repB_dragon( Position p ) {
    damageSkill( p, AllEnemy, 10, 15, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllEnemy, INT, INT, 5, DEBUFF );
}
void Battle::repA_dragon( Position p ) {
    damageSkill( p, AllEnemy, 10, 15, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllEnemy, INT, INT, 6, DEBUFF );
}
void Battle::repS_dragon( Position p ) {
    damageSkill( p, AllEnemy, 15, 20, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllEnemy, INT, INT, 7, DEBUFF );
}
// original
void Battle::novice_dragon( Position p ) {
    damageSkill( p, AllEnemy, 15, 20, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllEnemy, INT, INT, 6, DEBUFF );
}
void Battle::elite_dragon( Position p ) {
    damageSkill( p, AllEnemy, 15, 20, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllEnemy, INT, INT, 7, DEBUFF );
}
void Battle::wizdom_dragon( Position p ) {
    damageSkill( p, AllEnemy, 20, 25, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllEnemy, INT, INT, 8, DEBUFF );
}
void Battle::wyvern_dragon( Position p ) {
    damageSkill( p, AllEnemy, 25, 30, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllEnemy, INT, INT, 9, DEBUFF );
}
void Battle::golden_dragon( Position p ) {
    damageSkill( p, AllEnemy, 25, 30, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllEnemy, INT, INT, 10, DEBUFF );
}

// xxxx23    Bull        ブル
// replica
void Battle::repB_bull( Position p ) {
    damageSkill( p, AllEnemy, 25, 35, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 10, DEBUFF );
}
void Battle::repA_bull( Position p ) {
    damageSkill( p, AllEnemy, 30, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 9, DEBUFF );
}
void Battle::repS_bull( Position p ) {
    // 調査中
}
// original
void Battle::novice_bull( Position p ) {
    damageSkill( p, AllEnemy, 30, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 9, DEBUFF );
}
void Battle::elite_bull( Position p ) {
    damageSkill( p, AllEnemy, 35, 45, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 8, DEBUFF );
}
void Battle::brave_bull( Position p ) {
    damageSkill( p, AllEnemy, 40, 50, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 7, DEBUFF );
}
void Battle::bison( Position p ) {
    damageSkill( p, AllEnemy, 45, 55, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 6, DEBUFF );
}
void Battle::golden_bull( Position p ) {
    damageSkill( p, AllEnemy, 50, 60, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, PHY, 5, DEBUFF );
}

// xxxx24    Elephant    エレファント
// replica
void Battle::repB_elephant( Position p ) {
    damageSkill( p, FrontEnemy, 10, 15, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllAlly, PHY, PHY, 5, BUFF );
}
void Battle::repA_elephant( Position p ) {
    damageSkill( p, FrontEnemy, 15, 20, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllAlly, PHY, PHY, 6, BUFF );
}
void Battle::repS_elephant( Position p ) {
    damageSkill( p, FrontEnemy, 20, 25, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllAlly, PHY, PHY, 7, BUFF );
}
// original
void Battle::novice_elephant( Position p ) {
    damageSkill( p, FrontEnemy, 15, 20, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllAlly, PHY, PHY, 6, BUFF );
}
void Battle::elite_elephant( Position p ) {
    damageSkill( p, FrontEnemy, 20, 25, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllAlly, PHY, PHY, 7, BUFF );
}
void Battle::brave_elephant( Position p ) {
    damageSkill( p, FrontEnemy, 25, 30, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllAlly, PHY, PHY, 8, BUFF );
}
void Battle::mammoth( Position p ) {
    damageSkill( p, FrontEnemy, 30, 35, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllAlly, PHY, PHY, 9, BUFF );
}
void Battle::hannibals_war_elephant( Position p ) {
    damageSkill( p, FrontEnemy, 35, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllAlly, PHY, PHY, 10, BUFF );
}

// xxxx25    Monkey      モンキー
// replica
void Battle::repB_monkey( Position p ) {
    damageSkill( p, HP, LOW, ENEMY, 10, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, HP, LOW, ENEMY, Sleep );
}
void Battle::repA_monkey( Position p ) {
    damageSkill( p, HP, LOW, ENEMY, 10, 15, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, HP, LOW, ENEMY, Sleep );
}
void Battle::repS_monkey( Position p ) {
    // 調査中
}
// original
void Battle::novice_monkey( Position p ) {
    damageSkill( p, HP, LOW, ENEMY, 10, 15, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, HP, LOW, ENEMY, Sleep );
}
void Battle::elite_monkey( Position p ) {
    damageSkill( p, HP, LOW, ENEMY, 15, 20, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, HP, LOW, ENEMY, Sleep );
}
void Battle::wizdom_monkey( Position p ) {
    damageSkill( p, HP, LOW, ENEMY, 20, 25, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, HP, LOW, ENEMY, Sleep );
}
void Battle::silver_back( Position p ) {
    damageSkill( p, HP, LOW, ENEMY, 25, 30, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, HP, LOW, ENEMY, Sleep );
}
void Battle::hihi( Position p ) {
    damageSkill( p, HP, LOW, ENEMY, 30, 35, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, HP, LOW, ENEMY, Sleep );
}

// xxxx26    Snake       スネーク
// replica
void Battle::repB_snake( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, PHY, INT, 5, 15, BUFF );
    healSkill( p, HP, LOW, ALLY, 10, 30 );
}
void Battle::repA_snake( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, PHY, INT, 7, 17, BUFF );
    healSkill( p, HP, LOW, ALLY, 12, 32 );
}
void Battle::repS_snake( Position p ) {
    // 調査中
}
// original
void Battle::novice_snake( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, PHY, INT, 7, 17, BUFF );
    healSkill( p, HP, LOW, ALLY, 12, 32 );
}
void Battle::elite_snake( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, PHY, INT, 9, 19, BUFF );
    healSkill( p, HP, LOW, ALLY, 14, 34 );
}
void Battle::wizdom_snake( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, PHY, INT, 11, 21, BUFF );
    healSkill( p, HP, LOW, ALLY, 16, 36 );
}
void Battle::king_cobra( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, PHY, INT, 13, 23, BUFF );
    healSkill( p, HP, LOW, ALLY, 18, 38 );
}
void Battle::quetzalcoatl( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, PHY, INT, 15, 25, BUFF );
    healSkill( p, HP, LOW, ALLY, 20, 40 );
}

// xxxx27    Dog         ドッグ
// replica
void Battle::repB_dog( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 30, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 5, DEBUFF );
}
void Battle::repA_dog( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 30, 40, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 6, DEBUFF );
}
void Battle::repS_dog( Position p ) {
    // 調査中
}
// original
void Battle::novice_dog( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 30, 40, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 6, DEBUFF );
}
void Battle::elite_dog( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 35, 45, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 7, DEBUFF );
}
void Battle::wizdom_dog( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 40, 50, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 8, DEBUFF );
}
void Battle::molossus( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 45, 50, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 9, DEBUFF );
}
void Battle::shippei_taro( Position p ) {
    damageSkill( p, INT, HIGH, ENEMY, 50, 60, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 10, DEBUFF );
}


// xxxxxx0   休む
void Battle::rest( Position p ) {
    healSkill( p, OneSelf, 20 );
}
// xxxxxx1   レッドストライク
void Battle::red_strike( Position p ) {
    damageSkill( p, FrontEnemy, 40, 60, PHY, ACTIVE_DAMAGE );
}
// xxxxxx2   ハット・トリック
void Battle::hat_trick( Position p ) {
    damageSkill( p, FrontEnemy, 15, PHY, ACTIVE_DAMAGE );
    damageSkill( p, FrontEnemy, 15, PHY, ACTIVE_DAMAGE );
    damageSkill( p, FrontEnemy, 15, PHY, ACTIVE_DAMAGE );
}
// xxxxxx3   Punks Not Dead
void Battle::punks_not_dead( Position p ) {
    damageSkill( p, AllEnemy, 10, PHY, ACTIVE_DAMAGE );
    damageSkill( p, FrontEnemy,25, PHY, ACTIVE_DAMAGE );
}
// xxxxxx4   マゼンタマッシュルーム
void Battle::magenta_mushroom( Position p ) {
    damageSkill( p, FrontEnemy, 20, 40, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
}
// xxxxxx5   ゴロゴロパンチ
void Battle::cat_punch( Position p ) {
    damageSkill( p, FrontEnemy, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, AGI, AGI, 5, BUFF );
}
// xxxxxx6   無垢なる忠誠
void Battle::dogs_loyalty( Position p ) {
    damageSkill( p, FrontEnemy, 40, PHY, ACTIVE_DAMAGE );
    healSkill( p, OneSelf, 10 );
}
// xxxxxx7   サイドワインダー
void Battle::side_winder( Position p ) {
    damageSkill( p, FrontEnemy, 40, PHY, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Poison );
}
// xxxxxx8   女神のウインク
void Battle::goddess_wink( Position p ) {
    damageSkill( p, FrontEnemy, 40, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, PHY, INT, 5, DEBUFF );
}
// xxxxxx9   自由の女神
void Battle::goddess_of_liberty( Position p ) {
    damageSkill( p, AllEnemy, 10, PHY, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllEnemy, PHY, PHY, 5, DEBUFF );
}
// xxxxx10   ブラックシャウト
void Battle::black_shout( Position p ) {
    damageSkill( p, FrontEnemy, 40, 50, INT, ACTIVE_DAMAGE );
}
// xxxxx11   モンキー・マジック
void Battle::monkey_magic( Position p ) {
    damageSkill( p, FrontEnemy, 30, INT, ACTIVE_DAMAGE );
    statusAilmentSkill( p, FrontEnemy, Confusion );
}
// xxxxx12   ガールズ・トーク
void Battle::girls_talk( Position p ) {
    damageSkill( p, FrontEnemy, 30, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, INT, INT, 5, BUFF );
}
// xxxxx13   ダンディズム
void Battle::dandyism( Position p ) {
    damageSkill( p, FrontEnemy, 30, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, OneSelf, PHY, INT, 5, BUFF );
}
// xxxxx14   中二病
void Battle::fatal_desease( Position p ) {
    damageSkill( p, FrontEnemy, 30, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, FrontEnemy, INT, INT, 5, DEBUFF );
}
// xxxxx15   万里の長城
void Battle::chinese_wall( Position p ) {
    damageSkill( p, AllEnemy, 10, INT, ACTIVE_DAMAGE );
    changeAttrSkill( p, AllAlly, PHY, INT, 5, BUFF );
}
// xxxxx16   霊峰富士
void Battle::mt_fuji( Position p ) {
    damageSkill( p, AllEnemy, 10, INT, ACTIVE_DAMAGE );
    healSkill( p, AllAlly, 10 );
}
// xxxxx17   イエローブラスト
void Battle::yellow_blast( Position p ) {
    changeAttrSkill( p, FrontEnemy, INT, INT, 10, DEBUFF );
}
// xxxxx18   グリーンリース
void Battle::green_wreath( Position p ) {
    vector<Attr> va = { PHY, AGI };
    changeAttrSkill( p, FrontAlly, va, INT, 15, BUFF );
}
// xxxxx19   シアンフロスト
void Battle::cyan_frost( Position p ) {
    changeAttrSkill( p, FrontEnemy, PHY, INT, 10, DEBUFF );
}
// xxxxx20   ハード・トレーニング
void Battle::hard_training( Position p ) {
    changeAttrSkill( p, OneSelf, PHY, PHY, 5, BUFF );
    changeAttrSkill( p, FrontEnemy, AGI, AGI, 5, DEBUFF );
}
// xxxxx21   ハイ・フライヤー
void Battle::high_flyer( Position p ) {
    changeAttrSkill( p, OneSelf, AGI, AGI, 10, BUFF );
}
// xxxxx22   フル・スロットル
void Battle::full_throttle( Position p ) {
    changeAttrSkill( p, OneSelf, AGI, AGI, 5, BUFF );
    changeAttrSkill( p, FrontEnemy, AGI, AGI, 5, DEBUFF );
}
// xxxxx23   ブルーブロッサム
void Battle::blue_blossom( Position p ) {
    vector<Attr> va = { INT, AGI };
    changeAttrSkill( p, FrontAlly, va, INT, 10, BUFF );
}
// xxxxx24   眼鏡効果
void Battle::grasses_effect( Position p ) {
    changeAttrSkill( p, OneSelf, INT, INT, 5, BUFF );
    changeAttrSkill( p, FrontEnemy, INT, INT, 5, DEBUFF );
}
// xxxxx25   ホワイトキャンディー
void Battle::white_candy( Position p ) {
    healSkill( p, AllAlly, 20 );
}
// xxxxx26   森林浴
void Battle::forest_bath( Position p ) {
    healSkill( p, AllAlly, 10 );
    healSkill( p, HP, LOW, ALLY, 10 );
}
// xxxxx27   無条件幸福
void Battle::happiness_in_life( Position p ) {
    healSkill( p, HP, LOW, ALLY, 30 );
}
// xxxxx28   紳士の品格
void Battle::gentlemans_dignity( Position p ) {
    healSkill( p, OneSelf, 20 );
    changeAttrSkill( p, OneSelf, INT, INT, 5, BUFF );
}
