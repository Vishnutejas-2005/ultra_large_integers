def read_file(filename: str) -> tuple[list[int], int]:
    with open(filename) as file:
        # First line is the target
        target = int(file.readline())
        # Second line is the number of integers
        n = int(file.readline())
        # Read the n integers and return them as a list
        return ([int(file.readline()) for _ in range(n)], target)


def count_pairs(data: list[int], target: int) -> int:
    """Count the number of pairs of
    list indices i < j such that
    data[i] - data[j] = target.
    Time complexity: Naive O(n^2).
    """
    result = 0
    n = len(data)
    for i in range(n - 1):
        for j in range(i + 1, n):
            if data[i] - data[j] == target:
                result += 1
    return result


def test_count_pairs():
    # Simple correctness tests
    assert count_pairs([1, 2, 3, 4, 5], 1) == 0
    assert count_pairs([5, 4, 3, 2, 1], 1) == 4
    assert count_pairs([1, 2, 3, 4, 5], -3) == 2
    # Test with huge integers
    assert count_pairs([10**20 + 2, 10**20 + 1, 10**20], 1) == 2
    print("count_pairs.py: All tests passed")

import ctypes

def count_pairs_file_to_be_replicated_using_adt(filename: str) -> int:
    data, target = read_file(filename)
    return count_pairs(data, target)

def count_pairs_file(filename: str) -> int:
    # Load the shared library
    lib = ctypes.CDLL('./uint.so')

    # Define the function prototype
    lib.open_file.restype = ctypes.c_int
    lib.open_file.argtypes = [ctypes.c_char_p]

    # Call the C function
    input_str = filename
    return lib.open_file(input_str.encode('utf-8'))

