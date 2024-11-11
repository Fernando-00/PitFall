#include "model.hxx"


Model::Model(Game_config const& config)
        : config(config),
          floor(Block::from_top_left({config.floor.x, config.floor.y}, config
          .floor_dims)),
          floor_2(Block::from_top_left({config.floor_2.x, config.floor_2.y},
                                       config.floor_2_dims)),
           floor_3(Block::from_top_left({config.floor_3.x, config.floor_3.y},
                                       config.floor_3_dims)),
          floor_4(Block::from_top_left({config.floor_4.x, config.floor_4.y},
                                       config.floor_4_dims)),
          floor_5(Block::from_top_left({config.floor_5.x, config.floor_5.y},
                                       config.floor_5_dims)),
          floor_6(Block::from_top_left({config.floor_6.x, config.floor_6.y},
                                       config.floor_6_dims)),
          background(Block::from_top_left({config.background.x, config
                  .background.y}, config.background_dims)),
          lose(Block::from_top_left({config.lose.x, config.lose.y},
                                    config.lose_dims)),
                                    win(Block::from_top_left({config.win.x,
                                                              config.win.y},
                                                              config
                                                              .win_dims)),
          alligator_block(
                  config.alligator_block.x,
                   config.alligator_block.y,config.alligator_dims.width,
                   config
                   .alligator_dims.height),
          alligator_block_2(config.alligator_block_2.x,
                            config.alligator_block_2.y,
                            config.alligator_dims.width,
                            config.alligator_dims.height),
          log_block(floor.width, floor.y + 20, config.floor_dims.width,
                    config.floor_dims.height),
          ladder(config.ladder.x, config.ladder.y, config.ladder_dims.width,
                    config.ladder_dims.height),
          platform(Block::from_top_left({config.platform.x, config.platform
          .y}, config.platform_dims)),
          player(floor, config),
          log(log_block, config),
          alligator(alligator_block,config),
          alligator_2(alligator_block_2, config),
          water(alligator_block,config),
          state(0),
          lives(3),
          alligator_counter(0),
          alligator_open(false)

{

}

void
Model::on_frame(double dt)
{

    Player next_player = player.next(dt);
    Obstacles next_log = log.next(dt);
    Obstacles next_alligator = alligator.next(dt);
    Obstacles next_alligator_2 = alligator_2.next(dt);

    if (next_player.hits_right(config))
    {
        player.velocity.width = 0;
        state += 1;
        player.center = player.initial_spawn;
    }

    if (next_player.hits_left(config))
    {
        player.velocity.width = 0;
    }

    if (state == 0)
    {

        if (next_player.hits_floor(floor))
        {
            player.velocity.height = 0;
        }

        if(!next_player.hits_floor(floor))
        {
            player.velocity.height = 100;
        }
        if (next_log.log_hits_left(config.log_dims))
        {
            log.log_center = log.spawn_point_log;
        }

        if(next_log.hits_player(player, config.log_dims))
        {
            if(next_player.jumping_up)
            {
                player.jumping_up = false;
                player.jumping_down = true;
            }
            player.velocity.width = 0;
        }


    }

    if(state == 1)
    {
        alligator_counter += 1;

        if (next_player.hits_floor(floor_3) || next_player.hits_floor(floor_5))
        {
            player.velocity.height = 0;
        }


        if(!next_player.hits_floor(floor_3) && !next_player.hits_floor(floor_5))
        {
            player.velocity.height = 100;
        }

        // When player falls in the water
        if(next_player.center.y > floor_3.y + player.player_dims.height)
        {
            player.center = player.initial_spawn;
            lives -= 1;
        }

        if(next_alligator.hits_player(player, config.alligator_dims) )
        {
            player.velocity.height = 0;
            if(alligator_open)
            {
                lives-=1;
                player.center = player.initial_spawn;
            }
        }

        if(next_alligator_2.hits_player(player, config.alligator_dims) )
        {
            player.velocity.height = 0;
            if(alligator_open)
            {
                lives-=1;
                player.center = player.initial_spawn;
            }
        }

        if (alligator_counter >= 120)
        {
            alligator_open = true;
        }

        if (alligator_counter == 240)
        {
            alligator_counter = 0;
            alligator_open = false;
        }

        if (next_log.log_hits_left(config.log_dims))
        {
            log.log_center = log.spawn_point_log;
        }

        if(next_log.hits_player(player, config.log_dims))
        {
            if(next_player.jumping_up)
            {
                player.jumping_up = false;
                player.jumping_down = true;
            }
            player.velocity.width = 0;
        }


    }

    if(state == 2)
    {

        alligator_counter += 1;

        if (next_player.hits_floor(floor_3) ||
            next_player.hits_floor(floor_5) ||
            next_player.hits_floor(platform))
        {
           player.velocity.height = 0;
        }
        if (next_player.hits_floor(floor_4) )
        {
            player.velocity.width = 0;
            player.velocity.height = 100;
        }


        if(!next_player.hits_floor(floor_3) && !next_player.on_ladder &&
        !next_player.hits_floor(platform) && !next_player.hits_floor(floor_5))
        {
            player.velocity.height = 100;
        }


        if(next_player.near_ladder(ladder) && !player.jumping_up)
        {
            player.on_ladder = true;
        }

        if(!next_player.near_ladder(ladder))
        {
            player.on_ladder = false;

        }


        // When player falls in the water
        if(next_player.center.y > floor_3.y + player.player_dims.height)
        {
            player.center = player.initial_spawn;
            lives -= 1;
        }

        if(next_alligator.hits_player(player, config.alligator_dims) )
        {
            player.velocity.height = 0;
            if(alligator_open)
            {
                lives-=1;
                player.center = player.initial_spawn;
            }
        }

        if(next_alligator_2.hits_player(player, config.alligator_dims))
        {
            player.velocity.height = 0;
            if(alligator_open)
            {
                lives-=1;
                player.center = player.initial_spawn;
            }
        }

        if (alligator_counter >= 120)
        {
            alligator_open = true;
        }

        if (alligator_counter == 240)
        {
            alligator_counter = 0;
            alligator_open = false;
        }

        if (next_log.log_hits_left(config.log_dims))
        {
            log.log_center = log.spawn_point_log;
        }

        if(next_log.hits_player(player, config.log_dims))
        {
            if(next_player.jumping_up)
            {
                player.jumping_up = false;
                player.jumping_down = true;
            }
            player.velocity.width = 0;
        }

    }

    //------------------------------------------------------------------------

    if(next_player.jumping_up)
    {

        player.counter += 1;
        player.jump_up(player.counter);

    }

    player = player.next(dt);
    log = log.next(dt);

    return;

}
