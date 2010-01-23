# Create your views here.
from django.template import Context, loader
from django.http import HttpResponse, Http404
from django.shortcuts import render_to_response, get_object_or_404
from tsite.polls.models import Poll

def index(request):
	poll_list = Poll.objects.all()
	poll_list = poll_list.order_by('-pub_date')[:5]

	template = loader.get_template('polls/index.html')
	c = Context({'latest_poll_list' : poll_list})
	return HttpResponse(template.render(c))

def detail(request, poll_id):
	p = get_object_or_404(Poll, pk=poll_id)
	return render_to_response('polls/detail.html', {'poll':p})
