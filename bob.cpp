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
    if(false) {
        // Found a puzzle solution path that leads to the goal, at the desired
        // path length
        seq = path;
        // assert(depth == 0); // should be at zero depth by now
    // TODO: Condition for checking that more paths should be considered
    } else if(false) {
        // Have not yet found a solution, but still have deeper paths remaining
        // to explore
        const slide_puzzle_t& curr_sp(start_sp);

        // List of possible next moves
        /* const */ vector<slide_puzzle_t> next_possible_sp;

        // To avoid cycles, do not go back to puzzles that have already
        // been visited
        for (const auto &next_sp: next_possible_sp) {
            // TODO: fix condition
            if (false) {
                // This puzzle has already been visited,
                // so do nothing.
            } else {
                // This puzzle has not been visited, so visit it.
                // TODO: Adjust visited_sp and path
                vector<slide_puzzle_t> subseq;
                // TODO: recursion
                //subseq = slpz_search_itdp_r(...,
                //        ..., visited_sp, ..., depth - 1);
                if(!subseq.empty()) {
                    // Found a solution
                    seq = subseq;
                    break; // prefer a different approach later...
                }
                // TODO: Readjust visited_sp and path
            }
        }
    }
    return seq;
}