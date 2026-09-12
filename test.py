def get_index(c, s):
    for i in range(len(s)):
        if s[i] == c:
            return i
    return -1


def par(s) -> bool:
    start: str = '({['
    end: str = "}])"
    stash: str = ''
    for i in s:
        if i in start:
            stash = end[get_index(i, start) - 1] + stash
        elif i in end:
            if not stash:
                return False
            if stash[0] != i:
                return False
            else:
                stash = stash[1:]
    return stash == ''


if __name__ == '__main__':
    print(par('{}'))
    n_coder = 8
    coder = 1
    print((coder + n_coder + n_coder - 2) % n_coder + 1)