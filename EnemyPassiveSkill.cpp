#include "Battle.hpp"

// スパムボム2.0
bool Battle::spam_bomb_2_0( Position p ) {
    bool is_used = usePassiveHPLessThan( p, 30, 100 );
    if ( is_used ) {
        damageSkill( p, AllEnemy, 30, 60, PHY, NOT_ACTIVE_DAMAGE );
    }
    return is_used;
}
// ロールバックボム2.0
bool Battle::rollback_bomb_2_0( Position p ) {
    bool is_used = usePassiveHPLessThan( p, 30, 100 );
    if ( is_used ) {
        healSkill( p, AllAlly, 10, 60 );
    }
    return is_used;
}
// フィッシングボム2.0
bool Battle::phishing_bomb_2_0( Position p ) {
    bool is_used = usePassiveHPLessThan( p, 30, 100 );
    if ( is_used ) {
        damageSkill( p, AllEnemy, 30, 60, INT, NOT_ACTIVE_DAMAGE );
    }
    return is_used;
}
// スミッシング1.0
bool Battle::smishing_1_0( Position p ) {
    bool is_used = usePassiveDamaged( p, 20 );
    if ( is_used ) {
        healSkill( p, HP, LOW, ALLY, 30 );
    }
    return is_used;
}
// スミッシング2.0
bool Battle::smishing_2_0( Position p ) {
    bool is_used = usePassiveDamaged( p, 25 );
    if ( is_used ) {
        healSkill( p, HP, LOW, ALLY, 40 );
    }
    return is_used;
}
// コードインジェクション2.0
bool Battle::code_injection_2_0( Position p ) {
    bool is_used = usePassiveHPLessThan( p, 60, 100 );
    if ( is_used ) {
        changeAttrSkill( p, AllEnemy, INT, PHY, 20, 70, DEBUFF );
    }
    return is_used;
}