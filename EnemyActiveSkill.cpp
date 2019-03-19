#include "Battle.hpp"

// スパミング1.0
void Battle::spamming_1_0( Position p ) {
    damageSkill( p, FrontEnemy, 10, 30, PHY, ACTIVE_DAMAGE );
}
// スパミング1.2
void Battle::spamming_1_2( Position p ) {
    damageSkill( p, FrontEnemy, 25, 45, PHY, ACTIVE_DAMAGE );
}
// スパミング2.0
void Battle::spamming_2_0( Position p ) {
    damageSkill( p, AllEnemy, 10, 50, PHY, ACTIVE_DAMAGE );
}

// リファクタリング1.0
void Battle::refactoring_1_0( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, PHY, INT, 5, 15, BUFF );
}
// リファクタリングボム2.0
void Battle::refactoring_bomb_2_0( Position p ) {
    changeAttrSkill( p, AllAlly, PHY, INT, 10, 30, BUFF );
}

// フィッシング1.0
void Battle::phishing_1_0( Position p ) {
    damageSkill( p, FrontEnemy, 10, 30, INT, ACTIVE_DAMAGE );
}
// フィッシング1.2
void Battle::phishing_1_2( Position p ) {
    damageSkill( p, FrontEnemy, 25, 45, INT, ACTIVE_DAMAGE );
}
// フィッシング2.0
void Battle::phishing_2_0( Position p ) {
    damageSkill( p, AllEnemy, 10, 50, INT, ACTIVE_DAMAGE );
}

// ディープラーニング1.0
void Battle::deep_learning_1_0( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, INT, INT, 5, 15, BUFF );
}
// ディープラーニング1.5
void Battle::deep_learning_1_5( Position p ) {
    changeAttrSkill( p, HP, LOW, ALLY, INT, INT, 10, 25, BUFF );
}
// ディープラーニングボム2.0
void Battle::deep_learning_bomb_2_0( Position p ) {
    changeAttrSkill( p, AllAlly, INT, INT, 10, 30, BUFF );
}

// ロールバック1.0
void Battle::rollback_1_0( Position p ) {
    healSkill( p, HP, LOW, ALLY, 10, 30 );
}
// ロールバック1.5
void Battle::rollback_1_0( Position p ) {
    healSkill( p, HP, LOW, ALLY, 25, 45 );
}

// コードインジェクション1.0
void Battle::code_injection_1_0( Position p ) {
    changeAttrSkill( p, AllEnemy, INT, PHY, 10, 20, DEBUFF );
}
// コードインジェクション1.5
void Battle::code_injection_1_5( Position p ) {
    changeAttrSkill( p, AllEnemy, INT, PHY, 20, 40, DEBUFF );
}


