from django.contrib import auth
from django.db import models

class Map(models.Model):
	userinfo = models.ForeignKey(auth.models.User)
	map_data = models.TextField()
	def __unicode__(self):
		return self.userinfo.username
