height = input("Height: ")
while not (height.isdigit() and height == ''):
    if (height.isdigit()):
        if int(height) >= 1 and int(height) <= 8:
            break
        else:
            height = input("Height: ")
    else:
        height = input("Height: ")

height = int(height)
r = 0
for h in range(height):
    for ra in range(height - r - 1):
        print(' ', end='')
    r += 1
    for a in range(r):
        print('#', end='')
    print('  ', end='')
    for a in range(r):
        print('#', end='')
    print()