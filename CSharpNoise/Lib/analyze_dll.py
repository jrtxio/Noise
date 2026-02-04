
import sys

def strings(filename, min_len=4):
    with open(filename, "rb") as f:
        result = ""
        for b in f.read():
            c = chr(b)
            if c.isprintable():
                result += c
            else:
                if len(result) >= min_len:
                    yield result
                result = ""

def main():
    dll_path = "libracketcs-x86_64-windows.dll"
    print(f"Scanning {dll_path}...")
    try:
        count = 0
        with open("dll_dump.txt", "w", encoding="utf-8", errors="replace") as f_out:
            for s in strings(dll_path):
                if len(s) > 3:
                     f_out.write(s + "\n")
        print("Dumped to dll_dump.txt")
    except FileNotFoundError:
        print("File not found.")

if __name__ == "__main__":
    main()
