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