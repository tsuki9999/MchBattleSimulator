const Attack = 0;
const Difence = 1;

const Front = 0;
const Middle = 1;
const Back = 2;

const Legendary = 5000;
const Epic = 4000;
const Rare = 3000;
const Uncommon = 2000;
const Novice = 1000;

const ArtEditSkill = 100000;

const SideToNum = {
    Attack: 0, Defence:1
}

const OrderToNum = {
    Front: 0, Middle: 1, Back: 2
}
const AttrToNum = {
    HP: 0, PHY: 1, INT: 2, AGI: 3
}

const SideStr = [
    "Attack","Defence"
];

const OrderStr = [
    "Front","Middle", "Back"
];

const AttrStr = [
    "HP", "PHY", "INT", "AGI"
];

const RarityToNum = {
    Legendary:5000, Epic:4000, Rare:3000, Uncommon:2000, Novice:1000, Common:1000,
};


const AttrAllZero = {
    HP:0, PHY:0, INT:0, AGI:0
};

const HeroAttr = {
    5001: { HP:459, PHY:185, INT:96, AGI:118 },
    5002: { HP:384, PHY:105, INT:181, AGI:138 },
};


const ExtensionAttr = {

    1001: { HP:60, PHY:59, INT:0, AGI:0 },
    2001: { HP:72, PHY:73, INT:0, AGI:0 },
    3001: { HP:87, PHY:86, INT:0, AGI:0 },
    4001: { HP:96, PHY:97, INT:0, AGI:0 },
    5001: { HP:114, PHY:113, INT:0, AGI:0 },
    10001: { HP:15, PHY:15, INT:0, AGI:0 },
    20001: { HP:24, PHY:21, INT:0, AGI:0 },
    30001: { HP:27, PHY:28, INT:0, AGI:0 },
    40001: { HP:33, PHY:34, INT:0, AGI:0 },
    50001: { HP:36, PHY:38, INT:0, AGI:0 },
    60001: { HP:45, PHY:46, INT:0, AGI:0 },
    70001: { HP:72, PHY:75, INT:0, AGI:0 },
    

};

let TeamAttr = {
    Attack: {
        Front : { HP:0, PHY:0, INT:0, AGI:0 },
        Middle : { HP:0, PHY:0, INT:0, AGI:0 },
        Back : { HP:0, PHY:0, INT:0, AGI:0 }
    },
    Defence: {
        Front : { HP:0, PHY:0, INT:0, AGI:0 },
        Middle : { HP:0, PHY:0, INT:0, AGI:0 },
        Back : { HP:0, PHY:0, INT:0, AGI:0 }
    }
}


function searchSide( element ) {

    return $(element).parents().hasClass('Attack') ? "Attack" : "Defence";
}
function searchOrder( element ) {
    let order;
    for ( let i = 0; i < OrderStr.length; i++ ) {
        if ( $(element).parents().hasClass( OrderStr[i] ) ) { order = OrderStr[i]; }
    }
    return order;
}
function searchSkillNumber( element ) {
    if ( $(element).hasClass('skill1') ) { return 0; }
    else if ( $(element).hasClass('skill2') ) { return 1; }
    else if ( $(element).hasClass('skill3') ) { return 2; }
    else { return 3; }
}

function calcAttr( element ) {
    
    const side = searchSide( element );
    const order = searchOrder( element );
    

    for ( let i = 0; i < AttrStr.length; i++ ) {
        TeamAttr[side][order][AttrStr[i]] = 0;
    }

    let position;
    $(element).parents().each( function() {
        if ( $(this).hasClass( order ) ) { position = this; return; }
    });
    
    let str = "合計能力値　";
    $(position).find('input').each( function() {
        TeamAttr[side][order][this.className] += parseInt( $(this).val() );
    });

    for ( let i = 0; i < AttrStr.length; i++ ) {
        str += AttrStr[i] + ": " + String(TeamAttr[side][order][AttrStr[i]]) + "　";
    }
    
    $(position).find('p').each( function() {
        if ( $(this).hasClass('attr_sum') ) {
            $(this).text(str)
        }
    });
    
}

function printTextArea() {
    // ID

    let str = new Array(12);
    for ( let i = 0; i < 12; i++ ) {
        str[i] = new Array(4);
    }

    $( 'textarea' ).val(null);

    // ID
    $( 'fieldset select' ).each( function() {

        if ( $(this).hasClass('children') ) {

            const side = searchSide( this );
            const order = searchOrder( this );

            const pos = ( SideToNum[side] * 3 + OrderToNum[order] )*2;

            if ( $(this).hasClass('hero') ) {
                const val1 = $(this.previousElementSibling).val();
                const val2 = $(this).val();
                // if ( !val1 || !val2 ) { $( 'textarea' ).val( $( 'textarea' ).val() + side + " " + order + " のヒーローが未設定です\n" ); }
                if ( !val1 || !val2 ) { str[pos][0] = "未設定"; }
                else {
                    const rarity = RarityToNum[ val1 ];
                    const n = parseInt( val2 );
                    const id = rarity + n;
                    str[pos][0] = String( id );
                }
                
            }
            else if ( $(this).hasClass('skill') ) {
                const val1 = $(this).val();
                const val2 = $(this.previousElementSibling).val();

                const n = searchSkillNumber(this);
                // if ( !val1 || !val2 ) { $( 'textarea' ).val( $( 'textarea' ).val() + side + " " + order + " のスキル" + String(n+1) + "が未設定です\n" ); }
                if ( !val1 || !val2 ) { str[pos][n+1] = "未設定"; }
                else {
                    const id = parseInt( val1 ) + parseInt( val2 );
                    str[pos][n+1] = String( id );
                }                
            }            
        }
        
    });


    for ( let i = 0; i < SideStr.length; i++ ) {
    for ( let j = 0; j < OrderStr.length; j++ ) {
    for ( let k = 0; k < AttrStr.length; k++ ) {
        const side = SideStr[i];
        const order = OrderStr[j];
        const attr = AttrStr[k];
        str[ ( SideToNum[side] * 3 + OrderToNum[order] )*2+1 ][ AttrToNum[attr] ] = TeamAttr[side][order][attr];
    }
    }
    }
    

    let s = "";
    for ( let i = 0; i < 12; i++ ) {
        let t = "";

        let n_art_edit_skill = 0;
        let all_id_done = true;

        for ( let j = 0; j < 4; j++ ) {

            if ( parseInt( str[i][j] ) >= ArtEditSkill ) { n_art_edit_skill++; }
            if ( str[i][j] == "未設定" ) { all_id_done = false; }

            t += str[i][j];
            if ( j != 3 ) { t += "\t"; }
        }

        if ( i%2 == 0 ) {
            if ( all_id_done && n_art_edit_skill == 0 ) { t += "　アートエディットスキルが設定されていません"; }
            if ( all_id_done && n_art_edit_skill > 1 ) { t += "　アートエディットスキルが複数設定されています"; }
        }

        s += t + "\n";


    }



    $( 'textarea' ).val( s );


}



$(document).ready( function(){


    // 能力値の input を追加
    const element = document.getElementsByClassName('attr_value');

    const target = document.getElementsByClassName('attr_input');

    $(target).each( function() {
        $(this).html( $(element).html() );

        $(this).find('input').each( function() {

            $(this).change( function() {
                calcAttr( this );
                printTextArea();
            });
            calcAttr( this );
            printTextArea();
        }); 
    });


    // ヒーローのレアリティを選択
    $('.parent.hero').each(function() {
        $(this).html( $('.parent.hero.dummy').html() );

        $(this).change( function(){
            const val1 = $(this).val();
            
            const children = $(this.nextElementSibling);

            children.html( $('.children.hero.dummy').html() ).find('option').each( function() {
                const val2 = $(this).data('val');
                if (val1 != val2) {
                    $(this).not($('.msg')).remove();
                }
            });

            children.val("");
            
            if ($(this).val() == "") {
                children.attr('disabled', 'disabled');
            }
            else  { children.removeAttr('disabled'); }

            // 能力値の設定をリセット
            let flag = false;
            $(this).parents().each( function() {
                if ( flag ) { return; }
                $(this).find('input').each( function() {
                    flag = true;
                    const name = this.className;
                    $(this).val(AttrAllZero[name]);
                }); 
            });

            calcAttr( this );
            printTextArea();
        });

    })

    // ヒーローを選択
    $('.children.hero').each(function() {
        $(this).html( $('.children.hero.dummy').html() );

        // 選択肢によって能力値を設定
        $(this).change( function() {
            
            const rarity = RarityToNum[ $(this.previousElementSibling).val() ];
            const n = parseInt( $(this).val() );            
            const id = rarity + n;            
            const attr = HeroAttr[String(id)];
            
            let flag = false;
            $(this).parents().each( function() {
                if ( flag ) { return; }
                $(this).find('input').each( function() {
                    flag = true;
                    const name = this.className;
                    $(this).val(attr[name]);
                }); 
                
            });
            

            calcAttr( this );
            printTextArea();
        });

    })

    // スキルの種類を選択
    $('.parent.skill').each(function() {
        $(this).html( $('.parent.skill.dummy').html() );

        $(this).change( function(){

            const val1 = ( parseInt( $(this).val() ) == ArtEditSkill ) ? "art_edit" : "extension";

            const children = $(this.nextElementSibling);
            
            children.html( $('.children.skill.dummy').html() ).find('option').each( function() {
                const val2 = $(this).data('val');
                if (val1 != val2) {
                    $(this).remove();
                }
            });

            children.val("");
            
            if ($(this).val() == "") {
                children.attr('disabled', 'disabled');
            }
            else  { children.removeAttr('disabled'); }

            // 能力値の設定をリセット
            let flag = false;
            $(this).parents().each( function() {
                if ( flag ) { return; }
                $(this).find('input').each( function() {
                    flag = true;
                    const name = this.className;
                    $(this).val(AttrAllZero[name]);
                }); 
            });

            calcAttr( this );
            printTextArea();

        });


    })

    // エクステンションのレアリティまたはアートエディットスキルを選択
    $('.children.skill').each(function() {
        $(this).html( $('.children.skill.dummy').html() );

        // 選択肢によって能力値を設定
        $(this).change( function() {
            const id = parseInt( $(this).val() ) + parseInt( $(this.previousElementSibling).val() );
            const attr = id >= ArtEditSkill ? AttrAllZero : ExtensionAttr[String(id)];
            
            let flag = false;
            $(this).parents().each( function() {
                if ( flag ) { return; }
                $(this).find('input').each( function() {
                    flag = true;
                    const name = this.className;
                    $(this).val(attr[name]);
                }); 
            });


            // $(this.parentNode).find('input').each( function() {
            //     const name = this.className;
            //     $(this).val(attr[name]);
            // });

            calcAttr( this );            
            printTextArea();
        });

    })








    


});