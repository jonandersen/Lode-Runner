
//{{BLOCK(sprite)

//======================================================================
//
//	sprite, 256x128@8, 
//	+ palette 256 entries, not compressed
//	+ 512 tiles not compressed
//	Total size: 512 + 32768 = 33280
//
//	Time-stamp: 2011-11-22, 12:33:34
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SPRITE_H
#define GRIT_SPRITE_H

#define spriteTilesLen 16384
extern const unsigned short spriteTiles[8192];

#define spritePalLen 512
extern const unsigned short spritePal[256];


#define PLAYER_NORMAL 0
#define PLAYER_WALK S_O_8(12,0)
#define PLAYER_WALK_STEPS 5

#define ENEMY_NORMAL S_O_8(8,4);
#define ENEMY_FALL S_O_8(8,20);
#define ENEMY_WALK_STEPS 4


#endif // GRIT_SPRITE_H

//}}BLOCK(sprite)
