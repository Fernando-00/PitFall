#pragma once


#include "game_config.hxx"

#include <ge211.hxx>

#include <iostream>

using Position = ge211::Posn<float>;

using Velocity = ge211::Dims<float>;

using Block = ge211::Rect<int>;

struct Player
{


    Player(Block const& floor, Game_config const&);

    // Retrieves the top left corner of the player's hit box
    Position top_left() const;

    // Detects a collision between the player and the left side of the screen
    bool hits_left(Game_config const&) const;

    // Detects a collision between the player and the right side of the screen
    bool hits_right(Game_config const&) const;

    // Returns the state of the player after 'dt' seconds have passed
    Player next(double dt) const;

    // Moves the player left
    void move_left();

    // Moves the player left
    void move_right();

    // The first half of the jump
    void jump_up(int counter);

    // The second half of the jump
    void jump_down(int counter);

    // Detects a collision between the player and the floor
    bool hits_floor(Block const&);

    // Detects if the player is near a ladder
    bool near_ladder(Block const&) const;


    ge211::Image_sprite const& get_sprite() const {
        return sprite_;
    }



    /// The position of the center of the ball.
    Position center;

    /// The velocity of the ball in pixels per tick.
    Velocity velocity;


    ge211::Image_sprite sprite_;

    bool jumping_up;

    bool jumping_down;

    int counter;

    int max_counter;

    ge211::Dims<float> player_dims;

    Position initial_spawn;

    bool on_ladder;







};
