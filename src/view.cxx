#include "view.hxx"
#include "model.hxx"




// Colors are red-green-blue(-alpha), each component
// from 0 to 255.
static ge211::Color const player_color {0, 100, 0};
static ge211::Color const floor_color {199, 199, 52};
static ge211::Color const floor_2_color {132, 142, 43};
static ge211::Color const water_color {48, 131, 159};
static ge211::Color const water_2_color {0, 30, 170};
static ge211::Color const background_color {52, 124, 44};
static ge211::Color const black {0, 0, 0};

///
/// VIEW CONSTRUCTOR
///


View::View(Model const& m)
        : model(m),
          floor_sprite(m.floor.dimensions(), floor_color),
          floor_2_sprite(m.floor_2.dimensions(), floor_2_color),
          floor_3_sprite(m.floor_3.dimensions(),
                         floor_color),
          floor_4_sprite(m.floor_4.dimensions(), floor_2_color),
          floor_5_sprite(m.floor_5.dimensions(),
                         floor_color),
          floor_6_sprite(m.floor_6.dimensions(), floor_2_color),
          background_sprite(m.background.dimensions(), background_color),
          sprite_log(m.config.filename_log),
          sprite_alligator_open(m.config.filename_alligator_open),
          sprite_alligator_closed(m.config.filename_alligator_closed),
          ladder_sprite(m.config.filename_ladder),
          alligator_lose_screen(m.config.filename_alligator_lose_screen),
          cat_sprite(m.config.filename_cat_win),
          sprite_water(m.floor_3.dimensions(),
                         water_color),
          sprite_water_2(m.floor_4.dimensions(), water_2_color),
          platform_sprite(m.platform.dimensions(), floor_color),
          sprite_displacement(74, 63),
          log_displacement(16, 20),
          gator_displacement(40, 20),
          ladder_displacement(25, 53)

{ }

void
View::draw(ge211::Sprite_set& set)
{
    // Lives display
    ge211::Text_sprite::Builder explain_builder(sans28_);
    explain_builder.color(ge211::Color(0xFF, 0xFF, 0xFF));

    ge211::Text_sprite::Builder win_builder(sans28_);
    win_builder.color(ge211::Color(0, 0, 0));

    if (model.lives > 0 && model.state != 3)
    {
        explain_builder << "Lives : "
                        << (int) model.lives;

        lives_display.reconfigure(explain_builder);
        set.add_sprite(lives_display, {50, 20}, 10);
    }

    if (model.lives <= 0)
    {
        explain_builder << "YOU LOSE";

        lives_display.reconfigure(explain_builder);
        set.add_sprite(lives_display, {model.config.scene_dims.width/3, model
        .config.scene_dims.height/3}, 10);

        set.add_sprite(alligator_lose_screen, {60, 0}, 10);
    }




    // First Level with log that stuns player if hit
    if(model.state == 0)
    {
        set.add_sprite(model.player.sprite_, model.player.top_left()
        .into<int>() - sprite_displacement, 9);

        set.add_sprite(floor_sprite,  {model.floor.x, model.floor.y}, 1);

        set.add_sprite(floor_2_sprite, {model.floor_2.x, model.floor_2.y}, 2);

        set.add_sprite(sprite_log, model.log.log_center.into<int>() -
                log_displacement, 3);

        set.add_sprite(background_sprite, {model.background.x, model
        .background.y}, 0);

    }

    // Level 2 with water, alligators, and a log
    if(model.state == 1 && model.lives != 0)
    {

        set.add_sprite(model.player.sprite_, model.player.top_left()
                                                  .into<int>() -
                                                          sprite_displacement, 9);

        set.add_sprite(floor_3_sprite,
                       {model.floor_3.x, model.floor_3.y}, 0);

        set.add_sprite(floor_4_sprite,
                       {model.floor_4.x, model.floor_4.y}, 1);

        set.add_sprite(floor_5_sprite,
                       {model.floor_5.x, model.floor_5.y}, 0);

        set.add_sprite(floor_6_sprite,
                       {model.floor_6.x, model.floor_6.y}, 1);

        set.add_sprite(sprite_log, model.log.log_center.into<int>() -
                                   log_displacement, 3);

        set.add_sprite(sprite_water,
                       {model.floor_3.width, model.floor_3.y},0);

        set.add_sprite(sprite_water_2,
                       {model.floor_4.width, model.floor_4.y}, 1);

        set.add_sprite(background_sprite, {model.background.x, model
                .background.y}, 0);


        if (model.alligator_counter < 120)
        {
            set.add_sprite(sprite_alligator_closed,
                           {model.alligator_block.x -gator_displacement.width,
                            model.alligator_block.y -gator_displacement.height},
                           2);
            set.add_sprite(sprite_alligator_closed,
                           {model.alligator_block_2.x -gator_displacement.width,
                            model.alligator_block_2.y -gator_displacement.height},
                           2);
        }
        if (model.alligator_counter >= 120)
        {

            set.add_sprite(sprite_alligator_open,
                           {model.alligator_block.x -gator_displacement.width,
                            model.alligator_block.y -gator_displacement.height},
                           2);
            set.add_sprite(sprite_alligator_open,
                           {model.alligator_block_2.x -gator_displacement.width,
                            model.alligator_block_2.y -gator_displacement.height},
                           2);
        }



    }
    // level 3 with a ladder and platform, water, alligators, and logs
    if(model.state == 2 && model.lives != 0)
    {

        set.add_sprite(model.player.sprite_, model.player.top_left()
                                                  .into<int>() -
                                                          sprite_displacement, 9);

        set.add_sprite(floor_3_sprite,  {model.floor_3.x, model.floor_3.y}, 0);

        set.add_sprite(floor_4_sprite, {model.floor_4.x, model.floor_4.y}, 1);

        set.add_sprite(ladder_sprite, {model.ladder.x - ladder_displacement
        .width,model.ladder.y},1);

        set.add_sprite(sprite_log, model.log.log_center.into<int>() -
                                   log_displacement, 3);

        set.add_sprite(platform_sprite, {model.platform.x -10, model.platform
        .y},1);


        set.add_sprite(floor_5_sprite,
                       {model.floor_5.x, model.floor_5.y}, 0);

        set.add_sprite(floor_6_sprite,
                       {model.floor_6.x, model.floor_6.y}, 1);

        set.add_sprite(sprite_water,
                       {model.floor_3.width, model.floor_3.y},0);

        set.add_sprite(sprite_water_2,
                       {model.floor_4.width, model.floor_4.y}, 1);

        set.add_sprite(background_sprite, {model.background.x, model
                .background.y}, 0);


        if (model.alligator_counter < 120)
        {
            set.add_sprite(sprite_alligator_closed,
                           {model.alligator_block.x -gator_displacement.width,
                            model.alligator_block.y -gator_displacement.height},
                           2);
            set.add_sprite(sprite_alligator_closed,
                           {model.alligator_block_2.x -gator_displacement.width,
                            model.alligator_block_2.y -gator_displacement.height},
                           2);
        }
        if (model.alligator_counter >= 120)
        {

            set.add_sprite(sprite_alligator_open,
                           {model.alligator_block.x -gator_displacement.width,
                            model.alligator_block.y -gator_displacement.height},
                           2);
            set.add_sprite(sprite_alligator_open,
                           {model.alligator_block_2.x -gator_displacement.width,
                            model.alligator_block_2.y -gator_displacement.height},
                           2);
        }

    }

    if(model.state == 3)
    {

        win_builder << "YOU WIN";

        win_display.reconfigure(win_builder);
        set.add_sprite(win_display, {35 + model.config.scene_dims.width/3,
                                       75+ model.config.scene_dims.height/2},
                       10);

        set.add_sprite(cat_sprite, {-300, 0}, 10);

    }


}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return model.config.scene_dims;
}



