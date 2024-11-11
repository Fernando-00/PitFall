#pragma once

#include <ge211.hxx>
#include <player.hxx>
#include <obstacles.hxx>
#include <game_config.hxx>

#include <vector>


struct Model
{
    ///
    /// CONSTRUCTOR
    ///

    // Constructs a model from a game configuration.
    //
    // The `= Game_config()` syntax makes the argument optional, in which case
    // it defaults to the default `Game_config`. That is, you can explicitly
    // create a `Game_config` to pass the `Model` constructor like so:
    //
    //     Game_config config;
    //     config.ball_radius = 2;
    //     Model model(config);
    //
    // Or you can omit the constructor argument, in which case you get
    // the default `Game_config` (as defined in game_config.cpp):
    //
    //     Model model;
    //
    // The word `explicit` means that this constructor doesn't define an
    // implicit conversion whereby C++ would automatically convert
    // `Game_config`s into `Model`s if needed. You don't want that.
    explicit Model(Game_config const& config = Game_config());


    void on_frame(double dt);

    ///
    /// MEMBER VARIABLES
    ///

    // The configuration parameters of the model. See game_config.hxx for a
    // description of what this determines. Models can be constructed with
    // different configurations, but the configuration never changes on an
    // existing model.
    Game_config const config;

    // All of the bricks, in no particular order. `Block` is a type
    // alias for `ge211::Rect<float>`, which means it gives both the
    // position of the top-left corner of each brick and the dimensions.
    std::vector<Block> platforms;

    // The position and dimensions of the paddle.
    Block floor;
    Block floor_2;
    Block floor_3;
    Block floor_4;
    Block floor_5;
    Block floor_6;
    Block background;
    Block lose;
    Block win;
    Block alligator_block;
    Block alligator_block_2;
    Block log_block;
    Block ladder;
    Block platform;

    // The state of the ball. Much of the model's business actually
    // happens in there, so see ball.hxx for that.
    Player player;

    Obstacles log;

    Obstacles alligator;

    Obstacles alligator_2;

    Obstacles water;

    int state;

    int lives;

    int alligator_counter;

    bool alligator_open;


};
