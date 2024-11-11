#include "obstacles.hxx"
#include "game_config.hxx"


static Position
spawn_point(
        Block const& block,
        Game_config const& config)
{
    Position log_start(block.x, block.y );

    log_start.into<int>();
    return log_start;
}


Obstacles::Obstacles(Block const& floor, Game_config const& config)
        : log_center(spawn_point(floor, config)),
          log_velocity(config.log_velocity),
          spawn_point_log(spawn_point(floor, config))


{}


bool
Obstacles::log_hits_left(Dims const dims)
{
    int log_right = log_center.x + dims.width/2;
    if (log_right < 0)
    {
        return true;
    }
    return false;
}

Obstacles
Obstacles::next(double dt) const
{
    Obstacles result(*this);

    result.log_center.x = log_center.x + (log_velocity.width * dt);
    result.log_center.y = log_center.y + (log_velocity.height * dt);

    return result;
}

bool
Obstacles::hits_player(Player const& player, Dims const dims) const
{
    float left_log = log_center.x - dims.width/2;
    float right_log = log_center.x + dims.width/2;
    float left_player = player.top_left().x;
    float right_player = player.top_left().x + player.player_dims.width;

// -------------------------------------------------------------------

    float top_log = log_center.y;
    float bot_log = log_center.y + dims.height/2 ;
    float top_player = player.top_left().y;
    float bot_player = player.top_left().y + player.player_dims.height;

    if (bot_log < top_player || bot_player < top_log
    || right_log < left_player || right_player < left_log)
    {
        return false;
    }

    return true;

}
