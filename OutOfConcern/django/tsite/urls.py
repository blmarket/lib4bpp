from django.conf.urls.defaults import *

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    # Example:
    # (r'^tsite/', include('tsite.foo.urls')),

    # Uncomment the admin/doc line below and add 'django.contrib.admindocs' 
    # to INSTALLED_APPS to enable admin documentation:
    # (r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
	(r'^polls/$', 'tsite.polls.views.index'),
	(r'^polls/(?P<poll_id>\d+)$', 'tsite.polls.views.detail'),
    (r'^admin/(.*)', admin.site.root),
	(r'^$', 'tsite.main.views.index'),
)
