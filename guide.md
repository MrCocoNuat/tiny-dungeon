# Tiny Dungeon - the Complete Guide

Venture into the depths of the Dungeon for its ultimate prize, the Amulet of Yendor.

## Core Mechanics

### You Only Live Once
Many hopeful warriors who entered the Dungeon have never been heard from again. Many more will likely follow. Permadeath doesn't give second chances to anyone - if the adventurer's health points drop to 0, the game is over, and all that is left is for the next in line to try.

Monsters operate on the same principle, but seeing as there are so many more of them, they surely don't mind.

### The Future is Unpredictable
There's no telling what the Dungeon hides in its bowels. Sometimes, an abundance of equipment and resources will lie waiting to be used, other times it will seem as if nothing but monsters roam the halls. It's all a little random, and no two Dungeons will play quite the same.

This randomness extends to the adventurer's time in combat as well. Most monsters and the adventurer themself have some unpredictability built into their statistics. A weapon that deals `ATK: 1-5` will usually strike for 3, but could graze for just 1 or hit a soft spot for 5.
```
x ~ TRIANGLE(min,max)
```
That an attack will land true is not guaranteed either. Depending on the assailant's Accuracy and target's Evasion, the hit rate can vary greatly.

```
p(HIT) = (ACC - EVA)/100
```
The most important way an adventurer can bend the odds in their favor is the element of surprise. Against a monster that doesn't see the adventurer coming, an attack will always hit.


### Self-Improvement
Entering the Dungeon is a adventurer at Level 1. If fortune wills it, exiting triumphantly will be a veteran at level 10. Slaying monsters provides invaluable experience points, directly improving the adventurer's stats, while avoiding monsters and sneaking around will deny this, putting them in future peril.
```
HP: 30 +5/LEVEL
EVA: 15 + 3/LEVEL
ACC: +3/LEVEL
```

### Inventory
While carrying all the loot an adventurer can find would doubtless increase their change of success, there is a limit to how much gear one can be burdened with before no longer being able to move. There are 8 inventory slots able to carry 1 item each as well as 2 additional slots representing the current equipped melee weapon and armor.

### Equipment and Strength
The adventurer starts with a basic set composed of a Worn Shortsword and Comfy Shirt. These provide some `ATK` and `DEF` respectively, but are woefully underpowered for anything past the first floors of the Dungeon. More powerful gear can be found within, but usually is more difficult to use and so requires more strength. Potions of Strength are the only way to develop this inside the Dungeon and should be carefully scouted for, as insufficient strength to wield a weapon or wear armor will result in serious penalties - weapons lose massive amounts of Accuracy and their wielder becomes incapable of leveraging surprise, and armor carries a large Speed penalty.
```
EFF: ACC -30/(STR difference) NO SURPRISE ATTACK
EFF: SPD -0.1/(STR difference)
```

### Sticks and Stones
Damage comes in two forms in this dungeon. Physical damage is resisted by Defense on a point-for-point basis.
```
DMG = ATK - DEF
```
Magical damage, however, has no effective mitigation and so will always be taken in full. It is usually extremely accurate as well, as aiming a wand is much simpler than throwing a spear. Magic has its downsides though - wands can run out of charges at inopportune times, and monsters usually don't know how to use their magical attacks up close.
```
DMG = ATKMAG
```

### Range, Distance, and Vision
Weapons can have a range greater than `1`, in which case they are able to hit at a distance. The same applies to attacks from monsters. All ranges and distances are calculated with the Chebyshev metric - think of a king moving on a chessboard.

However, certain terrain features like doors or walls can block attacks from passing through them. Other features, like tall grass, will not stop attacks, but will still interrupt vision. This is the main opportunity to inflict surprise attacks - doors are especially powerful here because you can close them after you pass, and an enemy immediately following you will not be able to tell you are about to attack them!

### Upgrades
Magical Scrolls of Upgrade are found throughout the Dungeon and directly increase the power of equipment, as well as making them easier to use by lowering their strength requirements. Upgradable equipment can be improved up to +8.
```
STR/UPGRADE: +1 -> -1, +3 -> -2, +5 -> -3, +8 -> -4
````

### Hunger and Speed
Normally when well fed, wounds will slowly heal as the adventurer's body repairs itself. This happens per turn, and most actions taken by either the adventurer or a player take 1 turn, like attacking in combat or using an item. The main exception is movement, which will depend on a runner's Speed.

```
EFF: HEAL 0.1/TURN
```
However, eventually this state of satiety ceases to be, and no adventurer can continue exploring on an empty stomach for long. When satiety declines to 0, starvation takes over and slowly causes damage instead.
```
EFF: HARM MAXHP*0.01/TURN
```
But the smart adventurer knows that when health is already high there is no reason to keep well fed, and starving for a while is a effective way to stretch out meager supplies of food.

## The Dungeon

### Regions

#### City Sewers (1-4)
The nearest floors of the Dungeon were repurposed into sewers to serve the bustling city. The looming threat of monsters wafts up along with the stench, but only faintly.

#### Barren Mines (5-8)
In the old times, the citizens of the city extracted bounties of gold from the earth here. But now, the growing presence of monsters has made this place far too dangerous, and in any case there's no gold left to mine.

#### Demon Halls (9-13)
Something horrible must have happened here in the depths from which none have ever returned, the walls seem of flesh and the air smells of searing iron. Everything about this hell screams silent madness...

## Bestiary

#### City Sewers

##### Marsupial Rat
Common denizens of the sewers that are weak on their own, but in their usual swarms they can become quite threatening.
```
HP: 8
DEF: 0-1
EVA: 10
ATK: 1-5 ACC: 85
```
##### Sewer Snake
These slithery creatures are very difficult to pin down and strike.
```
HP: 4
DEF: 0
EVA: 85
ATK: 1-4 ACC: 95
```

##### Foul Gnoll
Hyena-like humanoids, they either fight up close with their claws or at range with salvaged stones
```
HP: 12
DEF: 2-4
EVA: 10
ATK1: 2-5 ACC: 85
ATK2: 1-4 ACC: 75 RNG: 3
```

##### Armored Crab
Wicked fast on their 8 legs and covered in shells as tough as common iron.
```
HP: 16
EVA: 10
DEF: 2-5
SPD: 2
ATK: 4-6 ACC: 80
```

##### Dark Goo
A somehow intelligent conglomeration of sewer filth and sewer magic. Occasionally, it charges up a powerful arcane blast that can easily take an adventurer by surprise.
```
HP: 60
EVA: 20
DEF: 1-4
ATK1: 3-7 ACC: 95
ATK2: 15-20MAG ACC: 125 RNG: 2 CHRG: 1
```

#### Barren Mines

##### Skeleton
Bones of an unlucky soul from ages past, they hound the living with an unreal vengeance. After dying, their bones explode into sharp fragments, rending everything nearby.
```
HP: 30
EVA: 25
DEF: 2-5
ATK1: 3-6 ACC: 85
ATK2: 4-7 ACC: 100 RNG: 1
```

##### Necromancer
Enterprising wizards that have learned to bend the local skeletons to their bidding, these fearsome ghouls boost the attack power of nearby skeletons significantly.
```
HP: 24
EVA: 20
DEF: 0-4
ATK: 3-6MAG ACC: 130 RNG: 2-3
EFF: Skeleton ATK*1.5 RNG: 3
```

##### Vampire Bat
Bloodsucking beasts far larger than their natural cousins, they sport fangs to match and heal for themselves any damage they deal.
```
HP: 28
EVA: 45
DEF: 0-3
SPD: 2
ATK: 4-7DRAIN ACC: 100
```

##### Lithic Golem
A mine's guard long past its last maintenance, this magical creation has lost all control of itself and now survives only to destroy any threats.
```
HP: 144
EVA: 15
DEF: 5-12
ATK: 8-15 ACC: 120
SPD: 0.5
```

#### Demon Halls

##### Dread Ripper
The most common form of demons, they skillfully shred armor and adventurer alike with their claws.
```
HP: 60
EVA: 20
DEF: 4-8
ATK: 8-12 ACC: 105
```

##### Scorpio
Horrific half-imitations of the more familiar arthropod, their stingers instead fire spines from range. They seemingly don't know how to use them up close though.
```
HP: 48
EVA: 40
DEF: 3-7
ATK: 9-14 RNG: 2-4
```

##### Evil Eye
These unspeakable nightmares singlemindedly prowl the depths for targets. When found, they adopt a defensive stance and charge up a beam of pure disintegration that harms both friend and foe - taking cover is highly advised.
```
HP: 80
EVA: 30
DEF: 2-5
ATK1: 6-10 ACC: 130
ATK2: 18-30MAG ACC: 120 CHRG: 3 RNG: 99 DEF: +10-15
```

##### Yog-Dzewa
A dark god that exists outside of our mortal plane, the wretched eye at the bottom of the Dungeon is but its first foothold of manifestation here. Beat it back with all your fury so that it never sees fit to invade this realm again!
```
HP: 256
EVA: 20
DEF: 4-10
ATK1: 6-14MAG ACC: 140 RNG: 7
ATK2: 3-8MAG CHRG: 1 ACC: 145 RNG: 99
SPD: 0
EFF: Yog's Fist INVULNERABLE RNG: 5
```

##### Yog's Fist
Aspects of Yog-Dzewa's power emanating from its eye, these ferocious apparitions are deployed to hunt interlopers down. Worse, they become fully cloaked in the dark energy of Yog and are therefore invulnerable when nearby.
```
HP: 128
EVA: 10
DEF: 5-12
ATK: 9-19 ACC: 125
```

#### Ubiquitous

##### Mimic
Too many an adventurer has been lured by the false promise of riches, drawn towards this casket richly decorated with gold trim and sharp teeth.
```
HP: 4*FLOOR
EVA: 3*FLOOR
DEF: (0.4-0.8)*FLOOR
ATK: (0.5-1)*FLOOR ACC: 120
```

## Tools of the Trade

### Weapons

#### Melee

##### Worn Shortsword
Although it has seen better days, in the hands of a seasoned adventurer this can certainly do some damage.
```
ATK: 1-6 +1-1/UPGRADE ACC: 110
STR: 10
```
##### Broadsword
An old reliable slab of steel is the armament of choice for many an adventurer.
```
ATK: 6-14 +1-3/UPGRADE ACC: 105
STR: 14
```
##### Longsword
Storied tradition underlies this exquisite blade surely crafted and maintained with the utmost of care, and its performance shows.
```
ATK: 11-20 +1-4/UPGRADE ACC: 100
STR: 16
```

##### Greataxe
When wielded with sufficient strength, this ridiculously titanic weapon produces crushing yet graceful swings belying its hundred-kilogram heft.
```
ATK: 15-26 +1-5/UPGRADE ACC: 95
STR: 18
```

#### Ranged

##### Fine Wand
Sorcery is still a young science, but a simple magical bolt can be understood and casted by pretty much anyone nowadays with the appropriate equipment.
```
ATK: 8-12MAG +2-4/UPGRADE RNG: 99
CHARGES: 3 +1/UPGRADE
CHRG: 0.05/TURN +0.03/TURN/UPGRADE
```

##### Throwing Knife
Well-balanced and quick to toss, these knives are a classic choice of adventurers everywhere. Up to 4 can be carried in a single stack.
```
ATK: 4-12 RNG: 99
STR: 11
```

##### Bident
A glorified large fork, but still proof of the old wisdom that two tines are better than one. Up to 4 can be carried in a single stack.
```
ATK: 8-18 RNG: 99
STR: 15
```

### Armor
Your shield against the dangers of the Dungeon, armor helps to mitigate physical damage points received. However, it is entirely useless against any form of magical power.

##### Comfy Shirt
Your favorite, but probably not the best gear for exploring the Dungeon.
```
DEF: 1-1 +1-1/UPGRADE
STR: 10
```

##### Leather Armor
Sturdy tanned leather provides decent protection from blows.
```
DEF: 2-4 +1-2/UPGRADE
STR: 12
```

##### Chain Mail
Linked metal rings effectively trap blades and projectiles for strong protection.
```
DEF: 3-7 +2-3/UPGRADE
STR: 14
```

##### Plate Mail
A full encasing inside thick steel provides the ultimate in protection from the outside world.
```
DEF: 4-10 +3-4/UPGRADE
STR: 16
```

### Scrolls

#### Scroll of Upgrade
Some divine fortune must have left these scattered across the Dungeon, as if to give any adventurer brave enough to enter a fair shot at claiming its prize. Each scroll can infuse a piece of equipment with just the thing it needs to power it up and even decrease its strength requirement. *Exactly one is guaranteed to appear on each ordinary floor.*
```
STR/UPGRADE: +1 -> -1, +3 -> -2, +5 -> -3, +8 -> -4
````

#### Scroll of Rage
The roaring incantation on this scroll warps the mind of monsters that hear it. Anyone in earshot will be driven amok and begin attacking targets without regard for allegiance, and anyone else will instead be drawn to this location by the havoc.
```
DURATION: 20
```

#### Scroll of Terror
The shriek recorded on this scroll instills incredible fear into monsters that hear it, causing them to try to flee from its source as fast as possible. Pain from taking damage will shorten the duration of this fear, though.
```
DURATION: 20
```

#### Scroll of Recharging
The raw energy bound in this scroll, when unleashed, rapidly restores the charge of the user's wands. If there are no wands at less than full charge, the energy instead accumulates around the user, shielding them from magical damage.
```
EFF1: CHARGE EVERY WAND 0.25/TURN DURATION: 20
EFF2: SHIELD HPMAX*0.3
```

### Potions

#### Potion of Strength
Some divine fortune must have left these scattered across the Dungeon, as if to give any adventurer brave enough to enter a fair shot at claiming its prize. Each bottle of this potent brew empowers your muscles with strength, as if you had trained with them for years. *Two are guaranteed to appear in each region.*
```
EFF: STR+1
```

#### Potion of Healing
A magical remedy that closes wounds and leaves you feeling as if you just woke up, this can instantly restore a large quantity of health points. Alternatively, thrown at an undead enemy, it can corrode their unnatural bodies for significant damage as well.
```
EFF: HEAL HPMAX*0.7
EFF: HARM 4*FLOOR
```

#### Potion of Invisibility
A curious draught that causes its drinker to become undetectable by monsters for a short time. Attacking a monster will immediately nullify this effect, though.
```
DURATION: 20
```

#### Potion of Haste
An sweet and sticky brew that causes its drinker to be able to run at tremendous speed for a quick duration. Throwing it at a monster will instead bind their body parts together, inhibiting their movement.
```
EFF1: SPD*3 DURATION: 20
EFF2: SPD*0.5 DURATION: 20
```

### Food
#### Meat Pie
It sure tastes good, but who knows how this got down here, or worse, what it's made of? *One is guaranteed to appear on each ordinary floor*.
```
EFF: SATIETY+80
```

#### Suspicious Drumstick
This came off of a monster expertly butchered by expert bladework. *Can only drop when*
```
EFF: SATIETY+10
EFF: HEAL 1*FLOOR
```