
//{{BLOCK(bg)

//======================================================================
//
//	bg, 256x256@8,
//	+ palette 256 entries, not compressed
//	+ 158 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32
//	Total size: 512 + 10112 + 2048 = 12672
//
//	Time-stamp: 2011-11-20, 19:36:15
//	Exported by Cearn's GBA Image Transmogrifier
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef __BG__
#define __BG__

#define bgTilesLen 10112
extern const unsigned short bgTiles[5056];

#define bgMapLen 2048
extern const unsigned short bgMap[1024];

#define bgPalLen 512
extern const unsigned short bgPal[256];

#endif // __BG__

//}}BLOCK(bg)
