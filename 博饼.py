from random import randint
# 创建虚拟骰子的类
class Die():
	def __init__(self, die_sides=6):
		self.die_sides = die_sides
	def roll(self):
		return randint(1, self.die_sides)
# 创建6个虚拟的骰子
die_1 = Die()
die_2 = Die()
die_3 = Die()
die_4 = Die()
die_5 = Die()
die_6 = Die()
# 记录每一次博饼的结果
def bb():
	results = [die_1.roll(), die_2.roll(), die_3.roll(), die_4.roll(),
	die_5.roll(), die_6.roll()]
	return results
# 博饼的人数
def num():
	num_bb = int(input('游戏人数：',))
	return num_bb
# 定义博饼奖项的对应编号
A = "状元插金花"
B = "六勃红"
C = "遍地锦"
D = "六勃黑"
E = "五红"
F = "五子"
G = "四红"
H = "对堂"
I = "三红"
J = "四进"
K = "二举"
L = "一秀"
M = "None"
bb_award = [A, B, C, D, E, F, G, H, I, J, K, L, M]
bb_result = []
# 创建函数，检查每次掷骰子结果所对应的博饼奖项
def check_result():
	if bb().count(1) == 2 and bb().count(4) == 4:
		bb_result.append(A)
	elif bb().count(4) == 6:
		bb_result.append(B)
	elif bb().count(1) == 6:
		bb_result.append(C)
	elif bb().count(2) == 6 or bb().count(3) == 6 or bb().count(5) == 6 or bb().count(6) == 6:
		bb_result.append(D)
	elif bb().count(4) == 5:
		bb_result.append(E)
	elif bb().count(1) == 5 or bb().count(2) == 5 or bb().count(3) == 5 or bb().count(5) == 5 or bb().count(6) == 5:
		bb_result.append(F)
	elif bb().count(4) == 4:
		bb_result.append(G)
	elif bb().count(1) == 1 and bb().count(2) == 1 and bb().count(3) == 1 and bb().count(4) == 1 and bb().count(5) == 1 and bb().count(6) == 1:
		bb_result.append(H)
	elif bb().count(4) == 3:
		bb_result.append(I)
	elif bb().count(1) == 4 or bb().count(2) == 4 or bb().count(3) == 4 or bb().count(5) == 4 or bb().count(6) == 4:
		bb_result.append(J)
	elif bb().count(4) == 2:
		bb_result.append(K)
	elif bb().count(4) == 1:
		bb_result.append(L)
	else:
		bb_result.append(M)
	return bb_result
# 执行博饼
num_bb = num()
def res():
	result1 = 'None'
	global num_bb
	for num in range(num_bb):
		bb()
		result1 = check_result()
	return  result1
res()



