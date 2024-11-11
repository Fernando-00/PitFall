#pragma once


#include "game_config.hxx"

#include "player.hxx"

#include <ge211.hxx>

#include <iostream>

using Position = ge211::Posn<float>;

using Velocity = ge211::Dims<float>;

using Block = ge211::Rect<int>;


struct Obstacles {

    Obstacles(Block const& floor, Game_config const&);


    bool log_hits_left(Dims const);

    Obstacles next(double dt) const;

    // The position of the center of the ball.
    Position log_center;

    // The velocity of the ball in pixels per tick.
    Velocity log_velocity;

    Position spawn_point_log;

    // Detects a collision between the player and the floor
    bool hits_player(Player const&, Dims const) const;




};
