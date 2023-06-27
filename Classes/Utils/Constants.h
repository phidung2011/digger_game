//
//  Constants.h
//  gamebase
//
//  Created by NGOCDIEP on 4/20/15.
//
//

//---Define Post NotificationCenter
//---Define Background
//---Define Logo
//---Define FONT
//---Define UI
//---Define Text
//---Define Data
//---Define Other

#ifndef gamebase_Constants_h
#define gamebase_Constants_h

//--------------------Define FONT--------------------
#define FONT_PATH_BUBBLEGUM "fonts/Bubblegum.ttf"
#define FONT_PATH_GROBOLD "fonts/GROBOLD.ttf"
//--------------------*********--------------------


//UI BTN STRING
#define NOTI_START_GAME "NOTI_START_GAME"
#define NOTI_TOPSCORE_GAME "NOTI_TOPSCORE_GAME"
#define NOTI_SHOP_GAME "NOTI_SHOP_GAME"
#define NOTI_UPDATE_GAME "NOTI_UPDATE_GAME"
#define NOTI_SETTING_GAME "NOTI_SETTING_GAME"
#define NOTI_ABOUT_GAME "NOTI_ABOUT_GAME"
#define NOTI_HELP_GAME "NOTI_HELP_GAME"
#define NOTI_SHARE_FB_GAME "NOTI_SHARE_FB_GAME"
#define NOTI_SHARE_TW_GAME "NOTI_SHARE_TW_GAME"

//---------------------------------------------------

#define BGM_LAND1 "Sound/BackgroundMusic/bgm_land_1.mp3"
#define BGM_LAND2 "Sound/BackgroundMusic/bgm_land_2.mp3"
#define BGM_LAND3 "Sound/BackgroundMusic/bgm_land_3.mp3"
#define BGM_LAND4 "Sound/BackgroundMusic/bgm_land_4.mp3"
#define BGM_LAND5 "Sound/BackgroundMusic/bgm_land_5.mp3"
#define BGM_LAND "Sound/BackgroundMusic/bgm_land_%d.mp3"

#define BGM_MAIN "Sound/BackgroundMusic/bgm_main.mp3"

#define EFFECT_BOMB_1 "Sound/Effect/bomb_1.mp3"
#define EFFECT_BOMB_2 "Sound/Effect/bomb_2.mp3"
#define EFFECT_BTN "Sound/Effect/btn_1.mp3"
#define EFFECT_CHOOSE_MAP "Sound/Effect/btn_choosemap_2.mp3"
#define EFFECT_CHOOSE_MAP_PTR "Sound/Effect/btn_choosemap.mp3"
#define EFFECT_BTN_PLAY "Sound/Effect/btn_play.mp3"
#define EFFECT_CART "Sound/Effect/cart_1.mp3"
#define EFFECT_DIG_1 "Sound/Effect/dig_dirt_1.mp3"
#define EFFECT_DIG_2 "Sound/Effect/dig_dirt_2.mp3"
#define EFFECT_DIG "Sound/Effect/dig_dirt_%d.mp3"
#define EFFECT_DIG_SNOW_1 "Sound/Effect/dig_sand_snow_1.mp3"
#define EFFECT_DIG_SNOW_2 "Sound/Effect/dig_sand_snow_2.mp3"
#define EFFECT_DIG_SNOW "Sound/Effect/dig_sand_snow_%d.mp3"
#define EFFECT_GEM_1 "Sound/Effect/gem_1.mp3"
#define EFFECT_GEM_2 "Sound/Effect/gem_2.mp3"
#define EFFECT_GEM_3 "Sound/Effect/gem_3.mp3"
#define EFFECT_GET_ITEM_1 "Sound/Effect/itemget_1.mp3"
#define EFFECT_GET_ITEM_2 "Sound/Effect/itemget_2.mp3"
#define EFFECT_GET_ITEM_3 "Sound/Effect/itemget_3.mp3"
#define EFFECT_GET_ITEM_4 "Sound/Effect/itemget_4.mp3"
#define EFFECT_GET_ITEM_5 "Sound/Effect/itemget_5.mp3"
#define EFFECT_GET_ITEM_6 "Sound/Effect/itemget_6.mp3"
#define EFFECT_GET_ITEM_7 "Sound/Effect/itemget_7.mp3"
#define EFFECT_MINE_1 "Sound/Effect/mine_1.mp3"
#define EFFECT_DYNAMITE_1 "Sound/Effect/itemuse_dynomite_1.mp3"
#define EFFECT_DYNAMITE_2 "Sound/Effect/itemuse_dynomite_2.mp3"
#define EFFECT_DYNAMITE_3 "Sound/Effect/itemuse_dynomite_3.mp3"
#define EFFECT_ROCKET_1 "Sound/Effect/itemuse_rocket_1.mp3"
#define EFFECT_ROCKET_2 "Sound/Effect/itemuse_rocket_2.mp3"
#define EFFECT_DOOR "Sound/Effect/pop_teleport.mp3"
#define EFFECT_WIN "Sound/Effect/pop_win.mp3"
#define EFFECT_ROCK_1 "Sound/Effect/rock_1.mp3"
#define EFFECT_ROCK_2 "Sound/Effect/rock_2.mp3"
#define EFFECT_ROCK_3 "Sound/Effect/rock_3.mp3"
#define EFFECT_BLOCK_MOVE "Sound/Effect/ui_blockmove.mp3"
#define EFFECT_COUNT_DOWN "Sound/Effect/ui_countdown.mp3"
#define EFFECT_FAIL "Sound/Effect/ui_fail.mp3"
#define EFFECT_PAUSE "Sound/Effect/ui_pause.mp3"
#define EFFECT_QUIT "Sound/Effect/ui_quit.mp3"
#define EFFECT_READY "Sound/Effect/ui_ready.mp3"
#define EFFECT_RESTART "Sound/Effect/ui_restart.mp3"

#define SIZE_BT_LEVEL       Size(94,94) //Size cac button chon Level
#define SIZE_GRID_VIEW      Size(620,280) //Size Grid View chon Level
#define GRID_VIEW_COLUMN    5
#define GRID_VIEW_ROW       2

//Define resource (MainGameScene.cpp)
#define UI_CONTROL_BOARD    "GUI/Control/control_baseboard.png"
#define UI_CONTROL_JOYSTICK "GUI/Control/control_joystick.png"




#define UI_BTN_BOMB_NORMAL "GUI/PlayGame/btn_bomb_normal.png"
#define UI_BTN_BOMB_DISABLE "GUI/PlayGame/btn_bomb_disable.png"

#define UI_BTN_ROCKET_NORMAL "GUI/PlayGame/btn_rocket_normal.png"
#define UI_BTN_ROCKET_DISABLE "GUI/PlayGame/btn_rocket_disable.png"

#define UI_BTN_TIMEBOMB_NORMAL "GUI/PlayGame/btn_timebomb_normal.png"
#define UI_BTN_TIMEBOMB_DISABLE "GUI/PlayGame/btn_timebomb_disable.png"

#define UI_BTN_MINE_NORMAL "GUI/PlayGame/btn_mine_normal.png"
#define UI_BTN_MINE_DISABLE "GUI/PlayGame/btn_mine_disable.png"

#define UI_IMG_BAR_PLAYER "GUI/PlayGame/bar_player.png"
#define UI_IMG_BAR_MAIN "GUI/PlayGame/bar_main.png"
#define UI_IMG_BAR_ENEMIES "GUI/PlayGame/bar_enemies.png"
#define UI_IMG_BAR_DIAMONDS "GUI/PlayGame/bar_diamonds.png"

#define UI_PROGRESS_BAR_FUEL "GUI/PlayGame/progressbar_fuel.png"
#define UI_NUMBER_CIRCLE "GUI/PlayGame/number_circle.png"

#define UI_BTN_PAUSE "GUI/PlayGame/btn_pause.png"

//--------------------*********--------------------



//--------- LayerMenu.cpp ------------

#define BG_START_GAME "GUI/StartGame/bg.png"
#define BG_LAND1_START_GAME "GUI/StartGame/bg_land1.png"
#define BG_LAND2_START_GAME "GUI/StartGame/bg_land2.png"
#define UI_BTN_BACK "GUI/StartGame/btn_back.png"
#define UI_BTN_PLAYGAME "GUI/StartGame/SelectMenu/btn_play.png"
#define UI_BTN_EXIT "GUI/StartGame/SelectMenu/btn_exit.png"
#define UI_BTN_HELP "GUI/StartGame/SelectMenu/btn_help.png"
#define UI_BTN_HIGHSCORE "GUI/StartGame/SelectMenu/btn_highscore.png"
#define UI_BTN_SETTING "GUI/StartGame/SelectMenu/btn_setting.png"
#define UI_BTN_SHOP "GUI/StartGame/SelectMenu/btn_shop.png"
#define UI_BTN_SHARE_FB "GUI/StartGame/SelectMenu/btn_facebook.png"
#define UI_BTN_SHARE_TW "GUI/StartGame/SelectMenu/btn_twitter.png"
#define UI_IMG_LOGO "GUI/StartGame/SelectMenu/img_logo.png"


//--------- LayerSelectLand.cpp ------------

#define UI_IMG_MAP1 "GUI/StartGame/SelectLand/img_map1.png"
#define UI_IMG_MAP2 "GUI/StartGame/SelectLand/img_map2.png"
#define UI_IMG_MAP3 "GUI/StartGame/SelectLand/img_map3.png"
#define UI_IMG_MAP4 "GUI/StartGame/SelectLand/img_map4.png"
#define UI_IMG_MAP5 "GUI/StartGame/SelectLand/img_map5.png"
#define UI_IMG_POINTER "GUI/StartGame/SelectLand/img_pointer.png"
#define UI_IMG_SHADOW_POINTER "GUI/StartGame/img_shadow_pointer.png"
#define UI_IMG_BAR_TITLE "GUI/StartGame/SelectLand/bar_title.png"

//--------- LayerSelectLevel.cpp ------------

#define UI_IMG_LOCK "GUI/StartGame/SelectLevel/img_lock.png"
#define UI_IMG_STAR "GUI/StartGame/SelectLevel/img_star.png"
#define UI_IMG_STAR_1 "GUI/StartGame/SelectLevel/img_star_1.png"
#define UI_IMG_BG_MAP1 "GUI/StartGame/SelectLevel/img_map1.jpg"
#define UI_IMG_BG_MAP2 "GUI/StartGame/SelectLevel/img_map2.jpg"
#define UI_IMG_BG_MAP3 "GUI/StartGame/SelectLevel/img_map3.jpg"
#define UI_IMG_BG_MAP4 "GUI/StartGame/SelectLevel/img_map4.jpg"
#define UI_IMG_BG_MAP5 "GUI/StartGame/SelectLevel/img_map5.jpg"


//---------- PopupWin -------------
#define UI_BG_POPUP_WIN "GUI/PlayGame/PopupLevelComplete/bg.png"


//------popup pause-----
#define UI_BG_POPUP_PAUSE "GUI/PlayGame/PopupPause/bg.png"
#define UI_BTN "GUI/btn.png"


//Define resourc (LayerHelp.cpp)
#define UI_BG_HELP  "UI/hepl_g.png"


//--------------------Define Other--------------------
//--------------------*********--------------------

//--------------------Define ID's para Local Storage--------------------

#define USER_CONTROL_IS_JOYPAD "KEY_CONTROL_IS_JOYPAD"
#define USER_SAVE_REPLAY "KEY_REPLAY_NUMBER_%d"
#define USER_PLAYER_SELECTED "KEY_PLAYER_SELECTED"
#define USER_MAX_SCORE "KEY_MAX_SCORE"
#define USER_TOTAL_GAMES_PLAYED "KEY_TOTAL_GAMES_PLAYED"
#define USER_TOTAL_SCORE "KEY_TOTAL_SCORE"
#define USER_SCORE_IN_LEVEL "KEY_SCORE_LEVEL_%d"
#define USER_OBSTACLES_JUMPED "KEY_OBSTACLES_JUMPED"
#define USER_MANAGE_MUSIC "KEY_MUSIC"
#define USER_TUTORIAL "KEY_TUTORIAL_%d"

#define USER_DATA "userData"
#define USER_SCORE "scores"
#define USER_COIN "coins"
#define USER_REMOVE_ADS "removeAds"

#define ROCKET_PRICE 150
#define BOMB_PRICE 75
#define MINE_PRICE 50
#define TIMEBOMB_PRICE 100

#endif

