import numpy as np
import requests
import json


NaN = float('nan')
class cvat_dealt:

	def __init__ (self):
		self.outputs = []
		self.longsf = [(NaN)]
		self.shortsf = [(NaN)]
		self.key = ''
		self.f = {}

	def dtu(self):
		h = '{"username":"test","password":"bMptg48UvC2h83v6gq5x"}'
		self.f = requests.post("http://ec2-3-68-67-13.eu-central-1.compute.amazonaws.com:8080/api/v1/auth/login", json = json.loads(h))
		key = self.f.json()['key']
		print (key)

	def fre(self):
		hw = { 'X-CSRFToken': self.f.cookies['csrftoken'],  'Content-Type': 'application/json', 'accept': 'application/json'}
		e = requests.post("http://ec2-3-68-67-13.eu-central-1.compute.amazonaws.com:8080/api/v1/tasks", headers = hw, cookies = self.f.cookies)
		print (e.json())

