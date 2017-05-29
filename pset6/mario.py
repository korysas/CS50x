import sys

def main():
    height = input('Height: ')

    height = int(height)

    for i in range(0, height):
        for j in range(0, height - i - 1):
            print(' ', end='')
        for k in range(0, i + 1):
            print('#', end='')
        print('')

if __name__ == '__main__':
    main()