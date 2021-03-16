#include <gb/gb.h>
#include <stdio.h>
#include "GameCharacter.c"
#include "GameSprites.c"

#define SPRITE_SIZE 8

GameCharacter ship;
GameCharacter bug;

void performantdelay(UINT8 numloops){
    for(UINT8 i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void movegamecharacter(GameCharacter* character, UINT8 x, UINT8 y){
    // implies that four tiles from the value of tile_start and up are for the same meta sprite
    // and are arranged clockwise, starting from the top left 8x8 quadrant
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + SPRITE_SIZE, y);
    move_sprite(character->spritids[2], x, y + SPRITE_SIZE);
    move_sprite(character->spritids[3], x + SPRITE_SIZE, y + SPRITE_SIZE);
}

void setup_GameCharacter(GameCharacter* character, UINT8 x_position, UINT8 y_position, UINT8 tile_start){
    character->x = x_position;
    character->y = y_position;

    // load sprites for sprite
    // starts reading from tile_start and increments up by one to retrieve sprite ids
    for(UINT8 i=0; i<4; i++) {
		set_sprite_tile(tile_start, tile_start);
        character->spritids[i] = tile_start;

        tile_start++;
	}

    movegamecharacter(character, character->x, character->y);
}

void main(){
    set_sprite_data(0, 8, GameSprites);

    setup_GameCharacter(&ship, 80, 130, 0);
    setup_GameCharacter(&bug, 30, 0, 4);

    SHOW_SPRITES;
    DISPLAY_ON;

    while(1){
       if(joypad() & J_LEFT){
           ship.x -= 2;
           movegamecharacter(&ship, ship.x, ship.y);
       }
       if(joypad() & J_RIGHT){
           ship.x += 2;
           movegamecharacter(&ship, ship.x, ship.y);
       }

       bug.y += 5;

       if(bug.y >= 144){
           bug.y=0;
           bug.x = ship.x;
       }

       movegamecharacter(&bug,bug.x,bug.y);

       performantdelay(5);      
    }
}
