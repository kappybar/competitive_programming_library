
def Miller_Rabin(x):
    import random
    if x < 2 : return False
    if x == 2 : return True
    if x & 1 == 0: return False

    d = x - 1
    while d%2 ==0 : d //= 2

    for _ in range(20):
        p = random.randint(1,x-1)
        a = pow(p,d,x)
        s = d

        while s != x-1 and a != 1 and a != x-1:
            a = (a * a)%x
            s <<= 1

        if a != x-1 and s%2 == 0: return False

    return True

n = int(input())

for _ in range(n):
    x = int(input())
    print(x,1 if Miller_Rabin(x) else 0)