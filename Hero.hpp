#ifndef HERO_HPP
#define HERO_HPP

#include "common.hpp"


class Hero {

    private:
    ID id;
    /*
    Legendary 5xxxx
    Epic      4xxxx
    Rare      3xxxx
    Uncommon  2xxxx
    Novice    1xxxx
    */

    Side side;
    Order order;

    // 初期能力値
    int attr_init[ATTR_END];

    ACTIVE_SKILL_ID active_skill_id[3];
    ACTION_STAGE action_stage = 0; // アクティブスキル発動後にインクリメント 0~2
    
    public:
    Hero();
    Hero( ID i, Side s, Order o, int attr[], ACTIVE_SKILL_ID active_skill_index[] );

    void set( ID i, Side s, Order o, int attr[], ACTIVE_SKILL_ID active_skill_index[] );
    
    // バトル中の能力値
    int attr_battle[ATTR_END];

    ACTION_VALUE action_value = 0; // 行動値

    Status status = Normal; // 混乱、睡眠、毒などの状態

    // このヒーローがパッシブ条件１（main.cppのメモ参照）を満たしたら true
    // パッシブスキル発動フェイズが終わったら false に戻す
    bool passed_passive_1 = false;
    int n_passed_passive_1 = 0; // このヒーローがパッシブ条件１（main.cppのメモ参照）を満たした回数
    // パッシブ条件１と２をクリアしたフラグ（main.cppのメモ参照）
    bool passed_passive12 = false;

    int damaged = 0; // あるアクティブスキルによってこのヒーローが受けたダメージ量





    ID getID();
    int getInitAttr( Attr a );
    vector<ACTIVE_SKILL_ID> getActiveSkillIDAll();

    ACTIVE_SKILL_ID getActiveSkillID();

    // すべての能力値、ステータスなどを初期状態に戻す
    void reset();




    // todo
    // バトルの統計情報
    /*
    int attack_damage[2][3]; // このヒーローが与えたダメージの合計



    int poison_damage; // 毒によって受けたダメージの合計
    int confusion_damage[2][3]; // 混乱によってこのヒーローが与えたダメージの合計
    int sleep_turn; // 睡眠によってActive時に何もしなかった回数
    */



};




#endif