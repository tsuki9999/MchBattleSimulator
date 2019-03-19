#include "Battle.hpp"


bool Battle::fileOpen() {
    string s;
    ifstream ifs;
    int a = -1;

    for ( int i = 1; i < 1000; i++ ) {
        s = "battle_log_" + to_string(i) + ".txt";
        ifs.open( s );
        if ( !ifs ) {
            a = i;
            ifs.close();
            break;
        }
        else { ifs.close(); }
    }
    if ( a == - 1 ) { return false; }

    // ログ出力用ファイルを開く
    ofs_battle_log.open( s, ios::out );

    return !( ofs_battle_log.fail() );
}

void Battle::fileClose() {
    ofs_battle_log.close(); // ログ出力用ファイルを閉じる 
}

void Battle::startBattle() {

    printHeroes();

    pre_battle = true;
    // バトル開始時に発動するパッシブスキル
    usePassiveSkills();
    pre_battle = false;

    while ( true ) {

        increaseActionValue();

        // アクティブスキル発動フェイズ → パッシブスキル発動フェイズ
        if ( useSkills() ) { break; }
    }

    ofs_battle_log << "Battle End" << endl;
}

// 生存している全ヒーローの行動値を AGI + 100 増加
void Battle::increaseActionValue() {
    
    for ( Side s = Attack; s <= Defence; s++ ) {
    for ( Order o = Front; o <= Back; o++ ) {        
        Position p = { s, o };
        if ( isDead( p ) ) { continue; }

        Hero* hero = &heroes[s][o];
        hero->action_value += hero->attr_battle[AGI] + 100;
    }
    }
}

// アクティブスキル発動フェイズ → パッシブスキル発動フェイズ
// 戦闘が終了したら true そうでなければ false を返す
bool Battle::useSkills() {

    // 行動値が1000を超えたヒーローがActiveSkillを発動
    /* 
    行動順
    行動値が高い順
    行動値が同じなら、
    攻撃側前衛 → 攻撃側中衛 → 攻撃側後衛
    → 防御側前衛 → 防御側中衛 → 防御側後衛
    */


    vector< pair< ACTION_VALUE, Position > > vp;
    
    for ( Side s = Attack; s <= Defence; s++ ) {
    for ( Order o = Front; o <= Back; o++ ) {
        Position pos = { s, o };

        if ( isDead( pos ) ) { continue; } // 死亡

        Hero* hero = &heroes[s][o];

        // 行動値が1000以上なら Position を vector に格納
        if ( hero->action_value >= 1000 ) {
            vp.push_back( make_pair( hero->action_value, pos ) );
        }
    }
    }
    // 行動値が1000以上のヒーローがいなければ return
    if ( vp.empty() ) { return false; }

    sort( vp.begin(), vp.end(), greater< pair< ACTION_VALUE, Position > >() );

    for ( auto& x : vp ) {
    // for ( int i = 0; i < static_cast<int>( vp.size() ); i++ ) {
        // Position p = vp[i].second;

        Position p = x.second;

        Side s = p.side;
        Order o = p.order;

        if ( isDead( p ) ) { continue; }

        Hero* hero = &heroes[s][o];
        hero->action_value = 0;

        // バトルログ出力
        printAction( p );

        // アクティブスキル発動フェイズ
        switch ( hero->status ) {            

            // 通常時
            case Normal: useActiveSkill( p ); break;
            // 毒
            case Poison: useActiveSkill( p ); poisonDamage( p ); break;
            // 混乱
            case Confusion:
                // 混乱が解除されたら
                if ( determineNormalization() ) {
                    hero->status = Normal;
                    useActiveSkill( p );
                }
                // 解除されなかったら
                else {
                    confusionRandomAttack( p );
                }
                break;
            // 睡眠
            case Sleep:
                // 睡眠が解除されたら
                if ( determineNormalization() ) {
                    hero->status = Normal;
                    useActiveSkill( p );
                }
                // 解除されなかったら何もしない
                break;
            default: assert( false ); // ここにきたらエラー   
        }


        printAllHeroInfo();

        n_action++;
        p_active = p;
        
        // 終了条件の優先順位は要検証 todo
        // とりあえず、200アクションに達したらパッシブスキル発動フェイズに入らずに終了することにしておく
        for ( Side s = Attack; s <= Defence; s++ ) {
            if ( isEndGameByDead( s ) ) { return true; }
        }

        if ( n_action >= 200 ) { return true; } // 200アクションで終了

        // パッシブスキル発動フェイズ
        if ( usePassiveSkills() ) { return true; }



    }

    return false;
}


// パッシブスキル発動フェイズ
// 戦闘が終了したら true そうでなければ false を返す
bool Battle::usePassiveSkills() {


    // ヒーロー全員に対して、パッシブスキル発動条件を満たしているか確認

    // あるパッシブスキルが発動したことで、ほかのパッシブスキルの発動条件を満たすことがある
    // 全ヒーローの発動条件を順番にチェックし、一人も発動しなかったらループ終了
    while ( true ) {
        bool is_use = false;
        for ( Side s = Attack; s <= Defence; s++ ) {
        for ( Order o = Front; o <= Back; o++ ) {
            Position p = { s, o };
            if ( usePassiveSkill( p ) ) {
                is_use = true;
                n_action++;
                printAllHeroInfo();
            }
            if ( n_action >= 200 ) { return true; } // 200アクションで終了
            
        }
        }
        if ( !is_use ) { break; }
    }

    

    for ( Side s = Attack; s <= Defence; s++ ) {        
    for ( Order o = Front; o <= Back; o++ ) {
        heroes[s][o].passed_passive_1 = false;
    }
    }

    // アクティブスキルによってダメージを受けたときに立つフラグをリセットする
    resetAllDamaged();

    for ( Side s = Attack; s <= Defence; s++ ) {    
        if ( isEndGameByDead( s ) ) { return true; }
    }

    return false;
}   


bool Battle::isSleepOrCofusion( Status s ) {
    return ( s == Sleep || s == Confusion );
}

bool Battle::isAilment( Status s ) {
    return ( s == Poison || s == Confusion || s == Sleep );
}


// 毒ダメージ
void Battle::poisonDamage( Position p ) {
    int damage = ( heroes[p.side][p.order].getInitAttr(HP) * 5 ) / 100;
    giveDamage( p, damage, false );
}

// p にいるヒーローが混乱時に、ランダムなヒーローに対してPHY100%ダメージ
void Battle::confusionRandomAttack( Position p ) {

    // damageSkill( p, Random, 100, PHY, NOT_ACTIVE_DAMAGE );

    Position p_attacked = randomHero();

    Hero* hero_attack = &heroes[p.side][p.order];
    Hero* hero_attacked = &heroes[p_attacked.side][p_attacked.order];

    int damage = calcDamage( hero_attack->attr_battle[PHY], 100, hero_attacked->attr_battle[PHY] );
    giveDamage( p_attacked, damage, false );

    if ( print_battle_log ) { ofs_battle_log << "混乱によるランダム攻撃 →   ";  }

    printPositionHero( p_attacked );
    printChangeAttributeValue( HP, damage, false );

}

// ある Position のヒーローが死んでいるかどうか
bool Battle::isDead( Position p ) {
    return ( heroes[p.side][p.order].attr_battle[HP] <= 0 );
}

// ある Side のヒーローが全員死んでいるかどうか
bool Battle::isEndGameByDead( Side s ) {
    Position p;
    p.side = s;
    for ( Order o = Front; o <= Back; o++ ) {
        p.order = o;
        if ( !isDead( p ) ) { return false; } // 一人でも生きていたら falase
    }
    return true;
}



void Battle::useActiveSkill( Position p ) {
    ACTIVE_SKILL_ID id = heroes[p.side][p.order].getActiveSkillID();
    active_skill( id, p );
}
bool Battle::usePassiveSkill( Position p ) {
    ID id = heroes[p.side][p.order].getID();
    return passive_skill( id, p );
}





/* ---------------------- 対象のヒーローを探す ---------------------- */


// ある Side の（生存している）すべてのヒーローの Positon を返す
vector<Position> Battle::searchAll( Side s ) {
    vector< Position > ret;
    for ( Order o = Front; o < Order_End; o++ ) {
        Position p = { s, o };
        if ( !isDead( p ) ) { ret.push_back( p ); }
    }
    if ( ret.empty() ) {
        Position p_empty = { Side_End, Order_End };
        ret.push_back( p_empty );
    }
    return ret;
}
// （生存している）敵味方すべてのヒーローの Position を返す
vector<Position> Battle::searchAll() {
    vector< Position > ret;
    for ( Side s = Attack; s < Side_End; s++ ) {
    for ( Order o = Front; o < Order_End; o++ ) {
        Position p = { s, o };
        if ( !isDead( p ) ) { ret.push_back( p ); }
    }
    }

    if ( ret.empty() ) {
        Position p_empty = { Side_End, Order_End };
        ret.push_back( p_empty );
    }

    return ret;
}

// 生存している中で先頭のヒーローを探す
Position Battle::searchFrontHero( Side s ) {
    Position ret;
    ret.side = s;
    for ( Order o = Front; o <= Back; o++ ) {
        ret.order = o;
        if ( !isDead( ret ) ) { return ret; }
    }

    ret.order = Order_End;
    ret.side = Side_End;
    return ret;
}

// ある Side の（生存している中で）最も能力値の高いヒーローを探す
Position Battle::searchHighestAttrHero( Side s, Attr a ) {

    Position ret;

    Order o_highest = Order_End;

    int value_highest = -1;
    for ( Order o = Front; o <= Back; o++ ) {
        Position p = { s, o };
        if ( !isDead( p ) && value_highest < heroes[s][o].attr_battle[a] ) {
            o_highest = o;
            value_highest = heroes[s][o].attr_battle[a];
        }
    }
    if ( value_highest == -1 ) {
        ret.side = Side_End;
        ret.order = Order_End;
        return ret;
    }
    ret.side = s;
    ret.order = o_highest;  
    return ret;
}
// ある Side の（生存している中で）最も能力値の低いヒーローを探す
Position Battle::searchLowestAttrHero( Side s, Attr a ) {

    Position ret;

    Order o_lowest = Order_End;
    int value_lowest = INT_MAX;
    for ( Order o = Front; o <= Back; o++ ) {
        Position p = { s, o };
        if ( !isDead( p ) && value_lowest > heroes[s][o].attr_battle[a] ) {
            o_lowest = o;
            value_lowest = heroes[s][o].attr_battle[a];
        }
    }

    if ( value_lowest == INT_MAX ) {
        ret.side = Side_End;
        ret.order = Order_End;
        return ret;
    }
    ret.side = s;
    ret.order = o_lowest;
    return ret;
}

// （生存している中で）ランダムなヒーローの Position を返す
Position Battle::randomHero() {

    vector<Position> vp;

    for ( Side s = Attack; s <= Defence; s++ ) {
    for ( Order o = Front; o <= Back; o++ ) {
        Position p = { s, o };
        if ( !isDead( p ) ) { vp.push_back( p ); }
    }
    }

    if ( vp.empty() ) {
        Position ret = { Side_End, Order_End };
        return ret;
    }
    else {
        int i = Dice( 0, static_cast<int>(vp.size())-1 );
        return vp[ i ];
    }
}


// Target にあてはまるヒーローの Positon を返す
// 引数の Position はスキルを発動するヒーローのもの
vector<Position> Battle::searchTarget( Position p, Target t ) {
    
    Side s_ally = p.side;
    Side s_enemy = oppositeSide( p.side );

    // スキル効果対象ヒーローの Position をvector<Position> に格納
    vector<Position> target;
    switch( t ) {
        case OneSelf: // 自分自身
            if ( !isDead( p ) ) { target.push_back( p ); }
            else { 
                Position ret = { Side_End, Order_End };
                target.push_back( p );
            }
            break;
        case AllAlly: // 味方すべて
            target = searchAll( s_ally );
            break;
        case AllEnemy: // 敵すべて
            target = searchAll( s_enemy );
            break;
        case AllHero: // 敵味方すべて
            target = searchAll();
            break;
        case FrontAlly: // 味方の先頭
            target.push_back( searchFrontHero( s_ally ) );
            break;
        case FrontEnemy: // 敵の先頭
            target.push_back( searchFrontHero( s_enemy ) );
            break;
        case Random: // 敵味方の中からランダムに１体
            target.push_back( randomHero() );
            break;
        default: assert( false );
    }
    return target;
}


/* -------------------------- ステータス変化 -------------------------- */

// p の位置にいるヒーローの HP を damage 分減らす
void Battle::giveDamage( Position p, int damage, bool is_active ) {
    Hero* hero = &heroes[p.side][p.order];

    assert( !isDead(p) );

    if ( is_active ) { hero->damaged += damage; } // アクティブスキルによって受けたダメージ量に加算

    hero->attr_battle[HP] -= damage;

    // 死亡時に HP 以外の能力値とステータスを初期値に戻す（行動値はそのまま）
    if ( hero->attr_battle[HP] <= 0 ) {
        resetOtherThanHP( p );
        hero->attr_battle[HP] = 0; // HP は０にする
    }
}
// p の位置にいるヒーローの HP を heal 分回復する
void Battle::giveHeal( Position p, int heal ) {
    Hero* hero = &heroes[p.side][p.order];

    hero->attr_battle[HP] += heal;
    hero->attr_battle[HP] = min( hero->attr_battle[HP], hero->getInitAttr(HP) );
}


// p の位置にいるヒーローの 能力値（HP以外） を buff 分増やす
void  Battle::giveBuff( Position p, Attr a, int buff ) {
    heroes[p.side][p.order].attr_battle[a] += buff;
    heroes[p.side][p.order].attr_battle[a] = min( 999, heroes[p.side][p.order].attr_battle[a] );
}
// p の位置にいるヒーローの 能力値（HP以外） を debuff 分減らす
void  Battle::giveDebuff( Position p, Attr a, int debuff ) {
    heroes[p.side][p.order].attr_battle[a] -= debuff;
    heroes[p.side][p.order].attr_battle[a] = max( 1, heroes[p.side][p.order].attr_battle[a] );
}


// p の位置にいるヒーローの HP 以外の能力値とステータスを初期値に戻す（行動値は０にする）
void Battle::resetOtherThanHP( Position p ) {
    Hero* hero = &heroes[p.side][p.order];

    for ( Attr a = PHY; a < ATTR_END; a++ ) {
        hero->attr_battle[a] = hero->getInitAttr(a);
    }
    hero->action_value = 0;

    hero->status = Normal;
}


// p の位置にいるヒーローを（混乱・睡眠・毒）にする
void Battle::giveStatusAilment( Position p, Status s ) {
    heroes[p.side][p.order].status = s;
}


// p の位置にいるヒーローを、 HP が per % の状態で復活させる
void Battle::comeBack( Position p, int per ) {
    Hero* hero = &heroes[p.side][p.order];
    hero->attr_battle[HP] = hero->getInitAttr(HP) * per / 100;
}

/* ---------------------- ダメージを与える ---------------------- */


// p の位置にいるヒーローが、Target に rate% の PHY/INT ダメージを与える
void Battle::damageSkill( Position p, Target t, int rate, Attr a_damage, bool is_active ) {

    assert( a_damage == PHY || a_damage == INT );

    Hero* hero_attack = &heroes[p.side][p.order];

    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    Side s_temp = Side_End;

    
    // スキル効果対象ヒーローに対して、rate% の PHY/INT ダメージを与える
    for ( Position& p_attacked : target ) {
    
        Hero* hero_attacked = &heroes[p_attacked.side][p_attacked.order];

        int damage = calcDamage( hero_attack->attr_battle[a_damage], rate, hero_attacked->attr_battle[a_damage] );
        giveDamage( p_attacked, damage, is_active );

        // ログに出力
        if ( s_temp != p_attacked.side ) {
            printSide( p_attacked.side );
        }
        s_temp = p_attacked.side;

        printOrder( p_attacked.order );
        printHeroName( p_attacked );
        printChangeAttributeValue( HP, damage, false );
    }
}

// p の位置にいるヒーローが、Target に rateA ~ rateB% の PHY/INT ダメージを与える    
void Battle::damageSkill( Position p, Target t, int rateA, int rateB, Attr a_damage, bool is_active ) {

    assert(a_damage == PHY || a_damage == INT );

    Hero* hero_attack = &heroes[p.side][p.order];
    
    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    Side s_temp = Side_End;


    // スキル効果対象ヒーローに対して、rate% の PHY/INT ダメージを与える
    for ( Position& p_attacked : target ) {



        Hero* hero_attacked = &heroes[p_attacked.side][p_attacked.order];

        int rate = Dice( rateA, rateB );

        int damage = calcDamage( hero_attack->attr_battle[a_damage], rate, hero_attacked->attr_battle[a_damage] );
        giveDamage( p_attacked, damage, is_active );

        // ログに出力
        if ( s_temp != p_attacked.side ) {
            printSide( p_attacked.side );
        }
        s_temp = p_attacked.side;

        printOrder( p_attacked.order );
        printHeroName( p_attacked );
        printChangeAttributeValue( HP, damage, false );
    }
}


// p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） に rate% の PHY/INT ダメージを与える
void Battle::damageSkill( Position p, Attr a_target, bool is_high, bool is_ally, int rate, Attr a_damage, bool is_active ) {

    assert(a_damage == PHY || a_damage == INT );

    Hero* hero_attack = &heroes[p.side][p.order];

    // スキル効果対象ヒーローの Side
    Side s_target = is_ally ? p.side : oppositeSide( p.side );
    // スキル効果対象ヒーローの Position
    Position p_attacked = is_high ? searchHighestAttrHero( s_target, a_target ) : searchLowestAttrHero( s_target, a_target );
    if ( p_attacked.side == Side_End && p_attacked.order == Order_End ) { return; }

    Hero* hero_attacked = &heroes[p_attacked.side][p_attacked.order];

    int damage = calcDamage( hero_attack->attr_battle[a_damage], rate, hero_attacked->attr_battle[a_damage] );
    giveDamage( p_attacked, damage, is_active );

    // ログに出力
    printPositionHero( p_attacked );
    printChangeAttributeValue( HP, damage, false );
}

// p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） に rateA ~ rateB% の PHY/INT ダメージを与える
void Battle::damageSkill( Position p, Attr a_target, bool is_high, bool is_ally, int rateA, int rateB, Attr a_damage, bool is_active ) {

    assert(a_damage == PHY || a_damage == INT );

    Hero* hero_attack = &heroes[p.side][p.order];

    // スキル効果対象ヒーローの Side
    Side s_target = is_ally ? p.side : oppositeSide( p.side );
    // スキル効果対象ヒーローの Position
    Position p_attacked = is_high ? searchHighestAttrHero( s_target, a_target ) : searchLowestAttrHero( s_target, a_target );
    if ( p_attacked.side == Side_End && p_attacked.order == Order_End ) { return; }

    Hero* hero_attacked = &heroes[p_attacked.side][p_attacked.order];

    int rate = Dice( rateA, rateB );

    int damage = calcDamage( hero_attack->attr_battle[a_damage], rate, hero_attacked->attr_battle[a_damage] );
    giveDamage( p_attacked, damage, is_active );

    // ログに出力
    printPositionHero( p_attacked );
    printChangeAttributeValue( HP, damage, false );
}

/* ---------------------- バフ、デバフ ---------------------- */


// p の位置にいるヒーローが、Target の a_change に対して、 a_ref の値の rate% の （バフ・デバフ）を与える
void Battle::changeAttrSkill( Position p, Target t, Attr a_change, Attr a_ref, int rate, bool is_buff ) {

    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    // a_ref の値の rate%
    int delta = ( heroes[p.side][p.order].attr_battle[a_ref] * rate ) / 100;    

    Side s_temp = Side_End;
    // スキル効果対象ヒーローに対して、rate% の （バフ・デバフ）を a_change に与える
    for ( Position& p_target : target ) {
        
        // ログに出力
        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        printOrder( p_target.order );
        printHeroName( p_target );
        printChangeAttributeValue( a_change, delta, is_buff );
        // 能力値変化
        is_buff ? giveBuff( p_target, a_change, delta ) : giveDebuff( p_target, a_change, delta );
    }


}
void Battle::changeAttrSkill( Position p, Target t, vector<Attr> a_change, Attr a_ref, int rate, bool is_buff ) {

    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    // a_ref の値の rate%
    int delta = ( heroes[p.side][p.order].attr_battle[a_ref] * rate ) / 100;

    Side s_temp = Side_End;
    // スキル効果対象ヒーローに対して、rate% の （バフ・デバフ）を a_change に与える
    for ( Position& p_target : target ) {
        
        // ログに出力
        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        printOrder( p_target.order );
        printHeroName( p_target );

        for ( Attr& a_target: a_change ) {
            printChangeAttributeValue( a_target, delta, is_buff );
            // 能力値変化
            is_buff ? giveBuff( p_target, a_target, delta ) : giveDebuff( p_target, a_target, delta );
        }
    }

}
// p の位置にいるヒーローが、Target の a_change に対して、 a_ref の値の rateA ~ rateB% の （バフ・デバフ）を与える
void Battle::changeAttrSkill( Position p, Target t, Attr a_change, Attr a_ref, int rateA, int rateB, bool is_buff ) {

    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    // a_ref の値
    int delta = heroes[p.side][p.order].attr_battle[a_ref];

    Side s_temp = Side_End;
    // スキル効果対象ヒーローに対して、rate% の （バフ・デバフ）を a_change に与える
    for ( Position& p_target : target ) {

        int rate = Dice( rateA, rateB );
        delta = delta * rate / 100;

        // ログに出力
        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        printOrder( p_target.order );
        printHeroName( p_target );
        printChangeAttributeValue( a_change, delta, is_buff );

        // 能力値変化
        is_buff ? giveBuff( p_target, a_change, delta ) : giveDebuff( p_target, a_change, delta );
    }

}
void Battle::changeAttrSkill( Position p, Target t, vector<Attr> a_change, Attr a_ref, int rateA, int rateB, bool is_buff ) {

    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    // a_ref の値
    int delta = heroes[p.side][p.order].attr_battle[a_ref];

    Side s_temp = Side_End;
    // スキル効果対象ヒーローに対して、rate% の （バフ・デバフ）を a_change に与える
    for ( Position& p_target : target ) {
        
        // ログに出力
        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        printOrder( p_target.order );
        printHeroName( p_target );

        for ( Attr& ac: a_change ) {

            int rate = Dice( rateA, rateB );
            delta = delta * rate / 100;

            printChangeAttributeValue( ac, delta, is_buff );
            // 能力値変化
            is_buff ? giveBuff( p_target, ac, delta ) : giveDebuff( p_target, ac, delta );
        }
    }
}

// p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） の a_change に対して、 a_ref の値の rate% の （バフ・デバフ）を与える
void Battle::changeAttrSkill( Position p, Attr a_target, bool is_high, bool is_ally, Attr a_change, Attr a_ref, int rate, bool is_buff ) {

    // スキル効果対象ヒーローの Side
    Side s_target = is_ally ? p.side : oppositeSide( p.side );
    // スキル効果対象ヒーローの Position
    Position p_target = is_high ? searchHighestAttrHero( s_target, a_target ) : searchLowestAttrHero( s_target, a_target );
    if ( p_target.side == Side_End && p_target.order == Order_End ) { return; }

    int delta = heroes[p.side][p.order].attr_battle[a_ref] * rate / 100;

    printPositionHero( p_target );
    printChangeAttributeValue( a_change, delta, is_buff );
    is_buff ? giveBuff( p_target, a_change, delta ) : giveDebuff( p_target, a_change, delta );

}
void Battle::changeAttrSkill( Position p, Attr a_target, bool is_high, bool is_ally, vector<Attr> a_change, Attr a_ref, int rate, bool is_buff ) {

    // スキル効果対象ヒーローの Side
    Side s_target = is_ally ? p.side : oppositeSide( p.side );
    // スキル効果対象ヒーローの Position
    Position p_target = is_high ? searchHighestAttrHero( s_target, a_target ) : searchLowestAttrHero( s_target, a_target );
    if ( p_target.side == Side_End && p_target.order == Order_End ) { return; }

    int delta = heroes[p.side][p.order].attr_battle[a_ref] * rate / 100;

    printPositionHero( p_target );
    for ( Attr ac : a_change ) {        
        printChangeAttributeValue( ac, delta, is_buff );
        is_buff ? giveBuff( p_target, ac, delta ) : giveDebuff( p_target, ac, delta );
    }    

}
// p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） の a_change に対して、 a_ref の値の rateA ~ rateB% の （バフ・デバフ）を与える
void Battle::changeAttrSkill( Position p, Attr a_target, bool is_high, bool is_ally, Attr a_change, Attr a_ref, int rateA, int rateB, bool is_buff ) {

    // スキル効果対象ヒーローの Side
    Side s_target = is_ally ? p.side : oppositeSide( p.side );
    // スキル効果対象ヒーローの Position
    Position p_target = is_high ? searchHighestAttrHero( s_target, a_target ) : searchLowestAttrHero( s_target, a_target );
    if ( p_target.side == Side_End && p_target.order == Order_End ) { return; }

    int rate = Dice( rateA, rateB );
    int delta = heroes[p.side][p.order].attr_battle[a_ref] * rate / 100;

    printPositionHero( p_target );
    printChangeAttributeValue( a_change, delta, is_buff );
    is_buff ? giveBuff( p_target, a_change, delta ) : giveDebuff( p_target, a_change, delta );

}
void Battle::changeAttrSkill( Position p, Attr a_target, bool is_high, bool is_ally, vector<Attr> a_change, Attr a_ref, int rateA, int rateB, bool is_buff ) {
    
    // スキル効果対象ヒーローの Side
    Side s_target = is_ally ? p.side : oppositeSide( p.side );
    // スキル効果対象ヒーローの Position
    Position p_target = is_high ? searchHighestAttrHero( s_target, a_target ) : searchLowestAttrHero( s_target, a_target );
    if ( p_target.side == Side_End && p_target.order == Order_End ) { return; }

    int delta = heroes[p.side][p.order].attr_battle[a_ref];

    printPositionHero( p_target );
    for ( Attr ac : a_change ) {

        int rate = Dice( rateA, rateB );
        delta = delta * rate / 100;

        printChangeAttributeValue( ac, delta, is_buff );
        is_buff ? giveBuff( p_target, ac, delta ) : giveDebuff( p_target, ac, delta );
    }    
}

// p の位置にいるヒーローが、Target の a_change に対して value の rate% の （バフ・デバフ）を a_change に与える
void Battle::changeAttrSkill( Position p, Target t, Attr a_change, int value, int rate, bool is_buff ) {

    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    // value の値の rate%
    int delta = value * rate / 100;

    Side s_temp = Side_End;
    // スキル効果対象ヒーローに対して、rate% の （バフ・デバフ）を a_change に与える
    for ( Position& p_target : target ) {
        
        // ログに出力
        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        printOrder( p_target.order );
        printHeroName( p_target );
        printChangeAttributeValue( a_change, delta, is_buff );
        // 能力値変化
        is_buff ? giveBuff( p_target, a_change, delta ) : giveDebuff( p_target, a_change, delta );
    }


}
void Battle::changeAttrSkill( Position p, Target t, vector<Attr> a_change, int value, int rate, bool is_buff ) {

    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    // value の値の rate%
    int delta = value * rate / 100;

    Side s_temp = Side_End;
    // スキル効果対象ヒーローに対して、rate% の （バフ・デバフ）を a_change に与える
    for ( Position& p_target : target ) {
        
        // ログに出力
        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        printOrder( p_target.order );
        printHeroName( p_target );

        for ( Attr& a_target: a_change ) {
            printChangeAttributeValue( a_target, delta, is_buff );
            // 能力値変化
            is_buff ? giveBuff( p_target, a_target, delta ) : giveDebuff( p_target, a_target, delta );
        }
    }

}
void Battle::changeAttrSkill( Position p, Target t, vector<Attr> a_change, int value, int rateA, int rateB, bool is_buff ) {

    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    // value の値の rate%
    int rate = Dice( rateA, rateB );
    int delta = value * rate / 100;

    Side s_temp = Side_End;
    // スキル効果対象ヒーローに対して、rate% の （バフ・デバフ）を a_change に与える
    for ( Position& p_target : target ) {
        
        // ログに出力
        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        printOrder( p_target.order );
        printHeroName( p_target );

        for ( Attr& a_target: a_change ) {
            printChangeAttributeValue( a_target, delta, is_buff );
            // 能力値変化
            is_buff ? giveBuff( p_target, a_target, delta ) : giveDebuff( p_target, a_target, delta );
        }
    }

}





/* ---------------------- 回復効果 ---------------------- */


// p の位置にいるヒーローが、Target に rate% の 回復効果を与える
void Battle::healSkill( Position p, Target t, int rate ) {
    
    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    Side s_temp = Side_End;
    for ( Position& p_target : target ) {
        int heal = calcHeal( heroes[p.side][p.order].attr_battle[INT], heroes[p_target.side][p_target.order].attr_battle[PHY], rate );
        giveHeal( p_target, heal );

        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        // ログに出力
        printOrder( p_target.order );
        printHeroName( p_target );
        printChangeAttributeValue( HP, heal, true );
    }
}

// p の位置にいるヒーローが、Target に rate% の 回復効果を与える
void Battle::healSkill( Position p, Target t, double rate ) {
    
    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    Side s_temp = Side_End;
    for ( Position& p_target : target ) {
        int heal = calcHeal( heroes[p.side][p.order].attr_battle[INT], heroes[p_target.side][p_target.order].attr_battle[PHY], rate );
        giveHeal( p_target, heal );

        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        // ログに出力
        printOrder( p_target.order );
        printHeroName( p_target );
        printChangeAttributeValue( HP, heal, true );
    }
}


// p の位置にいるヒーローが、Target に rateA ~ rateB% の 回復効果を与える
void Battle::healSkill( Position p, Target t, int rateA, int rateB ) {
    
    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    Side s_temp = Side_End;
    for ( Position& p_target : target ) {

        int rate = Dice( rateA, rateB );

        int heal = calcHeal( heroes[p.side][p.order].attr_battle[INT], heroes[p_target.side][p_target.order].attr_battle[PHY], rate );
        giveHeal( p_target, heal );

        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        // ログに出力
        printOrder( p_target.order );
        printHeroName( p_target );
        printChangeAttributeValue( HP, heal, true );
    }

}

// p の位置にいるヒーローが、Target に value の rate% の回復効果を与える
void Battle::healSkillException( Position p, Target t, int value, int rate ) {
    
    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    Side s_temp = Side_End;
    for ( Position& p_target : target ) {
        int heal = calcHeal( value, rate );
        giveHeal( p_target, heal );

        if ( s_temp != p_target.side ) {
            printSide( p_target.side );
        }
        s_temp = p_target.side;

        // ログに出力
        printOrder( p_target.order );
        printHeroName( p_target );
        printChangeAttributeValue( HP, heal, true );
    }
}


// p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） に rate% の 回復効果を与える
void Battle::healSkill( Position p, Attr a_target, bool is_high, bool is_ally, int rate ) {

    // スキル効果対象ヒーローの Side
    Side s_target = is_ally ? p.side : oppositeSide( p.side );
    // スキル効果対象ヒーローの Position
    Position p_target = is_high ? searchHighestAttrHero( s_target, a_target ) : searchLowestAttrHero( s_target, a_target );
    if ( p_target.side == Side_End && p_target.order == Order_End ) { return; }

    int heal = calcHeal( heroes[p.side][p.order].attr_battle[INT], heroes[p_target.side][p_target.order].attr_battle[PHY], rate );
    giveHeal( p_target, heal );

    // ログに出力
    printPositionHero( p_target );
    printChangeAttributeValue( HP, heal, true );

}
// p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） に rateA ~ rateB% の 回復効果を与える
void Battle::healSkill( Position p, Attr a_target, bool is_high, bool is_ally, int rateA, int rateB ) {

    // スキル効果対象ヒーローの Side
    Side s_target = is_ally ? p.side : oppositeSide( p.side );
    // スキル効果対象ヒーローの Position
    Position p_target = is_high ? searchHighestAttrHero( s_target, a_target ) : searchLowestAttrHero( s_target, a_target );
    if ( p_target.side == Side_End && p_target.order == Order_End ) { return; }


    int rate = Dice( rateA, rateB );

    int heal = calcHeal( heroes[p.side][p.order].attr_battle[INT], heroes[p_target.side][p_target.order].attr_battle[PHY], rate );
    giveHeal( p_target, heal );

    // ログに出力
    printPositionHero( p_target );
    printChangeAttributeValue( HP, heal, true );
}


/* ---------------------- 状態異常付与 ---------------------- */

// p の位置にいるヒーローが、Target を （混乱・睡眠・毒）状態にすることがある
void Battle::statusAilmentSkill( Position p, Target t, Status s ) {
    
    vector<Position> target = searchTarget( p, t );
    if ( target[0].side == Side_End && target[0].order == Order_End ) { return; }

    Side s_temp = Side_End;
    for ( Position& p_target : target ) {
        Hero* hero_target = &heroes[p_target.side][p_target.order];

        // 既に状態異常なら continue
        if ( isAilment( hero_target->status ) ) { continue; }

        if ( determineStatusAilment( heroes[p.side][p.order].attr_battle[INT], hero_target->attr_battle[INT] ) ) {
            giveStatusAilment( p_target, s );

            // ログに出力
            if ( s_temp != p_target.side ) {
                printSide( p_target.side );
            }
            s_temp = p_target.side;

            printOrder( p_target.order );
            printHeroName( p_target );
            printStatusAilment( s );
        }
    }

}
// p の位置にいるヒーローが、ある能力値が最も（高い・低い）（敵・味方） を （混乱・睡眠・毒）状態にすることがある
void Battle::statusAilmentSkill( Position p, Attr a_target, bool is_high, bool is_ally, Status s ) {

    // スキル効果対象ヒーローの Side
    Side s_target = is_ally ? p.side : oppositeSide( p.side );
    // スキル効果対象ヒーローの Position
    Position p_target = is_high ? searchHighestAttrHero( s_target, a_target ) : searchLowestAttrHero( s_target, a_target );
    if ( p_target.side == Side_End && p_target.order == Order_End ) { return; }

    Hero* hero_target = &heroes[p_target.side][p_target.order];

    // 既に状態異常なら return
    if ( isAilment( hero_target->status ) ) { return; }

    if ( determineStatusAilment( heroes[p.side][p.order].attr_battle[INT], hero_target->attr_battle[INT] ) ) {
            giveStatusAilment( p_target, s );

            printPositionHero( p_target );
            printStatusAilment( s );
    }
}





/* ---------------------- Passive Skill の発動条件 ---------------------- */


// パッシブ条件１、２、３についてはmain.cppのメモ参照

// アクティブ時、prob% の確率で
bool Battle::usePassiveInActiveByChance( Position p, int prob ) {

    if ( isDead( p ) ) { return false; } // 死亡時には発動しない

    Hero* hero = &heroes[p.side][p.order];

    /* ---------------------- パッシブ条件１ ---------------------- */
    // このパッシブスキル発動フェイズでパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->passed_passive_1 ) { return false; }

    // アクティブ時かどうか確認
    if ( p != p_active ) { return false; }

    hero->n_passed_passive_1++; // パッシブ条件１を満たした回数をインクリメント
    hero->passed_passive_1 = true; // パッシブ条件１を満たした


    /* ---------------------- パッシブ条件２ ---------------------- */
    // 確率で決定
    if ( !determineByDice( prob ) ) { return false; }


    /* ---------------------- パッシブ条件３ ---------------------- */
    // 混乱か睡眠なら発動しない
    if ( isSleepOrCofusion( hero->status ) ) { return false; }


    // ログに出力
    printPassiveSkill( p );

    return true;
}

// バトル開始時、prob% の確率で一度だけ
// バトル開始時に必ず呼ぶ
bool Battle::usePassiveInBattleStart( Position p, int prob ) {

    if ( isDead( p ) ) { return false; } // 死亡時には発動しない
    
    Hero* hero = &heroes[p.side][p.order];
    
    // 条件１と２をクリアしたフラグが立っていたら、条件１と２を飛ばす
    if ( hero->passed_passive12 ) { goto PASSED_PASSIVE_12; }

    /* ---------------------- パッシブ条件１ ---------------------- */
    // このパッシブスキル発動フェイズでパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->passed_passive_1 ) { return false; }    
    // これまでにパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->n_passed_passive_1 > 0 ) { return false; }

    if ( !pre_battle ) { return false; }
    
    hero->passed_passive_1 = true; // パッシブ条件１を満たしたフラグを立てる
    hero->n_passed_passive_1++; // パッシブ条件１を満たした回数をインクリメント

    /* ---------------------- パッシブ条件２ ---------------------- */
    // 確率で決定
    if ( !determineByDice( prob ) ) { return false; }


    PASSED_PASSIVE_12:

    /* ---------------------- パッシブ条件３ ---------------------- */
    // 混乱か睡眠なら発動せず、条件１と２をクリアしたフラグを立てる
    if ( isSleepOrCofusion( hero->status ) ) {
        hero->passed_passive12 = true;
        return false;
    }

    
    hero->passed_passive12 = false; // 一度スキルが発動したらフラグをリセットする

    // ログに出力
    printPassiveSkill( p );

    return true;
}


// Active Skill によるダメージを受けたとき、prob% の確率で
bool Battle::usePassiveDamaged( Position p, int prob ) {

    if ( isDead( p ) ) { return false; } // 死亡時には発動しない

    Hero* hero = &heroes[p.side][p.order];

    // 条件１と２をクリアしたフラグが立っていたら、条件１と２を飛ばす
    if ( hero->passed_passive12 ) { goto PASSED_PASSIVE_12; }

    /* ---------------------- パッシブ条件１ ---------------------- */
    // このパッシブスキル発動フェイズでパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->passed_passive_1 ) { return false; }

    // アクティブスキルによってダメージを受けたかどうか確認
    if ( hero->damaged == 0 ) { return false; }
    
    hero->passed_passive_1 = true; // パッシブ条件１を満たしたフラグを立てる
    hero->n_passed_passive_1++; // パッシブ条件１を満たした回数をインクリメント


    /* ---------------------- パッシブ条件２ ---------------------- */
    // 確率で決定
    if ( !determineByDice( prob ) ) { return false; }


    PASSED_PASSIVE_12:

    /* ---------------------- パッシブ条件３ ---------------------- */
    // 混乱か睡眠なら発動せず、条件１と２をクリアしたフラグを立てる
    if ( isSleepOrCofusion( hero->status ) ) {
        hero->passed_passive12 = true;
        return false;
    }

    hero->passed_passive12 = false; // 一度スキルが発動したらフラグをリセットする

    // ログに出力
    printPassiveSkill( p );

    return true;

}

// 自分の HP が rate% 未満になったとき一度だけ prob% の確率で
bool Battle::usePassiveHPLessThan( Position p, int rate, int prob ) {

    if ( isDead( p ) ) { return false; } // 死亡時には発動しない
    
    Hero* hero = &heroes[p.side][p.order];

    // 条件１と２をクリアしたフラグが立っていたら、条件１と２を飛ばす
    if ( hero->passed_passive12 ) { goto PASSED_PASSIVE_12; }

    /* ---------------------- パッシブ条件１ ---------------------- */
    // このパッシブスキル発動フェイズでパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->passed_passive_1 ) { return false; }
    // これまでにパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->n_passed_passive_1 > 0 ) { return false; }

    if ( hero->attr_battle[HP] >= hero->getInitAttr(HP) * rate / 100 ) { return false; }
    
    hero->passed_passive_1 = true; // パッシブ条件１を満たしたフラグを立てる
    hero->n_passed_passive_1++; // パッシブ条件１を満たした回数をインクリメント
    
    /* ---------------------- パッシブ条件２ ---------------------- */
    // 確率で決定
    if ( !determineByDice( prob ) ) { return false; }


    PASSED_PASSIVE_12:

    
    /* ---------------------- パッシブ条件３ ---------------------- */
    // 混乱か睡眠なら発動せず、条件１と２をクリアしたフラグを立てる
    if ( isSleepOrCofusion( hero->status ) ) {
        hero->passed_passive12 = true;
        return false;
    }

    hero->passed_passive12 = false; // 一度スキルが発動したらフラグをリセットする

    // ログに出力
    printPassiveSkill( p );

    return true;
}

// 味方全体の合計 HP が rate% 未満になったとき一度だけ prob% の確率で
bool Battle::usePassiveTeamHPLessThan( Position p, int rate, int prob ) {

    if ( isDead( p ) ) { return false; } // 死亡時には発動しない

    Hero* hero = &heroes[p.side][p.order];

    // 条件１と２をクリアしたフラグが立っていたら、条件１と２を飛ばす
    if ( hero->passed_passive12 ) { goto PASSED_PASSIVE_12; }
    
    /* ---------------------- パッシブ条件１ ---------------------- */
    // このパッシブスキル発動フェイズでパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->passed_passive_1 ) { return false; }
    // これまでにパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->n_passed_passive_1 > 0 ) { return false; }

    int team_hp_battle = 0;
    int team_hp_init = 0;
    for ( Order o = Front; o <= Back; o++ ) {
        team_hp_battle += heroes[p.side][o].attr_battle[HP];
        team_hp_init += heroes[p.side][o].getInitAttr(HP);
    }
    if ( team_hp_battle >= team_hp_init * rate / 100 ) { return false; }
    
    hero->passed_passive_1 = true; // パッシブ条件１を満たしたフラグを立てる
    hero->n_passed_passive_1++; // パッシブ条件１を満たした回数をインクリメント
    
    /* ---------------------- パッシブ条件２ ---------------------- */
    // 確率で決定
    if ( !determineByDice( prob ) ) { return false; }

    PASSED_PASSIVE_12:

    
    /* ---------------------- パッシブ条件３ ---------------------- */
    // 混乱か睡眠なら発動せず、条件１と２をクリアしたフラグを立てる
    if ( isSleepOrCofusion( hero->status ) ) {
        hero->passed_passive12 = true;
        return false;
    }

    hero->passed_passive12 = false; // 一度スキルが発動したらフラグをリセットする

    // ログに出力
    printPassiveSkill( p );

    return true;
}

// 死亡時に一度だけ prob% の確率で
bool Battle::usePassiveDying( Position p, int prob ) {

    Hero* hero = &heroes[p.side][p.order];

    /* ---------------------- パッシブ条件１ ---------------------- */
    // このパッシブスキル発動フェイズでパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->passed_passive_1 ) { return false; }
    // これまでにパッシブ条件１を満たしたことがあれば発動しない
    if ( hero->n_passed_passive_1 > 0 ) { return false; }

    if ( hero->attr_battle[HP] > 0 ) { return false; }

    hero->passed_passive_1 = true; // パッシブ条件１を満たしたフラグを立てる
    hero->n_passed_passive_1++; // パッシブ条件１を満たした回数をインクリメント
    
    /* ---------------------- パッシブ条件２ ---------------------- */
    // 確率で決定
    if ( !determineByDice( prob ) ) { return false; }

    /* ---------------------- パッシブ条件３ ---------------------- */
    // 死亡時にステータスは通常状態に戻るのでここは飛ばす

    
    // ログに出力
    printPassiveSkill( p );

    return true;
}

// アクティブスキルによって受けたダメージ量をリセット
void Battle::resetAllDamaged() {
    for ( Side s = Attack; s <= Defence; s++ ) {
    for ( Order o = Front; o <= Back; o++ ) {
        heroes[s][o].damaged = 0;
    }
    }
}


int Battle::getNumberOfAction() {
    return n_action;
}



// すべてのヒーローを初期状態に戻す
void Battle::resetBattle() {
    for ( Side s = Attack; s <= Defence; s++ ) {
    for ( Order o = Front; o <= Back; o++ ) {
        heroes[s][o].reset();
    }
    }
    n_action = 0;
    p_active.side = Side_End;
    p_active.order = Order_End;


}
    



/* ---------------------- ログに出力 ---------------------- */


// ログに罫線を出力
void Battle::printLine() {
    if ( !print_battle_log ) { return; }

    ofs_battle_log << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

// Attack側 / Defence側をログに出力
void Battle::printSide( Side s ) {
    if ( !print_battle_log ) { return; }

    ofs_battle_log << sideToName( s ) << " ";
}
// 前衛 / 中衛 / 後衛 をログに出力
void Battle::printOrder( Order o ) {
    if ( !print_battle_log ) { return; }

    ofs_battle_log << orderToName( o ) << " ";
}
// p にいるヒーロー名をログに出力
void Battle::printHeroName( Position p ) {

    if ( !print_battle_log ) { return; }
    ofs_battle_log << convertIDToHeroName( heroes[p.side][p.order].getID() ) << " ";
}


// p にいるヒーローの Side Order ヒーロー名 (状態異常)をログに出力
void Battle::printPositionHero( Position p ) {
    if ( !print_battle_log ) { return; }

    Hero* hero = &heroes[p.side][p.order];

    

    ofs_battle_log << sideToName(p.side) << " " << orderToName(p.order) << " "
        << convertIDToHeroName( hero->getID() ) << ( isAilment( hero->status ) ? "(" + statusToName(hero->status) + ")" : "" ) << " ";
}



// Action xx 
void Battle::printAction( Position p ) {
    if ( !print_battle_log ) { return; }

    printLine();
    ofs_battle_log << "Action " <<  n_action+1 << endl;

    printPositionHero( p );
}

// アクティブスキル名をログに出力
void Battle::printActiveSkill( ACTIVE_SKILL_ID id ) {
    if ( !print_battle_log ) { return; }

    ofs_battle_log << convertIDToExtensionName( id ) << " →     ";
}

// パッシブスキルをログに出力
void Battle::printPassiveSkill( Position p ) {
    if ( !print_battle_log ) { return; }

    printLine();
    ofs_battle_log << "Action " <<  n_action+1 << endl;

    printPositionHero( p );
    ofs_battle_log << "Passive" << "  →    ";
}





/* 発動後の各ヒーローのステータス */
// Side Order ヒーロー名、（状態異常）、HP/最大HP、PHY( + or - )、INT( + or - )、AGI( + or -)
void Battle::printAllHeroInfo() {
    if ( !print_battle_log ) { return; }

    ofs_battle_log << endl << endl;;

    for ( Side s = Attack; s <= Defence; s++ ) {
        ofs_battle_log << uniformStringLength( sideToName(s), 12 ) << " ";
        for ( Order o = Front; o <= Back; o++ ) {
            Hero* hero = &heroes[s][o];

            string str = "";
            str += orderToName(o) + " "
                + convertIDToHeroName( hero->getID() ) + " " + ( isAilment( hero->status ) ? "(" + statusToName(hero->status) + ")" : "" )
                + attributeToName( HP ) + ":" + to_string( hero->attr_battle[HP] ) + "/" + to_string( hero->getInitAttr(HP) ) + " ";
            
            for ( Attr a = PHY; a < ATTR_END; a++ ) {
                str += attributeToName( a ) + ":" + to_string( hero->attr_battle[a] ) + "(" + ( hero->attr_battle[a] > hero->getInitAttr(a) ? "+" : "" ) + to_string( hero->attr_battle[a] - hero->getInitAttr(a) ) + ") ";
            }
            str += "行動値: " + to_string(hero->action_value) + " ";

            ofs_battle_log << uniformStringLength( str, 70 );
            

        }
        ofs_battle_log << endl;
    }
    printLine();
    ofs_battle_log << endl;
    
}

void Battle::printChangeAttributeValue( Attr a, int delta, bool sign ) {
    if ( !print_battle_log ) { return; }

    string str = "";

    str += attributeToName( a ) + ( sign ? "+" : "-" ) + to_string( delta ) + " ";

    ofs_battle_log << str << " ";
}

// 状態異常をログに出力
void Battle::printStatusAilment( Status s ) {
    if ( !print_battle_log ) { return; }
    ofs_battle_log << statusToName( s ) << " ";
}

// バトル開始前に、ヒーローの情報をログに出力
void Battle::printHeroes() {
    
    if ( !print_battle_log ) { return; }

    printLine();
    ofs_battle_log << endl;

    for ( Side s = Attack; s < Side_End; s++ ) {
        printSide( s );
        ofs_battle_log << endl;
        for ( Order o = Front; o < Order_End; o++ ) {
            Hero* hero = &heroes[s][o];
            Position p = { s, o };
            printOrder( o );
            ofs_battle_log << "   ";

            ofs_battle_log << uniformStringLength( convertIDToHeroName( hero->getID() ), 25 ) << " ";
            
            vector<ACTIVE_SKILL_ID> v = hero->getActiveSkillIDAll();
            for ( auto& id : v ) {
                ofs_battle_log << uniformStringLength( convertIDToExtensionName( id ), 25 ) << " ";
            }

            ofs_battle_log << "HP: " << hero->getInitAttr(HP) << " ";
            for ( Attr a = PHY; a < ATTR_END; a++ ) {
                ofs_battle_log << attributeToName( a ) + ":" + to_string( hero->attr_battle[a] ) + " ";
            }

            ofs_battle_log << endl;
        }
        ofs_battle_log << endl;
    }

    printLine();
    ofs_battle_log << endl;
}



// 統計情報を出力
void Battle::printInfo() {


    



    
}




// 攻撃のダメージ計算
// attack は攻撃側のPHY/INT、attacked は攻撃を受ける側のPHY/INT
// rate は % ( 0~100 )
int Battle::calcDamage( int attack, int rate, int attacked ) {

    int d = ( attack * rate ) / 100;

    return ( d * ( 100 - min( 40, attacked/2 ) ) ) / 100;
}


// 回復効果を計算
// rate は % ( 0~100 )
int Battle::calcHeal( int inte, int phy, int rate ) {
    return ( ( inte + phy ) / 2 ) * rate / 100;
}
int Battle::calcHeal( int inte, int phy, double rate ) {
    return static_cast<int>( static_cast<double>( ( inte + phy ) / 2 ) * rate / static_cast<double>(100) );
}

// 回復効果を計算
// rate は % ( 0~100 )
int Battle::calcHeal( int value, int rate ) {
    return ( value * rate ) / 100;
}

// 状態異常になるかどうか決める
bool Battle::determineStatusAilment( int int_attack, int int_attacked ) {

    assert( int_attack > 0 );
    assert( int_attacked > 0 );

    int p = ( 30 * ( int_attack * 100 / int_attacked ) ) / 100;
    p = min( 100, p );
    
    return determineByDice( p );
}

// 混乱や睡眠が解除されるかどうか決める
bool Battle::determineNormalization() {
    return determineByDice(50);
}


// p にいるヒーローの、バトル中のステータスを返す
int Battle::getBattleAttr( Position p, Attr a ) {
    return heroes[p.side][p.order].attr_battle[a];
}
// p にいるヒーローの、初期ステータスを返す
int Battle::getInitAttr( Position p, Attr a ) {
    return heroes[p.side][p.order].getInitAttr(a);
}
// p にいるヒーローが、あるアクティブスキルによって受けたダメージ量を返す
int Battle::getDamaged( Position p ) {
    return heroes[p.side][p.order].damaged;
}