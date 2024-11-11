#include "game_config.hxx"

Game_config::Game_config()
        : scene_dims {624, 368},
          floor_dims({624,150}),
          floor_2_dims({624, 100}),
          floor_3_dims({270,150}),
          floor_4_dims({270,100}),
          floor_5_dims({scene_dims.width - 2*floor_3_dims.width, floor_3_dims
          .height}),
          floor_6_dims({scene_dims.width - 2*floor_3_dims.width, floor_4_dims
          .height}),
          platform_dims({scene_dims.width/5, 20}),
          ladder_dims({40, 106}),
          background_dims({624, scene_dims.height - floor_dims.height}),
          lose_dims({scene_dims.width, scene_dims.height}),
          win_dims({scene_dims.width, scene_dims.height}),
          log_dims({32, 40}),
          alligator_dims({50,19}),
          floor(0,scene_dims.height - 150, floor_dims.width, floor_dims.height),
          floor_2(0, scene_dims.height - 100, floor_2_dims.width, floor_2_dims
          .height),
          floor_3(0,scene_dims.height - 150, floor_3_dims.width, floor_3_dims
          .height),
          floor_4(0,scene_dims.height - 100, floor_4_dims.width, floor_4_dims
          .height),
          floor_5(floor_3_dims.width*2, scene_dims.height - 150, floor_5_dims
          .width, floor_5_dims.height),
          floor_6(floor_3_dims.width*2, scene_dims.height - 100, floor_5_dims
                  .width, floor_5_dims.height),
                  ladder(floor_3_dims.width/2, floor_3_dims
                  .height - ladder_dims.height/3, ladder_dims.width, ladder_dims
                  .height),
          platform(ladder.x + ladder_dims.width, ladder.y, platform_dims
          .width, platform_dims.height),
          background(0, 0, background_dims.width, background_dims.height),
          lose(0, 0, lose_dims.width, lose_dims.height),
          win(0, 0, win_dims.width, win_dims.height),
          alligator_block(floor_3_dims.width + 100, scene_dims.height -
          3*floor_3_dims.height/4,
                          alligator_dims
          .width, alligator_dims.height),
          alligator_block_2(alligator_block.x + 100, alligator_block.y,
                            alligator_dims.width, alligator_dims.height),
          player_velocity_0 {0, 50},
          filename_player("harry.png"),
          filename_log("log_sprite.png"),
          filename_alligator_open("alligator_sprite.png"),
          filename_alligator_closed("alligator_closed.png"),
          filename_ladder("ladder.png"),
          filename_alligator_lose_screen("alligator_lose_screen.jpg"),
          filename_cat_win("cat_sprite.png"),
          log_velocity {-150, 0},
          pos_displacement(60)

{ }


