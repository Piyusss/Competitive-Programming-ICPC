string manacher_algo(string s)
{
    string t = "$";
    for (char c : s)
        t += "#" + string(1, c);
    t += "#";

    int n = t.length();
    vector<int> p(n, 0);
    int center = 0, right = 0;

    for (int i = 1; i < n - 1; ++i)
    {
        if (i < right)
        {
            p[i] = min(right - i, p[2 * center - i]);
        }

        while (t[i + p[i] + 1] == t[i - p[i] - 1])
        {
            p[i]++;
        }

        if (i + p[i] > right)
        {
            center = i;
            right = i + p[i];
        }
    }

    int maxLen = 0, start = 0;
    for (int i = 1; i < n - 1; ++i)
    {
        if (p[i] > maxLen)
        {
            maxLen = p[i];
            start = (i - p[i]) / 2;
        }
    }

    return s.substr(start, maxLen);
}
