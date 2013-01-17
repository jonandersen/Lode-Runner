
//{{BLOCK(bg1)

//======================================================================
//
//	bg1, 512x256@8, 
//	+ palette 256 entries, not compressed
//	+ 2036 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 130304 + 4096 = 134912
//
//	Time-stamp: 2011-11-19, 21:58:54
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BG1_H
#define GRIT_BG1_H

#define bg1TilesLen 130304
extern const unsigned short bg1Tiles[65152];

#define bg1MapLen 4096
extern const unsigned short bg1Map[2048];

#define bg1PalLen 512
extern const unsigned short bg1Pal[256];

#endif // GRIT_BG1_H

//}}BLOCK(bg1)
