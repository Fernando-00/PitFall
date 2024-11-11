#pragma once

#include "view.hxx"

#include <ge211.hxx>

struct Controller : public ge211::Abstract_game
{

    explicit Controller(Model&);


    void draw(ge211::Sprite_set&) override;

    void on_key_down(ge211::Key) override;

    void on_key_up(ge211::Key) override;

    ge211::Dims<int> initial_window_dimensions() const override;

    void on_frame(double dt) override;


    Model& model;
    View view;
};
