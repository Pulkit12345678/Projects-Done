from stack import Stack

class SimpleCalculator:
	def __init__(self):
		"""
		Instantiate any data attributes
		"""
		self.s = None
		self.history = []
		pass

	def evaluate_expression(self, input_expression):
		"""
		Evaluate the input expression and return the output as a float
		Return a string "Error" if the expression is invalid
		"""
		self.s = input_expression
		l = ['+','-','*','/',' ']
		ls = []
		lst = []
		def expre(s):
			if s.isnumeric()==True:
				ls.append(s)
				return ls,lst
			else:
				for ele in s:
					if ele in l:
						i = s.index(ele)
						ls.append(s[:i])
						lst.append(ele)
						s = s[i+1:]
				return expre(s)
		phi = expre(self.s)
		a = phi[0]
		b = phi[1]
		if len(a)!=2 or len(b)!=1:
			self.history = [(self.s,"Error")] + self.history
			return "Error"
		else:
			if b[0]=='+':
				self.history = [(self.s,float(a[0])+float(a[1]))] + self.history
				return float(a[0])+float(a[1])
			elif b[0]=='-':
				self.history = [(self.s,float(a[0])-float(a[1]))]+ self.history
				return float(a[0])-float(a[1])
			elif b[0]=='*':
				self.history = [(self.s,float(a[0])*float(a[1]))]+ self.history
				return float(a[0])*float(a[1])
			elif b[0]=='/':
				if a[1]=='0':
					self.history = [(self.s,"Error")] + self.history
					return "Error"
				else:
					self.history = [(self.s,float(a[0])/float(a[1]))]+ self.history
					return float(a[0])/float(a[1])
	def get_history(self):
		"""
		Return history of expressions evaluated as a list of (expression, output) tuples
		The order is such that the most recently evaluated expression appears first 
		"""
		return self.history