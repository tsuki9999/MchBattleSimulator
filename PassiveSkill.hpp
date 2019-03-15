#ifndef PASSIVESKILL_HPP
#define PASSIVESKILL_HPP

#include "Battle.hpp"


class PassiveSkill {

    private:
    
    /*
    Legendary 5xxxx
    Epic      4xxxx
    Rare      3xxxx
    Uncommon  2xxxx
    Novice    1xxxx
    */
    
    public:

    PassiveSkill() {}

    bool dummy( Battle* b, Position p ); // functionPointerTable の index が 0 のときはエラーにする　そのためのダミー

    // パッシブスキルが発動したら true, しなければ false を返す
    // 引数の Position は Passive Skill を 発動するヒーローの Position

    // Novice
    // MCHウォーリアー
    bool MCH_Warrior( Battle* b, Position p );
    // MCHタクティシャン
    bool MCH_Tactician( Battle* b, Position p );
    // MCHアーティスト
    bool MCH_Artist( Battle* b, Position p );
    // 福沢諭吉
    bool Fukuzawa_Yukichi( Battle* b, Position p );
    // 孫尚香
    bool Sun_Shangxiang( Battle* b, Position p );
    // パスカル
    bool Blaise_Pascal( Battle* b, Position p );
    // ダビデ
    bool David( Battle* b, Position p );
    
    // Uncommon
    // ライト兄弟
    bool Wright_Brothers( Battle* b, Position p );
    // スパルタクス
    bool Spartacus( Battle* b, Position p );
    // ジャック・ザ・リッパー
    bool Jack_the_Ripper( Battle* b, Position p );
    // シューベルト
    bool Franza_Schubert( Battle* b, Position p );
    // グリム兄弟
    bool Brothers_Grimm( Battle* b, Position p );
    // アルキメデス
    bool Archimedes( Battle* b, Position p );
    // サンタクロース
    bool Santa_Claus( Battle* b, Position p );
    // シュレディンガー
    bool Erwin_Schrodinger( Battle* b, Position p );
    // 森蘭丸
    bool Mori_Ranmaru( Battle* b, Position p );
    // カフカ
    bool Franz_Kafka( Battle* b, Position p );
    // 孫子
    bool Sun_Tzu( Battle* b, Position p );
    // 石田三成
    bool Ishida_Mitsunari( Battle* b, Position p );
    // 許褚
    bool Xu_Chu( Battle* b, Position p );
    // 徳川慶喜
    bool Tokugawa_Yoshinobu( Battle* b, Position p );

    // Rare
    // イーサエモン・レッド
    bool Etheremon_Red( Battle* b, Position p );
    // ダルタニャン
    bool Dartagnan( Battle* b, Position p );
    // 平賀源内
    bool Gennai_Hiraga( Battle* b, Position p );
    // マタ・ハリ
    bool Mata_Hari( Battle* b, Position p );
    // イーサエモン・ブルー
    bool Etheremon_Blue( Battle* b, Position p );
    // イーサエモン・グリーン
    bool Etheremon_Green( Battle* b, Position p );
    // 皇帝ネロ
    bool Emperor_Nero( Battle* b, Position p );
    // ノストラダムス
    bool Michel_Nostradamus( Battle* b, Position p );
    // 太公望
    bool Jiang_Ziya( Battle* b, Position p );
    // 服部半蔵
    bool Hanzo_Hattroi( Battle* b, Position p );
    // 前田慶次
    bool Keiji_Maeda( Battle* b, Position p );
    // 天草四郎
    bool Amakusa_Shiro( Battle* b, Position p );
    // 石川五右衛門
    bool Goemon_Ishikawa( Battle* b, Position p );
    // 直江兼続
    bool Naoe_Kanetsugu( Battle* b, Position p );
    // イワン雷帝
    bool Ivan_the_Terrible( Battle* b, Position p );
    // 松尾芭蕉
    bool Matsuo_Basho( Battle* b, Position p );
    // 三蔵法師
    bool Xuanzang( Battle* b, Position p );
    // 武蔵坊弁慶
    bool Benkei( Battle* b, Position p );
    // 黄忠
    bool Huang_Zhong( Battle* b, Position p );
    // 貂蝉
    bool Diao_Chan( Battle* b, Position p );
    // ヴァレンティヌス
    bool Saint_Valentine( Battle* b, Position p );
    // ポカホンタス
    bool Pocahontas( Battle* b, Position p );
    // 孫堅
    bool Sun_Jian( Battle* b, Position p );

    //Epic
    // 張飛
    bool Zhang_Fei( Battle* b, Position p );
    // ナイチンゲール
    bool Florence_Nightingale( Battle* b, Position p );
    // ベートーヴェン
    bool Ludwig_van_Beethoven( Battle* b, Position p );
    // 佐々木小次郎
    bool Kojiro_Sasaki( Battle* b, Position p );
    // 勝海舟
    bool Kaishu_Katsu( Battle* b, Position p );
    // ビリー・ザ・キッド
    bool Billy_the_Kid( Battle* b, Position p );
    // トーマス・エジソン
    bool Thomas_Edison( Battle* b, Position p );
    // マルコ・ポーロ
    bool Marco_Polo( Battle* b, Position p );
    // 伊達政宗
    bool Masamune_Date( Battle* b, Position p );
    // 王キ
    bool Wang_Ki( Battle* b, Position p );
    // マルクス
    bool Karl_Marx( Battle* b, Position p );
    // 沖田総司
    bool Soji_Okita( Battle* b, Position p );
    // チャイコフスキー
    bool Pyotr_Tchaikovsky( Battle* b, Position p );
    // マリー・アントワネット
    bool Marie_Antoinette( Battle* b, Position p );
    // 楊貴妃
    bool Yang_Guifei( Battle* b, Position p );
    // 呂布
    bool Lu_Bu( Battle* b, Position p );
    // キュリー夫人
    bool Marie_Curie( Battle* b, Position p );
    // 孫権
    bool Sun_Quan( Battle* b, Position p );
    // カメハメハ大王
    bool Kamehameha_1( Battle* b, Position p );
    // カラミティ・ジェーン
    bool Calamity_Jane( Battle* b, Position p );
    // ゴッホ
    bool Vincent_van_Gogh( Battle* b, Position p );
    // 巴御前
    bool Tomoe_Gozen( Battle* b, Position p );
    // 趙雲
    bool Zhao_Yun( Battle* b, Position p );
    // 岳飛
    bool Yue_Fei( Battle* b, Position p );
    // 武田信玄
    bool Takeda_Shinge( Battle* b, Position p );
    // カエサル
    bool Gaius_Iulius_Caesar( Battle* b, Position p );

    // Legendary
    // 織田信長
    bool Nobunaga_Oda( Battle* b, Position p );
    // ナポレオン・ボナパルト
    bool Napoleon_Bonaparte( Battle* b, Position p );
    // 曹操
    bool Cao_Cao( Battle* b, Position p );
    // ジョージ・ワシントン
    bool George_Washington( Battle* b, Position p );
    // レオナルド・ダ・ビンチ
    bool Leonardo_da_Vinci( Battle* b, Position p );
    // アーサー王
    bool King_Arthur( Battle* b, Position p );
    // ジャンヌ・ダルク
    bool Joan_of_Arc( Battle* b, Position p );
    // 坂本龍馬
    bool Ryoma_Sakamoto( Battle* b, Position p );
    // 劉備
    bool Liu_Bei( Battle* b, Position p );
    // アインシュタイン
    bool Albert_Einstein( Battle* b, Position p );
    // 卑弥呼
    bool Himiko( Battle* b, Position p );
    // バッハ
    bool Johann_Sebastian_Bach( Battle* b, Position p );
    // チンギス・ハン
    bool Genghis_Khan( Battle* b, Position p );





    bool execFunc( ID id, Battle* b, Position p );
};



#endif