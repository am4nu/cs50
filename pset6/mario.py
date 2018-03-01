import cs50


def do():
    on = 0

    while(True):
        print("height: ", end="")
        n = cs50.get_int()
        if n >= 0 and n <= 23:
            break

    space = n - 1
    curspace = space

    for i in range(1, n * (n + 2)):

        if curspace == 0:
            on = 1

        else:
            on = 0

        if on == 0:
            print(" ", end="")
            curspace = curspace - 1

        elif i % (n + 2) == 0:
            print()
            on = 0
            space = space - 1
            curspace = space

        else:
            print("#", end="")

    print()


if __name__ == "__main__":
    do()
