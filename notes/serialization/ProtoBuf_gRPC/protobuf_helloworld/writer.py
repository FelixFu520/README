from felix.helloworld_pb2 import helloworld

def main():
    hw = helloworld()
    hw.id = 123
    hw.str = "eric"
    print(hw)

    with open("mybuffer.io", "wb") as f:
        f.write(hw.SerializeToString())

if __name__ == "__main__":
    main()