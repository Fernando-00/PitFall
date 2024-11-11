#pragma once

#include <ge211.hxx>

using Block = ge211::Rect<int>;

using Dims = ge211::geometry::Dims<int>;

struct Game_config
{

    Game_config();

    // The dimensions of the whole window:
    ge211::Dims<int> scene_dims;

    // The dimensions of the floor:
    ge211::Dims<int> floor_dims;

    ge211::Dims<int> floor_2_dims;

    ge211::Dims<int> floor_3_dims;

    ge211::Dims<int> floor_4_dims;

    ge211::Dims<int> floor_5_dims;

    ge211::Dims<int> floor_6_dims;

    ge211::Dims<int> platform_dims;

    ge211::Dims<int> ladder_dims;

    ge211::Dims<int> background_dims;

    ge211::Dims<int> lose_dims;

    ge211::Dims<int> win_dims;

    ge211::Dims<int> log_dims;

    ge211::Dims<int> alligator_dims;

    Block floor;

    Block floor_2;

    Block floor_3;

    Block floor_4;

    Block floor_5;

    Block floor_6;

    Block ladder;

    Block platform;

    Block background;

    Block lose;

    Block win;

    Block alligator_block;

    Block alligator_block_2;

    // The ball's initial velocity {width, height}:
    ge211::Dims<int> player_velocity_0;

    std::string filename_player;

    std::string filename_log;

    std::string filename_alligator_open;

    std::string filename_alligator_closed;

    std::string filename_ladder;

    std::string filename_alligator_lose_screen;

    std::string filename_cat_win;

    // The log's velocity
    ge211::Dims<int> log_velocity;

    // The log's velocity


    int pos_displacement;



};
