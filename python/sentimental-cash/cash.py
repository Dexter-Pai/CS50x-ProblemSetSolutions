import cs50


def main():
    cents = get_cents()
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    coins = quarters + dimes + nickels + pennies
    print(coins)


def get_cents():
    i = cs50.get_float("Input Cents: ")
    while i < 0:
        i = cs50.get_float("Input Cents: ")
    return i * 100


def calculate_quarters(cents):
    if (cents >= 25):
        i = int(cents / 25)
        return i
    else:
        return 0


def calculate_dimes(cents):
    if (cents >= 10):
        i = int(cents / 10)
        return i
    else:
        return 0


def calculate_nickels(cents):
    if (cents >= 5):
        i = int(cents / 5)
        return i
    else:
        return 0


def calculate_pennies(cents):
    return cents


if __name__ == "__main__":
    main()