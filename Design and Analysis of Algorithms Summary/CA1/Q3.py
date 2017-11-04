def find_max(arr, index, max_dic):
	if index in max_dic:
		return max_dic[index]

	n = 0
	if index == 1:
		n = arr[index-1]
	else:
		n = max(arr[index-1] + find_max(arr, index-2, max_dic), find_max(arr, index-1, max_dic))
	max_dic[index] = n
	return n

if __name__ == '__main__':
	n = int(input())

	arr = input()
	arr = list(map(int, arr.split()))

	m1 = {0: 0}
	m2 = {0: 0}

	print( max(find_max(arr[1:], n-1, m2), find_max(arr[:-1], n-1, m1)) )