    // TODO: Condition for checking that path to solution was found
{
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