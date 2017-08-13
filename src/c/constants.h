#ifndef CONSTANTS_H
#define CONSTANTS_H

#define CONST_TILE_SIZE    10
#define CONST_FONT_SIZE     5
#define CONST_TOTAL_BLOCKS 25
#define CONST_FONT_W       50
#define CONST_TILES_X     110
#define CONST_TILES_Y      20

#ifdef PBL_RECT
#define CONST_ORIGIN_X 17
#define CONST_ORIGIN_Y 15
#else
#define CONST_ORIGIN_X 35
#define CONST_ORIGIN_Y 22
#endif

#ifdef PBL_ROUND
#define CONST_NUM_SLOTS 18
#else
#define CONST_NUM_SLOTS 8
#endif

#endif /* end of include guard: CONSTANTS_H */
