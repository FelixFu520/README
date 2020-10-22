from felix.helloworld_pb2 import helloworld


def main():
    hw = helloworld()
    with open("mybuffer.io", "rb") as f:
        hw.ParseFromString(f.read())
        print(hw.id)
        print(hw.str)


if __name__ == "__main__":
    main()