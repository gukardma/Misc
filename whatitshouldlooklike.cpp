//==============================================================================
//==============================================================================
// C++ Application
//==============================================================================
//==============================================================================

//region Compiler directives

//==============================================================================
//==============================================================================
// Compiler directives
//==============================================================================
//==============================================================================

//#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "readability-static-accessed-through-instance"

// #pragma clang diagnostic push
// Allow scanf int without check
// #pragma ide diagnostic ignored "cert-err34-c"
// #pragma clang diagnostic pop

// Disable assert
// #define NDEBUG

//endregion Compiler directives

//region Notes

//==============================================================================
//==============================================================================
// Notes
//==============================================================================
//==============================================================================

// g++ -std=c++17 -g -Werror -Wall prg.c -o prg

// Tuple documentation http://www.cplusplus.com/reference/tuple/tuple

// Boost library documentation https://www.boost.org/doc/libs

// Book: The Boost C++ Libraries
// https://theboostcpplibraries.com

// Boost JSON https://www.boost.org/doc/libs/1_75_0/libs/json/doc/html/json/quick_look.html

// https://cppreference.com

// http://www.cplusplus.com/reference

// g++ -std=c++11 prg.cpp -o prg
// g++ -std=c++14 prg.cpp -o prg
// g++ -std=c++17 prg.cpp -o prg

//endregion Notes

//region Utility macros

//==============================================================================
//==============================================================================
// Utility macros
//==============================================================================
//==============================================================================

// Print debug messages only when ZZDEBUG is defined
//#define debug_print(fmt, ...)
//    do { if(ZZDEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)
//#define dp(fmt, ...)
//    do { if(ZZDEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

//#define max(a, b) \
//   ({ __typeof__ (a) _a = (a); \
//       __typeof__ (b) _b = (b); \
//     _a > _b ? _a : _b; })

//#define min(a, b) \
//   ({ __typeof__ (a) _a = (a); \
//       __typeof__ (b) _b = (b); \
//     _a < _b ? _a : _b; })

//endregion Utility macros

//region Includes

//==============================================================================
//==============================================================================
// Includes
//==============================================================================
//==============================================================================

// #include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cassert>
#include <utility>
#include <fstream>
#include <random>
#include <condition_variable>
#include <chrono>
#include <thread>
#include <memory>

#include <tuple>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

//#include <regex>
//#include <cassert>
//#include <ctime>

//#include <boost/timer/timer.hpp>
//#include "boost/json/src.hpp"

#include "shr.h"
#include "other.h"
//#include "geo.h"
#include "slpz.h"

//#define BOOST_TEST_MODULE prg_test
//#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

//endregion Includes

//region Namespace use

//==============================================================================
//==============================================================================
// Namespace use
//==============================================================================
//==============================================================================

using namespace std;

//endregion Namespace use

//region Global definitions and functions

//==============================================================================
//==============================================================================
// Global definitions and functions
//==============================================================================
//==============================================================================

//region Signal handling

//==============================================================================
// Signal handling
//==============================================================================

//endregion Signal handling

//region Execution time

//==============================================================================
// Execution time
//==============================================================================

//endregion Execution time

//region Error functions

//==============================================================================
// Error functions
//==============================================================================

//endregion Error functions

//endregion Global definitions and functions

//region Data definitions

//==============================================================================
//==============================================================================
// Data definitions
//==============================================================================
//==============================================================================

// /** Directions for movement */
//enum gen_move_t {UP, DOWN, LEFT, RIGHT};

//endregion Data definitions

//region Slide puzzle

//==============================================================================
//==============================================================================
// Slide puzzle
//==============================================================================
//==============================================================================

/**
 * Slide puzzle
 *
 * A slide puzzle contains 15 pieces on a 4x4 grid with 16 positions, with
 * one position being marked as empty (identified as 0). The rows and columns
 * are occupied with pieces marked incrementally from 1 to 15 when solved.
 *
 * Slide puzzle (solved)(assume 0 "space" is on bottom right)
 *
 *  1  2  3  4
 *  5  6  7  8
 *  9 10 11 12
 * 13 14 15
 *
 * Pieces can be moved around, as shown in the example below. The empty
 * slot is identified with number 0.
 *
 * Slide puzzle movement step 1 of 5 (move left = piece 15 moves right)
 *  1  2  3  4
 *  5  6  7  8
 *  9 10 11 12
 * 13 14  0 15
 *
 * Slide puzzle movement step 2 of 5 (move up = piece 11 moves down)
 *  1  2  3  4
 *  5  6  7  8
 *  9 10  0 12
 * 13 14 11 15
 *
 * Slide puzzle movement step 3 of 5 (move up = piece 7 moves down)
 *  1  2  3  4
 *  5  6  0  8
 *  9 10  7 12
 * 13 14 11 15
 *
 * Slide puzzle movement step 4 of 5 (move right = piece 8 moves left)
 *  1  2  3  4
 *  5  6  8  0
 *  9 10  7 12
 * 13 14 11 15
 *
 * Slide puzzle movement step 4 of 5 (move down = piece 12 moves up)
 *  1  2  3  4
 *  5  6  8 12
 *  9 10  7  0
 * 13 14 11 15
 *
 */

/** Directions for movement for slide puzzle */
enum slpz_move_t {UP, DOWN, LEFT, RIGHT};

/**
 * Location of blank or other slot for slide puzzle.
 * Layout of location is slots[a][b].
 */
struct slpz_loc_t {
    int a;
    int b;

    slpz_loc_t(): a(-1), b(-1) {}; // default set to -1, -1
    slpz_loc_t(int aa, int bb): a(aa), b(bb) {}; // set at creation time
    void reset() {a = -1; b = -1;}; // reset to invalid value
    void set(int aa, int bb) {a = aa; b = bb;}; // set to specific value
    bool valid() const { // NOLINT
        return clamp(a, 0, 3) == a && clamp(b, 0, 3) == b;
    };
};

class slide_puzzle_t {
private:
    int slots[4][4]; // Current board configuration
    slpz_loc_t blank_slot; // Position of blank slot

    // Solved board configuration
    int slots_solved[4][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9,  10, 11, 12},
        {13, 14, 15, 0}
    };

    /** Copy board positions from provided configuration */
    void copy_board(const int s[4][4]){
        blank_slot.reset();
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                slots[i][j] = s[i][j];
                if(slots[i][j] == 0) {
                    blank_slot.set(i, j);
                }
            }
        }
    };

    /** Check if this configuration is same as other configuration */
    bool is_equal(const int s[4][4]) const {
        bool eq = true;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(slots[i][j] != s[i][j]) {
                    eq = false;
                }
            }
        }
        return eq;
    };

public:

    /** Create a puzzle (default configuration is in solved state) */
    slide_puzzle_t() {  // NOLINT
        reset_board();
    }

    /** Create a puzzle as a copy of another puzzle */
    slide_puzzle_t(const slide_puzzle_t &sp) {  // NOLINT
        copy_board(sp.slots);
    }

    /** Create a puzzle with a specific configuration provided as a 2D array */
    explicit slide_puzzle_t(const int spa[4][4]) {  // NOLINT
        copy_board(spa);
    }

    /**
     * Determine if two slide puzzles have the same configuration.
     */
    bool operator==(const slide_puzzle_t &sp) const {  // NOLINT
        return is_equal(sp.slots);
    }

    /**
     * Set the configuration of the puzzle to the same configuration of
     * a different puzzle
     */
    slide_puzzle_t& operator=(const slide_puzzle_t &sp) {  // NOLINT
        copy_board(sp.slots);
        return *this;
    }

    /**
     * Set the configuration of the puzzle to the same configuration of
     * a provided slots array
     */
    slide_puzzle_t& operator=(int slots_new[4][4]) {
        copy_board(slots_new);
        return *this;
    }

    /** Reset board to the solved configuration */
    void reset_board() {
        copy_board(slots_solved);
    }

    /** Set the board to the provided configuration */
    void set_board(int slots_new[4][4]) {
        copy_board(slots_new);
    }

    // TODO: Implement blank slot location blank_loc()
    /**
     * Identify array location of blank slot.
     * Minimum is a,b location 0,0 and maximum is a,b location 3,3.
     */
    slpz_loc_t blank_loc() const {
        // [[maybe_unused]] int ign = 0 * blank_slot.a * blank_slot.b; // can be deleted
        // ll.a = -1;
        // ll.b = -1;
        //assert(clamp(ll.a, 0, 3) == ll.a && clamp(ll.b, 0, 3) == ll.b);

        slpz_loc_t ll;

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(slots[i][j] == 0) {
                    ll.set(i, j);
                    break;
                }
            }
        }
        return ll;
    }

    // TODO: Implement board correct positions board_status_pos()
    /**
     * Identify number of slots occupied by the correct puzzle piece.
     * Minimum is 0 (all out of place), and maximum is 15 (puzzle solved).
     */
    int board_status_pos() const {
        // [[maybe_unused]] int ign = 0 * blank_slot.a * blank_slot.b; // can be deleted
        int num_good = 0;
        int correct_num_of_pos = 1;

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                // cout << "current number in slot: " << slots[i][j] << endl;
                // cout << "What it should be:" << correct_num_of_pos << endl;
                if(slots[i][j] == correct_num_of_pos) {
                    num_good++;
                    // cout << "numerated" << endl;
                }
                correct_num_of_pos++;
            }
        }
//        allowed_moves();
        return num_good;
    }

    // TODO: Implement allowed moves allowed_moves()
    /**
     * Identify allowed moves from current blank space.
     */
    vector<slpz_move_t> allowed_moves() const {
        // [[maybe_unused]] int ign = 0 * blank_slot.a * blank_slot.b; // can be deleted
        vector<slpz_move_t> moves;
        slpz_loc_t cur_blank_pos = blank_loc();
//        moves.insert(moves.begin(),{UP,DOWN,LEFT,RIGHT});

        if(cur_blank_pos.a > 0) moves.push_back(UP);
        if(cur_blank_pos.a < 3) moves.push_back(DOWN);
        if(cur_blank_pos.b > 0) moves.push_back(LEFT);
        if(cur_blank_pos.b < 3) moves.push_back(RIGHT);


//        if(cur_blank_pos.a == 0){
//            moves.erase(moves.begin());
//        }
//        if(cur_blank_pos.a == 3){
//            moves.erase(moves.begin()+1);
//        }
//        if(cur_blank_pos.b == 0){
//            moves.erase(moves.begin()+2);
//        }
//        if(cur_blank_pos.b == 3){
//            moves.erase(moves.begin()+3);
//        }
//
//        for(auto itr : moves)
//            cout << itr << endl;

        return moves;
    }

    /**
     * Identify new boards for allowed moves from current blank space.
     */
    vector<slide_puzzle_t> allowed_moves_boards() const {
        vector<slide_puzzle_t> boards;
        vector<slpz_move_t> moves = allowed_moves();
        for(auto dir: moves) {
            slide_puzzle_t new_sp(*this);
            new_sp.move(dir);
            boards.push_back(new_sp);
        }
        return boards;
    }

    /**
     * Move empty slot in a specific direction. Assume direction is allowed.
     * @param dir Direction to move (UP, DOWN, LEFT, RIGHT)
     */
    void move(slpz_move_t dir) {
        vector<slpz_move_t> moves = allowed_moves();

        {
            for(auto itr : moves)
                cout << itr << endl;
        }

        // Check if can move in this direction
        assert(find(moves.begin(), moves.end(), dir) != moves.end());
        int a = blank_slot.a;
        int b = blank_slot.b;
        switch(dir) {
            case(UP): {
                // move up
                slots[a][b] = slots[a-1][b];
                slots[a-1][b] = 0;
                blank_slot.a--;
            } break;
            case(DOWN): {
                // move down
                slots[a][b] = slots[a+1][b];
                slots[a+1][b] = 0;
                blank_slot.a++;
            } break;
            case(LEFT): {
                // move left
                slots[a][b] = slots[a][b-1];
                slots[a][b-1] = 0;
                blank_slot.b--;
            } break;
            case(RIGHT): {
                // move left
                slots[a][b] = slots[a][b+1];
                slots[a][b+1] = 0;
                blank_slot.b++;
            } break;
            default: {
                assert(false); // should not happen
            }
        }
    }

    /** Print slide puzzle */
    void print(ostream &os) const {
        for(int i = 0; i < 4; i++) {  // NOLINT
            os << setw(2) << slots[i][0]
               << setw(3) << slots[i][1]
               << setw(3) << slots[i][2]
               << setw(3) << slots[i][3] << "\n";
        }
    }

    /** Hash function for C++ STL */
    size_t stl_hash() const { // NOLINT
        size_t h = 0;
        h = h ^ ((slots[0][0] << 12) && (slots[0][1] << 8) &&
                 (slots[0][2] << 4) && (slots[0][3]));
        h = h ^ ((slots[1][0] << 28) && (slots[1][1] << 24) &&
                 (slots[1][2] << 20) && (slots[1][3]) << 16);
        h = h ^ ((slots[2][0] << 12) && (slots[2][1] << 8) &&
                 (slots[2][2] << 4) && (slots[2][3]));
        h = h ^ ((slots[3][0] << 28) && (slots[3][1] << 24) &&
                 (slots[3][2] << 20) && (slots[3][3]) << 16);
        return h;
    }

};

/** Hash function for C++ STL */
template<> struct std::hash<slide_puzzle_t>
{
    std::size_t operator()(slide_puzzle_t const& s) const noexcept
    {
        return s.stl_hash();
    }
};

const auto zzz_trash_sp_hash = std::hash<slide_puzzle_t>{}(slide_puzzle_t());

/** Print slide puzzle */
ostream &operator<<(ostream &os, const slide_puzzle_t &sp) {
    sp.print(os);
    return os;
}

/**
 * A set of example configurations for the slide puzzle
 */

// Sample configurations for internal use:
// Solved
int ii_slpz_solved[4][4] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9,  10, 11, 12},
    {13, 14, 15, 0}
};
// Move left
int ii_slpz_1[4][4] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9,  10, 11, 12},
    {13, 14, 0,  15}
};
// Move up
int ii_slpz_2[4][4] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9,  10, 0,  12},
    {13, 14, 11, 15}
};
// Move up
int ii_slpz_3[4][4] = {
    {1,  2,  3,  4},
    {5,  6,  0,  8},
    {9,  10, 7,  12},
    {13, 14, 11, 15}
};
// Move right
int ii_slpz_4[4][4] = {
    {1,  2,  3,  4},
    {5,  6,  8,  0},
    {9,  10, 7,  12},
    {13, 14, 11, 15}
};
// Move down
int ii_slpz_5[4][4] = {
    {1,  2,  3,  4},
    {5,  6,  8,  12},
    {9,  10, 7,  0},
    {13, 14, 11, 15}
};

// Sample configurations for global use

const slide_puzzle_t gg_slpz_solved(ii_slpz_solved); // NOLINT
const slide_puzzle_t gg_slpz_1(ii_slpz_1); // NOLINT
const slide_puzzle_t gg_slpz_2(ii_slpz_2); // NOLINT
const slide_puzzle_t gg_slpz_3(ii_slpz_3); // NOLINT
const slide_puzzle_t gg_slpz_4(ii_slpz_4); // NOLINT
const slide_puzzle_t gg_slpz_5(ii_slpz_5); // NOLINT

/**
 * Sample of configuration steps from an unsolved puzzle to a solved puzzle,
 * containing a sequence of states from an initial unsolved configuration
 * gg_slpz_5 to a solved configuration
 */
const vector<slide_puzzle_t> gg_slpz_sol_seq({  // NOLINT
    gg_slpz_5,
    gg_slpz_4,
    gg_slpz_3,
    gg_slpz_2,
    gg_slpz_1,
    gg_slpz_solved
});

/**
 * Sample of configuration steps from an unsolved puzzle to a solved puzzle,
 * containing a sequence of states from an initial unsolved configuration
 * gg_slpz_2 to a solved configuration (two steps only)
 */
const vector<slide_puzzle_t> gg_slpz_sol_seq_b({  // NOLINT
    gg_slpz_2,
    gg_slpz_1,
    gg_slpz_solved
});

/**
 * Sample of several puzzle configurations, with no specific order.
 */
const vector<slide_puzzle_t> gg_slpz_coll_a({  // NOLINT
    gg_slpz_3,
    gg_slpz_1,
    gg_slpz_5,
    gg_slpz_2
});

//==============================================================================
// Search for slide puzzle
//==============================================================================

// TODO: Implement slide puzzle solution using iterative deepening (recursion)
/**
 * Find a slide puzzle solution sequence with iterative deepening search
 * using recursion.
 *
 * @param start_sp Starting puzzle configuration
 * @param end_sp Ending puzzle configuration
 * @param visited_sp Collection of puzzle configurations that have already
 *         been considered (begin with start_sp)
 * @param path Path of visited puzzle moves from origin
 * @param depth Depth of traversal to consider
 *
 * @return Calculated puzzle solution sequence from start to end
 */
vector<slide_puzzle_t> slpz_search_itdp_r(
        const slide_puzzle_t &start_sp,
        const slide_puzzle_t &end_sp,
        unordered_set<slide_puzzle_t> &visited_sp,
        vector<slide_puzzle_t> &path,
        int depth) {
    vector<slide_puzzle_t> seq;
    // TODO: Condition for checking that path to solution was found
    if (depth == 0) {
        return seq;
    }
    if (start_sp == end_sp) {
        path.push_back(start_sp);
        return path;
    }
    auto moves = start_sp.allowed_moves();
    for (const auto &move: moves) {
        slide_puzzle_t next_sp = start_sp;
        next_sp.move(move);
        if (visited_sp.find(next_sp) == visited_sp.end()) {
            visited_sp.insert(next_sp);
            path.push_back(next_sp);
            seq = slpz_search_itdp_r(next_sp, end_sp, visited_sp, path, depth - 1);
            if (!seq.empty()) {
                return seq;
            }
            path.pop_back();
        }
    }
    return seq;
}
//    if(start_sp == end_sp) {
//        // Found a puzzle solution path that leads to the goal, at the desired
//        // path length
//        seq = path;
//        // assert(depth == 0); // should be at zero depth by now
//    // TODO: Condition for checking that more paths should be considered
//    } else if(false) {
//        // Have not yet found a solution, but still have deeper paths remaining
//        // to explore
//        const slide_puzzle_t& curr_sp(start_sp);
//
//        // List of possible next moves
//        /* const */ vector<slide_puzzle_t> next_possible_sp;
//
//        // To avoid cycles, do not go back to puzzles that have already
//        // been visited
//        for (const auto &next_sp: next_possible_sp) {
//            // TODO: fix condition
//            if (false) {
//                // This puzzle has already been visited,
//                // so do nothing.
//            } else {
//                // This puzzle has not been visited, so visit it.
//                // TODO: Adjust visited_sp and path
//                vector<slide_puzzle_t> subseq;
//                // TODO: recursion
//                //subseq = slpz_search_itdp_r(...,
//                //        ..., visited_sp, ..., depth - 1);
//                if(!subseq.empty()) {
//                    // Found a solution
//                    seq = subseq;
//                    break; // prefer a different approach later...
//                }
//                // TODO: Readjust visited_sp and path
//            }
//        }
//    }
//    return seq;
//}

// ITEM: Implement slide puzzle solution using iterative deepening (entry)
/**
 * Find a slide puzzle solution with iterative deepening search using recursion.
 *
 * @param start_sp Starting puzzle configuration
 * @param end_sp Ending puzzle configuration
 *
 * @return Calculated puzzle solution sequence from start to end
 */
vector<slide_puzzle_t> slpz_search_itdp(const slide_puzzle_t &start_sp,
            const slide_puzzle_t &end_sp) {
    //vector<slide_puzzle_t> path;
    vector<slide_puzzle_t> seq;
    int depth = 0;
    int maxDepth = 20;
    bool found = false;
    //unordered_set<slide_puzzle_t> visited_sp;
    //visited_sp.insert(start_sp);
    //seq = slpz_search_itdp_r(start_sp, end_sp, visited_sp, path, 0);
    while(!found && depth <= maxDepth) {
        vector<slide_puzzle_t> path;
        path.push_back(start_sp);
        unordered_set<slide_puzzle_t> visited_sp;
        visited_sp.insert(start_sp);
        seq = slpz_search_itdp_r(start_sp, end_sp, visited_sp, path, depth);
        if(!seq.empty()) {
            found = true;
        }
        depth++;
    }
    return seq;
}

//==============================================================================

vector<slide_puzzle_t> slpz_search(const slide_puzzle_t &start_sp,
                                   const slide_puzzle_t &end_sp) {
    vector<slide_puzzle_t> slpz_seq;
    slpz_seq = slpz_search_itdp(start_sp, end_sp);
    return slpz_seq;
}

//endregion Slide puzzle

//region Slide puzzle exec

//==============================================================================
//==============================================================================
// Slide puzzle exec
//==============================================================================
//==============================================================================

//==============================================================================
// Slide puzzle unit tests
//==============================================================================

//==============================================================================

// Blank location
void do_prg_test_slpz_blank_location() {
    //int i = 1;
    //BOOST_CHECK(i*i == 1);

    slpz_loc_t bl = gg_slpz_5.blank_loc();
    slpz_loc_t bl_test(2, 3);
    cout << "Expected blank location for gg_slpz_5 is "
         << bl_test.a << " " << bl_test.b << endl;
    cout << "Actual blank location for gg_slpz_5 is "
         << bl.a << " " << bl.b << endl;
    if (bl.a == bl_test.a && bl.b == bl_test.b) {
    } else {
        cout << "ERROR: blank location for gg_slpz_5 is incorrect"
                << endl;
    }
    BOOST_CHECK(bl.a == bl_test.a && bl.b == bl_test.b);
}

BOOST_AUTO_TEST_CASE(prg_test_slpz_blank_location) { // NOLINT
    do_prg_test_slpz_blank_location();
}

//==============================================================================

// Pieces in correct location
void do_prg_test_slpz_piece_location() {
    int num_correct = gg_slpz_5.board_status_pos();
    int num_correct_test = 10;
    cout << "Expected correct position count for gg_slpz_5 is "
         << num_correct_test << endl;
    cout << "Actual correct position count for gg_slpz_5 is "
         << num_correct << endl;
    if (num_correct == num_correct_test) {
    } else {
        cout << "ERROR: correct position count for gg_slpz_5 is incorrect"
                << endl;
    }
    BOOST_CHECK(num_correct == num_correct_test);
}

BOOST_AUTO_TEST_CASE(prg_test_slpz_piece_location) { // NOLINT
    do_prg_test_slpz_piece_location();
}

//==============================================================================

// Slide puzzle solver
void do_prg_test_slpz_solve_puzzle()
{
    ofstream ofs("slpz-out.txt");
    vector<slide_puzzle_t> slpz_seq;
    const slide_puzzle_t &slpz_start(gg_slpz_5);
    slpz_seq = slpz_search(slpz_start, gg_slpz_solved);

    if (!slpz_seq.empty()) {
        cout << "Slide puzzle solution found" << endl;
        cout << "solution path length = " << slpz_seq.size() << endl;
        cout << "start" << endl;
        cout << slpz_start;
        cout << "end" << endl;
        cout << gg_slpz_solved;
        for (const auto &sp: slpz_seq) {
            cout << "state" << endl;
            cout << sp;
            ofs << "state" << endl;
            ofs << sp;
        }
        //path_cost = path_cost_dist(mi, path);
        //cout << "Path cost is " << path_cost;
        //cout << endl;
    } else {
        cout << "ERROR: no solution found for slide puzzle" << endl;
        ofs << "error" << endl;
    }
    BOOST_CHECK(!slpz_seq.empty());

    if(!slpz_seq.empty() && slpz_seq[0] == slpz_start && gg_slpz_solved == slpz_seq[slpz_seq.size()-1]) {
        cout << "Slide puzzle solution start and goal found in path" << endl;
    } else {
        cout << "ERROR: Slide puzzle solution start or goal not in path" << endl;
    }
    BOOST_CHECK(!slpz_seq.empty() && slpz_seq[0] == slpz_start && gg_slpz_solved == slpz_seq[slpz_seq.size()-1]);
}

BOOST_AUTO_TEST_CASE(prg_test_slpz_solve_puzzle) { // NOLINT
    do_prg_test_slpz_solve_puzzle();
}

//==============================================================================
// Slide puzzle main execution
//==============================================================================

void slpz_exec() {
    //cout << "Hello" << endl;

    //bool isTestRun = getenv("APP_MODE_TEST_SLPZ") == NULL ? false : true; // NOLINT

    // Check slide puzzle
    if(true) // NOLINT
    {
        do_prg_test_slpz_blank_location();
        do_prg_test_slpz_piece_location();
        do_prg_test_slpz_solve_puzzle();
    }

    //cout << "Bye" << endl;
}

//endregion Slide puzzle exec

//region Other items

//==============================================================================
//==============================================================================
// Other items
//==============================================================================
//==============================================================================

//endregion Other items

//region Other

//==============================================================================
//==============================================================================
// Other
//==============================================================================
//==============================================================================

//BOOST_AUTO_TEST_CASE(prg_test_submod_001)
//{
//    int i = 1;
//    BOOST_CHECK(i*i == 1);
//}

//endregion Other

//==============================================================================
//==============================================================================
// End
//==============================================================================
//==============================================================================

//#pragma clang diagnostic pop
