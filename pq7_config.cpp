#include "pq7_config.h"

//namespace using c_Config;

c_Config::c_Config()
{
    Traits << "Name" << "Race"  << "Class"  << "Level";

    PrimeStats << "STR" << "INT" << "WIS" << "DEX" << "CON"  << "CHA";

    Equips << "Weapon" << "Shield" << "Helm" << "Hauberk" << "Brassairts"
           << "Vambraces" << "Gauntlets" << "Gambeson" << "Cuisses"
           << "Greaves" << "Sollerets";

    Spells << "Slime Finger" << "Rabbit Punch" << "Hastiness" << "Good Move"
           << "Sadness" << "Seasick" << "Gyp" << "Shoelaces" << "Innoculate"
           << "Cone of Annoyance" << "Magnetic Orb" << "Invisible Hands"
           << "Revolting Cloud" << "Aqueous Humor" << "Spectral Miasma"
           << "Clever Fellow" << "Lockjaw" << "History Lesson" << "Hydrophobia"
           << "Big Sister" << "Cone of Paste" << "Mulligan" << "Nestor's Bright Idea"
           << "Holy Batpole" << "Tumor (Benign)" << "Braingate" << "Summon a Bitch"
           << "Nonplus" << "Animate Nightstand" << "Eye of the Troglodyte" << "Curse Name"
           << "Dropsy" << "Vitreous Humor" << "Roger's Grand Illusion" << "Covet"
           << "Black Idaho" << "Astral Miasma" << "Spectral Oyster" << "Acrid Hands"
           << "Angioplasty" << "Grognor's Big Day Off" << "Tumor (Malignant)"
           << "Animate Tunic" << "Ursine Armor" << "Holy Roller" << "Tonsilectomy"
           << "Curse Family" << "Infinite Confusion" << "Recursive Maladiction"
           << "Enzyme's Taco Mastication" << "Xeno's Timeslip";

    OffenseAttrib << "Polished|+1" << "Serrated|+1" << "Heavy|+1" << "Pronged|+2"
                  << "Steely|+2" << "Vicious|+3" << "Venomed|+4" << "Stabbity|+4"
                  << "Dancing|+5" << "Invisible|+6" << "Vorpal|+7";

    DefenseAttrib << "Studded|+1" << "Cambric|+1" << "Gilded|+2" << "Banded|+2"
                  << "Festooned|+3" << "Holy|+4" << "Fine|+4" << "Impressive|+5"
                  << "Custom|+5" << "Stalwart|+6" << "Abative|+7";

    OffenseBad << "Dull|-2" << "Tarnished|-1" << "Rusty|-3" << "Padded|-5" << "Bent|-4" << "Mini|-4"
               << "Rubber|-6" << "Nerf|-7" << "Unbalanced|-2";

    DefenseBad << "Holey|-1" << "Patched|-1" << "Threadbare|-2" << "Faded|-1" << "Rusty|-3" << "Motheaten|-3"
               << "Mildewed|-2" << "Torn|-3" << "Dented|-3" << "Cursed|-5" << "Plastic|-4" << "Cracked|-4"
               << "Warped|-3" << "Corroded|-3";

    Shields << "Parasol|0" << "Pie Plate|1" << "Garbage Can Lid|2" << "Buckler|3"
            << "Plexiglass|4" << "Fender|4" << "Round Shield|5" << "Carapace|5"
            << "Scutum|6" << "Propugner|6" << "Kite Shield|7" << "Pavise|8"
            << "Tower Shield|9" << "Baroque Shield|11" << "Aegis|12"
            << "Magnetic Field|18";

    Armors << "Lace|1" << "Macrame|2" << "Burlap|3" << "Canvas|4" << "Flannel|5"
           << "Chamois|6" << "Pleathers|7" << "Leathers|8" << "Bearskin|9"
           << "Ringmail|10" << "Scale Mail|12" << "Chainmail|14" << "Splint Mail|15"
           << "Platemail|16" << "ABS|17" << "Kevlar|18" << "Titanium|19"
           << "Mithril Mail|20" << "Diamond Mail|25" << "Plasma|30";

    Weapons << "Stick|0" << "Broken Bottle|1" << "Shiv|1" << "Sprig|1" << "Oxgoad|1"
            << "Eelspear|2" << "Bowie Knife|2" << "Claw Hammer|2" << "Handpeen|2"
            << "Andiron|3" << "Hatchet|3" << "Tomahawk|3" << "Hackbarm|3" << "Crowbar|4"
            << "Mace|4" << "Battleadze|4" << "Leafmace|5" << "Shortsword|5"
            << "Longiron|5" << "Poachard|5" << "Baselard|5" << "Whinyard|6"
            << "Blunderbuss|6" << "Longsword|6" << "Crankbow|6" << "Blibo|7"
            << "Broadsword|7" << "Kreen|7" << "Warhammer|7" << "Morning Star|8"
            << "Pole-adze|8" << "Spontoon|8" << "Bastard Sword|9" << "Peen-arm|9"
            << "Culverin|10" << "Lance|10" << "Halberd|11" << "Poleax|12"
            << "Bandyclef|15";

    Specials << "Diadem" << "Festoon" << "Gemstone" << "Phial" << "Tiara" << "Scabbard"
             << "Arrow" << "Lens" << "Lamp" << "Hymnal" << "Fleece" << "Laurel"
             << "Brooch" << "Gimlet" << "Cobble" << "Albatross" << "Brazier"
             << "Bandolier" << "Tome" << "Garnet" << "Amethyst" << "Candelabra"
             << "Corset" << "Sphere" << "Sceptre" << "Ankh" << "Talisman" << "Orb"
             << "Gammel" << "Ornament" << "Brocade" << "Galoon" << "Bijou" << "Spangle"
             << "Gimcrack" << "Hood" << "Vulpeculum";

    ItemAttrib << "Golden" << "Gilded" << "Spectral" << "Astral" << "Garlanded"
               << "Precious" << "Crafted" << "Dual" << "Filigreed" << "Cruciate"
               << "Arcane" << "Blessed" << "Reverential" << "Lucky" << "Enchanted"
               << "Gleaming" << "Grandiose" << "Sacred" << "Legendary" << "Mythic"
               << "Crystalline" << "Austere" << "Ostentatious" << "One True"
               << "Proverbial" << "Fearsome" << "Deadly" << "Benevolent" << "Unearthly"
               << "Magnificent" << "Iron" << "Ormolu" << "Puissant";

    ItemOfs << "Foreboding" << "Foreshadowing" << "Nervousness" << "Happiness"
            << "Torpor" << "Danger" << "Craft" << "Silence" << "Invisibility"
            << "Rapidity" << "Pleasure" << "Practicality" << "Hurting" << "Joy"
            << "Petulance" << "Intrusion" << "Chaos" << "Suffering" << "Extroversion"
            << "Frenzy" << "Sisu" << "Solitude" << "Punctuality" << "Efficiency"
            << "Comfort" << "Patience" << "Internment" << "Incarceration"
            << "Misapprehension" << "Loyalty" << "Envy" << "Acrimony" << "Worry"
            << "Fear" << "Awe" << "Guile" << "Prurience" << "Fortune"
            << "Perspicacity" << "Domination" << "Submission" << "Fealty" << "Hunger"
            << "Despair" << "Cruelty" << "Grob" << "Dignard" << "Ra" << "the Bone"
            << "Diamonique" << "Electrum" << "Hydragyrum";

    BoringItems << "nail" << "lunchpail" << "sock" << "I.O.U." << "cookie" << "pint"
                << "toothpick" << "writ" << "newspaper" << "letter" << "plank" << "hat"
                << "egg" << "coin" << "needle" << "bucket" << "ladder" << "chicken"
                << "twig" << "dirtclod" << "counterpane" << "vest" << "teratoma"
                << "bunny" << "rock" << "pole" << "carrot" << "canoe" << "inkwell"
                << "hoe" << "bandage" << "trowel" << "towel" << "planter box" << "anvil"
                << "axle" << "tuppence" << "casket" << "nosegay" << "trinket"
                << "credenza" << "writ";

    MonSpcDrop << "toe" << "foot" << "giblet" << "eye" << "fur" << "meat" << "leg" << "kneecap"
               << "wishbone" << "femor" << "thorax" << "finger" << "signet" << "symbol" << "head"
               << "tail" << "arm" << "scale" << "fat glob" << "sinew" << "token" << "feces" << "spittle"
               << "scent" << "urine" << "egg" << "fang" << "tongue" << "gizzard" << "intrail"
               << "juice" << "blood" << "soul";

    Monsters << "Anhkheg|6|chitin" << "Ant|0|antenna" << "Ape|4|ass" << "Baluchitherium|14|ear"
             << "Beholder|10|eyestalk" << "Black Pudding|10|saliva" << "Blink Dog|4|eyelid"
             << "Cub Scout|1|neckerchief" << "Girl Scout|2|cookie" << "Boy Scout|3|merit badge"
             << "Eagle Scout|4|merit badge" << "Bugbear|3|skin" << "Bugboar|3|tusk"
             << "Boogie|3|slime" << "Camel|2|hump" << "Carrion Crawler|3|egg"
             << "Catoblepas|6|neck" << "Centaur|4|rib" << "Centipede|0|leg" << "Cockatrice|5|wattle"
             << "Couatl|9|wing" << "Crayfish|0|antenna" << "Demogorgon|53|tentacle"
             << "Jubilex|17|gel" << "Manes|1|tooth" << "Orcus|27|wand" << "Succubus|6|bra"
             << "Vrock|8|neck" << "Hezrou|9|leg" << "Glabrezu|10|collar" << "Nalfeshnee|11|tusk"
             << "Marilith|7|arm" << "Balor|8|whip" << "Yeenoghu|25|flail" << "Asmodeus|52|leathers"
             << "Baalzebul|43|pants" << "Barbed Devil|8|flame" << "Bone Devil|9|hook"
             << "Dispater|30|matches" << "Erinyes|6|thong" << "Geryon|30|cornucopia"
             << "Malebranche|5|fork" << "Ice Devil|11|snow" << "Lemure|3|blob" << "Pit Fiend|13|seed"
             << "Anklyosaurus|9|tail" << "Brontosaurus|30|brain" << "Diplodocus|24|fin"
             << "Elasmosaurus|15|neck" << "Gorgosaurus|13|arm" << "Iguanadon|6|thumb";
    Monsters << "Megalosaurus|12|jaw" << "Monoclonius|8|horn" << "Pentasaurus|12|head"
             << "Stegosaurus|18|plate" << "Triceratops|16|horn" << "Tyranosauraus Rex|18|forearm"
             << "Djinn|7|lamp" << "Doppleganger|4|face" << "Black Dragon|7|*" << "Plaid Dragon|7|sporrin"
             << "Blue Dragon|9|*" << "Beige Dragon|9|*" << "Brass Dragon|7|pole" << "Tin Dragon|8|*"
             << "Bronze Dragon|9|medal" << "Chromatic Dragon|16|scale" << "Copper Dragon|8|loafer"
             << "Gold Dragon|8|filling" << "Green Dragon|8|*" << "Platinum Dragon|21|*"
             << "Red Dragon|10|cocktail" << "Silver Dragon|10|*" << "White Dragon|6|tooth"
             << "Dragon Turtle|13|shell" << "Dryad|2|acorn" << "Dwarf|1|drawers" << "Eel|2|sashimi"
             << "Efreet|10|cinder" << "Sand Elemental|8|glass" << "Bacon Elemental|10|bit"
             << "Porn Elemental|12|lube" << "Cheese Elemental|14|curd" << "Hair Elemental|16|follicle"
             << "Swamp Elf|1|lilypad" << "Brown Elf|1|tusk" << "Sea Elf|1|jerkin" << "Ettin|10|fur"
             << "Frog|0|leg" << "Violet Fungi|3|spore" << "Gargoyle|4|gravel" << "Gelatinous Cube|4|jam"
             << "Ghast|4|vomit" << "Ghost|10|*" << "Ghoul|2|muscle" << "Humidity Giant|12|drops"
             << "Beef Giant|11|steak" << "Quartz Giant|10|crystal" << "Porcelain Giant|9|fixture"
             << "Rice Giant|8|grain" << "Cloud Giant|12|condensation" << "Fire Giant|11|cigarettes"
             << "Frost Giant|10|snowman" << "Hill Giant|8|corpse" << "Stone Giant|9|hatchling"
             << "Storm Giant|15|barometer" << "Mini Giant|4|pompadour" << "Gnoll|2|collar"
             << "Gnome|1|hat" << "Goblin|1|ear" << "Grid Bug|1|carapace" << "Jellyrock|9|seedling";
    Monsters << "Beer Golem|15|foam" << "Oxygen Golem|17|platelet" << "Cardboard Golem|14|recycling"
             << "Rubber Golem|16|ball" << "Leather Golem|15|fob" << "Gorgon|8|testicle"
             << "Gray Ooze|3|gravy" << "Green Slime|2|sample" << "Griffon|7|nest" << "Banshee|7|larynx"
             << "Harpy|3|mascara" << "Hell Hound|5|tongue" << "Hippocampus|4|mane" << "Hippogriff|3|egg"
             << "Hobgoblin|1|patella" << "Homonculus|2|fluid" << "Hydra|8|gyrum" << "Imp|2|tail"
             << "Invisible Stalker|8|*" << "Iron Peasant|3|chaff" << "Jumpskin|3|shin" << "Kobold|1|penis"
             << "Leprechaun|1|wallet" << "Leucrotta|6|hoof" << "Lich|11|crown" << "Lizard Man|2|tail"
             << "Lurker|10|sac" << "Manticore|6|spike" << "Mastodon|12|tusk" << "Medusa|6|eye"
             << "Multicell|2|dendrite" << "Pirate|1|booty" << "Berserker|1|shirt" << "Caveman|2|club"
             << "Dervish|1|robe" << "Merman|1|trident" << "Mermaid|1|gills" << "Mimic|9|hinge"
             << "Mind Flayer|8|tentacle" << "Minotaur|6|map" << "Yellow Mold|1|spore" << "Morkoth|7|teeth"
             << "Mummy|6|gauze" << "Naga|9|rattle" << "Nebbish|1|belly" << "Neo-Otyugh|11|organ "
             << "Nixie|1|webbing" << "Nymph|3|hanky" << "Ochre Jelly|6|nucleus" << "Octopus|2|beak"
             << "Ogre|4|talon" << "Ogre Mage|5|apparel" << "Orc|1|snout" << "Otyugh|7|organ"
             << "Owlbear|5|feather" << "Pegasus|4|aileron" << "Peryton|4|antler" << "Piercer|3|tip"
             << "Pixie|1|dust" << "Man-o-war|3|tentacle" << "Purple Worm|15|dung" << "Quasit|3|tail"
             << "Rakshasa|7|pajamas" << "Rat|0|tail" << "Remorhaz|11|protrusion" << "Roc|18|wing"
             << "Roper|11|twine" << "Rot Grub|1|eggsac" << "Rust Monster|5|shavings" << "Satyr|5|hoof"
             << "Sea Hag|3|wart" << "Silkie|3|fur" << "Shadow|3|silhouette" << "Shambling Mound|10|mulch"
             << "Shedu|9|hoof" << "Shrieker|3|stalk" << "Skeleton|1|clavicle" << "Spectre|7|vestige"
             << "Sphinx|10|paw" << "Spider|0|web" << "Sprite|1|can" << "Stirge|1|proboscis"
             << "Stun Bear|5|tooth" << "Stun Worm|2|trode" << "Su-monster|5|tail" << "Sylph|3|thigh";
    Monsters << "Titan|20|sandal" << "Trapper|12|shag" << "Treant|10|acorn" << "Triton|3|scale"
             << "Troglodyte|2|tail" << "Troll|6|hide" << "Umber Hulk|8|claw" << "Unicorn|4|blood"
             << "Vampire|8|pancreas" << "Wight|4|lung" << "Will-o'-the-Wisp|9|wisp" << "Wraith|5|finger"
             << "Wyvern|7|wing" << "Xorn|7|jaw" << "Yeti|4|fur" << "Zombie|2|forehead" << "Wasp|0|stinger"
             << "Rat|1|tail" << "Bunny|0|ear" << "Moth|0|dust" << "Beagle|0|collar" << "Midge|0|corpse"
             << "Ostrich|1|beak" << "Billy Goat|1|beard" << "Bat|1|wing" << "Koala|2|heart" << "Wolf|2|paw"
             << "Whippet|2|collar" << "Uruk|2|boot" << "Poroid|4|node" << "Moakum|8|frenum" << "Fly|0|*"
             << "Hogbird|3|curl" << "Wolog|4|lemma";

    MonHealth << "dying *|-5" << "comatose *|-4" << "decrepid *|-3" << "sickly *|-2" << "undernourished *|-1"
              << "well-fed *|+1" << "husky *|+2" << "muscled *|+3" << "robust *|+4" << "glowing *|+5";

    MonAge << "fetal *|-5" << "baby *|-4" << "preadolescent *|-3" << "teenage *|-2" << "underage *|-1"
           << "mature *| +1" << "elder *|+2" << "veteran *|+3" << "senior *|+4" << "ancient *|+5";

    MonSize << "tiny *|-5" << "miniature *|-4" << "small *|-3" << "short *|-2" << "lesser *|-1"
            << "greater *|+1" << "massive *|+2" << "enormous *|+3" << "giant *|+4" << "titanic *|+5";

    MonCast << "drunk *|-5" << "* day-dreamer|-4" << "lazy *|-3" << "* slacker|-2" << "* novice|-1"
            << "* warrior|+1" << "* elite|+2"  << "* leiutenent|+3" << "* shaman|+4" << "* chief|+5" ;

    MonSpecial << "battle-*|+5" << "* thug|+5" << "gelatinous *|+5" << "master *|+10" << "poisonous *|+10"
               << "* hero |+10" << "spellcasting *|+20" << "desert *|+20" << "* swashbuckler|+20" << "double-headed *|+30"
               << "metal-plated *|+30" << "undead *|+30" << "* assassin|+30" << "war-*|+40" << "steam-powered *|+40"
               << "* ninja|+40" << "translucent *|+50" << "* patriarch|+50" << "* champion|+50" << "* defender|+60"
               << "* shade|+60" << "* executioner|+60" << "were-*|+70" << "* lord|+70" << "invisable *|+70"
               << "vampiric *|+80" << "* high-lord|+80" << "* knight|+80" << "* lich|+90" << "* ironclad *|+90"
               << "* farseer|+90" << "* initiate of the outer circle|+100" << "etheral *|+100" << "* summoner|+100"
               << "* seer of the outer planes|+110" << "* demi-lich|+110" << "* master summoner|+110" << "astral *|+120"
               << "* timecaster|+120" << "* master of the east sun|+120" << "* voidcaster|+130"
               << "* master of the west sun|+130" << "* skywalker|+130" << "* master of the north moon|+140"
               << "* of gehenna|+140" << "arcadian *|+140" << "* master of the south star|+150" << "* of hades|+150"
               << "god-emperor *|+150";

    Races << "Half Orc|HP Max" << "Half Man|CHA" << "Half Halfling|DEX" << "Double Hobbit|STR"
          << "Hob-Hobbit|DEX,CON" << "Low Elf|CON" << "Dung Elf|WIS" << "Talking Pony|MP Max,INT"
          << "Gyrognome|DEX" << "Lesser Dwarf|CON" << "Crested Dwarf|CHA" << "Eel Man|DEX"
          << "Panda Man|CON,STR" << "Trans-Kobold|WIS" << "Enchanted Motorcycle|MP Max"
          << "Will o' the Wisp|WIS" << "Battle-Finch|DEX,INT" << "Double Wookiee|STR"
          << "Skraeling|WIS" << "Demicanadian|CON" << "Land Squid|STR,HP Max";

    Klasses << "Ur-Paladin|WIS,CON" << "Voodoo Princess|INT,CHA" << "Robot Monk|STR" << "Mu-Fu Monk|DEX"
            << "Mage Illusioner|INT,MP Max" << "Shiv-Knight|DEX" << "Inner Mason|CON"
            << "Fighter/Organist|CHA,STR" << "Puma Burgular|DEX" << "Runeloremaster|WIS"
            << "Hunter Strangler|DEX,INT" << "Battle-Felon|STR" << "Tickle-Mimic|WIS,INT"
            << "Slow Poisoner|CON" << "Bastard Lunatic|CON" << "Lowling|WIS" << "Birdrider|WIS"
            << "Vermineer|INT";

    Titles << "Mr." << "Mrs." << "Sir" << "Sgt." << "Ms." << "Captain" << "Chief" << "Admiral" << "Saint";

    ImpressiveTitles << "King" << "Queen" << "Lord" << "Lady" << "Viceroy" << "Mayor" << "Prince"
                     << "Princess" << "Chief" << "Boss" << "Archbishop";
}

QString c_Config::toRoman(int value)
{
    QList<int> values;
    QStringList romanNumerals;

    int curValue(0), index(0) ;
    QString rtnNumerals;

    rtnNumerals.clear();

    values << 1000 << 900 << 500 << 400 << 100 << 90
           << 50 << 40 << 10 << 9 << 5 << 4 << 1;

    romanNumerals << "M" << "CM" << "D" << "CD" << "C"
                  << "XC" << "L" << "XL" << "X" << "IX"
                  << "V" << "IV" << "I";

    curValue = value;
    while (curValue > 0) {

        // find index of highest value
        for (int i = 0; (curValue < values.at(i)); i++)
            index = i + 1;

        // reduce by highest value, add roman numeral to set
        curValue -= values.at(index);
        rtnNumerals += romanNumerals.at(index);
    }

    return rtnNumerals;
}

// signif cost (0.11%)
QString c_Config::capWords(QString string)
{
    QString build;
    bool b = false; // word bound (space delim rule)

    // traverse string from left to right
    for (int i = 0; i < string.size(); i++) {
        if (b) {
            // look for space to reset bound
            if (string.at(i) == QChar(' '))  {
                b = false;
            }
            build += string.at(i); // case-irrelavent, possible spc
        }
        else
        {
            // look for word to set bound
            if (string.at(i) != QChar(' ')) {
                b = true;
                build += string.at(i).toUpper(); // upper first char
            }
            else
            {
                // spaces here - add
                build += string.at(i);
            }
        }
    }
    return build;
}


QString c_Config::sufPlural(QString string)
{
    QString s = string.toLower(); // lc all chars

    if (s.endsWith(QString("y")) )
        return QString (string.mid(0,string.length()-1) + "ies");
    else if (s.endsWith(QString("us")) )
      return QString (string.mid(0,string.length()-2) + "i");
    else if (s.endsWith(QString("ch")) || s.endsWith(QString("x")) ||\
             s.endsWith(QString("s")) || s.endsWith(QString("sh")) )
      return string + QString("es");
    else if (s.endsWith(QString("f")) )
      return QString (string.mid(0,string.length()-1) + "ves");
    else if ( s.endsWith(QString("man")) )
      return QString (string.mid(0,string.length()-2) + "en");
    else return string + QString("s");
}

QString c_Config::Indefinite(QString string)
{
    QString s = string.toLower(); // lc all chars
    QString rtn;
    if (
            s.left(1) == QString("a") ||\
            s.left(1) == QString("e") ||\
            s.left(1) == QString("i") ||\
            s.left(1) == QString("o") ||\
            s.left(1) == QString("u")
       )
        rtn = "an " + string;
    else rtn= "a " + string;
    return rtn;
}

int c_Config::fnPercent(int value, int percent) {
    //if ((percent >0) && (percent <= 100))
        return (int)((float)value * ( (float)percent / 100.0 ) );
    //else
    //    return 0;
}

int c_Config::fnPercentOf(int value, int of) {
        return (int)( ((float)value / (float)of) * 100.0 ) ;
}

unsigned long long int c_Config::fnPercentOf(unsigned long long int value, unsigned long long int of)
{
    return (unsigned long long int)( ((double)value / (double)of) * 100.0 );
}


// signif cost (0.02%)
int c_Config::fnRandTop(int value, int percent) {

    // sanity
    if (value < 2) return 0 ;

    int p  = c_Config::fnPercent(value, percent);
    int rp = c_Config::fnPercent(value, 100 - percent);
    return rand() % p + rp;
}

// signif cost (0.04%)
QString c_Config::fnInterpStr(QString pattern, QString interpolation)
{
    /*
      This takes patterns such as "* whatever" and converts the '*'
      into the interpolation string
      */
    QStringList tmp;
    tmp = pattern.split("*");

    // find empty and put interp into it
    if (tmp.at(0) == "") tmp[0] = interpolation;
    else tmp[1] = interpolation;

    return tmp.at(0) + tmp.at(1);
}

