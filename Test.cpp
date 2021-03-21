#include <string>
#include <algorithm>
#include "doctest.h"
#include "Board.hpp"
using namespace ariel;
using namespace std;

TEST_CASE("simple post and read cases - single words")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "CPP");
    board.post(0, 3, Direction::Horizontal, "course");
    board.post(1, 0, Direction::Vertical, "Ariel");
    board.post(7, 0, Direction::Vertical, "University");
    board.post(10, 10, Direction::Horizontal, "Science");
    board.post(11, 11, Direction::Vertical, "computer");

    CHECK(board.read(0, 0, Direction::Horizontal, 3) == "CPP");
    CHECK(board.read(0, 3, Direction::Horizontal, 6) == "course");
    CHECK(board.read(0, 1, Direction::Horizontal, 2) == "PP");
    CHECK(board.read(0, 0, Direction::Horizontal, 8) == "CPPcourse");
    CHECK(board.read(1, 0, Direction::Vertical, 5) == "Ariel");
    CHECK(board.read(7, 0, Direction::Vertical, 10) == "University");
    CHECK(board.read(1, 0, Direction::Vertical, 15) == "ArielUniversity");
    CHECK(board.read(10, 10, Direction::Horiontal, 7) == "Science");
    CHECK(Board.read(10, 13, Direction::Horizontal, 4) == "ence");
    CHECK(board.read(11, 11, Direction::Vertical, 8) == "computer");
    CHECK(board.read(13, 11, Direction::Vertical, 6) == "mputer");

    CHECK(board.read(20, 20, Direction::Horizontal, 5) == "_____"); //empty space on board
}

TEST_CASE("simple post and read cases - multiple words")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "CPP course");
    board.post(1, 0, Direction::Vertical, "PP is powerfull");

    CHECK(board.read(0, 0, Direction::Horizontal, 10) == "CPP course");
    CHECK(board.read(0, 0, Direction::Vertical, 16) == "CPP is powerfull");
    CHECK(board.read(0, 4, Direction::Horizontal, 6) == "course");  //partial reading
    CHECK(board.read(7, 0, Direction::Vertical, 9) == "powerfull"); //partial reading
}
TEST_CASE("multiple lines post and read cases-Vertical to Horizontal")
{
    Board board;
    board.post(0, 0, Direction::Vertical, "CPP\ncourse");
    board.post(0, 2, Direction::Vertical, "Ariel\nUniversity");

    CHECK(board.read(0, 0, Direction::Vertical, 3) == "CPP");         //reading first line
    CHECK(board.read(1, 0, Direction::Vertical, 6) == "course");      //reading second line
    CHECK(board.read(2, 0, Direction::Vertical, 5) == "Ariel");       //reading first line
    CHECK(board.read(3, 0, Direction::Vertical, 10) == "University"); //reading second line
    CHECK(board.read(0, 0, Direction::Horizontal, 2) == "Cc");        //reading Horizontal letters from vertical messages
    CHECK(board.read(3, 0, Direction::Horizontal, 2) == "_r");
    CHECK(board.read(0, 0, Direction::Horizontal, 4) == "CnAU");
    CHECK(board.read(4, 0, Direction::Horizontal, 4) == "_e_v");
}
TEST_CASE("multiple lines post and read cases-Horizontal to vertical")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "CPP\ncourse");
    board.post(0, 2, Direction::Horizontal, "Ariel\nUniversity");

    CHECK(board.read(0, 0, Direction::Horizontal, 3) == "CPP");
    CHECK(board.read(1, 0, Direction::Horizontal, 6) == "course");
    CHECK(board.read(2, 0, Direction::Horizontal, 6) == "Ariel");
    CHECK(board.read(0, 3, Direction::Horizontal, 10) == "University");
    CHECK(board.read(0, 0, Direction::Horizontal, 4) == "CcAU");
    CHECK(board.read(0, 4, Direction::Vertical, 4) == "_sle");
}
TEST_CASE("overriding posts - single line cases")
{
    Board board;
    board.post(0, 0, Direction::Horizontal, "program");
    board.post(0, 0, Direction::Horizontal, "frogg"); //partial overriding
    board.psot(0, 10, Direction::Horizontal, "ariel");
    board.post(0, 9, Direction::Horizontal, "university") //full word overriding
        board.post(3, 0, Direction::Vertical, "programming");
    board.post(3, 0, Direction::Vertical, "shawarma");
    board.post(10, 10, Direction::Horizontal, "cat");
    board.post(10, 10, Direction::Vertical, "just");                                 //full word overriding
    board.post(2, 0, Direction::Horizontal, "CS degree will give you great income"); //overriding in multiple words message-Horizontal
    board.post(2, 11, Direction::Horizontal, "wont");
    board.post(11, 11, Direction::Vertical, "Walker Texas Ranger");
    board.post(18, 11, Direction::Vertical, "Haifa")

        CHECK(board.read(0, 0, Direction::Horizontal, 7) == "froggam");
    CHECK(board.read(0, 9, Direction::Horizontal, 10) == "university");
    CHECK(board.read(3, 0, Direction::Vertical, 11) == "shawarmaing");
    CHECK(board.read(10, 10, Direction::Vertical, 4) == "just");
    CHECK(board.read(2, 0, Direction::Horizontal, 35) == "CS degree wont give you great income")
    CHECK(board.read(11, 11, Direction::Vertical, 19) == "Walker Haifa Ranger");
}
TEST_CASE("overriding posts - multiple lines cases")
{
    Board board;
    board.post(1, 0, Direction::Horizontal, "Haifa");
    board.post(0, 0, Direction::Horizontal, "Tel\nAviv");
    board.post(2, 1, Direction::Vertical, "small");
    board.post(2, 0, Direction::Vertical, "Bibi Is\nYamin");

    CHECK(board.read(1, 0, Direction::Horizontal, 5) == "Aviva");
    CHECK(board.read(2, 1, Direction::Vertical, 5) == "Yamin")
}
TEST_CASE("bad input cases")
{
    Board board;
    CHECK_THROWS(board.post(0, 0, Direction::Horizontal, 3));
    CHECK_THROWS(board.post(0, 0, Direction::Horizontal, A));
    CHECK_THROWS(board.post(0, 0, Direction::Horizontal, 3.3));
    CHECK_THROWS(board.read(0, 0, Direction::Horizontal, ));
    CHECK_THROWS(board.read(0, 0, Direction::Horizontal, ))
    CHECK_THROWS(board.read(0, 0, Direction::Horizontal, ));
}
TEST_CASE("bad coordinates cases")
{
    Board board;
    CHECK_THROWS(board.post(-1, 0, Direction::Horizontal, "abc"));
    CHECK_THROWS(board.post(0, -1, Direction::Horizontal, "abc"));
    CHECK_THROWS(board.post(-1, -1, Direction::Horizontal, "abc"));
    CHECK_THROWS(board.read(-1, 0, Direction::Horizontal, ));
    CHECK_THROWS(board.read(0, -1, Direction::Horizontal, ))
    CHECK_THROWS(board.read(-1, -1, Direction::Horizontal, ));
}
TEST_CASE("no room errors")
{
    usigned int max = 4294967295;
    Board board;
    CHECK_THROWS(board.post(max + 1, 0, Direction::Vertical, "a"));
    CHECK_THROWS(board.post(max, 0, Direction::Vertical, "ab"));
    CHECK_THROWS(board.post(0, max + 1, Direction::Horizontal, "a"));
    CHECK_THROWS(board.post(0, max, Direction::Horizontal, "ab"));
}