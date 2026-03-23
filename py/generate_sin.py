import math

if __name__ == "__main__":
    for i in range(64):
        value = int(math.sin(i / 128 * math.pi) * (2**15 - 1))
        print(f"{i:>02}: rom_sin = 15'h{value:>04x};")
