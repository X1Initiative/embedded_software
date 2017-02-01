# Data Processing Overview
# 1. Queue1: sensor directions (receive/pop at rate of 1ms)
# 2. Queue2: computer vision instructions (receive/pop when turn is executed)
# 3. Priorities
#	- Sensor distance gets extremely low -> Turn on that motor/turn off opposing motor
#   - Sensor distance in travel direction gets low -> Slowly turn that motor on/slowly turn opposing motor off
#	- Turn on motor opposite of direction of travel -> Slowly turn on motor opposite of desired travel direction

class Queue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.insert(0,item)

    def dequeue(self):
        return self.items.pop()

    def size(self):
        return len(self.items)

ee_queue = Queue()
cv_queue = Queue()

cv_file = open('temp_cv_file.txt', 'r')
cv_queue.items = cv_file.read().splitlines()
cv_queue.items.reverse()

num_cv_directions = cv_queue.size()
for i in range(num_cv_directions):
	print(cv_queue.dequeue())