#include <gb/gb.h>

//generical character structure: id, position, graphics
typedef struct {
	UBYTE spritids[4]; // all characters use 4 sprites
	UINT8 x;
	UINT8 y;
} GameCharacter;
