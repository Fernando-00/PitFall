#include "controller.hxx"

#include "model.hxx"

Controller::Controller(Model& model)
        : model(model),
          view(model)


{ }

void
Controller::on_frame(double dt)
{
    model.on_frame(dt);
}

void
Controller::on_key_down(ge211::Key key)
{
    // right arrow key
    if (key == ge211::Key::right())
    {
        model.player.move_right();
    }

    // left arrow key
    if (key == ge211::Key::left())
    {
        model.player.move_left();
    }

    //up and down for ladders
    if (key == ge211::Key::up() && model.player.on_ladder && !model.player
    .jumping_up)
    {
        model.player.velocity.height = -100;
    }

    if (key == ge211::Key::down() && model.player.on_ladder)
    {
        model.player.velocity.height = 100;
    }
}

void
Controller::on_key_up(ge211::Key key)
{
    // right arrow key
    if (key == key.right())
    {
        model.player.velocity.width = 0;
    }

    // left arrow key
    if (key == key.left())
    {
        model.player.velocity.width = 0;
    }


    if(model.state == 0)
    {
        if (key == key.code(' ') && model.player.hits_floor(model.floor))
        {
            model.player.jumping_up = true;
        }
    }
    if(model.state == 1)
    {
        if (key == key.code(' ') && model.player.hits_floor(model.floor_3))
        {
            model.player.jumping_up = true;
        }
        if (key == key.code(' ') && model.player.hits_floor(model.floor_5))
        {
            model.player.jumping_up = true;
        }
        if (key == key.code(' ') &&
        model.alligator.hits_player(model.player,
                                    model.config.alligator_dims))
        {
            model.player.jumping_up = true;
        }
        if (key == key.code(' ') &&
            model.alligator_2.hits_player(model.player,
                                        model.config.alligator_dims))
        {
            model.player.jumping_up = true;
        }
    }
    if(model.state == 2)
    {
        if (key == key.code(' ') && model.player.hits_floor(model.floor_3))
        {
            model.player.jumping_up = true;
        }
        if (key == key.code(' ') && model.player.hits_floor(model.platform))
        {
            model.player.jumping_up = true;
        }

        if (key == key.up() && model.player.on_ladder)
        {
            model.player.velocity.height = 0;
        }
        if (key == key.down() && model.player.on_ladder)
        {
            model.player.velocity.height = 0;
        }

        if (key == key.code(' ') &&
            model.alligator.hits_player(model.player,
                                        model.config.alligator_dims))
        {
            model.player.jumping_up = true;
        }
        if (key == key.code(' ') &&
            model.alligator_2.hits_player(model.player,
                                          model.config.alligator_dims))
        {
            model.player.jumping_up = true;
        }

    }



}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view.initial_window_dimensions();
}

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view.draw(sprites);
}