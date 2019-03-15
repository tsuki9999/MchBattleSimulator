#include "Hero.hpp"

Hero::Hero() {}

Hero::Hero( ID i, Side s, Order o, int attr[], ACTIVE_SKILL_ID active_skill_index[] ) {
    id = i;
    side = s;
    order = o;

    for ( Attr a = HP; a < ATTR_END; a++ ) {
        attr_init[a] = attr_battle[a] = attr[a];
    }

    for ( int i = 0; i < 3; i++ ) {
        active_skill_id[i] = active_skill_index[i];
    }
}



void Hero::reset() {
    for ( Attr a = HP; a < ATTR_END; a++ ) {
        attr_battle[a] = attr_init[a];
    }

    status = Normal;
    action_value = 0;
    action_stage = 0;

    passed_passive_1 = false;
    passed_passive12 = false;
    n_passed_passive_1 = 0;

    damaged = 0;
}



ID Hero::getID() {
    return id;
}

int Hero::getInitAttr( Attr a ) {
    return attr_init[a];
}

vector<ACTIVE_SKILL_ID> Hero::getActiveSkillIDAll() {
    vector<ACTIVE_SKILL_ID> v;
    for ( int i = 0; i < 3; i++ ) { v.push_back( active_skill_id[i] ); }
    return v;
}

ACTIVE_SKILL_ID Hero::getActiveSkillID() {
    action_stage %= 3;
    return active_skill_id[action_stage++];   
}

void Hero::set( ID i, Side s, Order o, int attr[], ACTIVE_SKILL_ID active_skill_index[] ) {
        
        id = i;
        side = s;
        order = o;

        for ( Attr a = HP; a < ATTR_END; a++ ) {
            attr_init[a] = attr_battle[a] = attr[a];
        }

        for ( int i = 0; i < 3; i++ ) {
            active_skill_id[i] = active_skill_index[i];
        }
    }