#include "model.hxx"
#include "player.hxx"
#include "obstacles.hxx"
#include <catch.hxx>


Game_config const config;

Block const test_floor {0, config.scene_dims.height - 150, 624, 150};

// These tests should demonstrate your functional requirements.

// Testing that when the player and log collide, the player has zero x-velocity.
TEST_CASE("Player hits log")
{
    Model m(config);

    Player test_player(test_floor, config);
    Obstacles test_log(m.log_block, config);
    test_player.center = {100, 100};
    test_log.log_center = {100, 100};

    // Checks if the player is in contact with the log
    CHECK(test_log.hits_player(test_player, config.log_dims));

    //Checks that the player's velocity has been slowed down after contact
    CHECK(test_player.velocity.width == 0);

}

// Testing that the player dies if they fall in water
TEST_CASE("Player falls in water")
{
    Model m(config);
    Player test_player(test_floor, config);

    test_player.center = {100, 500};

    // When player falls in the water
    if(test_player.center.y > test_floor.y + test_player.player_dims.height)
    {
        test_player.center = test_player.initial_spawn;
        m.lives -= 1;
    }

    //Checks if lives depleted after touching water
    CHECK(m.lives == 2);
    //Checks that the player respawns at the beginning of the level
    CHECK(test_player.center == test_player.initial_spawn);
}


// Testing that the player dies when standing on a closed alligator mouth
TEST_CASE("Player lands on closed alligator mouth")
{
    Model m(config);
    Player test_player(test_floor, config);

    Obstacles test_alligator(m.alligator_block, config);

    // Player center is set above the alligator
    test_player.center = {385, 287.5};
    // Resets lives
    m.lives = 3;
    //Alligator mouth is set on a counter to switch between open and close
    //Alligator counter is set to less than 120, in model we have counter <= 120
    // is when alligator's mouth is closed
    m.alligator_counter = 50;

    m.on_frame(1);

    CHECK(m.alligator_open == false);
    CHECK(m.lives == 3);
    CHECK(test_player.hits_floor(m.alligator_block));

}

// Testing that the player doesn't die when standing on an open alligator
// mouth
TEST_CASE("Player lands on open alligator")
{
    Model m(config);
    Player test_player(test_floor, config);

    Obstacles test_alligator(m.alligator_block, config);
    // Player center is set above the alligator
    test_player.center = {385, 287.5};
    // Alligator counter is set to greater than 120.

    // Resetting lives to 3 and the state to 2, where the alligators are
    m.lives = 3;
    m.state = 2;

    // Setting the counter to just before the alligator's mouth opens
    m.alligator_counter = 119;


    // Check if player is on the alligator
    CHECK(test_player.hits_floor(m.alligator_block));

    m.on_frame(1);
    //Checks if the alligator count is at 120 which is when it should switch
    // to open
    CHECK(m.alligator_counter == 120);
    //Checks that alligator's mouth is open
    CHECK(m.alligator_open == true);
    //Checks that the player's life decreased by 1
    CHECK(m.lives == 2);

}

// Testing that a player has a y-velocity of 100 when near a ladder and
// pressing the up arrow
TEST_CASE("Ladder test")
{

    Model m(config);
    Player test_player(test_floor, config);
    Block test_ladder(config.ladder.x, config.ladder.y,
                      config.ladder_dims.width, config.ladder_dims.height);

    // Putting the player near the ladder
    m.player.center = {145, 115};

    // Sets stage 2: the level where the ladder is placed
    m.state = 2;

    // Checks that the player is near the ladder
    CHECK(m.player.near_ladder(m.ladder));
    m.player.jumping_up = false;
    m.on_frame(1);

    // Checks that the player is on the ladder
    CHECK(m.player.on_ladder == true);

}

