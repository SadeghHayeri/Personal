def inversion_merge(left_array, right_array):
    i = j = 0
    sorted_array = []
    inversions = []

    while i < len(left_array) and j < len(right_array):
        if left_array[i][0] > right_array[j][0]:
            sorted_array.append(left_array[i])
            i+=1
        else:
            sorted_array.append(right_array[j])
            for r in left_array[i:]:
                inversions += [(r, right_array[j])]
            j+=1

    sorted_array += left_array[i:]
    sorted_array += right_array[j:]

    return sorted_array, inversions

def inversion(array):
    if len(array) == 1:
        return array, []

    mid = len(array) // 2

    left_array, left_inversions = inversion(array[:mid])
    right_array, right_inversions = inversion(array[mid:])
    sorted_array, merge_inversions = inversion_merge(left_array, right_array)

    return sorted_array, left_inversions + right_inversions + merge_inversions

if __name__ == '__main__':
    n = input()
    arr = input()
    arr = list(map(int, arr.split()))

    _, inversions = inversion( list(zip(list(reversed(arr)), list(reversed(range(len(arr)))))) )

    res = len(arr) * [0]
    for i, j in inversions:
        res[j[1]] += 1

    print(" ".join(map(str, res)))