#include "player.hxx"
#include "game_config.hxx"


static Position
spawn_point(
        Block const& block,
        Game_config const& config)
{
    Position player_start(block.x + config.pos_displacement, block.y );

    player_start.into<int>();
    return player_start;
}


Player::Player(Block const& floor, Game_config const& config)
        : center(spawn_point(floor, config)),
          velocity(config.player_velocity_0),
          sprite_(config.filename_player),
          jumping_up(false),
          jumping_down(false),
          counter(0),
          max_counter(25),
          player_dims({33, 32}),
          initial_spawn(spawn_point(floor, config)),
          on_ladder(false)



{}


Position
Player::top_left() const
{
    return Position (center.x - (player_dims.width / 2) , center.y -
    (player_dims.height / 2));
}

bool
Player::hits_right(Game_config const& config) const
{
    int player_right = top_left().x + player_dims.width;

    if (player_right > config.scene_dims.width)
    {
        return true;
    }
    return false;
}

bool
Player::hits_left(Game_config const& config) const
{
    int player_left = top_left().x;

    if (player_left < 0)
    {
        return true;
    }
    return false;
}

Player
Player::next(double dt) const
{
    Player result(*this);

    result.center.x = center.x + (velocity.width * dt);
    result.center.y = center.y + (velocity.height * dt);

    return result;
}

void
Player::move_left()
{
    velocity.width = -100;
}

void
Player::move_right()
{
    velocity.width = 100;
}

bool
Player::hits_floor(Block const& floor)
{


    float top_player = top_left().y ;
    float bot_player = top_left().y + player_dims.height;
    float top_block = floor.top_left().y +player_dims.height;
    float bot_block = floor.bottom_left().y;

// ------------------------------------------------------------------

    float left_player = top_left().x;
    float right_player = top_left().x + player_dims.width;
    float left_block = floor.top_left().x;
    float right_block = floor.top_right().x;

    if (right_player < left_block || right_block < left_player ||
    bot_player < top_block || bot_block < top_player)
    {
        return false;
    }

    return true;
}


void
Player::jump_up(int counter_)
{
    if (counter_ <= max_counter)
    {
        velocity.height = -125;
                // * (1 / counter_);
        // velocity.height *= (1 / counter_);
        // if (velocity.height > 0)
        //{
        //    velocity.height *= -1;
        //}
    }
    else
    {
        jumping_down = true;
        jumping_up = false;
        counter = 0;
    }
}

bool
Player::near_ladder(Block const& ladder) const
{
    float top_player = top_left().y;
    float bot_player = top_left().y + player_dims.height;
    float top_ladder = ladder.top_left().y;
    float bot_ladder = ladder.bottom_left().y;

    //---------------------------------------------------------

    float left_player = top_left().x;
    float right_player = top_left().x + player_dims.width;
    float left_ladder = ladder.top_left().x;
    float right_ladder = ladder.top_right().x ;

    if (right_player > left_ladder && left_player < right_ladder
    && bot_player > top_ladder && top_player < bot_ladder)
    {
        return true;
    }
    return false;
}


