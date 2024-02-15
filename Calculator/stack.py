class Stack:
	def __init__(self):
	
		self.l=[]
		
	
	def push(self, item):
		self.l.append(item)

	

	def peek(self):
		if len(self.l)>0 :
			return self.l[-1]
		

	def pop(self):
		if len(self.l)>0:
			return self.l.pop()
		

	def is_empty(self):
		return self.l==[]
		

	def __str__(self):
		s=""
		for i in range(len(self.l)):
			s=s+str(self.l[-i-1])
			s=s+" "
		return s[:-1]

		

	def __len__(self):
		return len(self.l)
