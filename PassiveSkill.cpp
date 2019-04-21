#include "Battle.hpp"


bool (Battle::*functionPointerTablePassive[])( Position p ) = {
    &Battle::dummy_passive,

    // Novice
    // MCHウォーリアー
    &Battle::MCH_Warrior, 
    // MCHタクティシャン
    &Battle::MCH_Tactician,
    // MCHアーティスト
    &Battle::MCH_Artist,
    // 福沢諭吉
    &Battle::Fukuzawa_Yukichi,
    // 孫尚香
    &Battle::Sun_Shangxiang,
    // パスカル
    &Battle::Blaise_Pascal,
    // ダビデ
    &Battle::David,
    // 雷電為右衛門
    &Battle::Raniden_Tameemon,
        
    // Uncommon
    // ライト兄弟
    &Battle::Wright_Brothers,
    // スパルタクス
    &Battle::Spartacus,
    // ジャック・ザ・リッパー
    &Battle::Jack_the_Ripper,
    // シューベルト
    &Battle::Franza_Schubert,
    // グリム兄弟
    &Battle::Brothers_Grimm,
    // アルキメデス
    &Battle::Archimedes,
    // サンタクロース
    &Battle::Santa_Claus,
    // シュレディンガー
    &Battle::Erwin_Schrodinger,
    // 森蘭丸
    &Battle::Mori_Ranmaru,
    // カフカ
    &Battle::Franz_Kafka,
    // 孫子
    &Battle::Sun_Tzu,
    // 石田三成
    &Battle::Ishida_Mitsunari,
    // 許褚
    &Battle::Xu_Chu,
    // 徳川慶喜
    &Battle::Tokugawa_Yoshinobu,
    // モンテスキュー
    &Battle::Montesquieu,
    // アナスタシア
    &Battle::Anastasia,
    // ジェロニモ
    &Battle::Geronimo,
    // 茶々
    &Battle::Lady_Chacha,

    // Rare
    // イーサエモン・レッド
    &Battle::Etheremon_Red,
    // ダルタニャン
    &Battle::Dartagnan,
    // 平賀源内
    &Battle::Gennai_Hiraga,
    // マタ・ハリ
    &Battle::Mata_Hari,
    // イーサエモン・ブルー
    &Battle::Etheremon_Blue,
    // イーサエモン・グリーン
    &Battle::Etheremon_Green,
    // 皇帝ネロ
    &Battle::Emperor_Nero,
    // ノストラダムス
    &Battle::Michel_Nostradamus,
    // 太公望
    &Battle::Jiang_Ziya,
    // 服部半蔵
    &Battle::Hanzo_Hattroi,
    // 前田慶次
    &Battle::Keiji_Maeda,
    // 天草四郎
    &Battle::Amakusa_Shiro,
    // 石川五右衛門
    &Battle::Goemon_Ishikawa,
    // 直江兼続
    &Battle::Naoe_Kanetsugu,
    // イワン雷帝
    &Battle::Ivan_the_Terrible,
    // 松尾芭蕉
    &Battle::Matsuo_Basho,
    // 三蔵法師
    &Battle::Xuanzang,
    // 武蔵坊弁慶
    &Battle::Benkei,
    // 黄忠
    &Battle::Huang_Zhong,
    // 貂蝉
    &Battle::Diao_Chan,
    // ヴァレンティヌス
    &Battle::Saint_Valentine,
    // ポカホンタス
    &Battle::Pocahontas,    
    // 孫堅
    &Battle::Sun_Jian,
    // ルーベンス
    &Battle::Peter_Paul_Rubens,
    // 真田幸村
    &Battle::Sanada_Yukimura,
    // ロビンフッド
    &Battle::Robin_Hood,
    // 楊端和
    &Battle::Yang_Duan_He,

    //Epic
    // 張飛
    &Battle::Zhang_Fei,
    // ナイチンゲール
    &Battle::Florence_Nightingale,
    // ベートーヴェン
    &Battle::Ludwig_van_Beethoven,
    // 佐々木小次郎
    &Battle::Kojiro_Sasaki,
    // 勝海舟
    &Battle::Kaishu_Katsu,
    // ビリー・ザ・キッド
    &Battle::Billy_the_Kid,
    // トーマス・エジソン
    &Battle::Thomas_Edison,
    // マルコ・ポーロ
    &Battle::Marco_Polo,
    // 伊達政宗
    &Battle::Masamune_Date,
    // 王キ
    &Battle::Wang_Ki,
    // マルクス
    &Battle::Karl_Marx,
    // 沖田総司
    &Battle::Soji_Okita,
    // チャイコフスキー
    &Battle::Pyotr_Tchaikovsky,
    // マリー・アントワネット
    &Battle::Marie_Antoinette,
    // 楊貴妃
    &Battle::Yang_Guifei,
    // 呂布
    &Battle::Lu_Bu,
    // キュリー夫人
    &Battle::Marie_Curie,
    // 孫権
    &Battle::Sun_Quan,
    // カメハメハ大王
    &Battle::Kamehameha_1,
    // カラミティ・ジェーン
    &Battle::Calamity_Jane,
    // ゴッホ
    &Battle::Vincent_van_Gogh,
    // 巴御前
    &Battle::Tomoe_Gozen,
    // 趙雲
    &Battle::Zhao_Yun,
    // 岳飛
    &Battle::Yue_Fei,
    // 武田信玄
    &Battle::Takeda_Shinge,
    // カエサル
    &Battle::Gaius_Iulius_Caesar,
    // 土方歳三
    &Battle::Hijikata_Toshizo,
    // ダーウィン
    &Battle::Charles_Darwin,
    // ヤマトタケル
    &Battle::Yamato_Takeru,

    // Legendary
    // 織田信長
    &Battle::Nobunaga_Oda,
    // ナポレオン・ボナパルト
    &Battle::Napoleon_Bonaparte,
    // 曹操
    &Battle::Cao_Cao,
    // ジョージ・ワシントン
    &Battle::George_Washington,
    // レオナルド・ダ・ビンチ
    &Battle::Leonardo_da_Vinci,
    // アーサー王
    &Battle::King_Arthur,
    // ジャンヌ・ダルク
    &Battle::Joan_of_Arc,
    // 坂本龍馬
    &Battle::Ryoma_Sakamoto,
    // 劉備
    &Battle::Liu_Bei,
    // アインシュタイン
    &Battle::Albert_Einstein,
    // 卑弥呼
    &Battle::Himiko,
    // バッハ
    &Battle::Johann_Sebastian_Bach,
    // チンギス・ハン
    &Battle::Genghis_Khan,
    // カール大帝
    &Battle::Charles_the_Great,
    // 諸葛亮
    &Battle::Zhuge_Liang,
    // クレオパトラ
    &Battle::Cleopatra,


};

bool Battle::passive_skill( ID id, Position p )
{
    int index = convertIDToHeroIndex( id );
    return (this->*functionPointerTablePassive[index])( p );
}




bool Battle::dummy_passive( Position p ) { return true; }

// Novice
// MCHウォーリアー
bool Battle::MCH_Warrior( Position p ) {
    bool use = usePassiveHPLessThan( p, 50, 100 );
    if ( use ) {
        damageSkill( p, FrontEnemy, 120, PHY, NOT_ACTIVE_DAMAGE );
    }
    return use;
}
// MCHタクティシャン
bool Battle::MCH_Tactician( Position p ) {
    bool use = usePassiveHPLessThan( p, 50, 100 );
    if ( use ) {
        damageSkill( p, FrontEnemy, 120, INT, NOT_ACTIVE_DAMAGE );
    }
    return use;
}
// MCHアーティスト
bool Battle::MCH_Artist( Position p ) {
    bool use = usePassiveDying( p, 50 );
    if ( use ) {
        healSkill( p, AllAlly, 70 );
    }
    return use;
}
// 福沢諭吉
bool Battle::Fukuzawa_Yukichi( Position p ) {
    bool use = usePassiveDying( p, 100 );
    if ( use ) {
        changeAttrSkill( p, AllAlly, INT, INT, 20, BUFF );
    }
    return use;
}
// 孫尚香
bool Battle::Sun_Shangxiang( Position p ) {
    bool use = usePassiveDamaged( p, 100 );
    if ( use ) {
        damageSkill( p, FrontEnemy, 15, PHY, NOT_ACTIVE_DAMAGE );
    }
    return use;
}

// パスカル
bool Battle::Blaise_Pascal( Position p ) {
    bool use = usePassiveHPLessThan( p, 70, 100 );
    if ( use ) {

        changeAttrSkill( p, AllAlly, INT, INT, 10, BUFF );
        healSkill( p, AllAlly, 10 );
    }
    return use;
}
// ダビデ
bool Battle::David( Position p ) {
    bool use = usePassiveInActiveByChance( p, 25 );
    if ( use ) {
        damageSkill( p, FrontEnemy, 30, PHY, NOT_ACTIVE_DAMAGE );
    }
    return use;
}
// 雷電為右衛門
bool Battle::Raniden_Tameemon( Position p ) {
    bool use = usePassiveInBattleStart( p, 100 );
    if ( use ) {
        changeAttrSkill( p, OneSelf, PHY, PHY, 30, BUFF );
    }
    return use;
}



// Uncommon
// ライト兄弟
bool Battle::Wright_Brothers( Position p ) {
    bool use = usePassiveInBattleStart( p, 100 );
    if ( use ) {
        changeAttrSkill( p, AllAlly, AGI, INT, 10, BUFF );
    }
    return use;
}

// スパルタクス
bool Battle::Spartacus( Position p ) {
	bool use = usePassiveHPLessThan( p, 20, 100 );
	if ( use ) {
        changeAttrSkill( p, AllEnemy, INT, INT, 10, DEBUFF );
    }
     return use;
}
// ジャック・ザ・リッパー
bool Battle::Jack_the_Ripper( Position p ) {
	bool use = usePassiveInActiveByChance( p, 100 );
	if ( use ) {
        damageSkill( p, Random, 10, 30, PHY, NOT_ACTIVE_DAMAGE );
        changeAttrSkill( p, OneSelf, AGI, AGI, 5, BUFF );
    }
     return use;
}
// シューベルト
bool Battle::Franza_Schubert( Position p ) {
	bool use = usePassiveDying( p, 100 );
	if ( use ) {
        statusAilmentSkill( p, AllEnemy, Sleep );
    }
     return use;
}
// グリム兄弟
bool Battle::Brothers_Grimm( Position p ) {
	bool use = usePassiveDamaged( p, 100 );
	if ( use ) {
        healSkill( p, OneSelf, 10 );
        statusAilmentSkill( p, FrontEnemy, Confusion );
    }
     return use;
}
// アルキメデス
bool Battle::Archimedes( Position p ) {
	bool use = usePassiveInActiveByChance( p, 50 );
	if ( use ) {
        changeAttrSkill( p, OneSelf, INT, INT, 10, BUFF );
        statusAilmentSkill( p, OneSelf, Confusion );
    }
     return use;
}
// サンタクロース
bool Battle::Santa_Claus( Position p ) {
	bool use = usePassiveInActiveByChance( p, 12 );      
	if ( use ) {
        healSkill( p, Random, 12.25 );
    }
     return use;
}
// シュレディンガー
bool Battle::Erwin_Schrodinger( Position p ) {
	bool use = usePassiveDying( p, 50 );
	if ( use ) {
        comeBack( p, 30 );
        changeAttrSkill( p, OneSelf, INT, INT, 20, BUFF );
    }
     return use;
}
// 森蘭丸
bool Battle::Mori_Ranmaru( Position p ) {
	bool use = usePassiveInActiveByChance( p, 50 );
	if ( use ) {
        changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 10, DEBUFF );
        changeAttrSkill( p, FrontAlly, INT, INT, 10, DEBUFF );
    }
     return use;
}
// カフカ
bool Battle::Franz_Kafka( Position p ) {
	bool use = usePassiveInBattleStart( p, 100 );
	if ( use ) {
        healSkill( p, AllAlly, 30 );
        changeAttrSkill( p, AllAlly, AGI, AGI, 5, BUFF );
    }
     return use;
}
// 孫子
bool Battle::Sun_Tzu( Position p ) {
	bool use = usePassiveInBattleStart( p, 100 );
	if ( use ) {
        changeAttrSkill( p, AllHero, AGI, INT, 10, DEBUFF );
    }
     return use;
}
// 石田三成
bool Battle::Ishida_Mitsunari( Position p ) {
	bool use = usePassiveInActiveByChance( p, 40 );
	if ( use ) {
        vector<Attr> va = { PHY, AGI };
        changeAttrSkill( p, FrontAlly, va, PHY, 10, BUFF );
        changeAttrSkill( p, OneSelf, PHY, PHY, 20, DEBUFF );        
    }
     return use;
}
// 許褚
bool Battle::Xu_Chu( Position p ) {
	bool use = usePassiveInActiveByChance( p, 50 ); 
	if ( use ) {
        changeAttrSkill( p, OneSelf, PHY, INT, 30, BUFF );
        changeAttrSkill( p, OneSelf, INT, INT, 25, DEBUFF );
    }
     return use;
}
// 徳川慶喜
bool Battle::Tokugawa_Yoshinobu( Position p ) {
    bool use = usePassiveInActiveByChance( p, 30 );
    if ( use ) {
        vector<Attr> va = { PHY, INT };
        changeAttrSkill( p, AllAlly, va, INT, 15, DEBUFF );
        changeAttrSkill( p, OneSelf, INT, INT, 40, DEBUFF );
    }
    return use;
}
// モンテスキュー
bool Battle::Montesquieu( Position p ) {
    bool use = usePassiveInBattleStart( p, 100 );
    if ( use ) {
        changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 30, DEBUFF );
        Position p_lowest = searchLowestAttrHero( oppositeSide(p.side), INT );
        if ( !isValidPosition( p_lowest ) ) { return true; }
        changeAttrSkill( p_lowest, OneSelf, INT, INT, 30, BUFF );
    }
    return use;
}
// アナスタシア
bool Battle::Anastasia( Position p ) {
    bool use = usePassiveHPLessThan( p, 50, 100 );
    if ( use ) {
        changeAttrSkill( p, AllEnemy, INT, INT, 20, DEBUFF );
        changeAttrSkill( p, AllAlly, PHY, INT, 20, DEBUFF );
    }
    return use;
}
// ジェロニモ
bool Battle::Geronimo( Position p ) {
    bool use = usePassiveDamaged( p, 15 );
    if ( use ) {
        changeAttrSkill( p, FrontEnemy, INT, PHY, 15, DEBUFF );
        changeAttrSkill( p, OneSelf, INT, INT, 15, DEBUFF );
    }
    return use;
}
// 茶々
bool Battle::Lady_Chacha( Position p ) {
    bool use = usePassiveTeamHPLessThan( p, 60, 100 );
    if ( use ) {
        changeAttrSkill( p, AllAlly, PHY, INT, 30, BUFF );
        changeAttrSkill( p, AllAlly, INT, INT, 40, DEBUFF );
    }
    return use;
}


// Rare
// イーサエモン・レッド
bool Battle::Etheremon_Red( Position p ) {
	bool use = usePassiveInActiveByChance( p, 10 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 50, PHY, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// ダルタニャン
bool Battle::Dartagnan( Position p ) {
	bool use = usePassiveInBattleStart( p, 100 );
	if ( use ) {
        vector<Attr> va = { PHY, INT };
        changeAttrSkill( p, AllAlly, va, INT, 10, BUFF );
    }
     return use;
}
// 平賀源内
bool Battle::Gennai_Hiraga( Position p ) {
	bool use = usePassiveHPLessThan( p, 60, 100 );
	if ( use ) {
        damageSkill( p, AllEnemy, 40, INT, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// マタ・ハリ
bool Battle::Mata_Hari( Position p ) {
	bool use = usePassiveInActiveByChance( p, 100 );
	if ( use ) {
        changeAttrSkill( p, FrontEnemy, INT, INT, 10, DEBUFF );
        damageSkill( p, OneSelf, 10, 30, INT, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// イーサエモン・ブルー
bool Battle::Etheremon_Blue( Position p ) {
	bool use = usePassiveInActiveByChance( p, 10 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 50, INT, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// イーサエモン・グリーン
bool Battle::Etheremon_Green( Position p ) {
	bool use = usePassiveInActiveByChance( p, 10 );
	if ( use ) {
        healSkill( p, AllAlly, 30 );
    }
     return use;
}
// 皇帝ネロ
bool Battle::Emperor_Nero( Position p ) {
	bool use = usePassiveInActiveByChance( p, 100 );
	if ( use ) {
        changeAttrSkill( p, Random, PHY, INT, 10, DEBUFF );
        changeAttrSkill( p, Random, INT, INT, 19, 28, BUFF );
    }
     return use;
}
// ノストラダムス
bool Battle::Michel_Nostradamus( Position p ) {
	bool use = usePassiveHPLessThan( p, 50, 100 );
	if ( use ) {
        statusAilmentSkill( p, AllEnemy, Confusion );
    }
     return use;
}
// 太公望
bool Battle::Jiang_Ziya( Position p ) {
	bool use = usePassiveHPLessThan( p, 50, 100 );
	if ( use ) {
        changeAttrSkill( p, AllAlly, INT, INT, 30, BUFF );
    }
     return use;
}
// 服部半蔵
bool Battle::Hanzo_Hattroi( Position p ) {
	bool use = usePassiveTeamHPLessThan( p, 70, 100 );
	if ( use ) {
        healSkill( p, AllAlly, 100 );
    }
     return use;
}
// 前田慶次
bool Battle::Keiji_Maeda( Position p ) {
	bool use = usePassiveInActiveByChance( p, 50 );
	if ( use ) {
        changeAttrSkill( p, FrontEnemy, INT, INT, 10, DEBUFF );
        changeAttrSkill( p, FrontEnemy, PHY, INT, 10, BUFF );
    }
     return use;
}
// 天草四郎
bool Battle::Amakusa_Shiro( Position p ) {
	bool use = usePassiveTeamHPLessThan( p, 60, 100 );
	if ( use ) {
        changeAttrSkill( p, AllAlly, PHY, INT, 20, BUFF );
    }
     return use;
}
// 石川五右衛門
bool Battle::Goemon_Ishikawa( Position p ) {
	bool use = usePassiveDying( p, 100 );
	if ( use ) {
        comeBack( p, 30 );
        damageSkill( p, AllEnemy, 20, PHY, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// 直江兼続
bool Battle::Naoe_Kanetsugu( Position p ) {
	bool use = usePassiveInActiveByChance( p, 50 );
	if ( use ) {
        statusAilmentSkill( p, FrontEnemy, Confusion );
    }
     return use;
}
// イワン雷帝
bool Battle::Ivan_the_Terrible( Position p ) {
	bool use = usePassiveTeamHPLessThan( p, 70, 100 );
	if ( use ) {
        damageSkill( p, AllAlly, 15, INT, NOT_ACTIVE_DAMAGE );
        vector<Attr> va = { PHY, INT };
        changeAttrSkill( p, AllAlly, va, INT, 20, BUFF );
    }
     return use;
}
// 松尾芭蕉
bool Battle::Matsuo_Basho( Position p ) {
	bool use = usePassiveInActiveByChance( p, 100 );
	if ( use ) {
        changeAttrSkill( p, OneSelf, AGI, AGI, 3, BUFF );
        changeAttrSkill( p, FrontAlly, AGI, AGI, 3, BUFF );
    }
     return use;
}
// 三蔵法師
bool Battle::Xuanzang( Position p ) {
	bool use = usePassiveInActiveByChance( p, 15 );
	if ( use ) {
        changeAttrSkill( p, AllAlly, INT, INT, 3, BUFF );
    }
     return use;
}
// 武蔵坊弁慶
bool Battle::Benkei( Position p ) {
	bool use = usePassiveDying( p, 100 );
	if ( use ) {
        comeBack( p, 100 );
        changeAttrSkill( p, OneSelf, PHY, PHY, 100, DEBUFF );
    }
     return use;
}
// 黄忠
bool Battle::Huang_Zhong( Position p ) {
	bool use = usePassiveInActiveByChance( p, 50 );
	if ( use ) {
        changeAttrSkill( p, PHY, HIGH, ENEMY, PHY, PHY, 15, DEBUFF );
    }
     return use;
}
// 貂蝉
bool Battle::Diao_Chan( Position p ) {
	bool use = usePassiveInBattleStart( p, 100 );
	if ( use ) {
        vector<Attr> va = { PHY, INT };
        changeAttrSkill( p, AllEnemy, va, INT, 10, DEBUFF );
    }
     return use;
}
// ヴァレンティヌス
bool Battle::Saint_Valentine( Position p ) {
	bool use = usePassiveInActiveByChance( p, 100 );
	if ( use ) {
        healSkill( p, FrontAlly, 10 );
        healSkill( p, HP, LOW, ALLY, 10 );
        damageSkill( p, OneSelf, 10, INT, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// ポカホンタス
bool Battle::Pocahontas( Position p ) {
	bool use = usePassiveInActiveByChance( p, 20 );
	if ( use ) {
        healSkill( p, FrontEnemy, 15 );
        changeAttrSkill( p, AllEnemy, AGI, INT, 15, DEBUFF );
    }
    return use;
}
// 孫堅
bool Battle::Sun_Jian( Position p ) {
    bool use = usePassiveTeamHPLessThan( p, 70, 100 );
	if ( use ) {
        damageSkill( p, OneSelf, 50, PHY, NOT_ACTIVE_DAMAGE );
        vector<Attr> va = { PHY, AGI };
        changeAttrSkill( p, AllAlly, va, PHY, 15, BUFF );
    }
    return use;
}
// ルーベンス
bool Battle::Peter_Paul_Rubens( Position p ) {
    bool use = usePassiveInActiveByChance( p, 25 );
	if ( use ) {
        for ( Order o = Front; o < Order_End; o++ ) {
            Position p_temp = { p.side, o };
            if ( !isDead( p_temp ) ) { changeAttrSkill( p_temp, OneSelf, AGI, AGI, 10, DEBUFF ); }
        }
        changeAttrSkill( p, OneSelf, AGI, AGI, 20, BUFF );
    }
    return use;
}
// 真田幸村
bool Battle::Sanada_Yukimura( Position p ) {
    bool use = usePassiveTeamHPLessThan( p, 80, 100 );
    if ( use ) {
        vector<Attr> va = { PHY, INT };
        changeAttrSkill( p, FrontEnemy, va, PHY, 60, DEBUFF );
        changeAttrSkill( p, OneSelf, AGI, AGI, 100, DEBUFF );
    }
    return use;
}
// ロビンフッド
bool Battle::Robin_Hood( Position p ) {
    bool use = usePassiveInActiveByChance( p, 30 );
    if ( use ) {
        damageSkill( p, HP, HIGH, ENEMY, 20, INT, NOT_ACTIVE_DAMAGE );
        healSkill( p, HP, LOW, ALLY, 20 );
    }
    return use;
}
// 楊端和
bool Battle::Yang_Duan_He( Position p ) {
    bool use = usePassiveTeamHPLessThan( p, 60, 100 );
    if ( use ) {
        changeAttrSkill( p, AllAlly, AGI, PHY, 20, BUFF );
    }
    return use;
}

//Epic
// 張飛
bool Battle::Zhang_Fei( Position p ) {
	bool use = usePassiveDying( p, 100 );
	if ( use ) {
        comeBack( p, 50 );
    }
     return use;
}
// ナイチンゲール
bool Battle::Florence_Nightingale( Position p ) {
	bool use = usePassiveInActiveByChance( p, 20 );
	if ( use ) {
        healSkill( p, AllAlly, 100 );
    }
     return use;
}
// ベートーヴェン
bool Battle::Ludwig_van_Beethoven( Position p ) {
	bool use = usePassiveHPLessThan( p, 50, 100 );
	if ( use ) {
        vector<Attr> va = { PHY, INT, AGI };
        changeAttrSkill( p, AllEnemy, va, INT, 25, DEBUFF );
    }
     return use;
}
// 佐々木小次郎
bool Battle::Kojiro_Sasaki( Position p ) {
	bool use = usePassiveInActiveByChance( p, 100 );
	if ( use ) {
        changeAttrSkill( p, OneSelf, AGI, AGI, 10, BUFF );
    }
     return use;
}
// 勝海舟
bool Battle::Kaishu_Katsu( Position p ) {
	bool use = usePassiveInActiveByChance( p, 15 );
	if ( use ) {
        vector<Attr> va = { PHY, INT };
        changeAttrSkill( p, AllAlly, va, INT, 30, BUFF );
    }
     return use;
}
// ビリー・ザ・キッド
bool Battle::Billy_the_Kid( Position p ) {
	bool use = usePassiveDamaged( p, 100 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 30, INT, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// トーマス・エジソン
bool Battle::Thomas_Edison( Position p ) {
	bool use = usePassiveInActiveByChance( p, 20 );
	if ( use ) {
        changeAttrSkill( p, AllAlly, INT, INT, 30, BUFF );
    }
     return use;
}
// マルコ・ポーロ
bool Battle::Marco_Polo( Position p ) {
	bool use = usePassiveDying( p, 100 );
	if ( use ) {
        healSkill( p, AllAlly, 70 );
        comeBack( p, 5 );
    }
     return use;
}
// 伊達政宗
bool Battle::Masamune_Date( Position p ) {
	bool use = usePassiveInActiveByChance( p, 20 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 140, INT, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// 王キ
bool Battle::Wang_Ki( Position p ) {
	bool use = usePassiveDying( p, 100 );
	if ( use ) {
        changeAttrSkill( p, FrontAlly, PHY, PHY, 50, BUFF );
    }
     return use;
}
// マルクス
bool Battle::Karl_Marx( Position p ) {
	bool use = usePassiveDying( p, 100 );
	if ( use ) {
        changeAttrSkill( p, AllAlly, INT, INT, 20, BUFF );
    }
     return use;
}
// 沖田総司
bool Battle::Soji_Okita( Position p ) {
	bool use = usePassiveHPLessThan( p, 50, 100 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 50, PHY, NOT_ACTIVE_DAMAGE );
        damageSkill( p, FrontEnemy, 50, PHY, NOT_ACTIVE_DAMAGE );
        damageSkill( p, FrontEnemy, 50, PHY, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// チャイコフスキー
bool Battle::Pyotr_Tchaikovsky( Position p ) {
	bool use = usePassiveDying( p, 100 );
	if ( use ) {
        comeBack( p, 20 );
        changeAttrSkill( p, OneSelf, AGI, AGI, 30, BUFF );
    }
     return use;
}
// マリー・アントワネット
bool Battle::Marie_Antoinette( Position p ) {
	bool use = usePassiveInActiveByChance( p, 30 );
	if ( use ) {
        damageSkill( p, AllEnemy, 20, INT, NOT_ACTIVE_DAMAGE );
        statusAilmentSkill( p, OneSelf, Poison );
    }
     return use;
}
// 楊貴妃
bool Battle::Yang_Guifei( Position p ) {
	bool use = usePassiveInActiveByChance( p, 30 );
	if ( use ) {
        changeAttrSkill( p, AllHero, INT, INT, 5, DEBUFF );
    }
     return use;
}
// 呂布
bool Battle::Lu_Bu( Position p ) {
	bool use = usePassiveInBattleStart( p, 100 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 60, PHY, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// キュリー夫人
bool Battle::Marie_Curie( Position p ) {
	bool use = usePassiveInActiveByChance( p, 30 );
	if ( use ) {
        healSkill( p, AllAlly, 20 );
        damageSkill( p, OneSelf, 10, INT, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// 孫権
bool Battle::Sun_Quan( Position p ) {
	bool use = usePassiveTeamHPLessThan( p, 50, 100 );
	if ( use ) {
        changeAttrSkill( p, OneSelf, PHY, PHY, 30, BUFF );
        changeAttrSkill( p, OneSelf, INT, INT, 30, BUFF );
        changeAttrSkill( p, OneSelf, AGI, AGI, 30, BUFF );
    }
     return use;
}
// カメハメハ大王
bool Battle::Kamehameha_1( Position p ) {
	bool use = usePassiveDamaged( p, 100 );
	if ( use ) {
        int damage = getDamaged( p );
        healSkillException( p, OneSelf, damage, 20 );
    }
     return use;
}
// カラミティ・ジェーン
bool Battle::Calamity_Jane( Position p ) {
	bool use = usePassiveInActiveByChance( p, 30 );
	if ( use ) {
        changeAttrSkill( p, INT, HIGH, ENEMY, INT, INT, 10, DEBUFF );
    }
     return use;
}
// ゴッホ
bool Battle::Vincent_van_Gogh( Position p ) {
	bool use = usePassiveInActiveByChance( p, 30 );
	if ( use ) {
            changeAttrSkill( p, AllAlly, INT, INT, 30, BUFF );
            statusAilmentSkill( p, OneSelf, Confusion );
    }
     return use;
}
// 巴御前
bool Battle::Tomoe_Gozen( Position p ) {
	bool use = usePassiveHPLessThan( p, 30, 100 );
	if ( use ) {
        damageSkill( p, INT, HIGH, ENEMY, 160, PHY, NOT_ACTIVE_DAMAGE );
        damageSkill( p, OneSelf, 160, PHY, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// 趙雲
bool Battle::Zhao_Yun( Position p ) {
	bool use = usePassiveHPLessThan( p ,50, 100 );
	if ( use ) {
        int hp_max = getInitAttr( p, HP );
        healSkillException( p, OneSelf, hp_max, 30 );
        changeAttrSkill( p, OneSelf, AGI, AGI, 20, BUFF );
    }
     return use;
}
// 岳飛
bool Battle::Yue_Fei( Position p ) {
	bool use = usePassiveTeamHPLessThan( p, 70, 100 );
	if ( use ) {
        vector<Attr> va = { PHY, INT, AGI };
        changeAttrSkill( p, AllAlly, va, INT, 10, BUFF );
    }
     return use;
}
// 武田信玄
bool Battle::Takeda_Shinge( Position p ) {
	bool use = usePassiveHPLessThan( p, 40, 100 );
	if ( use ) {
        int hp_max = getInitAttr( p, HP );
        vector<Attr> va = { PHY, AGI };
        changeAttrSkill( p, AllAlly, va, hp_max, 10, 25, BUFF );
    }
    return use;
}
// カエサル
bool Battle::Gaius_Iulius_Caesar( Position p ) {
    bool use = usePassiveHPLessThan( p, 40, 100 );
	if ( use ) {
        changeAttrSkill( p, AllEnemy, INT, PHY, 15, DEBUFF );
        changeAttrSkill( p, AllAlly, PHY, PHY, 10, 20, BUFF );
    }
    return use;
}
// 土方歳三
bool Battle::Hijikata_Toshizo( Position p ) {
    bool use = usePassiveInActiveByChance( p, 40 );
	if ( use ) {
        changeAttrSkill( p, FrontEnemy, AGI, PHY, 10, DEBUFF );
        changeAttrSkill( p, HP, LOW, ALLY, PHY, PHY, 10, BUFF );
    }
    return use;
}
// ダーウィン
bool Battle::Charles_Darwin( Position p ) {
    bool use = usePassiveInActiveByChance( p, 50 );
    if ( use ) {
        Position p_target = searchFrontHero( oppositeSide(p.side) );
        int buff = calcBuff( p_target, PHY );
        changeAttrSkill( p, FrontEnemy, PHY, buff, 30, DEBUFF );
        buff = calcBuff( p_target, AGI );
        changeAttrSkill( p, FrontEnemy, AGI, buff, 30, DEBUFF );
    }
    return use;
}
// ヤマトタケル
bool Battle::Yamato_Takeru( Position p ) {
    bool use = usePassiveDamaged( p, 25 );
    if ( use ) {
        for ( Attr a = PHY; a <= AGI; a++ ) {
            int debuff = calcDebuff( p, a );
            if ( debuff == 0 ) { continue; }
            changeAttrSkill( p, OneSelf, a, debuff, 150, BUFF );
        }
    }
    return use;
}


// Legendary
// 織田信長
bool Battle::Nobunaga_Oda( Position p ) {
	bool use = usePassiveInActiveByChance( p, 25 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 150, PHY, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// ナポレオン・ボナパルト
bool Battle::Napoleon_Bonaparte( Position p ) {
	bool use = usePassiveInActiveByChance( p, 25 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 150, INT, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// 曹操
bool Battle::Cao_Cao( Position p ) {
	bool use = usePassiveInActiveByChance( p, 100 );
	if ( use ) {
        int phy = getBattleAttr( p, PHY );
        healSkillException( p, OneSelf, phy, 30 );
    }
     return use;
}
// ジョージ・ワシントン
bool Battle::George_Washington( Position p ) {
	bool use = usePassiveInActiveByChance( p, 20 );
	if ( use ) {
        vector<Attr> va = { INT, AGI };
        changeAttrSkill( p, AllAlly, va, INT, 30, BUFF );
    }
     return use;
}
// レオナルド・ダ・ビンチ
bool Battle::Leonardo_da_Vinci( Position p ) {
	bool use = usePassiveHPLessThan( p, 60, 100 );
	if ( use ) {
        damageSkill( p, AllEnemy, 80, INT, NOT_ACTIVE_DAMAGE );
    }
     return use;
}
// アーサー王
bool Battle::King_Arthur( Position p ) {
	bool use = usePassiveInActiveByChance( p, 40 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 30, PHY, NOT_ACTIVE_DAMAGE );
        healSkill( p, OneSelf, 20 );
    }
     return use;
}
// ジャンヌ・ダルク
bool Battle::Joan_of_Arc( Position p ) {
	bool use = usePassiveDamaged( p, 100 );
	if ( use ) {
        changeAttrSkill( p, AllAlly, PHY, INT, 10, BUFF );
    }
     return use;
}
// 坂本龍馬
bool Battle::Ryoma_Sakamoto( Position p ) {
	bool use = usePassiveInActiveByChance( p, 40 );
	if ( use ) {
        healSkill( p, AllAlly, 30 );
        changeAttrSkill( p, AllAlly, INT, INT, 10, BUFF );
    }
     return use;
}
// 劉備
bool Battle::Liu_Bei( Position p ) {
	bool use = usePassiveInActiveByChance( p, 40 );
	if ( use ) {
        vector<Attr> va = { PHY, INT };
        changeAttrSkill( p, HP, LOW, ALLY, va, INT, 20, BUFF );
        healSkill( p, HP, LOW, ALLY, 20 );
    }
     return use;
}
// アインシュタイン
bool Battle::Albert_Einstein( Position p ) {
	bool use = usePassiveInActiveByChance( p, 40 );
	if ( use ) {
        vector<Attr> va = { PHY, AGI };
        changeAttrSkill( p, AllAlly, va, INT, 30, BUFF );
    }
     return use;
}
// 卑弥呼
bool Battle::Himiko( Position p ) {
	bool use = usePassiveInBattleStart( p, 100 );
	if ( use ) {
        changeAttrSkill( p, AllHero, INT, INT, 50, DEBUFF );    
    }
     return use;
}
// バッハ
bool Battle::Johann_Sebastian_Bach( Position p ) {
	bool use = usePassiveInActiveByChance( p, 30 );
	if ( use ) {
        vector<Attr> va = { PHY, INT, AGI };
        changeAttrSkill( p, AllAlly, va, INT, 10, BUFF );
    }
     return use;
}
// チンギス・ハン
bool Battle::Genghis_Khan( Position p ) {
	bool use = usePassiveDamaged( p, 100 );
	if ( use ) {
        damageSkill( p, FrontEnemy, 40, PHY, NOT_ACTIVE_DAMAGE );
    }
    return use;
}
// カール大帝
bool Battle::Charles_the_Great( Position p ) {
    bool use = usePassiveInActiveByChance( p, 25 );
	if ( use ) {
        changeAttrSkill( p, OneSelf, INT, INT, 30, BUFF );
        Position p_highest = searchHighestAttrHero( oppositeSide(p.side), INT );
        if ( !isValidPosition(p_highest) ) { return true; }
        changeAttrSkill( p_highest, OneSelf, INT, INT, 30, DEBUFF );
    }
    return use;
}
// 諸葛亮
bool Battle::Zhuge_Liang( Position p ) {
    bool use = usePassiveDying( p, 100 );
	if ( use ) {
        for ( Order o = Front; o < Order_End; o++ ) {
            Attr a[3] = { PHY, INT, AGI };
            Position p_temp = { oppositeSide(p.side), o };
            if ( !isDead( p_temp ) ) {
                for ( int i = 0; i < 3; i++ ) {
                    Hero* hero = &heroes[p_temp.side][p_temp.order];
                    int value = hero->attr_battle[a[i]] - hero->getInitAttr(a[i]);
                    if ( value <= 0 ) { continue; }
                    changeAttrSkill( p_temp, OneSelf, a[i], value, 100, DEBUFF );
                }
            }
        }
    }
    return use;
}
// クレオパトラ
bool Battle::Cleopatra( Position p ) {
    bool use = usePassiveDamaged( p, 100 );
	if ( use ) {
        int value = heroes[p.side][p.order].damaged;
        changeAttrSkill( p, FrontEnemy, AGI, value, 25, DEBUFF );
    }
    return use;
}

