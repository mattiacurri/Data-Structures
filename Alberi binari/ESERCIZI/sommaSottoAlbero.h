int sommaSottoAlbero(const Tree_ptr<int> &B, int k, Tree_ptr<int>::node n, int &count) {
    if (B.leftEmpty(n) && B.rightEmpty(n)) {
        if (B.read(n) == k) {
            count++;
        }
        return B.read(n);
    } else {
        int sx = 0;
        int dx = 0;
        if (!B.leftEmpty(n)) {
            sx = sommaSottoAlbero(B, k, B.leftNode(n), count);
            if (sx + B.read(n) == k) {
                count++;
            }
        }
        if (!B.rightEmpty(n)) {
            dx = sommaSottoAlbero(B, k, B.rightNode(n), count);
            if (dx + B.read(n) == k) {
                count++;
            }
        }
        if (!B.leftEmpty(n) && !B.rightEmpty(n)) {
            if (sx + dx + B.read(n) == k) {
                count++;
            }
        }
        return (B.read(n) + sx + dx);
    }
}