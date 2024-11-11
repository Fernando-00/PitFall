#pragma once

#include "model.hxx"

struct Model;

struct View
{


    explicit View(Model const&);

    void draw(ge211::Sprite_set& set);


    // This is a reference to the model. It means that the view doesn't
    // own the model but has access to it. Thus, the client of the view
    // (controller.cxx) must have or create a `Model` first and then
    // pass that by reference to the `View` constructor.

    Model const& model;


    // Returns the size of the window as given by `config.scene_dims`.
    ge211::Dims<int> initial_window_dimensions() const;

    // These three definitions hold the sprites that we need to
    // display the circle, the paddle, and the bricks to the screen.
    // They’re initialized in View’s constructor (in view.cxx, see
    // View::View(Model const&))


    ge211::Rectangle_sprite const floor_sprite;

    ge211::Rectangle_sprite const floor_2_sprite;

    ge211::Rectangle_sprite const floor_3_sprite;

    ge211::Rectangle_sprite const floor_4_sprite;

    ge211::Rectangle_sprite const floor_5_sprite;

    ge211::Rectangle_sprite const floor_6_sprite;

    ge211::Rectangle_sprite const background_sprite;

    ge211::Image_sprite sprite_log;

    ge211::Image_sprite sprite_alligator_open;

    ge211::Image_sprite sprite_alligator_closed;

    ge211::Image_sprite ladder_sprite;

    ge211::Image_sprite alligator_lose_screen;

    ge211::Image_sprite cat_sprite;

    ge211::Rectangle_sprite const sprite_water;

    ge211::Rectangle_sprite const sprite_water_2;

    ge211::Rectangle_sprite const platform_sprite;

    ge211::Text_sprite lives_display;
    ge211::Font sans28_{"sans.ttf", 28};

    ge211::Text_sprite win_display;

    ge211::Dims<int> sprite_displacement;

    ge211::Dims<int> log_displacement;

    ge211::Dims<int> gator_displacement;

    ge211::Dims<int> ladder_displacement;


};
