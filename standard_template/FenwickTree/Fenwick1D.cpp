template <class T>
class BIT
{
private:
    int N;
    vector<T> A;
    vector<T> BIIT;

public:
    BIT(int size) : N(size), A(size + 1), BIIT(size + 1) {}

    void set(ll idx, ll val)
    {
        update(idx, val - A[idx]);
        A[idx] = val;
    }
    void update(ll idx, ll diff)
    {
        for (idx = idx; idx <= N; idx += idx & (-idx))
            BIIT[idx] += diff;
    }
    ll sumQuery(ll idx)
    {
        if (idx == 0)
            return 0LL;
        ll summ = 0;
        for (idx = idx; idx > 0; idx -= idx & (-idx))
            summ += BIIT[idx];
        return summ;
    }
};
